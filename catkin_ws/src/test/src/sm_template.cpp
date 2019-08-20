include <iostream>
#include <ros/ros.h>

#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiNavigation.h"

enum state {
        SM_INIT_STATE,
        SM_FIND_WRIST,
        SM_HANDOVER,
        SM_FINAL_STATE
};

int main(int argc, char *argv[]) {
        std::cout << "||------This is a template------||" << '\n';
        ros::init(argc, argv,"template_sm_node");
        ros::NodeHandle n;
        ros::NodeHandle nh_priv("~");

        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiHRI::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

        ros::Rate loop(1);

        //setup
        state nextState=SM_INIT_STATE;

        bool success = false;

        while (ros::ok() && !success)
        {
                switch (nextState)
                {
                }

                loop.sleep();
        }
        return 0;
}
