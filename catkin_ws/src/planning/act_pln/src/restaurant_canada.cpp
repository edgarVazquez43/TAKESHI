////////////////////////////////////////////////////////
// Note: this code was commented into CMake file,
// If you are brave enough to edit this code please
// make sure to uncomment this code into CMakeList.txt
///////////////////        EDD-II    ////////////////////

#include <iostream>
#include "ros/ros.h"
#include "justina_tools/JustinaHardware.h"
#include "justina_tools/JustinaHRI.h"
#include "justina_tools/JustinaManip.h"
#include "justina_tools/JustinaNavigation.h"
#include "justina_tools/JustinaKnowledge.h"
#include "justina_tools/JustinaTools.h"
#include "justina_tools/JustinaVision.h"
#include "justina_tools/JustinaTasks.h"
#include "justina_tools/JustinaRepresentation.h"
#include "std_msgs/Bool.h"
#include "string"
#include "vision_msgs/FindPlane.h"

#define SM_INIT 0
#define SM_WAIT_FOR_INIT_COMMAND 10
#define SM_SEARCH_BAR 20
#define SM_SEARCH_WAVING 30
#define SM_ALIGN_WAVING 32
#define SM_FIND_PERSONS 33
#define SM_WAIT_FOR_TAKE_ORDER 35
#define SM_CLOSE_TO_CLIENT 36
#define SM_SAY_TYPE_ORDER 40
#define SM_TYPE_ORDER_CONFIRM 41
#define SM_TAKE_ORDER 45
#define SM_ORDER_CONFIRM 50
#define SM_RETURN_BAR 60
#define SM_FINISH_TEST 150

int main(int argc, char** argv)
{
    std::cout << "INITIALIZING RESTAURANT TEST..." << std::endl;
    ros::init(argc, argv, "act_pln");
    ros::NodeHandle n;
    JustinaHardware::setNodeHandle(&n);
    JustinaHRI::setNodeHandle(&n);
    JustinaManip::setNodeHandle(&n);
    JustinaNavigation::setNodeHandle(&n);
    JustinaTools::setNodeHandle(&n);
    JustinaVision::setNodeHandle(&n);
    JustinaNavigation::setNodeHandle(&n);
    JustinaKnowledge::setNodeHandle(&n);
    JustinaRepresentation::setNodeHandle(&n);
   
    ros::Rate loop(10);
    
    int nextState = 0;
    bool fail     = false;
    bool success  = false;
    bool stop     = false;
    bool findGesture = false;

    std::string lastRecoSpeech;
    std::string lastInteSpeech;
    std::string obj1, obj2, typeOrder;
    int timeoutspeech = 10000;

    float robot_y, robot_x, robot_a;    
    float gx_w, gy_w, gz_w;    
    float goalx, goaly, goala, angleError;    
    float dist_to_head;

    std::vector<std::string> attendCommands;
    attendCommands.push_back("takeshi take the order");
    attendCommands.push_back("takeshi wait");
    std::vector<std::string> confirmCommands;
    confirmCommands.push_back("takeshi yes");
    confirmCommands.push_back("takeshi no");
    std::vector<std::string> typeOrderCommands;
    confirmCommands.push_back("I want a drink");
    confirmCommands.push_back("I want a combo");

    std::stringstream ss;

    Eigen::Vector3d centroidGesture;

    bool findGestureOrAttendOrder = false;
    bool validateCombo = true;
    bool isCombo = false;

    int attempsNavigation    = 1;
    int maxAttempsNavigation = 2;
    int attempsSpeechReco    = 1;
    int maxAttempsSpeechReco = 4;
    int attempsSpeechInt     = 1;
    int maxAttempsSpeechInt  = 2;
    int attempsWaitConfirmation    = 1;
    int maxAttempsWaitConfirmation = 3;
    int attempsConfirmation        = 1;
    int maxAttempsConfirmation     = 3;

    std::string bar_search="";
    
    std::vector<std::string> tokens;
    
    std::string grammarCommands = "restaurant_commands.xml";
    std::string grammarBeverage = "restaurant_beverage.xml";
    std::string grammarCombo    = "restaurant_combo.xml";
    
    //JustinaHRI::setInputDevice(JustinaHRI::KINECT);
    JustinaHRI::loadGrammarSpeechRecognized(grammarCommands);//load the grammar

    nextState = SM_INIT;

    while(ros::ok() && !fail && !success){
        switch(nextState){
            case SM_INIT:
                std::cout << "State machine: SM_INIT" << std::endl;	
                JustinaManip::hdGoTo(0, 0, 2000);
                JustinaHRI::waitAfterSay("I'm ready for the restaurant test", 3000);
                JustinaHRI::enableSpeechRecognized(true);
                nextState = SM_WAIT_FOR_INIT_COMMAND;
                break;

            case SM_WAIT_FOR_INIT_COMMAND:
                std::cout << "State machine: SM_WAIT_FOR_INIT_COMMAND" << std::endl;
				if(JustinaHRI::waitForSpecificSentence("takeshi start", timeoutspeech)){
                    JustinaHRI::enableSpeechRecognized(false);
                    JustinaHRI::waitAfterSay("I will search the bar", 3500);
                    nextState = SM_SEARCH_BAR;
                }else
                    nextState = SM_WAIT_FOR_INIT_COMMAND;
                break;

            case SM_SEARCH_BAR:
                std::cout << "State machine: SM_SERACH_BAR" << std::endl;
                JustinaTasks::findTable(bar_search);  
                // TODO delimited the table to find
                JustinaNavigation::getRobotPose(robot_x, robot_y, robot_a);

                if (bar_search.compare("right") == 0){
                    JustinaHRI::waitAfterSay("I see the bar in my right side", 4000);
                    robot_a+M_PI;
                }else if (bar_search.compare("left") == 0){
                    JustinaHRI::waitAfterSay("I see the bar in my left side", 10000);
                }
                else{
                    std::cout << "SM_SERACH_BAR: Bar default" << std::endl;
                    JustinaHRI::waitAfterSay("I see the bar in my left side", 10000);       
                }

                JustinaKnowledge::addUpdateKnownLoc("kitchen_bar", robot_a);
                JustinaManip::armGoToFindPerson();
                JustinaManip::hdGoTo(0.0, 0.0, 3000);    
                findGestureOrAttendOrder = true;

                JustinaHRI::waitAfterSay("I will find to the client", 4000);
                nextState = SM_SEARCH_WAVING;     
                
                break;

            case SM_SEARCH_WAVING:
                std::cout << "State machine: SM_SEARCH_WAVING" << std::endl;
                // TODO Test the motion the head tilt angle
				JustinaVision::startSkeletonFinding();

                findGesture = JustinaTasks::turnAndRecognizeGesture("waving", 0, 0, 0, -0.2f, -0.2f, -0.2f, 0.0f, 0.0f, 9.0, centroidGesture, "");
                
                if(findGesture){
                    JustinaVision::stopSkeletonFinding();
                    ros::spinOnce();
                    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
                    JustinaHRI::waitAfterSay("I noticed that somebody are asking for my service", 4000);
                    JustinaHRI::waitAfterSay("Tell me takeshi take the order for confirmation", 4000);
                    JustinaHRI::enableSpeechRecognized(true);
                    nextState = SM_WAIT_FOR_TAKE_ORDER;
                }
                else
                    nextState = SM_SEARCH_WAVING;
                break;

            case SM_WAIT_FOR_TAKE_ORDER:
                std::cout << "State machine: SM_WAIT_FOR_TAKE_ORDER" << std::endl;
                if(JustinaHRI::waitForSpecificSentence(attendCommands, lastRecoSpeech, timeoutspeech)){
                    if(lastRecoSpeech.find("take the order") != std::string::npos){
                        JustinaHRI::waitAfterSay("Ok, I am going to approach to the client", 4000);
                        nextState = SM_CLOSE_TO_CLIENT;
                    }
                    else if(lastRecoSpeech.find("wait") != std::string::npos){
                        JustinaHRI::waitAfterSay("I will find to the another client", 5000);
                        JustinaHRI::enableSpeechRecognized(false);
                        JustinaVision::startSkeletonFinding();
                        nextState = SM_SEARCH_WAVING;
                    }
                }
                else{
                    JustinaHRI::enableSpeechRecognized(false);
                    JustinaHRI::waitAfterSay("I noticed that somebody are asking for my service", 4000);
                    JustinaHRI::waitAfterSay("Tell me takeshi take the order for confirmation", 4000);
                    JustinaHRI::enableSpeechRecognized(true);
                }
                break;

            case SM_CLOSE_TO_CLIENT:
                std::cout << "State machine: SM_CLOSE_TO_CLIENT" << std::endl;

                JustinaTools::transformPoint("/base_link", centroidGesture(0, 0), centroidGesture(1, 0) , centroidGesture(2, 0), "/map", gx_w, gy_w, gz_w);
                JustinaTasks::closeToGoalWithDistanceTHR(gx_w, gy_w, 1.5, 120000);
                dist_to_head = sqrt( pow(gx_w, 2) + pow(gy_w, 2));
                JustinaNavigation::getRobotPose(robot_x, robot_y, robot_a);
                // JustinaManip::startHdGoTo(atan2(gy_w, gx_w) - robot_a, atan2(gz_w - 1.6, dist_to_head)); 
                JustinaManip::startHdGoTo(0, atan2(gz_w - 1.6, dist_to_head));

                JustinaKnowledge::addUpdateKnownLoc("table_1", robot_a);
                
                // JustinaHRI::waitAfterSay("Hello my name is Justina, and for today I will take your order, please tell me what order do you want me to bring", 12000);
                JustinaHRI::waitAfterSay("Hello my name is takeshi, and for today I will take your order", 7000);
                attempsConfirmation = 1;
                attempsWaitConfirmation = 1;
                attempsSpeechReco = 1;
                attempsSpeechInt = 1;
                validateCombo = false;
                nextState = SM_SAY_TYPE_ORDER;
                break;

            case SM_SAY_TYPE_ORDER:
                std::cout << "State machine: SM_TAKE_TYPE_ORDER" << std::endl;
                JustinaHRI::enableSpeechRecognized(false);
                if(validateCombo)
                    JustinaHRI::waitAfterSay("Do you want a combo, please tell me takeshi yes or takeshi no", 7000);
                else 
                    JustinaHRI::waitAfterSay("Do you want a drink, please tell me takeshi yes or takeshi no", 7000);
                JustinaHRI::enableSpeechRecognized(true);
                nextState = SM_TYPE_ORDER_CONFIRM;
                break;

            case SM_TYPE_ORDER_CONFIRM:
                std::cout << "State machine: SM_TYPE_ORDER_CONFIRM" << std::endl;
                if(JustinaHRI::waitForSpecificSentence(confirmCommands, lastRecoSpeech, timeoutspeech)){
                    if(lastRecoSpeech.find("yes") != std::string::npos){
                        attempsSpeechReco = 1;
                        attempsSpeechInt = 1;
                        attempsConfirmation = 1;
                        attempsWaitConfirmation = 1;
                        isCombo = validateCombo;
                        JustinaHRI::enableSpeechRecognized(false);
                        if(isCombo){
                            JustinaHRI::waitAfterSay("Please tell me what order do you want", 4000);
                            JustinaHRI::loadGrammarSpeechRecognized(grammarCombo);
                        }else{
                            JustinaHRI::waitAfterSay("Please tell me what kind of drink do you want", 4000);
                            JustinaHRI::loadGrammarSpeechRecognized(grammarBeverage);
                        }
                        JustinaHRI::enableSpeechRecognized(true);
                        nextState = SM_TAKE_ORDER;
                    }
                    else{
                        if(attempsConfirmation <= maxAttempsConfirmation){
                            attempsConfirmation++;
                            attempsWaitConfirmation = 1;
                            nextState = SM_SAY_TYPE_ORDER;
                        }
                        else{
                            attempsSpeechReco = 1;
                            attempsSpeechInt = 1;
                            attempsConfirmation = 1;
                            attempsWaitConfirmation = 1;
                            isCombo = validateCombo;
                            JustinaHRI::enableSpeechRecognized(false);
                            if(isCombo){
                                JustinaHRI::waitAfterSay("Please tell me what order do you want", 4000);
                                JustinaHRI::loadGrammarSpeechRecognized(grammarCombo);
                            }else{
                                JustinaHRI::waitAfterSay("Please tell me what kind of drink do you want", 4000);
                                JustinaHRI::loadGrammarSpeechRecognized(grammarBeverage);
                            }
                            JustinaHRI::enableSpeechRecognized(true);
                            nextState = SM_TAKE_ORDER;
                        }
                        if(validateCombo)
                            validateCombo = false;
                        else
                            validateCombo = true;
                    }
                }
                else {
                    if(attempsWaitConfirmation <= maxAttempsWaitConfirmation){
                        attempsWaitConfirmation++;
                        nextState = SM_SAY_TYPE_ORDER;
                    }
                    else{
                        attempsSpeechReco = 1;
                        attempsSpeechInt = 1;
                        attempsConfirmation = 1;
                        attempsWaitConfirmation = 1;
                        isCombo = validateCombo;
                        JustinaHRI::enableSpeechRecognized(false);
                        if(isCombo){
                            JustinaHRI::waitAfterSay("Please tell me what order do you want", 4000);
                            JustinaHRI::loadGrammarSpeechRecognized(grammarCombo);
                        }else{
                            JustinaHRI::waitAfterSay("Please tell me what kind of drink do you want", 4000);
                            JustinaHRI::loadGrammarSpeechRecognized(grammarBeverage);
                        }
                        nextState = SM_TAKE_ORDER;
                    }
                }
                break;

            case SM_TAKE_ORDER:
                std::cout << "State machine: SM_TAKE_ORDER" << std::endl;
                if(JustinaHRI::waitForSpeechRecognized(lastRecoSpeech, timeoutspeech)){
                    if(JustinaRepresentation::stringInterpretation(lastRecoSpeech, lastInteSpeech)){
                        if(JustinaRepresentation::orderInterpeted(lastInteSpeech, typeOrder, obj1, obj2)){
                            // TODO Review what happend with object with two words
                            ss.str("");
                            ss << "Do you want ";
                            if(typeOrder.compare("take_order_beverage") == 0){
                                tokens.clear();
                                boost::algorithm::split(tokens, obj1, boost::algorithm::is_any_of("_"));
                                for(int i = 0; i < tokens.size(); i++)
                                    ss << tokens[i] << " ";
                                isCombo = false;
                            }else if(typeOrder.compare("take_order_combo") == 0){
                                tokens.clear();
                                boost::algorithm::split(tokens, obj1, boost::algorithm::is_any_of("_"));
                                for(int i = 0; i < tokens.size(); i++)
                                    ss << tokens[i] << " ";
                                ss << "and ";
                                tokens.clear();
                                boost::algorithm::split(tokens, obj2, boost::algorithm::is_any_of("_"));
                                for(int i = 0; i < tokens.size(); i++)
                                    ss << tokens[i] << " ";
                                isCombo = true;
                            }
                            ss << ", please tell me takeshi yes or takeshi no";
                            JustinaHRI::enableSpeechRecognized(false);
                            JustinaHRI::waitAfterSay(ss.str(), 10000);
                            JustinaHRI::loadGrammarSpeechRecognized(grammarCommands);
                            JustinaHRI::enableSpeechRecognized(true);
                            nextState = SM_ORDER_CONFIRM;
                            break;
                        }
                    }
                    if(maxAttempsSpeechInt <= maxAttempsSpeechInt){
                        JustinaHRI::enableSpeechRecognized(false);
                        if(isCombo){
                            JustinaHRI::waitAfterSay("Sorry I did not understand you, Please tell me what order do you want", 5000);
                            //JustinaHRI::loadGrammarSpeechRecognized(grammarCombo);
                        }else{
                            JustinaHRI::waitAfterSay("Sorry I did not understand you, Please tell me what kind of drink do you want", 5000);
                            //JustinaHRI::loadGrammarSpeechRecognized(grammarBeverage);
                        }
                        attempsSpeechInt++;
                        JustinaHRI::enableSpeechRecognized(true);
                        nextState = SM_TAKE_ORDER;
                    }
                    else{
                        JustinaHRI::enableSpeechRecognized(false);
                        JustinaHRI::waitAfterSay("Sorry I did not understand you, I'm going back to the kitchen bar", 12000);
                        attempsSpeechReco = 1;
                        attempsSpeechInt = 1;
                        findGestureOrAttendOrder = true;
                        nextState = SM_RETURN_BAR;
                    }
                }
                else{
                    if(attempsSpeechReco <= maxAttempsSpeechReco){
                        JustinaHRI::enableSpeechRecognized(false);
                        if(isCombo){
                            JustinaHRI::waitAfterSay("Sorry I did not understand you, Please tell me what order do you want", 5000);
                            //JustinaHRI::loadGrammarSpeechRecognized(grammarCombo);
                        }else{
                            JustinaHRI::waitAfterSay("Sorry I did not understand you, Please tell me what kind of drink do you want", 5000);
                            //JustinaHRI::loadGrammarSpeechRecognized(grammarBeverage);
                        }
                        attempsSpeechReco++;
                        JustinaHRI::enableSpeechRecognized(true);
                        nextState = SM_TAKE_ORDER;
                    }
                    else{
                        JustinaHRI::enableSpeechRecognized(false);
                        JustinaHRI::waitAfterSay("Sorry I did not understand you, I'm going back to the kitchen bar", 12000);
                        attempsSpeechReco = 1;
                        attempsSpeechInt = 1;
                        findGestureOrAttendOrder = true;
                        nextState = SM_RETURN_BAR;
                    }
                }
                break;

            case SM_ORDER_CONFIRM:
                std::cout << "State machine: SM_FIRST_ORDER_CONFIRM" << std::endl;
                attempsSpeechReco = 1;
                attempsSpeechInt = 1;
                if(JustinaHRI::waitForSpecificSentence(confirmCommands, lastRecoSpeech, timeoutspeech)){
                    if(lastRecoSpeech.find("yes") != std::string::npos){
                        JustinaHRI::enableSpeechRecognized(false);
                        JustinaHRI::waitAfterSay("Ok, i will go to the kitchen bar and i will be back with your order", 7000);
                        findGestureOrAttendOrder = false;
                        nextState = SM_RETURN_BAR;
                    }
                    else{
                        if(attempsConfirmation <= maxAttempsConfirmation){
                            attempsConfirmation++;
                            JustinaHRI::enableSpeechRecognized(false);
                            if(isCombo){
                                JustinaHRI::waitAfterSay("Sorry I did not understand you, Please tell me what order do you want", 5000);
                                JustinaHRI::loadGrammarSpeechRecognized(grammarCombo);
                            }else{
                                JustinaHRI::waitAfterSay("Sorry I did not understand you, Please tell me what kind of drink do you want", 5000);
                                JustinaHRI::loadGrammarSpeechRecognized(grammarBeverage);
                            }
                            JustinaHRI::enableSpeechRecognized(true);
                            nextState = SM_TAKE_ORDER;
                        }
                        else{
                            JustinaHRI::enableSpeechRecognized(false);
                            JustinaHRI::waitAfterSay("Ok, i will go to the kitchen bar and i will be back with your order", 10000);
                            findGestureOrAttendOrder = false;
                            nextState = SM_RETURN_BAR;
                        }
                    }
                }
                else {
                    if(attempsWaitConfirmation <= maxAttempsWaitConfirmation){
                        attempsWaitConfirmation++;
                        JustinaHRI::enableSpeechRecognized(false);
                        JustinaHRI::waitAfterSay(ss.str(), 10000);
                        JustinaHRI::enableSpeechRecognized(true);
                        nextState = SM_ORDER_CONFIRM;
                    }
                    else{
                        JustinaHRI::enableSpeechRecognized(false);
                        JustinaHRI::waitAfterSay("Ok, i will go to the kitchen bar and i will be back with your order", 10000);
                        findGestureOrAttendOrder = false;
                        nextState = SM_RETURN_BAR;
                    }
                }
                break;	

            case SM_RETURN_BAR:
                std::cout << "State machine: SM_RETURN_BAR" << std::endl;
                JustinaHRI::loadGrammarSpeechRecognized(grammarCommands);//load the grammar
                JustinaHRI::enableSpeechRecognized(false);
                if(!JustinaNavigation::getClose("kitchen_bar", 120000)){
                    attempsNavigation++;
                    if(attempsNavigation <= maxAttempsNavigation)
                        break;
                    else{
                        JustinaNavigation::getRobotPose(robot_x, robot_y, robot_a);
                        JustinaKnowledge::getKnownLocation("kitchen_bar", goalx, goaly, goala);
                        angleError = goala - robot_a;
                        if(angleError > M_PI) angleError -= 2*M_PI;
                        if(angleError <= -M_PI) angleError += 2*M_PI;
                        JustinaNavigation::moveDistAngle(0.0, angleError, 3000);
                    }
                }
                JustinaHRI::waitAfterSay("I arrived to the kitchen bar", 2000);
                if(findGestureOrAttendOrder){
                    JustinaHRI::waitAfterSay("I will find to the client", 5000);
                    JustinaVision::startSkeletonFinding();
                    nextState=SM_SEARCH_WAVING;
                }
                else{
                    // TODO This is for attend the order in kitchen bar
                    nextState = SM_FINISH_TEST;
                }
                break;
            case SM_FINISH_TEST:
                JustinaHRI::waitAfterSay("I have finished the test", 5000);
                success = true;
            break;    
        }
        ros::spinOnce();
        loop.sleep();
    }

    return 1;
}

