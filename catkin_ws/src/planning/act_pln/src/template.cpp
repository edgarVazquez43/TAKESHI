#include <iostream>
#include <algorithm>
#include <ros/package.h>
#include <stack>
#include <ros/ros.h>
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiNavigation.h"

enum state {
        SM_INIT_STATE,
        SM_FINAL_STATE //goto human
};

int main(int argc, char *argv[]) {
        std::cout << "||------Tidy up test------||" << '\n';
        ros::init(argc, argv,"tidy_up_test");
        ros::NodeHandle n;
        ros::Rate loop(0.5);
        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

        std::string pathToKnowledge = ros::package::getPath("knowledge");
        string pathObjectTidyUp=pathToKnowledge+"/navigation/wrs2018_I_tidy.txt";

        state nextState=SM_INIT_STATE;

        std::cout << "Stating state machine" << '\n';
        while (ros::ok() && !success)
        {
                switch (nextState)
                {
                case SM_INIT_STATE:
                        break;
                }
                ros::spinOnce();
                loop.sleep();
        }
        return 0;
}
}
