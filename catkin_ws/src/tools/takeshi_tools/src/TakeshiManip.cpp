#include "takeshi_tools/TakeshiManip.h"

bool TakeshiManip::is_node_set = false;
ros::Publisher TakeshiManip::pubTrGoToPose;
bool TakeshiManip::_stopReceived = false;
bool TakeshiManip::_isTrGoalReached = false;
bool TakeshiManip::_isHdGoalReached = false;
bool TakeshiManip::_isArmGoalReached = false;
geometry_msgs::Vector3 TakeshiManip::_force_data;

float TakeshiManip::forceX = 0.0;
float TakeshiManip::_torsoCurrentPos;


ros::Publisher TakeshiManip::pubArmGoToAngles;
ros::Publisher TakeshiManip::pubArmCloseGripper;
ros::Publisher TakeshiManip::pubArmOpenGripper;
ros::Publisher TakeshiManip::pubHdGoToAngles;
ros::Subscriber TakeshiManip::subTrGoalReached;
ros::Subscriber TakeshiManip::subHdGoalReached;
ros::Subscriber TakeshiManip::subTorsoCurrentPos;
//Subscribers for indicating that a goal pose has been reached
ros::Subscriber TakeshiManip::subStopRobot;
ros::Subscriber TakeshiManip::subArmGoalReached;
//Subcribers for torque gripper
ros::Subscriber TakeshiManip::subWristWrench;
ros::Subscriber TakeshiManip::wrenchSub;

ros::ServiceClient TakeshiManip::cltIKFloatArray;


bool TakeshiManip::setNodeHandle(ros::NodeHandle* nh)
{
    if(TakeshiManip::is_node_set)
        return true;
    if(nh == 0)
        return false;
    cout << "\033[1;32m     TakeshiManip.->Setting ros node...\033[0m" << endl;
    TakeshiManip::pubTrGoToPose = nh->advertise<std_msgs::Float32>("/hardware/torso/goal_pose", 1);
    TakeshiManip::pubArmGoToAngles   = nh->advertise<std_msgs::Float32MultiArray>("/hardware/arm/goal_pose", 1);
    TakeshiManip::pubArmCloseGripper = nh->advertise<std_msgs::Float32>("/hardware/arm/torque_gripper", 1);
    TakeshiManip::pubArmOpenGripper  = nh->advertise<std_msgs::Float32>("/hardware/arm/goal_gripper", 1);
    TakeshiManip::pubHdGoToAngles = nh->advertise<std_msgs::Float32MultiArray>("/manipulation/manip_pln/hd_goto_angles", 1);
    TakeshiManip::cltIKFloatArray = nh->serviceClient<manip_msgs::InverseKinematicsFloatArray>("/manipulation/ik_geometric/ik_float_array");             // TAKESHI
    TakeshiManip::subStopRobot = nh->subscribe("/hardware/robot_state/stop", 1, &TakeshiManip::callbackRobotStop);
    //Subscribers for indicating that a goal pose has been reached
    TakeshiManip::subHdGoalReached = nh->subscribe("/manipulation/hd_goal_reached", 1, &TakeshiManip::callbackHdGoalReached);
    TakeshiManip::subTrGoalReached = nh->subscribe("/hardware/torso/goal_reached", 1, &TakeshiManip::callbackTrGoalReached);
    TakeshiManip::subArmGoalReached = nh->subscribe("/hardware/arm/armGoalPose", 1, &TakeshiManip::callbackArmGoalReached);
    TakeshiManip::subTorsoCurrentPos = nh->subscribe("/hardware/torso/current_pose", 1, &TakeshiManip::callbackTorsoCurrentPos);
    TakeshiManip::subWristWrench = nh->subscribe("/hsrb/wrist_wrench/compensated", 1, &TakeshiManip::callbackWristWrench);
    TakeshiManip::wrenchSub = nh->subscribe("/hsrb/wrist_wrench/compensated",2,&TakeshiManip::wristWrenchCallback);

    TakeshiManip::is_node_set = true;
    return true;
}

void TakeshiManip::printTakeshiManipMessage(string message){
        cout << "\033[1;32m     TakeshiManip.->"<< message <<"\033[0m" << endl;
}

void TakeshiManip::printTakeshiManipError(string message){
        cout << "\033[1;31m     TakeshiManip.->"<< message <<"\033[0m" << endl;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////Takeshi Articular methods//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TakeshiManip::armGoToArticular(std::vector<float> articular, int timeOut_ms)
{
  TakeshiManip::startArmGoToArticular(articular);
  return TakeshiManip::waitForArmGoalReached(timeOut_ms);
}

bool TakeshiManip::armGoToArticular(float theta_0, float theta_1, float theta_2, float theta_3, int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(theta_0);
  articular.push_back(theta_1);
  articular.push_back(theta_2);
  articular.push_back(theta_3);
  TakeshiManip::startArmGoToArticular(articular);
  return TakeshiManip::waitForArmGoalReached(timeOut_ms);
}


void TakeshiManip::startArmGoToArticular(std::vector<float> articular)
{
  std_msgs::Float32MultiArray msg;
  msg.data = articular;
  TakeshiManip::printTakeshiManipMessage("Start arm go to articular: "
  + to_string(articular[0]) + " " 
  + to_string(articular[1]) + " " 
  + to_string(articular[2]) + " " 
  + to_string(articular[3]) );
  TakeshiManip::pubArmGoToAngles.publish(msg);
}

bool TakeshiManip::waitForArmGoalReached(int timeOut_ms)
{
    int attempts = timeOut_ms / 100;
    ros::Rate loop(10);
    TakeshiManip::_stopReceived = false;
    TakeshiManip::_isArmGoalReached = false;
    while(ros::ok() && !TakeshiManip::_isArmGoalReached && !TakeshiManip::_stopReceived && attempts-- >= 0)
    {
        ros::spinOnce();
        loop.sleep();
    }
    if(_isArmGoalReached)
      TakeshiManip::printTakeshiManipMessage("Wait for arm goal reached: " + to_string(_isArmGoalReached));
    else
      TakeshiManip::printTakeshiManipError("Wait for arm goal reached: " + to_string(_isArmGoalReached));
    TakeshiManip::_stopReceived = false; //This flag is set True in the subscriber callback
    return TakeshiManip::_isArmGoalReached;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////TakeshiPoses//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TakeshiManip::findObjectsPose(bool inFront, bool rightSide, int timeOut_ms){
    
    if(!inFront){
          TakeshiManip::printTakeshiManipMessage("Find objects pose. rightSide="+to_string(rightSide));
          TakeshiManip::armGoToFindObjects(false);
          TakeshiManip::torsoGoTo(0.65, timeOut_ms);
          if(!rightSide)
      	  {
      	    TakeshiManip::hdGoTo(1.5707, 0.0, 5000);
      	    TakeshiManip::hdGoTo(1.5707, -0.8, 5000);
      	  }
      	  else
      	  {
      	    TakeshiManip::hdGoTo(-1.5707, 0.0, 5000);
      	    TakeshiManip::hdGoTo(-1.5707, -0.8, 5000);
      	  }
      	  return true;
    }

    else{
        TakeshiManip::printTakeshiManipMessage("Find objects in front");
        TakeshiManip::hdGoTo(0.0, 0.0, 5000);
        ros::Duration(1).sleep();
        TakeshiManip::armGoToNavigation();
        TakeshiManip::torsoGoTo(0.15, timeOut_ms);  
        TakeshiManip::hdGoTo(0.0, -0.5, 5000);
    }
}

bool TakeshiManip::navigationPose(int timeOut_ms){
    cout << "\033[1;32m     TakeshiManip.-> Navigation pose\033[0m" << endl;
    bool success=false;
    int nextState=1;


    ros::Rate loop(10);

    while(ros::ok() && !success){
      switch (nextState) {
        case 1:
          TakeshiManip::hdGoTo(0.0, 0.0, 5000);
          nextState=2;
          break;

        case 2:
          TakeshiManip::armGoToNavigation();
          nextState=3;
          break;

        case 3:
          if(TakeshiManip::torsoGoTo(0.0, timeOut_ms))
            nextState=4;
          break;

        case 4:
          success=true;
          break;
      }

      ros::spinOnce();
      loop.sleep();
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////TakeshiArmPoses//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TakeshiManip::armGoToFindObjects(bool waitForFinish, int timeOut_ms){
  std::vector<float> articular;
  articular.push_back(-0.35);
  articular.push_back( -1.5707);
  articular.push_back( -1.5707);
  articular.push_back( 0.0);
  if(waitForFinish)
    return TakeshiManip::armGoToArticular(articular, timeOut_ms);
  else
    TakeshiManip::startArmGoToArticular(articular);
  return true;
}

bool TakeshiManip::armGoToGraspBag(float wristPosition, int timeOut_ms){
  TakeshiManip::openGripper(1.0);
  ros::Duration(1).sleep();
  std::vector<float> articular;
  articular.push_back( -1.3);
  articular.push_back(  0.0);
  articular.push_back( -1.8);
  articular.push_back( wristPosition);
  TakeshiManip::armGoToArticular(articular,timeOut_ms);
  return true;
}

bool TakeshiManip::armGoToGetObjects(int timeOut_ms){
  TakeshiManip::openGripper(1.0);
  ros::Duration(1).sleep();
  std::vector<float> articular;
  articular.push_back(  0.0);
  articular.push_back(  0.0);
  articular.push_back( -1.5);
  articular.push_back(  0.0);
  return TakeshiManip::armGoToArticular(articular,timeOut_ms);
}

bool TakeshiManip::armGoToDeliverObjectInFloor(int timeOut_ms){
  std::vector<float> articular;
  articular.push_back(-1.9);
  articular.push_back( 0.0);
  articular.push_back(-0.3);
  articular.push_back(0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::armGoToShelf(int numberShelf, bool waitForFinish, int timeOut_ms){ 
  std::vector<float> articular;
  float torso=0;
  TakeshiManip::printTakeshiManipMessage("Arm go to shelf pose: " + to_string(numberShelf));
  if(numberShelf == 0){
      articular.push_back(-0.5);
      articular.push_back( 0.0);
      articular.push_back(-1.1);
      articular.push_back( 0.0);
      torso = 0.1;
  }

  else if(numberShelf == 1){
      articular.push_back(-1.45);
      articular.push_back( 0.0);
      articular.push_back(-0.2);
      articular.push_back( 0.0);
      torso = 0.1;
  }

  else{
      articular.push_back(-2.0);
      articular.push_back( 0.0);
      articular.push_back( 0.4);
      articular.push_back( 0.0);
      torso = 0.0;
  }

  TakeshiManip::torsoGoTo(torso, 2000);

  if(waitForFinish)
    return TakeshiManip::armGoToArticular(articular, timeOut_ms);
  else
    TakeshiManip::startArmGoToArticular(articular);
  return true;

}

bool TakeshiManip::armGoToAfterPlaceInShelf(bool waitForFinish, int timeOut_ms){
      std::vector<float> articular;
      articular.push_back( 0.0);
      articular.push_back( 0.0);
      articular.push_back(-1.57);
      articular.push_back( 0.0);
      if(waitForFinish)
          return TakeshiManip::armGoToArticular(articular, timeOut_ms);
      else
          TakeshiManip::startArmGoToArticular(articular);
      return true;
}

bool TakeshiManip::releaseObjectPose(int timeOut_ms){
    cout << "\033[1;32m     TakeshiManip.-> Release Object Pose\033[0m" << endl;
    std::vector<float> articular;
    articular.push_back( -0.5);
    articular.push_back(  0.0);
    articular.push_back( -2.0);
    articular.push_back( 0.0);

    TakeshiManip::torsoGoTo(3.0, timeOut_ms);
    TakeshiManip::armGoToArticular(articular, timeOut_ms);
    TakeshiManip::hdGoTo(0.0, -0.8, timeOut_ms);
    TakeshiManip::openGripper(1.0);
    ros::Duration(5.0).sleep();
    TakeshiManip::hdGoTo(0.0, 0.0, timeOut_ms);
    return true;
}

//Missing: made a subscriber for fill torso current pos
void TakeshiManip::getTorsoCurrentPos(float& pos)
{
  pos = TakeshiManip::_torsoCurrentPos;
}


bool TakeshiManip::torsoGoTo(float goal, int timeOut_ms)
{
    TakeshiManip::startTorsoGoTo(goal);
    TakeshiManip::_isTrGoalReached = false;
    return TakeshiManip::waitForTorsoGoalReached(timeOut_ms);
}

void TakeshiManip::startTorsoGoTo(float goal)
{
    std_msgs::Float32 msg;
    msg.data=goal;
    cout << "\033[1;32m     TakeshiManip.->Start torso go to: " << goal <<"\033[0m" << endl;
    TakeshiManip::pubTrGoToPose.publish(msg);
}

bool TakeshiManip::waitForTorsoGoalReached(int timeOut_ms)
{
    int attempts = timeOut_ms / 100;
    ros::Rate loop(10);
    TakeshiManip::_stopReceived = false;
    TakeshiManip::_isTrGoalReached = false;
    while(ros::ok() && !TakeshiManip::_isTrGoalReached && !TakeshiManip::_stopReceived && attempts-- >= 0)
    {
        ros::spinOnce();
        loop.sleep();
    }
    TakeshiManip::_stopReceived = false; //This flag is set True in the subscriber callback
    cout << "\033[1;32m     TakeshiManip.->Wait for torso goal reached: " << _isTrGoalReached <<"\033[0m" << endl;
    return TakeshiManip::_isTrGoalReached;
}



bool TakeshiManip::armGoToGraspDrawer(int timeOut_ms){
  std::vector<float> articular;
  articular.push_back(-1.5707);
  articular.push_back(0.0);
  articular.push_back(-1.5707);
  articular.push_back(-1.5707);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGoToNavigation(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(0.0);
  articular.push_back(-1.5707);
  articular.push_back(-1.5707);
  articular.push_back(0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGoToGraspFridge(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(-0.5);
  articular.push_back(0.0);
  articular.push_back(-1.1);
  articular.push_back(0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGoToOpenFridge(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(-1.5);
  articular.push_back(-1.5);
  articular.push_back(-1.5);
  articular.push_back(0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGoToOpenFridge2(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(-1.5);
  articular.push_back(-1.5);
  articular.push_back(-1.7);
  articular.push_back(0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGoToAxiSZ(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(0.0);
  articular.push_back(0.0);
  articular.push_back(0.0);
  articular.push_back(0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGoToAxiSX(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(-1.5707);
  articular.push_back(-1.5707);
  articular.push_back(0.0);
  articular.push_back(0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::armGoToNavigation()
{
  std::vector<float> articular;
  articular.push_back(0.0);
  articular.push_back(-1.5707);
  articular.push_back(-1.5707);
  articular.push_back(0.0);
  TakeshiManip::startArmGoToArticular(articular);
  return true;
}

bool TakeshiManip::armDeliverBag()
{
  std::vector<float> articular;
  articular.push_back( -1.2);
  articular.push_back(  0.0);
  articular.push_back( -1.7);
  articular.push_back( 1.5);
  TakeshiManip::startArmGoToArticular(articular);
  return true;
}

bool TakeshiManip::armGoToFindPerson()
{
  std::vector<float> articular;
  articular.push_back(-2.8);
  articular.push_back(0.0);
  articular.push_back(0.5);
  articular.push_back(0.0);
  TakeshiManip::startArmGoToArticular(articular);
  return true;
}

bool TakeshiManip::armGoToFindPersonHelp()
{
  std::vector<float> articular;
  articular.push_back(-0.4);
  articular.push_back(-1.5);
  articular.push_back(-1.5);
  articular.push_back(0.0);
  TakeshiManip::startArmGoToArticular(articular);
  return true;
}


bool TakeshiManip::waitForArmGoToOpenDoor(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(-1.5);
  articular.push_back(-1.5);
  articular.push_back(1.5);
  articular.push_back( 0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGoToCloseFridge(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(-0.8);
  articular.push_back(1.5);
  articular.push_back(-1.0);
  articular.push_back( 2.4);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGraspFloor(int timeOut_ms, float articular3)
{
  std::vector<float> articular;
  articular.push_back(-1.9);
  articular.push_back( 0.0);
  articular.push_back(-1.0);
  articular.push_back(articular3);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::waitForArmGoToColorBin(int timeOut_ms)
{
  std::vector<float> articular;
  articular.push_back(-1.8);
  articular.push_back( 0.0);
  articular.push_back(-0.9);
  articular.push_back( 0.0);
  return TakeshiManip::armGoToArticular(articular, timeOut_ms);
}

bool TakeshiManip::isHdGoalReached()
{
  return TakeshiManip::_isHdGoalReached;
}


bool TakeshiManip::isArmGoalReached()
{
  return TakeshiManip::_isArmGoalReached;
}

bool TakeshiManip::isTorsoGoalReached()
{
  return TakeshiManip::_isTrGoalReached;
}
  

void TakeshiManip::closeGripper(float torque)
{
  std_msgs::Float32 msg;
  msg.data = torque;
  cout << "\033[1;32m     TakeshiManip.->Close gripper: " << torque << "\033[0m" << endl;
  TakeshiManip::pubArmCloseGripper.publish(msg);
  return;
}

void TakeshiManip::openGripper(float pos)
{
  std_msgs::Float32 msg;
  msg.data = pos;
  cout << "\033[1;32m     TakeshiManip.->Open gripper: " << pos << "\033[0m" << endl;
  TakeshiManip::pubArmOpenGripper.publish(msg);
  return;
}


bool TakeshiManip::hdGoTo(float pan, float tilt, int timeOut_ms)
{
    TakeshiManip::startHdGoTo(pan, tilt);
    return TakeshiManip::waitForHdGoalReached(timeOut_ms);
}

void TakeshiManip::startHdGoTo(float pan, float tilt)
{
	cout << "\033[1;32m     TakeshiManip.->Start Head go to   pan: " << pan << " tilt: " << tilt << "\033[0m" << endl;
    std_msgs::Float32MultiArray msg;
    msg.data.push_back(pan);
    msg.data.push_back(tilt);
    TakeshiManip::pubHdGoToAngles.publish(msg);
}

bool TakeshiManip::waitForHdGoalReached(int timeOut_ms)
{
    int attempts = timeOut_ms / 100;
    ros::Rate loop(10);
    TakeshiManip::_stopReceived = false;
    TakeshiManip::_isHdGoalReached = false;
    while(ros::ok() && !TakeshiManip::_isHdGoalReached && !TakeshiManip::_stopReceived && attempts-- >= 0)
    {
        ros::spinOnce();
        loop.sleep();
    }
    TakeshiManip::_stopReceived = false; //This flag is set True in the subscriber callback
    cout << "\033[1;32m     TakeshiManip.->Wait for head goal reached: " << _isHdGoalReached <<"\033[0m" << endl;
    return TakeshiManip::_isHdGoalReached;
}


bool TakeshiManip::inverseKinematicsGeometric(std::vector<float>& cartesian, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction)
{
    cout << "\033[1;32m     TakeshiManip.->Calling service for inverse kinematics...\033[0m" << endl;
    manip_msgs::InverseKinematicsFloatArray srv;
    srv.request.cartesian_pose.data = cartesian;
    bool success = TakeshiManip::cltIKFloatArray.call(srv);
    articular       = srv.response.articular_pose.data;
    base_correction = srv.response.base_correction;
    torso           = srv.response.torso_pose.data;
    return success;
}

bool  TakeshiManip::isTheObjectTaken(bool verify){
    ros::Rate loop(10);
    float torque=0;

    if(!verify)
      return true;

    for(int i=0; i<10; i++){
       torque+=TakeshiManip::_force_data.y;
       ros::spinOnce();
       loop.sleep();
    }


    torque/=10;
    if(torque < -0.38){
      cout << "\033[1;32m     TakeshiManip.->Is the object taken?: True " <<torque <<"\033[0m" << endl;
      return true;
      }

    else{
      cout << "\033[1;32m     TakeshiManip.->Is the object taken?: False " <<torque << "\033[0m" << endl;
      return false;
    }
}

bool  TakeshiManip::isTheHandPressed(){
    ros::Rate loop(10);

    if(TakeshiManip::forceX>15.0){
      cout << "\033[1;32m     TakeshiManip.->Got force of: " << TakeshiManip::forceX <<"\033[0m" << endl;
      return true;
    }

    else{
      cout << "\033[1;32m     TakeshiManip.->Got force of: " << TakeshiManip::forceX <<"\033[0m" << endl;
      return false;
    }
}

void TakeshiManip::getCurrentForce(geometry_msgs::Vector3& force_data){
    force_data.x=0;
    force_data.y=0;
    force_data.z=0;

    for(int i=0; i<10; i++){
      ros::spinOnce();
      force_data.x+=TakeshiManip::_force_data.x;
      force_data.y+=TakeshiManip::_force_data.y;
      force_data.z+=TakeshiManip::_force_data.z;
    }
    force_data.x/=10;
    force_data.y/=10;
    force_data.z/=10;
    cout << "force_data " << force_data <<endl;
}

void TakeshiManip::wristWrenchCallback(const geometry_msgs::WrenchStamped wr)
{
        TakeshiManip::forceX=wr.wrench.force.x;
}

double TakeshiManip::computeWeight(geometry_msgs::Vector3 pre_data, geometry_msgs::Vector3 post_data) {
  // Calculate square sum of difference
  double force_difference = sqrt (pow(post_data.x - pre_data.x, 2) + pow(post_data.y - pre_data.y, 2) + pow(post_data.z - pre_data.z, 2));
  double weight = force_difference / 9.81 * 1000;

  return weight;
}

void TakeshiManip::callbackWristWrench(const geometry_msgs::WrenchStamped::ConstPtr& msg){
    TakeshiManip::_force_data=msg->wrench.force;   
}
//
//Callbacks for catching goal-reached signals
//
void TakeshiManip::callbackRobotStop(const std_msgs::Empty::ConstPtr& msg)
{
    TakeshiManip::_stopReceived = true;
}

void TakeshiManip::callbackTrGoalReached(const std_msgs::Bool::ConstPtr& msg)
{
    TakeshiManip::_isTrGoalReached = msg->data;
}

void TakeshiManip::callbackHdGoalReached(const std_msgs::Bool::ConstPtr& msg)
{
    TakeshiManip::_isHdGoalReached = msg->data;
}

void TakeshiManip::callbackArmGoalReached(const std_msgs::Bool::ConstPtr& msg)
{
    TakeshiManip::_isArmGoalReached = msg->data;
}

void TakeshiManip::callbackTorsoCurrentPos(const std_msgs::Float32::ConstPtr& msg)
{
  TakeshiManip::_torsoCurrentPos = msg->data;
}
