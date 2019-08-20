#include "ros/ros.h"
#include "takeshi_tools/TakeshiHardware.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiRepresentation.h"


enum state {
        SM_INIT,
        SM_WAIT_DOOR,
        SM_GOING_TO_START_POINT,
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
        SM_FIND_HOST,
        SM_FIND_GUEST_TO_POINT,
        SM_POINTING_TO_GUEST,
        SM_INTRODUCING_GUEST,
        SM_ASSIGN_PLACE,
        SM_AVAILABILITY_OF_SEAT,
        SM_POINTING_SEAT,
        SM_CHECK_NUMBER_OF_GUESTS,
        SM_GO_TO_THE_DOOR,
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

    return "john this is"+name+" . "+name+" likes "+beverage+". "+ name+ " this is john and he likes beer."; 
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
    


    bool userConfirmation=false;

    std::vector<std::string> validCommandsNames;              
    std::vector<std::string> validCommands;              
    std::vector<std::string> validCommandsDrinks;              
    std::string lastRecoSpeech;
    std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
    vision_msgs::VisionFaceObjects vfo;
    std::string host_name;
    std::map<std::string, std::vector<float> > knownlocations;
    host_name="john";
    float locX,locY,locA;
    float angleError, robot_x,robot_y,robot_a;

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

    ros::Rate rate(10);
    int nextState = SM_INIT;
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
                    nextState = SM_GOING_TO_START_POINT;
                break;
            case SM_GOING_TO_START_POINT:
                printState("going to starting point");
                    TakeshiHRI::say("I'm going to the start point");
                    TakeshiNavigation::moveDist(1.5,7000);
                    if(!TakeshiNavigation::getClose("start_receptionist",8000))
                        if(!TakeshiNavigation::getClose("start_receptionist",7000))
                            TakeshiNavigation::getClose("start_receptionist",7000);
                nextState=SM_GET_CLOSE_DOOR;
                break;

            case SM_GET_CLOSE_DOOR:
                printState("get close to the door");
                if(!TakeshiNavigation::getClose("door_receptionist",5000))
                        if(!TakeshiNavigation::getClose("door_receptionist",4000))
                            TakeshiNavigation::getClose("door_receptionist",4000);
                nextState=SM_RECOGNIZING_FACE;
                break;

            case SM_RECOGNIZING_FACE:
                printState("recognizing face");
                TakeshiHRI::waitAfterSay("open the door, please",2000);
                //posible move of face
                //check get face
                //vfo=TakeshiTasks::turnAndRecognizeFacenet("", false); //lastRecognizedFaces = TakeshiVision::getFaces("").recog_faces;
                //TakeshiHardware::stopRobot();
                
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
                //TakeshiVision::stopFaceRecognition();
                nextState=SM_ASK_FOR_NAME;
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
                //ros::Duration(.3).sleep();
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
                        //vfo = TakeshiVision::facenetRecognize("train_"+ name);
                        //vfo = TakeshiVision::facenetRecognize("train_"+name);

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
                TakeshiHRI::waitAfterSay("please look at me eyes",2000);
                TakeshiHRI::waitAfterSay("what's your favorite drink",1000);
                nextState=SM_WAIT_FOR_DRINK;
                //TakeshiVision::facenetTrain(name);
                //TakeshiVision::facenetTrain(name);
                vfo = TakeshiVision::facenetRecognize("train_"+ name);
                vfo = TakeshiVision::facenetRecognize("train_"+ name);
                TakeshiHRI::enableSphinxMic(true);
                break;

            case SM_WAIT_FOR_DRINK:
                printState("wait for drink");
                TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/receptionist_drinks.jsgf","receptionist");

                if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                       std::cout << "PARSING WORD..." << std::endl;
                       //beverage=find_in_scentence(lastRecoSpeech, validCommandsDrinks);
                        //TakeshiVision::facenetTrain(name);
                        //TakeshiVision::facenetTrain(name);
                        vfo = TakeshiVision::facenetRecognize("train_"+ name);
                        vfo = TakeshiVision::facenetRecognize("train_"+ name);
                       if(TakeshiHRI::find_in_sentence(lastRecoSpeech,validCommandsDrinks,beverage)){
                           nextState = SM_COMFIRM_DRINK;
                        }
                    }
                break;

            case SM_COMFIRM_DRINK:
                TakeshiHRI::enableSphinxMic(false);
                printState("confirm drink");
                TakeshiVision::facenetTrain(name);
                TakeshiHRI::waitAfterSay("Did you say",1000);
                TakeshiHRI::waitAfterSay(beverage,1000);
                //ros::Duration(.5).sleep();
                vfo = TakeshiVision::facenetRecognize("train_"+name);
                vfo = TakeshiVision::facenetRecognize("train_"+name);
                //TakeshiVision::facenetTrain(name);
                nextState=SM_WAIT_CONFIRMATION_DRINK;
                TakeshiHRI::enableSphinxMic(true);
                break;

            case SM_WAIT_CONFIRMATION_DRINK:
                printState("wait confirmation for name");

                if(TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000)){
                    if(userConfirmation){
                        userConfirmation=false;
                        nextState=SM_GUIDING_TO_LIVINGROOM;
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
                TakeshiTasks::guidePersonFacenet("living_room",name,25000);
                TakeshiHRI::waitAfterSay("we arrive to the living room, please stand behind me",2000);
                TakeshiKnowledge::addUpdateKnownLoc(name);
                nextState=SM_FIND_HOST;
                break;
            case SM_FIND_HOST:
                printState("Finding HOST)");
                TakeshiHRI::say("looking for "+host_name);
                if(TakeshiTasks::turnAndRecognizeFacenet(host_name,false)){
                    TakeshiHRI::say("I found you "+host_name);
                    TakeshiNavigation::getRobotPose(robot_x,robot_y, robot_a);
                    TakeshiKnowledge::getKnownLocation(host_name,locX,locY,locA);
                    angleError = atan2(locY-robot_y, locX-robot_x)- robot_a;
                    if(angleError >   M_PI) angleError -= 2*M_PI;
                    if(angleError <= -M_PI) angleError += 2*M_PI;
                    TakeshiManip::hdGoTo(0.0, 0.0, 3000);
                    std::cout<<"angleError: "<<angleError<<std::endl;
                    TakeshiNavigation::moveDistAngle(0.4,angleError,5000);
                    TakeshiNavigation::moveDistAngle(0,3.1415,5000);
                    arm[1]=0.0;
                    TakeshiManip::closeGripper(.04);
                    TakeshiManip::armGoToArticular(arm,3000);
                    nextState=SM_INTRODUCING_GUEST;
                }
                break;

            case SM_FIND_GUEST_TO_POINT:
                /*name="hugo";
                beverage="coke";*/            
                TakeshiHRI::say("looking for "+name);
                printState("find a guest to point");
                counter=0;
                TakeshiManip::hdGoTo(0, 0.3, 3000);
                TakeshiManip::torsoGoTo(.4,1000);
                vfo = TakeshiVision::facenetRecognize("");
                while (vfo.recog_faces.size()<1)
                {
                    ros::spinOnce();
                    TakeshiHRI::waitAfterSay("looking for a guest, please stand in front of me",3000);
                    ros::Duration(4.0).sleep();
                    vfo = TakeshiVision::facenetRecognize("");
                    if(counter > 2){
                        break;
                    }
                    counter++;
                }
                nextState=SM_POINTING_TO_GUEST;
                break;

            case SM_POINTING_TO_GUEST:
                printState("pointing to guest");
                TakeshiHRI::say("pointting to the guest");

                TakeshiKnowledge::getKnownLocation(name,locX,locY,locA);
                /*std::cout<<"locX: "<<locX<<std::endl;
                std::cout<<"locY: "<<locY<<std::endl;
                std::cout<<"locA: "<<locA<<std::endl;*/
                TakeshiKnowledge::getRobotPose(robot_x, robot_y, robot_a);
                angleError = atan2(locY-robot_y, locX-robot_x)- robot_a;
                if(angleError >   M_PI) angleError -= 2*M_PI;
                if(angleError <= -M_PI) angleError += 2*M_PI;
                if(angleError >   M_PI/2) angleError = M_PI/2;
                if(angleError <= -M_PI/2) angleError = -M_PI/2;
                /*std::cout<<"robot_x: "<<robot_x<<std::endl;
                std::cout<<"robot_y: "<<robot_y<<std::endl;
                std::cout<<"roaot_a: "<<robot_a<<std::endl;
                std::cout<<"angleError: "<<angleError<<std::endl;*/
                arm[1]=angleError;
                TakeshiManip::closeGripper(.04);
                TakeshiManip::armGoToArticular(arm,3000);
                TakeshiManip::hdGoTo(-M_PI, 0.0, 3000);
                nextState=SM_INTRODUCING_GUEST;
                break;

            case SM_INTRODUCING_GUEST:
                printState("introducing the guest");
                TakeshiHRI::waitAfterSay("Could I have your attention?, please. I'm going to introduce someone",2000);
                TakeshiHRI::waitAfterSay(generate_introduction(name,beverage),2000);
                nextState=SM_ASSIGN_PLACE;
            //assign a place
            case  SM_ASSIGN_PLACE:
                printState("chosing place");
                 if(seats[0]==false){
                    chair="chair_1";
                    nextState=SM_AVAILABILITY_OF_SEAT;
                 }
                 else{
                    chair="chair_2";
                    nextState=SM_AVAILABILITY_OF_SEAT;
                 }
                 /*else if(seats[1]==false){
                    chair="chair_2";
                    nextState=SM_AVAILABILITY_OF_SEAT;
                 }else if(seats[2]==false){
                    chair="chair_3";
                    nextState=SM_AVAILABILITY_OF_SEAT;
                 }else{
                    TakeshiHRI::waitAfterSay("All seats are occupied",1000);
                    number_of_guest++;
                    clean_var(&chair_index, &counter, seats);
                    nextState=SM_CHECK_NUMBER_OF_GUESTS;
                 }*/
                 break;

            case SM_AVAILABILITY_OF_SEAT:
                printState("checking chair");
                TakeshiHRI::waitAfterSay("I'm looking for an empty seat",3000);
                    if(!TakeshiNavigation::getClose(chair, 20000))
                        if(!TakeshiNavigation::getClose(chair, 20000))
                            TakeshiNavigation::getClose(chair, 20000);
                if(chair!="chair_2"){
                    TakeshiHardware::stopRobot();
                    TakeshiManip::hdGoTo(0, 0, 3000);
                    ros::spinOnce();
                    lastRecognizedFaces = TakeshiVision::getFaces("").recog_faces;
                    if(lastRecognizedFaces.size() < 1){
                        nextState=SM_POINTING_SEAT;
                    }else{
                        seats[chair_index]=true;
                        chair_index++;
                        TakeshiHRI::waitAfterSay("this seat is occupied, I'll check another seat",3000);
                        nextState=SM_ASSIGN_PLACE;
                    }
                    TakeshiVision::stopFaceRecognition();
                }
                else{
                    nextState=SM_POINTING_SEAT;
                } 
                break;

            case SM_POINTING_SEAT:
                //move manipulatior
                arm[1]=0.0;
                TakeshiManip::closeGripper(.04);
                TakeshiManip::armGoToArticular(arm,3000);
                TakeshiHRI::waitAfterSay("please sit there!",1000);
                TakeshiManip::navigationPose(4000);
                TakeshiManip::openGripper(.2);
                nextState= SM_CHECK_NUMBER_OF_GUESTS;
                break;

            case SM_CHECK_NUMBER_OF_GUESTS:
                if(number_of_guest<1){
                        std::cout<<"number of guest: "<<number_of_guest<<std::endl;
                        number_of_guest++;
                        clean_var(&chair_index, &counter, seats);
                        nextState=SM_GO_TO_THE_DOOR;
                    }
                else{

                    nextState=SM_FINAL_STATE;

                }


            case SM_GO_TO_THE_DOOR:
                printState("go to the door");
                TakeshiHRI::say("I will go to the entrance door");
                if(!TakeshiNavigation::getClose("door_1", 30000))
                    if(!TakeshiNavigation::getClose("door_1", 30000))
                        TakeshiNavigation::getClose("door_1", 30000);

                TakeshiHRI::say("I have arrived to the door");
                nextState=SM_RECOGNIZING_FACE;
                break;

            case SM_FINAL_STATE:
                TakeshiHRI::waitAfterSay("The test has finished",2000);
                    TakeshiManip::navigationPose(4000);
                    TakeshiManip::openGripper(.2);  
                    success=true;
                break;
            
        }
  
        rate.sleep();
        ros::spinOnce();
    }
    return 1;
}
