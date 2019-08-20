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
  ros::init(argc, argv, "act_pln");
  
  ros::NodeHandle n;
  // JustinaHardware::setNodeHandle(&n);
  // JustinaHRI::setNodeHandle(&n);
  // JustinaManip::setNodeHandle(&n);
  // JustinaNavigation::setNodeHandle(&n);
  // JustinaTools::setNodeHandle(&n);
  JustinaVision::setNodeHandle(&n);
  // JustinaTasks::setNodeHandle(&n);
  // JustinaKnowledge::setNodeHandle(&n);

  ros::spinOnce();
  ros::Rate loop(10);

  JustinaVision::handCameraManip("marker");

  return 0;
}
