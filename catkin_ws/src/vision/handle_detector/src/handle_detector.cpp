#include "handle_detector/handle_detector.h"

handleDetector::handleDetector(ros::NodeHandle &nh)
{
        std::cout << "Hello!" << '\n';
        nh_=nh;
        ros::NodeHandle nh_priv("~");
        nh_priv.param<float>("voxel_size",voxelSize,0.01);
        nh_priv.param<float>("crop_size",cropSize,2.0);
        nh_priv.param<float>("seg_ratio",segRatio,0.5);
        nh_priv.param<float>("prism_height",prismHeight,0.20);
        nh_priv.param<float>("cluster_tolerance",clusterTolerance,0.20);
        nh_priv.param<int>("min_points_cluster",minPointsCluster,20);
        nh_priv.param<int>("max_points_cluster",maxPointsCluster,500);
}

void handleDetector::setCallback()
{
        pclSubcriber=nh_.subscribe("/cloud",1,&handleDetector::pclCallback,this);
        pclPublisher=nh_.advertise<sensor_msgs::PointCloud2>("/processed_cloud",10);
        markerPub = nh_.advertise<visualization_msgs::Marker>("centroids_marker",1);
        return;
}

void handleDetector::setServiceServer()
{
        rgbdClient = nh_.serviceClient<point_cloud_manager::GetRgbd>("/hardware/point_cloud_man/get_rgbd_wrt_robot");
        handleServer = nh_.advertiseService("/vision/handle_detector/detect_handles", &handleDetector::getHandles,this);
        pclPublisher=nh_.advertise<sensor_msgs::PointCloud2>("/processed_cloud",1);
        markerPub = nh_.advertise<visualization_msgs::Marker>("centroids_marker",1);
        return;
}

bool handleDetector::getHandles(
        vision_msgs::DetectHandles::Request  &req,
        vision_msgs::DetectHandles::Response &res)
{
        std::cout << "Hi there" << '\n';
        std::vector<geometry_msgs::Point> p;
        serverProcess(p);
        res.handle_centroids = p;
        return true;
}

bool handleDetector::serverProcess(std::vector<geometry_msgs::Point> &centroids)
{
        point_cloud_manager::GetRgbd srv;
        if(!rgbdClient.call(srv))
        {
                std::cout << "HandleDetector:: Cannot get point cloud" << std::endl;
                return false;
        }

        pointCloudXYZRGB::Ptr cloud(new pointCloudXYZRGB);
        pointCloudXYZRGB::Ptr procCloud(new pointCloudXYZRGB);
        pcl::fromROSMsg(srv.response.point_cloud, *cloud);
        if (voxelSize>0) {
                voxelFiltering(cloud, procCloud,voxelSize);
                cropCloud(procCloud,procCloud,cropSize);
        }
        else
        {
                cropCloud(cloud,procCloud,cropSize);
        }
        int nPoints = procCloud->points.size ();
        std::vector<planeCloud> planes;
        //Extract all panes perpendicular to z
        std::cout << " Had: "<< nPoints <<'\n';
        do {
                planeCloud PC;
                if(!extractPlane(procCloud,*procCloud,PC))
                {
                        std::cout << "FAiled to get a plane" << '\n';
                        return false;
                }  planes.push_back(PC);
                // std::cout << "\tHave" <<  procCloud->points.size()<<'\n';
                // std::cout << "Plane is of size: " << PC.inliers.points.size()<< '\n';
        } while(procCloud->points.size() > segRatio * nPoints);
        //use closest cloud
        planeCloud closestPlane = getClosestPlane(planes);
        pointCloudXYZRGB::Ptr projectedCloud( new pointCloudXYZRGB);
        projectCloud(closestPlane,projectedCloud);
        pointCloudXYZRGB::Ptr handlesCloud( new pointCloudXYZRGB);
        polygonalSegmentation(procCloud, projectedCloud, handlesCloud );
        std::vector<pcl::PointIndices> cluster_indices;
        clusterExtraction(handlesCloud,cluster_indices);
        std::vector<Eigen::Matrix<float,4,1> > centroides;
        getCentroids(handlesCloud,cluster_indices,centroides);

        makeVizMessageAndPublish(centroides);

        //publish cloud
        sensor_msgs::PointCloud2 cloud_msg;
        pcl::toROSMsg(*handlesCloud,cloud_msg);
        pclPublisher.publish(cloud_msg);

        //copy eigen centroides to centroids
        centroids.resize(centroides.size());
        for (size_t i = 0; i < centroids.size(); i++) {
                centroids[i].x=centroides[i](0);
                centroids[i].y=centroides[i](1);
                centroids[i].z=centroides[i](2);
        }
        std::cout << "Handle detecctor:: Got: "
                  << centroids.size()
                  << "centroids" <<'\n';
        return true;
}

void handleDetector::pclCallback(const sensor_msgs::PointCloud2ConstPtr &msg)
{
        // std::cout << "Got a new point_cloud!!!" << '\n';
        // printf("[%d,%d]\n",msg->width,msg->height );
        pointCloudXYZRGB::Ptr cloud(new pointCloudXYZRGB);
        pointCloudXYZRGB::Ptr procCloud(new pointCloudXYZRGB);
        pcl::fromROSMsg(*msg, *cloud);
        if (voxelSize>0) {
                voxelFiltering(cloud, procCloud,voxelSize);
                cropCloud(procCloud,procCloud,cropSize);
        }
        else
        {
                cropCloud(cloud,procCloud,cropSize);
        }
        int nPoints = procCloud->points.size ();
        std::vector<planeCloud> planes;
        //Extract all panes perpendicular to z
        std::cout << " Had: "<< nPoints <<'\n';
        do {
                planeCloud PC;
                if(!extractPlane(procCloud,*procCloud,PC))
                {
                        std::cout << "FAiled to get a plane" << '\n';
                        return;
                }
                planes.push_back(PC);
                // std::cout << "\tHave" <<  procCloud->points.size()<<'\n';
                // std::cout << "Plane is of size: " << PC.inliers.points.size()<< '\n';
        } while(procCloud->points.size() > segRatio * nPoints);
        //use closest cloud
        planeCloud closestPlane = getClosestPlane(planes);
        pointCloudXYZRGB::Ptr projectedCloud( new pointCloudXYZRGB);
        projectCloud(closestPlane,projectedCloud);
        pointCloudXYZRGB::Ptr handlesCloud( new pointCloudXYZRGB);
        polygonalSegmentation(procCloud, projectedCloud, handlesCloud );
        std::vector<pcl::PointIndices> cluster_indices;
        clusterExtraction(handlesCloud,cluster_indices);
        std::vector<Eigen::Matrix<float,4,1> > centroides;
        getCentroids(handlesCloud,cluster_indices,centroides);
        makeVizMessageAndPublish(centroides);

        //publish cloud
        sensor_msgs::PointCloud2 cloud_msg;
        pcl::toROSMsg(*handlesCloud,cloud_msg);
        pclPublisher.publish(cloud_msg);
        return;
}

void handleDetector::voxelFiltering(pointCloudXYZRGB::Ptr cloud_in, pointCloudXYZRGB::Ptr cloud_out, float leafSize) {
        //Simple voxel filtering object
        pcl::VoxelGrid<pcl::PointXYZRGB> sor;
        sor.setInputCloud (cloud_in);
        sor.setLeafSize (leafSize, leafSize, leafSize);
        sor.filter (*cloud_out);
}

bool handleDetector::extractPlane(
        pointCloudXYZRGB::Ptr cloud_in,
        pointCloudXYZRGB &cloud_out,
        planeCloud &plane)
{
        //extrac most dominant plane from cloud
        //and retuns the plane model and point belonging to it
        //it also removes point from pointcloud
        pointCloudXYZRGB::Ptr cloud_p (new pointCloudXYZRGB);
        pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients ());
        pcl::PointIndices::Ptr inliers (new pcl::PointIndices ());
        // Create the segmentation object
        pcl::SACSegmentation<pcl::PointXYZRGB> seg;
        // Optional
        seg.setOptimizeCoefficients (true);
        // Mandatory
        //seg.setModelType (pcl::SACMODEL_PLANE);
        seg.setModelType (pcl::SACMODEL_PERPENDICULAR_PLANE);
        seg.setMethodType (pcl::SAC_RANSAC);
        seg.setMaxIterations (1000);
        seg.setDistanceThreshold (0.02);
        //parrallel to z == perpendicular to x and y
        Eigen::Vector3f ax(1,0,0);
        seg.setAxis(ax);
        seg.setEpsAngle(15*M_PI/180); //search around 10 degrees

        // Create the filtering object
        pcl::ExtractIndices<pcl::PointXYZRGB> extract;

        seg.setInputCloud (cloud_in);
        //std::cout << "Extract" << '\n';
        seg.segment (*inliers, *coefficients);
        if (inliers->indices.size () == 0)
        {
                std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
                return false;
        }
        // Extract the inliers and store them on output
        extract.setInputCloud (cloud_in);
        extract.setIndices (inliers);
        extract.setNegative (false);
        extract.filter (plane.inliers);
        plane.model = *coefficients;
        // Extract the inliers
        extract.setIndices (inliers);
        extract.setNegative (true);
        extract.filter (cloud_out);

        return true;
}

void handleDetector::cropCloud(pointCloudXYZRGB::Ptr cloud_in, pointCloudXYZRGB::Ptr cloud_out, float zCrop)
{
        //Crops cloud in z axis ,kiinect frame.
        pcl::PassThrough<pcl::PointXYZRGB> pass;
        pass.setInputCloud (cloud_in);
        pass.setFilterFieldName ("z");
        pass.setFilterLimits (0.05, zCrop);
        //pass.setFilterLimitsNegative (true);
        pass.filter(*cloud_out);
        return;

}

planeCloud handleDetector::getClosestPlane(
        std::vector<planeCloud> &planes)
{
        int closestIdx=0;
        float minDist=100;
        for (int i = 0; i < planes.size(); i++)
        {
                //std::cout << planes[i].model.values[3] << '\n';
                if (minDist>fabs(planes[i].model.values[3]))
                {
                        minDist=fabs(planes[i].model.values[3]);
                        closestIdx=i;
                }
        }
        // std::cout <<"\t" << planes[closestIdx].model.values[3] << " "<< closestIdx<< '\n';
        return planes[closestIdx];

}

void handleDetector::projectCloud(
        planeCloud pC,
        pointCloudXYZRGB::Ptr cloud_out)
{
        pointCloudXYZRGB::Ptr cloudPTR(new pointCloudXYZRGB);
        pcl::ModelCoefficients::Ptr coeffPTR (new pcl::ModelCoefficients ());
        *cloudPTR = pC.inliers;
        *coeffPTR = pC.model;
        pcl::ProjectInliers<pcl::PointXYZRGB> proj;
        proj.setModelType (pcl::SACMODEL_PLANE);
        proj.setInputCloud (cloudPTR);
        proj.setModelCoefficients (coeffPTR);
        proj.filter (*cloud_out);
}

void handleDetector::polygonalSegmentation(
        pointCloudXYZRGB::Ptr cloud_in,
        pointCloudXYZRGB::Ptr cloud_plane,
        pointCloudXYZRGB::Ptr cloud_out)
{
        //calcculates convex hull
        pointCloudXYZRGB::Ptr hull_cloud (new pointCloudXYZRGB ());
        pcl::ConvexHull<pcl::PointXYZRGB> hull;
        // hull.setDimension (2); // not necessarily needed, but we need to check the dimensionality of the output
        hull.setInputCloud (cloud_plane);
        hull.reconstruct (*hull_cloud);
        pcl::PointIndices::Ptr inPrism (new pcl::PointIndices ());
        if (hull.getDimension () == 2)
        {
                pcl::ExtractPolygonalPrismData<pcl::PointXYZRGB> prism;
                prism.setInputCloud (cloud_in);
                prism.setInputPlanarHull (hull_cloud);
                prism.setHeightLimits (0.05, prismHeight);
                prism.segment (*inPrism);
                pcl::ExtractIndices<pcl::PointXYZRGB> extract;
                extract.setInputCloud (cloud_in);
                extract.setIndices (inPrism);
                extract.setNegative (false);
                extract.filter (*cloud_out);
        }
        else
        {
                printf ("!!!!The input cloud does not represent a planar surface!!!!\n");
        }
        return;
}

void handleDetector::clusterExtraction(
        pointCloudXYZRGB::Ptr cloud_in,
        std::vector<pcl::PointIndices> &clusters )
{
// Creating the KdTree object for the search method of theextraction
        pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
        tree->setInputCloud (cloud_in);
        //Eclidean segmentation
        pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
        ec.setClusterTolerance (clusterTolerance);
        ec.setMinClusterSize (minPointsCluster);
        ec.setMaxClusterSize (maxPointsCluster);
        ec.setSearchMethod (tree);
        ec.setInputCloud (cloud_in);
        std::cout << "\t" << "processed cloud hasmo " << cloud_in->size() <<'\n';
        ec.extract (clusters);
        for (size_t i = 0; i < clusters.size(); i++) {
                std::cout << "In cluster: " << i << " there are: " << clusters[i].indices.size() << " points"<<'\n';
        }
}

void handleDetector::getCentroids(
        pointCloudXYZRGB::Ptr cloud_in,
        std::vector<pcl::PointIndices> &clusters,
        std::vector<Eigen::Matrix<float,4,1> > &centroids
        )
{
        //from all detected clusters, get 3d centroid.
        centroids.clear();
        centroids.resize(clusters.size());
        for (size_t i = 0; i < centroids.size(); i++)
        {
                //iterate over all clusters and get centroids
                //Not enterily sure why a 4d vector....
                pcl::compute3DCentroid  (*cloud_in,clusters[i],centroids[i]);
                //std::cout << "\t"<< centroids[i] << '\n';
        }
}

void handleDetector::makeVizMessageAndPublish(std::vector<Eigen::Matrix<float,4,1> > &centroids)
{
        const float radius = 0.075;
        std::vector<geometry_msgs::Point> cnts; //Viz messages use a geometry messages as backend, centroids are in eigen.
        //Must convert
        cnts.resize(centroids.size());
        for (size_t i = 0; i < centroids.size(); i++) {
                cnts[i].x=centroids[i](0);
                cnts[i].y=centroids[i](1);
                cnts[i].z=centroids[i](2);
        }

        visualization_msgs::Marker centroidsMarker;
        //centroidsMarker.points.resize(codebook.size());
        centroidsMarker.ns = "centroids";
        centroidsMarker.action = visualization_msgs::Marker::ADD;
        centroidsMarker.header.frame_id = "base_link";
        centroidsMarker.header.stamp = ros::Time();
        centroidsMarker.type = visualization_msgs::Marker::SPHERE_LIST;
        centroidsMarker.pose.orientation.w = 1.0;
        centroidsMarker.scale.x = radius;
        centroidsMarker.scale.y = radius;
        centroidsMarker.scale.z = radius;


        centroidsMarker.id = 1;
        centroidsMarker.color.r=0.0;
        centroidsMarker.color.b=1.0;
        centroidsMarker.color.g=0.0;
        centroidsMarker.color.a=1.0;

        centroidsMarker.points = cnts;
        std::cout << "Publishing codebook of:" << centroids.size()<<'\n';
        markerPub.publish(centroidsMarker);
        return;
}
