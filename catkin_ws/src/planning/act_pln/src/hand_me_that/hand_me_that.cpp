#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ros/ros.h"
#include "interactive_clean_test.h"

#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiNavigation.h"

enum state {
        SM_INIT,
        SM_WAIT_DOOR,
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

int main(int argc, char *argv[]) {
        std::cout << "------------ HAND ME THAT TEST  ---------" << std::endl;
        ros::init(argc, argv, "hand_me_that_test");
        ros::NodeHandle n;
        ros::Rate loop(1);

    bool add_obj=false;
        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);
        std::vector<geometry_msgs::PointStamped> armL, armR, armP, armC;
        vision_msgs::Skeleton closestSkeleton;
        std::vector<vision_msgs::VisionObject> detectedObjects;
        std::vector<std::string> allObjectsFound;
        std::string object_to_grasp;
        tf::TransformListener * tf_listener = new tf::TransformListener();
        bool tmpSux,success;
        geometry_msgs::Point pointedObjCentroid, floorPointed;
        geometry_msgs::Pose2D destination;
        std::string location="moderator";
    std::string lastRecoSpeech;
        int timeoutspeech = 10000;
    std::string grammarCommands = "grammars/pre_sydney/receptionist_names.jsgf";
        interactiveCleaner ic(n); //setup
        std::map<std::string, std::vector<float> > ls;
        TakeshiKnowledge::getKnownLocations(ls);
        ic.setKnownLocations(ls);
        double armAngle=0;
    bool userConfirmation=false;

    int try_no = 0;
    int try_no_see = 0;
    bool get_near_locations = false;

    TakeshiHRI::loadJSGFGrammar(grammarCommands,"hand_me_that");
        state nextState = SM_INIT;
        while (ros::ok() && !success)
        {
                switch (nextState) {
                    case SM_INIT:
                        printState("SM START");
                        TakeshiHRI::waitAfterSay("waitting for the door to be open",2000);
                        nextState=SM_WAIT_DOOR;
                    break;
                    case SM_WAIT_DOOR:
                        printState("wait for the door");
                        if(!TakeshiNavigation::obstacleInFront()){
                            nextState = SM_INIT_STATE;
                        }
                    break;
                case SM_INIT_STATE:
                        printState(" Initial State");
                        //if(!MSG_ARE_YOU_READY.compare(ic.receivedMessage))
                        //{
                                //ic.sendMessage(MSG_I_AM_READY);
                        TakeshiHRI::say("I'm going to the start point");
                        TakeshiNavigation::moveDist(1.5,7000); //avoid door
                        TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                        TakeshiNavigation::getClose("carry_luggage",25000);//uncomment

                        TakeshiManip::hdGoTo(0.0, 0.0, 5000);
                                TakeshiHRI::waitAfterSay("I'm ready for the hand me that test", 3000);
                                ic.startRoutine(true);
                                nextState = SM_FIND_PICKUP;
                                TakeshiHRI::waitAfterSay("what do you need?, Please stand in front of me and point to the object", 3000);
                                TakeshiHRI::waitAfterSay("Say takeshi yes when you are ready", 3000);
                                TakeshiHRI::enableSphinxMic(true);
                        //}
                        //else
                        //{
                                //nextState = SM_INIT_STATE;
                        //}
                        break;
                // case SM_TRACK_ETHAN:
                //         if(!MSG_PICK_UP.compare(ic.receivedMessage))
                //         {
                //                 nextState = SM_FIND_PICKUP;
                //                 ic.sendMessage(MSG_I_AM_READY);
                //                 ic.startRoutine();
                //         }
                //         break;

                case SM_FIND_PICKUP:
                        printState("Finding skeleton pickup");
                        if (!ic.getArmsByTopicOnMap(armL,armR, closestSkeleton))
                        {
                                std::cout << "Could not find arms" << '\n';
                                TakeshiHRI::waitAfterSay("I can't see you, please stand in front of me and point to the object", 3000);
                                nextState = SM_FIND_PICKUP;
                                break;
                        }
                        

                        TakeshiHRI::waitAfterSay("Are you pointing to the object?", 3000);
                        TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 10000);
                        std::cout << lastRecoSpeech <<  '\n';
                        if(TakeshiHRI::waitForUserConfirmation(userConfirmation, 5000)){

                            if(ic.validateArms(armL,armR,armP))
                            {
                                TakeshiHRI::waitAfterSay("Ok", 3000);
                                interactiveCleaner::printArm(armP);
                                TakeshiHRI::enableSphinxMic(false);

                                    TakeshiHRI::waitAfterSay("I will pick the object", 3000);
                                    ic.startRoutine(false);
                                    //nextState = SM_FIND_CLEANUP;
                                    nextState = SM_FND_LOCATION_PK;
                                /*for(size_t i=0;i<5;i++){
                                    TakeshiVision::detectAllYoloObjects(detectedObjects, 5000);
                                    for(size_t j=0;j<detectedObjects.size();j++){
                                        add_obj =true;
                                        for(size_t k=0; k<allObjectsFound.size();k++){
                                            if(allObjectsFound[k].compare(detectedObjects[j].id)==0){
                                                add_obj = false;
                                                break;
                                            }
                                        }
                                        if(add_obj) allObjectsFound.push_back(detectedObjects[j].id);
                                    }
                                }
                                 
                                if(allObjectsFound.size()!=0){
                                    TakeshiHRI::waitAfterSay("I will pick the object", 3000);
                                    //nextState = SM_FIND_CLEANUP;
                                    nextState = SM_FND_LOCATION_PK;
                                } else {
                                    std::cout << "Can't find objects" << '\n';
                                    //TakeshiHRI::waitAfterSay("I can't find any objects, please point to the object", 3000);
                                }*/

                            } else {
                                std::cout << "Can't SEE you" << '\n';
                                TakeshiHRI::waitAfterSay("I can't see where you are pointing at, please stand in front of me and point to the object", 3000);
                            }   
                        } else {
                            std::cout << "Can't hear" << '\n';
                            TakeshiHRI::waitAfterSay("I can't hear you, please stand in front of me and point to the object", 3000);
                        }

                        TakeshiHRI::loadJSGFGrammar(grammarCommands);
                        //if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                          //      if(lastRecoSpeech.compare("pickup") == 0){
                        /*if(TakeshiHRI::waitForSpecificSentence("pick up", timeoutspeech)){
                                        if(ic.validateArms(armL,armR,armP))
                                        {
                                                interactiveCleaner::printArm(armP);
                                                TakeshiHRI::waitAfterSay("Ok, I am going to pick that object", 4000);
                                                nextState = SM_FIND_CLEANUP;
                                        } else {
                                                TakeshiHRI::waitAfterSay("Please point to the object and say pickup", 3000);
                                        }   
                        }*/                    
                            //    }
                        //}
                        /*if (!ic.getArmsByTopicOnMap(armL,armR))
                        {
                                std::cout << "Could not find arms" << '\n';
                                nextState = SM_FIND_PICKUP;
                        }
                        if(!MSG_PICK_UP.compare(ic.receivedMessage))
                        {
                                if(ic.validateArms(armL,armR,armP))
                                {
                                        interactiveCleaner::printArm(armP);
                                        nextState = SM_FIND_CLEANUP;
                                }
                        }*/

                        break;
                case SM_FIND_CLEANUP:
                        printState("Finding skeleton cleanup");
                        if (!ic.getArmsByTopicOnMap(armL,armR, closestSkeleton))
                        {
                                std::cout << "Could not find arms" << '\n';
                                nextState = SM_FIND_CLEANUP;
                        }

                        if(!MSG_CLEAN_UP.compare(ic.receivedMessage))
                        {
                                if(ic.validateArms(armL,armR,armC)) {
                                        interactiveCleaner::printArm(armC);
                                        nextState = SM_FND_LOCATION_PK;
                                        ic.startRoutine(false);
                                }
                        }

                        break;

                case SM_FND_LOCATION_PK:
                        printState("finding location");
                        /*armAngle = ic.angleOfArm(armP);
                        if (fabs(armAngle)>=30* M_PI/180)
                        {
                                std::cout << "\tPointing to floor " << armAngle *180/M_PI << '\n';
                                destination=ic.floorLocation(armP);
                                nextState = SM_GOTO_XY_PICK;
                                //FIND CLOSEST AND SAVE
                                //nextState = OBJECT_PICK;
                        }
                        else
                        {
                                location = ic.findPointedLocation(armP);
                                std::cout << "\tPointing to location " << location << '\n';
                                nextState = SM_GOTO_LOCATION_PICK;
                        }*/
                        /*if (fabs(armAngle)>=30* M_PI/180){
                            get_near_locations = true;
                        } else {
                            get_near_locations = false;
                        }*/
                        get_near_locations = (fabs(armAngle)>=30* M_PI/180); //same as above. If pointing to low, its a location near

                                location = ic.findPointedLocation(armP, closestSkeleton, get_near_locations);
                                std::cout << "\tPointing to location " << location << '\n';
                                nextState = SM_GOTO_LOCATION_PICK;
                        break;
                case SM_GOTO_LOCATION_PICK:
                        printState("Calculate destination and get close to pick up by location");
                        //location = ic.findPointedLocation(armP);
                        TakeshiNavigation::getClose(location,25000);
                        TakeshiNavigation::getClose(location,25000);
                        nextState = SM_FIND_OBJECTS_TABLE;
                        /*if(TakeshiNavigation::getClose(location,25000))
                        {
                                nextState = SM_FIND_OBJECTS_TABLE;
                        }

                        else
                        {
                                nextState = SM_GOTO_LOCATION_PICK;
                                //OR ask fro repoint
                        }*/

                        break;
                case SM_GOTO_XY_PICK:
                        printState("Calculate destination and get close to pick up by XY th");
                        if(!TakeshiNavigation::getClose(destination.x,destination.y,destination.theta,25000)){
                            //Not OK :p
                            tf::StampedTransform transform;
                            tf::Quaternion q;
                    
                            tf_listener->lookupTransform("map", "base_link", ros::Time(0), transform);
                            //q = transform.getRotation();
                            //currentX = transform.getOrigin().x();
                            //currentY = transform.getOrigin().y();
                            //currentTheta = atan2((float)q.z(), (float)q.w()) * 2;

                            TakeshiNavigation::getClose(transform.getOrigin().x(),transform.getOrigin().y(),destination.theta,5000);
                        }

                        nextState = SM_FIND_OBJECTS_FLOOR;
                        /*if(TakeshiNavigation::getClose(destination.x,destination.y,destination.theta,25000))
                        {
                                nextState = SM_FIND_OBJECTS_FLOOR;
                        }

                        else
                        {
                                nextState = SM_GOTO_XY_PICK;
                                //OR ask fro repoint
                        }*/
                        break;

                case SM_FIND_OBJECTS_TABLE:
                        printState("Finding objects on location");
                        TakeshiTasks::alignWithTable();
                        // Find objects
                        //ros::Duration(2.0).sleep(); //why?
                        if(TakeshiVision::detectAllObjects(detectedObjects))
                        {
                                pointedObjCentroid.x = detectedObjects[0].pose.position.x;//=ic.findPointedObj(detectedObjects,armP);
                                pointedObjCentroid.y = detectedObjects[0].pose.position.y;
                                pointedObjCentroid.z = detectedObjects[0].pose.position.z;
                                nextState = SM_GRASP_OBJ_TABLE;
                        }
                        else
                        {
                                //TakeshiNavigation::moveDist(-0.05, 3000);

                            TakeshiNavigation::getClose(location,25000);
                            try_no_see++;
                            if(try_no_see >= 1){
                                try_no_see = 0;
                                TakeshiHRI::waitAfterSay("I give up",1000);

                            //TakeshiManip::armGoToDeliverObjectInFloor(5000);
                            
                            TakeshiManip::navigationPose(5000);
                            ros::spinOnce();
                            loop.sleep();

                            ic.startRoutine(true);
                            TakeshiHRI::enableSphinxMic(true);
                            TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                            TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                            TakeshiHRI::waitAfterSay("what do you need?, Please stand in front of me and point to the object in the next group", 3000);
                            TakeshiHRI::waitAfterSay("Say takeshi yes when you are ready", 3000);
                            nextState=SM_FIND_PICKUP;
                            }

                        }
                        break;
                case SM_FIND_OBJECTS_FLOOR:
                        printState("Finding objects on floor");
                        //if(tmpSux){nextState = SM_MISSION_COMPLETE;}
                        // Find objects
                        //ros::Duration(2.0).sleep(); //why?
                        TakeshiManip::hdGoTo(0,-1.00,5000);

                        if(TakeshiVision::detectAllObjectsFloor(detectedObjects))
                        {

                                pointedObjCentroid = ic.findPointedObj(detectedObjects,armP);//check detectedObjects[0].pose.position;
                                nextState = SM_GRASP_OBJ_FLOOR;
                        }
                        else
                        {
                                //TakeshiNavigation::moveDist(-0.05, 5000);
                                TakeshiNavigation::moveDist(-0.05, 3000);
                        }

                        break;
                case OBJECT_PICK:
                        printState("Grasping object floor");
                        tmpSux=TakeshiTasks::graspObjectOnFloor(
                                pointedObjCentroid.x,
                                pointedObjCentroid.y,
                                pointedObjCentroid.z,
                                true);
                        if (tmpSux) {
                                //ic.sendMessage(MSG_OBJECT_GRASPED);
                                nextState = SM_GOTO_LOCATION_CLEAN;
                        }
                        else
                        {
                                nextState = SM_FIND_OBJECTS_FLOOR;
                        }

                        break;
                case SM_GRASP_OBJ_FLOOR:
                 TakeshiManip::hdGoTo(0,0.00,5000);
                        printState("Grasping object floor");
                        /*tmpSux=TakeshiTasks::graspObjectOnFloorFromAbove(
                                pointedObjCentroid.x,
                                pointedObjCentroid.y,
                                pointedObjCentroid.z,
                                pointedObjCentroid.z,
                                true);
                         CHECK*/
                        tmpSux=TakeshiTasks::graspObjectOnFloor(
                                pointedObjCentroid.x,
                                pointedObjCentroid.y,
                                pointedObjCentroid.z,
                                true);

                        //if (tmpSux) {
                            nextState = SM_TASK_FNSH;
                                //ic.sendMessage(MSG_OBJECT_GRASPED);
                                //nextState = SM_GOTO_LOCATION_CLEAN;
                                //TakeshiHRI::waitAfterSay("Task finished", 3000);
                                //nextState = SM_MISSION_COMPLETE;
                        //}
                        //else
                        //{
                        //    TakeshiNavigation::moveDist(-0.25, 3000);
                        //        nextState = SM_FIND_OBJECTS_FLOOR;
                        //}

                        break;

                case SM_GRASP_OBJ_TABLE:
                        printState("Grasping object table");
                        tmpSux=TakeshiTasks::graspObjectLateral(
                                pointedObjCentroid.x,
                                pointedObjCentroid.y,
                                pointedObjCentroid.z,true);
                        //nextState = SM_TASK_FNSH;
                        if (tmpSux) {
                                //ic.sendMessage(MSG_OBJECT_GRASPED);
                                //nextState = SM_GOTO_LOCATION_CLEAN;
                                //TakeshiHRI::waitAfterSay("Task finished", 3000);
                                //nextState = SM_MISSION_COMPLETE;
                             nextState = SM_TASK_FNSH;
                        }
                        else
                        {

                            /*nextState = SM_FIND_OBJECTS_TABLE;
                            TakeshiNavigation::getClose(location,25000);
                            try_no_see++;
                            if(try_no_see >= 8){
                                try_no_see = 0;
                                TakeshiHRI::waitAfterSay("I give up",1000);

                            //TakeshiManip::armGoToDeliverObjectInFloor(5000);
                            
                            TakeshiManip::navigationPose(5000);
                            ros::spinOnce();
                            loop.sleep();

                            ic.startRoutine(true);
                            TakeshiHRI::enableSphinxMic(true);
                            TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                            TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                            TakeshiHRI::waitAfterSay("what do you need?, Please stand in front of me and point to the object in the next group", 3000);
                            TakeshiHRI::waitAfterSay("Say takeshi yes when you are ready", 3000);
                            nextState=SM_FIND_PICKUP;
                            }*/
nextState = SM_TASK_FNSH;
                        }

                        break;



                case SM_GOTO_LOCATION_CLEAN:
                        printState("Calculate destination and get close to cleanup place");

                        location = ic.findPointedLocation(armC, closestSkeleton, get_near_locations);
                        if(TakeshiNavigation::getClose(location,25000))
                        {
                                nextState = SM_PLACE_OBJ;
                        }

                        else
                        {
                                nextState = SM_GOTO_LOCATION_CLEAN;
                                //OR ask fro repoint
                        }
                        break;
                case SM_PLACE_OBJ:
                        printState("Placing object");
                        if(TakeshiTasks::placeObject(0.01, true,true))
                        {
                                //ic.sendMessage(MSG_TASK_FINISHED);
                                nextState = SM_TASK_FNSH;
                        }
                        break;
                case SM_TASK_FNSH:
                        /*printState("Waiting for evaluation");
                        if (!MSG_TASK_SUCCEEDED.compare(ic.receivedMessage))
                        {
                                nextState = SM_INIT_STATE;
                        }
                        else if (!MSG_TASK_FAILED.compare(ic.receivedMessage))
                        {
                                nextState = SM_INIT_STATE;
                        }
                        else if (!MSG_MISSION_COMPLETE.compare(ic.receivedMessage))
                        {
                                nextState = SM_MISSION_COMPLETE;
                        }*/
                        TakeshiHRI::enableSphinxMic(true);
                        TakeshiHRI::waitAfterSay("Is this the object?", 3000);

                if(TakeshiHRI::waitForUserConfirmation(userConfirmation, 5000)){
                    if(userConfirmation){

                        TakeshiHRI::waitAfterSay("Ok, here is the object",1000);


                        //FINISH END LOOP
                        /*
                        TakeshiManip::armDeliverBag();
                        TakeshiHRI::enableSphinxMic(false);
                        nextState=SM_MISSION_COMPLETE;
                        */
                        //FINISH END LOOP


                        //RESTART NEXT GROUP
                        //TakeshiManip::armGoToDeliverObjectInFloor(5000);
                        TakeshiHRI::waitAfterSay("Ok, I will try with the next group",1000);
                        TakeshiNavigation::startMoveDist(-0.2);
                        TakeshiManip::startHdGoTo(0.0, 0.0);
                        TakeshiManip::startTorsoGoTo(0.5);
                        ros::Duration(1.0).sleep();
                        TakeshiManip::armGoToArticular(0.0, 0.0, -1.4, 0.0, 300);
                        TakeshiHRI::waitAfterSay("Human. Please take the object... ",1000);
                        //TakeshiManip::armGoToDeliverObjectInFloor(5000);
                        TakeshiHRI::waitAfterSay("I am going to release the object...",500);
                        ros::Duration(0.5).sleep();
                        TakeshiManip::openGripper(1.0);
                        ros::Duration(2.0).sleep();//wait to open
                        TakeshiHRI::waitAfterSay("Thank you human...",1000);
                        TakeshiManip::navigationPose(300);

                        /*std::vector<float> articular;
                        articular.push_back( 0.0);
                        articular.push_back(0.0);
                        articular.push_back(0.0);
                        TakeshiManip::startArmGoToArticular(articular);*/
                        TakeshiManip::armGoToNavigation();
                        TakeshiManip::closeGripper(1.0);
                        ic.startRoutine(true);
                        TakeshiHRI::enableSphinxMic(true);

                        TakeshiHRI::waitAfterSay("I will navigate to the starting point for the next group", 3000);
                        TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                        TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                        TakeshiHRI::waitAfterSay("what do you need?, Please stand in front of me and point to the object in the next group", 3000);
                        TakeshiHRI::waitAfterSay("Say takeshi yes when you are ready", 3000);
                        //TakeshiHRI::enableSphinxMic(false); Needed for find pickup, so it's not turned off
                        nextState=SM_FIND_PICKUP;
                        //RESTART NEXT GROUP

                    } else {
                        try_no++;
                        if(try_no >= 1){
                            try_no = 0;
                            TakeshiHRI::waitAfterSay("I give up",1000);

                            //TakeshiManip::armGoToDeliverObjectInFloor(5000);
                            TakeshiHRI::waitAfterSay("Ok, I will try again",1000);
                            TakeshiNavigation::startMoveDist(-0.2);
                            TakeshiManip::startHdGoTo(0.0, 0.0);
                            TakeshiManip::startTorsoGoTo(0.5);
                            ros::Duration(1.0).sleep();
                            TakeshiManip::armGoToArticular(0.0, 0.0, -1.4, 0.0, 300);
                            TakeshiHRI::waitAfterSay("Human. Please take the object... ",1000);
                            //TakeshiManip::armGoToDeliverObjectInFloor(5000);
                            TakeshiHRI::waitAfterSay("I am going to release the object...",500);
                            ros::Duration(0.5).sleep();
                            TakeshiManip::openGripper(1.0);
                            ros::Duration(2.0).sleep();//wait to open
                            TakeshiHRI::waitAfterSay("Thank you human...",1000);
                            TakeshiManip::navigationPose(300);
                            //TakeshiNavigation::moveDist(-0.5, 3000);
                            /*std::vector<float> articular;
                            articular.push_back( 0.0);
                            articular.push_back(0.0);
                            articular.push_back(0.0);
                            TakeshiManip::startArmGoToArticular(articular);*/
                            
                            ros::Rate loop(10);
                            TakeshiManip::navigationPose(5000);
                            ros::spinOnce();
                            loop.sleep();

                            TakeshiManip::closeGripper(1.0);
                        ic.startRoutine(true);
                        TakeshiHRI::enableSphinxMic(true);

                        TakeshiHRI::waitAfterSay("I will navigate to the starting point for the next group", 3000);
                        TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                        TakeshiNavigation::getClose("carry_luggage",25000);//uncomment
                        TakeshiHRI::waitAfterSay("what do you need?, Please stand in front of me and point to the object in the next group", 3000);
                        TakeshiHRI::waitAfterSay("Say takeshi yes when you are ready", 3000);
                        //TakeshiHRI::enableSphinxMic(false); Needed for find pickup, so it's not turned off
                        nextState=SM_FIND_PICKUP;
                        }

                        TakeshiHRI::waitAfterSay("Ok, I will try again",1000);
                        TakeshiNavigation::startMoveDist(-0.2);
                        TakeshiManip::startHdGoTo(0.0, 0.0);
                        TakeshiManip::startTorsoGoTo(0.5);
                        ros::Duration(1.0).sleep();
                        TakeshiManip::armGoToArticular(0.0, 0.0, -1.4, 0.0, 300);
                        TakeshiHRI::waitAfterSay("Human. Please take the object... ",1000);
                        //TakeshiManip::armGoToDeliverObjectInFloor(5000);
                        TakeshiHRI::waitAfterSay("I am going to release the object...",500);
                        ros::Duration(0.5).sleep();
                        TakeshiManip::openGripper(1.0);
                        ros::Duration(2.0).sleep();//wait to open
                        TakeshiHRI::waitAfterSay("Thank you human...",1000);
                        TakeshiManip::navigationPose(300);
                        //TakeshiNavigation::moveDist(-0.5, 3000);
                        /*std::vector<float> articular;
                        articular.push_back( 0.0);
                        articular.push_back(0.0);
                        articular.push_back(0.0);
                        TakeshiManip::startArmGoToArticular(articular);*/
                        
                        ros::Rate loop(10);
                        TakeshiManip::navigationPose(5000);
                        ros::spinOnce();
                        loop.sleep();

                        TakeshiManip::closeGripper(1.0);
                              TakeshiNavigation::getClose(location,25000);
                              nextState = SM_FIND_OBJECTS_TABLE;


                    }
                    TakeshiHRI::loadJSGFGrammar(grammarCommands);
                }

                        break;
                case SM_MISSION_COMPLETE:
                        success= true;
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
        std::cout << "        CASE: "<< st << std::endl << std::endl;
}
