#include <iostream>
#include "ros/ros.h"
#include "manip_msgs/InverseKinematicsFloatArray.h"
#include "manip_msgs/InverseKinematicsPath.h"
#include "manip_msgs/InverseKinematicsPose.h"
#include "manip_msgs/DirectKinematics.h"
#include "InverseKinematics.h"



bool callbackInverseKinematicsFloatArray(manip_msgs::InverseKinematicsFloatArray::Request &req,
                                         manip_msgs::InverseKinematicsFloatArray::Response &resp)
{
    //In all cases, the resulting articular pose is a std::vector<float> with seven values corresponding to the 7DOF of the arm
    if(req.cartesian_pose.data.size() == 6)
    {
        float x = req.cartesian_pose.data[0];
        float y = req.cartesian_pose.data[1];
        float z = req.cartesian_pose.data[2];
        float roll = req.cartesian_pose.data[3];
        float pitch = req.cartesian_pose.data[4];
        float yaw = req.cartesian_pose.data[5];
        std::cout << "InverseKinematics.->Calculating inverse kinematics from float array with six values..." << std::endl;
        return InverseKinematics::GetInverseKinematics(x, y, z, roll, pitch, yaw, resp.articular_pose.data, resp.torso_pose.data, resp.base_correction);
    }
    
    if (req.cartesian_pose.data.size() == 3)
    {
        float x = req.cartesian_pose.data[0];
        float y = req.cartesian_pose.data[1];
        float z = req.cartesian_pose.data[2];
        std::cout << "InverseKinematics.->Calculating inverse kinematics from float array with three values..." << std::endl;
        return InverseKinematics::GetInverseKinematics(x, y, z, resp.articular_pose.data, resp.torso_pose.data, resp.base_correction);
    }

    std::cout << "Ik_Geometric.->Cannot calculate inv kinematics: Invalid number of args in request." << std::endl;
    return false;
}

bool callbackDirectKinematics(manip_msgs::DirectKinematics::Request &req, manip_msgs::DirectKinematics::Response &resp)
{
    return InverseKinematics::GetDirectKinematics(req.articular_pose.data, resp.cartesian_pose.data);
}




// ####################################
// ###             MAIN             ###
int main(int argc, char** argv)
{
  std::cout << "INITIALIZING INVERSE KINEMATICS GEOMETRIC BY [EDD-II]... " << std::endl;
  ros::init(argc, argv, "inverse_kinematics_geometric");
  ros::NodeHandle n;

  ros::ServiceServer srvSrvIKFloatArray          = n.advertiseService("/manipulation/ik_geometric/ik_float_array", callbackInverseKinematicsFloatArray);
  ros::ServiceServer srvSrvDirectKin             = n.advertiseService("/manipulation/ik_geometric/direct_kinematics", callbackDirectKinematics);
  ros::Rate loop(30);

  while(ros::ok())
    {
      ros::spinOnce();
      loop.sleep();
    }
  return 0;
}
