#include <ros/ros.h>
#include "std_msgs/Bool.h"
#include "vision_msgs/Skeletons.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"

#include "sensor_msgs/JointState.h"
#include "trajectory_msgs/JointTrajectory.h"

class skeleton_follower {
private:
ros::NodeHandle nh_;
ros::Subscriber skeletonSubscriber;
ros::Subscriber enableSubscriber;
ros::Publisher control_pub;
ros::Publisher  twistPublisher;
double setpointY,setpointX,kx,ky;
void enableCallback(const std_msgs::Bool &msg);
void skeletonCallback(const vision_msgs::Skeletons &skl);
bool getHeadPose(sensor_msgs::JointState &headState);
void headCtrl(double error, double kp);
public:
skeleton_follower (ros::NodeHandle &nh);

};
