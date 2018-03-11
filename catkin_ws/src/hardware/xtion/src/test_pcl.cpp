#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/PointCloud2.h>
#include "justina_tools/JustinaTools.h"

cv::Mat imgBGR;
cv::Mat imgDepth;
sensor_msgs::PointCloud2 pc2_output;


void cloud_callback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  // ROS_INFO("Msg cloud recived");

  pc2_output = *cloud_msg;
  std::cout << "Point_step[msg_recived]:  " << (int)cloud_msg->point_step << std::endl;
  std::cout << "Point_step[msg_recived]:  " << (int)cloud_msg->point_step << std::endl;
  std::cout << "Point_step[msg_recived]:  " << (int)cloud_msg->point_step << std::endl;

  JustinaTools::PointCloud2Msg_ToCvMat(cloud_msg, imgBGR, imgDepth);
  
  cv::imshow("Depth", imgDepth);
  cv::imshow("RGB", imgBGR);
}



int main(int argc, char** argv)
{
  std::cout << "TEST_PCL     BY   [EDD-2]" << std::endl;
  ros::init(argc, argv, "Tets_pcl_hsr");
  ros::NodeHandle nh;
  ros::Rate loop_rate(10);
  ros::Subscriber sub;

  sub = nh.subscribe("/hsrb/head_rgbd_sensor/depth_registered/rectified_points", 1, cloud_callback);

  while(ros::ok() && cv::waitKey(15) != 27 )
  {
    ros::spinOnce();
    loop_rate.sleep();
  }

  std::cout << "Point_step[msg_outpu]:  " << (int)pc2_output.point_step << std::endl;
  std::cout << "Point_step[msg_outpu]:  " << pc2_output.header.frame_id << std::endl;

  cv::destroyAllWindows();
  return 0;
}
