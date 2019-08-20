#pragma once
#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Bool.h"
#include "boost/date_time/posix_time/posix_time.hpp"
//#include "boost/thread/thread.hpp"

class TakeshiHardware
{
private:
static bool is_node_set;
//Publishers and subscribers for checking robot state
static bool stopSub;

static ros::Publisher pubRobotStop;
//Publishers and subscribers for time monitor
static ros::Publisher pubInitTimeMonitor;
static ros::Publisher pubRestartTimeMonitor;
static ros::Subscriber subTasksStop;

public:
static bool setNodeHandle(ros::NodeHandle *nh);
//Methods for operating robot state
static void stopRobot();

static void initTimeMonitor(int timeout);
//Methos for callbascks time Monitor
static bool isTaskStop();
static void taskStop(const std_msgs::Bool::ConstPtr& msg);
static void restartTime();
static bool getHeadCurrentPose(float& pan, float& tilt);

};
