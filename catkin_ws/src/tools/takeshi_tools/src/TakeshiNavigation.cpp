#include "takeshi_tools/TakeshiNavigation.h"

bool TakeshiNavigation::is_node_set = false;

float TakeshiNavigation::currentRobotX = 0;
float TakeshiNavigation::currentRobotY = 0;
float TakeshiNavigation::currentRobotTheta = 0;
bool TakeshiNavigation::_stopReceived = false;
bool TakeshiNavigation::_isGlobalGoalReached = false;
bool TakeshiNavigation::_isGoalReached = false;
bool TakeshiNavigation::_obstacleInFront = false;
bool TakeshiNavigation::_collisionRisk;   


//Subscriber for checking goal-pose-reached signal
ros::Subscriber TakeshiNavigation::subGlobalGoalReached;
ros::Subscriber TakeshiNavigation::subGoalReached;
ros::Subscriber TakeshiNavigation::subStopRobot;

//Publishers and subscriber for mvn_pln
ros::ServiceClient TakeshiNavigation::cltPlanPath; 
ros::Publisher TakeshiNavigation::pubMvnPlnGetCloseLoc;
ros::Publisher TakeshiNavigation::pubSimpleMoveGoalPath;

ros::Publisher TakeshiNavigation::pubMvnPlnGetCloseXYA;
tf::TransformListener* TakeshiNavigation::tf_listener;
//Subscribers for obstacle avoidance
ros::Publisher TakeshiNavigation::pubObsAvoidEnable;
ros::Subscriber TakeshiNavigation::subObsInFront;
ros::Subscriber TakeshiNavigation::subCollisionRisk;   

//Publishers and subscribers for operating the simple_move node
ros::Publisher TakeshiNavigation::pubSimpleMoveDist;
ros::Publisher TakeshiNavigation::pubSimpleMoveDistAngle;
ros::Publisher TakeshiNavigation::pubSimpleMoveLateral;
ros::Publisher TakeshiNavigation::pubSimpleMoveGoalPose;
ros::Publisher TakeshiNavigation::pubSimpleMoveGoalRelPose;  

//
//The startSomething functions, only publish the goal pose or path and return inmediately after starting movement
//The others, block until a goal-reached signal is received
//

//for path planning
ros::ServiceClient TakeshiNavigation::cltPathFromMapAStar;
ros::ServiceClient TakeshiNavigation::cltGetMap;

using namespace std; //omg esto no esta bien!!!


bool TakeshiNavigation::setNodeHandle(ros::NodeHandle* nh)
{
        if(TakeshiNavigation::is_node_set)
                return true;
        if(nh == 0)
                return false;

        cout << "\033[1;37m     TakeshiNavigation.->Setting ros node...\033[0m" << endl;
	tf_listener = new tf::TransformListener();
        //Subscriber for checking goal-pose-reached signal
        subStopRobot = nh->subscribe("/hardware/robot_state/stop", 1, &TakeshiNavigation::callbackRobotStop);
        subGlobalGoalReached = nh->subscribe("/navigation/global_goal_reached", 1, &TakeshiNavigation::callbackGlobalGoalReached);
        subGoalReached = nh->subscribe("/navigation/goal_reached", 1, &TakeshiNavigation::callbackGoalReached);
        //Publishers and subscribers for mvn_pln
	cltPlanPath = nh->serviceClient<navig_msgs::PlanPath>("/navigation/mvn_pln/plan_path");
        pubMvnPlnGetCloseLoc = nh->advertise<std_msgs::String>("/navigation/mvn_pln/get_close_loc", 1);
        pubMvnPlnGetCloseXYA = nh->advertise<std_msgs::Float32MultiArray>("/navigation/mvn_pln/get_close_xya", 1);
        //Publishers and subscribers for operating the simple_move node
        pubSimpleMoveDist = nh->advertise<std_msgs::Float32>("/navigation/path_planning/simple_move/goal_dist", 1);
        pubSimpleMoveDistAngle=nh->advertise<std_msgs::Float32MultiArray>("/navigation/path_planning/simple_move/goal_dist_angle",1);
        pubSimpleMoveLateral = nh->advertise<std_msgs::Float32>("/navigation/path_planning/simple_move/goal_lateral", 1);
        pubSimpleMoveGoalPath = nh->advertise<nav_msgs::Path>("/navigation/path_planning/simple_move/goal_path", 1);
	pubSimpleMoveGoalPose = nh->advertise<geometry_msgs::Pose2D>("/navigation/path_planning/simple_move/goal_pose", 1);
	pubSimpleMoveGoalRelPose = nh->advertise<geometry_msgs::Pose2D>("/navigation/path_planning/simple_move/goal_rel_pose", 1);
        //Subscribers and publishers for obstacle avoidance

        subObsInFront = nh->subscribe("/navigation/obs_avoid/obs_in_front", 1, &TakeshiNavigation::callbackObstacleInFront);
	subCollisionRisk = nh->subscribe("/navigation/obs_avoid/collision_risk", 1, &TakeshiNavigation::callbackCollisionRisk);  
        pubObsAvoidEnable = nh->advertise<std_msgs::Bool>("/navigation/obs_avoid/enable", 1);

        //Subscribers for path planning
        cltGetMap = nh->serviceClient<nav_msgs::GetMap>("/navigation/localization/static_map");
        cltPathFromMapAStar = nh->serviceClient<navig_msgs::PathFromMap>("/navigation/path_planning/path_calculator/a_star_from_map");

	//Publisher and subscribers for localization
	tf_listener->waitForTransform("map", "base_link", ros::Time(0), ros::Duration(5.0));
	
        TakeshiManip::setNodeHandle(nh);
        TakeshiHardware::setNodeHandle(nh);
        TakeshiNavigation::is_node_set = true;
        return true;
}

void printMessage(std::string message){
    std::cout << "\033[1;35m     TakeshiNavigation.->" << message << "\033[0m" << std::endl;
}

void printErrorMessage(std::string message){
    std::cout << "\033[1;31m     TakeshiNavigation Error!.->" << message << "\033[0m" << std::endl;
}

void TakeshiNavigation::startGetClose(std::string location)
{
        std_msgs::String msg;
        msg.data = location;
        TakeshiNavigation::_isGlobalGoalReached = false;
        pubMvnPlnGetCloseLoc.publish(msg);
}

void TakeshiNavigation::startGetClose(float x, float y)
{
        std_msgs::Float32MultiArray msg;
        msg.data.push_back(x);
        msg.data.push_back(y);
        TakeshiNavigation::_isGlobalGoalReached = false;
        pubMvnPlnGetCloseXYA.publish(msg);
}

void TakeshiNavigation::startGetClose(float x, float y,  float angle)
{
        std_msgs::Float32MultiArray msg;
        msg.data.push_back(x);
        msg.data.push_back(y);
	msg.data.push_back(angle);
	TakeshiManip::torsoGoTo(0.0, 1500);
	TakeshiManip::armGoToNavigation();
	ros::Duration(2.0).sleep();
        TakeshiNavigation::_isGlobalGoalReached = false;
        pubMvnPlnGetCloseXYA.publish(msg);
}

void TakeshiNavigation::startGoToPose(float x, float y, float angle)
{
  geometry_msgs::Pose2D msg;
  msg.x = x;
  msg.y = y;
  msg.theta = angle;
  TakeshiNavigation::_isGoalReached = false;
  pubSimpleMoveGoalPose.publish(msg);
}

void TakeshiNavigation::startGoToRelPose(float relX, float relY, float relTheta)
{
  geometry_msgs::Pose2D msg;
  msg.x = relX;
  msg.y = relY;
  msg.theta = relTheta;
  TakeshiNavigation::_isGoalReached = false;
  pubSimpleMoveGoalRelPose.publish(msg);
} 

//These methods use the simple_move node
void TakeshiNavigation::startMoveDist(float distance)
{
    std_msgs::Float32 msg;
    msg.data = distance;
    TakeshiNavigation::_isGoalReached = false;
    printMessage("Start Move distance: "+ std::to_string(distance));
    pubSimpleMoveDist.publish(msg);
}


bool TakeshiNavigation::getClose(std::string location, int timeOut_ms)
{
        ros::Rate loop(10);
        TakeshiManip::navigationPose(5000);
        ros::spinOnce();
        loop.sleep();
        TakeshiNavigation::startGetClose(location);
        printMessage("Get close: " + location + "  timeout: " + std::to_string(timeOut_ms));
        return TakeshiNavigation::waitForGlobalGoalReached(timeOut_ms);
}

//Aqui!!!!!!!!!!!!
bool TakeshiNavigation::getClose(std::vector<std::string> location, int timeOut_ms)
{
        ros::Rate loop(10);
        TakeshiManip::navigationPose(5000);
        ros::spinOnce();
        loop.sleep();
        
        std::vector<std::string> tmp;

        tmp=location;


        TakeshiNavigation::startGetClose(tmp[1]);
        printMessage("Get close: " + tmp[1] + "  timeout: " + std::to_string(timeOut_ms));
        return TakeshiNavigation::waitForGlobalGoalReached(timeOut_ms);
}

void TakeshiNavigation::startMoveDistAngle(float distance, float angle)
{
        std_msgs::Float32MultiArray msg;
        msg.data.push_back(distance);
        msg.data.push_back(angle);
        TakeshiNavigation::_isGoalReached = false;
        printMessage("Start move dist angle: " + std::to_string(distance) + " angle: " + std::to_string(angle));
        pubSimpleMoveDistAngle.publish(msg);
}

void TakeshiNavigation::startMovePath(nav_msgs::Path& path)
{
    printMessage("Publishing goal path..");
    TakeshiNavigation::_isGoalReached = false;
    TakeshiNavigation::pubSimpleMoveGoalPath.publish(path);
}

bool TakeshiNavigation::getClose(float x, float y,float th, int timeOut_ms)
{
        ros::Rate loop(10);
        TakeshiManip::navigationPose(5000);
        ros::spinOnce();
        loop.sleep();
        std_msgs::Float32MultiArray msg;
        msg.data.push_back(x);
        msg.data.push_back(y);
        msg.data.push_back(th);
        TakeshiNavigation::_isGlobalGoalReached = false;
        pubMvnPlnGetCloseXYA.publish(msg);
        cout << "\033[1;37m     TakeshiNavigation.->Get close: "
             <<  x <<","<< y<<"," << th <<", "
             << "timeout: " << timeOut_ms << "\033[0m" << endl;
        return TakeshiNavigation::waitForGlobalGoalReached(timeOut_ms);
}

void TakeshiNavigation::startMoveLateral(float distance)
{
        printMessage("Publishing goal lateral distance: " + std::to_string(distance));
        std_msgs::Float32 msg;
        msg.data = distance;
        TakeshiNavigation::_isGoalReached = false;
        TakeshiNavigation::pubSimpleMoveLateral.publish(msg);
}

bool TakeshiNavigation::waitForGlobalGoalReached(int timeOut_ms)
{
        int attempts = timeOut_ms / 100;
        ros::Rate loop(10);
        TakeshiNavigation::_stopReceived = false;
        while(ros::ok() && !TakeshiNavigation::_isGlobalGoalReached && !TakeshiNavigation::_stopReceived && attempts-- >= 0){
                ros::spinOnce();
                loop.sleep();
        }
        TakeshiNavigation::_stopReceived = false; //This flag is set True in the subscriber callback

        _isGlobalGoalReached ? printMessage("Global goal reached: true") : printErrorMessage("Global goal reached: false") ;
        if(!_isGlobalGoalReached)
            TakeshiHardware::stopRobot();
        return TakeshiNavigation::_isGlobalGoalReached;
}
//Coyo is here_:

void TakeshiNavigation::getRobotPose(float& currentX, float& currentY, float& currentTheta)
{
  tf::StampedTransform transform;
  tf::Quaternion q;
  TakeshiNavigation::tf_listener->lookupTransform("map", "base_link", ros::Time(0), transform);
  TakeshiNavigation::currentRobotX = transform.getOrigin().x();
  TakeshiNavigation::currentRobotY = transform.getOrigin().y();
  q = transform.getRotation();
  TakeshiNavigation::currentRobotTheta = atan2((float)q.z(), (float)q.w()) * 2;

  currentX = TakeshiNavigation::currentRobotX;
  currentY = TakeshiNavigation::currentRobotY;
  currentTheta = TakeshiNavigation::currentRobotTheta;
}

void TakeshiNavigation::getRobotPoseFromOdom(float& currentX, float& currentY,
					     float& currentTheta) {
  tf::StampedTransform transform;
  tf::Quaternion q;
  TakeshiNavigation::tf_listener->lookupTransform("/odom", "/base_link",
						  ros::Time(0), transform);
  q = transform.getRotation();

  currentX = transform.getOrigin().x();
  currentY = transform.getOrigin().y();
  currentTheta = q.getAngle() * q.getAxis().z();
}     

bool TakeshiNavigation::getOccupancyGrid(nav_msgs::OccupancyGrid& map)
{
        nav_msgs::GetMap srvGetMap;
        if(!TakeshiNavigation::cltGetMap.call(srvGetMap)){
                printErrorMessage("Cannot get map from map_server");
                return false;
        }
        map = srvGetMap.response.map;
        return true;
}


bool TakeshiNavigation::calcPathFromMapAStar(float startX, float startY, float goalX, float goalY, nav_msgs::Path& result)
{
        printMessage("Calculating path from " + std::to_string(startX) + " " + std::to_string(startX) + " to " + std::to_string(goalX) + " " + std::to_string(goalY) + "by A* using only map");
        nav_msgs::GetMap srvGetMap;
        navig_msgs::PathFromMap srvPathFromMap;

        if(!TakeshiNavigation::cltGetMap.call(srvGetMap)){
                printMessage("(feat coyo)->Cannot get map from map_server.");
                return false;
        }
        srvPathFromMap.request.map = srvGetMap.response.map;
        srvPathFromMap.request.start_pose.position.x = startX;
        srvPathFromMap.request.start_pose.position.y = startY;
        srvPathFromMap.request.goal_pose.position.x = goalX;
        srvPathFromMap.request.goal_pose.position.y = goalY;

        bool success;
        success = TakeshiNavigation::cltPathFromMapAStar.call(srvPathFromMap);
        success ? printMessage("Path calculated succesfully by path_calculator using A* using only map") : 
                  printErrorMessage("Cannot calculate path by path_calculator using A* using only map");
        ros::spinOnce();
        result = srvPathFromMap.response.path;
        return success;
}
//Coyo was here
//Callbacks for subscribers

void TakeshiNavigation::callbackRobotStop(const std_msgs::Empty::ConstPtr& msg)
{
        TakeshiNavigation::_stopReceived = true;
}

void TakeshiNavigation::callbackGlobalGoalReached(const std_msgs::Bool::ConstPtr& msg)
{
        TakeshiNavigation::_isGlobalGoalReached = msg->data;
}

bool TakeshiNavigation::moveDist(float distance, int timeOut_ms)
{
    TakeshiNavigation::startMoveDist(distance);
    return TakeshiNavigation::waitForGoalReached(timeOut_ms);
}

bool TakeshiNavigation::moveDistAngle(float distance, float angle, int timeOut_ms)
{
        TakeshiNavigation::startMoveDistAngle(distance, angle);
        return TakeshiNavigation::waitForGoalReached(timeOut_ms);
}


bool TakeshiNavigation::movePath(nav_msgs::Path& path, int timeOut_ms)
{
  TakeshiNavigation::startMovePath(path);
  return TakeshiNavigation::waitForGoalReached(timeOut_ms);
}

bool TakeshiNavigation::goToPose(float x, float y, float angle, int timeOut_ms)
{
  TakeshiNavigation::startGoToPose(x, y, angle);
  return TakeshiNavigation::waitForGoalReached(timeOut_ms);
}

bool TakeshiNavigation::goToRelPose(float relX, float relY, float relTheta, int timeOut_ms)
{
  TakeshiNavigation::startGoToRelPose(relX, relY, relTheta);
  return TakeshiNavigation::waitForGoalReached(timeOut_ms);
}

//These methods use the mvn_pln node.
bool TakeshiNavigation::planPath(float startX, float startY, float goalX, float goalY, nav_msgs::Path& path)
{
  navig_msgs::PlanPath srv;
  srv.request.start_location_id = "";
  srv.request.goal_location_id = "";
  srv.request.start_pose.position.x = startX;
  srv.request.start_pose.position.y = startY;
  srv.request.goal_pose.position.x = goalX;
  srv.request.goal_pose.position.y = goalY;
  bool success = TakeshiNavigation::cltPlanPath.call(srv);
  path = srv.response.path;
  return success;
}

bool TakeshiNavigation::planPath(float goalX, float goalY, nav_msgs::Path& path)
{
  float robotX, robotY, robotTheta;
  TakeshiNavigation::getRobotPose(robotX, robotY, robotTheta);
  return TakeshiNavigation::planPath(robotX, robotY, goalX, goalY, path);
}

bool TakeshiNavigation::planPath(std::string start_location, std::string goal_location, nav_msgs::Path& path)
{
  navig_msgs::PlanPath srv;
  srv.request.start_location_id = start_location;
  srv.request.goal_location_id = goal_location;
  bool success = TakeshiNavigation::cltPlanPath.call(srv);
  path = srv.response.path;
  return success;
}

bool TakeshiNavigation::planPath(std::string start_location, float goalX, float goalY, nav_msgs::Path& path)
{
  navig_msgs::PlanPath srv;
  srv.request.start_location_id = start_location;
  srv.request.goal_location_id = "";
  srv.request.goal_pose.position.x = goalX;
  srv.request.goal_pose.position.y = goalY;
  bool success = TakeshiNavigation::cltPlanPath.call(srv);
  path = srv.response.path;
  return success;
}

bool TakeshiNavigation::planPath(float startX, float startY, std::string goal_location, nav_msgs::Path& path)
{
  navig_msgs::PlanPath srv;
  srv.request.start_location_id = "";
  srv.request.goal_location_id = goal_location;
  srv.request.start_pose.position.x = startX;
  srv.request.start_pose.position.y = startY;
  bool success = TakeshiNavigation::cltPlanPath.call(srv);
  path = srv.response.path;
  return success;
} 

bool TakeshiNavigation::isGoalReached()
{
    return TakeshiNavigation::_isGoalReached;
}

void TakeshiNavigation::callbackGoalReached(const std_msgs::Bool::ConstPtr& msg)
{
        TakeshiNavigation::_isGoalReached = msg->data;
}

bool TakeshiNavigation::waitForGoalReached(int timeOut_ms)
{
        int attempts = timeOut_ms / 100;
        ros::Rate loop(10);
        TakeshiNavigation::_stopReceived = false;
        while(ros::ok() && !TakeshiNavigation::_isGoalReached && !TakeshiNavigation::_stopReceived && attempts-- >= 0)
        {
                ros::spinOnce();
                loop.sleep();
        }
        TakeshiNavigation::_stopReceived = false; //This flag is set True in the subscriber callback
        TakeshiNavigation::_isGoalReached ? printMessage("Goal reached: true") :
                                            printErrorMessage("Goal reached : false");
        return TakeshiNavigation::_isGoalReached;
}

//Methods for obstacle avoidance
bool TakeshiNavigation::obstacleInFront()
{
    ros::spinOnce();
    return TakeshiNavigation::_obstacleInFront;
}

bool TakeshiNavigation::collisionRisk()
{
  return TakeshiNavigation::_collisionRisk;
} 

//Callbacks for obstacle avoidance
void TakeshiNavigation::callbackObstacleInFront(const std_msgs::Bool::ConstPtr& msg)
{
        TakeshiNavigation::_obstacleInFront = msg->data;
}

void TakeshiNavigation::callbackCollisionRisk(const std_msgs::Bool::ConstPtr& msg)
{
  //std::cout << "JustinaNvigation.-<CollisionRisk: " << int(msg->data) << std::endl;
  TakeshiNavigation::_collisionRisk = msg->data;
}    

void TakeshiNavigation::enableObstacleDetection(bool enable)
{
        enable ? printMessage("Enabling obstacle detection..."):
                 printMessage("Disabling obstacle detection...");
        std_msgs::Bool msg;
        msg.data = enable;
        TakeshiNavigation::pubObsAvoidEnable.publish(msg);
}


bool TakeshiNavigation::moveLateral(float distance, int timeOut_ms)
{
        TakeshiNavigation::startMoveLateral(distance);
        return TakeshiNavigation::waitForGoalReached(timeOut_ms);
}
