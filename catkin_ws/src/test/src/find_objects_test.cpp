#include <iostream>
#include "ros/ros.h"
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Float32MultiArray.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp> 
#include "manip_msgs/InverseKinematicsFloatArray.h"


int main(int argc, char** argv)
{
  std::cout << std::endl;
  std::cout << "----> INITIALIZING INVERSE KINEMATIC TEST BY EDGAR-II..." << std::endl;
  ros::init(argc, argv, "IK_test_MoveIt");
  ros::NodeHandle    n;
  ros::Publisher     marker_pub;
  ros::Publisher     armPub;
  ros::Publisher     headPub;
  ros::Publisher     torsoPub;

  std_msgs::Float32MultiArray msg_arm;
  std_msgs::Float32MultiArray msg_head;
  std_msgs::Float32MultiArray msg_torso;

  // ROS Topic Publisher 
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  armPub     = n.advertise<std_msgs::Float32MultiArray>("/hardware/arm/goal_pose", 10);
  headPub    = n.advertise<std_msgs::Float32MultiArray>("/hardware/head/goal_pose", 10);
  torsoPub   = n.advertise<std_msgs::Float32MultiArray>("/hardware/torso/goal_pose", 10);

  msg_arm.data.resize(4);
  msg_head.data.resize(2);
  msg_torso.data.resize(1);

  ros::Rate loop(10);


  msg_arm.data[0] = -0.4;
  msg_arm.data[1] = -1.5707;
  msg_arm.data[2] = -1.5707;
  msg_arm.data[3] = 0.0;

  msg_head.data[0] = 1.5707;
  msg_head.data[1] = -0.9;

  msg_torso.data[0] = 0.5;

  while(ros::ok())
  {
    ros::spinOnce();
    armPub.publish(msg_arm);
    ros::spinOnce();
    loop.sleep();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(10000));
    
    headPub.publish(msg_head);
    ros::spinOnce();
    loop.sleep();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(10000));

    torsoPub.publish(msg_torso);
    ros::spinOnce();
    loop.sleep();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(10000));
    

    ros::spinOnce();
    loop.sleep();
  }
  return 0;
}
