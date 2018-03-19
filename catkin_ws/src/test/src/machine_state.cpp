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
#define SM_SPEECH       10
#define SM_CALCULATE_IK 20
#define SM_MOVE_BASE    30
#define SM_MOVE_ARM     40


bool success;
int  next_state;

float                  torso;
std::vector<float>     cartesian;
std::vector<float>     articular;
geometry_msgs::Pose2D  base_correction;


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

  cartesian.resize(6);
  articular.resize(4);


  cartesian[0] = 0.35;
  cartesian[1] = 0.15;
  cartesian[2] = 0.10;
  cartesian[3] = 0.00;
  cartesian[4] = 1.5707;
  cartesian[5] = 0.00;
  
  
  while( ros::ok() && !success)
  {
    switch(next_state)
    {
    case SM_INIT_STATE:
      std::cout << "--------------------------------------------" << std::endl;
      std::cout << "        CASE:  INIT-CASE" << std::endl << std::endl;
      next_state = SM_SPEECH;
      break;
      
    case SM_SPEECH:
      std::cout << "---------------------------------------------" << std::endl;
      std::cout << "        CASE:  SPEECH-CASE" << std::endl << std::endl;
      JustinaHRI::say("I am ready for initial command.");
      next_state = SM_CALCULATE_IK;
      break;

    case SM_CALCULATE_IK:
      std::cout << "----------------------------------------------" << std::endl;
      std::cout << "        CASE:  CALCULATE INVERSE-KINEMATIC " << std::endl << std::endl;
      JustinaManip::inverseKinematics(cartesian, articular, torso, base_correction);
      std::cout << "Articular values: ";
      for(int i = 0; i < articular.size(); i++ ) std::cout << articular[i] << "  " << std::endl;
      std::cout << " Base correction: " << base_correction.x << "  "
		<< base_correction.y << " "
		<< base_correction.theta << std::endl;
      std::cout << " Torso correction: " << torso << std::endl;
      next_state = SM_MOVE_BASE;
      break;

    case SM_MOVE_BASE:
      std::cout << "----------------------------------------------" << std::endl;
      std::cout << "        CASE:  MOVE-BASE " << std::endl << std::endl;
      JustinaNavigation::moveLateral(base_correction.y, 4000);
      JustinaNavigation::moveDist(base_correction.x, 4000);
      JustinaNavigation::moveDistAngle(0.0, base_correction.theta, 5000);
      next_state = SM_MOVE_ARM;
      break;
      
    case SM_MOVE_ARM:
      std::cout << "----------------------------------------------" << std::endl;
      std::cout << "        CASE:  MOVE-ARM " << std::endl << std::endl;
      JustinaManip::startArmGoToArticular(articular);
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
