#pragma once
#include "ros/ros.h"

#include "pcl_conversions/pcl_conversions.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiHardware.h"
#include "tf_conversions/tf_eigen.h"
#include "vision_msgs/ObjectCoordinatesForDetection.h"

class TakeshiTasks
{
    private:
        static bool is_node_set;

    public:
        //
        //The startSomething functions, only publish the goal pose or path and return inmediately after starting movement
        //The others, block until a goal-reached signal is received
        //
        enum POSE{
            NONE,
            STANDING,
            SITTING,
            LYING
        };

        enum headPose{
            LATERAL,
            CENTERDOWN,
            LATERALUP,
            CENTER
        };

        enum followState{
          SM_GUIDING_MEMORIZING_OPERATOR_SAY,
          SM_GUIDING_MEMORIZING_OPERATOR_ELF,
          SM_GUIDING_MEMORIZING_OPERATOR,
          SM_GUIDING_PHASE,
          SM_GUIDING_STOP,
          SM_GUIDING_FINISHED,
          SM_WAIT_FOR_OPERATOR,
          SM_MEMORIZING_OPERATOR,
          SM_WAIT_FOR_LEGS_FOUND,
          SM_FOLLOWING_PHASE,
          SM_FOLLOWING_FINISHED
        };

        static bool _tasksStop;
        static ros::Subscriber subTasksStop;
        static void callbackTasksStop(const std_msgs::Empty::ConstPtr& msg);
        static bool tasksStop();

        static bool setNodeHandle(ros::NodeHandle* nh);
        static void printTakeshiTaskMessage(string message);
        static void printTakeshiTaskError(string message);
        //////////Vision Tasks/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool alignWithTable();
        static bool alignWithTable(float distToTable);
        static bool alignWithFrontTable();
        static bool alignWithFrontTable(float distToTable);
        static bool alignWithTable(float distToTable, bool inFront);
        //////////Manipulation Tasks////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool placeObject(float objectHeight = 0, float planeHeight=.77, bool inFront=false);
	static bool placeObjectLateralAtPoint(float x, float y, float z);
        static bool placeObjectInShelf(int pose, bool inFront=true);
        static bool placeObjectInShelfByCategory(string category);
        static bool placeObjectInColorBin(string color);
        static bool placeObjectAtHeight(float objectHeight, float planeHeight,bool inFront=true);
        static bool placeObjectInFront(float objectHeight = 0, float planeHeight=0.6);
        static bool graspObjectOnFloorFromAbove(vision_msgs::VisionObject detectedObject, float height, bool verify);
        static bool graspObjectOnFloorFromAbove(float x, float y, float z, float height, bool verify);
        static bool graspBagInFloor(string color,vision_msgs::ObjectCoordinatesForDetection& bagsCoordinates);
        static bool graspThePointingBag(int attempts=1);
        static bool graspObjectLateral(float x, float y, float z, bool verify, bool& fail);
        static bool graspObjectLateral(float x, float y, float z, bool verify);
    	static bool graspObjectLateralRight(float x, float y, float z, bool verify);
        static bool graspObjectLateral(std::string idObject, bool verify);
        static bool graspObjectOnTheFridge(float x, float y, float z, bool verify);
        static bool graspObjectOnTheFridge(std::string idObject, bool verify);
        static bool graspObject(std::string idObject, bool verify);
        static bool graspObject(float x, float y, float z, bool verify, bool& fail);
        static bool graspObject(float x, float y, float z, bool verify);
        static bool graspObjectOnFloor(float x, float y, float z, bool verify);
        static bool graspObjectOnPlane(std::string idObject, double planeHeight, bool verify);
        static bool graspObjectOnTheDrawer(std::string idObject, double planeHeight, bool verify);
        static bool graspYoloObject(std::vector<std::string> idObjects,std::vector<vision_msgs::VisionObject>& recognizedObjects,int attempts, int timeOut, bool verify, vision_msgs::ObjectCoordinatesForDetection objectCoordinates=TakeshiVision::objectCoordinates);

        //This is for grasp rope
        static bool graspRopeOnFloor(float x, float y, float z, bool verify);

        ///////////Gesture Skeleton Tasks//////////////////////////////////////////////////////////////////////////////////////////////////////
        static bool waitRecognizedGesture(std::vector<vision_msgs::GestureSkeleton> &gestures, float timeout);
        static bool waitForSpecificGesture(vision_msgs::GestureSkeleton &gestures, std::vector<std::string> specificGesture, float timeout);
        static bool findGesture(std::vector<vision_msgs::GestureSkeleton> gestures, std::vector<std::string> specifiGesture, int& indexGesture);

        static bool findObject(std::string idObject, geometry_msgs::Pose & pose);
        static bool findObject(std::string idObject, geometry_msgs::Pose & pose, headPose headpose);
        static bool findObjectAndLateralMove(std::string idObject, geometry_msgs::Pose & pose,headPose headpose);
        static bool findObjectOnPlane(std::string idObject, geometry_msgs::Pose & pose, headPose headpose, double planeHeight);
        static bool detectObjectsNtimes(std::vector<vision_msgs::VisionObject>& recoObjList, int times);
        static bool detectObjectsOnPlaneNtimes(std::vector<vision_msgs::VisionObject>& recoObjList, int times, double height);
        static bool giveObjectToHuman();
        static bool findPerson(std::string person = "", int gender = -1, POSE pose = NONE, bool recogByID = false);
        static bool findPersonFacenet(std::string name = "", float anghd=0.0, bool get_close=true);
        static bool findPersonLoc(std::string person = "", int gender = -1, POSE pose = NONE, bool recogByID = false,std::string location = "");
        static bool waitRecognizedFace(float timeout, std::string id, int gender, POSE pose, std::vector<vision_msgs::VisionFaceObject> &faces);
        static bool waitRecognizedFacenet(float timeout, std::string id, int gender, POSE pose, std::vector<vision_msgs::VisionFaceObject> &faces);
        static void closeToGoalWithDistanceTHR(float goalx, float goaly, float thr, float timeout);
        
        static bool getPanoramic(float initAngTil, float incAngTil, float maxAngTil, float initAngPan, float incAngPan, float maxAngPan, sensor_msgs::Image& image, float timeout);
        static bool guidePerson(std::string location, int timeOut_ms);
        static bool guidePersonFacenet(std::string location,std::string id, int timeOut_ms);
        static bool followAPerson(std::string stopRecog);
        static bool recognizeFace(int gender, POSE pose, float initAngPan, float incAngPan, float maxAngPan, float initAngTil, float incAngTil, float maxAngTil, Eigen::Vector3d &centroidFace, int &genderRecog);
        static bool trainObjectOnline(std::string objectName,std::string& object);
        static bool giveObject(float x, float y, float z);
        static bool takeHandle(float x, float y, float z, float & height, bool fridge);
        static bool moveHandle(float x, float y, float z, float & height);
        static bool openFridge();
        static bool closeFridge();
        static bool openDoor();
        static bool openShelfDoor();
        static bool openDrawer();
        static bool findObjectOnPlaneAndLateralMove(std::vector<vision_msgs::VisionObject>& recoObjList,  double height);
        static bool detectAllObjectsOnPlaneAndMove(std::vector<vision_msgs::VisionObject>& recoObjList, double height);
        static void sayAndAsyncNavigateToLoc(std::string location, bool say = true);
        static bool sayAndSyncNavigateToLoc(std::string location, int timeout, bool say = true);
        static bool findCrowd(int &man, int &woman, int &sitting, int &standing, int &lying, std::string location = "");
        static bool findTable(std::string &ss);
        static bool turnAndRecognizeGesture(std::string typeGesture, float initAngPan, float incAngPan, float maxAngPan, float initAngTil, float incAngTil, float maxAngTil, float incAngleTurn, float maxAngleTurn, float maxDistance, Eigen::Vector3d &gesturePos, std::string location);
        static bool turnAndRecognizeFacenet(std::string name, bool get_close=true);


    private:
        static bool getNearestRecognizedFace(std::vector<vision_msgs::VisionFaceObject> facesObject, float distanceMax, Eigen::Vector3d &centroidFace, int &genderRecog);
        static bool getNearestRecognizedFaceGPSR(std::vector<vision_msgs::VisionFaceObject> facesObject, float distanceMax, Eigen::Vector3d &centroidFace, int &genderRecog, std::string location);
        static bool turnAndRecognizeFace(std::string id, int gender, POSE pose, float initAngPan, float incAngPan,float maxAngPan, float initAngTil, float incAngTil, float maxAngTil,float incAngleTurn, float maxAngleTurn, Eigen::Vector3d &centroidFace, int &genderRecog);
        static bool turnAndRecognizeFaceGPSR(std::string id, int gender, POSE pose, float initAngPan, float incAngPan,float maxAngPan, float initAngTil, float incAngTil, float maxAngTil,float incAngleTurn, float maxAngleTurn, Eigen::Vector3d &centroidFace, int &genderRecog, std::string location);
        static bool getNearestRecognizedGesture(std::string typeGesture, std::vector<vision_msgs::GestureSkeleton> gestures, float distanceMax, Eigen::Vector3d &nearestGesture, std::string location);
        static std::vector<vision_msgs::VisionFaceObject> recognizeAllFaces(float timeOut, bool &recognized);
};
