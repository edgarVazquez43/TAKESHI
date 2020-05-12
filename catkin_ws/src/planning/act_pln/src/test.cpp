#include <iostream>
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/types_c.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "justina_tools/JustinaVision.h"
#include "justina_tools/JustinaTasks.h"

#include "vision_msgs/DetectObjects.h"

using namespace std;
using namespace cv;
bool success=false;
enum state {
        SM_START,
        SM_INSTRUCTIONS
       
};

void printState(std::string st);

int main(int argc, char** argv){
        cout << "--------------Test------------" << endl;

        ros::init(argc, argv,"test");
        ros::NodeHandle n;
        ros::Rate loop(30);
        int nextState=SM_START;
        vision_msgs::ObjectCoordinatesForDetection bagsRestrictions;
        cout << bagsRestrictions.y_max << endl;

        TakeshiVision::setNodeHandle(&n);
        TakeshiHRI::setNodeHandle(&n);
        TakeshiTasks::setNodeHandle(&n);
        JustinaVision::setNodeHandle(&n);
        JustinaTasks::setNodeHandle(&n);
        
        Mat BGR,PCL;
        std::vector<vision_msgs::VisionObject> recognizedYoloObjects;
        vision_msgs::VisionObject recognizedYoloObject;
        std::vector<std::string> specificYoloObjects;
        std::vector<std::string> hola;
        specificYoloObjects.push_back("green_mug");
        specificYoloObjects.push_back("purple_mug");
        specificYoloObjects.push_back("red_mug");
        std::stringstream takeshi_say;
        //  std::string object="redLego4x4";
        geometry_msgs::Point centroid3D;
        float y_correction, x_correction;
        float distToGrasp=0.45;
        float torso=0.27, torso_correction;  
        std::vector<vision_msgs::GestureSkeleton> gestures;
        vision_msgs::GestureSkeleton gesture;
        vision_msgs::VisionFlattenedObjectList recoObjList;
        vision_msgs::Skeleton skeletonZero;
        bool findBagLeftSide=false;
        bool findBagRightSide=false; 
        int closestSkl;               
        vision_msgs::Skeletons skl;
        std::vector<std::string> specificGestures;
        std::vector<std::string> colored_bags;
                specificGestures.push_back("right_hand_rised");
                specificGestures.push_back("left_hand_rised");
                specificGestures.push_back("left_hand_rised");
                specificGestures.push_back("left_waving");
                specificGestures.push_back("right_waving");
        colored_bags.push_back("red");
        colored_bags.push_back("yellow");
        colored_bags.push_back("blue");
        colored_bags.push_back("green");
        int y_min=0;
        int y_max=0;
        bool graspBag=false;
        std::vector<std::string> idobject;
        vision_msgs::ObjectCoordinatesForDetection bagsCoordinates;
        vision_msgs::VisionObject object;
float robot_y, robot_x, robot_a;    
    
        float gx_w, gy_w, gz_w;
float dist_to_head;
std::vector<float> obj_position;
                        bool useFeedback= true;
Eigen::Vector3d centroidGesture;
vision_msgs::VisionFaceObjects vfo;
specificYoloObjects.clear();

        while(ros::ok() && !success) {

                switch(nextState) {

                case SM_START:

                    //TakeshiVision::detectAllYoloObjects(recognizedYoloObjects,4000);
                    //TakeshiTasks::graspYoloObject(specificYoloObjects,recognizedYoloObjects,3, 4000, true);
                    //TakeshiVision::detectAllYoloObjects(recognizedYoloObjects, 1000);
                    TakeshiTasks::giveObjectToHuman();
                    //TakeshiVision::detectCircles(object);
                    //TakeshiTasks::alignWithFrontTable(0.58);
                    //0TakeshiVision::detectAllYoloObjectsWithArmCamera(recognizedYoloObjects,100);
                    //ros::Duration(1.0).sleep();
                    ros::spinOnce();
  
                        break;
                case SM_INSTRUCTIONS:
                        //takeshi_say.str(std::string());
                        //takeshi_say << "I am grasping the object " << recognizedYoloObjects[0].id;
//                        TakeshiHRI::waitAfterSay(takeshi_say.str(),1000 );
                        //TakeshiTasks::graspObjectOnFloorFromAbove(
                        //TakeshiTasks::graspObject(
                        for(int i=0; i<colored_bags.size();i++){
                            //graspBag=TakeshiTasks::graspBagInFloor(colored_bags[i], y_min, y_max);
                            if(graspBag)
                                break;
                        }

                        if(!graspBag){
                            TakeshiHRI::say("I could not take any bag");
                            nextState=SM_START;
                        }
                        else
                            success=true;
                        break;
                        
                }

                ros::spinOnce();
                loop.sleep();

        }

}
