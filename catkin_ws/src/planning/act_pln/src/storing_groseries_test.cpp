/////////////////////////////////////////
/////*   By - Edd-II (Support)     *//
#include <iostream>
#include "ros/ros.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiVision.h"
//#include "hri_msgs/RecognitionResult.h"
#include "vision_msgs/Cube.h"


#include "std_msgs/Bool.h"
#include "string"

#define SM_INIT_STATE           00
#define SM_WAIT_START_SIGNAL    05
#define SM_NAVIGATE_TABLE       10
#define SM_RECO_OBJ_TABLE       20
#define SM_PDF_GEN              25
#define SM_GRASP_OBJ            30
#define SM_ALIGN_TABLE          35
#define SM_NAVIGATE_SHELF       40
#define SM_RECO_OBJ_SHELF_UP    50
#define SM_RECO_OBJ_SHELF_MDDL  60
#define SM_RECO_OBJ_SHELF_DOWN  70
#define SM_PLACE_OBJ_SHELF      80
#define SM_FINAL_STATE          100

bool success;
bool fail;
bool saveFiles;
bool use_yolo;
bool lateral_grasp;

int  next_state;
int  attemp_num;
int  attemp_find_line;
int  attemp_find_object;


const string kitchen_table_location="kitchen_table";
const string shelf_location="kitchen_cabinet";
bool openDoorByYourself;



std::vector<vision_msgs::VisionObject> recoObjList;
std::vector<vision_msgs::VisionObject> recoObj_shelf;
std::vector<std::string> classes;

std::vector<float> obj_position;
std::vector<float> articular;


geometry_msgs::Pose pose;
bool leftArm;

// Strings for append to pdf file.
std::string name_test = "storingGroseries_Takeshi_3";
std::string object_category = "";
std::stringstream takeshi_say;


int main(int argc, char** argv)
{
  std::cout << "------------ TEST  ---------" << std::endl;
  ros::init(argc, argv, "act_pln_storing");

  ros::NodeHandle n;

  TakeshiHRI::setNodeHandle(&n);
  TakeshiTasks::setNodeHandle(&n);
  TakeshiManip::setNodeHandle(&n);
  TakeshiVision::setNodeHandle(&n);

  ros::Rate loop(30);

  success            = false;
  fail               = false;
  saveFiles          = true;
  attemp_num         = 0;
  attemp_find_line   = 0;
  attemp_find_object = 0;


  openDoorByYourself = true;
  use_yolo           = true;
  lateral_grasp      = false;

  next_state         = SM_INIT_STATE;
 
  while( ros::ok() && !success)
  {
    switch(next_state)
    {
    case SM_INIT_STATE:
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "        CASE:  INIT-CASE" << std::endl << std::endl;
      TakeshiHRI::waitAfterSay("I am ready for storing groseries test.", 2000);
      ros::Duration(2.0).sleep();
      TakeshiHRI::waitAfterSay("Now I can see that the door is open...", 2000);
      ros::Duration(2.0).sleep();
      TakeshiNavigation::moveDist(2.0, 8000);
      ros::Duration(3.0).sleep();
      if(openDoorByYourself)
	next_state         = SM_NAVIGATE_SHELF;
      else
	next_state         = SM_NAVIGATE_TABLE;
      break;

   case SM_WAIT_START_SIGNAL:
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "        CASE:  SM_WAIT_START_SIGNAL" << std::endl << std::endl;
       while(!TakeshiHRI::initTest() && ros::ok()){
          ros::Duration(0.5).sleep();
          ros::spinOnce();
      }

       next_state = SM_NAVIGATE_TABLE;
       //next_state = SM_RECO_OBJ_TABLE;
      break;

    case SM_NAVIGATE_TABLE:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  NAVIGATE-TABLE" << std::endl << std::endl;

      // Is important set the orientation of location, to robot be towards table
      TakeshiHRI::say("I navigate to the table.");
      if(!TakeshiNavigation::getClose( kitchen_table_location, 50000))
      	if(!TakeshiNavigation::getClose( kitchen_table_location, 50000) )
      	  TakeshiNavigation::getClose( kitchen_table_location, 50000);

      TakeshiNavigation::getClose( kitchen_table_location, 50000);
      next_state = SM_ALIGN_TABLE;
      break;

    case SM_ALIGN_TABLE:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  ALIGN-WITH-TABLE" << std::endl << std::endl;

      if(attemp_find_line < 2)
      {
	attemp_find_line++;
	
	// Aling whit table
	if(!lateral_grasp)
	  {
	    std::cout << "Align front table...." << std::endl;
	    if(!TakeshiTasks::alignWithFrontTable())
	      if(!TakeshiTasks::alignWithFrontTable())
		break;
	  }
	else
	  {
	    std::cout << "Aling lateral table...." << std::endl;
	      if(!TakeshiTasks::alignWithTable())
	      {
		attemp_find_object = 3;
		break;
	      }
	  }
      }
      else
      {
	next_state = SM_RECO_OBJ_TABLE;
	break;
      }
      

        
      next_state = SM_RECO_OBJ_TABLE;
      break;

   case SM_RECO_OBJ_TABLE:
     std::cout << "---------------------------------------------" << std::endl;
     std::cout << "        CASE:  RECO-OBJ     " << std::endl << std::endl;
     // // Find objects
     if(!lateral_grasp)
     {
       TakeshiManip::hdGoTo(0.0, 0.0, 2000);
       TakeshiManip::torsoGoTo(0.15, 2000);
       TakeshiManip::findObjectsPose(true);  //true is for objects in front
       TakeshiManip::hdGoTo(0.0, -0.4, 2000);
     }
    
     ros::Duration(1.0).sleep();
     
     if(attemp_find_object < 3)
     {
       attemp_find_object++;
       
       if(use_yolo)
	 {
	   std::cout << "   -> Takeshi is detecting objects whit Yolo.......   " << std::endl;
	   if(!TakeshiVision::detectAllYoloObjects(recoObjList, 2000))
	     if(!TakeshiVision::detectAllYoloObjects(recoObjList, 2000))
	       break;
	 }
       else
	 {
	   std::cout << "Takeshi is detecting objects whit Yisus...   " << std::endl;
	   if(!TakeshiVision::detectAllObjects(recoObjList, saveFiles))
	     if(!TakeshiVision::detectAllObjects(recoObjList, saveFiles))
	       break;
	 }
     }
     else
     {
        TakeshiNavigation::getClose( kitchen_table_location, 50000);  
       next_state = SM_NAVIGATE_SHELF;
       break;
     }
     
     // justina_say.str(std::string());
     // justina_say << "I found " << recoObjList.size() << " objects";
     // std::cout << "I found " << recoObjList.size() << " objects" << std::endl;
     // TakeshiHRI::say( justina_say.str() );

      obj_position.resize(3);
      for(int i = 0; i < recoObjList.size(); i++)
      {
	std::cout << "  -> Obj[" << i << "]: " << recoObjList[i].id
		  << " - category: " << recoObjList[i].category << std::endl;
      }

      
      //RecoObj[0] is the nearest objetc by euclidean distance
      obj_position[0] = recoObjList[0].pose.position.x;
      obj_position[1] = recoObjList[0].pose.position.y;
      obj_position[2] = recoObjList[0].pose.position.z;
      object_category = recoObjList[0].category;

      if(!use_yolo)
	obj_position[0] = obj_position[0] + 0.02;
      
      next_state = SM_GRASP_OBJ;
      break;

    case SM_PDF_GEN:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  PDF-GEN     " << std::endl << std::endl;
      //JustinaTools::pdfImageStop(name_test, "/home/$USER/objs/");
      next_state = SM_GRASP_OBJ;
      break;

   case SM_GRASP_OBJ:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  GRASP_OBJ" << std::endl << std::endl;
      std::cout << "Object coordinates:  " << obj_position[0] << "  " << obj_position[1] << "  " << obj_position[2] << std::endl;

      //Fuction only to speak
      takeshi_say.str(std::string());
      TakeshiHRI::waitAfterSay("I am grasping the...", 2000);
      takeshi_say << recoObjList[0].id;
      TakeshiHRI::waitAfterSay(takeshi_say.str(), 2000);


      takeshi_say.str(std::string());
      TakeshiHRI::waitAfterSay("This  belong  to  category...", 2000);
      takeshi_say << recoObjList[0].category;
      TakeshiHRI::waitAfterSay(takeshi_say.str(), 2000);


      
      TakeshiManip::hdGoTo(0.0, 0.0, 1000);
      if(!lateral_grasp)
      {
	if(!TakeshiTasks::graspObject(obj_position[0], obj_position[1], obj_position[2], false))
	  if(!TakeshiTasks::graspObject(obj_position[0], obj_position[1], obj_position[2], false))
	{
	  next_state = SM_RECO_OBJ_TABLE;
	  break;
	}
      }
      else
      {
	if(!TakeshiTasks::graspObjectLateral(obj_position[0], obj_position[1], obj_position[2], false))
	  if(!TakeshiTasks::graspObjectLateral(obj_position[0], obj_position[1], obj_position[2], false))
	{
	  next_state = SM_RECO_OBJ_TABLE;
	  break;
	}
      }

      next_state = SM_NAVIGATE_SHELF;
      break;


    case SM_NAVIGATE_SHELF:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  NAVIGATE_SHELF" << std::endl << std::endl;
      if( !TakeshiNavigation::getClose(shelf_location, 50000) )
      	if( !TakeshiNavigation::getClose(shelf_location, 50000) )
      	  TakeshiNavigation::getClose(shelf_location, 50000);

      if(openDoorByYourself){
	if(attemp_num < 1)
	  {
	    TakeshiHRI::waitAfterSay("I am going to open the Shelf door...", 4000);
	    TakeshiTasks::openShelfDoor();
	    attemp_num++;
	    next_state         = SM_NAVIGATE_TABLE;
	    break;
	  }
      }
      else
	{
	  if(attemp_num < 1)
	    TakeshiHRI::waitAfterSay("Human can you open the door, please.", 4000);
	}

	attemp_num++;
	next_state = SM_PLACE_OBJ_SHELF;
	break;


    case SM_RECO_OBJ_SHELF_UP:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  RECO-OBJ-SHELF-UP   " << std::endl << std::endl;

      // Aling whit table
      TakeshiTasks::alignWithFrontTable(0.60);

      // Find objects
      // TakeshiManip::hdGoTo(0.0, 0.4, 6000);
      ros::Duration(3.0).sleep();
      
      TakeshiManip::torsoGoTo(0.2, 2000);
      ros::Duration(2.5).sleep();
      TakeshiHRI::waitAfterSay("I am searching categories into the shelf...", 1000);
      TakeshiVision::detectAllYoloObjects(recoObjList, 2000);
      TakeshiHRI::waitAfterSay("I can see the categories...", 1000);

      for(int i; i < recoObjList.size(); i++)
      {
	takeshi_say.str(std::string());
	takeshi_say << recoObjList[i].category;
	TakeshiHRI::waitAfterSay(takeshi_say.str(), 2000);
      }
      

      next_state = SM_PLACE_OBJ_SHELF;
      break;


    case SM_RECO_OBJ_SHELF_DOWN:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  RECO-OBJ-SHELF-DOWN   " << std::endl << std::endl;

      TakeshiManip::torsoGoTo(0.2, 2000);
      ros::Duration(2.5).sleep();
      TakeshiHRI::waitAfterSay("I am searching categories into the shelf...", 1000);
      TakeshiVision::detectAllObjects(recoObjList, saveFiles);
      TakeshiHRI::waitAfterSay("I can see the categories...", 1000);

      for(int i; i < recoObjList.size(); i++)
      {
	takeshi_say.str(std::string());
	takeshi_say << recoObjList[i].category;
	TakeshiHRI::waitAfterSay(takeshi_say.str(), 2000);
      }
      

      next_state = SM_RECO_OBJ_TABLE;
      break;


    case SM_PLACE_OBJ_SHELF:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  PLACE-OBJ_SHELF   " << std::endl << std::endl;
      
      TakeshiHRI::waitAfterSay("I am going to place object into the shelf.", 100);
      TakeshiTasks::placeObjectInShelfByCategory(object_category);

      if(attemp_num < 5)
	       next_state = SM_NAVIGATE_TABLE;
      else
	       next_state = -1;
      attemp_num++;
      attemp_find_line   = 0;
      attemp_find_object = 0;
      break;

    default:
      std::cout << "----------------------------------------------" << std::endl;
      std::cout << "        CASE:  FINAL-CASE" << std::endl << std::endl;
      TakeshiHRI::say("I finish my demostration. thank you for your attention...");
      success = true;
      break;
    }

  }

  return 0;
}
