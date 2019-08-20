////////////////////////////////////////////////////////
// Note: this code was commented into CMake file,
// If you are brave enough to edit this code please
// make sure to uncomment this code into CMakeList.txt
///////////////////        EDD-II    ////////////////////

#include <iostream>
#include <ros/ros.h>
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiHardware.h"

#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiVision.h"

using namespace std;

enum state {
        SM_INIT_STATE,
        SM_CHECK_QR,
        SM_LISTEN_CMDS,
        SM_GET_TABLE_LOCATIONS,
        SM_GET_SHELF_LOCATIONS,
        SM_GET_FRIDGE_LOCATIONS,
        SM_GET_DRAWER1_LOCATIONS,
        SM_GET_DRAWER2_LOCATIONS,
        SM_GET_DRAWER3_LOCATIONS,
        SM_GET_DRAWER4_LOCATIONS,
        SM_COMMAND_TAKE_OBJECT,
        SM_GOTO_TAKE_OBJECT,
        SM_GOTO_TAKE_OBJECT_CONF,
        SM_GET_KNOW_LOCATIONS,
        SM_FIND_OBJECT,
        SM_VERIFY_LOCATION,
        SM_TAKE_OBJECT,
        SM_FIND_PERSON,
        SM_OPEN_FRIDGE,
        SM_OPEN_DRAWER,
        SM_GRASP_FRIDGE,
        SM_GRASP_DRAWER,
        SM_GRASP_SHELF,
        SM_GRASP_OBJECT,
        SM_GOTO_RELEASE_OBJECT,
        SM_RELEASE_OBJECT,
        SM_RETURN_TO_INIT,
        SM_FINAL_STATE
};

void printState(std::string st);
std::string getClosestLocation(std::map<std::string, std::vector<float> > &locs);
bool writeQRObjects(std::string pth,std::vector<std::string> &objs);
bool readQRObjects(std::string pth,std::vector<std::string> &objs);

int main(int argc, char** argv){
        cout << "--------------Bring Me up test------------" << endl;

        ros::init(argc, argv,"bring_me_up_test");
        ros::NodeHandle n;
        ros::Rate loop(30);
        string unknownObject1;
        std::vector<std::string> validCommands;
        string lastRecoSpeech;
        std::string objectToTake,objectToTake_one, objectToTake_two, objectLocation, humanlocation;

        std::stringstream ss;
        std::vector<std::string> tokens;
        bool userConfirmation = false;
        std::map<std::string, std::vector<float> > locations;
        std::map<std::string, std::vector<float> >::iterator it;
        int mapCounter=0, locSize;
        bool verify = false;

        TakeshiTasks::setNodeHandle(&n);
        TakeshiHardware::setNodeHandle(&n);
        TakeshiVision::setNodeHandle(&n);

        bool success = false, isTaken=false, isFinded=false, findObject=false;
        bool command_two_objects=false, first_object=false, second_object=false;
        int nextState;
        std::stringstream takeshi_say;
        double planeFridge=0.25, searchInPlane=0.0, planeDrawer=0.09;

        validCommands.push_back("bring me wooden bowl");
        validCommands.push_back("bring me brown pail"); //////////
        validCommands.push_back("bring me mixed nuts");
        validCommands.push_back("bring me blue cup");
        validCommands.push_back("bring me pink cup");
        validCommands.push_back("bring me orange biscuits");
        validCommands.push_back("bring me yellow biscuits");
        validCommands.push_back("bring me watering can"); /////////////////
        validCommands.push_back("bring me flashlight");
        validCommands.push_back("bring me blue fork"); //////////////
        validCommands.push_back("bring me green fork"); ////////////////
        validCommands.push_back("bring me gray knife"); /////////////////
        validCommands.push_back("bring me pink biscuits");
        validCommands.push_back("bring me yellow clock");
        validCommands.push_back("bring me aluminum foil");
        validCommands.push_back("bring me green dish"); ///////////////
        validCommands.push_back("bring me yellow dish"); //////////////
        validCommands.push_back("bring me pink bowl");
        validCommands.push_back("bring me blue bowl");
        validCommands.push_back("bring me mineral water");
        validCommands.push_back("bring me oolong tea");
        validCommands.push_back("bring me ketchup");
        validCommands.push_back("bring me canned mustard");
        validCommands.push_back("bring me orange drink");
        validCommands.push_back("bring me green drink");
        validCommands.push_back("bring me tomato");
        validCommands.push_back("bring me potato");
        validCommands.push_back("bring me plant");
        validCommands.push_back("bring me spray");
        validCommands.push_back("bring me water bottle");
        validCommands.push_back("bring me blueberry drink");
        validCommands.push_back("bring me eggplant");

        validCommands.push_back("wooden bowl");
        validCommands.push_back("brown pail");
        validCommands.push_back("mixed nuts");
        validCommands.push_back("blue cup");
        validCommands.push_back("pink cup");
        validCommands.push_back("orange biscuits");
        validCommands.push_back("yellow biscuits");
        validCommands.push_back("watering can");
        validCommands.push_back("flashlight");
        validCommands.push_back("blue fork");
        validCommands.push_back("green fork");
        validCommands.push_back("gray knife");
        validCommands.push_back("pink biscuits");
        validCommands.push_back("yellow clock");
        validCommands.push_back("aluminum foil");
        validCommands.push_back("green dish");
        validCommands.push_back("yellow dish");
        validCommands.push_back("pink bowl");
        validCommands.push_back("blue bowl");
        validCommands.push_back("mineral water");
        validCommands.push_back("oolong tea");
        validCommands.push_back("ketchup");
        validCommands.push_back("canned mustard");
        validCommands.push_back("orange drink");
        validCommands.push_back("green drink");
        validCommands.push_back("tomato");
        validCommands.push_back("potato");
        validCommands.push_back("plant");
        validCommands.push_back("spray");
        validCommands.push_back("water bottle");
        validCommands.push_back("blueberry drink");
        validCommands.push_back("eggplant");

        nextState = SM_INIT_STATE;

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

        std::string pathQRObjs = "/home/takeshi/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/qr_object.txt";


        //int objs_cmds=5;
        int objs_cmds=0;
        std::vector<std::string> objectsToBring(5);
        bool startopendrawer=false;
        bool startopenfridge=false;

        while(ros::ok() && !success) {

                switch(nextState) {

                case SM_INIT_STATE:

                        while(!TakeshiManip::isTheHandPressed()) {
                                cout << "I am waiting" << endl;
                                ros::spinOnce();
                                loop.sleep();
                        }
                        TakeshiHRI::enableSpeechRecognized(false);
                        TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                        TakeshiKnowledge::loadNameUnknownObject(unknownObject1, pathObjectName);
                        printState("SM INIT STATE");
                        TakeshiHRI::waitAfterSay("Tell me what to bring!", 5000);
                        TakeshiHRI::enableSpeechRecognized(false);
                        TakeshiHRI::waitAfterSay("Show me QR code of the five objects",400);
                        nextState=SM_CHECK_QR;
                        break;

                case SM_CHECK_QR:
                        if(readQRObjects(pathQRObjs,objectsToBring))
                        {
                                if (objectsToBring.size()<1) {
                                        std::cout << "Nothing saved read QRs" << '\n';
                                        nextState = SM_LISTEN_CMDS;
                                }
                                nextState = SM_GET_SHELF_LOCATIONS;
                        }
                        else
                        {
                                std::cout << "File not read or empty means nothing to be found " << '\n';
                                nextState = SM_LISTEN_CMDS;
                        }

                        break;

                case SM_LISTEN_CMDS:
                        printState("Receiving locations");
                        if(objs_cmds<5)
                        {
                                if(TakeshiVision::read_QR(objectsToBring[objs_cmds]))
                                {
                                        takeshi_say.str(std::string());
                                        takeshi_say << "I will bring you " << objectsToBring[objs_cmds];
                                        TakeshiHRI::waitAfterSay(takeshi_say.str(),400);
                                        objs_cmds++;
                                }
                        }
                        else
                        {
                                TakeshiHRI::waitAfterSay("Ok",400);
                                writeQRObjects(pathQRObjs,objectsToBring);
                                nextState = SM_GET_TABLE_LOCATIONS;
                        }
                        break;


                case SM_GET_TABLE_LOCATIONS:
                        printState("Getting table  locations first");
                        TakeshiKnowledge::loadFromFile(pathObjectLocationsDining);
                        nextState = SM_GET_FRIDGE_LOCATIONS;
                        for (int i = 0; i < objectsToBring.size(); i++) {
                                if(TakeshiKnowledge::existKnownLocation(objectsToBring[i])) {
                                        TakeshiHRI::waitAfterSay("I know the location: table", 4000);
                                        objectLocation="dining_table";
                                        objectToTake = objectsToBring[i];
                                        takeshi_say.str(std::string());
                                        takeshi_say << "I will bring you " << objectToTake;
                                        TakeshiHRI::waitAfterSay(takeshi_say.str(), 4000);
                                        objectsToBring.erase(objectsToBring.begin()+i);
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        break;
                                }
                        }
                        break;

                case SM_GET_SHELF_LOCATIONS:
                        printState("Getting shelf locations first");
                        TakeshiKnowledge::loadFromFile(pathObjectLocationsShelf);
                        nextState = SM_GET_TABLE_LOCATIONS;
                        for (int i = 0; i < objectsToBring.size(); i++) {
                                if(TakeshiKnowledge::existKnownLocation(objectsToBring[i])) {
                                        TakeshiHRI::waitAfterSay("I know the location: shelf", 4000);
                                        objectLocation="wall_shelf";
                                        objectToTake = objectsToBring[i];
                                        objectsToBring.erase(objectsToBring.begin()+i); ////????????????????????????????????
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        break;
                                }
                        }
                        break;
                case SM_GET_FRIDGE_LOCATIONS:
                        printState("Getting fridge locations first");
                        TakeshiKnowledge::loadFromFile(pathObjectLocationsFridge);
                        nextState = SM_GET_DRAWER1_LOCATIONS;
                        for (int i = 0; i < objectsToBring.size(); i++) {
                                if(TakeshiKnowledge::existKnownLocation(objectsToBring[i])) {
                                        TakeshiHRI::waitAfterSay("I know the location: fridge", 4000);
                                        objectLocation="refrigerator";
                                        TakeshiNavigation::moveDistAngle(0.0, 1.5707, 4000);
                                        objectToTake = objectsToBring[i];
                                        objectsToBring.erase(objectsToBring.begin()+i);
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        break;
                                }
                        }
                        break;
                case SM_GET_DRAWER1_LOCATIONS:
                        printState("Getting drawer locations first");
                        TakeshiKnowledge::loadFromFile(pathObjectLocationsDrawer1);
                        nextState=SM_GET_DRAWER2_LOCATIONS;
                        for (int i = 0; i < objectsToBring.size(); i++) {
                                if(TakeshiKnowledge::existKnownLocation(objectsToBring[i])) {
                                        TakeshiHRI::waitAfterSay("I know the location: drawer", 4000);
                                        objectLocation="drawer_1";
                                        objectToTake = objectsToBring[i];
                                        objectsToBring.erase(objectsToBring.begin()+i);
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        break;
                                }
                        }
                        break;

                case SM_GET_DRAWER2_LOCATIONS:
                        printState("Getting drawer locations first");
                        TakeshiKnowledge::loadFromFile(pathObjectLocationsDrawer2);
                        nextState=SM_GET_DRAWER3_LOCATIONS;
                        for (int i = 0; i < objectsToBring.size(); i++) {
                                if(TakeshiKnowledge::existKnownLocation(objectsToBring[i])) {
                                        TakeshiHRI::waitAfterSay("I know the location: drawer", 4000);
                                        objectLocation="drawer_2";
                                        objectToTake = objectsToBring[i];
                                        objectsToBring.erase(objectsToBring.begin()+i);
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        break;
                                }
                        }
                        break;

                case SM_GET_DRAWER3_LOCATIONS:
                        printState("Getting drawer locations first");
                        TakeshiKnowledge::loadFromFile(pathObjectLocationsDrawer3);
                        nextState=SM_GET_DRAWER4_LOCATIONS;
                        for (int i = 0; i < objectsToBring.size(); i++) {
                                if(TakeshiKnowledge::existKnownLocation(objectsToBring[i])) {
                                        TakeshiHRI::waitAfterSay("I know the location: drawer", 4000);
                                        objectLocation="drawer_3";
                                        objectToTake = objectsToBring[i];
                                        objectsToBring.erase(objectsToBring.begin()+i);
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        break;
                                }
                        }
                        break;

                case SM_GET_DRAWER4_LOCATIONS:
                        printState("Getting drawer locations first");
                        TakeshiKnowledge::loadFromFile(pathObjectLocationsDrawer4);
                        nextState=SM_GET_KNOW_LOCATIONS;
                        for (int i = 0; i < objectsToBring.size(); i++) {
                                if(TakeshiKnowledge::existKnownLocation(objectsToBring[i])) {
                                        TakeshiHRI::waitAfterSay("I know the location: drawer", 4000);
                                        objectLocation="drawer_4";
                                        objectToTake = objectsToBring[i];
                                        objectsToBring.erase(objectsToBring.begin()+i);
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        break;
                                }
                        }
                        break;

                /*
                   case SM_VERIFY_LOCATION:
                   printState("SM_COMMAND_VERIFY_LOCATION");
                   TakeshiKnowledge::loadFromFile(pathObjectLocationsFridge);
                   if(TakeshiKnowledge::existKnownLocation(objectToTake)) {
                          TakeshiHRI::waitAfterSay("The object is in the fridge", 4000);
                          objectLocation="refrigerator";
                          TakeshiKnowledge::loadFromFile(pathVisitLocations);
                          nextState=SM_GOTO_TAKE_OBJECT;
                          break;
                   }

                   ros::spinOnce();
                   loop.sleep();

                   TakeshiKnowledge::loadFromFile(pathObjectLocationsDrawer);
                   if(TakeshiKnowledge::existKnownLocation(objectToTake)) {
                          TakeshiHRI::waitAfterSay("The object is in the drawer", 4000);
                          objectLocation="drawer_1";
                          TakeshiKnowledge::loadFromFile(pathVisitLocations);
                          nextState=SM_GOTO_TAKE_OBJECT;
                          break;
                   }

                   ros::spinOnce();
                   loop.sleep();

                   TakeshiKnowledge::loadFromFile(pathObjectLocations);
                   if(TakeshiKnowledge::existKnownLocation(objectToTake)) {
                          TakeshiHRI::waitAfterSay("I know the location", 4000);
                          objectLocation=objectToTake;
                          TakeshiKnowledge::loadFromFile(pathObjectLocations);
                          nextState=SM_GOTO_TAKE_OBJECT;
                   }

                   else{
                          TakeshiHRI::waitAfterSay("I do not the location of the object, i will find the object",4000);
                          TakeshiKnowledge::loadFromFile(pathVisitLocations);

                          nextState=SM_GET_KNOW_LOCATIONS;
                   }

                   break;
                 */
                case SM_GET_KNOW_LOCATIONS:
                        printState("SM_GET_KNOW_LOCATIONS");
                        //Get locations and iterator
                        //Load visit locations
                        mapCounter=0;
                        TakeshiKnowledge::loadFromFile(pathVisitLocations);
                        TakeshiKnowledge::getKnownLocations(locations);
                        it = locations.find("entrance");
                        if (it != locations.end())
                                locations.erase(it);

                        locSize=locations.size();
                        printState("Get Know locations");

                        takeshi_say.str(std::string());
                        takeshi_say << "I will visit " << locations.size() << " locations";
                        TakeshiHRI::say( takeshi_say.str() );
                        objectLocation=getClosestLocation(locations);
                        findObject=true;
                        nextState = SM_GOTO_TAKE_OBJECT;
                        break;

                case SM_GOTO_TAKE_OBJECT:
                        printState("Go to Object");
                        TakeshiKnowledge::loadFromFile(pathVisitLocations);
                        TakeshiHRI::enableSpeechRecognized(false);
                        takeshi_say.str(std::string());
                        takeshi_say << "I go to the object location";
                        TakeshiHRI::say( takeshi_say.str() );

                        if (findObject) {
                                if (mapCounter >= locSize)
                                {
                                        takeshi_say.str(std::string());
                                        takeshi_say << "Sorry, i can not grasp the object";
                                        TakeshiHRI::say( takeshi_say.str());
                                        nextState=SM_GET_SHELF_LOCATIONS;
                                }

                                else{
                                        mapCounter++;
                                        if(!TakeshiNavigation::getClose(objectLocation,100000))
                                                TakeshiNavigation::getClose(objectLocation,100000);
                                        nextState=SM_TAKE_OBJECT;
                                }
                        }

                        else{
                                if(!TakeshiNavigation::getClose(objectLocation,100000))
                                        TakeshiNavigation::getClose(objectLocation,100000);
                                nextState=SM_TAKE_OBJECT;
                        }

                        break;

                case SM_TAKE_OBJECT:
                        printState("Take Object");
                        humanlocation="human_location_1";


                        if (objectLocation == "refrigerator")
                                nextState=SM_OPEN_FRIDGE;
                        else if (objectLocation == "drawer_1")
                                nextState=SM_OPEN_DRAWER;
                        else if (objectLocation == "drawer_2")
                                nextState=SM_OPEN_DRAWER;
                        else if (objectLocation == "drawer_3")
                                nextState=SM_OPEN_DRAWER;
                        else if (objectLocation == "drawer_4")
                                nextState=SM_OPEN_DRAWER;
                        else if (objectLocation == "wall_shelf")
                                nextState=SM_GRASP_SHELF;
                        else
                                nextState=SM_GRASP_OBJECT;

                        if(findObject)
                                objectLocation=getClosestLocation(locations);
                        break;

                case SM_OPEN_FRIDGE:
                        printState("Open Fridge");

                        if(findObject) {
                                takeshi_say.str(std::string());
                                takeshi_say << "Human, can you open the fridge please?";
                                TakeshiHRI::say( takeshi_say.str() );
                                ros::Duration(5.0).sleep();

                        }

                        else{
                                if(TakeshiTasks::openFridge()) {
                                        takeshi_say.str(std::string());
                                        takeshi_say << "I will take the object";
                                        TakeshiHRI::say( takeshi_say.str() );
                                }

                                else{
                                        takeshi_say.str(std::string());
                                        takeshi_say << "Human, can you open the fridge please?";
                                        TakeshiHRI::say( takeshi_say.str() );
                                        ros::Duration(5.0).sleep();
                                }
                        }
                        nextState= SM_GRASP_FRIDGE;
                        break;

                case SM_GRASP_FRIDGE:
                        isTaken=TakeshiTasks::graspObjectOnTheFridge(objectToTake, verify);

                        if(!isTaken) {
                                takeshi_say.str(std::string());
                                takeshi_say << "Sorry, i can not grasp the object";
                                TakeshiHRI::say( takeshi_say.str());
                                TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                                if(findObject) {
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        TakeshiKnowledge::loadFromFile(pathVisitLocations);
                                }
                                else{
                                        nextState=SM_GET_SHELF_LOCATIONS;

                                        findObject=false;
                                }
                        }
                        else{
                                TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                                TakeshiTasks::closeFridge();
                                nextState=SM_GOTO_RELEASE_OBJECT;
                        }
                        break;

                case SM_OPEN_DRAWER:
                        printState("Open Drawer");

                        if(findObject) {
                                takeshi_say.str(std::string());
                                takeshi_say << "Human, can you open the drawer please?";
                                TakeshiHRI::say( takeshi_say.str() );
                                ros::Duration(5.0).sleep();

                        }
                        else{
                                if(startopendrawer) {

                                        if(TakeshiTasks::openDrawer()) {
                                                takeshi_say.str(std::string());
                                                takeshi_say << "I will take the object";
                                                TakeshiHRI::say( takeshi_say.str() );
                                        }
                                        else{
                                                takeshi_say.str(std::string());
                                                takeshi_say << "Human, can you open the drawer please?";
                                                TakeshiHRI::say( takeshi_say.str() );
                                                ros::Duration(5.0).sleep();
                                        }
                                }
                                else{
                                        takeshi_say.str(std::string());
                                        takeshi_say << "Human, can you open the drawer please?";
                                        TakeshiHRI::say( takeshi_say.str() );
                                        ros::Duration(5.0).sleep();
                                }
                        }
                        nextState=SM_GRASP_DRAWER;
                        break;

                case SM_GRASP_DRAWER:
                        if (objectLocation == "drawer_1")
                                planeDrawer=0.09;
                        else if (objectLocation == "drawer_2")
                                planeDrawer=0.09;
                        else if (objectLocation == "drawer_3")
                                planeDrawer=0.18;
                        else if (objectLocation == "drawer_4")
                                planeDrawer=0.18;
                        TakeshiNavigation::moveDistAngle(0.0, -1.5707, 3000);
                        TakeshiTasks::alignWithTable(0.15, true);
                        isTaken=TakeshiTasks::graspObjectOnTheDrawer(objectToTake, planeDrawer, verify);
                        if(!isTaken)
                                isTaken=TakeshiTasks::graspObjectOnTheDrawer(objectToTake, planeDrawer, verify);

                        if(!isTaken) {
                                takeshi_say.str(std::string());
                                takeshi_say << "Sorry, i can not grasp the object";
                                TakeshiHRI::say( takeshi_say.str());
                                TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                                if(findObject) {
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        TakeshiKnowledge::loadFromFile(pathVisitLocations);
                                }
                                else{
                                        nextState=SM_GET_SHELF_LOCATIONS;

                                        findObject=false;
                                }
                        }
                        else{
                                TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                                nextState=SM_GOTO_RELEASE_OBJECT;
                        }

                        break;

                case SM_GRASP_SHELF:
                        takeshi_say.str(std::string());
                        takeshi_say << "I will take the object";
                        TakeshiHRI::say( takeshi_say.str() );
                        TakeshiTasks::alignWithTable(0.25, false);

                        isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);
                        if(!isTaken)
                                isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);

                        if(!isTaken){
                          TakeshiManip::hdGoTo(0.0,0.8, 4000);
                          isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);
                          if(!isTaken)
                                  isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);
                        }

                        if(!isTaken){
                        TakeshiManip::torsoGoTo(0.0, 4000);
                        TakeshiManip::hdGoTo(0.0,-0.8, 4000);
                        isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);
                        if(!isTaken)
                                isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);
                        }
                        /*if(!isTaken)
                            isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);
                           if(!isTaken)
                            isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);
                         */
                        if(!isTaken) {
                                takeshi_say.str(std::string());
                                takeshi_say << "Sorry, i can not grasp the object";
                                TakeshiHRI::say( takeshi_say.str());
                                TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                                if(findObject) {
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        TakeshiKnowledge::loadFromFile(pathVisitLocations);
                                }else{
                                        nextState=SM_GET_SHELF_LOCATIONS;
                                        findObject=false;
                                }
                        }
                        else{
                                TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                                nextState=SM_GOTO_RELEASE_OBJECT;
                        }
                        break;

                case SM_GRASP_OBJECT:
                        takeshi_say.str(std::string());
                        takeshi_say << "I will take the object";
                        TakeshiHRI::say( takeshi_say.str() );
                        TakeshiTasks::alignWithTable(0.25, false);

                        isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);
                        if(!isTaken)
                                isTaken=TakeshiTasks::graspObjectLateral(objectToTake, verify);

                        if(!isTaken) {
                                takeshi_say.str(std::string());
                                takeshi_say << "Sorry, i can not grasp the object";
                                TakeshiHRI::say( takeshi_say.str());
                                TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                                if(findObject) {
                                        nextState=SM_GOTO_TAKE_OBJECT;
                                        TakeshiKnowledge::loadFromFile(pathVisitLocations);
                                }else{

                                        nextState=SM_GET_SHELF_LOCATIONS;

                                        findObject=false;
                                }
                        }
                        else{
                                TakeshiKnowledge::loadFromFile(pathKnowLocationFile);
                                nextState=SM_GOTO_RELEASE_OBJECT;
                        }
                        break;

                case SM_GOTO_RELEASE_OBJECT:
                        printState("Goto release object");
                        TakeshiHRI::say("I will go to Human Location");
                        if(!TakeshiNavigation::getClose(humanlocation,100000)) {
                                TakeshiHRI::say("I could not get to the human location, i will trying again");
                                if(!TakeshiNavigation::getClose(humanlocation,100000))
                                        TakeshiHRI::say("I could not get to the human location, but i will release the object");
                        }
                        TakeshiHRI::say("Hello Human, i will find you");
                        nextState=SM_FIND_PERSON;

                        break;

                case SM_FIND_PERSON:
                        if(TakeshiTasks::findPerson("", -1, TakeshiTasks::STANDING, false)) {
                                humanlocation="human_location_1";
                                nextState=SM_RELEASE_OBJECT;
                        }
                        else{
                                TakeshiHRI::say("I did not find you");

                                nextState=SM_GOTO_RELEASE_OBJECT;

                                if(humanlocation=="human_location_1")
                                        humanlocation="human_location_2";
                                else if(humanlocation=="human_location_2")
                                        humanlocation="human_location_3";
                                else if(humanlocation=="human_location_3") {
                                        TakeshiHRI::say("Human, please put yourself in front of me");
                                        TakeshiManip::navigationPose(4000);
                                        humanlocation="human_location_1";
                                        ros::Duration(5.0).sleep();
                                        nextState=SM_RELEASE_OBJECT;
                                }

                        }
                        break;

                case SM_RELEASE_OBJECT:
                        //Relase object task
                        TakeshiTasks::giveObjectToHuman();
                        TakeshiManip::navigationPose(5000);
                        TakeshiHRI::waitAfterSay("I will go to the next object", 5000);
                        TakeshiKnowledge::loadFromFile(pathObjectLocations);
                        TakeshiHRI::enableSpeechRecognized(true);
                        nextState=SM_GET_SHELF_LOCATIONS;

                        break;

                case SM_RETURN_TO_INIT:
                        printState("Return to init");
                        takeshi_say.str(std::string());
                        takeshi_say << "I finished";
                        TakeshiHRI::say( takeshi_say.str() );
                        //TakeshiNavigation::getClose("entrance",100000);
                        nextState=SM_GET_TABLE_LOCATIONS;
                        break;

                }

                ros::spinOnce();
                loop.sleep();

        }

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

bool writeQRObjects(std::string pth, std::vector<std::string> &objs)
{
        std::ofstream objFile(pth.c_str(),ios::app);
        std::cout << "Saving known QR locations from " << pth   << std::endl;

        if (objFile.is_open())
        {
                for (size_t i = 0; i < objs.size(); i++) {
                        objFile << objs[i] << "\n";
                        std::cout << "QR Object -> " << objs[i]<<'\n';
                }
        }
        else
        {
                objFile.close();
                return false;
        }
        objFile.close();
        return true;
}

bool readQRObjects(std::string pth, std::vector<std::string> &objs)
{
        //Will simply read file on from pth.
        std::cout << "Loading known object locations from " << pth   << std::endl;
        std::ifstream file(pth.c_str());
        if (!file.is_open()) {
                std::cout << "Cloud not open file" << '\n';
                file.close();
                return false;
        }
        std::string line;
        objs.clear();
        while (std::getline(file,line)) {
                std::istringstream iss(line);
                //float x, y, th;
                std::string objName;
                if (!(iss >>objName))
                {
                        std::cout << "Parsing Error" << '\n';
                        continue;
                }
                objs.push_back(objName);
                std::cout << "QR Object ->" << objName <<'\n';
        }
        if (objs.size()<1) {
                std::cout << "Nothing on file " << '\n';
                file.close();
                return false;
        }
        file.close();
        return true;
      }
