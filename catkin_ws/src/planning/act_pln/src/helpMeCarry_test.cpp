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
        SM_INIT,
        SM_INSTRUCTIONS,
        SM_WAIT_FOR_OPERATOR,
        SM_MEMORIZING_OPERATOR,
        SM_WAIT_FOR_LEGS_FOUND,
        SM_FOLLOWING_PHASE,
        SM_FOLLOW_OBSTACLE,
        SM_FOLLOW_OBSTACLE_SAY,
        SM_BRING_GROCERIES,
        SM_BRING_GROCERIES_CONF,
        SM_BRING_GROCERIES_TAKE,
        SM_BAG_DELIVERY,
        SM_BAG_DELIVERY_PLACE,
        SM_LOOKING_HELP,
        SM_GUIDING_ASK,
        SM_GUIDING_HELP,
        SM_TAKE_BAG,
        SM_GUIDING_MEMORIZING_OPERATOR,
        SM_GUIDING_MEMORIZING_OPERATOR_ELF,
        SM_GUIDING_MEMORIZING_OPERATOR_SAY,
        SM_GUIDING_PHASE,
        SM_GUIDING_STOP,
        SM_GUIDING_CAR,
        SM_OPEN_DOOR,
        SM_FINAL_STATE,
        SM_HOKUYO_TEST
};


void printState(std::string st){
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        STATE MACHINE: "<< st << "\033[0m" << std::endl;
}











#define MAX_ATTEMPTS_RECOG 5
#define MAX_ATTEMPTS_CONF 3

sensor_msgs::LaserScan laser;
std::vector<float> laser_ranges;
bool door_isopen=false;
bool door_loc=false;
bool obstacleInFront=false;
bool obstacle;

int range=0,range_i=0,range_f=0,range_c=0,cont_laser=0;
float laser_l=0;
float leg_x=0, leg_y=0, leg_z=0;
float outX,outY,outZ;

void Callback_laser(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    range=msg->ranges.size();
    range_c=range/2;
    range_i=range_c-(range/10);
    range_f=range_c+(range/10);
    std::cout<<"Range Size: "<< range << "\n ";
    std::cout<<"Range Central: "<< range_c << "\n ";
    std::cout<<"Range Initial: "<< range_i << "\n ";
    std::cout<<"Range Final: "<< range_f << "\n ";

    cont_laser=0;
    laser_l=0;
    for(int i=range_c-(range/10); i < range_c+(range/10); i++)
    {
        if(msg->ranges[i] > 0 && msg->ranges[i] < 4){
            laser_l=laser_l+msg->ranges[i];
            cont_laser++;
        }
    }
    std::cout<<"Laser promedio: "<< laser_l/cont_laser << std::endl;
    if(laser_l/cont_laser > 2.0){
        door_isopen=true;
    }
    else{
        door_isopen=false;
    }
}
/*
void callbackObstacleInFront(const std_msgs::Bool::ConstPtr& msg)
{

    obstacle = msg->data;

    cout << obstacle << endl;
    if(obstacle == true){
        TakeshiHRI::stopFollowHuman();
        ros::spinOnce();
        TakeshiHRI::stopFollowHuman();
        ros::spinOnce();
        obstacleInFront=true;
    }

}*/

int main(int argc, char** argv)
{
    std::cout << "INITIALIZING HELP ME CARRY TEST..." << std::endl;
    ros::init(argc, argv, "act_pln");
    ros::NodeHandle n;

    bool fail = false;
    bool success = false;
    ros::Rate loop(10);


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

    std::vector<std::string> validCommandsStop;
    std::vector<std::string> validCommandsTake;
    std::vector<std::string> validCommandsInstruction;


    validCommandsStop.push_back("here is the car");
    validCommandsStop.push_back("stop follow me");
    //validCommandsStop.push_back("take the bag");

    validCommandsInstruction.push_back("take the bag");

    //places
    validCommandsTake.push_back("take this bag to the dining room");
    validCommandsTake.push_back("get this bag to the dining room");
    //location="bed";

    validCommandsTake.push_back("take this bag to the bedroom");
    validCommandsTake.push_back("get this bag to the bedroom");
    //location="bedroom";

    validCommandsTake.push_back("take this bag to the living room");
    validCommandsTake.push_back("get this bag to the living room");

    validCommandsTake.push_back("take this bag to the kitchen table");
    validCommandsTake.push_back("get this bag to the kitchen table");
    //location="buro";
    validCommandsTake.push_back("take this bag to the kitchen");
    validCommandsTake.push_back("get this bag to the kitchen");
    //location="counter";

    validCommandsTake.push_back("take this bag to the exit");
    validCommandsTake.push_back("get this bag to the exit");
    //location="corridor";

    validCommandsTake.push_back("take this bag to the entrance");
    validCommandsTake.push_back("get this bag to the entrance");
    //location="cupboard";

    validCommandsTake.push_back("take this bag to the hall");
    validCommandsTake.push_back("get this bag to the hall");
    //location="dining_room";

    validCommandsTake.push_back("take this bag to the dining table");
    validCommandsTake.push_back("get this bag to the dining table");
    //location="dining_table";

    validCommandsTake.push_back("take this bag to the shelf");
    validCommandsTake.push_back("get this bag to the shelf");
    //location="desk";

    validCommandsTake.push_back("take this bag to the night stand");
    validCommandsTake.push_back("get this bag to the night stand");
    //location="dishwasher";

    validCommandsTake.push_back("take this bag to the bed");
    validCommandsTake.push_back("get this bag to the bed");
    //location="entrance";

    validCommandsTake.push_back("take this bag to the center table");
    validCommandsTake.push_back("get this bag to the center table");
    //location="couch";

    validCommandsTake.push_back("take this bag to the side table");
    validCommandsTake.push_back("get this bag to the side table");
    //location="end_table";

    validCommandsTake.push_back("take this bag to the tv table");
    validCommandsTake.push_back("get this bag to the tv table");
    //location="exit_2";

    validCommandsTake.push_back("take this bag to the fridge");
    validCommandsTake.push_back("get this bag to the fridge");
    //location="kitchen";


    //location="living_room";


    ros::Subscriber laser_subscriber;
    //ros::Subscriber subObsInFront;
    laser_subscriber = n.subscribe<sensor_msgs::LaserScan>("/scan", 1, Callback_laser);
    //subObsInFront = n.subscribe("/navigation/obs_avoid/obs_in_front", 1, &callbackObstacleInFront);


    bool hokuyoRear = false;
    bool userConfirmation = false;
    bool alig_to_place=true;




    int nextState = SM_INIT;
    int attemps=0;
    bool start_follow=false;

    TakeshiHRI::enableSphinxMic(true);
    TakeshiHRI::loadJSGFGrammar("grammars/helpme_carry_grammar.jsgf", "help_me_carry_grammar");

    while(ros::ok() && !fail && !success)
    {
        switch(nextState)
        {
            case SM_INIT:
                printState("SM_INIT");
                TakeshiHRI::waitAfterSay("Hello, i am Takeshi", 5000);
                TakeshiHRI::enableSphinxMic(false);
                TakeshiHRI::enableLegFinder(false);
                nextState = SM_INSTRUCTIONS;
                break;

            case SM_INSTRUCTIONS:
                cout << "State machine: SM_INSTRUCTIONS" << endl;
                TakeshiHRI::waitAfterSay("Please tell me, here is the car, at the car location. Tell me takeshi yes, or takeshi no to confirm. Tell me, follow me, to start following you. I am waiting for your voice command", 15000);
                TakeshiHRI::enableSphinxMic(true);
                attemps=0;
                nextState=SM_WAIT_FOR_OPERATOR;
                break;

            case SM_WAIT_FOR_OPERATOR:
                printState("SM_WAIT_FOR_OPERATOR");
                if(TakeshiHRI::waitForSpecificSentence("follow me" , 7000)){
                	TakeshiHRI::enableSphinxMic(false);
                    nextState = SM_MEMORIZING_OPERATOR;
				}
                else
                    attemps++;

                if(attemps>3){
                    TakeshiHRI::waitAfterSay("Please, tell me follow me to start", 2000);
                    attemps=0;
                }

                break;

            case SM_MEMORIZING_OPERATOR:
                printState("SM_MEMORIZING_OPERATOR");

                if(!start_follow){
                    TakeshiHRI::waitAfterSay("Human, please put in front of me",3500);
                    TakeshiHRI::enableLegFinder(true);
                }
                else
                    TakeshiHRI::enableLegFinder(true);

                nextState=SM_WAIT_FOR_LEGS_FOUND;

                break;

            case SM_WAIT_FOR_LEGS_FOUND:

                cout << "State machine: SM_WAIT_FOR_LEGS_FOUND" << endl;
                if(TakeshiHRI::frontalLegsFound()){
                    if(start_follow){
                        cout << "Frontal legs found!" << std::endl;
                        TakeshiHRI::waitAfterSay("I found you, please walk.", 3000);
                        TakeshiHRI::startFollowHuman();
                        //TakeshiNavigation::enableObstacleDetection(true);
                        TakeshiHRI::enableSphinxMic(true);
                        nextState = SM_FOLLOWING_PHASE;
                    }

                    else{
                        std::cout << "NavigTest.->Frontal legs found!" << std::endl;
                        TakeshiHRI::waitAfterSay("I found you, i will start to follow you human, please walk. ", 3000);
                        TakeshiHRI::startFollowHuman();
                        //TakeshiNavigation::enableObstacleDetection(true);
                        TakeshiHRI::enableSphinxMic(true);
                        start_follow=true;
                        nextState = SM_FOLLOWING_PHASE;
                    }
                }

                break;
/*
            case SM_FOLLOW_OBSTACLE_SAY:
                 cout << "State machine: SM_FOLLOWING_OBSTACLE_SAY" << endl;
                 TakeshiHRI::stopFollowHuman();
                 nextState=SM_FOLLOW_OBSTACLE;
            break;

            case SM_FOLLOW_OBSTACLE:
                cout << "State machine: SM_FOLLOWING_OBSTACLE" << endl;
                cout << "Obstacle in front" << endl;
                TakeshiHRI::stopFollowHuman();
                ros::spinOnce();
                TakeshiHRI::waitAfterSay("Human, let me pass please", 2500);

                while(obstacle){
                    ros::spinOnce();
                    loop.sleep();
                }

                obstacleInFront=false;
                nextState=SM_FOLLOWING_PHASE;
                TakeshiHRI::waitAfterSay("Thank you", 500);
                TakeshiHRI::startFollowHuman();


            break;
*/
            case SM_FOLLOWING_PHASE:

                cout << "State machine: SM_FOLLOWING_PHASE" << endl;
                /*if(obstacleInFront==true){
                    nextState = SM_FOLLOW_OBSTACLE_SAY;
                    break;
                }*/

                if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000)){
                    if(lastRecoSpeech.find("here is the car") != std::string::npos || lastRecoSpeech.find("stop follow me") != std::string::npos){
                        //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Here is the car command was recognized");
                        //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Waiting for user confirmation");
                        TakeshiHRI::waitAfterSay("is this the car location?", 2500);
                        TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000);
                        if(userConfirmation){
                            TakeshiHRI::stopFollowHuman();
                            TakeshiHRI::enableLegFinder(false);
                            TakeshiKnowledge::addUpdateKnownLoc("car_location");
                            TakeshiHRI::waitAfterSay("I stopped", 1000);
                            userConfirmation=false;
                            TakeshiManip::hdGoTo(0.0, 0.5,2000);
                            TakeshiHRI::loadJSGFGrammar("grammars/helpme_carry_grammar.jsgf", "help_me_carry_grammar");
                            nextState = SM_BRING_GROCERIES;
                            attemps=8;
                            //TakeshiNavigation::enableObstacleDetection(false);
                            break;
                        }

                        else
                            TakeshiHRI::waitAfterSay("Ok, please walk.",2000);
                            TakeshiHRI::loadJSGFGrammar("grammars/helpme_carry_grammar.jsgf", "help_me_carry_grammar");

                            //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Robot No command was recognized");

                    }
                }



                if(!TakeshiHRI::frontalLegsFound()){
                    cout << "State machine: SM_FOLLOWING_PHASE -> Lost human!" << std::endl;
                    TakeshiHRI::waitAfterSay("I lost you, please put in front of me again", 3500);
                    TakeshiHRI::stopFollowHuman();
                    TakeshiHRI::enableLegFinder(false);
                    //subObsInFront.shutdown();
                    nextState=SM_MEMORIZING_OPERATOR;
                }
				break;

            case SM_BRING_GROCERIES:
                cout << "State machine: SM_BRING_GROCERIES" << endl;
                if(attemps>4){
                    TakeshiHRI::waitAfterSay("I am ready to help you, Please tell me, take this bag to some location", 5000);
                    attemps=0;
                }

                attemps++;

                if(TakeshiHRI::waitForSpecificSentence(validCommandsTake, lastRecoSpeech, 7000)){
                    attemptsRecogLoc++;

                    if(lastRecoSpeech.find("this bag to dining room") != std::string::npos){
                        location="dining_room";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the bedroom") != std::string::npos){
                        location="bedroom";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the living room") != std::string::npos){
                        location="living_room";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }



                    else if(lastRecoSpeech.find("this bag to the exit") != std::string::npos){
                        location="exit_1";
                        alig_to_place=true;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the entrance") != std::string::npos){
                        location="entrance_1";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the hall") != std::string::npos){
                        location="hall";
                        alig_to_place=true;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the dining table") != std::string::npos){
                        location="dining_table";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the shelf") != std::string::npos){
                        location="shelf";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the night stand") != std::string::npos){
                        location="night_stand";
                        alig_to_place=true;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the bed") != std::string::npos){
                        location="bed";
                        alig_to_place=true;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the center table") != std::string::npos){
                        location="center_table";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the side table") != std::string::npos){
                        location="side_table";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the tv table") != std::string::npos){
                        location="tv_table";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the fridge") != std::string::npos){
                        location="fridge";
                        alig_to_place=false;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(lastRecoSpeech.find("this bag to the kitchen table") != std::string::npos){
                        location="kitchen_table";
                        alig_to_place=true;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                     else if(lastRecoSpeech.find("this bag to the kitchen") != std::string::npos){
                        location="kitchen";
                        alig_to_place=true;
                        nextState=SM_BRING_GROCERIES_CONF;
                    }

                    else if(attemptsRecogLoc >= MAX_ATTEMPTS_RECOG){
                        location = "dining_room";
                        alig_to_place=true;
                        nextState = SM_BRING_GROCERIES_TAKE;
                    }

                    if(location.compare("") != 0 && nextState == SM_BRING_GROCERIES_CONF){
                        ss.str("");
                        ss << "Do you want me take this bag to the ";
                        tokens.clear();
                        boost::algorithm::split(tokens, location, boost::algorithm::is_any_of("_"));
                        for(int i = 0; i < tokens.size(); i++)
                            ss << tokens[i] << " ";
                        TakeshiHRI::waitAfterSay(ss.str(), 3000);
                    }

                }
                break;

            case SM_BRING_GROCERIES_CONF:
                cout << "State machine: SM_BRING_GROCERIES_CONF" << endl;
                TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000);
                attemptsConfLoc++;
                if(userConfirmation){
                    nextState = SM_TAKE_BAG;
                    TakeshiManip::armGoToGraspBag(-1.5);
                    TakeshiHRI::loadJSGFGrammar("grammars/helpme_carry_grammar.jsgf", "help_me_carry_grammar");
                    attemps=8;
                }
                else if(attemptsConfLoc < MAX_ATTEMPTS_CONF){
                    nextState = SM_BRING_GROCERIES;
                    TakeshiHRI::loadJSGFGrammar("grammars/helpme_carry_grammar.jsgf", "help_me_carry_grammar");
                    TakeshiManip::armGoToGraspBag(-1.5);
                    attemps=8;
                }
                else{
                    nextState = SM_TAKE_BAG;
                    attemps=8;
                    TakeshiManip::armGoToGraspBag(-1.5);
                }

                break;


            case SM_TAKE_BAG:
                printState("SM_TAKE_BAG");
                if(attemps > 3){
                    TakeshiHRI::waitAfterSay("Please, put the middle of the bag in my gripper and then, tell me, take the bag",3000);
                    attemps=0;
                }
                if(TakeshiHRI::waitForSpecificSentence(validCommandsInstruction,lastRecoSpeech,7000)){
                    if(lastRecoSpeech.find("take the bag") != std::string::npos){
                        TakeshiHRI::enableSphinxMic(false);
                        TakeshiManip::closeGripper(1.0);
                        TakeshiManip::navigationPose(4000);
                        nextState=SM_BRING_GROCERIES_TAKE;
                    }
                }
                else
                    attemps++;
            break;



            case SM_BRING_GROCERIES_TAKE:
                cout << "State machine: SM_BRING_GROCERIES_TAKE" << endl;
                //JustinaTasks::detectBagInFront(true, 20000);
                ss.str("");
                ss << "Ok human, I will go to the ";
                tokens.clear();
                boost::algorithm::split(tokens, location, boost::algorithm::is_any_of("_"));
                for(int i = 0; i < tokens.size(); i++)
                    ss << tokens[i] << " ";
                ss << "and i will be back to the car";
                TakeshiHRI::say(ss.str());
                TakeshiHRI::enableSphinxMic(false);
                nextState=SM_BAG_DELIVERY;
                break;

            case SM_BAG_DELIVERY:
                cout << "State machine: SM_BAG_DELIVERY" << endl;
                //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Command was recognized, carry the bag to: "+ location);

                if(!TakeshiKnowledge::existKnownLocation(location)){
                    cout << "SM_BAG_DELIVERY: NO LOCATION!" << endl;
                    location="kitchen_table";
                    alig_to_place=true;
                    //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Location not found: "+ location);
                    //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Change location to default location: kitchen table ");
                }

				TakeshiManip::torsoGoTo(0.0,5000);
                TakeshiManip::armGoToNavigation();

                std::cout << "Location -> " << location << std::endl;
                if(!TakeshiNavigation::getClose(location, 200000))
                    if(!TakeshiNavigation::getClose(location, 200000))
                        TakeshiNavigation::getClose(location, 200000);
                TakeshiHRI::waitAfterSay("I arrived", 1000);
                //TakeshiNavigation::moveDistAngle(0.0, -1.5708, 10000);
                //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Arrived to location: "+ location);
                nextState=SM_BAG_DELIVERY_PLACE;

                break;

            case SM_BAG_DELIVERY_PLACE:
                std::cout << "State machine: SM_BAG_DELIVERY_PLACE" << std::endl;
                TakeshiHRI::say("I will deliver the bag");
                //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Starting delivery the bag function");

                /*
                if(alig_to_place==true){
                    if(!TakeshiTasks::placeObject(0.25, true))
                        if(!TakeshiTasks::placeObject(0.25, true))
                            TakeshiTasks::placeObject(0.25, true);
                        }
                else{*/
                    TakeshiManip::torsoGoTo(0.15,2000);
                    TakeshiManip::armGoToDeliverObjectInFloor(4000);
                    TakeshiManip::openGripper(1.0);
                    ros::Duration(3.0).sleep();
                    TakeshiManip::navigationPose(4000);
                    TakeshiManip::openGripper(0.0);
                //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Finish delivery the bag");
                nextState=SM_LOOKING_HELP;

                break;

            case SM_LOOKING_HELP:
                std::cout << "State machine: SM_LOOKING_HELP" << std::endl;

                TakeshiHRI::waitAfterSay("I will look for help", 1500);
                TakeshiHRI::enableSphinxMic(true);
                //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Searching a human for help to the carry the bags");
                //TakeshiManip::torsoGoTo(0.3,2000);
                TakeshiNavigation::moveDistAngle(-0.05, 0.0, 3000);
                ros::spinOnce();


                if(TakeshiTasks::findPerson("", -1, TakeshiTasks::STANDING, false)){
                    nextState=SM_GUIDING_ASK;

                    //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Finish search, human was found");
                }
                else{
                    TakeshiHRI::say("I did not find anyone");
                    //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Finish search, human was not found");
                }

                break;

            case SM_GUIDING_ASK:
                std::cout << "State machine: SM_GUIDING_ASK" << std::endl;
                TakeshiHRI::waitAfterSay("Human, can you help me bring some bags please", 3500);
                //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Waiting for human confirmation");

                TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000);
                if(userConfirmation){
                    nextState = SM_GUIDING_MEMORIZING_OPERATOR_SAY;
                    //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Robot yes command was recognized");
                    TakeshiManip::armGoToNavigation();
                    boost::this_thread::sleep(boost::posix_time::milliseconds(4000));
                    TakeshiManip::torsoGoTo(0.0,4000);

                }
                else {
                    nextState = SM_LOOKING_HELP;
                    TakeshiNavigation::moveDistAngle(0.0, 1.5708, 10000);
                    //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Robot no command was recognized");
                }

                break;

            case SM_GUIDING_MEMORIZING_OPERATOR_SAY:
                std::cout << "State machine: SM_GUIDING_MEMORIZING_OPERATOR_SAY" << std::endl;
                TakeshiHRI::say("I will guide you to the car location");
                //TakeshiNavigation::moveDistAngle(0.0, 3.14159, 6000);
                TakeshiHRI::say("Please, stand behind me");
                location="car_location";
                // location="entrance_2";
                /////doorlocation
                attemps=8;
                nextState=SM_GUIDING_PHASE;

                break;

            case SM_GUIDING_PHASE:
                std::cout << "State machine: SM_GUIDING_PHASE" << std::endl;
                std::cout << "Location -> " << location << std::endl;

                if(!door_loc){
	                if(TakeshiTasks::guidePerson(location, 15000)){

                		//TakeshiHRI::enableDoorIsOpen(&n, true);
                    	nextState=SM_GUIDING_CAR;
                    }
                else{
                    	nextState=SM_GUIDING_CAR;
                    }
                }
                

                break;

            case SM_GUIDING_CAR:
                    std::cout << "State machine: SM_GUIDING_CAR" << std::endl;
                    TakeshiHRI::say("Here is the car, please help us");
                    //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Arrived to car location");
                    //JustinaTools::pdfAppend("HelpMeCarry_Plans", "Finish the HelpMeCarry test");
                    TakeshiHRI::say("I have finished the test");
                    //JustinaHRI::enableLegFinderRear(false);
                    nextState=SM_FINAL_STATE;
               // }
                break;

            case SM_OPEN_DOOR:
                std::cout << "State machine: SM_OPEN_DOOR" << std::endl;
                if(TakeshiHRI::isDoorOpen()){
                    //T//akeshiHRI::waitAfterSay("Thank you", 2500);
                    std::cout << "Tank You" << std::endl;
                    //laser_subscriber.shutdown();
                    door_loc=true;
                    //TakeshiHRI::enableDoorIsOpen(&n, false);
                    location="car_location";
                    nextState= SM_GUIDING_PHASE;
                }

                else{
                    if(attemps>5){
                        std::cout << "Human Open the door" << std::endl;
                        TakeshiHRI::waitAfterSay("Human, can you open the door please", 4500);
                        TakeshiHRI::waitAfterSay("Please move, i will move backwards", 10000);
                        sleep(1.0);
                        TakeshiNavigation::moveDistAngle(-0.4,0.0, 4000);
                        attemps=0;
                    }
                    std::cout << "Open the door time" << std::endl;
                    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
                    attemps++;
                }

                break;

            case SM_FINAL_STATE:
                std::cout << "State machine: SM_FINAL_STATE" << std::endl;
                //JustinaTools::pdfStop("HelpMeCarry_Plans");
                success = true;
                break;


        }

        ros::spinOnce();
        loop.sleep();
    }



    return 1;
}
