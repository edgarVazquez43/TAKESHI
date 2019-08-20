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
        validCommandsStop.push_back("pick up the object");
        validCommandsStop.push_back("follow me");
        validCommandsStop.push_back("this is the dining table");
        validCommandsStop.push_back("deliver object to the living room");
        validCommandsStop.push_back("take it to the dining table");

        int nextState=SM_FIND_OBJ;

        ros::Rate rate(10);
        nextState = SM_FIND_OBJ;

        std::vector<vision_msgs::VisionObject> recognizedObjects;
        vision_msgs::VisionObject objToGrasp;

        std::stringstream takeshi_say;
        geometry_msgs::Pose poseToGrasp;
        bool success = false;
        TakeshiHRI::enableSpeechRecognized(true);
        TakeshiVision::startQRReader();
        TakeshiHRI::loadGrammarSpeechRecognized("demo_noviembre.xml");
        TakeshiHRI::waitAfterSay("Hello, my name is takeshi", 4000);
        //TakeshiVision::loadSpecificTrainingDir("dining");



        while (ros::ok() && !success) {
                switch (nextState) {
                case SM_START:
                        printState("¡¡¡¡SM START!!!!!!");
                        if (!TakeshiManip::isTheHandPressed()) {
                                //cout << "I am waiting" << endl;
                        }
                        else
                        {
                                TakeshiHRI::enableSpeechRecognized(false);
                                TakeshiHRI::waitAfterSay("I am looking for objects on the floor", 2500);
                                nextState= SM_FIND_OBJ;
                        }
                        break;
                case SM_FIND_OBJ:

                        printState("Finding objects on location");
                        TakeshiManip::hdGoTo(0.0,-1.0, 4000);
                        if (TakeshiVision::detectObjectsFloor(recognizedObjects, true))
                        {
                                nextState = SM_GRASP_OBJ_FLOOR;

                        }
                        break;

                case SM_GRASP_OBJ_FLOOR:

                        printState("Grasping objects floor");
                        objToGrasp = recognizedObjects[0];
                        takeshi_say.str(std::string());
                        takeshi_say << "I am grasping the object" << objToGrasp.id;
                        poseToGrasp = objToGrasp.pose;
                        TakeshiHRI::say( takeshi_say.str());
                        TakeshiManip::hdGoTo(0,0.0,5000);
                        if(TakeshiTasks::graspObjectOnFloorFromAbove(
                                   recognizedObjects[0],
                                   0.0,
                                   true))
                        {
                                TakeshiHRI::waitAfterSay("Ok?", 3000);
                                nextState = SM_INIT_FOLLOW_CONFIRM;

                        }
                        else{
                                nextState=SM_FIND_OBJ;
                        }
                        break;



                case SM_INIT_FOLLOW_CONFIRM:
                        TakeshiHRI::say("Hello Human, i will find you");

                        if(TakeshiTasks::findPerson("", -1, TakeshiTasks::STANDING, false)) {

                                nextState=SM_RELEASE_OBJECT;
                        }
                        break;

                case SM_RELEASE_OBJECT:
                        //Relase object task
                        TakeshiTasks::giveObjectToHuman();
                        TakeshiManip::navigationPose(5000);
                        TakeshiVision::stopQRReader();
                        success=true;

                        break;
                }

                rate.sleep();
                ros::spinOnce();
        }

        return 0;

}
