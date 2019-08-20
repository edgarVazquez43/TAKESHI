#include <ros/ros.h>
#include <ros/package.h>
#include <controller_manager_msgs/ControllerState.h>
#include <controller_manager_msgs/ListControllers.h>
#include <control_msgs/JointTrajectoryControllerState.h>
#include <sensor_msgs/JointState.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Twist.h>
//for grasping
#include <actionlib/client/simple_action_client.h>
#include <tmc_control_msgs/GripperApplyEffortAction.h>
#include <tmc_control_msgs/GripperApplyEffortGoal.h>

typedef actionlib::SimpleActionClient<tmc_control_msgs::GripperApplyEffortAction> act_cli;


class camera_manipulation
{
float kp_arm_lift;
float kp_arm_flex;
float kp_arm_roll;
float kp_wrist_flex;
float kp_wrist_roll;
float kp_base_x,kp_base_y;
//2 more for base
float positions[6];

bool enable;

int x_center,y_center; //camera center
float obj_area;

trajectory_msgs::JointTrajectory ctrl;
trajectory_msgs::JointTrajectory pos;

std_msgs::Float32MultiArray point;

sensor_msgs::JointState joints;

// std::map<std::string,float> j;

ros::NodeHandle nh_;
ros::Subscriber point_sub;
ros::Subscriber enable_sub;
ros::Subscriber position_sub;
ros::Publisher control_pub;
ros::Publisher error_pub;
ros::Publisher base_pub;
ros::Publisher gripper_pub;
ros::Publisher fnsh_pub;

void set_ctrl_to_current();
void get_current_position_controller(const control_msgs::JointTrajectoryControllerState &state);
void get_current_position(const sensor_msgs::JointState &joints);
void finish_manip(const std_msgs::Float32MultiArray error_msg);
public:
camera_manipulation(float kps[6], float kp_base[2],int x_c,int y_c,float area,int routine);
void ctrl_law_slide(const std_msgs::Float32MultiArray &p);
void ctrl_law_pose2D(const std_msgs::Float32MultiArray &p);
bool check_controllers();
void ctrl_law_flex(const std_msgs::Float32MultiArray &p);
void ctrl_law_cartesian(const std_msgs::Float32MultiArray &p);
void set_kp(float kp[6]);
void move_arm(float pos[5]);
void enable_callback(const std_msgs::Bool en);
void ctrl_callback_shelf(const std_msgs::Float32MultiArray &p);
void ctrl_callback_table(const std_msgs::Float32MultiArray &p);

};
