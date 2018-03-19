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
#include "justina_tools/JustinaRepresentation.h"
#include "std_msgs/Bool.h"
#include "string"


int main(int argc, char** argv)
{
  std::cout << "------------ TEST  ---------" << std::endl;
  ros::init(argc, argv, "manipulation_test");
  
  ros::NodeHandle n;
  JustinaHardware::setNodeHandle(&n);
  JustinaHRI::setNodeHandle(&n);
  JustinaManip::setNodeHandle(&n);
  JustinaNavigation::setNodeHandle(&n);
  JustinaTools::setNodeHandle(&n);
  JustinaVision::setNodeHandle(&n);
  JustinaTasks::setNodeHandle(&n);
  
  ros::Rate loop(10);

  std::vector<vision_msgs::VisionObject> recognizedObjects;
  std::vector<float> cartesian;
  std::vector<float> articular;
  std::vector<float> base_correction;

  int nextState = 1;
  bool fail = false;

  cartesian.resize(6);
  articular.resize(4);
  base_correction.resize(3);

  articular[0] = -0.2;
  articular[1] = 1.5707;
  articular[2] = 1.5707;
  articular[3] = 0.0;

  while(ros::ok() && !fail)
  {
    ros::spinOnce();
    loop.sleep();
    switch(nextState){
    case 1:
      // JustinaNavigation::goToRelPose(0.0, 0.0, -1.5707, 4000);
      JustinaHardware::setArmGoalPose(articular);
      JustinaManip::hdGoTo(1.5707, 0.0, 4000);
      nextState = 2;
      break;
      
    case 2:
      if (JustinaVision::detectObjects(recognizedObjects, false) )
      std::cout << "Obj_position:" << recognizedObjects[0].pose.position
    		<< std::endl;
      nextState = -1;
      break;
    default:
      std::cout << "Finish tests" << std::endl;
      fail = true;

    }
    ros::spinOnce();
    loop.sleep();
  }
  

  return 0;
}
