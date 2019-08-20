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
#include "std_msgs/Bool.h"
#include "string"

#define SM_INIT_STATE   00
#define SM_PANORAMIC    10


bool success;
int  next_state;

vision_msgs::VisionFaceObjects panoramicFaces;
sensor_msgs::Image     image;


int main(int argc, char** argv)
{
  std::cout << "------------ TEST  ---------" << std::endl;
  ros::init(argc, argv, "act_pln");
  
  ros::NodeHandle n;
  JustinaHardware::setNodeHandle(&n);
  JustinaHRI::setNodeHandle(&n);
  JustinaManip::setNodeHandle(&n);
  JustinaNavigation::setNodeHandle(&n);
  JustinaTools::setNodeHandle(&n);
  JustinaVision::setNodeHandle(&n);
  JustinaTasks::setNodeHandle(&n);
  JustinaKnowledge::setNodeHandle(&n);

  ros::Rate loop(30);

  success    = false;
  next_state = SM_INIT_STATE;
  
  while( ros::ok() && !success)
  {
    switch(next_state)
    {
    case SM_INIT_STATE:
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "        CASE:  INIT-CASE" << std::endl << std::endl;

      JustinaHRI::say("I am doing a panoramic photo.");
      ros::Duration(2.5).sleep();

      next_state = SM_PANORAMIC;
      break;
      
    case SM_PANORAMIC:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  PANORAMIC-TEST" << std::endl << std::endl;
        
      JustinaTasks::getPanoramic(-0.2, -0.3, -0.5, -0.3, 0.3, 0.3, image, 30000);
      panoramicFaces = JustinaVision::getRecogFromPano(image);

      next_state = -1;
      break;

    default:
      std::cout << "----------------------------------------------" << std::endl;
      std::cout << "        CASE:  FINAL-CASE" << std::endl << std::endl;
      success = true;
      break;
    }
    
  }

  return 0;
}









