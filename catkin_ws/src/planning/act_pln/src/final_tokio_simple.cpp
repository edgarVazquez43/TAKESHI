#include "ros/ros.h"

#include "takeshi_tools/TakeshiHardware.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiRepresentation.h"

void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "        CASE: "<< st << std::endl << std::endl;
}

enum state {
        SM_INIT,
        SM_INIT_FOLLOW,
        SM_INI
};

int main(int argc, char **argv) {

        ros::init(argc, argv, "final_challenge_tokio_test");
        ros::NodeHandle n;

        TakeshiHRI::setNodeHandle(&n);
        TakeshiHardware::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiManip::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiTasks::setNodeHandle(&n);
        TakeshiTools::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);
        TakeshiRepresentation::setNodeHandle(&n);
        TakeshiHRI::setNodeHandle(&n);
        TakeshiTasks::setNodeHandle(&n);
        bool userConfirmation=false;

        string lastRecoSpeech;
        std::vector<std::string> validCommandsStop;
        validCommandsStop.push_back("this is the kitchen table");
        validCommandsStop.push_back("give me the bag");
        ros::Rate rate(10);
        int nextstate = SM_INIT_FOLLOW;

        while (ros::ok()) {
                switch (state) {
                case SM_INIT_FOLLOW:

                        cout << "State machine: SM_INIT" << endl;
                        TakeshiHRI::waitAfterSay("Hello, my name is takeshi", 4000);
                        TakeshiHRI::enableLegFinder(false);
                        TakeshiHRI::enableSpeechRecognized(false);
                        state=SM_NAVIGATE_FOLLOW;
                        break;

                case SM_NAVIGATE_FOLLOW:
                        cout << "State machine: SM_NAVIGATE_FOLLOW" << endl;
                        TakeshiHRI::waitAfterSay("I will follow you Human", 4000);
                        TakeshiHRI::enableLegFinder(true);
                        state=SM_FOLLOW_ME;
                        break;

                case SM_FOLLOW_ME:
                        cout << "SM: SM_FOLLOW_ME" << endl;
                        if(TakeshiHRI::frontalLegsFound()) {
                                cout << "Frontal legs found!" << std::endl;
                                TakeshiHRI::waitAfterSay("I found you", 4000);
                                TakeshiHRI::startFollowHuman();
                                // ros::spinOnce();
                                // rate.sleep();
                                TakeshiHRI::startFollowHuman();
                                TakeshiHRI::enableSpeechRecognized(true);
                                state = SM_FOLLOWING_PHASE;
                        }

                        break;

                case SM_FOLLOWING_PHASE:
                        cout << "SM: SM_FOLLOWING_PHASE" <<  endl;
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                                if(lastRecoSpeech.find("this is the kitchen table") != std::string::npos) {
                                        TakeshiHRI::enableSpeechRecognized(false);
                                        rate.sleep();
                                        ros::spinOnce();
                                        TakeshiHRI::waitAfterSay("Is This the kitchen table?", 2500);
                                        rate.sleep();
                                        ros::spinOnce();
                                        TakeshiHRI::enableSpeechRecognized(true);
                                        state= SM_FOLLOW_CONFIRMATION;
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
                                state=SM_DELIVERY_BAG;
                        }
                        else{
                                TakeshiHRI::waitAfterSay("Ok, continue", 4000);
                                state=SM_FOLLOWING_PHASE;
                        }
                        break;

                case SM_DELIVERY_BAG:
                        cout << "SM: SM_DELIVERY_BAG" << endl;
                        TakeshiTasks::giveObjectToHuman();
                        TakeshiNavigation::getClose("kitchen_table", 120000);
                        state=SM_INIT;
                        break;

                case SM_INIT:
                        if (startSignalSM) {
                                TakeshiHRI::waitAfterSay(
                                        "I am ready  attend to you",
                                        2000);
                                float currx, curry, currentTheta;
                                JustinaNavigation::getRobotPose(currx, curry, currentTheta);
                                TakeshiKnowledge::addUpdateKnownLoc("dining_room", currx, curry, currentTheta);
                                TakeshiKnowledge::addUpdateKnownLoc("table", currx, curry, currentTheta);
                                JustinaHRI::loadGrammarSpeechRecognized("open_chalenge.xml"); //load the grammar
                                TakeshiHRI::enableSpeechRecognized(true); //Enable recognized speech
                                state = SM_NAVIGATE_TO_THE_LOCATION;
                        }
                        std::cout << "state:" << state << std::endl;
                        break;
                case SM_NAVIGATE_TO_THE_LOCATION:
                        std::cout << "GPSRTest.->First try to move" << std::endl;
                        TakeshiHRI::waitAfterSay("I'am ready for user questions.", 3500);
                        state = SM_SEND_INIT_CLIPS;
                        break;
                case SM_SEND_INIT_CLIPS:
                        TakeshiVision::startQRReader();
                        initMsg.successful = 0;
                        runSMCLIPS = true;
                        command_response_pub.publish(initMsg);
                        state = SM_RUN_SM_CLIPS;
                        break;
                case SM_RUN_SM_CLIPS:
                        break;
                }

                rate.sleep();
                ros::spinOnce();
        }

        JustinaVision::stopQRReader();

        return 0;

}
