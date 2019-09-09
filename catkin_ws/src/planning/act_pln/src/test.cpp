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
        while(ros::ok() && !success) {

                switch(nextState) {

                case SM_START:
                //TakeshiVision::detectAllYoloObjects(recognizedYoloObjects, 1000);
                TakeshiVision::detectObjectByColor("green", recognizedYoloObject,false);
                
                /*vfo = TakeshiVision::facenetRecognize("train_charlie");
                vfo = TakeshiVision::facenetRecognize("train_charlie");
                vfo = TakeshiVision::facenetRecognize("train_charlie");
                vfo = TakeshiVision::facenetRecognize("train_charlie");
                vfo = TakeshiVision::facenetRecognize("train_charlie");
                vfo = TakeshiVision::facenetRecognize("train_charlie");
                vfo = TakeshiVision::facenetRecognize("train_charlie");
                vfo = TakeshiVision::facenetRecognize("train_charlie");*/

                //if(TakeshiTasks::turnAndRecognizeGesture("waving", 0, 0, 0, -0.2f, -0.2f, -0.2f, 0.0f, 0.0f, 9.0, centroidGesture, ""))
                  //  cout << "hola" << endl;

/*
ros::Duration(2).sleep();
        TakeshiVision::startSkeletonFinding();


                if(!TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000))
                if(!TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000))
                        TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000);

            if(gesture.gesture.size() > 0) {
                if(gesture.gesture.compare("right_hand_rised")==0 || gesture.gesture.compare("right_waving")==0) {
                        TakeshiHRI::say("waving right");
                       ros::Duration(1.0).sleep();
                TakeshiVision::stopSkeletonFinding();
                ros::Duration(1.0).sleep();

                TakeshiTools::transformPoint("/base_link", gesture.gesture_centroid.x,gesture.gesture_centroid.y ,gesture.gesture_centroid.z, "/map", gx_w, gy_w, gz_w);
                TakeshiTasks::closeToGoalWithDistanceTHR(gx_w, gy_w, 1.5, 120000);
                dist_to_head = sqrt( pow(gx_w, 2) + pow(gy_w, 2));
                TakeshiKnowledge::getRobotPose(robot_x, robot_y, robot_a);
                // TakeshiManip::startHdGoTo(atan2(gy_w, gx_w) - robot_a, atan2(gz_w - 1.6, dist_to_head)); 
                TakeshiManip::startHdGoTo(0, atan2(gz_w - 1.6, dist_to_head));

                TakeshiKnowledge::addUpdateKnownLoc("table_1", robot_a);
              
                        }
                else if(gesture.gesture.compare("left_hand_rised")==0 || gesture.gesture.compare("left_waving")==0) {
                        TakeshiHRI::say("waving left");
              ros::Duration(1.0).sleep();
                TakeshiVision::stopSkeletonFinding();
                ros::Duration(1.0).sleep();

                TakeshiTools::transformPoint("/base_link", gesture.gesture_centroid.x,gesture.gesture_centroid.y ,gesture.gesture_centroid.z, "/map", gx_w, gy_w, gz_w);
                TakeshiTasks::closeToGoalWithDistanceTHR(gx_w, gy_w, 1.5, 120000);
                dist_to_head = sqrt( pow(gx_w, 2) + pow(gy_w, 2));
                TakeshiKnowledge::getRobotPose(robot_x, robot_y, robot_a);
                // TakeshiManip::startHdGoTo(atan2(gy_w, gx_w) - robot_a, atan2(gz_w - 1.6, dist_to_head)); 
                TakeshiManip::startHdGoTo(0, atan2(gz_w - 1.6, dist_to_head));

                TakeshiKnowledge::addUpdateKnownLoc("table_1", robot_a);
                       

                        }

                
        }

                ros::Duration(1.0).sleep();
                TakeshiVision::stopSkeletonFinding();
                ros::Duration(1.0).sleep();

                //TakeshiTasks::giveObjectToHuman();
//                        TakeshiTasks::guidePersonFacenet("trial","hugo",3000);
                       //TakeshiTasks::alignWithFrontTable();
                        //TakeshiTasks::giveObjectToHuman();}
                       //TakeshiVision::detectAllYoloObjectsCategories();
                       //TakeshiManip::findObjectsPose(false, false,4000);
                       //TakeshiVision::detectAllYoloObjects(recognizedYoloObjects, 1000);
               // TakeshiHRI::playSound();
               // TakeshiVision::detectObjectByColor("yellow",centroid3D,true);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /*
                        TakeshiVision::startSkeletonFinding();
                           ros::Duration(1.0).sleep();
                       if(TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000)) {
                                if(gesture.gesture.compare("right_hand_rised")==0)
                                        TakeshiHRI::waitAfterSay("right hand rised",3000);
                                if(gesture.gesture.compare("left_hand_rised")==0)
                                        TakeshiHRI::waitAfterSay("left hand rised",3000);
                                
                                //nextState=3;
                        }
                       
                       TakeshiVision::stopSkeletonFinding();
                                ros::Duration(1.0).sleep();
                        ros::spinOnce();

                        */

   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////             
                        //success=true;
                        //nextState=SM_INSTRUCTIONS;
                                        //TakeshiTasks::openDoor();
                        //TakeshiHRI::say(takeshi_say.str() );
                        //TakeshiManip::armGoToGraspBag();
                        //idobject.push_back("apple_juice");
                        //bool fail;
                        //bagsCoordinates=TakeshiVision::objectCoordinates;
                        //TakeshiVision::detectObjectByColor("brown",object,true);
                        //TakeshiTasks::graspThePointingBag(3);

                        //bagsCoordinates.x_min=-10.0;
                        //TakeshiTasks::graspYoloObject(hola,recognizedYoloObjects,3,2000,true,bagsCoordinates);
                        //TakeshiTasks::alignWithTable();
                        //TakeshiVision::detectAllYoloObjects(recognizedYoloObjects,1000,bagsCoordinates);
                        //TakeshiHRI::waitAfterSay(recognizedYoloObjects[0].category,2000);
                        //TakeshiManip::hdGoTo(0.0,0.0,2000);
                        //TakeshiTasks::graspObjectOnFloor(recognizedYoloObjects[0].pose.position.x, recognizedYoloObjects[0].pose.position.y, recognizedYoloObjects[0].pose.position.z, false);
                        //TakeshiTasks::graspObjectLateral(recognizedYoloObjects[0].pose.position.x,recognizedYoloObjects[0].pose.position.y,recognizedYoloObjects[0].pose.position.z, true, fail);
                        //if(TakeshiVision::detectAllYoloObjects(recognizedYoloObjects,1000))

                        //TakeshiTasks::graspObject(recognizedYoloObjects[0].pose.position.x,recognizedYoloObjects[0].pose.position.y,recognizedYoloObjects[0].pose.position.z, false);
                        //ros::Duration(2).sleep();
                        //TakeshiManip::hdGoTo(0.0, -0.8, 1000);
/*
                        bagsCoordinates=TakeshiVision::objectCoordinates;
                        cout << bagsCoordinates.x_min << endl;
                        cout << bagsCoordinates.x_max << endl;
                        cout << bagsCoordinates.y_min << endl;
                        cout << bagsCoordinates.y_max << endl;
                        cout << bagsCoordinates.z_min << endl;
                        cout << bagsCoordinates.z_max << endl;
                        
                        TakeshiTasks::graspThePointingBag(3);
*/
/*
                TakeshiTasks::alignWithTable();

                TakeshiVision::detectAllObjects(recognizedYoloObjects, false);

                TakeshiManip::hdGoTo(1.5707, 0.0, 6000);
      TakeshiManip::hdGoTo(0.0, 0.0, 6000);
                TakeshiTasks::graspObjectLateral(recognizedYoloObjects[0].pose.position.x,recognizedYoloObjects[0].pose.position.y, recognizedYoloObjects[0].pose.position.z, false);
      


                ///TakeshiTasks::graspThePointingBag(3);
                        //TakeshiTasks::alignWithFrontTable();
                       //TakeshiVision::detectObjectByColor("yellow", recognizedYoloObject,true);
                        //TakeshiHRI::waitAfterSay("I found you, when we get to the car tell me, here is the car, or, stop follow me. For confirmation tell me, takeshi yes, or, takeshi no",1000);
                        //ros::Duration(0.1).sleep();
                        //ros::Duration(1).sleep();
			           //TakeshiTasks::alignWithFrontTable();
                       //TakeshiTasks::placeObjectInFront(0.0,0.8);
                        //if(TakeshiVision::detectAllYoloObjects(recognizedYoloObjects,1000)){
                        //if(TakeshiVision::detectSpecificYoloObject(specificYoloObjects,recognizedYoloObjects,0.3,1000))

                        //for(int i=0; i<recognizedYoloObjects.size();i++)
                          //  cout << recognizedYoloObjects[i].id << endl;
                          //  TakeshiManip::hdGoTo(0.0, 0.0, 1000);
                        //    nextState=SM_INSTRUCTIONS;   
                        //}
                        //55,17
                        //TakeshiTasks::graspBagInFloor("blue");
                            //nextState=SM_INSTRUCTIONS;*/
                        

                        //ros::Duration(10).sleep();
                        //cout << centroid3D.val[0] << endl;
                        //cout << centroid3D.val[1] << endl;
                        //cout << centroid3D.val[2] << endl;
                        //imshow("BGR", BGR);
                        //imshow("PCL", PCL);
                        //waitKey(0);
  //                      success=true;
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
