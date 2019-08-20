#include <iostream>
#include <ros/ros.h>

#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiNavigation.h"

enum state {
        SM_INIT_STATE,
        SM_GET_KNOW_LOCATIONS,
        SM_GOTO_TRAIN_TABLE,
        SM_TRAIN_OBJECT_ONLINE,
        SM_GOTO_INITIAL_LOCATION,
        SM_DETECT_OBJECTS_IN_FRONT,
        SM_GOTO_NEXT_LOCATION,
        SM_WAIT_SEARCH_PHASE,
        SM_DETECT_OBJECTS,
        SM_COMMAND_TAKE_OBJECT,
        SM_GOTO_TAKE_OBJECT,
        SM_TAKE_OBJECT,
        SM_GOTO_RELEASE_OBJECT,
        SM_DETECT_OBJECTS_ON_FRIDGE,
        SM_DETECT_OBJECTS_ON_DININGTABLE,
        SM_DETECT_OBJECTS_ON_SHELF,
        SM_DETECT_OBJECTS_ON_DRAWER1,
        SM_DETECT_OBJECTS_ON_DRAWER2,
        SM_DETECT_OBJECTS_ON_DRAWER3,
        SM_DETECT_OBJECTS_ON_DRAWER4,
        SM_RELEASE_OBJECT,
        SM_RETURN_TO_INIT,
        SM_FINAL_STATE
};

void printState(std::string st);
bool saveDetectedObjects(std::vector<vision_msgs::VisionObject> detectedObjs, std::string pth );
std::string getClosestLocation(std::map<std::string, std::vector<float> > &locs);

int main(int argc, char *argv[]) {
        std::cout << "||------Searching for objects on all known locations------||" << '\n';
        ros::init(argc, argv,"search_train_node");
        ros::NodeHandle n;
        ros::NodeHandle nh_priv("~");
        ros::Rate loop(1);

        std::string knownObjLocFile;
        std::string objectToTake;
        string unknownObject1; //unknown object name
        std::vector<std::string> validCommands;
        validCommands.push_back("search phase");

        string lastRecoSpeech;
        string pathKnowLocationFile="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018.txt";
        string pathVisitLocations="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_visit_location.txt";
        string pathObjectLocations="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_object_location.txt";

        string pathObjectLocationsShelf="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_object_location_shelf.txt";
        string pathObjectLocationsDining="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_object_location_diningtable.txt";
        string pathObjectLocationsFridge="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_object_location_fridge.txt";
        string pathObjectLocationsDrawer1="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_object_location_drawer1.txt";
        string pathObjectLocationsDrawer2="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_object_location_drawer2.txt";
        string pathObjectLocationsDrawer3="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_object_location_drawer3.txt";
        string pathObjectLocationsDrawer4="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/WRS_2018_object_location_drawer4.txt";

        string pathObjectName="/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/unknown_object.txt";
        //addd param to filename
        // nh_priv.param<std::string>("known_objects_locations_file",knownObjLocFile,
        //                            "~/HSR_PUMAS/catkin_ws/src/planning/knowledge/known_object_locations.txt");
        //Bien hardcodeado, lo guarda en el mismo folder que known locations
        //Si le quieres cambiar la ruta:
        //rosrun act_pln search_online _known_objects_locations_file:="Ruta.txt"

        nh_priv.param<std::string>("known_objects_locations_file",knownObjLocFile,pathKnowLocationFile);
        TakeshiTasks::setNodeHandle(&n);
        TakeshiKnowledge::setNodeHandle(&n);
        TakeshiHRI::setNodeHandle(&n);
        TakeshiNavigation::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

        //Necessary objects:
        std::map<std::string, std::vector<float> > locations;
        std::map<std::string, std::vector<float> > objLocations;
        std::string nextLoc;
        int mapCounter=0, locSize;
        std::vector<vision_msgs::VisionObject> detectedObjects;
        float pose_x,pose_y,pose_th;
        std::stringstream takeshi_say;

        //Omit entrances and exits
        std::map<std::string, std::vector<float> >::iterator it;

        state nextState=SM_INIT_STATE;
        int attempts=0;
        //múltiples planos
        double planeFridge=0.25, searchInPlane=0.0, planeDrawer=0.09;

        bool success = false, onFridge=true;

        while (ros::ok() && !success)
        {
                switch (nextState)
                {

                case SM_INIT_STATE:
                        printState("Get Know locations");

                        while(!TakeshiManip::isTheHandPressed()){
                            cout << "I am waiting" << endl;
                            ros::spinOnce();
                          	loop.sleep();
                        }

                        TakeshiHRI::say("I am going to train table");
                        TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                        nextState= SM_GOTO_TRAIN_TABLE;
                        break;

                case SM_GOTO_TRAIN_TABLE:
                        printState("Go to train table");
                        //Train table location
                        TakeshiNavigation::getClose("kitchen_unit", 100000);
                        //TakeshiNavigation::getClose("coffee_table", 100000);
                        nextState= SM_TRAIN_OBJECT_ONLINE;
                        break;

                case SM_TRAIN_OBJECT_ONLINE:
                        printState("Train object online");
                        TakeshiHardware::initTimeMonitor(60000*5); //5 min
                        TakeshiTasks::trainObjectOnline("yourobject", unknownObject1);
                        cout << "Object trained: " << unknownObject1 << endl;
                        TakeshiKnowledge::saveNameUnknownObject(unknownObject1, pathObjectName);
                        TakeshiHRI::waitAfterSay("tell me the command, search phase, to start search objects", 4000);
                        TakeshiVision::startQRReader();
                        nextState = SM_WAIT_SEARCH_PHASE;
                        break;

                case SM_WAIT_SEARCH_PHASE:
                        TakeshiVision::startQRReader();
                        attempts++;
                        if(TakeshiHRI::waitForSpecificSentence(validCommands, lastRecoSpeech, 7000)){
                            if(lastRecoSpeech.find("search phase") != std::string::npos){
                                nextState=SM_GOTO_INITIAL_LOCATION;
                                attempts=0;
                            }
                        }
                        if(attempts > 5){
                            TakeshiHRI::waitAfterSay("tell me the command, search phase, to start search objects", 4000);
                            attempts=0;
                          }
                break;

                case SM_GOTO_INITIAL_LOCATION:
                        printState("Go to initial location");
                        TakeshiKnowledge::loadFromFile(pathVisitLocations);
                        TakeshiNavigation::moveLateral(-0.2, 4000);
                        nextState=SM_GET_KNOW_LOCATIONS;
                        break;

                case SM_GET_KNOW_LOCATIONS:
                        //Get locations and iterator
                        //Load visit locations
                        TakeshiKnowledge::getKnownLocations(locations);
                        it = locations.find("entrance");
                        if (it != locations.end())
                                locations.erase(it);

                        locSize=locations.size();
                        //TakeshiHardware::initTimeMonitor(60000*15); //15 min
                        printState("Get Know locations");

                        takeshi_say.str(std::string());
                        takeshi_say << "I will visit " << locations.size() << " locations";
                        TakeshiHRI::say( takeshi_say.str() );
                        nextLoc=getClosestLocation(locations);
                        nextState = SM_GOTO_NEXT_LOCATION;
                        break;

                case SM_GOTO_NEXT_LOCATION:
                        printState("Go next location");

                        if(TakeshiHardware::isTaskStop()){
                          takeshi_say.str(std::string());
                          takeshi_say << "My time is over, I finished searching for objects";
                          TakeshiHRI::say( takeshi_say.str() );
                          nextState=SM_FINAL_STATE;
                        }

                        takeshi_say.str(std::string());
                        takeshi_say << "I am now going to " << nextLoc;
                        TakeshiHRI::say( takeshi_say.str() );
                        if (mapCounter >= locSize)
                        {
                                nextState = SM_FINAL_STATE;
                        }
                        else if(TakeshiNavigation::getClose(nextLoc,100000))
                        {
                                mapCounter++;
                                if(nextLoc == "refrigerator"){
                                    TakeshiHRI::waitAfterSay("Human, can you open the fridge please?", 4000);
                                    TakeshiVision::loadSpecificTrainingDir("fridge");
                                    searchInPlane=planeFridge;
                                    onFridge=true;
                                    nextState=SM_DETECT_OBJECTS_ON_FRIDGE;
                                }
                                else if(nextLoc == "dining_table"){
                                    cout << "dining table" << endl;
                                    TakeshiVision::loadSpecificTrainingDir("dining");
                                    nextState=SM_DETECT_OBJECTS_ON_DININGTABLE;
                                }
                                else if (nextLoc =="wall_shelf"){
                                    TakeshiVision::loadSpecificTrainingDir("shelf");
                                    nextState=SM_DETECT_OBJECTS_ON_SHELF;
                                }
                                else if(nextLoc == "drawer_1"){
                                    TakeshiHRI::waitAfterSay("Human, can you open the drawer 1 please?", 4000);
                                    TakeshiVision::loadSpecificTrainingDir("drawer");
                                    searchInPlane=planeDrawer;
                                    onFridge=false;
                                    nextState=SM_DETECT_OBJECTS_ON_DRAWER1;
                                }
                                else if(nextLoc == "drawer_2"){
                                    TakeshiHRI::waitAfterSay("Human, can you open the drawer 2 please?", 4000);
                                    TakeshiVision::loadSpecificTrainingDir("drawer");
                                    searchInPlane=planeDrawer;
                                    onFridge=false;
                                    nextState=SM_DETECT_OBJECTS_ON_DRAWER2;
                                }
                                else if(nextLoc == "drawer_3"){
                                    TakeshiHRI::waitAfterSay("Human, can you open the drawer 3 please?", 4000);
                                    TakeshiVision::loadSpecificTrainingDir("drawer");
                                    searchInPlane=planeDrawer;
                                    onFridge=false;
                                    nextState=SM_DETECT_OBJECTS_ON_DRAWER3;
                                }
                                else if(nextLoc == "drawer_4"){
                                    TakeshiHRI::waitAfterSay("Human, can you open the drawer 4 please?", 4000);
                                    TakeshiVision::loadSpecificTrainingDir("drawer");
                                    searchInPlane=planeDrawer;
                                    onFridge=false;
                                    nextState=SM_DETECT_OBJECTS_ON_DRAWER4;
                                }
                                else
                                    nextState=SM_DETECT_OBJECTS_ON_DININGTABLE;

                                nextLoc=getClosestLocation(locations);
                        }
                        else
                        {
                                nextState = SM_GOTO_NEXT_LOCATION;
                        }
                        break;

                case SM_DETECT_OBJECTS_ON_FRIDGE:
                        printState("Detectic objects on fridge");
                        takeshi_say.str(std::string());
                        takeshi_say << "I am looking for objects";
                        TakeshiHRI::say( takeshi_say.str() );
                        TakeshiTasks::alignWithTable(0.4, false);
                        TakeshiManip::hdGoTo(1.5707,-0.3, 3000);

                        if(TakeshiTasks::detectObjectsNtimes(detectedObjects, 3))
                        {
                                //getlocation and save file
                                takeshi_say.str(std::string());
                                takeshi_say << "I found " << detectedObjects.size() << " objects.";
                                TakeshiHRI::say( takeshi_say.str() );
                                takeshi_say.str(std::string());
                                for(int i=0; i<detectedObjects.size();i++)
                                    takeshi_say << detectedObjects[i].id << ", ";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                saveDetectedObjects(detectedObjects,pathObjectLocationsFridge);
                        }
                        nextState = SM_GOTO_NEXT_LOCATION;

                break;

                case SM_DETECT_OBJECTS_ON_DRAWER1:
                        TakeshiManip::hdGoTo(0.0, -0.8, 4000);
                        searchInPlane=0.09;
                        TakeshiNavigation::moveDistAngle(0.0, -1.5707, 3000);
                        TakeshiTasks::alignWithTable(0.15, true);
                        if(TakeshiTasks::detectObjectsOnPlaneNtimes(detectedObjects, 3, searchInPlane))
                        {
                                //getlocation and save file
                                takeshi_say.str(std::string());
                                takeshi_say << "I found " << detectedObjects.size() << " objects.";
                                TakeshiHRI::say( takeshi_say.str() );
                                takeshi_say.str(std::string());
                                for(int i=0; i<detectedObjects.size();i++)
                                    takeshi_say << detectedObjects[i].id << ", ";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                saveDetectedObjects(detectedObjects,pathObjectLocationsDrawer1);
                        }

                        nextState = SM_GOTO_NEXT_LOCATION;
                break;

                case SM_DETECT_OBJECTS_ON_DRAWER2:
                        TakeshiManip::hdGoTo(0.0, -0.8, 4000);
                        searchInPlane=0.09;
                        TakeshiNavigation::moveDistAngle(0.0, -1.5707, 3000);
                        TakeshiTasks::alignWithTable(0.15, true);
                        if(TakeshiTasks::detectObjectsOnPlaneNtimes(detectedObjects, 3, searchInPlane))
                        {
                                //getlocation and save file
                                takeshi_say.str(std::string());
                                takeshi_say << "I found " << detectedObjects.size() << " objects.";
                                TakeshiHRI::say( takeshi_say.str() );
                                takeshi_say.str(std::string());
                                for(int i=0; i<detectedObjects.size();i++)
                                    takeshi_say << detectedObjects[i].id << ", ";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                saveDetectedObjects(detectedObjects,pathObjectLocationsDrawer2);
                        }

                        nextState = SM_GOTO_NEXT_LOCATION;
                break;

                case SM_DETECT_OBJECTS_ON_DRAWER3:
                        TakeshiManip::hdGoTo(0.0, -0.8, 4000);
                        searchInPlane=0.18;
                        TakeshiNavigation::moveDistAngle(0.0, -1.5707, 3000);
                        TakeshiTasks::alignWithTable(0.15, true);
                        if(TakeshiTasks::detectObjectsOnPlaneNtimes(detectedObjects, 3, searchInPlane))
                        {
                                //getlocation and save file
                                takeshi_say.str(std::string());
                                takeshi_say << "I found " << detectedObjects.size() << " objects.";
                                TakeshiHRI::say( takeshi_say.str() );
                                takeshi_say.str(std::string());
                                for(int i=0; i<detectedObjects.size();i++)
                                    takeshi_say << detectedObjects[i].id << ", ";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                saveDetectedObjects(detectedObjects,pathObjectLocationsDrawer3);
                        }

                        nextState = SM_GOTO_NEXT_LOCATION;
                break;

                case SM_DETECT_OBJECTS_ON_DRAWER4:
                        TakeshiManip::hdGoTo(0.0, -0.8, 4000);
                        searchInPlane=0.18;
                        TakeshiNavigation::moveDistAngle(0.0, -1.5707, 3000);
                        TakeshiTasks::alignWithTable(0.15, true);
                        if(TakeshiTasks::detectObjectsOnPlaneNtimes(detectedObjects, 3, searchInPlane))
                        {
                                //getlocation and save file
                                takeshi_say.str(std::string());
                                takeshi_say << "I found " << detectedObjects.size() << " objects.";
                                TakeshiHRI::say( takeshi_say.str() );
                                takeshi_say.str(std::string());
                                for(int i=0; i<detectedObjects.size();i++)
                                    takeshi_say << detectedObjects[i].id << ", ";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                saveDetectedObjects(detectedObjects,pathObjectLocationsDrawer4);
                        }

                        nextState = SM_GOTO_NEXT_LOCATION;
                break;

                case SM_DETECT_OBJECTS_ON_DININGTABLE:
                        printState("Detecting objects");
                        takeshi_say.str(std::string());
                        takeshi_say << "I am looking for objects";
                        TakeshiHRI::say( takeshi_say.str() );
                        TakeshiTasks::alignWithTable(0.4, false);
                        // Find objects
                        //ros::Duration(2.0).sleep(); //why?
                        if(TakeshiTasks::detectObjectsNtimes(detectedObjects, 3))
                        {
                                //getlocation and save file
                                takeshi_say.str(std::string());
                                takeshi_say << "I found " << detectedObjects.size() << " objects.";
                                TakeshiHRI::say( takeshi_say.str() );
                                takeshi_say.str(std::string());
                                for(int i=0; i<detectedObjects.size();i++)
                                    takeshi_say << detectedObjects[i].id << ", ";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                saveDetectedObjects(detectedObjects,pathObjectLocationsDining);
                        }
                        nextState = SM_GOTO_NEXT_LOCATION;

                        break;

                case SM_DETECT_OBJECTS_ON_SHELF:
                        printState("Detecting objects");
                        takeshi_say.str(std::string());
                        takeshi_say << "I am looking for objects";
                        TakeshiHRI::say( takeshi_say.str() );
                        TakeshiTasks::alignWithTable(0.4, false);
                        // Find objects
                        //ros::Duration(2.0).sleep(); //why?
                        if(TakeshiTasks::detectObjectsNtimes(detectedObjects, 3))
                        {
                                //getlocation and save file
                                takeshi_say.str(std::string());
                                takeshi_say << "I found " << detectedObjects.size() << " objects.";
                                TakeshiHRI::say( takeshi_say.str() );
                                takeshi_say.str(std::string());
                                for(int i=0; i<detectedObjects.size();i++)
                                    takeshi_say << detectedObjects[i].id << ", ";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                saveDetectedObjects(detectedObjects,pathObjectLocationsShelf);
                        }

                        TakeshiManip::torsoGoTo(0.0, 4000);

                        if(TakeshiTasks::detectObjectsNtimes(detectedObjects, 3))
                        {
                                //getlocation and save file
                                takeshi_say.str(std::string());
                                takeshi_say << "I found " << detectedObjects.size() << " objects.";
                                TakeshiHRI::say( takeshi_say.str() );
                                takeshi_say.str(std::string());
                                for(int i=0; i<detectedObjects.size();i++)
                                    takeshi_say << detectedObjects[i].id << ", ";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                saveDetectedObjects(detectedObjects,pathObjectLocationsShelf);
                        }

                        nextState = SM_GOTO_NEXT_LOCATION;

                        break;
                case SM_FINAL_STATE:
                        printState("Ending");
                        //all locations visited goto entrance and stop
                        takeshi_say.str(std::string());
                        takeshi_say << "I finished searching for objects";
                        TakeshiHRI::say( takeshi_say.str() );
                        TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                        TakeshiManip::navigationPose(4000);
                        success=true;
                        /*
                        //TakeshiKnowledge::getKnownObjectsLocationFromFile(knownObjLocFile,objLocations);
                        if(TakeshiNavigation::getClose("humanlocation1",100000))
                        {
                                nextState=SM_COMMAND_TAKE_OBJECT;
                                takeshi_say << "I am waiting for the next command";
                                TakeshiHRI::waitAfterSay( takeshi_say.str(), 5000 );
                                TakeshiKnowledge::loadFromFile(pathObjectLocations);
                                TakeshiHRI::enableSpeechRecognized(true);
                        } */
                        break;

                      }

                ros::spinOnce();
              	loop.sleep();

                }
        return 0;
}

bool saveDetectedObjects(std::vector<vision_msgs::VisionObject> detectedObjs, std::string pth )
{
        bool succes=true;
        float x,  y, th;

        std::cout << "Saving to: " << pth << '\n';
        TakeshiKnowledge::getRobotPose(x,y,th);
        for (size_t i = 0; i < detectedObjs.size(); i++) {
                if (detectedObjs[i].id.find("unknown") != std::string::npos) {
                        continue;
                        //unkonwn objects won't be sabed
                }
                //This saves to file
                succes = TakeshiKnowledge::saveObjToLTM(detectedObjs[i].id,pth,x,y,th);
                //This saves to known objects in LTM node
                TakeshiKnowledge::saveObjToLTM(detectedObjs[i].id,x,y,th);
                //This saves as known location on LTM node
                TakeshiKnowledge::addUpdateKnownLoc(detectedObjs[i].id,x,y,th);
        }
        return succes;
}

void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "        CASE: "<< st << std::endl << std::endl;
}

std::string getClosestLocation(std::map<std::string, std::vector<float> > &locs)
{
        nav_msgs::Path r;
        int minPthSize=10000;
        std::map<std::string, std::vector<float> >::iterator it;
        std::string closestLoc;
        if (locs.size()<1)
        {
                closestLoc = "";
                return closestLoc;
        }
        it = locs.begin();
        closestLoc = it->first;
        float currX,currY,currTh;
        TakeshiKnowledge::getRobotPose(currX,currY,currTh);
        for (; it != locs.end(); it++)
        {
                //gets the path to location it->first
                float x=it->second[0];
                float y=it->second[1];
                if(TakeshiNavigation::calcPathFromMapAStar(currX,currY,x,y,r))
                {
                        std::cout << "Path to " << it->first << " is "
                                  << r.poses.size() << "poses long" <<'\n';
                        //Find the smallest path to any node
                        if (r.poses.size()<minPthSize) {
                                minPthSize=r.poses.size();
                                closestLoc = it->first;
                        }
                }

        }
        locs.erase(closestLoc);
        return closestLoc;
}
