#include <iostream>
#include "ros/ros.h"
#include "takeshi_tools/TakeshiTasks.h"

int main(int argc, char** argv)
{
  std::cout << std::endl;
  std::cout << "----> INITIALIZING INVERSE KINEMATIC TEST BY EDGAR-II..." << std::endl;
  ros::init(argc, argv, "grasp_obj_test");

  ros::NodeHandle    n;
  ros::Rate loop(10);

  TakeshiTasks::setNodeHandle(&n);

  // TakeshiTasks::alignWithTable(0.4, false);
  // TakeshiTasks::graspObjectLateral("", false);

  TakeshiTasks::alignWithTable(0.4, false);
  TakeshiTasks::placeObject(0.0, 1.3, false);
  

  loop.sleep();
  return 0;
}
