#include <iostream>
#include "ros/ros.h"
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Float32MultiArray.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include "manip_msgs/InverseKinematicsFloatArray.h"

visualization_msgs::Marker endEffector_marker;

bool markerSetup()
{
  endEffector_marker.header.frame_id = "base_link";    
  endEffector_marker.header.stamp = ros::Time::now();
  endEffector_marker.ns = "endEffector_r";
    
  endEffector_marker.pose.orientation.w = 1.0;
    
  endEffector_marker.id = 0;
    
  endEffector_marker.type = visualization_msgs::Marker::SPHERE;
    
  // POINTS markers use x and y scale for width/height respectively
  endEffector_marker.scale.x = 0.040;
  endEffector_marker.scale.y = 0.040;
  endEffector_marker.scale.z = 0.040;

  endEffector_marker.color.g = 1.0f;
  endEffector_marker.color.a = 1.0;

  return true;
}


int main(int argc, char** argv)
{
  std::cout << std::endl;
  std::cout << "----> INITIALIZING INVERSE KINEMATIC TEST BY EDGAR-II..." << std::endl;
  ros::init(argc, argv, "IK_test_MoveIt");
  ros::NodeHandle    n;
  ros::Publisher     marker_pub;
  ros::Publisher     arm_pub;
  ros::Publisher     torso_pub;

  ros::ServiceClient cltIKinematicsArm;

  std::vector<float>          cartesian;
  std_msgs::Float32MultiArray ra_gp_msgs;

  manip_msgs::InverseKinematicsFloatArray srv_ki;

  tf::TransformListener  listener;
  tf::StampedTransform   transform;

  geometry_msgs::Pose    endEffector_pose;

  // ROS  Service Client
  cltIKinematicsArm = n.serviceClient<manip_msgs::InverseKinematicsFloatArray>("/manipulation/ik_moveit/gripper_inverse_kinematics");

  // ROS Topic Publisher 
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  arm_pub    = n.advertise<std_msgs::Float32MultiArray>("/hardware/arm/goal_pose", 10);
  torso_pub  = n.advertise<std_msgs::Float32>("/hardware/torso/goal_pose", 10);

  // Data request to Inverse Kinematic
  cartesian.push_back( 0.45);   // X-axis respect robot
  cartesian.push_back( 0.10);   // Y-axis respect robot     
  cartesian.push_back( 0.90);     // Z-axis respect robot
  
  cartesian.push_back(0.0);       // yaw
  cartesian.push_back(-1.5707);    // pitch
  cartesian.push_back(3.141592);       // roll
  srv_ki.request.cartesian_pose.data = cartesian;

  // Response data is already respect to base_link frame
  endEffector_pose.position.x = cartesian[0];
  endEffector_pose.position.y = cartesian[1];
  endEffector_pose.position.z = cartesian[2];

  markerSetup();

 
  ros::Rate loop(30);

  loop.sleep();
  ros::spinOnce();
  ros::Duration(0.5).sleep();

  //while(ros::ok()) {
  for(int i = 0; i < 5; i++ ){
      endEffector_marker.pose.position = endEffector_pose.position;
      marker_pub.publish(endEffector_marker);
      ros::spinOnce();
  }
      
      if(!cltIKinematicsArm.call(srv_ki))
        {
	  std::cout << std::endl <<
	    "Justina::Manip can't calling inverse kinematics service" << std::endl << std::endl;
        }
      else
        {
	  std::cout << "InverseKinematics.-> Calculated cartesian...." << std::endl;
	  std::cout << "[Joints values]:  " << std::endl;
	  for (int i=0; i < srv_ki.response.articular_pose.data.size() ; i++)
	      std::cout << "   " << srv_ki.response.articular_pose.data[i] << std::endl;
	  std::cout << "OmniBase correction: " << std::endl << srv_ki.response.base_correction << std::endl;
	  std::cout << "Torso correction: " << srv_ki.response.torso_pose << std::endl;
	}

      std_msgs::Float32MultiArray arm_msg;
      std_msgs::Float32 trs_msg;
      arm_msg = srv_ki.response.articular_pose;
      trs_msg.data = srv_ki.response.torso_pose.data;

      arm_pub.publish(arm_msg);
      torso_pub.publish(trs_msg);

      loop.sleep();
      ros::spinOnce();
      ros::Duration(0.5).sleep();
      
      std::cout << "---------------------------" << std::endl;
      // }
  return 0;
}
