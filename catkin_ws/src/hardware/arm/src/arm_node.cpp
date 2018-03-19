/// @brief Copyright (C) 2016 Toyota Motor Corporation
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <controller_manager_msgs/ControllerState.h>
#include <controller_manager_msgs/ListControllers.h>
#include <tmc_control_msgs/GripperApplyEffortGoal.h>
#include <tmc_control_msgs/GripperApplyEffortAction.h>
#include <control_msgs/JointTrajectoryControllerState.h>



float torso_goal_pose;

std::vector<float>  arm_goal_pose;
std::vector<float>  arm_complete_cp;
std::vector<float>  gripper_goal_pose;
bool msg_arm_recived     = true;
bool msg_gripper_recived = true;


void armGoalPoseCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
  if(msg->data.size() != 4)
  {
    std::cout << "[ARM-NODE]: Error data size." << std::endl;
    std::cout << "[ARM-NODE]: Arm data must be four values." << std::endl;
  }
  else
    msg_arm_recived = true;
 
  arm_goal_pose.resize(4);
  
  for(int i = 0; i < 4; i++)
    arm_goal_pose[i] = msg->data[i];
  
}

void gripperPoseCallback(const std_msgs::Float32::ConstPtr& msg)
{
  // Expected value between [0.0 - 1.0] where 0.0 is close gripper and 1.0 is totally open gripper
  gripper_goal_pose.resize(1);
  gripper_goal_pose[0] = -0.105 + (msg->data)*( 1.23 + 0.105);  // Joint limits from official page
  
  msg_gripper_recived = true;
}


void torsoGoalPoseCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
  torso_goal_pose = msg->data[0];
  msg_arm_recived = true;
}

void armCurrentPoseCallback(const control_msgs::JointTrajectoryControllerState::ConstPtr& msg)
{
  // Read five values of torso and arm
  arm_complete_cp.resize(5);
  arm_complete_cp[0] = msg->actual.positions[0];   // torso joint
  arm_complete_cp[1] = msg->actual.positions[1];  
  arm_complete_cp[2] = msg->actual.positions[2];   
  arm_complete_cp[3] = msg->actual.positions[3];  
  arm_complete_cp[4] = msg->actual.positions[4];    
}



int main(int argc, char **argv)
{
  std::cout << std::endl << "------------------------->" << std::endl;
  std::cout << "INITIALIZING ARM_BRIDGE_NODE BY [EDD-II] " << std::endl;
  ros::init(argc, argv, "arm_bridge");

  std_msgs::Float32MultiArray msg_torso_current_pose;
  std_msgs::Float32MultiArray msg_arm_current_pose;

  // initalize ROS publisher
  ros::NodeHandle  n;
  ros::Publisher   pub_hsr_arm_gp;
  ros::Publisher   pub_hsr_gripp_gp;
  ros::Publisher   pub_torso_curren_pose;
  ros::Publisher   pub_arm_curren_pose;

  ros::Subscriber  sub_pumas_arm_gp;
  ros::Subscriber  sub_pumas_gripp_gp;
  ros::Subscriber  sub_torso_goal_pose;
  ros::Subscriber  sub_hsr_arm_cp;

  // actionlib::SimpleActionClient<tmc_control_msgs::GripperApplyEffortAction> gripperActionClient;

  ros::Rate        loop(30);

  // Publishers for hsr-hardware
  pub_hsr_arm_gp      = n.advertise<trajectory_msgs::JointTrajectory>("/hsrb/arm_trajectory_controller/command", 10);
  pub_hsr_gripp_gp    = n.advertise<trajectory_msgs::JointTrajectory>("/hsrb/gripper_controller/command", 10);
  pub_torso_curren_pose = n.advertise<std_msgs::Float32MultiArray>("/hardware/torso/current_pose", 10);
  pub_arm_curren_pose = n.advertise<std_msgs::Float32MultiArray>("/hardware/arm/current_pose", 10);

  
  sub_pumas_arm_gp    = n.subscribe("/hardware/arm/goal_pose", 10, armGoalPoseCallback);
  sub_pumas_gripp_gp  = n.subscribe("/hardware/arm/goal_gripper", 10, gripperPoseCallback);
  sub_torso_goal_pose = n.subscribe("/hardware/torso/goal_pose", 10, torsoGoalPoseCallback);
  sub_hsr_arm_cp      = n.subscribe("/hsrb/arm_trajectory_controller/state", 10, armCurrentPoseCallback);

  //  gripperActionClient 
 


  // wait to establish connection between the controller
  while (pub_hsr_arm_gp.getNumSubscribers() == 0) {
    ros::Duration(0.1).sleep();
  }
  

  // make sure the controller is running
  ros::ServiceClient client = n.serviceClient<controller_manager_msgs::ListControllers>(
      "/hsrb/controller_manager/list_controllers");
  controller_manager_msgs::ListControllers list_controllers;
  bool running = false;
  while (running == false) {
    ros::Duration(0.1).sleep();
    if (client.call(list_controllers)) {
      for (unsigned int i = 0; i < list_controllers.response.controller.size(); i++) {
        controller_manager_msgs::ControllerState c = list_controllers.response.controller[i];
        if (c.name == "arm_trajectory_controller" && c.state == "running") {
          running = true;
        }
      }
    }
  }

  // fill ROS message
  trajectory_msgs::JointTrajectory traj_arm;
  trajectory_msgs::JointTrajectory traj_gripp;

  tmc_control_msgs::GripperApplyEffortGoal goal;

  

  traj_arm.joint_names.push_back("arm_lift_joint");
  traj_arm.joint_names.push_back("arm_flex_joint");
  traj_arm.joint_names.push_back("arm_roll_joint");
  traj_arm.joint_names.push_back("wrist_flex_joint");
  traj_arm.joint_names.push_back("wrist_roll_joint");
  traj_gripp.joint_names.push_back("hand_motor_joint");    // Gripper trayectorie msgs
  
  traj_arm.points.resize(1);
  traj_gripp.points.resize(1);

  traj_arm.points[0].positions.resize(5);
  traj_arm.points[0].velocities.resize(5);
  traj_gripp.points[0].positions.resize(1);
  traj_gripp.points[0].velocities.resize(1);
  traj_gripp.points[0].effort.resize(1);

  msg_torso_current_pose.data.resize(1);
  msg_arm_current_pose.data.resize(4);


  // Initial values
  traj_arm.points[0].velocities[0] = 0.0;
  traj_arm.points[0].velocities[1] = 0.0;
  traj_arm.points[0].velocities[2] = 0.1;
  traj_arm.points[0].velocities[3] = 0.1;
  traj_arm.points[0].velocities[4] = 0.1;
  traj_gripp.points[0].velocities[0] = -0.5;

  traj_arm.points[0].positions[0] = 0.0;
  traj_arm.points[0].positions[1] = 0.0;
  traj_arm.points[0].positions[2] = 0.0;
  traj_arm.points[0].positions[3] = 0.0;
  traj_arm.points[0].positions[4] = 0.0;
  traj_gripp.points[0].positions[0] = -0.4;

  traj_gripp.points[0].effort[0] = -0.2;
  
  traj_arm.points[0].time_from_start = ros::Duration(3.0);
  traj_gripp.points[0].time_from_start = ros::Duration(3.0);

  arm_goal_pose.resize(5);
  arm_complete_cp.resize(5);
  gripper_goal_pose.resize(1);


  
  goal.effort = -0.2;

  

  
  while(ros::ok())
  {
    // Set goal_pose
    for (size_t i = 0; i < 4; ++i) 
      traj_arm.points[0].positions[i+1] = arm_goal_pose[i];
    traj_gripp.points[0].positions[0] = gripper_goal_pose[0];
    traj_arm.points[0].positions[0] = torso_goal_pose;
    
    // Set current pose for publish
    msg_torso_current_pose.data[0] = arm_complete_cp[0];
    msg_arm_current_pose.data[0] = arm_complete_cp[1];
    msg_arm_current_pose.data[1] = arm_complete_cp[2];
    msg_arm_current_pose.data[2] = arm_complete_cp[3];
    msg_arm_current_pose.data[3] = arm_complete_cp[4];

    
    // publish ROS message
    if(msg_arm_recived)
    {
      pub_hsr_arm_gp.publish(traj_arm);
      msg_arm_recived = false;
    }

    if(msg_gripper_recived)
    {
      pub_hsr_gripp_gp.publish(traj_gripp);
      msg_gripper_recived = false;
    }

    

    if(pub_torso_curren_pose.getNumSubscribers() > 0)
      pub_torso_curren_pose.publish(msg_torso_current_pose);

    if(pub_arm_curren_pose.getNumSubscribers() > 0)
      pub_arm_curren_pose.publish(msg_arm_current_pose);

    

    loop.sleep();
    ros::spinOnce();
  }
  return 0;
}
