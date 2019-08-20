////////////////////////////////////////////////////////
// Note: this code was commented into CMake file,
// If you are brave enough to edit this code please
// make sure to uncomment this code into CMakeList.txt
///////////////////        EDD-II    ////////////////////

#include <iostream>
#include <ros/ros.h>
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiVision.h"

using namespace std;

enum state {
        SM_INIT_STATE,
        SM_FINAL_STATE
};

void printState(std::string st);

int main(int argc, char *argv[]) {
        std::cout << "||------Searching for objects on all known locations------||" << '\n';
        ros::init(argc, argv,"tidy_up_test");
        ros::NodeHandle n;
        ros::Rate loop(10);
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        TakeshiTasks::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);
        std::string objectToTake = "coffee";
        geometry_msgs::PointStamped wrist;
        state nextState=SM_INIT_STATE;

        bool success = false;

        while (ros::ok() && !success)
        {
                switch (nextState)
                {

                  case SM_INIT_STATE:
                        cout << "\033[1;34m     TakeshiTasks.->Give Object to the human: Find Wrist\033[0m" << endl;
                        if(TakeshiVision::getWrist(wrist))
                          {
                                  nextState=SM_FINAL_STATE;
                          }
                        break;

                   case SM_FINAL_STATE:
                       cout << "\033[1;34m     TakeshiTasks.->Give Object to the human: HandOver\033[0m" << endl;
                       TakeshiTasks::giveObject(wrist.point.x,wrist.point.y,wrist.point.z);
                       success=true;
                       break;
                }
					ros::spinOnce();
	        loop.sleep();
          }
        return 0;
}
