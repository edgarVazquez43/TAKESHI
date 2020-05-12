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
        SM_NAVIGATE_TO_MESS,
        SM_LOOK_ON_THE_FLOOR,
        SM_GRASP_FROM_FLOOR,
        SM_GOTO_PLACE, 
        SM_GO_TO_TABLE,
        SM_LOOK_ON_THE_TABLE,
        SM_FINAL_STATE
};

void printState(std::string st);

int main(int argc, char *argv[]) {
        std::cout << "||------Tidy up test------||" << std::endl;
        ros::init(argc, argv,"tidy_up_test");
        ros::NodeHandle n;
        ros::Rate loop(10);
        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

        std::vector<vision_msgs::VisionObject> recognizedObjects;
        vision_msgs::VisionObject objToGrasp;
        geometry_msgs::Pose poseToGrasp;
        bool userConfirmation = false, success=true;

        std::vector<std::string> validCommands;
        validCommands.push_back("tidy up the children room");
        validCommands.push_back("children room");

        std::string  lastRecoSpeech, takeshi_say="";

        vision_msgs::ObjectCoordinatesForDetection objectsCoordinates;
        objectsCoordinates=TakeshiVision::objectCoordinates;
        objectsCoordinates.z_max=0.3;
        std::vector<vision_msgs::VisionObject> detectedObjs;
        std::vector<std::string> aux_detectedObjs;
        std::vector<float> obj_position;
        /*In general the robot goes to messy location, look for objects and
           deposits them on tidyUpplace if no objects are found it turn a bit
           and looks again, if it turns more than 180 degrees it stops and finishes*/
        state nextState=SM_INIT_STATE;
        TakeshiHRI::loadGrammarSpeechRecognized("tokio_tidy_up_test.xml");
        while (ros::ok() && !success)
        {
            switch (nextState){

            case SM_INIT_STATE:
                printState("Initial state");
                    if(TakeshiManip::isTheHandPressed()){
                        TakeshiHRI::say("Hello, my name is Takeshi, i'm going to start the tidy up test");
                        nextState=SM_NAVIGATE_TO_MESS;
            break;

            case SM_NAVIGATE_TO_MESS:
                printState("SM_NAVIGATE_TO_MESS");
                if(!TakeshiNavigation::getClose("mess",8000))
                    if(!TakeshiNavigation::getClose("mess",7000))
                        TakeshiNavigation::getClose("mess",7000);
                nextState=SM_LOOK_ON_THE_FLOOR;

                break;
            case SM_LOOK_ON_THE_FLOOR:
                 printState("SM_LOOK_ON_THE_FLOOR");
                        TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                        ros::Duration(2).sleep();
                        if(TakeshiVision::detectAllYoloObjects(detectedObjs,1000,objectsCoordinates)){
                            nextState = SM_GRASP_FROM_FLOOR;
                        }
                        else{
                            nextState=SM_GO_TO_TABLE;      
                        }

                break;
            case SM_GRASP_FROM_FLOOR:
                printState("SM_GRASP_FROM_FLOOR");
                objToGrasp = detectedObjs[0];
                takeshi_say = "I am grasping the object " + objToGrasp.id;
                poseToGrasp = objToGrasp.pose;
                TakeshiHRI::waitAfterSay( takeshi_say,1000);
                TakeshiManip::hdGoTo(0,0.0,5000);

                if(TakeshiTasks::graspObjectOnFloor(
                //if(TakeshiTasks::graspObjectOnFloor(
                           objToGrasp.pose.position.x,
                           objToGrasp.pose.position.y,
                           objToGrasp.pose.position.z,
                           //0.0,
                           false))      {  
                    TakeshiHRI::say("I'm verifying if I grasped the object");
                    //TakeshiNavigation::moveDist(-0.2,4000);
                    TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                    ros::Duration(2).sleep();
                    if(!TakeshiVision::detectYoloObject(objToGrasp.id,detectedObjs[0],1000,objectsCoordinates)){
                        TakeshiHRI::say( "I took the object");
                        nextState= SM_GOTO_PLACE;
                    }
                    else{
                        TakeshiHRI::say( "I could not take the object");  
                    }
                }
                else{
                    TakeshiHRI::say( "I could not take the object");
                    TakeshiNavigation::moveDist(-0.25, 3000);
                    nextState=SM_NAVIGATE_TO_MESS;

                }
                break;
            case SM_GOTO_PLACE:
                printState("SM_GOTO_PLACE");


                break;
            case SM_GO_TO_TABLE:
                printState("SM_GO_TO_TABLE");
                if(!TakeshiNavigation::getClose("table",8000))
                    if(!TakeshiNavigation::getClose("table",7000))
                        TakeshiNavigation::getClose("table",7000);
                nextState=SM_LOOK_ON_THE_TABLE;
                break;

            case SM_LOOK_ON_THE_TABLE:
                TakeshiTasks::alignWithFrontTable();
                objectsCoordinates.z_max=0.9;
                if(TakeshiVision::detectAllYoloObjects(detectedObjs,10000,objectsCoordinates)){
                    obj_position.resize(3);
                    obj_position[0] = detectedObjs[0].pose.position.x;
                    obj_position[1] = detectedObjs[0].pose.position.y;
                    obj_position[2] = detectedObjs[0].pose.position.z;
                    TakeshiManip::hdGoTo(0, 0, 3000);
                    if(TakeshiTasks::graspObject(obj_position[0], obj_position[1], obj_position[2], false)){
                        TakeshiHRI::say("I'm verifying if I grasped the object");
                        TakeshiTasks::alignWithFrontTable();
                        ros::Duration(2).sleep();
                        objectsCoordinates.z_max=0.9;
                        if(!TakeshiVision::detectYoloObject(detectedObjs[0].id,detectedObjs[0],1000,objectsCoordinates))
                            nextState=SM_GOTO_PLACE;
                    }
                    
                }
                else{
                    TakeshiHRI::say("I didn't find anything on the table, first task is finished");
                    nextState=SM_FINAL_STATE;
                }

                break;
            
            case SM_FINAL_STATE:
                printState("Finishing going to human");
                TakeshiHRI::say("I finished the test reporting to human");
    //                    if(TakeshiNavigation::getClose(humanLocation,35000))
    //                    {
    //                            TakeshiHRI::say("task Finished");
    //                            success=true;
    //                    }
                break;
            }
            ros::spinOnce();
            loop.sleep();
        }
    }
    return 0;
}



void printState(std::string st){
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "\033[1;35m        CASE: "<< st << "\033[0m" << std::endl;
}