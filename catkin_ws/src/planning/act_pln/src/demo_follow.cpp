#include "ros/ros.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiNavigation.h"

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
        bool userConfirmation=false;

        string lastRecoSpeech;
        std::vector<std::string> validCommandsStop;
        validCommandsStop.push_back("pick up the object");
        validCommandsStop.push_back("follow me");
        validCommandsStop.push_back("this is the dining table");
        validCommandsStop.push_back("deliver object to the living room");
        validCommandsStop.push_back("take it to the dining table");
        
        int nextState=0;

        ros::Rate rate(10);
        nextState = SM_INIT_FOLLOW;

        std::vector<vision_msgs::VisionObject> recognizedObjects;
        vision_msgs::VisionObject objToGrasp;

        std::stringstream takeshi_say;
        geometry_msgs::Pose poseToGrasp;
        bool success = false;
        TakeshiHRI::enableSpeechRecognized(true);
        TakeshiVision::startQRReader();
        TakeshiHRI::loadGrammarSpeechRecognized("demo_noviembre.xml");
        TakeshiHRI::waitAfterSay("Hello, my name is takeshi", 4000);
        //TakeshiVision::loadSpecificTrainingDir("dining");
        
                        

        while (ros::ok() && !success) {
                switch (nextState) {
                
                case SM_INIT_FOLLOW:
                        cout << "State machine: SM_INIT_FOLLOW" << endl;
                        TakeshiManip::navigationPose(4000);
                        TakeshiHRI::enableSpeechRecognized(true);
                        ros::Duration(2.0).sleep();
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                        {
                                if(lastRecoSpeech.find("follow me") != std::string::npos) {
                                        TakeshiHRI::enableSpeechRecognized(false);
                                        nextState=SM_NAVIGATE_FOLLOW;
                                }
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
                                TakeshiHRI::enableSpeechRecognized(true);
                                nextState = SM_FOLLOWING_PHASE;
                        }

                        break;

                case SM_FOLLOWING_PHASE:
                        cout << "SM: SM_FOLLOWING_PHASE" <<  endl;
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                                if(lastRecoSpeech.find("this is the dining table") != std::string::npos) {
                                        TakeshiHRI::enableSpeechRecognized(false);
                                        rate.sleep();
                                        ros::spinOnce();
                                        TakeshiHRI::waitAfterSay("Ok", 2500);
                                        rate.sleep();
                                        ros::spinOnce();
                                        TakeshiHRI::enableSpeechRecognized(true);
                                        TakeshiHRI::stopFollowHuman();
                                        TakeshiHRI::enableLegFinder(false);
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
                                nextState=SM_PLACE_OBJ;
                        }
                        else{
                                TakeshiHRI::waitAfterSay("Ok, continue", 4000);
                                TakeshiHRI::loadGrammarSpeechRecognized("demo_noviembre.xml");
                                nextState=SM_FOLLOWING_PHASE;
                        }
                        break;

                }

                rate.sleep();
                ros::spinOnce();
        }

        return 0;

}