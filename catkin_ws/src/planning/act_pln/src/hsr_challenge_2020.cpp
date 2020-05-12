////////////////////////////////////////////////////////
// Note: this code was commented into CMake file,
// If you are brave enough to edit this code please
// make sure to uncomment this code into CMakeList.txt
///////////////////        EDD-II    ////////////////////

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
        SM_WAIT_FOR_COMMAND,
        SM_PARSE_RECOG,
        SM_FIND_OBJS,
        SM_GRASP_OBJ,
        SM_GOTO_LOC,
        SM_PLACE_OBJ,
        SM_GOTO_TRAY,
        SM_MOVE,
        SM_GOTO_MUG,
        SM_FIND_MUGS,
        SM_GRASP_MUG,
        SM_GOTO_TRASH,
        SM_ALIGN,
        SM_FIND_TRASH,
        SM_FINAL_STATE, //goto human
        SM_INITIAL_POSE
};

void printState(std::string st);
void getArticular(joints& arr,joints & j, float & torso);

int main(int argc, char *argv[]) {
        std::cout << "||------HSR CHALLENGE------||" << '\n';
        ros::init(argc, argv,"hsr_challenge");
        ros::NodeHandle n;
        ros::Rate loop(0.5);
        TakeshiTasks::setNodeHandle(&n);
        TakeshiHRI::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

        std::string pathToKnowledge = ros::package::getPath("knowledge");
        std::string pathObject3D=pathToKnowledge+"/navigation/objLocations/3Dlocations.txt";
        std::string pathToPoses = pathToKnowledge+"/navigation/objLocations/knownPoses.txt";

        std::map<std::string, loc3D> objLocs3D;
        TakeshiKnowledge::getKnownObjectsLocationFromFile(pathObject3D,
                                                          objLocs3D);

        std::map<std::string, joints> objPoses;
        joints articular;
        float trs;
        TakeshiKnowledge::getKnownObjectsLocationFromFile(pathToPoses,
                                                          objPoses);

        std::cout << "Known Locations:" <<  objLocs3D.size()<<'\n';
        for(std::map<std::string,loc3D >::const_iterator it = objLocs3D.begin();
            it != objLocs3D.end(); ++it)
        {
                std::cout << it->first << ": "
                          << it->second.name << " "
                          << it->second.height << "\n";

        }

        std::cout << "Known Poses:" <<  objPoses.size()<<'\n';
        for(std::map<std::string,joints >::const_iterator it = objPoses.begin();
            it != objPoses.end(); ++it)
        {
                std::cout << it->first << ": "
                          << it->second[0] << " "
                          << it->second[1] << " "
                          << it->second[2] << " "
                          << it->second[3] << " "
                          << it->second[4] << "\n";
        }

        state nextState=SM_INIT_STATE;
        bool success = false;
        std::cout << "Stating state machine" << '\n';
        //Flor plane detection
        std::vector<int> inliersOnPlane;
        std::vector<float> vacantPlane;
        //For object detection
        std::vector<vision_msgs::VisionObject> detectedObjs;
        vision_msgs::VisionObject objToGrasp;
        //For graspeo
        geometry_msgs::Pose poseToGrasp;
        //For talking
        std::stringstream takeshi_say;
        ///For naviation
        std::string mapLocation(""), trayLoc("tray");
        //counters for tries
        unsigned int maxDetects =3, detectTries=0;
        bool verify=true;
        bool detectInTray=false;
        bool detectTrash=false;
        bool detectMugs=false;       

        std::vector<std::string> trayObjects;
        trayObjects.push_back("red_lego");
        trayObjects.push_back("blue_lego");
        trayObjects.push_back("yellow_lego");
        trayObjects.push_back("bill");
        trayObjects.push_back("red_towel");


        std::vector<std::string> mugObjects;
        mugObjects.push_back("purple_mug");
        mugObjects.push_back("red_mug");
        mugObjects.push_back("green_mug");
        
        std::vector<std::string> trashObjects;
        trashObjects.push_back("apple_juice");
        //trashObjects.push_back("cube_block");
        //trashObjects.push_back("cajeta_cokkies");
        trashObjects.push_back("chocolate_cookies");
        trashObjects.push_back("gansito_envelop");
        trashObjects.push_back("pineapple_cookies");
        trashObjects.push_back("soap");
        trashObjects.push_back("strawberry_cookies");
        trashObjects.push_back("rope");
        TakeshiHRI::enableSphinxMic(false);

        vision_msgs::ObjectCoordinatesForDetection objectsCoordinates;
        objectsCoordinates=TakeshiVision::objectCoordinates;
        objectsCoordinates.z_max=0.3;
        TakeshiHRI::loadJSGFGrammar("grammars/hsr_challenge_august.jsgf","hsr_challenge");
        std::string lastRecoSpeech;
        std::vector<std::string> specificYoloObjects;
        std::vector<vision_msgs::VisionObject> recognizedYoloObjects;
        specificYoloObjects.clear();
        vision_msgs::VisionObject object; 
        float y_correction, torso_correction;  

        int attemps =0;
        nextState=SM_INIT_STATE;

        while (ros::ok() && !success)
        {
                switch (nextState)
                {
                case SM_INIT_STATE:
                        printState("SM_INIT_STATE");
                        
                        if(TakeshiManip::isTheHandPressed()){
                            TakeshiHRI::say("Hello, my name is Takeshi, i'm going to start the test hsr_challenge 6");
                            /*if(TakeshiNavigation::getClose(trayLoc,40000)){
                                nextState = SM_FIND_OBJS;
                                detectInTray=true;
                                detectTries=0;
                            }*/
                            TakeshiHRI::enableSphinxMic(true);
                            nextState=SM_WAIT_FOR_COMMAND;
                        }  
                break;

                case SM_WAIT_FOR_COMMAND:
                    printState("SM_WAIT_FOR_COMMAND");
                    //TakeshiHRI::loadJSGFGrammar("grammars/hsr_challenge_august.jsgf","hsr_challenge");
                    //if(TakeshiNavigation::getClose(6.4,4,0,4000)){
                                nextState = SM_FIND_OBJS;
                    //}
                break;

               
                case SM_FIND_OBJS:
                        printState("SM_FIND_OBJS");
                        TakeshiHRI::say("Scanning surface for objects");
                        TakeshiManip::closeGripper(0.3);
                        if(TakeshiTasks::graspYoloObject(specificYoloObjects,recognizedYoloObjects,3, 4000, true)){
                            nextState=SM_MOVE;
                        }

                        break;

                case SM_MOVE:
                        TakeshiNavigation::moveDistAngle(0.0,-1.57,3000);

                        nextState=SM_ALIGN;
                        break;

               case SM_ALIGN:
                    ros::Duration(1.0).sleep();
                    TakeshiHRI::say("Lining  up with  surface");
                    if(TakeshiTasks::alignWithFrontTable(0.32))
                        nextState=SM_GOTO_LOC;
               break;

                case SM_GOTO_LOC:
                        printState("SM_GOTO_LOC");

                        TakeshiNavigation::moveDistAngle(0.0,1.57,3000);
                        TakeshiManip::hdGoTo(0.0,0.0,2000);
                        TakeshiManip::torsoGoTo(0.7, 3000);                        
                        TakeshiManip::armGoToArticular(-1.0,0.0,-1.57,0.0,3000);
                        TakeshiManip::hdGoTo(-1.57,-0.9,2000);
                        nextState=SM_PLACE_OBJ;
                        break;

                case SM_PLACE_OBJ:
                        printState("SM_PLACE_OBJ");
                        ros::Duration(1.0).sleep();
                        if(TakeshiVision::detectCircles(object)){ 
                        std::cout << "Point: " << object.x << " " << object.y << std::endl;                      
                        nextState=SM_GRASP_MUG;
                        }
                        break;

                case SM_GRASP_MUG:
                        TakeshiNavigation::moveDistAngle(0.0,-1.57,3000);
                        TakeshiManip::hdGoTo(-0.0,-0.0,2000);
                        std::cout<<"object pose x:"<< object.pose.position.x<<std::endl;
                        /*
                        if((object.pose.position.x - 0.10) < 0){
                            std::cout<<"entre al if"<<std::endl;
                            y_correction = object.pose.position.x + 0.02;  // 0.10 is the distance from base_arm to robot_base in axis Y //yo digo que 12
                        }
                        else{
                            std::cout<<"NO entre al if"<<std::endl;
                            y_correction = object.pose.position.x - 0.14;
                        }*/
                        std::cout << y_correction << std::endl;
                        y_correction = object.pose.position.x-0.1;
                        TakeshiNavigation::moveLateral(y_correction,3000);
                        torso_correction=object.pose.position.z-0.39;
                        std::cout << torso_correction << std::endl;
                        TakeshiManip::armGoToArticular(-1.45,0.0,-1.57,0.0,3000);
                        //TakeshiManip::torsoGoTo(torso_correction, 3000);
                        ros::Duration(2.0).sleep();
                        TakeshiManip::openGripper(1.0); 
                        if (attemps<3){
                            nextState=SM_INITIAL_POSE;
                            attemps++;
                        }  
                        else{
                            nextState=SM_FINAL_STATE;
                        }
                        break;

                case SM_INITIAL_POSE:
                    TakeshiNavigation::moveDistAngle(-0.3,0,5000);
                    TakeshiManip::navigationPose(4000);
                    TakeshiManip::closeGripper(0.1);
                    TakeshiNavigation::moveDistAngle(-0.2,1.57,5000);
                    nextState=SM_FIND_OBJS;

                    break;

                case SM_FINAL_STATE:
                        printState("SM_FINAL_STATE");
                        TakeshiHRI::say("I have finished the test");
                        TakeshiManip::navigationPose(4000);

                        success=true;
                        break;
                }
                ros::spinOnce();
                loop.sleep();
        }
        return 0;
}


void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        CASE: "<< st << "\033[0m" << std::endl;
}

void getArticular(joints& arr,joints & articular, float & torso)
{
        //Copies from arr[1-4] to articular and torse = arr[0]
    for (int i=0; i<arr.size();i++)
        std::cout << arr[i] << std::endl;
        if (arr.size()<2) {
                std::cout << "Not enought elements on vector " << '\n';
                return;
        }
        torso = arr[0];
        for (size_t i = 1; i < arr.size(); i++) {
                articular.push_back(arr[i]);
        }
        return;
}
