/////////////////////////////////////////
/////*   By - Edd-II (Estupor)     *//
#include <iostream>
#include "ros/ros.h"
#include "justina_tools/JustinaHardware.h"
#include "justina_tools/JustinaHRI.h"
#include "justina_tools/JustinaManip.h"
#include "justina_tools/JustinaNavigation.h"
#include "justina_tools/JustinaTools.h"
#include "justina_tools/JustinaVision.h"
#include "justina_tools/JustinaTasks.h"
#include "justina_tools/JustinaKnowledge.h"

#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiVision.h"
#include "std_msgs/Bool.h"
#include "string"

#define SM_INIT_STATE           00
#define SM_NAVIGATE_TABLE       10
#define SM_RECO_OBJ_TABLE       20
#define SM_GRASP_OBJ            30
#define SM_NAVIGATE_WD          40
#define SM_PLACE_OBJ_WD   	50
#define SM_FINAL_STATE          100

bool success;
bool fail;
bool saveFiles;
bool useFeedback;
bool isFirstAttemp;
int  next_state;

// vision_msgs::VisionFlattenedObjectList recoObjList;
std::vector<vision_msgs::VisionObject> recoObjList;
std::vector<float> obj_position;



// Strings for append to pdf file.
std::string name_test = "P&G_Test_Takeshi_3";
std::string object_category;
std::stringstream justina_say;





int main(int argc, char** argv)
{
  std::cout << "------------ TEST  ---------" << std::endl;
  ros::init(argc, argv, "act_pln_pg_test");

  ros::NodeHandle n;
  JustinaHardware::setNodeHandle(&n);
  JustinaHRI::setNodeHandle(&n);
  JustinaManip::setNodeHandle(&n);
  JustinaNavigation::setNodeHandle(&n);
  JustinaTools::setNodeHandle(&n);
  JustinaVision::setNodeHandle(&n);
  JustinaTasks::setNodeHandle(&n);

  TakeshiTasks::setNodeHandle(&n);

  JustinaKnowledge::setNodeHandle(&n);

  ros::Rate loop(30);

  success    = false;
  fail       = false;
  useFeedback= true;
  saveFiles  = true;
  isFirstAttemp = true;

  JustinaTools::pdfStart(name_test);
  JustinaTools::pdfAppend(name_test, "");
  JustinaTools::pdfAppend(name_test, "Attempt:  1");
  JustinaTools::pdfAppend(name_test, "");
  JustinaTools::pdfAppend(name_test, "");


  next_state = SM_INIT_STATE;

  while( ros::ok() && !success)
  {
    switch(next_state)
    {
    case SM_INIT_STATE:
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "        CASE:  INIT-CASE" << std::endl << std::endl;
      JustinaHRI::waitAfterSay("I am ready for Clean Up the Table test.", 3000);
      ros::Duration(5.0).sleep();
      JustinaHRI::waitAfterSay("Now I can see that the door is open...", 3000);
      ros::Duration(1.0).sleep();
      JustinaNavigation::moveDist(1.5, 6000);
      
      next_state = SM_NAVIGATE_TABLE;
      break;

    case SM_NAVIGATE_TABLE:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  NAVIGATE-TABLE" << std::endl << std::endl;

      JustinaManip::armGoToNavigation();
      JustinaHRI::say("I navigate to kitchen table.");
      if(!JustinaNavigation::getClose("dinning_table", 50000))
	if(!JustinaNavigation::getClose("dinning_table", 50000) )
	  JustinaNavigation::getClose("dinning_table", 50000);

      ros::Duration(2.0).sleep();
      next_state = SM_RECO_OBJ_TABLE;
      break;


   case SM_RECO_OBJ_TABLE:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  RECO-OBJ     " << std::endl << std::endl;

      JustinaHRI::say("I am searching for cutlery on the table.");
      // Aling whit table
      JustinaTasks::alignWithTable(0.55);

      // Find objects
      JustinaManip::hdGoTo(1.5707, 0.0, 6000);
      JustinaManip::hdGoTo(1.5707, -0.9, 6000);
      ros::Duration(3.0).sleep();

      JustinaHRI::waitAfterSay("I have found tree cutlery... ", 2000);
      JustinaHRI::waitAfterSay("Spon... on my right side", 5000);
      JustinaHRI::waitAfterSay("Fork... on my right side", 5000);
      JustinaHRI::waitAfterSay("Spon... on my right side", 5000);
      // JustinaHRI::waitAfterSay("Spon... on my left side", 5000);
      // JustinaHRI::waitAfterSay("Fork... on my right side", 5000);
      ros::Duration(2.0).sleep();
      JustinaHRI::waitAfterSay("Sorry, I am no able to grasp this kind of objects...", 2000);
      ros::Duration(2.0).sleep();

      
      JustinaHRI::waitAfterSay("Human, I need a help", 2000);
      JustinaHRI::waitAfterSay("Please, put the spones and the fork into the glass...", 2000);
      ros::Duration(6.0).sleep();

      JustinaHRI::waitAfterSay("Thank you human...", 2000);
      ros::Duration(2.0).sleep();
      

      // Call color segmentation
      // JustinaVision::detectFlattenedObjects(recoObjList, saveFiles);
      TakeshiVision::detectAllObjects(recoObjList, false);

      // justina_say.str(std::string());                             //Clear strigStream variable
      // justina_say << "I found " << recoObjList.objectList.size() << " objects";
      // 	  std::cout << "I found " << recoObjList.objectList.size() << " objects" << std::endl;
      // 	  // JustinaHRI::say( justina_say.str() );


      // for(int i = 0; i < recoObjList.objectList.size(); i++)
      // 	{
      // 	  std::cout << "Obj[" << i << "]: " << recoObjList.objectList[i].id << std::endl;
      // 	}

      for(int i = 0; i < recoObjList.size(); i++)
      {
	std::cout << "  -> Obj[" << i << "]: " << recoObjList[i].id
		  << " - category: " << recoObjList[i].category << std::endl;
      }

      obj_position.resize(3);
      // obj_position[0] = recoObjList.objectList[0].center_point.x;
      // obj_position[1] = recoObjList.objectList[0].center_point.y;
      // obj_position[2] = recoObjList.objectList[0].center_point.z;
      

      obj_position[0] = recoObjList[0].pose.position.x;
      obj_position[1] = recoObjList[0].pose.position.y + 0.08;
      obj_position[2] = recoObjList[0].pose.position.z;
      object_category = recoObjList[0].category;

      next_state = SM_GRASP_OBJ;
      break;

   case SM_GRASP_OBJ:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  GRASP_OBJ" << std::endl << std::endl;
      std::cout << "Object coordinates:  "
		<< obj_position[0] << "  "
		<< obj_position[1] << "  "
		<< obj_position[2] << std::endl;
      JustinaManip::hdGoTo(1.5707, 0.0, 6000);
      JustinaManip::hdGoTo(0.0, 0.0, 6000);

      //Fuction only to speak
      justina_say.str(std::string());
      // justina_say << "I am going to grasping... the " << recoObjList.objectList[0].id << " object";
	  std::cout << "I am going to grasping... the " << recoObjList[0].id << " object" << std::endl;
      JustinaHRI::say(justina_say.str() );
      TakeshiTasks::graspObjectLateral(obj_position[0], obj_position[1], obj_position[2], false);
      //add service here
      JustinaNavigation::moveDistAngle(0.0, -3.141592, 4000);
      next_state = SM_NAVIGATE_WD;
      // next_state = SM_RECO_OBJ_TABLE;
      break;

    case SM_NAVIGATE_WD:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  NAVIGATE_SHELF" << std::endl << std::endl;
      JustinaManip::armGoToNavigation();
      JustinaHRI::say("I navigate to the dishwasher");
      if( !JustinaNavigation::getClose("dishwasher_2", 25000) )
	if( !JustinaNavigation::getClose("dishwasher_2", 25000) )
	  JustinaNavigation::getClose("dishwasher_2", 25000);
      JustinaNavigation::getClose("dishwasher_2", 25000);

      if(isFirstAttemp)
      {
	isFirstAttemp = false;
	JustinaHRI::waitAfterSay("Human, could you open the dishwasher, please.", 2000);
	ros::Duration(8.0).sleep();
      }

      // next_state = SM_PLACE_OBJ_SHELF;
      next_state = SM_PLACE_OBJ_WD;
      break;

    case SM_PLACE_OBJ_WD:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  PLACE-OBJ_SHELF   " << std::endl << std::endl;

      JustinaHRI::say("I am goin to place object into the dishwasher. I am align with dishwasher.....");
      JustinaManip::hdGoTo(0.0, -0.6, 2000);
      JustinaNavigation::moveDist(0.1, 3000);

      // JustinaNavigation::moveLateral(0.5, 3000);
      ros::Duration(2.0).sleep();
      JustinaManip::hdGoTo(0.0, 0.0, 2000);
      JustinaNavigation::moveDist(0.1, 3000);
      JustinaManip::torsoGoTo(0.6, 500);
      JustinaNavigation::moveDistAngle(0.0, 0.2, 3000);
      JustinaManip::armGoToArticular(-1.2, 0.0, -0.3, 0.0, 3000);
      ros::Duration(3.0).sleep();
      JustinaNavigation::moveDist(0.10, 100);
      ros::Duration(5.0).sleep();
      JustinaNavigation::moveDist(0.10, 100);
      ros::Duration(5.0).sleep();
      JustinaNavigation::moveDist(0.10, 100);
      ros::Duration(5.0).sleep();
      JustinaManip::torsoGoTo(0.5, 500);
      JustinaManip::armGoToArticular(-1.2, 0.0, -1.8, 0.0, 3000);
      ros::Duration(4.0).sleep();
      JustinaManip::openGripper(1.0);


      JustinaManip::torsoGoTo(0.6, 3000);
      JustinaNavigation::moveLateral(-0.2, 4000);
      JustinaManip::armGoToNavigation();
      JustinaNavigation::moveDist(-0.3, 2000);
      ros::Duration(2.0).sleep();
      

      JustinaNavigation::moveDistAngle(0.0, 3.1415, 4000);

      next_state = SM_NAVIGATE_TABLE;
      break;

    default:
      std::cout << "----------------------------------------------" << std::endl;
      std::cout << "        CASE:  FINAL-CASE" << std::endl << std::endl;
      JustinaHRI::say("I finish the storing groseries test.");
      success = true;
      break;
    }

  }

  return 0;
}
