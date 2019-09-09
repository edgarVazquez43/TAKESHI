
#include "ros/ros.h"
#include "takeshi_tools/TakeshiHardware.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiRepresentation.h"
#include <algorithm>
#include <vector>
#include <math.h>


enum state {
        SM_INIT,
        SM_WAIT_DOOR,
        SM_GO_TO_BAR,
        SM_CHECK_DRINKS,
        SM_GO_TO_LIVINGROOM,
        SM_FIND_PERSON_WITHOUT_DRINK,
        SM_FIND_PERSON_WITHOUT_DRINK_RISING_HAND,
        SM_RECOGNIZING_FACE,
        SM_ASK_FOR_NAME,
        SM_WAIT_FOR_NAME,
        SM_COMFIRM_NAME,
        SM_WAIT_CONFIRMATION_NAME,
        SM_ASK_FOR_DRINK,
        SM_WAIT_FOR_DRINK,
        SM_COMFIRM_DRINK,
        SM_WAIT_CONFIRMATION_DRINK,
        SM_ANNOUNCE_UNAVAILABILITY_OF_DRINK,
        SM_GO_FOR_ORDER,
        SM_TAKE_DRINK,
        SM_DELIVER_DRINK,
        SM_FIND_PERSON_TO_DELIVER,
        SM_RELEASE_OBJECT,
        SM_FINAL_STATE
};

void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        CASE: "<< st << "\033[0m" << std::endl;
}


int main(int argc, char **argv) {

    ros::init(argc, argv, "serving_drinks");
    ros::NodeHandle n;

    TakeshiHRI::setNodeHandle(&n);
    TakeshiHardware::setNodeHandle(&n);
    TakeshiKnowledge::setNodeHandle(&n);
    TakeshiNavigation::setNodeHandle(&n);
    TakeshiManip::setNodeHandle(&n);
    TakeshiTasks::setNodeHandle(&n);
    TakeshiTools::setNodeHandle(&n);
    TakeshiVision::setNodeHandle(&n);
    TakeshiRepresentation::setNodeHandle(&n);


    bool userConfirmation=false;

    std::string lastRecoSpeech;
    std::string train_name;
    std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
    train_name="train_";
    vision_msgs::VisionFaceObjects vfo;
    std::vector<std::string> validCommandsNames;
    std::vector<std::string> validCommandsDrinks;
    std::vector<std::string> AvailableDrinks;
    std::vector<std::string> aux_drinks;
    std::vector<std::string>::iterator it;
    std::vector<float> obj_position;
    std::vector<vision_msgs::GestureSkeleton> gestures;
    vision_msgs::GestureSkeleton gesture;
    vision_msgs::Skeleton skeletonZero;
    bool findBagLeftSide=false;
    bool findBagRightSide=false; 
    int closestSkl;               
    vision_msgs::Skeletons skl;
    std::vector<std::string> specificGestures;
    float cx, cy, cz,currx,curry,currtheta; 
   
    
    ros::Rate rate(10);






    int nextState =SM_INIT;
    
    int number_of_guest=0;
    int counter=0;
    int drinks_delivered=0;

    int hdposestate=1;
    int icount=0;
    float anghd=0;
   

    
    bool success=false;
    bool add_drink=false;
    std::string name="";
    std::string beverage="";

    //names
    validCommandsNames.push_back("amelia");
    validCommandsNames.push_back("angel");
    validCommandsNames.push_back("ava");
    validCommandsNames.push_back("charlie");
    validCommandsNames.push_back("oliver");
    validCommandsNames.push_back("hunter");
    validCommandsNames.push_back("max");
    validCommandsNames.push_back("mia");
    validCommandsNames.push_back("olivia");
    validCommandsNames.push_back("parker");
    validCommandsNames.push_back("sam");
    validCommandsNames.push_back("charlie");
    validCommandsNames.push_back("jack");
    validCommandsNames.push_back("noah");
    validCommandsNames.push_back("oliver");
    validCommandsNames.push_back("thomas");
    validCommandsNames.push_back("william");


    //drinks
    validCommandsDrinks.push_back("beer");
    validCommandsDrinks.push_back("chocolate milk");
    validCommandsDrinks.push_back("coke");
    validCommandsDrinks.push_back("juice");
    validCommandsDrinks.push_back("lemonade");
    validCommandsDrinks.push_back("tea bag");
    validCommandsDrinks.push_back("water");

    //OPENPOSES
     specificGestures.push_back("right_hand_rised");
     specificGestures.push_back("left_hand_rised");
     specificGestures.push_back("hand_right_extended");
     specificGestures.push_back("hand_left_extended");
     specificGestures.push_back("both_hands_down");

     AvailableDrinks.push_back("beer");
     AvailableDrinks.push_back("coke");
     AvailableDrinks.push_back("juice");
   

    std::vector<vision_msgs::VisionObject> detectedObjs;
    vision_msgs::ObjectCoordinatesForDetection objectsCoordinates;
    objectsCoordinates=TakeshiVision::objectCoordinates;

    while (ros::ok() && !success) {

        switch(nextState){
            case SM_INIT:
                printState("SM START");
                TakeshiHRI::waitAfterSay("I'm ready for the test to start",2000);
                nextState=SM_WAIT_DOOR;
                break;

            case SM_WAIT_DOOR:
                printState("wait for the door");
                TakeshiHRI::waitAfterSay("I'm waiting for the door to be open",1000);
                if(!TakeshiNavigation::obstacleInFront())
                    nextState = SM_GO_TO_LIVINGROOM;
                break;

            
            case SM_GO_TO_LIVINGROOM:
                printState("going to the livingroom");
                TakeshiHRI::say("I will go to the livingroom");
                if(!TakeshiNavigation::getClose("living_room", 30000))
                    if(!TakeshiNavigation::getClose("living_room", 30000))
                        TakeshiNavigation::getClose("living_room", 30000);
                nextState= SM_RECOGNIZING_FACE;
                break;

           
            case SM_RECOGNIZING_FACE:
            printState("recognizing face");
            TakeshiHRI::waitAfterSay("Scanning the room for guests, please look at me",3000);
            if(TakeshiTasks::turnAndRecognizeFacenet(""))
                {
                    TakeshiHRI::waitAfterSay("Ok, I see you",1500);
                    TakeshiHRI::waitAfterSay("hello, my name is takeshi",1500);
                    TakeshiHRI::waitAfterSay("when confirmation is needed say Takeshi yes, or takeshi no",1500);
                    //TakeshiVision::stopFaceRecognition();
                    nextState=SM_ASK_FOR_NAME;
                 }
            break;

            
            case SM_ASK_FOR_NAME:
                printState("ask for name");
                TakeshiHRI::waitAfterSay("what's your name",1000);
                nextState=SM_WAIT_FOR_NAME;
                TakeshiHRI::enableSphinxMic(true);
                TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/receptionist_names.jsgf","receptionist");
                break;

            case SM_WAIT_FOR_NAME:
                printState("wait for name");
                if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                       std::cout << "PARSING WORD..." << std::endl;
                       //name=find_in_scentence(lastRecoSpeech, validCommandsNames);
                       if(TakeshiHRI::find_in_sentence(lastRecoSpeech,validCommandsNames,name)){
                           nextState = SM_COMFIRM_NAME;
                        }
                    }
                break;

            case SM_COMFIRM_NAME:
                TakeshiHRI::enableSphinxMic(false);
                printState("confirm name");
                TakeshiHRI::waitAfterSay("Did you say",1000);
                TakeshiHRI::waitAfterSay(name,1000);
                nextState=SM_WAIT_CONFIRMATION_NAME;
                TakeshiHRI::enableSphinxMic(true);
                break;

            case SM_WAIT_CONFIRMATION_NAME:
                printState("wait confirmation for name");

                if(TakeshiHRI::waitForUserConfirmation(userConfirmation, 5000)){
                    if(userConfirmation){
                        //BUG: train name is never cleared outside SM loop,
                        //Eventually will read: train_oscartrain_felipetrain_john etc...
                        train_name= train_name+name;
                        TakeshiHRI::waitAfterSay(name,1000);
                        TakeshiHRI::waitAfterSay("Im learning your face please stare at me",1000);
                        vfo = TakeshiVision::facenetRecognize(train_name);
                        vfo = TakeshiVision::facenetRecognize(train_name);
                        userConfirmation=false;
                        nextState=SM_ASK_FOR_DRINK;
                        TakeshiHRI::enableSphinxMic(false);

                    }
                    else{
                        TakeshiHRI::waitAfterSay("Could you repeat your name",1000);
                        TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/receptionist_names.jsgf","receptionist");
                        nextState=SM_WAIT_FOR_NAME;
                    }
                }
                break;

            case SM_ASK_FOR_DRINK:
                printState("ask for drink");
                TakeshiHRI::waitAfterSay("what would you like to drink",1000);
                nextState=SM_WAIT_FOR_DRINK;
                TakeshiHRI::enableSphinxMic(true);
                break;

            case SM_WAIT_FOR_DRINK:
                printState("wait for drink");
                TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/receptionist_drinks.jsgf","receptionist");

                if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                       std::cout << "PARSING WORD..." << std::endl;
                       //beverage=find_in_scentence(lastRecoSpeech, validCommandsDrinks);
                       if(TakeshiHRI::find_in_sentence(lastRecoSpeech,validCommandsDrinks,beverage)){
                            nextState = SM_COMFIRM_DRINK;
                        }
                    }
                break;

            case SM_COMFIRM_DRINK:
                TakeshiHRI::enableSphinxMic(false);
                printState("confirm drink");
                TakeshiHRI::waitAfterSay("Did you say",1000);
                TakeshiHRI::waitAfterSay(beverage,1000);
                nextState=SM_WAIT_CONFIRMATION_DRINK;
                TakeshiHRI::enableSphinxMic(true);
                break;

            case SM_WAIT_CONFIRMATION_DRINK:
                printState("wait confirmation for name");

                if(TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000)){
                    if(userConfirmation){
                        userConfirmation=false;
                        std::cout<<"check if this dink is available"<<std::endl;
                        it = find(AvailableDrinks.begin(), AvailableDrinks.end(), beverage);
                        if(it!=AvailableDrinks.end()){
                            nextState=SM_GO_FOR_ORDER;
                        }else{
                            nextState=SM_ANNOUNCE_UNAVAILABILITY_OF_DRINK;
                        }
                            TakeshiHRI::enableSphinxMic(false);
                    }
                    else{
                        TakeshiHRI::waitAfterSay("Could you repeat your favorite drink",1000);
                        TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/receptionist_drinks.jsgf","receptionist");
                        nextState=SM_WAIT_FOR_DRINK;
                    }
                }
                break;
            case SM_ANNOUNCE_UNAVAILABILITY_OF_DRINK:
                printState("announce_unavailability_of_drink");
                std::cout<<"announce it, and say ask for alternative drink"<<std::endl;
                //TakeshiHRI::waitAfterSay(beverage,1000);
                TakeshiHRI::waitAfterSay(beverage+" is not available, which other drink would you like?",3000);
                TakeshiHRI::enableSphinxMic(true);
                nextState=SM_WAIT_FOR_DRINK;
                break;
            case SM_GO_FOR_ORDER:
                printState("going to get order");
                TakeshiHRI::say("I will get your drink");
                if(!TakeshiNavigation::getClose("bar", 30000))
                    if(!TakeshiNavigation::getClose("bar", 30000))
                        TakeshiNavigation::getClose("bar", 30000);
                nextState=SM_TAKE_DRINK;
                break;
            case SM_TAKE_DRINK:
                printState("grasping drink");
                std::cout<<"aling with table bar, grasp drink"<<std::endl;
                //TakeshiHRI::waitAfterSay("I should grasp the drink here",2000);
                aux_drinks.clear();
                aux_drinks.push_back(beverage);
                TakeshiTasks::alignWithFrontTable();
                objectsCoordinates.z_max=0.9;
                if(TakeshiVision::detectSpecificYoloObject(aux_drinks,detectedObjs,10000,objectsCoordinates)){
                    obj_position.resize(3);
                    obj_position[0] = detectedObjs[0].pose.position.x;
                    obj_position[1] = detectedObjs[0].pose.position.y;
                    obj_position[2] = detectedObjs[0].pose.position.z;

                    TakeshiManip::hdGoTo(0, 0, 3000);
                    if(TakeshiTasks::graspObject(obj_position[0], obj_position[1], obj_position[2], false)){
                        TakeshiHRI::say("I'm verifying if I grasped the object");
                        TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                        TakeshiNavigation::moveDist(-0.2, 3000);
                        ros::Duration(2).sleep();
                        objectsCoordinates.z_max=0.9;
                        if(!TakeshiVision::detectSpecificYoloObject(aux_drinks,detectedObjs,1000,objectsCoordinates))
                            nextState=SM_DELIVER_DRINK;
                    }
                    
                }
                else
                    TakeshiHRI::say("I didn't find the drink, I will look for it again");

                break;

            case SM_DELIVER_DRINK:
                printState("delivering drink");
                std::cout<<"get close to persond and give them the drink"<<std::endl;
                TakeshiHRI::say("I will go to the livingroom");
                if(!TakeshiNavigation::getClose("living_room", 30000))
                    if(!TakeshiNavigation::getClose("living_room", 30000))
                        TakeshiNavigation::getClose("living_room", 30000);
                nextState=SM_FIND_PERSON_TO_DELIVER;
                break;


            case SM_FIND_PERSON_TO_DELIVER:
                std::cout << "SM FIND PERSON TO DELIVER"<< std::endl;
                std::cout << "name: "<<name<< std::endl;
                while (!TakeshiTasks::turnAndRecognizeFacenet(name, true) ) //BUSCAR NAME!
                //while(lastRecognizedFaces.size() < 1)
                {
                        ros::spinOnce();
                        TakeshiHRI::waitAfterSay("I am looking for you",3000);
                        std::cout << "Looking ......."<< std::endl;
                }        
                std::cout << "I FOUND YA"<< std::endl;
                nextState=  SM_RELEASE_OBJECT;
                
                break;     

            case SM_RELEASE_OBJECT:
                printState("giving drink to a human");
                if(TakeshiTasks::giveObjectToHuman())
                    /*if(drinks_delivered < 3)
                        nextState=SM_FIND_PERSON_WITHOUT_DRINK;
                    else*/
                        nextState=SM_FINAL_STATE;
                break;

            case SM_FINAL_STATE:
                printState("final state");
                TakeshiHRI::say("I finished my demostration, thank ypou for you attention");
                success=true;
                TakeshiManip::navigationPose(4000);
        }

        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}
