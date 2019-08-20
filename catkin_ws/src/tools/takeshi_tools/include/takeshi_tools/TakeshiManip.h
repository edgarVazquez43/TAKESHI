#pragma once
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/WrenchStamped.h"
#include "manip_msgs/InverseKinematicsFloatArray.h"

using namespace std;

class TakeshiManip
{

private:
    static bool is_node_set;
    static bool _isTrGoalReached;
    static bool _stopReceived;
    static bool _isHdGoalReached;
    static geometry_msgs::Vector3 _force_data;
    static float forceX;
    static float _torsoCurrentPos;

    static ros::Publisher pubArmCloseGripper;
    static ros::Publisher pubArmGoToAngles;
    static ros::Publisher pubArmOpenGripper;
    static ros::Publisher pubHdGoToAngles;
    static ros::Publisher pubTrGoToPose;
    static ros::Subscriber subTrGoalReached;
    static ros::Subscriber subHdGoalReached;
    static ros::Subscriber subTorsoCurrentPos;
    static ros::ServiceClient cltIKFloatArray;
    //Publishers for indicating that a goal pose has been reached
    static ros::Subscriber subStopRobot;
    static ros::Subscriber subArmGoalReached;
    //Subscriber for torque gripper
    static ros::Subscriber subWristWrench;
    static ros::Subscriber wrenchSub;

    static bool _isArmGoalReached;

public:
    
    static bool setNodeHandle(ros::NodeHandle* nh);
    static void printTakeshiManipMessage(string message);
    static void printTakeshiManipError(string message);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static bool waitForArmGoalReached(int timeOut_ms);
    static void startArmGoToArticular(std::vector<float> articular);
    static bool armGoToArticular(std::vector<float> articular, int timeOut_ms);
    static bool armGoToArticular(float theta_0, float theta_1, float theta_2, float theta_3, int timeOut_ms);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////TakeshiPoses//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static bool findObjectsPose(bool inFront=false, bool rightSide=false, int timeOut_ms=4000);
    static bool navigationPose(int timeOut_ms);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////TakeshiArmPoses//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static bool armGoToFindObjects(bool waitForFinish=true, int timeOut_ms=3000);
    static bool armGoToShelf( int numberShelf, bool waitForFinish=true, int timeOut_ms=4000);
    static bool armGoToAfterPlaceInShelf(bool waitForFinish=true, int timeOut_ms=4000);
    static bool armGoToGraspBag(float wristPosition, int timeOut_ms=4000);
    static bool armGoToDeliverObjectInFloor(int timeOut_ms);
    static bool armGoToGetObjects(int timeOut_ms);

    static bool torsoGoTo(float goal,int timeOut_ms);
    static void startTorsoGoTo(float goal);
    static void getTorsoCurrentPos(float& pos);
    static bool waitForTorsoGoalReached(int timeOut_ms);
    
    

    static bool waitForArmGoToNavigation(int timeOut_ms);
    static bool waitForArmGoToOpenFridge(int timeOut_ms);
    static bool waitForArmGoToOpenFridge2(int timeOut_ms);
    static bool waitForArmGoToAxiSZ(int timeOut_ms);
    static bool waitForArmGoToAxiSX(int timeOut_ms);
    static bool waitForArmGoToOpenDoor(int timeOut_ms);
    static bool waitForArmGoToGraspFridge(int timeOut_ms);
    static bool waitForArmGraspFloor(int timeOut_ms, float articular3 = 0.0);
    static bool waitForArmGoToColorBin(int timeOut_ms);
    static bool waitForArmGoToCloseFridge(int timeOut_ms);

    static bool isHdGoalReached();
    static bool isArmGoalReached();
    static bool isTorsoGoalReached();
    
    static bool releaseObjectPose(int timeOut_ms);

    static bool armGoToFindPersonHelp();
    static void closeGripper(float torque);
    static bool armGoToNavigation();
    static bool armDeliverBag();
    static bool armGoToGraspDrawer(int timeOut_ms);
    static void openGripper(float pos);
    static bool armGoToFindPerson();
    static void startHdGoTo(float pan, float tilt);
    static void callbackHdGoalReached(const std_msgs::Bool::ConstPtr& msg);
    static bool waitForHdGoalReached(int timeOut_ms);
    static bool hdGoTo(float pan, float tilt, int timeOut_ms);
    static bool isTheObjectTaken(bool verify);
    static bool isTheHandPressed();
    static void getCurrentForce(geometry_msgs::Vector3& force_data);
    static double computeWeight(geometry_msgs::Vector3 pre_data, geometry_msgs::Vector3 post_data); 
     //Methods for calculating inverse kinematics
    static bool inverseKinematicsGeometric(std::vector<float>& cartesian, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction);  // Takeshi
    //Callbacks for catching goal-reached signals
    static void callbackRobotStop(const std_msgs::Empty::ConstPtr& msg);
    static void callbackArmGoalReached(const std_msgs::Bool::ConstPtr& msg);
    static void callbackTrGoalReached(const std_msgs::Bool::ConstPtr& msg);
    static void callbackWristWrench(const geometry_msgs::WrenchStamped::ConstPtr& msg);
    static void callbackTorsoCurrentPos(const std_msgs::Float32::ConstPtr& msg);
    static void wristWrenchCallback(const geometry_msgs::WrenchStamped wr);

};
