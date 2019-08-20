#include <iostream>
#include "ros/ros.h"
#include "justina_tools/JustinaVision.h"
#include "justina_tools/JustinaTasks.h"
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>


int main(int argc, char** argv)
{
  std::cout << std::endl;
  std::cout << "----> INITIALIZING INVERSE KINEMATIC TEST BY EDGAR-II..." << std::endl;
  ros::init(argc, argv, "TESST_find_objs");
  ros::NodeHandle    n;

  JustinaVision::setNodeHandle(&n);
  JustinaTasks::setNodeHandle(&n);

  float x;
  float y;
  float z;

  std::vector<vision_msgs::VisionObject> recoObjList;

  // ROS Topic Publisher

  ros::Rate loop(30);


  ros::spinOnce();
  loop.sleep();

  while(ros::ok())
  {
    if( JustinaVision::detectAllObjects(recoObjList, false) )
    {
      for(int i = 0; i < recoObjList.size(); i++)
	  std::cout << "Object[" << i << "]:  " << recoObjList[i].pose.position << std::endl;

      x = recoObjList[0].pose.position.x;
      y = recoObjList[0].pose.position.y;
      z = recoObjList[0].pose.position.z;

      JustinaTasks::graspObject(x, y, z, false);
    }

    ros::spinOnce();
    loop.sleep();

    break;
  }
  return 0;
}
