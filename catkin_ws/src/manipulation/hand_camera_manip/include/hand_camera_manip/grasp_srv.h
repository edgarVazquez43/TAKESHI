#include <iostream>
#include <ros/ros.h>
#include <ros/package.h>
#include <ros/duration.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include "vision_msgs/HandCameraGrasp.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <ros/package.h>
#include <string>
class grasp_srv
{
ros::NodeHandle nh;
ros::Publisher loader_pub;
ros::Publisher enable_surf;
ros::Publisher enable_sat;
ros::Publisher enable_hand;
ros::Subscriber fnsh_sub;
ros::ServiceServer hand_grasp_server;

bool success;
public:
grasp_srv();
bool service_callback(vision_msgs::HandCameraGrasp::Request& request,
                      vision_msgs::HandCameraGrasp::Response& response);
void finish_cb(const std_msgs::Bool &f);
void grasp_by_hand(std::string fileToLoad );
void grasp_kalas();

};
