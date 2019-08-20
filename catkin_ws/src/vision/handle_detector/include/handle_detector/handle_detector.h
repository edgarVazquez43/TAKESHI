#include <ros/ros.h>

#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <pcl/filters/voxel_grid.h>

#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/project_inliers.h>

#include <pcl/surface/convex_hull.h>
//convex hull uses qhull as a backbone
//there is a bug so i need to inclide this
///so it kinda works
//It is probably solved on PCL1.8
//But that is not mainline ros until melodic
//Kill me...
#include <pcl/surface/impl/convex_hull.hpp>
#include <pcl/segmentation/extract_polygonal_prism_data.h>

#include <Eigen/Dense>


#include <visualization_msgs/MarkerArray.h>
#include "geometry_msgs/Point.h"

#include "point_cloud_manager/GetRgbd.h"
#include "vision_msgs/DetectHandles.h"

typedef pcl::PointCloud<pcl::PointXYZRGB> pointCloudXYZRGB;
typedef struct planeCloud_ {
        //holds plane model and points of plane
        pointCloudXYZRGB inliers;
        pcl::ModelCoefficients model;
}planeCloud;

class handleDetector {
private:
ros::NodeHandle nh_;
ros::Subscriber pclSubcriber;
ros::Publisher pclPublisher, markerPub;
ros::ServiceClient rgbdClient;
ros::ServiceServer handleServer;
float voxelSize, cropSize, segRatio,prismHeight, clusterTolerance;
int minPointsCluster, maxPointsCluster;
void pclCallback(const sensor_msgs::PointCloud2ConstPtr &msg);
void cropCloud(pointCloudXYZRGB::Ptr cloud_in, pointCloudXYZRGB::Ptr cloud_out, float zCrop);

void voxelFiltering(pointCloudXYZRGB::Ptr cloud_in, pointCloudXYZRGB::Ptr cloud_out, float leafSize);
bool extractPlane(
        pointCloudXYZRGB::Ptr cloud_in,
        pointCloudXYZRGB &cloud_out,
        planeCloud &plane);
planeCloud getClosestPlane(
        std::vector<planeCloud> &planes);
void  projectCloud(
        planeCloud pC,
        pointCloudXYZRGB::Ptr cloud_out);
void polygonalSegmentation(
        pointCloudXYZRGB::Ptr cloud_in,
        pointCloudXYZRGB::Ptr cloud_plane,
        pointCloudXYZRGB::Ptr cloud_out);
void clusterExtraction(
        pointCloudXYZRGB::Ptr cloud_in,
        std::vector<pcl::PointIndices> &clusters  );
void makeVizMessageAndPublish(
        std::vector<Eigen::Matrix<float,4,1> > &centroids);
void getCentroids(
        pointCloudXYZRGB::Ptr cloud_in,
        std::vector<pcl::PointIndices> &clusters,
        std::vector<Eigen::Matrix<float,4,1> > &centroids
        );
bool getHandles(
        vision_msgs::DetectHandles::Request  &req,
        vision_msgs::DetectHandles::Response &res);
bool serverProcess(std::vector<geometry_msgs::Point> &centroids);
public:
handleDetector(ros::NodeHandle &nh);
void setCallback();
void setServiceServer();
};
