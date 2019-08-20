#include <iostream>
#include <algorithm>
#include <ros/package.h>
#include <stack>
#include <ros/ros.h>

//#include "hri_msgs/RecognitionResult.h"

#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiKnowledge.h"
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
        SM_FINAL_STATE, //goto human
        SM_NEXT_LOC1,
        SM_NEXT_LOC2,
        PRE_INIT,
        SM_TEST_CONFIG
};

void printState(std::string st);

std::string getSpokenLocation(std::string recog, std::vector<std::string> locations);

int var_find=0;

int main(int argc, char *argv[]) {
        std::cout << "||------Clean Up test------||" << '\n';
        ros::init(argc, argv,"clean_up_test");
        ros::NodeHandle n;
        ros::Rate loop(0.5);

        //nodehandleando

        TakeshiHRI::setNodeHandle(&n);
        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

         std::string pathToKnowledge = ros::package::getPath("knowledge");

        //List of objects
        string pathObjects=pathToKnowledge+"/navigation/clean_up_2019.txt";
        
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

        std::string endLocation ="door_1";
        
        bool userConfirmation = false;

        int tryCounter=0;

        //Read file in pairs {object:location}
        TakeshiKnowledge::getKnownObjectsLocationFromFile(pathObjects,tidyUpPlaces);

        std::cout << "Object Locations:" <<  tidyUpPlaces.size()<<'\n';

        for(std::map<std::string,std::string>::const_iterator it = tidyUpPlaces.begin(); it != tidyUpPlaces.end(); ++it)
        {
            std::cout << it->first << ": " << it->second << "\n";
        }

        std::map<std::string, std::vector<float> > knownLocations;
        std::map<std::string, std::vector<float> >::iterator it_loc;
        std::vector<string> locations;

        //Get list of known locations
        TakeshiKnowledge::getKnownLocations(knownLocations);

        std::cout << "Known Locations:" <<  knownLocations.size()<<'\n';
        for(std::map<std::string,std::vector<float> >::const_iterator it = knownLocations.begin(); it != knownLocations.end(); ++it)
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

        std::string tidy_up_location, lastRecoSpeech;
        bool tidyUpFloor;

        /*In general the robot goes to messy location, look for objects and
           deposits them on tidyUpplace if no objects are found it turn a bit
           and looks again, if it turns more than 180 degrees it stops and finishes*/

        std::vector<std::string> dining_Objects;

        dining_Objects.push_back("blue_mug");
        dining_Objects.push_back("green_mug");
        dining_Objects.push_back("purple_mug");
        dining_Objects.push_back("red_mug");
        dining_Objects.push_back("bill");
        dining_Objects.push_back("soap");
        dining_Objects.push_back("blue_lego");
        dining_Objects.push_back("red_lego");
        dining_Objects.push_back("yellow_lego");
        dining_Objects.push_back("apple_juice ");
        dining_Objects.push_back("cajeta_cokkies ");
        dining_Objects.push_back("pineapple_cookies");
        dining_Objects.push_back("strawberry_cookies"); 

        std::vector<std::string> living_Objects;

        living_Objects.push_back("blue_mug");
        living_Objects.push_back("green_mug");
        living_Objects.push_back("purple_mug");
        living_Objects.push_back("red_mug");
        living_Objects.push_back("bill");
        living_Objects.push_back("soap");
        living_Objects.push_back("blue_lego");
        living_Objects.push_back("red_lego");
        living_Objects.push_back("yellow_lego");
        living_Objects.push_back("apple_juice ");
        living_Objects.push_back("cajeta_cokkies ");
        living_Objects.push_back("pineapple_cookies");
        living_Objects.push_back("strawberry_cookies");
        
        std::vector<std::string> kitchen_Objects;

        kitchen_Objects.push_back("blue_mug");
        kitchen_Objects.push_back("green_mug");
        kitchen_Objects.push_back("purple_mug");
        kitchen_Objects.push_back("red_mug");
        kitchen_Objects.push_back("bill");
        kitchen_Objects.push_back("soap");
        kitchen_Objects.push_back("blue_lego");
        kitchen_Objects.push_back("red_lego");
        kitchen_Objects.push_back("yellow_lego");
        kitchen_Objects.push_back("apple_juice ");
        kitchen_Objects.push_back("cajeta_cokkies ");
        kitchen_Objects.push_back("pineapple_cookies");
        kitchen_Objects.push_back("strawberry_cookies");

        std::vector<std::string> bedroom_Objects;

        bedroom_Objects.push_back("blue_mug");
        bedroom_Objects.push_back("green_mug");
        bedroom_Objects.push_back("purple_mug");
        bedroom_Objects.push_back("red_mug");
        bedroom_Objects.push_back("bill");
        bedroom_Objects.push_back("soap");
        bedroom_Objects.push_back("blue_lego");
        bedroom_Objects.push_back("red_lego");
        bedroom_Objects.push_back("yellow_lego");
        bedroom_Objects.push_back("apple_juice ");
        bedroom_Objects.push_back("cajeta_cokkies ");
        bedroom_Objects.push_back("pineapple_cookies");
        bedroom_Objects.push_back("strawberry_cookies");

        std:string location_name;
        std::vector<std::string> objects_names;

        std::vector<vision_msgs::VisionObject> detectedObjs;
        vision_msgs::ObjectCoordinatesForDetection objectsCoordinates=TakeshiVision::objectCoordinates;

        //#######################################################################

        //state nextState=PRE_INIT;
        state nextState=SM_TEST_CONFIG;
        //state nextState=SM_FIND_OBJ_TABLE;

        //double angle=0.0;
        //double step = 33*M_PI/180;

        //double advance=0.00;
        //double adv_step=0.2;

        bool success = false;

        bool DEBUG_MODE=true;
        
        int attempts=4;

        const int max_grasp_tries = 1;

        int grasp_attempts = max_grasp_tries;

        std::size_t found;

        std::cout << "Starting state machine" << '\n';

        while (ros::ok() && !success)
        {
                switch (nextState)
                {

                case SM_TEST_CONFIG:

                    lastRecoSpeech="kitchen";

                    tidy_up_location="kitchen";

                    tidyUpFloor=false;
     
                    //...One for each possible tidy up. Poner sub locations en cada habitacion
                      
                    messyPlaces.push("kitchen3");
                    messyPlaces.push("kitchen2");
                    messyPlaces.push("kitchen");
                      
                    //TakeshiVision::loadSpecificTrainingDir("kitchen");
     
                    //nextState=SM_GOTO_MESS_CONF;

                    nextState=SM_FIND_OBJ_TABLE;

                    break;

                case PRE_INIT:

                    TakeshiHRI::waitAfterSay("Tell me tidy up and say a room...",1200);
                    TakeshiHRI::waitAfterSay("For example... tidy up the living room... ",1500);
                    TakeshiHRI::waitAfterSay("When confirmation is needed say... Takeshi yes, or Takeshi no ",1500);
                    
                    //TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/clean_up.jsfg", "clean_up");                    

                    nextState=SM_INIT_STATE;
                    break;

                case SM_INIT_STATE:

                        TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/clean_up.jsfg", "clean_up");

                        TakeshiHRI::enableSphinxMic(false);

                        TakeshiVision::startQRReader();
                    
                        if (attempts > 3) {
                                
                                TakeshiHRI::waitAfterSay("Tell me what to do!", 3000);
                                TakeshiHRI::enableSphinxMic(true);
                                attempts=0;
                                
                        }

                        
                        
                        if(TakeshiHRI::waitForSpecificSentence(validCommands, lastRecoSpeech, 7000)) 
                        {
                                if(lastRecoSpeech.find("bedroom") != std::string::npos) {
                                        tidy_up_location="bedroom";
                                        tidyUpFloor=true;
                                        TakeshiHRI::say( takeshi_say.str());  //esta linea va aquí?

                                        //...One for each possible tidy up. Poner sub locations en cada habitacion
                                        
                                        messyPlaces.push("bedroom3");
                                        messyPlaces.push("bedroom2");
                                        messyPlaces.push("bedroom");

                                        //TakeshiVision::loadSpecificTrainingDir("bedroom"); //jebus detector


                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("dining room") != std::string::npos) {
                                        tidy_up_location="dining_room";
                                        tidyUpFloor=false;

                                        //...One for each possible tidy up. Poner sub locations en cada habitacion
                                          
                                        messyPlaces.push("dining_room3"); 
                                        messyPlaces.push("dining_room2");       
                                        messyPlaces.push("dining_room");
                                        
                                        
                                        //TakeshiVision::loadSpecificTrainingDir("dining_room");
                                        
                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("living room") != std::string::npos) {
                                        tidy_up_location="living_room";

                                        tidyUpFloor=true;

                                        //...One for each possible tidy up. Poner sub locations en cada habitacion
                                                                                
                                        messyPlaces.push("living_room3");
                                        messyPlaces.push("living_room2");
                                        messyPlaces.push("living_room");
                                        
                                       
                                        //TakeshiVision::loadSpecificTrainingDir("living_room");

                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("kitchen") != std::string::npos) {
                                        tidy_up_location="kitchen";
                                        tidyUpFloor=false;

                                        //...One for each possible tidy up. Poner sub locations en cada habitacion
                                        
                                        messyPlaces.push("kitchen3");
                                        messyPlaces.push("kitchen2");
                                        messyPlaces.push("kitchen");
                                        
                                        //TakeshiVision::loadSpecificTrainingDir("kitchen");

                                        nextState=SM_GOTO_MESS_CONF;
                                }

                                if(tidy_up_location.compare("") != 0 && nextState == SM_GOTO_MESS_CONF) {
                                        
                                        TakeshiHRI::enableSphinxMic(false);
                                        ss.str("");
                                        ss << "Do you want me tidy up the "<<
                                        tidy_up_location << "?";
                                        
                                        TakeshiHRI::waitAfterSay(ss.str(), 3000);
                                        
                                        
                                }
                        }

                        attempts++;
                        break;

                case SM_GOTO_MESS_CONF:
                        cout << "State machine: SM_GOTO_MESS_CONF" << endl;

                        if(DEBUG_MODE){

                            nextState = SM_GOTO_MESS;
                            break;
                        }

                        TakeshiHRI::enableSphinxMic(true);
                        TakeshiHRI::waitForUserConfirmation(userConfirmation, 8000);
                        

                        if(userConfirmation) {
                                TakeshiHRI::waitAfterSay("Ok", 4000);
                                TakeshiVision::stopQRReader();
                                TakeshiHRI::enableSphinxMic(false);
                                //TakeshiVision::loadObjectTrainDir();
                                
                                nextState = SM_GOTO_MESS;
                        }
                        else{
                                nextState = SM_INIT_STATE;
                                TakeshiHRI::waitAfterSay("Sorry, please repeat the command", 4000);
                                
                        }

                        break;

                                
                case SM_GOTO_MESS:

                        printState("Going to mess");
                        
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

                        else if(TakeshiNavigation::getClose(messyPlaces.top(),100000)) //get close
                        {
                                //TakeshiNavigation::moveDist(advance,3000);
                                /*Rutina para detectar en superficies comming soon

                                tidyPlace = messyPlaces.top();
                                if(tidyPlace.compare("sofa")==0)
                                {
                                        nextState = SM_FIND_OBJ_SOFA;
                                        //SOFA esta hardcodeado, el plano no lo encuentra chidoris...
                                        //Vaaaa
                                }
                                */
                                TakeshiManip::openGripper(0.3);

                                if (tidyUpFloor)
                                {
                                        nextState=SM_FIND_OBJ_FLOOR;
                                }
                                else
                                {
                                        nextState=SM_FIND_OBJ_TABLE;
                                }
                        }

                        //if (grasp_attempts<=0)
                        //{
                                //validar agarre

                        //        nextState=SM_FINAL_STATE;
                        //        std::cout<<"Estado FINAL SM_GOTO_MESS"<<std::endl;
                        //}

                        /*
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
                        */

                        break;

                case SM_FIND_OBJ_FLOOR:

                        printState("Finding objects on location");
                        //TakeshiNavigation::moveDistAngle(0,angle,5000);
                        TakeshiHRI::say("I am finding objects on location" );
                        
                        //##############################
                        TakeshiManip::hdGoTo(0,-1.0,5000);

                        location_name=messyPlaces.top();

                        
                        objects_names=bedroom_Objects;
                        objectsCoordinates.z_max=0.3;
                        
                        if (location_name=="bedroom")
                        {                       
                           
                           objects_names=bedroom_Objects;

                        }else if (location_name=="living_room")
                        {
                            objects_names=living_Objects;

                        }else if (location_name=="kitchen")
                        {

                            objects_names=kitchen_Objects;

                        }else if (location_name=="dining_room")
                        {
                            objects_names=dining_Objects;
                        }

                        if (TakeshiVision::detectSpecificYoloObject(objects_names,recognizedObjects,2000,objectsCoordinates))
                        {
                                nextState = SM_GRASP_OBJ_FLOOR;
                                //Are all messy objects on the floor?
                                //No some are in table or sofa
                        }else {
                                if(tryCounter<2){

                                nextState = SM_FIND_OBJ_FLOOR;

                                tryCounter++;

                                }
                                else {

                                    if(var_find==0){
                                    
                                    var_find=1;
                                    nextState=SM_NEXT_LOC1;
                                    }
                                    else if (var_find==1)
                                    {
                                        
                                        var_find=2;
                                        nextState=SM_NEXT_LOC2;

                                    }
                                    else if (var_find==2)
                                    {
                                        nextState = SM_FINAL_STATE;
                                        std::cout<<"Estado FINAL SM_FIND_OBJ_TABLE"<<std::endl;
                                    }


                                }
                        }
                        break;



                case SM_FIND_OBJ_TABLE:

                        printState("Finding objects on location");
                        takeshi_say.str(std::string());
                        takeshi_say << "I am finding objects on location: " << messyPlaces.top();
                        TakeshiHRI::say(takeshi_say.str() );

                        

                        //cargar objetos per location
                        location_name=messyPlaces.top();
                        
                        if (location_name=="bedroom")
                        {                       
                           
                           objects_names=bedroom_Objects;

                        }else if (location_name=="living_room")
                        {
                            objects_names=living_Objects;

                        }else if (location_name=="kitchen")
                        {

                            objects_names=kitchen_Objects;

                        }else if (location_name=="dining_room")
                        {
                            objects_names=dining_Objects;
                        }else
                        {
                            objects_names=bedroom_Objects;
                        }

                        
                        //###################
                        //TakeshiTasks::alignWithFrontTable();
                        //string objects_names,vision_msgs recoObjects, max height,timeout_ms
                        objectsCoordinates.z_max=1.0;

                        if (TakeshiTasks::graspYoloObject(objects_names,recognizedObjects,3,2000,true,objectsCoordinates))
                        {
                                nextState = SM_GOTO_TIDY;
                        }
                        else
                        {   
                                //CAMBIAR LOCATION
                                messyPlaces.pop();
                                nextState=SM_GOTO_MESS;

                                // //detect 2 veces nomas
                                // //messyPlaces.pop();
                                // if(tryCounter<2){

                                // nextState = SM_FIND_OBJ_TABLE;
                                // tryCounter++;

                                // }
                                // else {

                                //     if(var_find==0){
                                    
                                //     var_find=1;
                                //     nextState=SM_NEXT_LOC1;
                                //     }
                                //     else if (var_find==1)
                                //     {
                                        
                                //         var_find=2;
                                //         nextState=SM_NEXT_LOC2;

                                //     }
                                //     else if (var_find==2)
                                //     {
                                //         nextState = SM_FINAL_STATE;
                                //     }


                                // }
                        }

                        break;

                case SM_NEXT_LOC1:

                std::cout<<"aqui SM_NEXT_LOC1 SM_NEXT_LOC1"<<std::endl;

                    messyPlaces.pop();
                    tryCounter=0;
                    grasp_attempts = max_grasp_tries;
                    nextState=SM_GOTO_MESS;

                    break;

                case SM_NEXT_LOC2:

                    std::cout<<"aqui SM_NEXT_LOC2 SM_NEXT_LOC2"<<std::endl;
                    messyPlaces.pop();
                    tryCounter=0;
                    grasp_attempts = max_grasp_tries;
                    nextState=SM_GOTO_MESS;

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
                                std::cout<< "grasp STATE"<<std::endl;
                                nextState = SM_GOTO_TIDY;
                        }

                        else
                        {
                                //messyPlaces.pop();
                                grasp_attempts--;
                                //advance+=adv_step;
                                //TakeshiNavigation::moveDist(advance,3000);
                                std::cout<< "grasp else STATE"<<std::endl;
                                nextState = SM_FIND_OBJ_FLOOR;

                        }
                        break;

                // case SM_GRASP_OBJ_TABLE:

                //         printState("Grasping objects table");
                //         objToGrasp = recognizedObjects[0];
                //         takeshi_say.str(std::string());
                //         takeshi_say << "I am grasping the "<< objToGrasp.id;
                //         poseToGrasp = objToGrasp.pose;
                //         TakeshiHRI::say( takeshi_say.str());
                        
                //         //TakeshiManip::hdGoTo(0,0.0,5000);
                        

                //         if(TakeshiTasks::graspObjectLateral(
                //                    poseToGrasp.position.x,
                //                    poseToGrasp.position.y,
                //                    poseToGrasp.position.z,
                //                    false))

                //         objectsCoordinates.x_max=1.5;
                //         if(TakeshiTasks::graspYoloObject(objects_names, 2, 4000, true,objectsCoordinates))

                //         {
                //                 nextState = SM_GOTO_TIDY;
                //         }
                //         else
                //         {
                //                 //grasp_attempts--;
                //                 nextState = SM_GOTO_MESS;
                //         }

                //         break;



                case SM_GOTO_TIDY:

                        printState("Going to tidy up location");
                        objToGrasp = recognizedObjects[0];
                        it = tidyUpPlaces.find(objToGrasp.id);
                        std::cout<< "IT STATE"<<std::endl;

                        //no entra a placear y regresa a mess
                        std::cout<<"ITERATOR   "<<it->first<<std::endl;
                        std::cout<<"ITERATOR   "<<it->second<<std::endl;
                        if (it != tidyUpPlaces.end())
                        {

                                std::cout<< "IF in STATE"<<std::endl;
                                std::cout << "Going to:" << it->second <<std::endl;
                                if(TakeshiNavigation::getClose(it->second,200000))
                                {
                                        std::cout<< "get close STATE"<<std::endl;
                                        nextState=SM_PLACE_OBJ;
                                }
                        }
                        else
                        {
                            //caso de contingencia
                            std::cout<<"MESSS EMERG   "<<std::endl;
                            nextState=SM_GOTO_MESS;

                        }

                        break;

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
                            //TakeshiNavigation::moveDistAngle(0, M_PI/2, 3000);
                            //TakeshiManip::waitForArmGoToTrashBin(4000);
                            TakeshiTasks::placeObjectInColorBin("red");
                            //TakeshiManip::armGoToDeliverObjectInFloor(4000);
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
