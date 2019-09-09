////////////////////////////////////////////////////////
// Note: this code was commented into CMake file,
// If you are brave enough to edit this code please
// make sure to uncomment this code into CMakeList.txt
///////////////////        EDD-II    ////////////////////

#include "ros/ros.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiManip.h"

enum state {
        SM_START,
        SM_FIND_OBJ,
        SM_GRASP_OBJ_FLOOR,
        SM_INIT_FOLLOW,
        SM_FOLLOW_ME,
        SM_FOLLOWING_PHASE,
        SM_INIT_FOLLOW_CONFIRM,
        SM_NAVIGATE_FOLLOW,
        SM_FOLLOW_CONFIRMATION,
        SM_PLACE_OBJ,
        SM_WAIT_ORDER,
        SM_FIND_OBJ_TABLE,
        SM_GRASP_OBJ_HAND,
        SM_GRASP_OBJ_TABLE,
        SM_FIND_PERSON,
        SM_GOTO_DELIVERY,
        SM_RELEASE_OBJECT
};

void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        CASE: "<< st << "\033[0m" << std::endl;
}


// This is for the attemps for a actions
std::string lastCmdName = "";
int numberAttemps = 0;

int main(int argc, char **argv) {

        ros::init(argc, argv, "demo18");
        ros::NodeHandle n;
        std::string locationsFilePath = "";

        TakeshiHRI::setNodeHandle(&n);
        TakeshiTasks::setNodeHandle(&n);
        TakeshiManip::setNodeHandle(&n);
        bool userConfirmation=false;
        
        string lastRecoSpeech;
        std::vector<std::string> validCommandsStop;
        validCommandsStop.push_back("pick up the objects");
        validCommandsStop.push_back("follow me");
        validCommandsStop.push_back("this is the kitchen table");
        validCommandsStop.push_back("deliver object to the living room");
        validCommandsStop.push_back("take it to the kitchen table");
        
        int nextState=0;

        ros::Rate rate(10);
        nextState = SM_START;

        std::vector<vision_msgs::VisionObject> recognizedObjects;
        vision_msgs::VisionObject objToGrasp;

        std::stringstream takeshi_say;
        geometry_msgs::Pose poseToGrasp;
        bool success = false;
        TakeshiVision::startQRReader();

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

        std::vector<std::string> mugObjects;
        mugObjects.push_back("purple_mug");
        mugObjects.push_back("red_mug");
        mugObjects.push_back("green_mug");

        vision_msgs::ObjectCoordinatesForDetection objectsCoordinates;
        objectsCoordinates=TakeshiVision::objectCoordinates;
        objectsCoordinates.z_max=0.3;
        unsigned int maxDetects =3, detectTries=0;
        //TakeshiVision::loadSpecificTrainingDir("dining");  }
       
        TakeshiHRI::waitAfterSay("Hello, my name is takeshi", 4000);
        TakeshiHRI::enableSphinxMic(true);
        TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/final_tmr.jsgf", "final_tmr");
        
        while (ros::ok() && !success) {
            switch (nextState) {
                
                case SM_START:
                    printState("¡¡¡¡SM START!!!!!!");
                    TakeshiHRI::enableSphinxMic(true);
                    if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                        if(lastRecoSpeech.find("pick up the objects") != std::string::npos) {
                                TakeshiHRI::enableSphinxMic(false);
                                TakeshiHRI::waitAfterSay("I am looking for objects on the floor", 2500);
                                nextState= SM_FIND_OBJ;
                        } 
                    break;

                case SM_FIND_OBJ:
                        printState("Finding objects on location");
                        TakeshiManip::hdGoTo(0.0,-1.0, 4000);
                        if(TakeshiVision::detectSpecificYoloObject(trashObjects,recognizedObjects,1000, objectsCoordinates)){
                                nextState = SM_GRASP_OBJ_FLOOR;
                        }
                        else{
                            if (detectTries>=maxDetects) {
                                TakeshiHRI::waitAfterSay( "I can not see the object",2000);
                                TakeshiHRI::waitAfterSay( "what do you want me to do now?",2000);
                                TakeshiHRI::enableSphinxMic(true);  
                                detectTries=0;    
                                nextState = SM_START;       
                            }
                            else  
                                detectTries++;
                        }
                        break;

                case SM_GRASP_OBJ_FLOOR:
                        printState("Grasping objects floor");
                        objToGrasp = recognizedObjects[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I am grasping the object " << objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::say( takeshi_say.str());
                        TakeshiManip::hdGoTo(0,0.0,5000);
                        if(TakeshiTasks::graspObjectOnFloorFromAbove(
                                   poseToGrasp.position.x,
                                   poseToGrasp.position.y,
                                   poseToGrasp.position.z,
                                   0.0,
                                   false)){

                                TakeshiHRI::say("I'm verifying if I grasped the object");
                                TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                                TakeshiNavigation::moveDist(-0.2, 3000);
                                ros::Duration(2).sleep();
                                if(!TakeshiVision::detectYoloObject(objToGrasp.id,objToGrasp,1000,objectsCoordinates)){
                                    TakeshiHRI::say( "I took the object");
                                    TakeshiHRI::waitAfterSay("Where do i put this object?", 3000);
                                    TakeshiHRI::enableSphinxMic(true);
                                    nextState = SM_INIT_FOLLOW_CONFIRM;
                                }
                                else{
                                    TakeshiHRI::say( "I could not take the object");    
                                    nextState=SM_FIND_OBJ;
                                }
                        }
                        else
                            nextState=SM_FIND_OBJ;
                        break;

                 case SM_INIT_FOLLOW_CONFIRM:
                 		cout << "State machine: SM_INIT_FOLLOW_CONFIRM" << endl;
                        TakeshiManip::navigationPose(4000);
                        ros::Duration(2.0).sleep();
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                                if(lastRecoSpeech.find("take it to the kitchen table") != std::string::npos) {
                                        TakeshiHRI::enableSphinxMic(false);
                                        TakeshiHRI::waitAfterSay("Where is the kitchen table?", 4000);
                                        nextState=SM_INIT_FOLLOW;
                                }                 	 
                        break;

                case SM_INIT_FOLLOW:
                        cout << "State machine: SM_INIT_FOLLOW" << endl;
                        TakeshiManip::navigationPose(4000);
                        TakeshiHRI::enableSphinxMic(true);
                        ros::Duration(2.0).sleep();
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                            if(lastRecoSpeech.find("follow me") != std::string::npos) {
                                TakeshiHRI::enableSpeechRecognized(false);
                                nextState=SM_NAVIGATE_FOLLOW;
                            }
                        break;

                case SM_NAVIGATE_FOLLOW:
                        cout << "State machine: SM_NAVIGATE_FOLLOW" << endl;
                        TakeshiHRI::waitAfterSay("I will follow you Human", 4000);
                        TakeshiHRI::enableLegFinder(true);
                        nextState=SM_FOLLOW_ME;
                        break;

                case SM_FOLLOW_ME:
                        cout << "SM: SM_FOLLOW_ME" << endl;
                        if(TakeshiHRI::frontalLegsFound()) {
                                cout << "Frontal legs found!" << std::endl;
                                TakeshiHRI::waitAfterSay("I found you", 4000);
                                TakeshiHRI::startFollowHuman();
                                ros::spinOnce();
                                rate.sleep();
                                TakeshiHRI::startFollowHuman();
                                TakeshiHRI::enableSphinxMic(true);
                                nextState = SM_FOLLOWING_PHASE;
                        }
                        break;

                case SM_FOLLOWING_PHASE:
                        cout << "SM: SM_FOLLOWING_PHASE" <<  endl;
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                            if(lastRecoSpeech.find("this is the kitchen table") != std::string::npos) {
                                TakeshiHRI::enableSphinxMic(false);
                                rate.sleep();
                                ros::spinOnce();
                                TakeshiHRI::waitAfterSay("is this the kitchen table?", 2500);
                                rate.sleep();
                                ros::spinOnce();
                                TakeshiHRI::enableSphinxMic(true);
                                nextState= SM_FOLLOW_CONFIRMATION;
                            }
                        break;

                case SM_FOLLOW_CONFIRMATION:
                        TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000);
                        rate.sleep();
                        ros::spinOnce();
                        if(userConfirmation) {
                            TakeshiHRI::stopFollowHuman();
                            TakeshiHRI::enableLegFinder(false);
                            TakeshiHRI::waitAfterSay("Ok", 1000);
                            userConfirmation=false;
                            TakeshiManip::hdGoTo(0.0, 0.0,2000);
                            //TakeshiNavigation::moveDistAngle(0.0, -3.1415, 3000);
                            TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/final_tmr.jsgf", "final_tmr");
                            nextState=SM_PLACE_OBJ;
                        }
                        else{
                            TakeshiHRI::waitAfterSay("Ok, continue", 4000);
                            TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/final_tmr.jsgf", "final_tmr");
                            //TakeshiHRI::loadGrammarSpeechRecognized("demo_noviembre.xml");
                            nextState=SM_FOLLOWING_PHASE;
                        }
                        break;

                case SM_PLACE_OBJ:
                        TakeshiNavigation::moveDistAngle(0.0, 1.5707, 4000);
                        if(TakeshiTasks::placeObject(0.05,1.6,false)){                                
	                        TakeshiHRI::waitAfterSay("Tell me what you need",10);	
                            TakeshiNavigation::moveDistAngle(0.0, -1.5707, 3000);
                            nextState = SM_WAIT_ORDER;
                        }
                        break;
                case SM_WAIT_ORDER:
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                            if(lastRecoSpeech.find("deliver object to the living room") != std::string::npos) {
                                TakeshiHRI::waitAfterSay("I will take the object", 2500);
                                detectTries=0;
                                nextState= SM_FIND_OBJ_TABLE;
                                //nextState= SM_GRASP_OBJ_HAND;
                            }
                        break;

                case SM_GRASP_OBJ_HAND:
                       //TakeshiTasks::graspObjectHand();
                       nextState=SM_GOTO_DELIVERY;
                break;


                case SM_FIND_OBJ_TABLE:
                        printState("Finding objects on location");
                        takeshi_say.str(std::string());
                        takeshi_say << "I am finding objects on location: table";
                        TakeshiNavigation::moveDistAngle(0.0, 1.5707, 4000);
                        TakeshiHRI::say(takeshi_say.str() );
                        TakeshiTasks::alignWithTable(0.5, false);
                        objectsCoordinates.z_max=1.7;

                        if(TakeshiVision::detectSpecificYoloObject(mugObjects,recognizedObjects,1000, objectsCoordinates)){
                                nextState = SM_GRASP_OBJ_TABLE;
                        }
                        else{
                            if (detectTries>=maxDetects) {
                                TakeshiHRI::waitAfterSay( "I can not see the object",2000);
                                TakeshiHRI::enableSphinxMic(true);  
                                detectTries=0;    
                                nextState = SM_FIND_OBJ_TABLE;       
                            }
                            else  
                                detectTries++;
                        }
                        break;

                case SM_GRASP_OBJ_TABLE:
                        printState("Grasping objects table");
                        objToGrasp = recognizedObjects[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I am grasping the "<< objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::say( takeshi_say.str());
                        TakeshiManip::hdGoTo(0,0.0,5000);

                        if(TakeshiTasks::graspObjectLateral(
                                   poseToGrasp.position.x,
                                   poseToGrasp.position.y,
                                   poseToGrasp.position.z,
                                   false)){

                                nextState = SM_GOTO_DELIVERY;
                        }
                        else
                            nextState=SM_FIND_OBJ_TABLE;
                        


                case SM_GOTO_DELIVERY:
                        TakeshiHRI::waitAfterSay("I will deliver this to someone in the living room",10);
                        if (TakeshiNavigation::getClose("living_room",100000))
                            nextState=SM_FIND_PERSON;
                        break;

                case SM_FIND_PERSON:
                        TakeshiHRI::say("Hello Human, i will find you");
                        if(TakeshiTasks::turnAndRecognizeFacenet("", true))
                            nextState=SM_RELEASE_OBJECT;                       
                        break;

                case SM_RELEASE_OBJECT:
                        //Relase object task
                        TakeshiManip::hdGoTo(0,0,5000);
                        TakeshiTasks::giveObjectToHuman();
                        TakeshiManip::navigationPose(5000);
                        TakeshiVision::stopQRReader();
                        success=true;
                        TakeshiHRI::say("I finished my demostration, thank you for your attention");
                        break;
                }
                rate.sleep();
                ros::spinOnce();
        }
        return 0;
}
