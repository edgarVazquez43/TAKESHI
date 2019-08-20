#include <iostream>
#include <vector>
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
        PRE_INIT
};

void printState(std::string st);

std::string getSpokenLocation(std::string recog, std::vector<std::string> locations);

int var_find=0;

int main(int argc, char *argv[]) 
{
        
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
        std::vector<std::vector<std::string> > messyPlaces;
        
        std::string tidyPlace;
               
        vision_msgs::VisionObject objToGrasp;
        geometry_msgs::Pose poseToGrasp;
        std::stringstream ss;

        std::string endLocation ="exit";
        
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

        validCommands.push_back("tidy up the office");
        validCommands.push_back("office");

        validCommands.push_back("tidy up the kitchen");
        validCommands.push_back("kitchen");

        std::string tidy_up_location, lastRecoSpeech;
        bool tidyUpFloor;

        /*In general the robot goes to messy location, look for objects and
           deposits them on tidyUpplace if no objects are found it turn a bit
           and looks again, if it turns more than 180 degrees it stops and finishes*/

        std::vector<std::string> all_Objects;
        
        all_Objects.push_back("biscuit");
        all_Objects.push_back("frosty_fruits");
        all_Objects.push_back("frosty_fruits_back");
        all_Objects.push_back("snakes");

        all_Objects.push_back("beer");
        all_Objects.push_back("chocolate_milk");
        all_Objects.push_back("coke");
        all_Objects.push_back("juice");
        all_Objects.push_back("lemonade");
        all_Objects.push_back("tea_bag");
        all_Objects.push_back("water");

        all_Objects.push_back("cheetos");
        all_Objects.push_back("cheetos_back");
        all_Objects.push_back("doritos");
        all_Objects.push_back("shapes_chicken");
        all_Objects.push_back("shapes_chicken_back");
        all_Objects.push_back("shapes_pizza");
        all_Objects.push_back("shapes_pizza_back");
        all_Objects.push_back("twisties");
        all_Objects.push_back("twisties_back");

        all_Objects.push_back("cloth");
        all_Objects.push_back("dishwasher_back");
        all_Objects.push_back("dishwasher_tab");
        all_Objects.push_back("sponge");
        all_Objects.push_back("sponge_back");
        all_Objects.push_back("trash_bag_white");
        all_Objects.push_back("purple_trashbag");
        all_Objects.push_back("yellow_trashbag");

        all_Objects.push_back("apple");
        all_Objects.push_back("kiwi");
        all_Objects.push_back("lemon");
        all_Objects.push_back("orange");
        all_Objects.push_back("pear");

        all_Objects.push_back("carrot");
        all_Objects.push_back("cereal");
        all_Objects.push_back("noodles");
        all_Objects.push_back("onion");
        all_Objects.push_back("vegemite");

        /*
        std::vector<std::string> office_Objects;

        office_Objects.push_back("biscuit");
        office_Objects.push_back("frosty_fruits");
        office_Objects.push_back("frosty_fruits_back");
        office_Objects.push_back("snakes");

        std::vector<std::string> living_Objects;        

        living_Objects.push_back("beer");
        living_Objects.push_back("chocolate_milk");
        living_Objects.push_back("coke");
        living_Objects.push_back("juice");
        living_Objects.push_back("lemonade");
        living_Objects.push_back("soap");
        living_Objects.push_back("tea_bag");
        living_Objects.push_back("water");

        living_Objects.push_back("cheetos");
        living_Objects.push_back("cheetos_back");
        living_Objects.push_back("doritos");
        living_Objects.push_back("shapes_chicken");
        living_Objects.push_back("shapes_chicken_back");
        living_Objects.push_back("shapes_pizza");
        living_Objects.push_back("shapes_pizza_back");
        living_Objects.push_back("twisties");
        living_Objects.push_back("twisties_back");
        
        
        std::vector<std::string> kitchen_Objects;

        kitchen_Objects.push_back("cloth");
        kitchen_Objects.push_back("dishwasher_back");
        kitchen_Objects.push_back("dishwasher_tab");
        kitchen_Objects.push_back("sponge");
        kitchen_Objects.push_back("sponge_back");
        kitchen_Objects.push_back("trash_bag_white");
        kitchen_Objects.push_back("purple_trashbag");
        kitchen_Objects.push_back("yellow_trashbag");

        kitchen_Objects.push_back("apple");
        kitchen_Objects.push_back("kiwi");
        kitchen_Objects.push_back("lemon");
        kitchen_Objects.push_back("orange");
        kitchen_Objects.push_back("pear");

        std::vector<std::string> bedroom_Objects;        

        bedroom_Objects.push_back("carrot");
        bedroom_Objects.push_back("cereal");
        bedroom_Objects.push_back("noodles");
        bedroom_Objects.push_back("onion");
        bedroom_Objects.push_back("vegemite");
        */

        std:string location_name;
        std::vector<std::string> objects_names;

        std::vector<vision_msgs::VisionObject> detectedObjs;
        vision_msgs::ObjectCoordinatesForDetection objectsCoordinates=TakeshiVision::objectCoordinates;

        //#######################################################################

        state nextState=PRE_INIT;

        //double angle=0.0;
        //double step = 33*M_PI/180;

        //double advance=0.00;
        //double adv_step=0.2;

        bool success = false;
        
        int attempts=4;

        const int max_grasp_tries = 1;

        int grasp_attempts = max_grasp_tries;

        std::size_t found;

        std::cout << "Starting state machine" << '\n';

        std::vector<std::string> tmp;

        while (ros::ok() && !success)
        {
                switch (nextState)
                {

                case PRE_INIT:

                    TakeshiHRI::waitAfterSay("Tell me tidy up the ... and say a room...",1500);
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
                                TakeshiHRI::waitAfterSay("Tell me tidy up the ... and say a room...",1500);
                                TakeshiHRI::waitAfterSay("For example... tidy up the living room... ",1500);
                                TakeshiHRI::waitAfterSay("When confirmation is needed say... Takeshi yes, or Takeshi no ",1500);
                                TakeshiHRI::enableSphinxMic(true);
                                attempts=0;
                                
                        }

                        //locations OK!!!!
                        
                        if(TakeshiHRI::waitForSpecificSentence(validCommands, lastRecoSpeech, 7000)) 
                        {
                                if(lastRecoSpeech.find("office") != std::string::npos) {
                                        tidy_up_location="office";
                                        //tidyUpFloor=true;
                                        TakeshiHRI::say( takeshi_say.str());  //esta linea va aquí?

                                        //...One for each possible tidy up. Poner sub locations en cada habitacion

                                        std::vector<std::string> tmpVec;
                                        
                                        tmpVec.push_back("table");
                                        tmpVec.push_back("desk1");
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("office3");                                        
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("office2");
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("office");
                                        messyPlaces.push_back(tmpVec);

                                        

                                        //TakeshiVision::loadSpecificTrainingDir("bedroom"); //jebus detector


                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("living_room") != std::string::npos) {
                                        tidy_up_location="living_room";
                                        //tidyUpFloor=true;

                                        //...One for each possible tidy up. Poner sub locations en cada habitacion

                                        std::vector<std::string> tmpVec;
                                        
                                        tmpVec.push_back("sofa");
                                        tmpVec.push_back("chair_1");
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("sofa");
                                        tmpVec.push_back("couch");
                                        messyPlaces.push_back(tmpVec);
                                                        
                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("living_room3");                                        
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("living_room2");
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("living_room");
                                        messyPlaces.push_back(tmpVec);
                                                                                
                                        
                                        //TakeshiVision::loadSpecificTrainingDir("dining_room");
                                        
                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("kitchen") != std::string::npos) {
                                        tidy_up_location="kitchen";

                                        //tidyUpFloor=true;

                                        //...One for each possible tidy up. Poner sub locations en cada habitacion
                                        std::vector<std::string> tmpVec;
                                        
                                        tmpVec.push_back("table");
                                        tmpVec.push_back("kitchen_table");
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("kitchen2");
                                        messyPlaces.push_back(tmpVec);
                                        

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("kitchen1");
                                        messyPlaces.push_back(tmpVec);                                       
                                        
                                       
                                        //TakeshiVision::loadSpecificTrainingDir("living_room");

                                        nextState=SM_GOTO_MESS_CONF;
                                }
                                else if(lastRecoSpeech.find("bedroom") != std::string::npos) {
                                        tidy_up_location="bedroom";
                                        //tidyUpFloor=false;

                                        //...One for each possible tidy up. Poner sub locations en cada habitacion
                                        
                                        std::vector<std::string> tmpVec;
                                        tmpVec.push_back("sofa");
                                        tmpVec.push_back("bed");
                                        
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("bedroom2");
                                        messyPlaces.push_back(tmpVec);

                                        tmpVec.clear();
                                        tmpVec.push_back("floor");
                                        tmpVec.push_back("bedroom1");
                                        messyPlaces.push_back(tmpVec);
                                        
                                        
                                        
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
                                
                                takeshi_say << "I am going to clean the " << tidy_up_location;
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 3000);
                        }

                        if (messyPlaces.empty()) {
                                nextState=SM_FINAL_STATE;
                                takeshi_say.str(std::string());
                                //takeshi_say << "Location not detected!";
                                takeshi_say << "Test finished!";
                        }

                        else if(TakeshiNavigation::getClose(messyPlaces.back(),100000)) //get close
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

                                std::vector<std::string> tmp_var;

                                tmp_var=messyPlaces.back();

                                if (tmp_var[0].compare("floor")==0)
                                {
                                        nextState=SM_FIND_OBJ_FLOOR;
                                }
                                else if(tmp_var[0].compare("table")==0)
                                {
                                        nextState=SM_FIND_OBJ_TABLE;
                                }
                                else if(tmp_var[0].compare("sofa")==0)
                                {
                                        nextState=SM_FIND_OBJ_SOFA;

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

                        //location_name=messyPlaces.top();
                        
                        //revisar si accede a location
                        tmp=messyPlaces.back();
                        location_name=tmp[1];

                        
                        objects_names=all_Objects;
                        objectsCoordinates.z_max=0.3; //h_max para el piso

                       
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

                                    
                                    nextState=SM_NEXT_LOC1;
                                    }
                        }
                        break;



                case SM_FIND_OBJ_TABLE:

                        printState("Finding objects on location");
                        takeshi_say.str(std::string());
                        tmp=messyPlaces.back();
                        location_name=tmp[1];

                        takeshi_say << "I am finding objects on location: " << location_name;
                        TakeshiHRI::say(takeshi_say.str() );
                        
                        //cargar objetos per location
                        
                        tmp=messyPlaces.back();
                        location_name=tmp[1];                       
                        
                        
                        //###################
                        //TakeshiTasks::alignWithFrontTable();
                        //string objects_names,vision_msgs recoObjects, max height,timeout_ms
                        objectsCoordinates.z_max=1.0;
                        if(TakeshiVision::detectObjectsFloor(recognizedObjects, false))
                        {
                        //if (TakeshiTasks::graspYoloObject(objects_names,recognizedObjects,3,2000,true,objectsCoordinates))
                        //{
                                TakeshiTasks::graspObjectOnFloor(recognizedObjects[0].pose.position.x, recognizedObjects[0].pose.position.y, recognizedObjects[0].pose.position.z, false);
                                nextState = SM_GOTO_TIDY;
                        }
                        else
                        {   
                                //CAMBIAR LOCATTION
                                messyPlaces.pop_back();
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

                    messyPlaces.pop_back();
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
                            std::string var;

                                //messyPlaces.pop();
                                grasp_attempts--;
                                //advance+=adv_step;
                                //TakeshiNavigation::moveDist(advance,3000);
                                std::cout<< "grasp else STATE"<<std::endl;
                                nextState = SM_FIND_OBJ_FLOOR;

                        }
                        break;

                //Integrado en grasp yolo
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
                            
                            
                            if(TakeshiTasks::placeObject(0.05))
                              {
                                   nextState = SM_GOTO_MESS;
                              }


                            TakeshiManip::openGripper(1.0);
                            ros::Duration(2.0).sleep();

                            

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
