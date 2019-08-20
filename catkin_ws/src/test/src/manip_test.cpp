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
  geometry_msgs::Pose2D base_correction;
  float torso;

  float x_obj, y_obj, z_obj;
  float x_base, y_base, z_base;
  

  int nextState = 1;
  bool fail = false;

  cartesian.resize(6);
  articular.resize(4);

  articular[0] = -0.2;
  articular[1] = 1.5707;
  articular[2] = 1.5707;
  articular[3] = 0.0;

  while(ros::ok() && !fail)
  {
    ros::spinOnce();
    loop.sleep();
    switch(nextState)
    {
    case 1:
      std::cout << "STATE:   ALING WITH TABLE---" << std::endl;
      JustinaNavigation::moveDistAngle(0.0, -1.5707, 10000);
      JustinaTasks::alignWithTable(0.5);
      nextState = 2;
      break;
      
    case 2:
      std::cout << "STATE:   DETECT OBJECTS---" << std::endl;
      JustinaManip::hdGoTo(1.5707, -0.9, 5000);
      ros::Duration(10.0).sleep();
      if (JustinaVision::detectObjects(recognizedObjects, false) )
	std::cout << "Obj_position:" << recognizedObjects[0].pose.position
		  << std::endl;
      x_obj = recognizedObjects[0].pose.position.x;
      y_obj = recognizedObjects[0].pose.position.y;
      z_obj = recognizedObjects[0].pose.position.z;

      JustinaNavigation::moveDistAngle(0.0, 1.5707, 10000);

      x_base = -(x_obj + 0.08);


      std::cout << "Base correction: " << std::endl;
      std::cout << "x correction: " << x_base << std::endl;
     
      JustinaNavigation::moveLateral(x_base, 6000);
      
      cartesian.resize(3);
      cartesian[0] = y_obj;
      cartesian[1] = x_obj;
      cartesian[2] = z_obj;
      nextState = 3;
      break;
    case 3:
      JustinaManip::hdGoTo(0.0, 0.0, 3000);
      cartesian[0] = cartesian[0] - 0.10;
      std::cout << "Request cartesian: "
		<< cartesian[0] << "  "
		<< cartesian[1] << "  "
		<< cartesian[2] << "  "
 		<< std::endl;
      JustinaManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction);
      ros::Duration(5.0).sleep();
      JustinaManip::openGripper(1.0);
      std::cout << "TorsoCorrection:   " << torso << std::endl;
      JustinaManip::torsoGoTo(torso, 2000);
      JustinaManip::armGoToArticular(articular, 2000);

      cartesian[0] = cartesian[0] + 0.10;
      std::cout << "Request cartesian: "
		<< cartesian[0] << "  "
		<< cartesian[1] << "  "
		<< cartesian[2] << "  "
 		<< std::endl;
      JustinaManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction);
      ros::Duration(5.0).sleep();
      JustinaManip::openGripper(1.0);
      std::cout << "TorsoCorrection:   " << torso << std::endl;
      JustinaManip::torsoGoTo(torso, 2000);
      JustinaManip::armGoToArticular(articular, 2000);

      nextState = 4;
      break;
    case 4:
      JustinaManip::closeGripper(0.01);
      ros::Duration(5.0).sleep();
      JustinaManip::torsoGoTo(torso + 0.1, 2000);
      JustinaManip::armGoToNavigation();
      JustinaManip::torsoGoTo(0.0, 2000);
    default:
      std::cout << "Finish tests" << std::endl;
      fail = true;

    }
    ros::spinOnce();
    loop.sleep();
  }
  

  return 0;
}
