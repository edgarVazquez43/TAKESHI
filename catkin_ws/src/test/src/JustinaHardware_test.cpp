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
  vision_msgs::VisionFlattenedObjectList recoObjList;
  
  ros::NodeHandle n;
  JustinaVision::setNodeHandle(&n);

  ros::spinOnce();
  ros::Rate loop(10);

  std::string recognizedSentence;
  std::vector<float> vacantPlane;
  std::vector<int>   inliers;

  
  // JustinaTasks::graspObject(0.45, -0.20, 0.80);
  // JustinaVision::findVacantPlane(vacantPlane, inliers);

  while(ros::ok())
    JustinaVision::detectFlattenedObjects(recoObjList, false);


  
  return 0;
}
