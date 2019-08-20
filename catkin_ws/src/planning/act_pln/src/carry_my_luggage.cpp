#include <iostream>
#include "ros/ros.h"
#include "hri_msgs/RecognitionResult.h"

#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiHardware.h"

#include "std_msgs/Bool.h"
#include "string"
#include <sensor_msgs/LaserScan.h>
#include "geometry_msgs/PointStamped.h"

using namespace std;


enum state {
        SM_START,
        SM_INSTRUCTIONS,
        SM_WAIT_FOR_INSTRUCTION_COMMAND,
        SM_SEARCH_PERSON,
        SM_GRASP_BAG,
        SM_WAIT_DOOR,
        SM_TAKE_BAG,
        SM_MEMORIZING_OPERATOR,
        SM_WAIT_FOR_LEGS_FOUND,
        SM_FOLLOWING_PHASE,
        SM_FOLLOW_OBSTACLE,
        SM_DELIVER_OBJECT,
        SM_RETURN_THE_ARENA,
        SM_FINISH
};

void printState(std::string st){
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        STATE MACHINE: "<< st << "\033[0m" << std::endl;
}

sensor_msgs::LaserScan laser;
std::vector<float> laser_ranges;
bool door_isopen=false;
bool door_loc=false;
bool obstacleInFront=false;

int range=0,range_i=0,range_f=0,range_c=0,cont_laser=0;
float laser_l=0;
float leg_x=0, leg_y=0, leg_z=0;
float outX,outY,outZ;

int main(int argc, char** argv)
{
    std::cout << "INITIALIZING CARRY MY LUGGAGE TEST..." << std::endl;
    ros::init(argc, argv, "act_pln");
    ros::NodeHandle n;
        
    bool fail = false;
    bool success = false;
    ros::Rate loop(10);

    
    int attemps=0;
    std::stringstream ss;
    std::vector<std::string> tokens;
    int attemptsRecogLoc = 0;
    int attemptsConfLoc = 0;
    string lastRecoSpeech;
    string location="entrance";


    TakeshiHRI::setNodeHandle(&n);
    TakeshiManip::setNodeHandle(&n);
    TakeshiKnowledge::setNodeHandle(&n);
    TakeshiNavigation::setNodeHandle(&n);
    TakeshiTasks::setNodeHandle(&n);
    TakeshiHardware::setNodeHandle(&n);

    std::vector<std::string> validCommandsInstruction;
    validCommandsInstruction.push_back("help me");
    validCommandsInstruction.push_back("take the bag");

    std::vector<std::string> validCommandsStop;
    validCommandsStop.push_back("here is the car");
    validCommandsStop.push_back("stop follow me");

    //std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
    vision_msgs::VisionFaceObjects lastRecognizedFaces;
    bool start_follow=false;
    bool userConfirmation = false;    

    int nextState = SM_START;    
    //ros::Subscriber laser_subscriber;
    
    TakeshiHRI::enableSphinxMic(true);
    TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/carry_my_luggage_grammar.jsgf", "carry_my_luggage");

    while(ros::ok() && !fail && !success)
    {
        switch(nextState)
        {  
            
            case SM_START:
                printState("SM_INIT");
                TakeshiHRI::enableSphinxMic(false);
                TakeshiHRI::enableLegFinder(false); 
                TakeshiManip::navigationPose(4000); 
                TakeshiHRI::say("waitting for the door to be open");
                nextState=SM_WAIT_DOOR;
            break;

            case SM_WAIT_DOOR:
                printState("wait for the door");
                if(!TakeshiNavigation::obstacleInFront()){
                    TakeshiHRI::say("I'm ready for carry my luggage test, i will navigate to initial point");
                    TakeshiNavigation::moveDist(2.0, 6000);
                    ros::Duration(1.0).sleep();
                    TakeshiNavigation::getClose("carry_luggage", 30000);
                    TakeshiManip::hdGoTo(0.0, 0.5, 5000);
                    attemps=0;
                    nextState = SM_SEARCH_PERSON;
                }
            break;
                
            case SM_INSTRUCTIONS:
                printState("SM_INSTRUCTIONS");
                TakeshiHRI::waitAfterSay("Please say ... help me, for me to take the bag", 15000);
                TakeshiHRI::enableSphinxMic(true);
                nextState=SM_WAIT_FOR_INSTRUCTION_COMMAND;
            break;    
            
            case SM_WAIT_FOR_INSTRUCTION_COMMAND:
                printState("SM_WAIT_FOR_OPERATOR");
                if(TakeshiHRI::waitForSpecificSentence(validCommandsInstruction,lastRecoSpeech,7000)){
                    if(lastRecoSpeech.find("help me") != std::string::npos){
                        TakeshiHRI::enableSphinxMic(false);
                        
                        nextState = SM_SEARCH_PERSON;
                    }
				}
                else                    
                    attemps++;    		

                if(attemps==4){
                    TakeshiHRI::waitAfterSay("Please repeat the command ... help me", 2000);
                    //attemps=0;
                }
                if(attemps>6){
                    nextState = SM_SEARCH_PERSON;
                }

            break;

            case SM_SEARCH_PERSON:
                printState("SM_SEARCH_PERSON");
                TakeshiHRI::waitAfterSay("Hello human, please, stand in front of me",3000);
                //lastRecognizedFaces = TakeshiVision::getFaces("").recog_faces;
                lastRecognizedFaces=TakeshiVision::facenetRecognize("");
                if(lastRecognizedFaces.recog_faces.size() > 0){
                    TakeshiHRI::waitAfterSay("ok, i see you",1500);
                    TakeshiManip::hdGoTo(0.0, 0.0, 5000);
                    TakeshiVision::stopFaceRecognition();  
                    attemps=5;
                    nextState=SM_GRASP_BAG;  
                }
                attemps++;
                if(attemps > 3){
                    TakeshiHRI::waitAfterSay("ok, i see you",1500);
                    TakeshiManip::hdGoTo(0.0, 0.0, 5000);
                    TakeshiVision::stopFaceRecognition();  
                    attemps=5;
                    nextState=SM_GRASP_BAG;  
                }

                
            break;

            case SM_TAKE_BAG:
                printState("SM_TAKE_BAG");
                if(attemps > 5){
                    TakeshiHRI::waitAfterSay("Ok",3000);
                    TakeshiHRI::enableSphinxMic(false);
                    attemps=0;
                    TakeshiManip::closeGripper(0.5);
                    nextState=SM_MEMORIZING_OPERATOR;
                }                
                if(TakeshiHRI::waitForSpecificSentence(validCommandsInstruction,lastRecoSpeech,7000)){
                    if(lastRecoSpeech.find("take the bag") != std::string::npos){
                        TakeshiHRI::waitAfterSay("Ok",3000);
                        TakeshiHRI::enableSphinxMic(false);
                        attemps=0;
                        TakeshiManip::closeGripper(0.5);
                        TakeshiHRI::waitAfterSay("Now I will follow you",3000);
                        TakeshiManip::navigationPose(4000); 
                        nextState=SM_MEMORIZING_OPERATOR;                    
                    }
                }
                else
                    attemps++;                             
            break;

            case SM_GRASP_BAG:
                    
                    if(!TakeshiTasks::graspThePointingBag(3)){
                        TakeshiHRI::waitAfterSay("Sorry, I cant take the bag, please put the bag in my hand, after that , tell me ... take the bag",3000);
                        TakeshiManip::armGoToGetObjects(4000);
                        attemps=0;
                        TakeshiHRI::enableSphinxMic(true);
                        nextState=SM_TAKE_BAG;
                    }
                    else{
                        TakeshiManip::navigationPose(4000); 
                        TakeshiHRI::waitAfterSay("Now I will follow you",3000);
                        nextState=SM_MEMORIZING_OPERATOR;
                    }
            break;
            
            case SM_MEMORIZING_OPERATOR:
                printState("SM_MEMORIZING_OPERATOR");                             
                if(!start_follow){
                    TakeshiHRI::waitAfterSay("Human, please stand in front of me",3500);
                    TakeshiHRI::enableLegFinder(true);
                    attemps=0;
                }
                else
                    TakeshiHRI::enableLegFinder(true);    
                nextState=SM_WAIT_FOR_LEGS_FOUND;
            break;

            case SM_WAIT_FOR_LEGS_FOUND:
                printState("SM_WAIT_FOR_LEGS_FOUND");  
                if(attemps > 50){
                    TakeshiHRI::waitAfterSay("Human, please stand in front of me",3500);
                    attemps=0;
                }

                if(TakeshiHRI::frontalLegsFound()){
                    if(start_follow){
                        cout << "Frontal legs found!" << std::endl;
                        TakeshiHRI::waitAfterSay("I found you, please walk.", 3000);
                        TakeshiHRI::startFollowHuman();
                        TakeshiHRI::enableSphinxMic(true);
                        nextState = SM_FOLLOWING_PHASE;
                    }
                    else{
                        std::cout << "NavigTest.->Frontal legs found!" << std::endl;
                        TakeshiHRI::waitAfterSay("I found you, when we get to the car tell me, here is the car, or, stop follow me. For confirmation tell me, takeshi yes, or, takeshi no",3000);
                        TakeshiHRI::say("Now,  I will start to follow you human, please walk.");
                        TakeshiHRI::startFollowHuman();
                        TakeshiHRI::enableSphinxMic(true);
                        start_follow=true;
                        nextState = SM_FOLLOWING_PHASE;                        
                    }
                }
                attemps++;
                
                break;  

            case SM_FOLLOWING_PHASE:
                printState("SM_FOLLOWING_PHASE");    
                
                if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000)){
                    TakeshiHRI::enableSphinxMic(false);
                    ros::spinOnce();
                    TakeshiHRI::waitAfterSay("is this the car location", 2500);
                    ros::spinOnce();
                    TakeshiHRI::enableSphinxMic(true);
                    ros::spinOnce();
                    TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000);
                    if(userConfirmation){
                        TakeshiHRI::stopFollowHuman();
                        TakeshiHRI::enableLegFinder(false);
                        TakeshiHRI::waitAfterSay("I stopped", 1000);
                        userConfirmation=false;
                        TakeshiManip::hdGoTo(0.0, 0.0,2000);
                        attemps=8;
                        nextState = SM_DELIVER_OBJECT;
                        break;
                    }
                    else {
                        TakeshiHRI::waitAfterSay("Ok, please walk.",2000);
                        TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/carry_my_luggage_grammar.jsgf", "carry_my_luggage");
                    }
                }                
                if(!TakeshiHRI::frontalLegsFound()){
                    cout << "State machine: SM_FOLLOWING_PHASE -> Lost human!" << std::endl;
                    TakeshiHRI::waitAfterSay("I lost you, please stand in front of me again", 3500);
                    TakeshiHRI::stopFollowHuman();
                    TakeshiHRI::enableLegFinder(false);
                    nextState=SM_MEMORIZING_OPERATOR;
                }        
                break;

            case SM_DELIVER_OBJECT:
                    printState("SM_DELIVER_OBJECT");    
                    TakeshiHRI::waitAfterSay("I will deliver the object", 3500);
                    if(!TakeshiTasks::giveObjectToHuman()){
                        //if(!TakeshiTasks::giveObjectToHuman())
                          //  if(!TakeshiTasks::giveObjectToHuman()){
                                TakeshiManip::armGoToGetObjects(4000);
                                TakeshiHRI::waitAfterSay("Take the object", 2000);
                                TakeshiManip::openGripper(1.0);
                                ros::Duration(7).sleep();
                                TakeshiManip::navigationPose(4000);
                          //
                            }
                    TakeshiManip::navigationPose(4000);
                    TakeshiManip::openGripper(0.0);
                    nextState=SM_RETURN_THE_ARENA;
            break;

            case SM_RETURN_THE_ARENA:
                printState("SM_RETURN_THE_ARENA");  
                TakeshiHRI::waitAfterSay("I will return to the arena", 3500);
                if(!TakeshiNavigation::getClose("living_room",100000))
                    if(!TakeshiNavigation::getClose("living_room",100000))
                        TakeshiNavigation::getClose("living_room",100000);
                nextState=SM_FINISH;
            break;

            case SM_FINISH:
                printState("SM_FINISH");  
                TakeshiHRI::waitAfterSay("I finished the test", 3500);
                success=true;
            break;
        }

        ros::spinOnce();
        loop.sleep();
    }
    return 1;
}
