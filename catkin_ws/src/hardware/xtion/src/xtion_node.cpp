#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/PointCloud2.h>
  
#include "pcl_ros/transforms.h"
#include "tf/transform_listener.h"
#include "justina_tools/JustinaTools.h"
#include "point_cloud_manager/GetRgbd.h"

cv::Mat imgBGR;
cv::Mat imgDepth;

tf::TransformListener* tf_listener;  
sensor_msgs::PointCloud2 pc2_wrtRobot;
sensor_msgs::PointCloud2 pc2_wrtKinect;


void cloud_callback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  pc2_wrtKinect = *cloud_msg;
  pcl_ros::transformPointCloud("base_link", pc2_wrtKinect, pc2_wrtRobot, *tf_listener);
  
  // JustinaTools::PointCloud2Msg_ToCvMat(pc2_wrtRobot, imgBGR, imgDepth); 
  // cv::imshow("Depth", imgDepth);
  // cv::imshow("RGB", imgBGR);
}


bool robotRgbd_callback(point_cloud_manager::GetRgbd::Request &req, point_cloud_manager::GetRgbd::Response &resp)                                                                                          
{
  resp.point_cloud = pc2_wrtRobot;
  return true;                                                                                  
}

bool kinectRgbd_callback(point_cloud_manager::GetRgbd::Request &req, point_cloud_manager::GetRgbd::Response &resp)                                                                                          
{
  resp.point_cloud = pc2_wrtKinect;
  return true;                                                                                  
}


int main(int argc, char** argv)
{
  std::cout << std::endl << "------------------------>" << std::endl;
  std::cout << "XTION_NODE  BY   [EDD-II]" << std::endl;
  ros::init(argc, argv, "xtion_node");
  ros::NodeHandle nh;
  ros::Rate loop(30);

  ros::Subscriber subHSRpc2;
  ros::Publisher pubKinectFrame;
  ros::Publisher pubRobotFrame;
  
  ros::ServiceServer srvRgbdRobot;
  ros::ServiceServer srvRgbdKinect;


  subHSRpc2 = nh.subscribe("/hsrb/head_rgbd_sensor/depth_registered/rectified_points", 1, cloud_callback);
  pubKinectFrame = nh.advertise<sensor_msgs::PointCloud2>("/hardware/point_cloud_man/rgbd_wrt_kinect",1);
  pubRobotFrame  = nh.advertise<sensor_msgs::PointCloud2>("/hardware/point_cloud_man/rgbd_wrt_robot", 1);

  srvRgbdRobot = nh.advertiseService("/hardware/point_cloud_man/get_rgbd_wrt_robot", robotRgbd_callback);
  srvRgbdKinect = nh.advertiseService("/hardware/point_cloud_man/get_rgbd_wrt_kinect", kinectRgbd_callback);

  tf_listener = new tf::TransformListener();
  // tf_listener->waitForTransform("base_link", "kinect_link", ros::Time(0), ros::Duration(10.0));
  tf_listener->waitForTransform("base_link", "head_rgbd_sensor_link", ros::Time(3), ros::Duration(10.0));
  
  ros::spinOnce();
  loop.sleep();

  
  while( ros::ok() )
  {
    if(pubKinectFrame.getNumSubscribers() > 0)
    {
      pubKinectFrame.publish(pc2_wrtKinect);
    }

    if(pubRobotFrame.getNumSubscribers() > 0)
      pubRobotFrame.publish(pc2_wrtRobot);

    // std::cout << "Respect to robot" << std::endl;
    // JustinaTools::PointCloud2Msg_ToCvMat(pc2_wrtRobot, imgBGR, imgDepth);

    // std::cout << "Respect to kinect" << std::endl;
    // JustinaTools::PointCloud2Msg_ToCvMat(pc2_wrtKinect, imgBGR, imgDepth);
    
    
    ros::spinOnce();
    loop.sleep();
  }
  
  return 0;
}
