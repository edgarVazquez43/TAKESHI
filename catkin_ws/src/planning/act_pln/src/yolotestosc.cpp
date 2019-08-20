#include <iostream>
#include <algorithm>
#include <ros/package.h>
#include <stack>
#include <ros/ros.h>
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiNavigation.h"

enum state {
        SM_INIT_STATE,
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
void getArticular(joints& arr,joints & j, float & torso);


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
int main(int argc, char *argv[]) {
        ros::init(argc, argv, "serving_drinks");
        ros::NodeHandle n;
        ros::Rate loop(0.5);
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








        std::string pathToKnowledge = ros::package::getPath("knowledge");
        std::string pathObject3D=pathToKnowledge+"/navigation/objLocations/3Dlocations.txt";
        std::string pathToPoses = pathToKnowledge+"/navigation/objLocations/knownPoses.txt";

        std::map<std::string, loc3D> objLocs3D;
        TakeshiKnowledge::getKnownObjectsLocationFromFile(pathObject3D,
                                                          objLocs3D);

        std::map<std::string, joints> objPoses;
        joints articular;
        float trs;
        TakeshiKnowledge::getKnownObjectsLocationFromFile(pathToPoses,
                                                          objPoses);

        std::cout << "Known Locations:" <<  objLocs3D.size()<<'\n';
        for(std::map<std::string,loc3D >::const_iterator it = objLocs3D.begin();
            it != objLocs3D.end(); ++it)
        {
                std::cout << it->first << ": "
                          << it->second.name << " "
                          << it->second.height << "\n";

        }

        std::cout << "Known Poses:" <<  objPoses.size()<<'\n';
        for(std::map<std::string,joints >::const_iterator it = objPoses.begin();
            it != objPoses.end(); ++it)
        {
                std::cout << it->first << ": "
                          << it->second[0] << " "
                          << it->second[1] << " "
                          << it->second[2] << " "
                          << it->second[3] << " "
                          << it->second[4] << "\n";
        }

        state nextState=SM_INIT_STATE;
        bool success = false;
        std::cout << "Stating state machine" << '\n';
        //Flor plane detection
        std::vector<int> inliersOnPlane;
        std::vector<float> vacantPlane;
        //For object detection
        std::vector<vision_msgs::VisionObject> detectedObjs;
        vision_msgs::VisionObject objToGrasp;
        //For graspeo
        geometry_msgs::Pose poseToGrasp;
        //For talking
        std::stringstream takeshi_say;
        ///For naviation
        std::string mapLocation(""), trayLoc("tray");
        //counters for tries
        unsigned int maxDetects =3, detectTries=0;
        bool verify=true;
        bool detectInTray=false;
        bool detectTrash=false;
        bool detectMugs=false;       

        std::vector<std::string> trayObjects;
        trayObjects.push_back("red_Lego");
        trayObjects.push_back("blue_Lego");
        trayObjects.push_back("yellow_Lego");
        trayObjects.push_back("bill");

        std::vector<std::string> mugObjects;
        mugObjects.push_back("purple_mug");
        mugObjects.push_back("red_mug");
        mugObjects.push_back("green_mug");
        
        std::vector<std::string> trashObjects;
        trashObjects.push_back("apple_juice");
        trashObjects.push_back("cube_block");
        trashObjects.push_back("cajeta_cokkies");
        trashObjects.push_back("pineapple_cookies");
        trashObjects.push_back("soap");
        trashObjects.push_back("strawberry_cookies");
        TakeshiHRI::enableSphinxMic(false);




bool userConfirmation=false;
  
    std::string lastRecoSpeech;
    std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
    std::vector<std::string> validCommandsNames;
    std::vector<std::string> validCommandsDrinks; 
    std::vector<std::string> AvailableDrinks; 
    std::vector<std::string>::iterator it; 


    ros::Rate rate(10);
    int nextState = SM_ASK_FOR_DRINK;
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
    AvailableDrinks.push_back("gin tonic");
    AvailableDrinks.push_back("margarita");
    AvailableDrinks.push_back("mojito");
    //AvailableDrinks.push_back("red wine");
    AvailableDrinks.push_back("chardonnay");
    //AvailableDrinks.push_back("tequila");
    AvailableDrinks.push_back("beer");
    AvailableDrinks.push_back("rum");
    AvailableDrinks.push_back("whiskey");

        while (ros::ok() && !success)
        {
                switch (nextState)
                {
                case SM_INIT_STATE:
                        printState("SM_INIT_STATE");
                        
                        //if(TakeshiManip::isTheHandPressed()){
                            TakeshiHRI::say("Hello, my name is Takeshi, i'm going to start the test");
                            
                                nextState = SM_FIND_OBJS;
                                detectInTray=true;
                                detectTries=0;
                            
                        //}  
                break;

                case SM_FIND_OBJS:


                std::cout << "---------------------------------------------" << std::endl;
     std::cout << "        CASE:  RECO-OBJ     " << std::endl << std::endl;
     // // Find objects
     
     TakeshiManip::torsoGoTo(0.65, 2000);
     articular.push_back(-3.1);
     articular.push_back(0);
     articular.push_back(0);
     articular.push_back( -0.1);
     TakeshiManip::armGoToArticular(articular, 2000);
     

     ros::Duration(3.0).sleep();
     
                        if (TakeshiVision::detectAllYoloObjects(detectedObjs, 2000)){
                            
                            
                                nextState = SM_GRASP_OBJ;
                        }
     // justina_say.str(std::string());
     // justina_say << "I found " << detectedObjs.size() << " objects";
     // std::cout << "I found " << detectedObjs.size() << " objects" << std::endl;
     // TakeshiHRI::say( justina_say.str() );

      
      for(int i = 0; i < detectedObjs.size(); i++)
      {
    std::cout << "Obj[" << i << "]: " << detectedObjs[i].id << " - Pos X: " << detectedObjs[i].pose.position.x << std::endl;
      }
                                      ros::Duration(3.0).sleep();
                                      nextState = SM_GRASP_OBJ;


      
      break;
                /*
                        printState("SM_FIND_OBJS");
                        //TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                        ros::Duration(2).sleep();
                        
                        if (TakeshiVision::detectAllYoloObjects(detectedObjs, 2000)){
                            
                            
                                nextState = SM_FIND_MUGS;
                        }
                        else{
                            if (detectTries>=maxDetects) {
                                TakeshiHRI::waitAfterSay( "I placed all objects, the tray is empty",2000);
                                detectInTray=false; 
                                detectMugs=true;        
                                nextState = SM_FIND_OBJS;       
                            }
                            else  
                                detectTries++;
                        }*/

                        break;

                case SM_GRASP_OBJ:
                        printState("SM_GRASP_OBJ");
                        objToGrasp = detectedObjs[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I'm going to grasp the object " << objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::waitAfterSay( takeshi_say.str(),1000);
                        TakeshiManip::hdGoTo(0,0.0,5000);

                        if(!TakeshiTasks::graspObject(
                        //if(TakeshiTasks::graspObjectOnFloorFromAbove(
                        //if(TakeshiTasks::graspObjectOnFloor(
                                   objToGrasp.pose.position.x,
                                   objToGrasp.pose.position.y,
                                   objToGrasp.pose.position.z,
                                   //0.0,
                                   false))     {
                            TakeshiHRI::say("I'm verifying if I grasped the object");
                            TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                            TakeshiNavigation::moveDist(-0.2, 3000);
                            ros::Duration(2).sleep();
                            if(!TakeshiVision::detectYoloObject(objToGrasp.id,objToGrasp,0.3,1000)){
                                TakeshiHRI::say( "I took the object");
                                //if(detectTrash)
                                //    nextState=SM_GOTO_LOC;
                                //else
                                    nextState= SM_GOTO_LOC;
                            }
                            else{
                                TakeshiHRI::say( "I could not take the object");    
                                if(detectTrash)
                                    nextState=SM_FIND_TRASH;
                                else
                                    nextState=SM_FIND_OBJS;
                            }
                        }
                        
                        else{
                            TakeshiHRI::say( "I could not take the object");
                            TakeshiNavigation::moveDist(-0.2, 3000);
                            if(detectTrash)
                                nextState=SM_FIND_TRASH;
                            else
                                nextState=SM_FIND_OBJS;
                        }
                        break;

                case SM_GOTO_LOC:
                        printState("SM_GOTO_LOC");
                        mapLocation=objLocs3D[objToGrasp.id].name;
                        if(TakeshiNavigation::getClose(mapLocation,50000)){
                                nextState = SM_PLACE_OBJ;
                        }
                        break;

                case SM_PLACE_OBJ:
                        printState("SM_PLACE_OBJ");
                        if(detectInTray){
                            articular.clear();
                            getArticular(objPoses[objToGrasp.id],articular,trs);

                            if(TakeshiTasks::alignWithFrontTable(0.60)) {
                                    //TakeshiTasks::placeObjectInFront(0.0,0.9);
                                if(objToGrasp.id.compare("bill") == 0)
                                    TakeshiNavigation::moveDist(-0.25,5000);
                                    
                                TakeshiManip::torsoGoTo(trs,10000);
                                TakeshiManip::armGoToArticular(articular,4000);
                                ros::spinOnce();
                                TakeshiNavigation::moveDist(0.30,5000);
                                TakeshiManip::openGripper(1.0);
                                ros::Duration(3).sleep();
                                TakeshiNavigation::moveDist(-0.30,5000);
                                nextState=SM_GOTO_TRAY;
                            }
                        }
                        
                        else if(objToGrasp.id.compare("red_mug")==0){
                            TakeshiTasks::placeObjectInColorBin("red");
                            nextState=SM_GOTO_MUG;
                        }
                        else if(objToGrasp.id.compare("purple_mug")==0){
                            TakeshiTasks::placeObjectInColorBin("blue");
                            nextState=SM_GOTO_MUG;
                        }
                        else if(objToGrasp.id.compare("green_mug")==0){
                            TakeshiTasks::placeObjectInColorBin("green");
                            nextState=SM_GOTO_MUG;
                        }                      
                        else{
                            TakeshiTasks::placeObjectInColorBin("yellow");
                            nextState=SM_GOTO_TRASH;
                        }
                       
                        break;

                case SM_GOTO_TRAY:
                        printState("SM_GOTO_TRAY");
                        if(TakeshiNavigation::getClose(trayLoc,40000))
                        {
                                nextState = SM_FIND_OBJS;
                        }
                        break;

                case SM_GOTO_MUG:
                        printState("SM_GOTO_MUG");
                        if(TakeshiNavigation::getClose("mug_location",40000))
                        {
                                nextState = SM_FIND_MUGS;
                                detectTries=0;
                        }
                break;

                
                
                case SM_FIND_MUGS:
                        printState("SM_FIND_MUGS");
                        TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                        ros::Duration(2).sleep();
                        if (TakeshiVision::detectAllYoloObjects(detectedObjs, 2000)){
                                nextState = SM_GRASP_MUG;
                                
                       }
                        else{
                            if (detectTries>=maxDetects) {
                                //TakeshiHRI::say( "I placed all mugs, the floor is empty");
                                TakeshiHRI::say( "There is no mugs left to place");
                                detectTrash=true;
                                nextState = SM_FINAL_STATE;       
                            }
                            else  
                                detectTries++;
                        }

                        break;

                case SM_GRASP_MUG:
                        printState("SM_GRASP_MUG");
                        objToGrasp = detectedObjs[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I am grasping the object " << objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::waitAfterSay( takeshi_say.str(),1000);
                        TakeshiManip::hdGoTo(0,0.0,5000);

                        if(TakeshiTasks::graspObjectOnFloor(
                        //if(TakeshiTasks::graspObjectOnFloor(
                                   objToGrasp.pose.position.x,
                                   objToGrasp.pose.position.y,
                                   objToGrasp.pose.position.z,
                                   //0.0,
                                   false))      {  
                            TakeshiHRI::say("I'm verifying if I grasped the object");
                            //TakeshiNavigation::moveDist(-0.2,4000);
                            TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                            ros::Duration(2).sleep();
                            if(!TakeshiVision::detectYoloObject(objToGrasp.id,detectedObjs[0],0.3,1000)){
                                TakeshiHRI::say( "I took the object");
                                nextState= SM_FINAL_STATE;
                            }
                            else{
                                TakeshiHRI::say( "I could not take the object");  
                            }
                        }
                        else{
                            TakeshiHRI::say( "I could not take the object");
                            TakeshiNavigation::moveDist(-0.25, 3000);
                            nextState=SM_FIND_MUGS;
                        }
                        break;

                case SM_FINAL_STATE:
                        printState("SM_FINAL_STATE");
                        TakeshiHRI::say( "This is the end, my only friend the end"); 
                        TakeshiManip::navigationPose(4000);
                        success=true;
                        break;
                }
                ros::spinOnce();
                loop.sleep();
        }
        return 0;
}


void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        CASE: "<< st << "\033[0m" << std::endl;
}

void getArticular(joints& arr,joints & articular, float & torso)
{
        //Copies from arr[1-4] to articular and torse = arr[0]
    for (int i=0; i<arr.size();i++)
        std::cout << arr[i] << std::endl;
        if (arr.size()<2) {
                std::cout << "Not enought elements on vector " << '\n';
                return;
        }
        torso = arr[0];
        for (size_t i = 1; i < arr.size(); i++) {
                articular.push_back(arr[i]);
        }
        return;
}
