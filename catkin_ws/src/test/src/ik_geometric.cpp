#include <iostream>
#include "ros/ros.h"
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32MultiArray.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include "manip_msgs/InverseKinematicsFloatArray.h"
#include "justina_tools/JustinaManip.h"
#include "justina_tools/JustinaNavigation.h"

visualization_msgs::Marker endEffector_marker, wristCenter_marker;

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


  wristCenter_marker.header.frame_id = "base_link";
  wristCenter_marker.header.stamp = ros::Time::now();
  wristCenter_marker.ns = "wristCenter";
  wristCenter_marker.pose.orientation.w = 1.0;
  wristCenter_marker.id = 0;
  wristCenter_marker.type = visualization_msgs::Marker::SPHERE;
  // POINTS markers use x and y scale for width/height respectively
  wristCenter_marker.scale.x = 0.040;
  wristCenter_marker.scale.y = 0.040;
  wristCenter_marker.scale.z = 0.040;
  wristCenter_marker.color.b = 1.0f;
  wristCenter_marker.color.a = 1.0;

  return true;
}


int main(int argc, char** argv)
{
  std::cout << std::endl;
  std::cout << "----> INITIALIZING INVERSE KINEMATIC TEST BY EDGAR-II..." << std::endl;
  ros::init(argc, argv, "IK_test_geometric");

  ros::NodeHandle    n;

  JustinaManip::setNodeHandle(&n);
  JustinaNavigation::setNodeHandle(&n);

  ros::Publisher     marker_pub;
  ros::ServiceClient cltIKinematicsArm;

  std::vector<float> cartesian;
  std::vector<float> articular;

  std_msgs::Float32MultiArray             ra_gp_msgs;
  manip_msgs::InverseKinematicsFloatArray srv_ki;

  tf::TransformListener  listener;
  tf::StampedTransform   transform;
  tf::Quaternion         q;
  tf::Transform          Rwc_EE;   // Transform to Center Wrist to EndEffector
  tf::Vector3            wristPos(0.0, 0.0, 0.0);

  geometry_msgs::Pose   endEffector_pose;
  geometry_msgs::Pose   wristCenter_pose;
  geometry_msgs::Pose2D base_correction;
  float torso, torso_correction;
  float x_wc, y_wc, z_wc;
  float x_wra, y_wra, z_wra;

  // ROS  Service Client
  cltIKinematicsArm = n.serviceClient<manip_msgs::InverseKinematicsFloatArray>("/manipulation/ik_geometric/ik_float_array");
  // ROS Topic Publisher
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

   ros::Rate loop(30);
   ros::spinOnce();


  // // Data request to Inverse Kinematic
  // cartesian.push_back( 0.650);    // X-axis respect robot
  // cartesian.push_back( 0.08);    // Y-axis respect robot
  // cartesian.push_back( 0.45);    // Z-axis respect robot

  // cartesian.push_back(0.0);      // roll
  // cartesian.push_back(1.5707);      // pitch
  // cartesian.push_back(0.0);   // yaw

  // // roll, pitch, yaw
  // q.setRPY(cartesian[3], cartesian[4], cartesian[5]);    //Transfor in format roll, pitch, yaw.
  // Rwc_EE.setIdentity();
  // Rwc_EE.setRotation(q);

  // wristPos[2] = 0.21;
  // wristPos = Rwc_EE * wristPos;

  // wristPos[0] = cartesian[0] - wristPos[0];
  // wristPos[1] = cartesian[1] - wristPos[1];
  // wristPos[2] = cartesian[2] - wristPos[2];

  // x_wc = wristPos[0];
  // y_wc = wristPos[1];
  // z_wc = wristPos[2];

  // std::cout << "End efector pos: "  << cartesian[0] << "  "
  // 	    << cartesian[1] << "  " << cartesian[2] << std::endl;

  //   std::cout << "WristCenter pos: "  << wristPos[0] << "  "
  // 	    << wristPos[1] << "  " << wristPos[2] << std::endl;

  // wristCenter_pose.position.x = wristPos[0];
  // wristCenter_pose.position.y = wristPos[1];
  // wristCenter_pose.position.z = wristPos[2];

  // // Response data is already respect to base_link frame
  // endEffector_pose.position.x = cartesian[0];
  // endEffector_pose.position.y = cartesian[1];
  // endEffector_pose.position.z = cartesian[2];

  // markerSetup();

  // articular.resize(4);
  // articular[0] = 0.0;
  // articular[1] = 0.0;
  // articular[2] = 0.0;
  // articular[3] = 0.0;
  // // JustinaManip::armGoToArticular(articular, 6000);
  // // JustinaManip::torsoGoTo(0.0, 0.0, 0.0, 6000);

  // for(int i = 0; i < 5; i++ )
  // {
  //   std::cout << "Publish marker point... " << " :  " << i << std::endl;
  //    endEffector_marker.pose.position = endEffector_pose.position;
  //    wristCenter_marker.pose.position = wristCenter_pose.position;
  //    marker_pub.publish(endEffector_marker);
  //    marker_pub.publish(wristCenter_marker);
  //    loop.sleep();
  //    ros::Duration(0.2).sleep();
  // }

  // ///////////////////////////////////////
  // ////   Before kinematic decoupling  ///
  // // 0.70 is the maximun lenght of torso in Z axis

  // x_wra = x_wc - 0.120;
  // if(x_wra > 0.37)
  // {
  //   std::cout << "This point is out of work space:" << std::endl;
  //   return false;
  // }

  // z_wra = sqrt( (0.37*0.37) - (x_wra*x_wra) );

  // std::cout << "X-Z dimensions with respect arm:  " << std::endl
  // 	    << "X:  " << x_wra << "  Z:  " << z_wra << std::endl;
  // torso_correction = z_wc - z_wra - 0.31;
  // std::cout << "TorsoCorrection (before transformation): " << torso_correction << std::endl;

  // if(torso_correction < 0.0)
  // {
  //   torso_correction = z_wc + z_wra - 0.33;

  //   articular[0] = atan2(-z_wra, x_wra) - 1.5707;
  //   articular[1] = 0.0 + (cartesian[3]);
  //   articular[2] = atan2(z_wra, x_wra) + (1.5707-cartesian[4]);
  //   articular[3] = 0.0 + (cartesian[5]);
  //   torso = torso_correction;
  // }
  // else
  // {
  //   articular[0] = atan2(z_wra, x_wra) - 1.5707;
  //   articular[1] = 0.0 + (cartesian[3]);
  //   articular[2] = -atan2(z_wra, x_wra) + (1.5707-cartesian[4]);
  //   articular[3] = 0.0 + (cartesian[5]);
  //   torso = torso_correction;
  // }
  // std::cout << "TorsoCorrection:   " << torso_correction << std::endl;
  // JustinaManip::torsoGoTo(torso_correction, 0.0, 0.0, 2000);

  // ros::Duration(2.0).sleep();



  // std::cout << "Articular poses: " << std::endl;
  // for (int i=0; i < articular.size() ; i++)
  //   std::cout << "   " << articular[i] << std::endl;

  // std::cout << "OmniBase correction: " << base_correction << std::endl;

  // JustinaManip::armGoToArticular(articular, 2000);

  // // JustinaNavigation::moveDistAngle(base_correction.x, base_correction.theta, 6000);
  // // JustinaNavigation::moveDistAngle(base_correction.y, 0.0, 6000);



  std::cout << "---------------------------" << std::endl;
  std::cout << "USING NODE CODE: " << std::endl;

  cartesian.resize(6);
  cartesian[0] = 0.500;    // X-axis respect robot
  cartesian[1] = 0.100;    // Y-axis respect robot
  cartesian[2] = 0.05;     // Z-axis respect robot

  cartesian[3] = 0.00;      // roll
  cartesian[4] = 1.80;      // pitch
  cartesian[5] = 0.00;      // yaw


  // // Response data is already respect to base_link frame
  endEffector_pose.position.x = cartesian[0];
  endEffector_pose.position.y = cartesian[1];
  endEffector_pose.position.z = cartesian[2];



  markerSetup();

  for(int i = 0; i < 5; i++ )
  {
    std::cout << "Publish marker point... " << " :  " << i << std::endl;
    endEffector_marker.pose.position = endEffector_pose.position;
    wristCenter_marker.pose.position = wristCenter_pose.position;
    marker_pub.publish(endEffector_marker);
    marker_pub.publish(wristCenter_marker);
    loop.sleep();
    ros::Duration(0.2).sleep();
  }


  articular.resize(4);
  if( JustinaManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
  {
    std::cout << "Articular poses: " << std::endl;
    for (int i=0; i < articular.size() ; i++)
      std::cout << "   " << articular[i] << std::endl;
    std::cout << "TorsoCorrection:   " << torso << std::endl;
    std::cout << "BaseCorrection:   "  << base_correction.x << std::endl;
    JustinaManip::torsoGoTo(torso, 2000);
    JustinaManip::armGoToArticular(articular, 2000);
    JustinaNavigation::moveDistAngle(base_correction.x, 0.0, 4000);
  }


  loop.sleep();
  return 0;
}
