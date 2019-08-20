#include "ros/ros.h"
#include "takeshi_tools/TakeshiHardware.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiRepresentation.h"

ros::Publisher pubName;
ros::Publisher pubDrink; 

enum state {
    SM_INIT,
    SM_WAIT_DOOR,
    SM_WAIT_FOR_START_SIGNAL,
    SM_GET_CLOSE_DOOR,
    SM_RECOGNIZING_FACE,
    SM_ASK_FOR_NAME,
    SM_WAIT_FOR_NAME,
    SM_COMFIRM_NAME,
    SM_WAIT_CONFIRMATION_NAME,
    SM_ASK_FOR_DRINK,
    SM_WAIT_FOR_DRINK,
    SM_COMFIRM_DRINK,
    SM_WAIT_CONFIRMATION_DRINK,
    SM_GUIDING_TO_LIVINGROOM,
    SM_INTRODUCING_GUEST,
    SM_POINTING,
    SM_GO_TO_OFFICE,
    SM_FINAL_STATE
};

void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        CASE: "<< st << "\033[0m" << std::endl;
}

void clean_var(int* chair_index, int* counter, std::vector<bool> &seats){
    *chair_index=0;
    *counter=0;
    for (int i = 0; i < seats.size(); ++i)
    {
        seats[i]=false;
    }
}

std::string generate_introduction(std::string name, std::string beverage){

    return "Justina the guest name is "+name+" and he likes "+ beverage; 
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "receptionist");
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

    pubName = n.advertise<std_msgs::String>("/alexa/who_person", 1);
    pubDrink = n.advertise<std_msgs::String>("/alexa/drink", 1); 
    


    bool userConfirmation=false;

    std::vector<std::string> validCommandsNames;              
    std::vector<std::string> validCommands;              
    std::vector<std::string> validCommandsDrinks;              
    std::string lastRecoSpeech;
    std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
    vision_msgs::VisionFaceObjects vfo;
    std::string host_name;

    std_msgs::String msg_name;
    std_msgs::String msg_drink;

    std::map<std::string, std::vector<float> > knownlocations;
    host_name="john";
    float locX,locY,locA;
    float angleError, robot_x,robot_y,robot_a;

    //names
    validCommandsNames.push_back("charlie");
    validCommandsNames.push_back("thomas");
    validCommandsNames.push_back("parker");
    //drinks
    validCommandsDrinks.push_back("chocolate milk");
    validCommandsDrinks.push_back("juice");
    validCommandsDrinks.push_back("lemonade");

    ros::Rate rate(10);
    int nextState = SM_WAIT_FOR_START_SIGNAL;
    int number_of_guest=0;
    int counter=0;
    int i =0;
  
    bool success=false;
    std::string name="";
    std::string beverage="";
    std::vector<bool>seats;
    seats.resize(1);
    std::string chair="";
    int chair_index=0;
    int attemps_finding=0;
    clean_var(&chair_index,&counter,seats);
    

    std::vector<float> arm;
    //arm pointing
    arm.push_back(-0.3);
    arm.push_back(0.0);
    arm.push_back(-1.3);
    arm.push_back(0.0);
    
    while (ros::ok() && !success) {

        switch(nextState){
            case SM_INIT:
                printState("SM START");
                TakeshiHRI::waitAfterSay("waitting for the door to be open",2000);
                nextState=SM_WAIT_DOOR;
                break;

            case SM_WAIT_DOOR:
                printState("wait for the door");
                if(!TakeshiNavigation::obstacleInFront())
                    nextState = SM_GET_CLOSE_DOOR;
                break;

            case SM_WAIT_FOR_START_SIGNAL:
                printState("waitting start signal");
                if(TakeshiHRI::waitForSpecificSentence("justina start", 1000)){
                    nextState=SM_GET_CLOSE_DOOR;
                }
                break;

            case SM_GET_CLOSE_DOOR:
                printState("get close to the door");
                if(!TakeshiNavigation::getClose("door_1",30000))
                        if(!TakeshiNavigation::getClose("door_1",30000))
                            TakeshiNavigation::getClose("door_1",30000);
                nextState=SM_RECOGNIZING_FACE;
                break;

            case SM_RECOGNIZING_FACE:
                printState("recognizing face");
                if(number_of_guest<2){
                    TakeshiHRI::waitAfterSay("get in",2000);
                    TakeshiManip::hdGoTo(0, 0.3, 3000);
                    TakeshiManip::torsoGoTo(.4,1000);
                    vfo = TakeshiVision::facenetRecognize("");
                    while (vfo.recog_faces.size()<1)
                    {
                            ros::spinOnce();
                            TakeshiHRI::waitAfterSay("looking for someone, please stand in front of me",3000);
                            //ros::spinOnce();
                            ros::Duration(4.0).sleep();
                            vfo = TakeshiVision::facenetRecognize("");
                            if(counter > 5)
                                    break;
                            counter++;
                    }
                    //TakeshiHRI::waitAfterSay("Ok, I see you. Hello, my name is Takeshi, when confirmation is needed say Takeshi yes, or takeshi no ",1500);
                    name=vfo.recog_faces[0].id;
                    TakeshiHRI::waitAfterSay(name+" nice to see you again",2000);                    
                    number_of_guest++;
                    nextState=SM_ASK_FOR_DRINK;

                }
                else{
                    TakeshiManip::hdGoTo(0, 0.3, 3000);
                    TakeshiManip::torsoGoTo(.4,1000);
                    vfo = TakeshiVision::facenetRecognize("");
                    while (vfo.recog_faces.size()<1)
                    //while(lastRecognizedFaces.size() < 1)
                    {
                            ros::spinOnce();
                            TakeshiHRI::waitAfterSay("looking for a guest, please stand in front of me",3000);
                            //ros::spinOnce();
                            ros::Duration(4.0).sleep();
                            vfo = TakeshiVision::facenetRecognize("");
                            if(counter > 5)
                                    break;
                            counter++;
                    }
                    TakeshiHRI::waitAfterSay("Ok, I see you. Hello, my name is Takeshi, when confirmation is needed say Takeshi yes, or takeshi no ",1500);
                    number_of_guest++;
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
                if(number_of_guest>2){
                    TakeshiHRI::waitAfterSay("plese stared at me, I'm going to train your face",2000);
                    vfo = TakeshiVision::facenetRecognize("train_"+ name);
                    vfo = TakeshiVision::facenetRecognize("train_"+name);
                    vfo = TakeshiVision::facenetRecognize("train_"+name);
                    vfo = TakeshiVision::facenetRecognize("train_"+name);
                    vfo = TakeshiVision::facenetRecognize("train_"+name);
                    TakeshiHRI::waitAfterSay("face trained",2000);
                }
                TakeshiHRI::waitAfterSay("what do you want to drink today?",1000);
                nextState=SM_WAIT_FOR_DRINK;
                TakeshiHRI::enableSphinxMic(true);
                break;

            case SM_WAIT_FOR_DRINK:
                printState("wait for drink");
                TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/receptionist_drinks.jsgf","receptionist");

                if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                       std::cout << "PARSING WORD..." << std::endl;
                       if(TakeshiHRI::find_in_sentence(lastRecoSpeech,validCommandsDrinks,beverage)){
                           nextState = SM_COMFIRM_DRINK;
                        }
                    }
                break;

            case SM_COMFIRM_DRINK:
                TakeshiHRI::enableSphinxMic(false);
                printState("confirm drink");
                //TakeshiVision::facenetTrain(name);
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
                        nextState=SM_GUIDING_TO_LIVINGROOM;
                        msg_name.data = name;
                        msg_drink.data = beverage;
                        std::cout << "name   msgs --- >" << msg_name.data << std::endl;
                        std::cout << "data   msgs --- >" << msg_name.data << std::endl;
                        pubName.publish(msg_name);
                        pubDrink.publish(msg_drink);
                        ros::spinOnce();
                        ros::Duration(0.2).sleep();
                        TakeshiHRI::enableSphinxMic(false);
                    }
                    else{
                        TakeshiHRI::waitAfterSay("Could you repeat your favorite drink",1000);
                        TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/receptionist_drinks.jsgf","receptionist");
                        nextState=SM_WAIT_FOR_DRINK;
                    }
                }
                break;

            case SM_GUIDING_TO_LIVINGROOM:
                printState("guiding person to livingroom");
                TakeshiHRI::waitAfterSay("I will guide you to the livingroom. Follow me, please!",2000);
                TakeshiNavigation::moveDistAngle(0,M_PI,1500);
                //TakeshiTasks::guidePerson("living_room",15000);
                TakeshiTasks::guidePersonFacenet("living_room","",60000);
                TakeshiKnowledge::addUpdateKnownLoc(name);
                nextState=SM_INTRODUCING_GUEST;
                break;

            case SM_INTRODUCING_GUEST:
                printState("introducing the guest");
                TakeshiHRI::waitAfterSay(generate_introduction(name,beverage),2000);
                nextState=SM_POINTING;

            case SM_POINTING:
                //move manipulatior
                TakeshiManip::closeGripper(.04);
                TakeshiManip::armGoToArticular(arm,3000);
                TakeshiHRI::waitAfterSay("here is the livingroom, Justina will bring you something to drink",1000);
                TakeshiManip::navigationPose(4000);
                TakeshiManip::openGripper(.2);
                nextState=SM_GO_TO_OFFICE;
                break;
            case SM_GO_TO_OFFICE:
                printState("get close to office");
                if(!TakeshiNavigation::getClose("start_receptionist",30000))
                        if(!TakeshiNavigation::getClose("start_receptionist",30000))
                            TakeshiNavigation::getClose("start_receptionist",30000);
                nextState=SM_WAIT_FOR_START_SIGNAL;
            break;
            case SM_FINAL_STATE:
                success=true;
            break;
        }
  
        rate.sleep();
        ros::spinOnce();
    }
    return 1;
}
