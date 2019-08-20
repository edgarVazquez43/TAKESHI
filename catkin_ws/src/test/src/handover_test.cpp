#include <iostream>
#include <ros/ros.h>

#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiNavigation.h"

#include "geometry_msgs/WrenchStamped.h"

enum state {
        SM_INIT_STATE,
        SM_FIND_WRIST,
        SM_WAIT,
        SM_HANDOVER,
        SM_FINAL_STATE
};

bool pressed=false;
void wristWrenchCallback(const geometry_msgs::WrenchStamped wr)
{
        if (wr.wrench.force.x>20.0)
        {
                std::cout << "\tGot force of " <<  wr.wrench.force.x<<'\n';
                pressed=true;
        }
        return;
}

int main(int argc, char *argv[]) {
        std::cout << "||------This is a handover test------||" << '\n';
        ros::init(argc, argv,"handover_node");
        ros::NodeHandle n;
        ros::NodeHandle nh_priv("~");

        ros::Subscriber wrenchSub =
                n.subscribe("/hsrb/wrist_wrench/compensated",2,&wristWrenchCallback);

        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiHRI::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

        ros::Rate loop(0.6);

        //setup
        state nextState=SM_INIT_STATE;

        bool success = false;
        geometry_msgs::PointStamped wrist;

        while (ros::ok() && !success)
        {
                switch (nextState)
                {
                case SM_INIT_STATE:
                        std::cout << "Initilaize" << '\n';
                        if (pressed) {
                                nextState = SM_FIND_WRIST;
                        }
                        else {
                                nextState = SM_INIT_STATE;
                        }
                        break;
                case SM_WAIT:
                        std::cout << "Waiting" << '\n';
                        ros::Duration(5.0).sleep();
                        nextState=SM_FIND_WRIST;
                        break;


                case SM_FIND_WRIST:
                        std::cout << "Find Wrist" << '\n';
                        if(TakeshiVision::getWrist(wrist))
                        {
                                nextState=SM_HANDOVER;
                        }
                        break;
                case SM_HANDOVER:
                        std::cout << "Handover" << '\n';
                        if(TakeshiTasks::graspObject(wrist.point.x,wrist.point.y,wrist.point.z+0.10, false))
                        {
                                nextState=SM_FINAL_STATE;
                        }
                        else
                        {
                          nextState = SM_INIT_STATE;
                        }
                        break;
                case SM_FINAL_STATE:
                        std::cout << "Final State" << '\n';
                        success = true;
                        break;
                }
                ros::spinOnce();
                loop.sleep();
        }
        return 0;
}
