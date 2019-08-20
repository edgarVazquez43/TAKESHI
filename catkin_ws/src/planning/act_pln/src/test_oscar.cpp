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
        SM_TRAIN,
        SM_HANDS_DOWN,
        SM_RECOG

};

void printState(std::string st);

int main(int argc, char** argv){
        cout << "--------------Test------------" << endl;

        ros::init(argc, argv,"test");
        ros::NodeHandle n;
        ros::Rate loop(30);
        int nextState=SM_START;  
    TakeshiHRI::setNodeHandle(&n);
    TakeshiHardware::setNodeHandle(&n);
    TakeshiKnowledge::setNodeHandle(&n);
    TakeshiNavigation::setNodeHandle(&n);
    TakeshiManip::setNodeHandle(&n);
    TakeshiTasks::setNodeHandle(&n);
    TakeshiTools::setNodeHandle(&n);
    TakeshiVision::setNodeHandle(&n);
    TakeshiRepresentation::setNodeHandle(&n);
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
        int counter =0;
        string  training_name="train_";
        
        while(ros::ok() && !success) {
                switch(nextState)
                {
                case SM_START:

                //posible move of face
                //check get face
                //vfo=TakeshiTasks::turnAndRecognizeFacenet("", false); //lastRecognizedFaces = TakeshiVision::getFaces("").recog_faces;
                //TakeshiHardware::stopRobot();
                //TakeshiManip::hdGoTo(0, 0.7, 3000);

                while (!TakeshiTasks::turnAndRecognizeFacenet(""))
                //while(lastRecognizedFaces.size() < 1)
                {
                        ros::spinOnce();
                        TakeshiHRI::waitAfterSay("looking ",3000);
                        //ros::spinOnce();
                        ros::Duration(4.0).sleep();
                        //vfo = TakeshiTasks::turnAndRecognizeFacenet("", false);
                        if(counter > 5)
                                break;
                        counter++;
                }
                        success=true;
                        break;


                case SM_TRAIN:
                   TakeshiVision::startSkeletonFinding();
            ros::Duration(1.0).sleep();


                     
            std::cout << "FINDING Rise Hand"<<std::endl;
                                               

            if(TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 14000)) 
                            {
                                
                                if(gesture.gesture.compare("right_hand_rised")==0 or gesture.gesture.compare("left_hand_rised")==0 
                                    or gesture.gesture.compare("hand_left_extended")==0 or gesture.gesture.compare("hand_right_extended")==0)
                                   {

                                    std::cout << "FOUND"<<std::endl;
                                    std::cout << gesture.gesture_centroid.x<<std::endl;
                                    std::cout << gesture.gesture_centroid.y<<std::endl;
                                    std::cout << gesture.gesture_centroid.z<<std::endl;
                                    nextState=SM_HANDS_DOWN;
                                   
                                    TakeshiVision::stopSkeletonFinding();
                                    break;
                                   }


                       
                                    }
                       
                        
                        ros::Duration(1.0).sleep();
                        ros::spinOnce();
                      


         
                   
                                           
                    break;


                case SM_HANDS_DOWN:
                   TakeshiVision::startSkeletonFinding();
            ros::Duration(1.0).sleep();


                     
            std::cout << "FINDING Hands Down"<<std::endl;
                                               

            if(TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 14000)) 
                            {
                                
                                if(gesture.gesture.compare("both_hands_down")==0)
                                   {

                                    std::cout << "FOUND"<<std::endl;
                                    std::cout << gesture.gesture_centroid.x<<std::endl;
                                    std::cout << gesture.gesture_centroid.y<<std::endl;
                                    std::cout << gesture.gesture_centroid.z<<std::endl;
                                    nextState= SM_RECOG;
                                    TakeshiVision::stopSkeletonFinding();
                                    break;
                                   }


                       
                                    }
                       
                        
                        ros::Duration(1.0).sleep();
                        ros::spinOnce();
                      


                                           
                    break;





                case SM_RECOG:
                         while (!TakeshiTasks::turnAndRecognizeFacenet("oscar"))
                //while(lastRecognizedFaces.size() < 1)
                {
                        ros::spinOnce();
                        TakeshiHRI::waitAfterSay("I am looking for you",3000);
                        //ros::spinOnce();
                        ros::Duration(4.0).sleep();
                        //vfo = TakeshiTasks::turnAndRecognizeFacenet("", false);
                        if(counter > 5)
                                break;
                        counter++;
                }               }

                ros::spinOnce();
                loop.sleep();

        }

}