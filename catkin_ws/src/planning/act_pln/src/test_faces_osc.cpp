#include "ros/ros.h"
#include "takeshi_tools/TakeshiHardware.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiRepresentation.h"
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
using namespace cv;
bool success=false;
enum state {
        SM_START,
        SM_FIND_PERSON,
        SM_END
};

void printState(std::string st);

int main(int argc, char** argv){
        cout << "--------------Test------------" << endl;

         ros::init(argc, argv, "faces_test");
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
       
        
        ros::Rate loop(30);
        int nextState=SM_START;
        TakeshiVision::setNodeHandle(&n);
         std::string lastRecoSpeech;
    std::string train_name;
    std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
    train_name="train_";
        vision_msgs::VisionFaceObjects vfo;
    std::vector<std::string> validCommandsNames;
    std::vector<std::string> validCommandsDrinks;
    std::vector<std::string> AvailableDrinks;
    std::vector<std::string> aux_drinks;
    std::vector<std::string>::iterator it;
    std::vector<float> obj_position;
    std::vector<vision_msgs::GestureSkeleton> gestures;
    vision_msgs::GestureSkeleton gesture;
    vision_msgs::Skeleton skeletonZero;

    bool findBagLeftSide=false;
    bool findBagRightSide=false; 
    int closestSkl;               
    vision_msgs::Skeletons skl;
    std::vector<std::string> specificGestures;
   
    
    ros::Rate rate(10);





    //names
   

    //OPENPOSES
     specificGestures.push_back("right_hand_rised");
     specificGestures.push_back("left_hand_rised");
     specificGestures.push_back("hand_right_extended");
     specificGestures.push_back("hand_left_extended");
     specificGestures.push_back("drinking_right");
     specificGestures.push_back("drinking_left");
     specificGestures.push_back("both_hands_down");









        int train_count =0;
        int i;
        string  training_name="train_";
        
        while(ros::ok() && !success) {
                switch(nextState)
                {
                case SM_START:

                        nextState=SM_FIND_PERSON;
                                               
                        break;


                case SM_FIND_PERSON:
               std::cout << "SM FIN PERSON"<< std::endl;
                while (!TakeshiTasks::turnAndRecognizeFacenet("",false) )
                //while(lastRecognizedFaces.size() < 1)
                {
                        ros::spinOnce();
                        TakeshiHRI::waitAfterSay("I am looking for you",3000);
                        std::cout << "Looking ......."<< std::endl;
                }        
                std::cout << "I FOUND YA"<< std::endl;
                nextState=  SM_END;
                
                

                break;     

                case SM_END:

                        success=true;
                                               
                        break;
 
                                               

            
                }

                ros::spinOnce();
                loop.sleep();

        }

}