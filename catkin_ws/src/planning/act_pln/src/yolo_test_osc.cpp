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


enum state {
        SM_INIT,
        SM_WAIT_DOOR,
        SM_GO_TO_BAR,
        SM_CHECK_DRINKS,
        SM_GO_TO_LIVINGROOM,
        SM_MATCH_PERSON_TO_DRINK,
        SM_FIND_PERSON_WITHOUT_DRINK,
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

std::string find_in_scentence(std::string s, std::vector<std::string> &delimiters){

    int prev_len=0;
    size_t pos = 0;
    std::string token;

    for(size_t i=0;i<delimiters.size();i++){
        while ((pos = s.find(delimiters[i])) != std::string::npos) {
            prev_len=s.length();
            token = s.substr(0, pos);
            //std::cout << token << std::endl;
            s.erase(0, pos + delimiters[i].length());
            if(s.length()<prev_len){
            return delimiters[i];
            }
        }
    }

    return "";
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
    std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
    std::vector<std::string> validCommandsNames;
    std::vector<std::string> validCommandsDrinks; 
    std::vector<std::string> AvailableDrinks; 
    std::vector<std::string>::iterator it; 


    ros::Rate rate(10);
    int nextState = SM_RECOGNIZING_FACE;
    int number_of_guest=0;
    int counter=0;
  
    bool success=false;
    std::string name="";
    std::string beverage="";

    //names
    validCommandsNames.push_back("hugo");
    validCommandsNames.push_back("jesus");
    validCommandsNames.push_back("adrian");
    validCommandsNames.push_back("edgar");
    validCommandsNames.push_back("oliver");
    validCommandsNames.push_back("mary");
    validCommandsNames.push_back("jack");
    validCommandsNames.push_back("john");
    validCommandsNames.push_back("marco");
    validCommandsNames.push_back("roberto");
    validCommandsNames.push_back("diego");
    validCommandsNames.push_back("alex");
    validCommandsNames.push_back("alejandra");
    validCommandsNames.push_back("oscar");


    //drinks
    validCommandsDrinks.push_back("martini");
    validCommandsDrinks.push_back("gin tonic");
    validCommandsDrinks.push_back("margarita");
    validCommandsDrinks.push_back("mojito");
    validCommandsDrinks.push_back("red wine");
    validCommandsDrinks.push_back("chardonnay");
    validCommandsDrinks.push_back("tequila");
    validCommandsDrinks.push_back("beer");
    validCommandsDrinks.push_back("whiskey");
    validCommandsDrinks.push_back("rum");


    //available drinks

    //AvailableDrinks.push_back("martini");
    //AvailableDrinks.push_back("gin tonic");
    //AvailableDrinks.push_back("margarita");
    //AvailableDrinks.push_back("mojito");
    //AvailableDrinks.push_back("red wine");
    //AvailableDrinks.push_back("chardonnay");
    AvailableDrinks.push_back("tequila");
    AvailableDrinks.push_back("beer");
    //AvailableDrinks.push_back("rum");
    AvailableDrinks.push_back("whiskey");

    std::vector<vision_msgs::VisionObject> detectedObjs;


    
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
                    nextState = SM_GO_TO_BAR;
                break;
            case SM_GO_TO_BAR:
                printState("going to the bar");
                TakeshiHRI::say("I will go to the bar");
                if(!TakeshiNavigation::getClose("bar", 30000))
                    if(!TakeshiNavigation::getClose("bar", 30000))
                        TakeshiNavigation::getClose("bar", 30000);
                    nextState=SM_CHECK_DRINKS;
                break;
            case SM_CHECK_DRINKS:
                printState("Checking for available drinks");
                std::cout<<"aling to the bar table, yolo recognized drink and add drinks too valids"<<std::endl;
                nextState=SM_GO_TO_LIVINGROOM;
                break;
                         
            case SM_GO_TO_LIVINGROOM:
                printState("going to the livingroom");
                TakeshiHRI::say("I will go to the livingroom");
                if(!TakeshiNavigation::getClose("living_room", 30000))
                    if(!TakeshiNavigation::getClose("living_room", 30000))
                        TakeshiNavigation::getClose("living_room", 30000);
                nextState=SM_MATCH_PERSON_TO_DRINK;
                break;
            case SM_MATCH_PERSON_TO_DRINK:
                printState("matching person with drink");
                std::cout<<"find people and matching to drink"<<std::endl;
                nextState=SM_FIND_PERSON_WITHOUT_DRINK;
                break;
            case SM_FIND_PERSON_WITHOUT_DRINK:
                printState("getting close to person");
                std::cout<<"ask people to faced you"<<std::endl;
                if(TakeshiTasks::findPerson()){
                    number_of_guest++;
                    nextState=SM_RECOGNIZING_FACE;
                }
                break;
            case SM_RECOGNIZING_FACE:
                printState("recognizing face");
                //posible move of face
                //check get face
                lastRecognizedFaces = TakeshiVision::facenetRecognize(std::string id)("");
                //TakeshiHardware::stopRobot();
                TakeshiManip::hdGoTo(0, 0.7, 3000);

                while(lastRecognizedFaces.size() < 1)
                {
                        ros::spinOnce();
                        TakeshiHRI::waitAfterSay("looking for a guest",3000);
                        //ros::spinOnce();
                        ros::Duration(4.0).sleep();
                        lastRecognizedFaces = TakeshiVision::facenetRecognize(std::string id);
                        if(counter > 5)
                                break;
                        counter++;
                }
                //TakeshiHRI::waitAfterSay("Ok, I see you",1500);
                //TakeshiHRI::waitAfterSay("hello, my name is takeshi",1500);
                //TakeshiHRI::waitAfterSay("when confirmation is needed say Takeshi yes, or takeshi no",1500);
                TakeshiVision::stopFaceRecognition();
                nextState=SM_ASK_FOR_NAME;
                break;
            
            case SM_ASK_FOR_NAME:SM_FINAL_STATE
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
                       name=find_in_scentence(lastRecoSpeech, validCommandsNames);
                       if(name!=""){
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
                TakeshiHRI::waitAfterSay("what's your favorite drink",1000);
                nextState=SM_WAIT_FOR_DRINK;
                TakeshiHRI::enableSphinxMic(true);
                break;

            case SM_WAIT_FOR_DRINK:
                printState("wait for drink");
                TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/receptionist_drinks.jsgf","receptionist");
                
                if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                       std::cout << "PARSING WORD..." << std::endl;
                       beverage=find_in_scentence(lastRecoSpeech, validCommandsDrinks);
                       if(beverage!=""){
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

                TakeshiTasks::alignWithFrontTable();
                TakeshiVision::detectSpecificYoloObject(AvailableDrinks,detectedObjs,.9,10000);
                //TakeshiVision::detectAllYoloObjects(detectedObjs, 10000);

                nextState=SM_TAKE_DRINK;
                success=true;
                break;
            case SM_TAKE_DRINK:
                printState("grasping drink");
                std::cout<<"aling with table bar, grasp drink"<<std::endl;
                TakeshiHRI::waitAfterSay("I should grasp the drink here",2000);
                nextState=SM_DELIVER_DRINK;
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
                printState("finding person to deliver drink");
                TakeshiHRI::say("Hello Human, i will find you");
                if(TakeshiTasks::findPerson("", -1, TakeshiTasks::STANDING, false))
                    nextState=SM_RELEASE_OBJECT;                       
                break;

            case SM_RELEASE_OBJECT:
                printState("giving drink to a human");
                TakeshiTasks::giveObjectToHuman();
                if(number_of_guest<2)
                    nextState=SM_FIND_PERSON_WITHOUT_DRINK;
                else
                    nextState=SM_FINAL_STATE;
                break;

            case SM_FINAL_STATE:
                printState("final state");
                success=true;
                TakeshiManip::navigationPose(4000);
        }
  
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}
