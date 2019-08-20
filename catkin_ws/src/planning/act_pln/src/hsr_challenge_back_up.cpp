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
        SM_FIND_OBJS,
        SM_GRASP_OBJ,
        SM_GOTO_LOC,
        SM_PLACE_OBJ,
        SM_GOTO_TRAY,
        SM_GOTO_MUG,
        SM_FIND_MUGS,
        SM_GRASP_MUG,
        SM_GOTO_TRASH,
        SM_FIND_TRASH,
        SM_FINAL_STATE //goto human
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

        std::vector<std::string> mugObjects;
        mugObjects.push_back("purple_mug");
        mugObjects.push_back("red_mug");
        mugObjects.push_back("green_mug");
        
        std::vector<std::string> trashObjects;
        trashObjects.push_back("apple_juice");
        trashObjects.push_back("cube_block");
        trashObjects.push_back("cajeta_cokkies");
        trashObjects.push_back("pineapple_cookies");
        trashObjects.push_back("soap");
        trashObjects.push_back("strawberry_cookies");
        TakeshiHRI::enableSphinxMic(false);

        vision_msgs::ObjectCoordinatesForDetection objectsCoordinates;
        objectsCoordinates=TakeshiVision::objectCoordinates;
        objectsCoordinates.z_max=0.3;
        TakeshiHRI::loadJSGFGrammar("grammars/hsr_challenge_august.jsgf","hsr_challenge");
        while (ros::ok() && !success)
        {
                switch (nextState)
                {
                case SM_INIT_STATE:
                        printState("SM_INIT_STATE");
                        
                        if(TakeshiManip::isTheHandPressed()){
                            TakeshiHRI::say("Hello, my name is Takeshi, i'm going to start the test");
                            if(TakeshiNavigation::getClose(trayLoc,40000)){
                                nextState = SM_FIND_OBJS;
                                detectInTray=true;
                                detectTries=0;
                            }
                        }  
                break;

                case SM_FIND_OBJS:
                        printState("SM_FIND_OBJS");
                        TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                        ros::Duration(2).sleep();
                        
                        if(TakeshiVision::detectSpecificYoloObject(trayObjects,detectedObjs,1000, objectsCoordinates)){
                                nextState = SM_GRASP_OBJ;
                        }
                        else{
                            if (detectTries>=maxDetects) {
                                TakeshiHRI::waitAfterSay( "I placed all objects, the tray is empty",2000);
                                detectInTray=false; 
                                detectMugs=true;        
                                nextState = SM_GOTO_MUG;       
                            }
                            else  
                                detectTries++;
                        }

                        break;

                case SM_GRASP_OBJ:
                        printState("SM_GRASP_OBJ");
                        objToGrasp = detectedObjs[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I'm going to grasp the object " << objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::waitAfterSay( takeshi_say.str(),1000);
                        TakeshiManip::hdGoTo(0,0.0,5000);

                        if(TakeshiTasks::graspObjectOnFloorFromAbove(
                        //if(TakeshiTasks::graspObjectOnFloor(
                                   objToGrasp.pose.position.x,
                                   objToGrasp.pose.position.y,
                                   objToGrasp.pose.position.z,
                                   0.0,
                                   false))     {
                            TakeshiHRI::say("I'm verifying if I grasped the object");
                            TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                            TakeshiNavigation::moveDist(-0.2, 3000);
                            ros::Duration(2).sleep();
                            if(!TakeshiVision::detectYoloObject(objToGrasp.id,objToGrasp,1000,objectsCoordinates)){
                                TakeshiHRI::say( "I took the object");
                                //if(detectTrash)
                                //    nextState=SM_GOTO_LOC;
                                //else
                                    nextState= SM_GOTO_LOC;
                            }
                            else{
                                TakeshiHRI::say( "I could not take the object");    
                                if(detectTrash)
                                    nextState=SM_FIND_TRASH;
                                else
                                    nextState=SM_FIND_OBJS;
                            }
                        }
                        
                        else{
                            TakeshiHRI::say( "I could not take the object");
                            TakeshiNavigation::moveDist(-0.2, 3000);
                            if(detectTrash)
                                nextState=SM_FIND_TRASH;
                            else
                                nextState=SM_FIND_OBJS;
                        }
                        break;

                case SM_GOTO_LOC:
                        printState("SM_GOTO_LOC");
                        mapLocation=objLocs3D[objToGrasp.id].name;
                        if(TakeshiNavigation::getClose(mapLocation,50000)){
                                nextState = SM_PLACE_OBJ;
                        }
                        break;

                case SM_PLACE_OBJ:
                        printState("SM_PLACE_OBJ");
                        if(detectInTray){
                            articular.clear();
                            getArticular(objPoses[objToGrasp.id],articular,trs);

                            if(TakeshiTasks::alignWithFrontTable(0.60)) {
                                    //TakeshiTasks::placeObjectInFront(0.0,0.9);
                                if(objToGrasp.id.compare("bill") == 0)
                                    TakeshiNavigation::moveDist(-0.25,5000);
                                    
                                TakeshiManip::torsoGoTo(trs,10000);
                                TakeshiManip::armGoToArticular(articular,4000);
                                ros::spinOnce();
                                TakeshiNavigation::moveDist(0.30,5000);
                                TakeshiManip::openGripper(1.0);
                                ros::Duration(3).sleep();
                                TakeshiNavigation::moveDist(-0.30,5000);
                                nextState=SM_GOTO_TRAY;
                            }
                        }
                        
                        else if(objToGrasp.id.compare("red_mug")==0){
                            TakeshiTasks::placeObjectInColorBin("red");
                            nextState=SM_GOTO_MUG;
                        }
                        else if(objToGrasp.id.compare("purple_mug")==0){
                            TakeshiTasks::placeObjectInColorBin("blue");
                            nextState=SM_GOTO_MUG;
                        }
                        else if(objToGrasp.id.compare("green_mug")==0){
                            TakeshiTasks::placeObjectInColorBin("green");
                            nextState=SM_GOTO_MUG;
                        }                      
                        else{
                            TakeshiTasks::placeObjectInColorBin("yellow");
                            nextState=SM_GOTO_TRASH;
                        }
                       
                        break;

                case SM_GOTO_TRAY:
                        printState("SM_GOTO_TRAY");
                        if(TakeshiNavigation::getClose(trayLoc,40000))
                        {
                                nextState = SM_FIND_OBJS;
                        }
                        break;

                case SM_GOTO_MUG:
                        printState("SM_GOTO_MUG");
                        if(TakeshiNavigation::getClose("mug_location",40000))
                        {
                                nextState = SM_FIND_MUGS;
                                detectTries=0;
                        }
                break;

                case SM_GOTO_TRASH:
                        printState("SM_GOTO_TRASH");
                        if(TakeshiNavigation::getClose("trash_location",40000))
                        {
                                nextState = SM_FIND_TRASH;
                                detectTries=0;
                        }
                break;

                case SM_FIND_TRASH:
                        printState("SM_FIND_TRASH");
                        TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                        ros::Duration(2).sleep();
                        if(TakeshiVision::detectSpecificYoloObject(trashObjects,detectedObjs,1000,objectsCoordinates)){
                                nextState = SM_GRASP_OBJ;
                        }
                        else{
                            if (detectTries>=maxDetects) {
                                TakeshiHRI::say( "I picked up the trash, I have finished the test");
                                nextState = SM_FINAL_STATE;       
                            }
                            else  
                                detectTries++;
                        }

                        break;

                case SM_FIND_MUGS:
                        printState("SM_FIND_MUGS");
                        TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                        ros::Duration(2).sleep();
                        if(TakeshiVision::detectSpecificYoloObject(mugObjects,detectedObjs,1000,objectsCoordinates)){
                                nextState = SM_GRASP_MUG;
                        }
                        else{
                            if (detectTries>=maxDetects) {
                                //TakeshiHRI::say( "I placed all mugs, the floor is empty");
                                TakeshiHRI::say( "There is no mugs left to place");
                                detectTrash=true;
                                nextState = SM_GOTO_TRASH;       
                                //nextState = SM_FINAL_STATE;       
                            }
                            else  
                                detectTries++;
                        }

                        break;

                case SM_GRASP_MUG:
                        printState("SM_GRASP_MUG");
                        objToGrasp = detectedObjs[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I am grasping the object " << objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::waitAfterSay( takeshi_say.str(),1000);
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
                                nextState= SM_GOTO_LOC;
                            }
                            else{
                                TakeshiHRI::say( "I could not take the object");  
                            }
                        }
                        else{
                            TakeshiHRI::say( "I could not take the object");
                            TakeshiNavigation::moveDist(-0.25, 3000);
                            nextState=SM_FIND_MUGS;
                        }
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
