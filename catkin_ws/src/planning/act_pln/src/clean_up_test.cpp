#include <iostream>
#include <algorithm>
#include <ros/package.h>
#include <stack>
#include <ros/ros.h>

#include "hri_msgs/RecognitionResult.h"

#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiNavigation.h"

enum state {
        SM_INIT_STATE,
        SM_WAIT_FOR_COM_PLACE,
        SM_GOTO_MESS,
        SM_GOTO_MESS_CONF,
        SM_GOTO_EXTRA_CHALLENGE,
        SM_OPEN_DOOR,
        SM_OPEN_FRIDGE,
        SM_FIND_OBJS,
        SM_FIND_OBJ_TABLE,
        SM_FIND_OBJ_FLOOR,
        SM_FIND_OBJ_SOFA,
        SM_GRASP_OBJ,
        SM_GOTO_ASK_FOR_LOCATION,
        SM_GRASP_OBJ_TABLE,
        SM_GRASP_OBJ_FLOOR,
        SM_GOTO_TIDY,
        SM_GOTO_SPOKEN_LOC,
        SM_ASK_FOR_LOCATION,
        SM_PLACE_OBJ,
        SM_FINAL_STATE //goto human
};

void printState(std::string st);

std::string getSpokenLocation(std::string recog, std::vector<std::string> locations);

int main(int argc, char *argv[]) {
        std::cout << "||------Clean Up test------||" << '\n';
        ros::init(argc, argv,"clean_up_test");
        ros::NodeHandle n;
        ros::Rate loop(0.5);

        TakeshiHRI::setNodeHandle(&n);
        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

        std::string pathToKnowledge = ros::package::getPath("knowledge");
        string pathObjectTidyUp=pathToKnowledge+"/navigation/clean_up_test.txt";
        //---This is where the robot starts returns and ask for locations ---//

        std::stringstream takeshi_say;
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        std::map<std::string, std::string> tidyUpPlaces;
        std::map<std::string, std::string>::iterator it;
        std::stack<std::string> messyPlaces;
        
        std::string tidyPlace;
               
        vision_msgs::VisionObject objToGrasp;
        geometry_msgs::Pose poseToGrasp;
        std::stringstream ss;

        std::string endLocation ="initial_point";
        
        bool userConfirmation = false;

        int tryCounter=0;

        TakeshiKnowledge::getKnownObjectsLocationFromFile(pathObjectTidyUp,tidyUpPlaces);

        std::cout << "Object Locations:" <<  tidyUpPlaces.size()<<'\n';
        for(std::map<std::string,std::string>::const_iterator it = tidyUpPlaces.begin();
            it != tidyUpPlaces.end(); ++it)
        {
                std::cout << it->first << ": " << it->second << "\n";
        }

        std::map<std::string, std::vector<float> > knownLocations;
        std::map<std::string, std::vector<float> >::iterator it_loc;
        std::vector<string> locations;
        TakeshiKnowledge::getKnownLocations(knownLocations);
        std::cout << "Known Locations:" <<  knownLocations.size()<<'\n';
        for(std::map<std::string,std::vector<float> >::const_iterator it = knownLocations.begin();
            it != knownLocations.end(); ++it)
        {
                std::cout << it->first << ": " << it->second[0]
                          << it->second[1]
                          << it->second[2] << "\n";
                locations.push_back(it->first);
        }

        std::vector<std::string> validCommands;
        validCommands.push_back("tidy up the bedroom");
        validCommands.push_back("bedroom");

        validCommands.push_back("tidy up the dining room");
        validCommands.push_back("dining room");

        validCommands.push_back("tidy up the living room");
        validCommands.push_back("living room");

        validCommands.push_back("tidy up the kitchen");
        validCommands.push_back("kitchen");

        // std::vector<std::string> validPlaces;
        // validPlaces.push_back("go to shelf");
        // validPlaces.push_back("go to chargin table");
        // validPlaces.push_back("go to edgar 1");
        // validPlaces.push_back("go to byron");

        std::string tidy_up_location, lastRecoSpeech;
        bool tidyUpFloor;

        /*In general the robot goes to messy location, look for objects and
           deposits them on tidyUpplace if no objects are found it turn a bit
           and looks again, if it turns more than 180 degrees it stops and finishes*/

        state nextState=SM_INIT_STATE;

        double angle=0.0, step = 33*M_PI/180;
        double advance=0.00, adv_step=0.2;
        bool success = false;
        const int max_grasp_tries = 1;
        int attempts=3, grasp_attempts = max_grasp_tries;
        std::size_t found;

        //TakeshiHRI::loadGrammarSpeechRecognized("clean_up_test.xml");
        std::cout << "Stating state machine" << '\n';
        while (ros::ok() && !success)
        {
                switch (nextState)
                {

                // case SM_WAIT_FOR_COM_PLACE:
                //         printState("Wating for start command");
                //         TakeshiHRI::enableSpeechRecognized(false);
                //         if(TakeshiManip::isTheHandPressed()) {
                //                 cout << "I am waiting" << endl;
                //                 nextState = SM_WAIT_FOR_COM_PLACE;
                //         }
                //         TakeshiHRI::enableSpeechRecognized(true);
                //         break;

                case SM_INIT_STATE:
                        if (attempts > 2) {
                                TakeshiHRI::waitAfterSay("Tell me what to do!", 3000);
                                attempts=0;
                        }
                        
                        //TakeshiHRI::enableSpeechRecognized(true);  //virtualosa (virtual machine) deprecated
                        TakeshiHRI::enableSphinxMic(true);
                        TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/clean_up.jsfg", "clean_up");
                        TakeshiVision::startQRReader();
                        ros::spinOnce();
                        loop.sleep();
                        
                        if(TakeshiHRI::waitForSpecificSentence(validCommands, lastRecoSpeech, 7000)) {
                                if(lastRecoSpeech.find("bedroom") != std::string::npos) {
                                        tidy_up_location="bedroom";
                                        tidyUpFloor=true;
                                        TakeshiHRI::say( takeshi_say.str());

                                        messyPlaces.push("bedroom");
                                        //...One for each possible tidy up
                                        TakeshiVision::loadSpecificTrainingDir("bedroom");

                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("dining room") != std::string::npos) {
                                        tidy_up_location="dining_room";
                                        tidyUpFloor=false;
                                        messyPlaces.push("dining_room");
                                        //...One for each possible tidy up
                                        TakeshiVision::loadSpecificTrainingDir("dining_room");
                                        
                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("living room") != std::string::npos) {
                                        tidy_up_location="living_room";
                                        tidyUpFloor=true;
                                        messyPlaces.push("living_room");
                                        //...One for each possible tidy up
                                        TakeshiVision::loadSpecificTrainingDir("living_room");

                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("kitchen") != std::string::npos) {
                                        tidy_up_location="kitchen";
                                        tidyUpFloor=false;
                                        messyPlaces.push("kitchen");
                                        //...One for each possible tidy up
                                        TakeshiVision::loadSpecificTrainingDir("kitchen");

                                        nextState=SM_GOTO_MESS_CONF;
                                }

                                if(tidy_up_location.compare("") != 0 && nextState == SM_GOTO_MESS_CONF) {
                                        //TakeshiHRI::enableSpeechRecognized(false);
                                        TakeshiHRI::enableSphinxMic(false);
                                        ss.str("");
                                        ss << "Do you want me tidy up the "<<
                                        tidy_up_location << "?";
                                        
                                        TakeshiHRI::waitAfterSay(ss.str(), 3000);
                                        TakeshiHRI::enableSphinxMic(true);
                                        //TakeshiHRI::loadGrammarSpeechRecognized("clean_up_confirm.xml"); //virutalosa deprecated
                                        //TakeshiHRI::enableSpeechRecognized(true);
                                }
                        }
                        attempts++;
                        break;

                case SM_GOTO_MESS_CONF:
                        cout << "State machine: SM_GOTO_MESS_CONF" << endl;

                        TakeshiHRI::waitForUserConfirmation(userConfirmation, 7000);

                        if(userConfirmation) {
                                TakeshiHRI::waitAfterSay("Ok", 4000);
                                TakeshiVision::stopQRReader();
                                //TakeshiHRI::enableSpeechRecognized(false);  //virutalosa deprecated
                                TakeshiHRI::enableSphinxMic(false);
                                TakeshiVision::loadObjectTrainDir();
                                
                                nextState = SM_GOTO_MESS;
                        }
                        else{
                                nextState = SM_INIT_STATE;
                                TakeshiHRI::waitAfterSay("Sorry, please repeat the command", 4000);
                                //TakeshiHRI::loadGrammarSpeechRecognized("clean_up_test.xml");  //virtualosa deprecated
                        }

                        break;

                                
                case SM_GOTO_MESS:

                        printState("Going to mess");
                        //TakeshiHRI::loadGrammarSpeechRecognized("clean_up_test.xml");  //virtualosa deprecated

                        if (!messyPlaces.empty()) {

                                takeshi_say.str(std::string());
                                takeshi_say << "I am going to clean the " << messyPlaces.top();
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 3000);
                        }

                        if (messyPlaces.empty()) {
                                nextState=SM_FINAL_STATE;
                                takeshi_say.str(std::string());
                                takeshi_say << "Location not detected!";
                        }

                        else if(TakeshiNavigation::getClose(messyPlaces.top(),100000))
                        {
                                TakeshiNavigation::moveDist(advance,3000);
                                tidyPlace = messyPlaces.top();
                                if(tidyPlace.compare("sofa")==0)
                                {
                                        nextState = SM_FIND_OBJ_SOFA;
                                        //SOFA esta hardcodeado, el plano no lo encuentra chidoris...
                                        //Vaaaa
                                }
                                else if (tidyUpFloor)
                                {
                                        nextState=SM_FIND_OBJ_FLOOR;
                                }
                                else
                                {
                                        nextState=SM_FIND_OBJ_TABLE;
                                }
                        }
                        if (grasp_attempts<=0)
                        {
                                //validar agarre

                                nextState=SM_FINAL_STATE;
                        }
                        if(advance>0.4)
                        {
                                
                                nextState=SM_GOTO_MESS;
                                TakeshiNavigation::getClose(messyPlaces.top(),100000);

                                if(tidy_up_location.compare("bedroom")==0) {
                                    tidyUpFloor=true;
                                    nextState=SM_FIND_OBJ_FLOOR;

                                }
                                else if(tidy_up_location.compare("dining_room")==0) {
                                        
                                        tidyUpFloor=false;
                                         nextState=SM_FIND_OBJ_TABLE;
                                }
                                else if(tidy_up_location.compare("living_room")==0) {
                                        
                                        tidyUpFloor=true;
                                        nextState=SM_FIND_OBJ_FLOOR;
                                }
                                else if(tidy_up_location.compare("kitchen")==0) {
                                        
                                        tidyUpFloor=false;
                                        nextState=SM_FIND_OBJ_TABLE;
                                }
                        }

                        break;
                case SM_FIND_OBJ_FLOOR:
                        printState("Finding objects on location");
                        //TakeshiNavigation::moveDistAngle(0,angle,5000);
                        TakeshiHRI::say("I am finding objects on location" );
                        
                        //##############################33
                        TakeshiManip::hdGoTo(0,-1.0,5000);
                        //if (TakeshiVision::detectAllYoloObjects(recognizedObjects, 2000))
                        if (TakeshiVision::detectObjectsFloor(recognizedObjects, true))
                        {
                                nextState = SM_GRASP_OBJ_FLOOR;
                                //Are all messy objects on the floor?
                                //No some are in table or sofa
                        }
                        /*else if(angle<M_PI/3) //if nothing is found turns
                           {
                                angle+=step;
                                std::cout << "Debug<> Angle is" <<  angle <<'\n';
                           }*/
                        else
                        {
                                //messyPlaces.pop();
                                //nextState = SM_GOTO_MESS;
                                //In case it tried to grasp to many times advance
                                advance+=adv_step;
                                TakeshiNavigation::moveDist(advance,3000);
                                nextState=SM_GOTO_MESS;
                        }
                        break;

                case SM_FIND_OBJ_TABLE:
                        printState("Finding objects on location");
                        takeshi_say.str(std::string());
                        takeshi_say << "I am finding objects on location: " << messyPlaces.top();
                        TakeshiHRI::say(takeshi_say.str() );

                        //###################
                        TakeshiTasks::alignWithTable(0.5, false);

                        //if (TakeshiVision::detectObjects(recognizedObjects, true))
                        if (TakeshiVision::detectAllYoloObjects(recognizedObjects, 2000))
                        {
                                nextState = SM_GRASP_OBJ_TABLE;
                        }
                        else
                        {   
                                //detect 2 veces nomas
                                //messyPlaces.pop();
                                if(tryCounter<2){

                                nextState = SM_GOTO_MESS;
                                tryCounter++;

                                }
                                else {

                                    nextState = SM_FINAL_STATE;


                            }
                        }

                        break;
                case SM_FIND_OBJ_SOFA:
                        printState("Finding objects on location");
                        takeshi_say.str(std::string());
                        takeshi_say << "I am finding objects on location: " << messyPlaces.top();
                        TakeshiHRI::say(takeshi_say.str() );
                        TakeshiTasks::alignWithTable(0.5,false);

                        //#################33
                        if (TakeshiVision::detectAllObjectsOnPlane(recognizedObjects,0.42))
                        {
                                nextState = SM_GRASP_OBJ_TABLE;
                        }
                        else
                        {
                                //messyPlaces.pop();
                                nextState = SM_GOTO_MESS;
                        }

                        break;

                case SM_GRASP_OBJ_FLOOR:
                        printState("Grasping objects floor");
                        objToGrasp = recognizedObjects[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I am grasping the "<< objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::say( takeshi_say.str());
                        TakeshiManip::hdGoTo(0,0.0,5000);

                        if(TakeshiTasks::graspObjectOnFloorFromAbove(
                                   poseToGrasp.position.x,
                                   poseToGrasp.position.y,
                                   poseToGrasp.position.z,
                                   0.0,
                                   false))
                        {
                                nextState = SM_GOTO_TIDY;
                        }

                        else
                        {
                                //messyPlaces.pop();
                                //grasp_attempts--;
                                advance+=adv_step;
                                TakeshiNavigation::moveDist(advance,3000);
                                nextState = SM_FIND_OBJ_FLOOR;

                        }
                        break;

                case SM_GRASP_OBJ_TABLE:

                        printState("Grasping objects table");
                        objToGrasp = recognizedObjects[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I am grasping the "<< objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::say( takeshi_say.str());
                        TakeshiManip::hdGoTo(0,0.0,5000);

                        if(TakeshiTasks::graspObjectLateral(
                                   poseToGrasp.position.x,
                                   poseToGrasp.position.y,
                                   poseToGrasp.position.z,
                                   false))
                        {
                                nextState = SM_GOTO_TIDY;
                        }
                        else
                        {
                                grasp_attempts--;
                                nextState = SM_GOTO_MESS;
                        }

                        break;

                case SM_GOTO_TIDY:

                        printState("Going to tidy up location");
                        it = tidyUpPlaces.find(objToGrasp.id);
                        if (it != tidyUpPlaces.end())
                        {
                                std::cout << "Going to:" << it->second <<std::endl;
                                if(TakeshiNavigation::getClose(it->second,200000))
                                {
                                        nextState=SM_PLACE_OBJ;
                                }
                        }
                        // else if(tidyUpFloor)
                        // {
                        //         std::cout << "Going to: the sound_toy";
                        //         if(TakeshiNavigation::getClose("sound_toy",200000))
                        //         {
                        //                 nextState=SM_PLACE_OBJ;
                        //         }

                        // }

                        break;

                // case SM_GOTO_ASK_FOR_LOCATION:
                //         printState("Go To Asking for location");
                //         //Here if there is no tidy up location the robot ask for
                //         //delivery location
                //         //where should I put this object
                //         TakeshiHRI::say("I do not know where this goes, I will go ask!");
                //         if(TakeshiNavigation::getClose(humanLocation,150000))
                //         {
                //                 nextState=SM_ASK_FOR_LOCATION;
                //         }
                //         break;

                // case SM_ASK_FOR_LOCATION:
                //         //ask for Location
                //         TakeshiHRI::waitAfterSay( "Human, Where should I put this object",1000);
                //         TakeshiHRI::enableSpeechRecognized(true);
                //         lastRecoSpeech = "";
                //         //delay
                //         if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech,7000))
                //         {
                //                 tidyPlace = getSpokenLocation(lastRecoSpeech,locations);
                //                 if (tidyPlace.empty()) {
                //                         TakeshiHRI::say("Sorry i did not understand you");
                //                         nextState=SM_ASK_FOR_LOCATION;
                //                 }
                //                 else {
                //                         takeshi_say.str(std::string());
                //                         takeshi_say << "I'll go to the: "<<tidyPlace;
                //                         TakeshiHRI::say( takeshi_say.str());
                //                         nextState=SM_GOTO_SPOKEN_LOC;
                //                 }

                //         }
                //         TakeshiHRI::enableSpeechRecognized(false);

                //         break;
                // case SM_GOTO_SPOKEN_LOC:
                //         printState("Going to tidy up location as instructed");
                //         std::cout << "Going to:" << tidyPlace <<std::endl;
                //         if(TakeshiNavigation::getClose(tidyPlace,50000))
                //         {
                //                 nextState=SM_PLACE_OBJ;
                //         }
                //         break;

                case SM_PLACE_OBJ:
                        printState("Looking to place an object");
                        // if (tidyUpFloor) {

                        //         if(TakeshiTasks::placeObjectInFront(0.05))
                        //         {
                        //                 nextState = SM_GOTO_MESS;
                        //         }
                        // }
                        // else
                        // {
                        //         if (tidy_up_location.compare("rubbish_bin")==0)
                        //         {
                        //                 TakeshiNavigation::moveDistAngle(0, M_PI/2, 3000);
                        //                 TakeshiManip::waitForArmGoToTrashBin(4000);
                        //                 TakeshiManip::openGripper(1.0);
                        //                 ros::Duration(2.0).sleep();
                        //         }
                        //         else if(TakeshiTasks::placeObject(0.05))
                        //         {
                        //                 nextState = SM_GOTO_MESS;
                        //         }
                        // }
                            TakeshiNavigation::moveDistAngle(0, M_PI/2, 3000);
                            //TakeshiManip::waitForArmGoToTrashBin(4000);
                            TakeshiManip::armGoToDeliverObjectInFloor(4000);
                            TakeshiManip::openGripper(1.0);
                            ros::Duration(2.0).sleep();

                            nextState = SM_GOTO_MESS;

                        break;
                case SM_FINAL_STATE:
                        printState("Finishing going to human");
                        //TakeshiHRI::say("I finished the test reporting to human");
                        if(TakeshiNavigation::getClose(endLocation,35000))
                        {
                                TakeshiHRI::say("task Finished");
                                success=true;
                        }
                        break;
                }
                ros::spinOnce();
                loop.sleep();
        }
        return 0;
}

void printState(std::string st){
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        STATE MACHINE: "<< st << "\033[0m" << std::endl;
}

std::string getSpokenLocation(std::string recog, std::vector<std::string> locations)
{
        std::string tidy_up_location("");
        std::cout << recog << '\n';
        std::replace(recog.begin(),recog.end(),' ','_');
        for (size_t i = 0; i < locations.size(); i++) {
                tidy_up_location=locations[i];
                //std::replace(tidy_up_location.begin(),tidy_up_location.end(),' ','_');
                std::cout <<"\t<-->" <<tidy_up_location<< '\n';
                if(recog.find(tidy_up_location) != std::string::npos)
                {
                        break;
                }
                else
                {
                        tidy_up_location="";
                }
        }
        return tidy_up_location;
}
