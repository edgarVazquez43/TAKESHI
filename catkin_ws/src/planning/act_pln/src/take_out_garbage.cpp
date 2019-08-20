/////////////////////////////////////////
/////*   By - Edd-II (Support)     *//
#include <iostream>
#include "ros/ros.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiVision.h"

#include "std_msgs/Bool.h"
#include "string"

#define SM_INIT_STATE           00
#define SM_GOTO_BIN_1           05
#define SM_GOTO_BIN_2           10
#define SM_GOTO_TRASH_ZONE      15
#define SM_GRASP_TRASH_BAG      20
#define SM_ASK_FOR_BAG          22
#define SM_PLACE_TRASH_BAG      25
#define SM_TAKE_OUT_LID         35
#define SM_FINAL_STATE          100

bool isFirstBag;
bool tryGraspBag_1;
bool tryGraspBag_2;
bool success;
bool fail;

int  next_state;
int  attempt;


const string bin1_location="trash_bin_1";
const string bin2_location="trash_bin_2";
const string trash_location="trash_zone";

std::stringstream takeshi_say;


geometry_msgs::Vector3 pre_force, post_force;
double weight;

int main(int argc, char** argv)
{
  std::cout << "------------ TEST  ---------" << std::endl;
  ros::init(argc, argv, "act_pln_take_out_garbage");
  ros::NodeHandle n;

  TakeshiHRI::setNodeHandle(&n);
  TakeshiTasks::setNodeHandle(&n);
  TakeshiManip::setNodeHandle(&n);
  TakeshiVision::setNodeHandle(&n);

  ros::Rate loop(30);

  success            = false;
  fail               = false;
  tryGraspBag_1      = true;
  tryGraspBag_2      = true;
  isFirstBag         = true;

  attempt            = 1; 
  next_state         = SM_INIT_STATE;

 
  while( ros::ok() && !success)
  {
    switch(next_state)
    {
    case SM_INIT_STATE:
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "        CASE:  INIT-CASE" << std::endl << std::endl;
      TakeshiHRI::waitAfterSay("I am ready to take out the garbage", 2000);
      ros::Duration(2.0).sleep();
      TakeshiNavigation::moveDist(2.0, 6000);
      ros::Duration(3.0).sleep();
      next_state = SM_GOTO_BIN_1;
      break;

    case SM_GOTO_BIN_1:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  GO TO BIN 1" << std::endl << std::endl;

      // Is important set the orientation of location, to robot be towards table
      TakeshiHRI::say("I am going to trash bin, one.");
      if(!TakeshiNavigation::getClose( bin1_location, 25000))
      	if(!TakeshiNavigation::getClose( bin1_location, 25000) )
      	  TakeshiNavigation::getClose( bin1_location, 25000);

      if(attempt == 1)
      {
	attempt++;
	if(!tryGraspBag_1)
	  {
	    next_state = SM_ASK_FOR_BAG;
	    break;
	  }
	else
	  {
	    next_state = SM_GRASP_TRASH_BAG;
	    break;
	  }
      }
      else
      {
	if(!tryGraspBag_2)
	  {
	    next_state = SM_ASK_FOR_BAG;
	    break;
	  }
	else
	  {
	    next_state = SM_GRASP_TRASH_BAG;
	    break;
	  }
      }

    case SM_TAKE_OUT_LID:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  TAKE OUT LID" << std::endl << std::endl;

      // Is important set the orientation of location, to robot be towards table
      TakeshiHRI::say("I am going to take out the trash bin lid...");
      TakeshiManip::openGripper(0.5);
      TakeshiNavigation::moveDist(0.15, 3000);
      ros::Duration(1.0).sleep();
      TakeshiNavigation::moveDistAngle(0.0, -0.2, 3000);
      TakeshiManip::torsoGoTo(0.42, 3000);
      ros::Duration(5.0).sleep();
      TakeshiManip::armGoToArticular(-1.4, 0.0, -1.5707, 0.0, 2000);
      TakeshiManip::torsoGoTo(0.33, 3000);
      ros::Duration(5.0).sleep();
      TakeshiManip::armGoToArticular(-1.4, 0.0, -1.5707, 1.5707, 2000);
      ros::Duration(5.0).sleep();
      TakeshiManip::armGoToArticular(-1.4, 0.0, -1.5707, -1.5707, 2000);
      ros::Duration(5.0).sleep();

      TakeshiManip::closeGripper(0.5);
      ros::Duration(5.0).sleep();

      TakeshiManip::torsoGoTo(0.42, 2000);
      ros::Duration(5.0).sleep();

      TakeshiNavigation::moveLateral(0.3, 2000);
      ros::Duration(5.0).sleep();

      TakeshiManip::armGoToArticular(-1.5707, 0.0, -1.5707, 0.0, 2000);
      TakeshiManip::torsoGoTo(0.0, 3000);
      ros::Duration(5.0).sleep();
      TakeshiManip::openGripper(0.5);
      ros::Duration(5.0).sleep();

      TakeshiManip::torsoGoTo(0.25, 3000);
      TakeshiNavigation::moveLateral(-0.3, 3000);
      ros::Duration(5.0).sleep();
      
      next_state = SM_GRASP_TRASH_BAG;
      break;

    case SM_ASK_FOR_BAG:
      
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  ASK FOR BAG" << std::endl << std::endl;
      TakeshiHRI::waitAfterSay("I am looking for the trash bin...", 2000);

      TakeshiManip::hdGoTo(0.0, -0.4, 2000);
      ros::Duration(5.0).sleep();
      
      TakeshiHRI::waitAfterSay("I am so sorry... I can not see the trash bag", 2000);
      TakeshiManip::hdGoTo(0.0, 0.0, 2000);
      ros::Duration(2.0).sleep();
      TakeshiNavigation::startMoveDistAngle(0.0, 2.1415);
      TakeshiHRI::waitAfterSay("Human, can you put the bag in my hand...", 2000);
      ros::Duration(1.0).sleep();
      TakeshiHRI::waitAfterSay("Please wait...", 2000);
      
      ros::Duration(1.0).sleep();
      TakeshiManip::armGoToArticular(-0.8, 0.0, -0.7, 0.0, 3000);
      TakeshiManip::openGripper(0.5);
      ros::Duration(5.0).sleep();
      TakeshiHRI::waitAfterSay("Human, can you put the bag in my hand...", 2000);
      ros::Duration(2.0).sleep();
      TakeshiHRI::waitAfterSay("I am closing my gripper...", 2000);
      TakeshiManip::closeGripper(0.5);
	    
      ros::Duration(2.0).sleep();
      TakeshiHRI::waitAfterSay("Thank you...", 2000);

      
      next_state = SM_GOTO_TRASH_ZONE;
      break;

    case SM_GRASP_TRASH_BAG:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  GRASP TRASH BAG" << std::endl << std::endl;
      TakeshiHRI::waitAfterSay("I am looking for the trash bin...", 2000);
      TakeshiManip::getCurrentForce(pre_force);
      ros::Duration(2.0).sleep();
      TakeshiHRI::waitAfterSay("Human, can you take ot the trash bin lid...", 2000);
      ros::Duration(4.0).sleep();
      ros::spinOnce();

      TakeshiManip::hdGoTo(0.0, -0.4, 2000);
      ros::Duration(2.0).sleep();
      TakeshiManip::hdGoTo(0.0, -0.4, 2000);
      ros::Duration(2.0).sleep();
      ros::spinOnce();


      // Insert manipulation trash bag TASK HERE:
      // ----->
      TakeshiHRI::waitAfterSay("I am going to grasp the trash bag... ", 2000);
      TakeshiNavigation::moveDistAngle(0.0, -0.30, 2000);
      TakeshiNavigation::moveDistAngle(0.1, 0.0, 2000);
      TakeshiManip::openGripper(0.0);
      ros::Duration(2.0).sleep();
      ros::spinOnce();
	    
      TakeshiManip::torsoGoTo(0.45, 2000);
      TakeshiManip::armGoToArticular(-1.9707, 0.0, -1.1707, 0.0, 2000);
      TakeshiNavigation::moveDistAngle(0.1, 0.0, 2000);
      TakeshiManip::openGripper(1.0);
      ros::Duration(2.0).sleep();

      TakeshiNavigation::moveDistAngle(0.1, 0.0, 2000);
      ros::Duration(2.0).sleep();
      ros::spinOnce();
      
      TakeshiManip::torsoGoTo(0.30, 2000);
      ros::Duration(2.0).sleep();
      TakeshiManip::closeGripper(0.5);
      ros::Duration(1.0).sleep();

      TakeshiManip::torsoGoTo(0.65, 2000);
      ros::Duration(3.0).sleep();
      TakeshiManip::navigationPose(2000);
      ros::Duration(2.0).sleep();


      TakeshiManip::getCurrentForce(post_force);
      weight=TakeshiManip::computeWeight(pre_force,post_force);
      std::cout << "Weight: " << weight << std::endl;
      if(weight > 90){
      	TakeshiHRI::say("I took the trash bag"); 
      	ros::Duration(2.0).sleep();
      }
      else
      {
      	std::cout << "Can not grasp object: force verify" << std::endl;
      	next_state = SM_ASK_FOR_BAG;
      	break;
      }
      
      next_state = SM_GOTO_TRASH_ZONE;
      break;

   case SM_GOTO_TRASH_ZONE:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  GO TO TRASH ZONE" << std::endl << std::endl;

      TakeshiHRI::say("I am going to trash zone.");
      if(!TakeshiNavigation::getClose( trash_location, 25000))
      	if(!TakeshiNavigation::getClose( trash_location, 25000) )
      	  TakeshiNavigation::getClose( trash_location, 25000);
      next_state = SM_PLACE_TRASH_BAG;
      break;

    case SM_PLACE_TRASH_BAG:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  PLACE TRASH BAG" << std::endl << std::endl;
      TakeshiHRI::waitAfterSay("I am going to place the bag", 2000);

      // Insert place trash bag task HERE:
      // ---->
      TakeshiManip::armGoToArticular(-1.4, 0.0, -0.5, 0.0, 3000);
      ros::Duration(2.0).sleep();
      TakeshiManip::openGripper(0.5);
      TakeshiManip::navigationPose(3000);

      if(isFirstBag)
      {
	TakeshiHRI::waitAfterSay("The first garbage bag has been placed in trash zone...", 2000);
	isFirstBag = false;
	next_state = SM_GOTO_BIN_2;
      }
      else
      {
	TakeshiHRI::waitAfterSay("Other garbage bag has been placed in the trash zone...", 2000);
	next_state = SM_FINAL_STATE;
      }
      
      break;

    case SM_GOTO_BIN_2:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  GO TO BIN 2" << std::endl << std::endl;

      // Is important set the orientation of location, to robot be towards table
      TakeshiHRI::say("I am going to trash bin, two.");
      if(!TakeshiNavigation::getClose( bin2_location, 25000))
      	if(!TakeshiNavigation::getClose( bin2_location, 25000) )
      	  TakeshiNavigation::getClose( bin2_location, 25000);
      next_state = SM_GRASP_TRASH_BAG;
      break;


    case SM_FINAL_STATE:
      std::cout << "----------------------------------------------" << std::endl;
      std::cout << "        CASE:  FINAL-CASE" << std::endl << std::endl;
      TakeshiHRI::say("The apartment is clean now... Enjoy it.");
      success = true;
      break;
    }

  }

  return 0;
}
