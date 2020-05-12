#pragma once
#include "ros/ros.h"
#include "vision_msgs/VisionFaceObjects.h"
#include "vision_msgs/FaceRecognition.h"
#include "vision_msgs/Yolov3_detector.h"
#include "std_msgs/Empty.h"
#include "std_msgs/Bool.h"
#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>

#include "vision_msgs/Skeletons.h"
#include "vision_msgs/Skeleton.h"

#include "vision_msgs/GestureSkeletons.h"
#include "vision_msgs/HandSkeletonPos.h"
#include "vision_msgs/GetFacesFromImage.h"
#include "vision_msgs/DetectObjects.h"
#include "vision_msgs/DetectObjectsInPlane.h"
#include "vision_msgs/VisionFlattenedObjectList.h"
#include "vision_msgs/RecognizeFlattenedObjects.h"
#include "vision_msgs/ObjectCoordinatesForDetection.h"

#include "point_cloud_manager/GetRgbd.h"
#include "vision_msgs/FindLines.h"
#include "vision_msgs/FindLines.h"
#include "vision_msgs/FindPlane.h"
#include "vision_msgs/FindPlaneAtHeight.h"
#include "vision_msgs/TrainObject.h"
#include "vision_msgs/DetectHandles.h"

#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PointStamped.h"

#include "takeshi_tools/TakeshiTools.h"

#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/BoundingBox.h>

using namespace std;

class TakeshiVision
{
private:

static bool is_node_set;
static bool _isObjectTrained;
//Members for operating face recognizer
//Service for face recognition
static ros::ServiceClient cltGetFaces;
//yolov3 detection
static ros::ServiceClient cltDetectAllYoloObjects;
static ros::ServiceClient cltDetectAllYoloObjectsWithArmCamera;
//Members for operating pano maker
static ros::Publisher pubTakePanoMaker;
static ros::Publisher pubClearPanoMaker;
static ros::Publisher pubMakePanoMaker;
static ros::Subscriber subPanoImage;
//Train Object status
static ros::Subscriber subIsObjectTrained;

static sensor_msgs::Image lastImage;
static bool panoImageRecived;
static ros::ServiceClient cltPanoFaceReco;
//Members for operating face recognizer
static ros::Publisher pubFacStopRecog;
static ros::Publisher pubRecFace;
static ros::Publisher pubRecFaceByID;
static std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
//Members for operating skeleton finder
static ros::Publisher pubSktEnableRecog;
static ros::Subscriber subGestures;
static ros::Subscriber subSkeletons;
static ros::Subscriber subLeftHandPositions;
static ros::Subscriber subRightHandPositions;
static std::vector<vision_msgs::Skeleton> lastSkeletons;
static std::vector<vision_msgs::GestureSkeleton> lastGestureRecog;
static std::vector<geometry_msgs::Point> lastLeftHandPos;
static std::vector<geometry_msgs::Point> lastRightHandPos;
//Members for operating face recognizer
static ros::Publisher pubFacStartRecog;
static ros::Publisher pubFacStartRecogOld;
//Services for getting point cloud
static ros::ServiceClient cltGetRgbdWrtRobot;
//Sevices for line finding
static ros::ServiceClient cltFindLines;
//Service for find plane
static ros::ServiceClient cltFindPlane;
//Service for find vacant plane
static ros::ServiceClient cltFindVacantPlane;
static ros::ServiceClient cltFindVacantPlaneAtHeight;
//Recog objects
static ros::ServiceClient cltDetectObjects;
static ros::ServiceClient cltDetectAllObjects;
static ros::ServiceClient cltDetectObjectsFloor;
static ros::ServiceClient cltDetectAllObjectsFloor;
static ros::ServiceClient cltDetectObjectsOnPlane;
static ros::ServiceClient cltDetectAllObjectsOnPlane;
static ros::ServiceClient srvTrainObject;
static ros::Publisher pubLoadTrainDir;
static ros::Publisher pubLoadSpecificTrainingDir;

//Arm camera
static bool is_arm_image;
static sensor_msgs::Image armCameraImage;
static ros::Subscriber subArmCamera;

//For what else? YOLO on darknet!!!
static ros::ServiceClient cltRgbdRobot;
//For openposes
static ros::Publisher pubEnableOpenposes;
//For facenet
static ros::ServiceClient cltDetectFaceNet;
static ros::ServiceClient cltRecognizeFaceNet;
static ros::ServiceClient cltTrainFaceNet;

//QR reader variables
static std::string QRString;
static ros::Publisher pubQRReaderStart;
static ros::Subscriber subQRReaded;

//For handlke detection
static ros::ServiceClient srvDetectHandles;

//Flat detector
static ros::ServiceClient cltFlattenedSeg;

public:
static bool setNodeHandle(ros::NodeHandle* nh);
static void printTakeshiMessage(string message);
static void printTakeshiError(string message);

//Yolo Methods
static bool detectAllYoloObjects(std::vector<vision_msgs::VisionObject>& recognizedYoloObjects, int timeOut_ms,vision_msgs::ObjectCoordinatesForDetection objectCoordinates=TakeshiVision::objectCoordinates);
static bool detectAllYoloObjectsWithArmCamera(std::vector<vision_msgs::VisionObject>& recognizedYoloObjects, int timeOut_ms);
static bool detectYoloObject(std::string objectName,vision_msgs::VisionObject& recognizedYoloObject, int timeOut_ms, vision_msgs::ObjectCoordinatesForDetection objectCoordinates=TakeshiVision::objectCoordinates);
static bool detectSpecificYoloObject(std::vector<std::string> objectsName,std::vector<vision_msgs::VisionObject>& specificYoloObjects,int timeOut_ms,vision_msgs::ObjectCoordinatesForDetection objectCoordinates=TakeshiVision::objectCoordinates);
static cv::Scalar getColorBoundingBoxes(std::string category);
static bool detectSpecificYoloObjectsCategories(std::vector<std::string> objectsName);
static bool detectAllYoloObjectsCategories();
static bool detectYoloObjectsCategories(std::vector<std::string> objectsName,bool allObjects);
static bool object_is_graspeable(cv::Vec3f centroid_3d, vision_msgs::ObjectCoordinatesForDetection object_coordinates);
static bool object_is_graspeable(float x, float y, float z, vision_msgs::ObjectCoordinatesForDetection object_coordinates);
static std::string getJesusObjectCategory(std::string object);
//arm image
static bool detectCircles(vision_msgs::VisionObject& object);


//Methods for pano maker
static void takePano();
static void clearPano();
static void makePano();
static bool isPanoImageRecived();
static sensor_msgs::Image getLastPanoImage();

//Methods for operating face recognizer
static void stopFaceRecognition();
static void facRecognize();
static void facRecognize(std::string id);
static bool getLastRecognizedFaces(std::vector<vision_msgs::VisionFaceObject>& faces);
//Methods for operating face recognizer
static void startFaceRecognition();
static void startFaceRecognitionOld();
static vision_msgs::VisionFaceObjects getRecogFromPano(sensor_msgs::Image image);
// this is justina implementation.
// Is strongly recommend replace it whit FaceNet function
static void facTrain(std::string id);
static void facTrain(std::string id, int numOfFrames);
static void facClearByID(std::string id);
static void facClearAll();

  
//Methods for operating skeleton finder
static void startSkeletonFinding();
static void getLastGesturesRecognize(std::vector<vision_msgs::GestureSkeleton> &gestures);
static void stopSkeletonFinding();

static vision_msgs::VisionFaceObjects getFaces(std::string id);

//Methods for the qr reader
static void startQRReader();
static void stopQRReader();
static bool read_QR(std::string &out_string);

//Methods for line finding
static bool findLine(float& x1, float& y1, float& z1, float& x2, float& y2, float& z2);
//Methods for plane findinig
static bool findPlane();
//Methods for plan vacant finding
static bool findVacantPlane(std::vector<float>& vacantPlane, std::vector<int>& inliersOnPlane, bool inFront=false);
static bool findVacantPlaneAtHeight(std::vector<float>& vacantPlane,
                                    std::vector<int>& inliersOnPlane,
                                    double minHeight, double maxHeight);
//Method for arm camera
static sensor_msgs::Image getArmImage();
//Methods for calculating inverse kinematics
//static bool inverseKinematicsGeometric(std::vector<float>& cartesian, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction);      // Takeshi


//Methods for object detector and Recognizer
static bool detectObjects(std::vector<vision_msgs::VisionObject>& recoObjList, bool saveFiles = false);
static bool detectAllObjects(std::vector<vision_msgs::VisionObject>& recoObjList, bool saveFiles = false);
static bool detectObjectsFloor(std::vector<vision_msgs::VisionObject>& recoObjList, bool saveFiles = false);
static bool detectAllObjectsFloor(std::vector<vision_msgs::VisionObject>& recoObjList, bool saveFiles = false);
static bool detectObjectsOnPlane(std::vector<vision_msgs::VisionObject>& recoObjList,double planeHeight);
static bool detectAllObjectsOnPlane(std::vector<vision_msgs::VisionObject>& recoObjList,double planeHeight);
//Methods for color detector
static bool detectObjectByColor(string color,vision_msgs::VisionObject& object, bool bag=false);

static bool getImagesFromTakeshi( cv::Mat& imaBGR, cv::Mat& imaPCL);

static bool getHandles(std::vector<geometry_msgs::Point> &handles);
static void trainObject(const std::string name);
static bool isObjectTrained();
static bool loadObjectTrainDir();
static bool loadSpecificTrainingDir(std::string dir);
static bool getSkeletons(vision_msgs::Skeletons &skl, float timeOut);
static bool getWrist(geometry_msgs :: PointStamped &wrist, bool right=true);
static bool getBothWrists(geometry_msgs :: PointStamped &left_wrist,
                          geometry_msgs::PointStamped &right_wrist);

static bool getArm(
        std::vector<geometry_msgs :: PointStamped> &arm,
        bool right=true );
static double  distanceToPerson(vision_msgs::Skeleton person);
static int getClosestSkeleton(std::vector< vision_msgs::Skeleton> &esqueletos);
//Facenet functions:
// Facenet Detect was meant to use facenet as a face detector, but honestly it is not
//Worth it, there are cheaper methods
//static bool facenetDetect(std::vector<vision_msgs::VisionFaceObject>& faces);
static vision_msgs::VisionFaceObjects facenetRecognize(std::string id="");
static bool facenetTrain(std::string id);

static vision_msgs::ObjectCoordinatesForDetection objectCoordinates;


private:
//callbacks for pano maker
static void callbackPanoRecived(const sensor_msgs::Image msg);
//callbacks for skeleton recognition
static void callbackSkeletons(const vision_msgs::Skeletons::ConstPtr& msg);
static void callbackGestures(const vision_msgs::GestureSkeletons::ConstPtr& msg);
static void callbackLeftHandPositions(const vision_msgs::HandSkeletonPos leftHandPositions);
static void callbackRightHandPositions(const vision_msgs::HandSkeletonPos rightHandPositions);
//callbacks for face recognition
static void callbackFaces(const vision_msgs::VisionFaceObjects::ConstPtr& msg);
static void callbackIsObjectTrained(const std_msgs::Bool::ConstPtr& msg);
//callbacks for QR reader
static void callbackRead_QR(const std_msgs::String::ConstPtr &msg);
//callbacks for arm image
static void callbackArmCameraImage(const sensor_msgs::Image msg);

bool detectFlattenedObjects(vision_msgs::VisionFlattenedObjectList& recoObjList,
                            bool saveFiles);

};
