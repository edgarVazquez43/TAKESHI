#include "ros/ros.h"
#include <fstream>
#include <ctime>

#include <geometry_msgs/Pose.h>
#include "moveit/robot_model_loader/robot_model_loader.h"
#include "moveit/robot_model/robot_model.h"
#include "moveit/robot_state/robot_state.h"
#include "manip_msgs/InverseKinematicsFloatArray.h"
#include "manip_msgs/DirectKinematicsFloatArray.h"


robot_state::RobotStatePtr    kinematic_state;
robot_state::JointModelGroup* joint_group_Arm;
std::vector<std::string>      joint_names_Arm;



bool callbackGripperDK(manip_msgs::DirectKinematicsFloatArray::Request  &req,
		       manip_msgs::DirectKinematicsFloatArray::Response &resp)
{
  std::cout << std::endl <<" -------> " << std::endl;
  std::cout << "Calling service to calculate HSRB arm Direct-Kinematic"
	    << std::endl << " --- (MoveIt Node)  --- "
	    << std::endl;

  resp.cartesian_pose.data.resize(6);    
  std::vector<double> pose;
  pose.resize(8);
  
  // This information is for joints of mobile base 
  pose[0] = 0.0;    // x_delta respect to robot
  pose[1] = 0.0;    // y_delta respect to robot
  pose[2] = 0.0;    // theta  respect to robot
  
  for(int i = 0; i < req.articular_pose.data.size(); i++)
    pose[i+3]=req.articular_pose.data[i];

  
  kinematic_state->setJointGroupPositions(joint_group_Arm, pose);
  const Eigen::Affine3d &end_effector_state = kinematic_state->getGlobalLinkTransform("hand_palm_link");
  Eigen::Vector3d euler = end_effector_state.rotation().eulerAngles(0,1,2);

  /* Print end-effector pose. Remember that this is in the model frame */
  ROS_INFO_STREAM("->  ARM GRIPPER CENTER POSITION  -----------");
  
  std::cout << "Position:  " << end_effector_state.translation()[0]
	    << "  " << end_effector_state.translation()[1]
	    << "  " << end_effector_state.translation()[2]
	    << std::endl;
  std::cout << "Orientation: " << euler[0] << "  " << euler[1]<< "  " << euler[2] << std::endl;

  resp.cartesian_pose.data[0] = end_effector_state.translation()[0];
  resp.cartesian_pose.data[1] = end_effector_state.translation()[1];
  resp.cartesian_pose.data[2] = end_effector_state.translation()[2];

  resp.cartesian_pose.data[3] = euler[0];
  resp.cartesian_pose.data[4] = euler[1];
  resp.cartesian_pose.data[5] = euler[2];
  std::cout << "---------------------------" << std::endl;
  return true;
}



bool callbackGripperIK(manip_msgs::InverseKinematicsFloatArray::Request  &req,
		       manip_msgs::InverseKinematicsFloatArray::Response &resp)
{
  std::cout << std::endl <<" -------> " << std::endl;
  std::cout << std::endl << "Calling service to calculate HSRB arm Inverse-Kinematic"
	    << std::endl << " --- (MoveIt Node)  --- "
	    << std::endl;

  std::cout << "Desire pose: " << std::endl
	    << "  x:  " << req.cartesian_pose.data[0] << std::endl
	    << "  y:  " << req.cartesian_pose.data[1] << std::endl
	    << "  z:  " << req.cartesian_pose.data[2] << std::endl
	    << "  roll :  " << req.cartesian_pose.data[3] << std::endl
	    << "  pitch:  " << req.cartesian_pose.data[4] << std::endl
    	    << "  yaw  :  " << req.cartesian_pose.data[5] << std::endl;
    

  bool found_ik;
  std::vector<double> result;
  
  Eigen::Affine3d desired_pose = Eigen::Affine3d::Identity();

  desired_pose.translate(Eigen::Vector3d((double)req.cartesian_pose.data[0],
					 (double)req.cartesian_pose.data[1],
					 (double)req.cartesian_pose.data[2]));
  
  desired_pose.rotate(Eigen::AngleAxisd((double)req.cartesian_pose.data[3], Eigen::Vector3d(0,0,1)));   //yaw
  desired_pose.rotate(Eigen::AngleAxisd((double)req.cartesian_pose.data[4], Eigen::Vector3d(0,1,0)));   //pitch
  desired_pose.rotate(Eigen::AngleAxisd((double)req.cartesian_pose.data[5], Eigen::Vector3d(1,0,0)));   //roll


  std::cout << "Trying to calculate inverse kinematic.... " << std::endl;
  found_ik = kinematic_state->setFromIK(joint_group_Arm, desired_pose, "hand_palm_link", 10, 0.5);

  
  if (found_ik)
  {
    resp.articular_pose.data.resize(5);
    kinematic_state->copyJointGroupPositions(joint_group_Arm, result);

    for (std::size_t i = 0; i < result.size(); ++i)
      ROS_INFO("Joint: %s   %f", joint_names_Arm[i].c_str(), result[i]);
    
    // Fill message response
    resp.omni_base_correction.x = result[0];
    resp.omni_base_correction.y = result[1];
    resp.omni_base_correction.theta = result[2];
    
    for (std::size_t i = 3; i < result.size(); ++i)
      resp.articular_pose.data[i-3] = result[i];
  }
  else
  {
    ROS_INFO("Did not find IK solution");
    return false;
  }

  std::cout << "---------------------------" << std::endl;
  return true;
}





int main(int argc, char** argv)
{
  std::cout << std::endl;
  std::cout << "--------------------->" << std::endl;
  std::cout << "INITIALIZING INVERSE KINEMATIC NODE BY [EDD-II] (MOVEIT)" << std::endl;
  ros::init(argc, argv, "ik_moveit_node");
  ros::NodeHandle n;

  ros::ServiceServer srvSrvIKFloatArray;
  ros::ServiceServer srvSrvDKFloatArray;

  robot_model_loader::RobotModelLoader robot_model_loader("robot_description");    // Instancia de RobotModelLoader
  robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();      // Get kinematic model

  ROS_INFO("Model frame: %s", kinematic_model->getModelFrame().c_str());

  
  // Create ROS services
  srvSrvIKFloatArray = n.advertiseService("ik_moveit/gripper_inverse_kinematics", callbackGripperIK);
  srvSrvDKFloatArray = n.advertiseService("ik_moveit/gripper_direct_kinematics", callbackGripperDK);
  
  // Create a kinematic_state
  kinematic_state = robot_state::RobotStatePtr( new robot_state::RobotState(kinematic_model) );

  joint_group_Arm  = kinematic_model->getJointModelGroup("whole_body");
  joint_names_Arm  = joint_group_Arm->getVariableNames();


  ros::Rate loop(30);
  
  while(ros::ok())
  {
    ros::spinOnce();
    loop.sleep();
  }  
}
