#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ros/ros.h"
//#include "interactive_clean_test.h"

#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include <act_pln/virtualMsg.h>

enum state {
        SM_INIT_STATE,
        SM_READY,
        SM_FIND_PICKUP,
        SM_FIND_CLEANUP,
        SM_FND_LOCATION_PK,
        SM_GOTO_LOCATION_PICK,
        SM_GOTO_XY_PICK,
        SM_FIND_OBJECTS_TABLE,
        SM_FIND_OBJECTS_FLOOR,
        OBJECT_PICK,
        SM_GRASP_OBJ_FLOOR,
        SM_GRASP_OBJ_TABLE,
        SM_GOTO_LOCATION_CLEAN,
        SM_PLACE_OBJ,
        SM_TASK_FNSH,
        SM_MISSION_COMPLETE
};


const std::string MSG_ARE_YOU_READY    = "Are_you_ready?";
const std::string MSG_PICK_UP         = "Pick_it_up!";
const std::string MSG_CLEAN_UP         = "Clean_up!";
const std::string MSG_TASK_SUCCEEDED   = "Task_succeeded";
const std::string MSG_TASK_FAILED      = "Task_failed";
const std::string MSG_MISSION_COMPLETE = "Mission_complete";

const std::string MSG_I_AM_READY      = "I_am_ready";
const std::string MSG_OBJECT_GRASPED  = "Object_grasped";
const std::string MSG_TASK_FINISHED   = "Task_finished";


void printState(std::string st);

void messageCallback(const act_pln::virtualMsg::ConstPtr& message){
    ROS_INFO("Subscribe message:%s, %s", message->message.c_str(), message->detail.c_str());
//std::cout << strcmp(message->message.c_str(),"GoTo") << std::endl;
//std::cout << "Div" << std::endl;
//std::cout << strcmp(message->message.c_str(),"Gosh") << std::endl;
    if(strcmp(message->message.c_str(),"GoTo") == 0){
        std::cout << "------------ going to  ---------" << std::endl;
        std::cout << message->detail.c_str() << std::endl;
        TakeshiNavigation::getClose(message->detail.c_str(),25000);
        std::cout << "------------ gone  ---------" << std::endl;
    }/* else {
       std::cout << "OTRO" << std::endl; 
    }*/

    /*
    else if (message->message.c_str() == "COMMAND"){
        DO SOMETHING
    }
    */

  }

int main(int argc, char *argv[]) {
        std::cout << "------------ VR HSR 2019  ---------" << std::endl;


        ros::init(argc, argv, "hand_me_that_test");
        ros::NodeHandle n;
        ros::Rate loop(1);

        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

std::string sub_task_msg_topic_name;
    n.param<std::string>("sub_task_msg_topic_name",         sub_task_msg_topic_name,         "/video/message/task_msg");
  ros::Subscriber sub_task_msg = n.subscribe<act_pln::virtualMsg>(sub_task_msg_topic_name, 100, messageCallback);



        while (ros::ok()){
            //std::cout << "------------ loopi  ---------" << std::endl;
                ros::spinOnce();
                loop.sleep();
        }

        return 0;
}

void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "        CASE: "<< st << std::endl << std::endl;
}
