#pragma once
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Empty.h"
#include "std_msgs/Float32MultiArray.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiHardware.h"
#include "navig_msgs/PlanPath.h"
#include "navig_msgs/PathFromMap.h"
#include "nav_msgs/Path.h"
#include "nav_msgs/GetMap.h"
#include "nav_msgs/OccupancyGrid.h"
#include "tf/transform_listener.h"

class TakeshiNavigation

{
 private:
  static bool is_node_set;
  static float currentRobotX;
  static float currentRobotY;
  static float currentRobotTheta;
  static bool _stopReceived;
  static bool _obstacleInFront;
  static bool _collisionRisk;
  static bool _isGlobalGoalReached;
  static bool _isGoalReached;

  //Subscriber for checking goal-pose-reached signal
  static ros::Subscriber subGlobalGoalReached;
  static ros::Subscriber subStopRobot;
  static ros::Subscriber subGoalReached;

  //Publishers and subscribers for mvn_pln
  static ros::ServiceClient cltPlanPath;
  static ros::Publisher pubMvnPlnGetCloseLoc;
  static ros::Publisher pubMvnPlnGetCloseXYA;
  //Publishers and subscribers for localization
  static tf::TransformListener* tf_listener;    
  //Publishers and subscribers for operating the simple_move node
  static ros::Publisher pubSimpleMoveDist;
  static ros::Publisher pubSimpleMoveDistAngle;
  static ros::Publisher pubSimpleMoveLateral;
  static ros::Publisher pubSimpleMoveGoalPath;
  static ros::Publisher pubSimpleMoveGoalPose;
  static ros::Publisher pubSimpleMoveGoalRelPose; 
  //Subscribers for obstacle avoidance
  static ros::Publisher pubObsAvoidEnable;
  static ros::Subscriber subObsInFront;
  static ros::Subscriber subCollisionRisk;
  //for path planning
  static ros::ServiceClient cltPathFromMapAStar;
  static ros::ServiceClient cltGetMap;




 public:
  //
  //The startSomething functions, only publish the goal pose or path and return inmediately after starting movement
  //The others, block until a goal-reached signal is received
  //
  static bool setNodeHandle(ros::NodeHandle* nh);

  //Callbacks for subscribers
  static void callbackGlobalGoalReached(const std_msgs::Bool::ConstPtr& msg);
  static void callbackRobotStop(const std_msgs::Empty::ConstPtr& msg);
  static void callbackGoalReached(const std_msgs::Bool::ConstPtr& msg);

  static void startGetClose(std::string location);
  static void startGetClose(float x, float y);
  static void startGetClose(float x, float y, float angle);
  static void startMovePath(nav_msgs::Path& path);
  static void startMoveDistAngle(float distance, float angle);
  static void startMoveDist(float distance);
  static void startMoveLateral(float distance);
  static void startGoToPose(float x, float y, float angle);
  static void startGoToRelPose(float relX, float relY, float relTheta);
  static bool waitForGoalReached(int timeOut_ms);
  static bool waitForGlobalGoalReached(int timeOut_ms);

  //These methods use the simple_move node
  static bool getClose(std::string location, int timeOut_ms);
  static bool getClose(std::vector<std::string> location, int timeOut_ms);
  static bool getClose(float x, float y,float th, int timeOut_ms);
  static void getRobotPose(float& currentX, float& currentY, float& currentTheta);
  static void getRobotPoseFromOdom(float& currentX, float& currentY, float& currentTheta);  
  static bool moveDist(float distance, int timeOut_ms);
  static bool moveLateral(float distance, int timeOut_ms);
  static bool movePath(nav_msgs::Path& path, int timeOut_ms);
  static bool goToPose(float x, float y, float angle, int timeOut_ms);
  static bool goToRelPose(float relX, float relY, float relTheta, int timeOut_ms);
  static bool planPath(float startX, float startY, float goalX, float goalY, nav_msgs::Path& path);
  static bool planPath(float goalX, float goalY, nav_msgs::Path& path);
  static bool planPath(std::string start_location, std::string goal_location, nav_msgs::Path& path);
  static bool planPath(std::string start_location, float goalX, float goalY,  nav_msgs::Path& path);
  static bool planPath(float startX, float startY, std::string goal_location, nav_msgs::Path& path);
  static bool moveDistAngle(float distance, float angle, int timeOut_ms);
  

  //Methods for obstacle avoidance
  static bool obstacleInFront();
  static bool collisionRisk();
  static void enableObstacleDetection(bool enable);

  //Callbacks for obstacle avoidance
  static void callbackObstacleInFront(const std_msgs::Bool::ConstPtr& msg);
  static void callbackCollisionRisk(const std_msgs::Bool::ConstPtr& msg);
  static bool isGoalReached();

  //This functions call services, so, they block until a response is received. They use the path_calculator node
  //This function uses the path calculator node, which only calculates a path and nothing more.
  //Instead, mvn_pln calcs path by taking into account kinect, laser and others.
  static bool getOccupancyGrid(nav_msgs::OccupancyGrid& map);
  static bool calcPathFromMapAStar(float startX, float startY, float goalX, float goalY, nav_msgs::Path& result);

};
