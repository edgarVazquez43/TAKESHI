  #include "takeshi_tools/TakeshiTools.h"

bool TakeshiTools::is_node_set = false;
tf::TransformListener* TakeshiTools::tf_listener;

using namespace std;



bool TakeshiTools::setNodeHandle(ros::NodeHandle* nh)
{

        if(TakeshiTools::is_node_set)
                return true;
        if(nh == 0)
                return false;
        cout << "\033[1;37m     TakeshiTools.->Setting ros node...\033[0m" << endl;
        tf_listener = new tf::TransformListener();
        tf_listener->waitForTransform("map", "base_range_sensor_link", ros::Time(0), ros::Duration(10.0));
        TakeshiTools::is_node_set = true;
        return true;
}

bool TakeshiTools::transformPoint(std::string src_frame, float inX, float inY, float inZ, std::string dest_frame, float& outX, float& outY, float& outZ)
{
        cout << "\033[1;37m     TakeshiTools.-> " << "Transform point : " << inX <<" " << inY << " " << inZ << endl;
        cout << "\033[1;37m     TakeshiTools.-> " << "In : " << outX <<" " << outY << " " << outZ << endl;
        tf::StampedTransform transformTf;
        tf_listener->lookupTransform(dest_frame,src_frame, ros::Time(0), transformTf);
        tf::Vector3 v(inX, inY, inZ);
        v = transformTf * v;
        outX = v.x();
        outY = v.y();
        outZ = v.z();
        return true;
}



void TakeshiTools::PointCloud2Msg_ToCvMat(sensor_msgs::PointCloud2& pc_msg, cv::Mat& bgr_dest, cv::Mat& pc_dest)
{
        // #################################
        //      Transform using PCL
        // #################################

        pcl::PointCloud<pcl::PointXYZRGBA> pc_pcl;
        pcl::fromROSMsg(pc_msg, pc_pcl); //Transform from PointCloud2 msg to pointCloud (from pcl) type

        if(!pc_pcl.isOrganized()){
                cout << "\033[1;37m     TakeshiTools.->Point cloud is not organized!! O M G!!!!\033[0m" << endl;
                return;
        }
        bgr_dest = cv::Mat::zeros(pc_pcl.height, pc_pcl.width, CV_8UC3);
        pc_dest = cv::Mat::zeros(pc_pcl.height, pc_pcl.width, CV_32FC3);

        for (int h=0; h<bgr_dest.rows; h++)
                for (int w=0; w<bgr_dest.cols; w++){
                        pcl::PointXYZRGBA p = pc_pcl.at(w, h);
                        bgr_dest.data[h*bgr_dest.step + w*3] = (unsigned char)p.b;
                        bgr_dest.data[h*bgr_dest.step + w*3 + 1] = (unsigned char)p.g;
                        bgr_dest.data[h*bgr_dest.step + w*3 + 2] = (unsigned char)p.r;
                        pc_dest.at<cv::Vec3f>(h,w)[0] = isnan(p.x) ? 0.0 : p.x;
                        pc_dest.at<cv::Vec3f>(h,w)[1] = isnan(p.y) ? 0.0 : p.y;
                        pc_dest.at<cv::Vec3f>(h,w)[2] = isnan(p.z) ? 0.0 : p.z;
                }
        return;
}


void TakeshiTools::PointCloud2Msg_ToCvMat(const sensor_msgs::PointCloud2::ConstPtr& pc_msg, cv::Mat& bgr_dest, cv::Mat& pc_dest)
{
    
  // ############################
  //       Transform using PCL
  // ############################

    pcl::PointCloud<pcl::PointXYZRGB> pc_pcl;
	pcl::fromROSMsg(*pc_msg, pc_pcl);  //Transform from PointCloud2 msg to pointCloud (from pcl) type

	if(!pc_pcl.isOrganized()){
		cout << "\033[1;37m     TakeshiTools.->Point cloud is not organized!! O M G!!!!\033[0m" << endl;
		return;
	}
	bgr_dest = cv::Mat::zeros(pc_pcl.height, pc_pcl.width, CV_8UC3);
	pc_dest = cv::Mat::zeros(pc_pcl.height, pc_pcl.width, CV_32FC3);
	
	for (int h=0; h<bgr_dest.rows; h++)
        for (int w=0; w<bgr_dest.cols; w++){
            pcl::PointXYZRGB p = pc_pcl.at(w,h);
            bgr_dest.data[h*bgr_dest.step + w*3] = (unsigned char)p.b;
            bgr_dest.data[h*bgr_dest.step + w*3 + 1] = (unsigned char)p.g;
            bgr_dest.data[h*bgr_dest.step + w*3 + 2] = (unsigned char)p.r;
            pc_dest.at<cv::Vec3f>(h,w)[0] = isnan(p.x) ? 0.0 : p.x;
            pc_dest.at<cv::Vec3f>(h,w)[1] = isnan(p.y) ? 0.0 : p.y;
            pc_dest.at<cv::Vec3f>(h,w)[2] = isnan(p.z) ? 0.0 : p.z;
      }
}
