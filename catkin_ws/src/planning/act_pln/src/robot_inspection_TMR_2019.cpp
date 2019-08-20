#include <iostream>
#include "ros/ros.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiKnowledge.h"

enum state {
        SM_INIT,
        SM_WAIT_DOOR,       
        SM_GO_TO_INSPECTION,
        SM_WAIT_FOR_COMMAND,
        SM_PARSE_SPOKEN_COMMAND, 
        SM_REPEAT_COMMAND,
        SM_FINAL_STATE,
        SM_FINISHED, 
        SM_WAIT_FOR_CONFIRMATION, 
        SM_PARSE_SPOKEN_CONFIRMATION
};


int main(int argc, char** argv) {
    std::cout << "INITIALIZING ROBOT INSPECTION TEST" << std::endl;
    ros::init(argc, argv, "act_pln");

    ros::NodeHandle n;
    TakeshiHRI::setNodeHandle(&n);
    TakeshiNavigation::setNodeHandle(&n);
    TakeshiVision::setNodeHandle(&n);  
    TakeshiKnowledge::setNodeHandle(&n); 

    ros::Rate loop(10);

    int nextState = SM_INIT;
    bool success = false;
    std::string lastRecoSpeech;

    std::vector<std::string> validCommands;
    std::string inspection_point = "kitchen";
    validCommands.push_back("finish");
    //validCommands.push_back("takeshi yes");
    //validCommands.push_back("takeshi no");
    bool userConfirmation = false;  
    int attempts=0;
    //TakeshiHRI::enableSpeechRecognized(false);
    //TakeshiHRI::loadGrammarSpeechRecognized("robot_inspection.xml");
    TakeshiHRI::enableSphinxMic(true);
    TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/robot_inspection.jsgf", "robot_inspection");
    
    while(ros::ok() && !success) {

        switch(nextState) {

            case SM_INIT:
                cout << "SM_INIT" << endl;
                TakeshiHRI::enableSphinxMic(false);
                //TakeshiHRI::say("I am ready");
                /* while(!TakeshiHRI::initTest()){
                    ros::Duration(0.5).sleep();
                    ros::spinOnce();
                }*/
                
                TakeshiHRI::waitAfterSay("I am ready to begin, I will wait for the door to be opened", 5000);
                nextState = SM_WAIT_DOOR;
                //nextState = SM_INIT;
                break;

            case SM_WAIT_DOOR:
                if(!TakeshiNavigation::obstacleInFront())
                    nextState = SM_GO_TO_INSPECTION;
                break;

            case SM_GO_TO_INSPECTION:

                TakeshiHRI::waitAfterSay("Now the door is open, I will go to inspection point", 4000);
                TakeshiNavigation::moveDist(2.5,2000);                               
                if(!TakeshiNavigation::getClose(inspection_point, 20000))
                    if(!TakeshiNavigation::getClose(inspection_point, 20000))
                        TakeshiNavigation::getClose(inspection_point, 20000);

                TakeshiHRI::waitAfterSay("I arrived to inspection point. Tell me finish to go to exit and end the test", 6000);                            
                TakeshiVision::startQRReader();
                TakeshiHRI::enableSphinxMic(true);
                nextState=SM_WAIT_FOR_COMMAND;
                //TakeshiHRI::enableSpeechRecognized(true);
                break;

            case SM_WAIT_FOR_COMMAND:                
                if(TakeshiHRI::waitForSpecificSentence(validCommands, lastRecoSpeech, 12000)){
                    if(lastRecoSpeech.find("finish") != std::string::npos) {
                        TakeshiHRI::waitAfterSay("Please, say Takeshi yes to confirm",4000);
                        nextState = SM_WAIT_FOR_CONFIRMATION;
                    } 
                    else {
                        TakeshiHRI::waitAfterSay("I can not understand you, Please repeat the command", 2000);
                    }
                }
                else{
                    attempts++;
                    if(attempts > 5){
                       TakeshiHRI::waitAfterSay("I can not understand you, Please repeat the command", 2000); 
                       attempts=0;
                    }
                }
            break;
                    

            case SM_WAIT_FOR_CONFIRMATION:   
                ros::spinOnce();
                TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000);             
                if(userConfirmation){
                    TakeshiHRI::waitAfterSay("I am finishing the robot inspection test", 3000);                        
                    TakeshiVision::stopQRReader();
                    TakeshiHRI::enableSphinxMic(false);
                    TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/robot_inspection.jsgf", "robot_inspection");
                    nextState = SM_FINAL_STATE;
                }
                else {
                     nextState = SM_WAIT_FOR_COMMAND;
                     TakeshiHRI::waitAfterSay("Ok, Please repeat the command", 2000); 
                     TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/robot_inspection.jsgf", "robot_inspection");
                 }
                break;     

            case SM_FINAL_STATE:
                TakeshiHRI::waitAfterSay("I am going to the exit", 2000);                
                if(!TakeshiNavigation::getClose("exit", 30000))
                    if(!TakeshiNavigation::getClose("exit", 30000))
                        TakeshiNavigation::getClose("exit", 30000);

                nextState = SM_FINISHED;
                break;

            case SM_FINISHED:
                TakeshiHRI::say("I have finished robot inspection test");
                success = true;
            break;
                
        }
        ros::spinOnce();
        loop.sleep();
    }

    return 0;
}
