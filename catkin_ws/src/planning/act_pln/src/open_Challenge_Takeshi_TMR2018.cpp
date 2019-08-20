////////////////////////////////////////////////////////
// Note: this code was commented into CMake file,
// If you are brave enough to edit this code please
// make sure to uncomment this code into CMakeList.txt
///////////////////        EDD-II    ////////////////////

#include <iostream>
#include "ros/ros.h"
#include "hri_msgs/RecognitionResult.h"
#include "justina_tools/JustinaHRI.h"
#include "justina_tools/JustinaHardware.h"
#include "justina_tools/JustinaHRI.h"
#include "justina_tools/JustinaManip.h"
#include "justina_tools/JustinaNavigation.h"
#include "justina_tools/JustinaKnowledge.h"
#include "justina_tools/JustinaTools.h"
#include "justina_tools/JustinaVision.h"
#include "justina_tools/JustinaTasks.h"

#include "std_msgs/Bool.h"
#include "string"
#include <sensor_msgs/LaserScan.h>

using namespace std;

#define SM_INIT               0
#define SM_NAVIGATE_OBSTACLE  10
#define SM_TALK_WITH_HUMAN    20
#define SM_GO_TO_OBSTACLE     30
#define SM_GRASP_OBSTACLE     40
#define SM_GO_TO_KITCHEN      50
#define SM_TRASH_GARBADGE     55
#define SM_GO_TO_DINING_ROOM  57
#define SM_NAVIGATE_MAIL      60
#define SM_ASK_MAIL           65
#define SM_TAKE_MAIL          70
#define SM_KITCHEN_FINAL      80
#define SM_FINAL_STATE        90


int main(int argc, char** argv)
{
  std::cout << "INITIALIZING OPEN CHALLENGE TAKESHI..." << std::endl;
  ros::init(argc, argv, "act_pln");
  ros::NodeHandle n;
  int nextState = SM_INIT;
  bool fail = false;
  bool success = false;
  ros::Rate loop(10);
    
  JustinaHRI::setNodeHandle(&n);
  JustinaTasks::setNodeHandle(&n);
  JustinaTools::setNodeHandle(&n);
  JustinaHardware::setNodeHandle(&n);
  JustinaManip::setNodeHandle(&n);
  JustinaNavigation::setNodeHandle(&n);
  JustinaKnowledge::setNodeHandle(&n);    
  JustinaVision::setNodeHandle(&n);

  std::vector<std::string> validCommands;

  validCommands.push_back("robot start");
  validCommands.push_back("robot yes");
  validCommands.push_back("take the object to the trash container");
  validCommands.push_back("bring me the mail");

  std::stringstream ss;
  std::vector<std::string> tokens;
    
  std::string lastRecoSpeech;
  std::string location="entrance";
   

  while(ros::ok() && !fail && !success)
    {
      switch(nextState)
        {  

	case SM_INIT:
	  std::cout << "State machine: SM_INIT" << std::endl;

	  JustinaHRI::waitAfterSay("I am ready for open challenge", 10000);
	  ros::Duration(4.0).sleep();
	  
	  JustinaHRI::waitAfterSay("I am going to find Alex, I am go to the living room", 2000); 
	  boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
	  location="dinning_room";   
	  nextState = SM_NAVIGATE_OBSTACLE;

	  break;
                
	case SM_NAVIGATE_OBSTACLE:
	  std::cout << "State machine: SM_NAVIGATE_OBSTACLE" << std::endl;

	  JustinaManip::torsoGoTo(0.0, 3000);
	  JustinaManip::armGoToNavigation();
	  if(!JustinaNavigation::getClose(location, 200000))
	    if(!JustinaNavigation::getClose(location, 200000))
	      JustinaNavigation::getClose(location, 200000);

	  JustinaHRI::waitAfterSay("Hello human, i found an object in the corridor and I think it's garbage", 10000);
	  ros::Duration(3.0).sleep();
	  JustinaHRI::waitAfterSay("I think this would be dangerous for you", 10000);
	  ros::Duration(3.0).sleep();
	  JustinaHRI::waitAfterSay("What do you want I do", 10000);
	  ros::Duration(3.0).sleep();

	  boost::this_thread::sleep(boost::posix_time::milliseconds(6000));
               
	  nextState=SM_TALK_WITH_HUMAN;

	case SM_TALK_WITH_HUMAN:
	  std::cout << "State machine: SM_TALK_WITH_HUMAN" << std::endl;
                
	  if(JustinaHRI::waitForSpecificSentence("take the object to the trash container" , 15000)){
	    JustinaHRI::waitAfterSay("Ok, wait a momment human", 10000);
	    location="obstacle_location";
	    nextState = SM_GO_TO_OBSTACLE;                
	  }


	  break;

	case SM_GO_TO_OBSTACLE:    
	  std::cout << "State machine: SM_GO_TO_OBSTACLE" << std::endl;

	  JustinaManip::torsoGoTo(0.0, 3000);
	  JustinaManip::armGoToNavigation();
	  if(!JustinaNavigation::getClose(location, 200000))
	    if(!JustinaNavigation::getClose(location, 200000))
	      JustinaNavigation::getClose(location, 200000);
	  JustinaNavigation::moveLateral(0.2, 3000);

	  nextState=SM_GRASP_OBSTACLE;

	  break;

	case SM_GRASP_OBSTACLE:
	  std::cout << "State machine: SM_GRASP_OBSTACLE" << std::endl;
	  JustinaHRI::waitAfterSay("I am looking for the object", 10000);

	  ros::Duration(3.0).sleep();
	  JustinaManip::hdGoTo(-0.0, -0.5, 4000);
	  ros::Duration(4.0).sleep();
	  JustinaHRI::waitAfterSay("I am updating object coordinates.", 10000);
	  ros::Duration(3.0).sleep();
	  
	  JustinaHRI::waitAfterSay("I think this is the garbage object", 10000);
	  ros::Duration(3.0).sleep();
	  JustinaTasks::graspObjectFromFloor(0.0, 0.0);
	  location="kitchen";
	  nextState=SM_GO_TO_KITCHEN;
            
	  break;

	case SM_GO_TO_KITCHEN:
	  std::cout << "State machine: SM_RETURN_KITCHEN" << std::endl;

	  JustinaManip::torsoGoTo(0.0, 3000);
	  JustinaManip::armGoToNavigation();
	  if(!JustinaNavigation::getClose(location, 200000))
	    if(!JustinaNavigation::getClose(location, 200000))
	      JustinaNavigation::getClose(location, 200000);
	  JustinaHRI::waitAfterSay("I am going to release the garbage", 10000);
	  nextState=SM_TRASH_GARBADGE;                

	  break;

	case SM_TRASH_GARBADGE:
	  std::cout << "State machine: SM_TRASH_GARBADGE" << std::endl;               
	  JustinaManip::armReleaseObject();
	  ros::Duration(2.0).sleep();
	  JustinaManip::openGripper(1.0);
	  boost::this_thread::sleep(boost::posix_time::milliseconds(7000));
	  JustinaManip::armGoToNavigation();    
	  boost::this_thread::sleep(boost::posix_time::milliseconds(7000));
	  JustinaManip::torsoGoTo(0.0, 4000);
	  boost::this_thread::sleep(boost::posix_time::milliseconds(3000));
	  JustinaHRI::waitAfterSay("I release the garbage", 10000);
	  location="dinning_room";
	  nextState=SM_GO_TO_DINING_ROOM;

	  break;   

	case SM_GO_TO_DINING_ROOM:
                
	  std::cout << "State machine: SM_GO_TO_DINING_ROOM" << std::endl;

	  JustinaManip::torsoGoTo(0.0, 3000);
	  JustinaManip::armGoToNavigation();
	  if(!JustinaNavigation::getClose(location, 200000))
	    if(!JustinaNavigation::getClose(location, 200000))
	      JustinaNavigation::getClose(location, 200000);
	  JustinaHRI::waitAfterSay("Do you want me to see for the mail", 10000);
	  ros::Duration(2.0).sleep();
	  nextState=SM_ASK_MAIL;    

	  break;

	case SM_ASK_MAIL:
	  std::cout << "State machine: SM_ASK_MAIL" << std::endl; 

	  if(JustinaHRI::waitForSpecificSentence("bring me the mail" , 15000)){
	    location="exit";
	    nextState = SM_NAVIGATE_MAIL;                
	  }

	  break;

	case SM_NAVIGATE_MAIL:

	  std::cout << "State machine: SM_NAVIGATE_MAIL" << std::endl;

	  JustinaManip::torsoGoTo(0.0, 3000);
	  JustinaManip::armGoToNavigation();
	  if(!JustinaNavigation::getClose(location, 200000))
	    if(!JustinaNavigation::getClose(location, 200000))
	      JustinaNavigation::getClose(location, 200000);
                
	  nextState=SM_TAKE_MAIL;
	  break;

	case SM_TAKE_MAIL:
                
	  std::cout << "State machine: SM_TAKE_MAIL" << std::endl;

	  //JustinaTasks::suctionPaper();
	  JustinaManip::torsoGoTo(0.0, 4000);    
	  JustinaHRI::waitAfterSay("I take the paper", 10000);

	  location="dinning_room";
	  nextState=SM_KITCHEN_FINAL;

	  break;    

	case SM_KITCHEN_FINAL:
	  std::cout << "State machine: SM_KITCHEN_FINAL" << std::endl;

	  JustinaManip::torsoGoTo(0.0, 3000);
	  JustinaManip::armGoToNavigation();
	  if(!JustinaNavigation::getClose(location, 200000))
	    if(!JustinaNavigation::getClose(location, 200000))
	      JustinaNavigation::getClose(location, 200000);
	  JustinaHRI::waitAfterSay("I finish the test", 10000);
	  nextState=SM_FINAL_STATE;

	  break;    


	case SM_FINAL_STATE:
	  std::cout << "State machine: SM_FINAL_STATE" << std::endl;
	  success = true;
	  break;

        }

      ros::spinOnce();
      loop.sleep();
    }



  return 1;
}

