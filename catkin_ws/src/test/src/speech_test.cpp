#include "ros/ros.h"
#include <justina_tools/JustinaHRI.h>

int main(int argc, char** argv)
{
  std::cout << "Test speech gen    by EDD-II" << std::endl;
  std::string ss;
  
  ros::init(argc, argv, "speech_test");
  ros::NodeHandle n;

  JustinaHRI::setNodeHandle(&n);
  ros::Rate loop(10);

  ss = "Hola amigos";
  
  JustinaHRI::say(ss);
  JustinaHRI::say("Sir edd, go home...");
  

  ros::spinOnce();
  loop.sleep();

  return 0;
}
