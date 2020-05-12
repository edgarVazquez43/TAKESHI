////////////////////////////////////////////////////////
// Note: this code was commented into CMake file,
// If you are brave enough to edit this code please
// make sure to uncomment this code into CMakeList.txt
///////////////////        EDD-II    ////////////////////

#include "ros/ros.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiNavigation.h"

enum state {
        SM_INIT_STATE,
        SM_START,
        SM_FIND_OBJ,
        SM_GRASP_OBJ_FLOOR,
        SM_INIT_FOLLOW,
        SM_FOLLOW_ME,
        SM_FOLLOWING_PHASE,
        SM_INIT_FOLLOW_CONFIRM,
        SM_NAVIGATE_FOLLOW,
        SM_FOLLOW_CONFIRMATION,
        SM_PLACE_OBJ,
        SM_WAIT_ORDER,
        SM_FIND_OBJ_TABLE,
        SM_GRASP_OBJ_HAND,
        SM_GRASP_OBJ_TABLE,
        SM_FIND_PERSON,
        SM_GOTO_DELIVERY,
        SM_RELEASE_OBJECT
};

void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        CASE: "<< st << "\033[0m" << std::endl;
}


// This is for the attemps for a actions
std::string lastCmdName = "";
int numberAttemps = 0;

int main(int argc, char **argv) {

        ros::init(argc, argv, "demo18");
        ros::NodeHandle n;
        std::string locationsFilePath = "";

        TakeshiHRI::setNodeHandle(&n);
        TakeshiTasks::setNodeHandle(&n);
        bool userConfirmation=false;

        string lastRecoSpeech;
        std::vector<std::string> validCommandsStop;
        validCommandsStop.push_back("pick up the objects");
        
        int nextState=SM_INIT_STATE;
        ros::Rate rate(10);
        
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        vision_msgs::VisionObject objToGrasp;

        std::stringstream takeshi_say;
        geometry_msgs::Pose poseToGrasp;
        bool success = false;
        TakeshiVision::startQRReader();
        TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/final_tmr.jsgf", "final_tmr");
        TakeshiHRI::enableSphinxMic(true);
        //TakeshiHRI::waitAfterSay("Hello, my name is takeshi");
        //TakeshiVision::loadSpecificTrainingDir("dining");
        
        std::vector<std::string> trashObjects;
        //trashObjects.push_back("cube_block");
        //trashObjects.push_back("cajeta_cokkies");
        trashObjects.push_back("chocolate_cookies");
        trashObjects.push_back("gansito_envelop");
        trashObjects.push_back("pineapple_cookies");
        //trashObjects.push_back("strawberry_cookies");
        //trashObjects.push_back("rope");
        trashObjects.push_back("bill");

        trashObjects.push_back("purple_mug");
        trashObjects.push_back("red_mug");
        trashObjects.push_back("green_mug");
        trashObjects.push_back("blue_mug");
        

        vision_msgs::ObjectCoordinatesForDetection objectsCoordinates;  
        objectsCoordinates=TakeshiVision::objectCoordinates;
        objectsCoordinates.z_max=0.3;
        unsigned int maxDetects =3, detectTries=0;

        while (ros::ok() && !success) {
                switch (nextState) {

                case SM_INIT_STATE:
                        printState("SM_INIT_STATE");
                        TakeshiHRI::enableSphinxMic(false);
                        if(TakeshiManip::isTheHandPressed()){
                            TakeshiManip::hdGoTo(0,0.7,3000);
                            TakeshiHRI::waitAfterSay("Hello, my name is Takeshi, i'm going to start the test, pick up demo, tell me what you want me to do");
                            TakeshiHRI::enableSphinxMic(true);
                            nextState=SM_START;
                        }  
                break;

                case SM_START:
                        printState("¡¡¡¡SM START!!!!!!");
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 4000))
                                if(lastRecoSpeech.find("pick up the objects") != std::string::npos) {
                                        TakeshiHRI::enableSphinxMic(false);
                                        TakeshiHRI::waitAfterSay("I'm going to look for objects on the floor");
                                        TakeshiManip::hdGoTo(0,0.7,3000);
                                        nextState= SM_FIND_OBJ;
                                } 
                        break;

                case SM_FIND_OBJ:
                        printState("Finding objects on location");
                        TakeshiManip::hdGoTo(0.0,-1.0, 4000);
                        if(TakeshiVision::detectSpecificYoloObject(trashObjects,recognizedObjects,1000, objectsCoordinates)){
                                nextState = SM_GRASP_OBJ_FLOOR;
                        }
                        else{
                            if (detectTries>=maxDetects) {
                                TakeshiHRI::waitAfterSay( "I can not see the object",2000);
                                TakeshiHRI::waitAfterSay( "what do you want me to do now?",2000);
                                TakeshiHRI::enableSphinxMic(true);  
                                detectTries=0;    
                                nextState = SM_START;       
                            }
                            else  
                                detectTries++;
                        }
                        break;

                case SM_GRASP_OBJ_FLOOR:
                        printState("Grasping objects floor");
                        objToGrasp = recognizedObjects[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I am grasping the object " << objToGrasp.id;
                        
                        if(objToGrasp.id.compare("rope") == 0 )
                        {
                            std::cout << "The object is a Rope" << std::endl;
                            objToGrasp.pose.position.y -= 0.08;
                        }
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::say( takeshi_say.str());
                        TakeshiManip::hdGoTo(0,0.0,5000);
                        if(TakeshiTasks::graspObjectOnFloorFromAbove(
                                   poseToGrasp.position.x,
                                   poseToGrasp.position.y,
                                   poseToGrasp.position.z,
                                   0.0,
                                   false)){

                                TakeshiHRI::say("I'm verifying if I grasped the object");
                                TakeshiManip::hdGoTo(0.0, -0.8, 5000);
                                TakeshiNavigation::moveDist(-0.2, 3000);
                                ros::Duration(2).sleep();
                                if(!TakeshiVision::detectYoloObject(objToGrasp.id,objToGrasp,1000,objectsCoordinates)){
                                    TakeshiHRI::say( "I took the object");
                                    TakeshiHRI::enableSphinxMic(true);
                                    nextState = SM_INIT_FOLLOW_CONFIRM;
                                }
                                else{
                                    TakeshiHRI::say( "I could not take the object");    
                                    nextState=SM_FIND_OBJ;
                                }
                        }
                        else
                            nextState=SM_FIND_OBJ;
                        break;
                

                case SM_INIT_FOLLOW_CONFIRM:
                        TakeshiHRI::say("Human, I'm going to look for you to give you the object");
                        if(TakeshiTasks::turnAndRecognizeFacenet("", true))
                            nextState=SM_RELEASE_OBJECT;                       
                        break;

                case SM_RELEASE_OBJECT:
                        //Relase object task
                        TakeshiManip::hdGoTo(0,0,5000);
                        TakeshiTasks::giveObjectToHuman();
                        TakeshiManip::navigationPose(5000);
                        TakeshiVision::stopQRReader();
                        success=true;
                        TakeshiHRI::say("I finished my demostration, thank you for your attention");
                        break;
                }

                rate.sleep();
                ros::spinOnce();
        }

        return 0;

}
