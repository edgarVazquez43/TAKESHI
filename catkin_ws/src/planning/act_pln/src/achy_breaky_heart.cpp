////////////////////////////////////////////////////////
// Note: this code was commented into CMake file,
// If you are brave enough to edit this code please
// make sure to uncomment this code into CMakeList.txt
///////////////////        EDD-II    ////////////////////

#include <ros/ros.h>
#include "takeshi_tools/TakeshiNavigation.h"

bool fist_part=false;

int main(int argc, char *argv[]) {
        std::cout << "archy_breaky_heart" << '\n';
        ros::init(argc, argv,"archy_breaky_heart");
        ros::NodeHandle n;
        ros::Rate loop(10);
        TakeshiNavigation::setNodeHandle(&n);


        while (ros::ok())
        {       
                if(!fist_part){
                        for(size_t i=0;i<4;i++){
                                TakeshiNavigation::moveDistAngle(0,-0.785,5000);
                                ros::Duration(.7).sleep();
                                TakeshiNavigation::moveDistAngle(0,0.785,5000);        
                                ros::Duration(.7).sleep();
                        }
                        fist_part=true;
                }

                TakeshiNavigation::moveLateral(-.30, 5000);
                ros::Duration(.5).sleep();
                ros::spinOnce();
                TakeshiNavigation::moveLateral(-.30, 5000);
                ros::Duration(.5).sleep();
                ros::spinOnce();

                TakeshiNavigation::moveLateral(.30, 5000);
                ros::Duration(.5).sleep();
                ros::spinOnce();
                TakeshiNavigation::moveLateral(.30, 5000);
                ros::Duration(.5).sleep();
                ros::spinOnce();

                TakeshiNavigation::moveDist(-.30,5000);
                ros::Duration(.5).sleep();
                ros::spinOnce();
                TakeshiNavigation::moveDist(-.30,5000);
                ros::Duration(.5).sleep();
                ros::spinOnce();

                TakeshiNavigation::moveDist(.30, 5000);
                ros::Duration(.5).sleep();
                ros::spinOnce();
                TakeshiNavigation::moveDist(.30, 5000);
                ros::Duration(.5).sleep();
                ros::spinOnce();

                TakeshiNavigation::moveDistAngle(0,1.570,5000);
                ros::Duration(.7).sleep();
                ros::spinOnce();
                loop.sleep();
        }
        return 0;
}
