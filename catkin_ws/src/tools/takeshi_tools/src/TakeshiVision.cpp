#include "takeshi_tools/TakeshiVision.h"

bool TakeshiVision::is_node_set = false;
bool TakeshiVision::_isObjectTrained = false;
bool callbackObjectTrained =false;
//color segmentation
//Come on we really need to hardcode this? Here of all places?
//who are you?
std::vector<int> HSV_blueBin = {101,87,60,116,255,255};
std::vector<int> HSV_yellowBin = {12,115,98,23,255,251};
std::vector<int> HSV_redBin = {165,140,91,181,255,230};
std::vector<int> HSV_greenBin = {39,104,92,64,255,255};
std::vector<int> HSV_yellowBag = {22,205,155,32,255,255};
std::vector<int> HSV_blueBag = {110,135,78,142,255,197};
std::vector<int> HSV_brownBag = {10,70,100,27,140,162};

bool debug_hsv_segmentation=false;
int hsv_max = 255;

std::vector<int> HSV = {0,0,0,255,255,255};
std::vector<cv::Scalar> colors={cv::Scalar(255,0,0),cv::Scalar(0,255,0),cv::Scalar(0,0,255),cv::Scalar(0,255,255),cv::Scalar(255,255,0),cv::Scalar(255,0,255)};
std::vector<std::string> categories={};
vision_msgs::ObjectCoordinatesForDetection TakeshiVision::objectCoordinates;


//Service for face recognition
ros::ServiceClient TakeshiVision::cltGetFaces;

//Service for yolov3 detection
ros::ServiceClient TakeshiVision::cltDetectAllYoloObjects;
ros::ServiceClient TakeshiVision::cltDetectAllYoloObjectsWithArmCamera;

//Members for operating skeleton finder
ros::Publisher TakeshiVision::pubSktEnableRecog;
ros::Subscriber TakeshiVision::subGestures;
ros::Subscriber TakeshiVision::subSkeletons;
ros::Subscriber TakeshiVision::subLeftHandPositions;
ros::Subscriber TakeshiVision::subRightHandPositions;

//Members for trained objects
ros::Subscriber TakeshiVision::subIsObjectTrained;

std::vector<vision_msgs::Skeleton> TakeshiVision::lastSkeletons;
std::vector<vision_msgs::GestureSkeleton> TakeshiVision::lastGestureRecog;
std::vector<geometry_msgs::Point> TakeshiVision::lastLeftHandPos;
std::vector<geometry_msgs::Point> TakeshiVision::lastRightHandPos;

//Members for operating pano maker
ros::Publisher TakeshiVision::pubTakePanoMaker;
ros::Publisher TakeshiVision::pubClearPanoMaker;
ros::Publisher TakeshiVision::pubMakePanoMaker;
ros::Subscriber TakeshiVision::subPanoImage;
sensor_msgs::Image TakeshiVision::lastImage;
bool TakeshiVision::panoImageRecived;
ros::ServiceClient TakeshiVision::cltPanoFaceReco;
//Members for operating face recognizer
std::vector<vision_msgs::VisionFaceObject> TakeshiVision::lastRecognizedFaces;
ros::Publisher TakeshiVision::pubFacStartRecog;
ros::Publisher TakeshiVision::pubFacStartRecogOld;
ros::Publisher TakeshiVision::pubFacStopRecog;
ros::Publisher TakeshiVision::pubRecFaceByID;
ros::Publisher TakeshiVision::pubRecFace;
//Members for facenet, we really ougth to order all this don't you think?
ros::ServiceClient TakeshiVision::cltDetectFaceNet;
ros::ServiceClient TakeshiVision::cltRecognizeFaceNet;
ros::ServiceClient TakeshiVision::cltTrainFaceNet;

//Members for operation of qr reader
ros::Publisher TakeshiVision::pubQRReaderStart;
ros::Subscriber TakeshiVision::subQRReaded;
std::string TakeshiVision::QRString="";


//Services for getting point cloud
ros::ServiceClient TakeshiVision::cltGetRgbdWrtRobot;
//Sevices for line finding
ros::ServiceClient TakeshiVision::cltFindLines;
//Sevices for finding a plane
ros::ServiceClient TakeshiVision::cltFindPlane;
//Service for find vacant plane
ros::ServiceClient TakeshiVision::cltFindVacantPlane;
ros::ServiceClient TakeshiVision::cltFindVacantPlaneAtHeight;
//Detect objects
ros::ServiceClient TakeshiVision::cltDetectObjects;
ros::ServiceClient TakeshiVision::cltDetectAllObjects;
ros::ServiceClient TakeshiVision::srvTrainObject;
ros::ServiceClient TakeshiVision::cltDetectObjectsFloor;
ros::ServiceClient TakeshiVision::cltDetectAllObjectsFloor;
ros::ServiceClient TakeshiVision::cltDetectObjectsOnPlane;
ros::ServiceClient TakeshiVision::cltDetectAllObjectsOnPlane;
ros::Publisher TakeshiVision::pubLoadTrainDir;
ros::Publisher TakeshiVision::pubLoadSpecificTrainingDir;


ros::ServiceClient TakeshiVision::cltRgbdRobot;
//For openposes
ros::Publisher TakeshiVision::pubEnableOpenposes;
//For get handles
//I like tamales
ros::ServiceClient TakeshiVision::srvDetectHandles;
//For flat obj detector:
ros::ServiceClient TakeshiVision::cltFlattenedSeg;
//Arm Image
bool TakeshiVision::is_arm_image=false;
sensor_msgs::Image TakeshiVision::armCameraImage;
ros::Subscriber TakeshiVision::subArmCamera;

bool TakeshiVision::setNodeHandle(ros::NodeHandle* nh)
{
        if(TakeshiVision::is_node_set)
                return true;
        if(nh == 0)
                return false;

        cout << "\033[1;34m     TakeshiVision.->Setting ros node...\033[0m" << endl;
        //Members for operating face recognizer
        TakeshiVision::cltGetFaces = nh->serviceClient<vision_msgs::FaceRecognition>("/vision/face_recognizer/face_recognition");
        TakeshiVision::pubFacStopRecog = nh->advertise<std_msgs::Empty>("/vision/face_recognizer/stop_recog", 1);
        TakeshiVision::pubRecFace = nh->advertise<std_msgs::Empty>("/vision/face_recognizer/run_face_recognizer", 1);
        TakeshiVision::pubRecFaceByID = nh->advertise<std_msgs::String>("/vision/face_recognizer/run_face_recognizer_id", 1);

        //Members for yolo detection
        TakeshiVision::cltDetectAllYoloObjects = nh->serviceClient<vision_msgs::Yolov3_detector>("/vision/yolov3_detector/detect_all_yolo_objects");
        TakeshiVision::cltDetectAllYoloObjectsWithArmCamera = nh->serviceClient<vision_msgs::Yolov3_detector>("/vision/yolov3_detector/detect_all_yolo_objects_with_arm_camera");

        //Members for operating skeleton finder
        TakeshiVision::pubSktEnableRecog = nh->advertise<std_msgs::Bool>("/vision/skeleton_finder/enable_tracking", 1);
        TakeshiVision::subGestures = nh->subscribe("/vision/gesture_recog_skeleton/gesture_recog", 1, &TakeshiVision::callbackGestures);
        TakeshiVision::subSkeletons = nh->subscribe("/vision/skeleton_finder/skeleton_recog", 1, &TakeshiVision::callbackSkeletons);
        TakeshiVision::subLeftHandPositions = nh->subscribe("/vision/gesture_recog_skeleton/left_hand_pos", 1, &TakeshiVision::callbackLeftHandPositions);
        TakeshiVision::subRightHandPositions = nh->subscribe("/vision/gesture_recog_skeleton/right_hand_pos", 1, &TakeshiVision::callbackRightHandPositions);

        //Member for trained object
        TakeshiVision::subIsObjectTrained = nh->subscribe("/vision/obj_reco/trainStatus", 1, &TakeshiVision::callbackIsObjectTrained);
        TakeshiVision::pubLoadTrainDir = nh->advertise<std_msgs::Bool>("/vision/obj_reco/loadTrainingDir", 1);
        TakeshiVision::pubLoadSpecificTrainingDir = nh->advertise<std_msgs::String>("/vision/obj_reco/loadSpecificTrainingDir", 1);

        //Members for operating pano maker
        TakeshiVision::pubTakePanoMaker = nh->advertise<std_msgs::Empty>("/vision/pano_maker/take_image", 1);
        TakeshiVision::pubClearPanoMaker = nh->advertise<std_msgs::Empty>("/vision/pano_maker/clear_images", 1);
        TakeshiVision::pubMakePanoMaker = nh->advertise<std_msgs::Empty>("/vision/pano_maker/make_panoramic", 1);
        TakeshiVision::subPanoImage = nh->subscribe("/vision/pano_maker/panoramic_image", 1, &callbackPanoRecived);
        TakeshiVision::panoImageRecived = false;
        TakeshiVision::cltPanoFaceReco = nh->serviceClient<vision_msgs::GetFacesFromImage>("/vision/face_recognizer/detect_faces");
        //Members for operation of qr reader
        TakeshiVision::pubQRReaderStart = nh->advertise<std_msgs::Bool>("/vision/qr/start_qr", 1);
        TakeshiVision::subQRReaded=nh->subscribe("/hri/qr/recognized", 1, &callbackRead_QR);

        //Services for getting point cloud
        TakeshiVision::cltGetRgbdWrtRobot = nh->serviceClient<point_cloud_manager::GetRgbd>("/hardware/point_cloud_man/get_rgbd_wrt_robot");
        //Sevices for line finding
        TakeshiVision::cltFindLines = nh->serviceClient<vision_msgs::FindLines>("/vision/line_finder/find_lines_ransac");

        //Members for operating face recognizer
        TakeshiVision::pubFacStartRecog = nh->advertise<std_msgs::Empty>("/vision/face_recognizer/start_recog", 1);
        TakeshiVision::pubFacStartRecogOld = nh->advertise<std_msgs::Empty>("/vision/face_recognizer/start_recog_old", 1);
        //For Facenet
        TakeshiVision::cltRecognizeFaceNet =
                nh->serviceClient<vision_msgs::FaceRecognition>("/vision/facenet_recognizer/faces");
        TakeshiVision::cltTrainFaceNet =
                nh->serviceClient<vision_msgs::FaceRecognition>("/vision/facenet_recognizer/train_face");
        //Service for find plane
        TakeshiVision::cltFindPlane = nh->serviceClient<vision_msgs::FindPlane>("/vision/geometry_finder/findPlane");
        //Service for find vacant plane
        TakeshiVision::cltFindVacantPlane = nh->serviceClient<vision_msgs::FindPlane>("/vision/geometry_finder/vacantPlane");
        TakeshiVision::cltFindVacantPlaneAtHeight = nh->serviceClient<vision_msgs::FindPlaneAtHeight>("/vision/geometry_finder/vacantPlaneAtHeight");
        //Detect objects
        TakeshiVision::cltDetectObjects         = nh->serviceClient<vision_msgs::DetectObjects>("/vision/obj_reco/det_objs");
        TakeshiVision::cltDetectAllObjects      = nh->serviceClient<vision_msgs::DetectObjects>("/vision/obj_reco/det_all_objs");
        TakeshiVision::cltDetectObjectsFloor    = nh->serviceClient<vision_msgs::DetectObjects>("/vision/obj_reco/det_objs_floor");
        TakeshiVision::cltDetectAllObjectsFloor = nh->serviceClient<vision_msgs::DetectObjects>("/vision/obj_reco/det_all_objs_floor");
        TakeshiVision::cltDetectObjectsOnPlane    = nh->serviceClient<vision_msgs::DetectObjectsInPlane>("/vision/obj_reco/det_objs_plane");
        TakeshiVision::cltDetectAllObjectsOnPlane = nh->serviceClient<vision_msgs::DetectObjectsInPlane>("/vision/obj_reco/det_all_objs_plane");

        TakeshiVision::cltRgbdRobot = nh->serviceClient<point_cloud_manager::GetRgbd>("/hardware/point_cloud_man/get_rgbd_wrt_robot");

        //Flat detection
        TakeshiVision::cltFlattenedSeg = nh->serviceClient<vision_msgs::RecognizeFlattenedObjects>("/vision/obj_reco/flattened_object");
        TakeshiVision::srvTrainObject  = nh->serviceClient<vision_msgs::TrainObject>("/vision/obj_reco/trainObject");

        //Arm camera
        TakeshiVision::subArmCamera = nh->subscribe("/hardware/arm/arm_camera",1,&TakeshiVision::callbackArmCameraImage);

        //For handle detection
        TakeshiVision::srvDetectHandles =
                nh->serviceClient<vision_msgs::DetectHandles>("/vision/handle_detector/detect_handles");
        TakeshiTools::setNodeHandle(nh);
        TakeshiVision::objectCoordinates.x_min=-1.0;
        TakeshiVision::objectCoordinates.x_max=2.0;
        TakeshiVision::objectCoordinates.y_min=-1.0;
        TakeshiVision::objectCoordinates.y_max=1.0;
        TakeshiVision::objectCoordinates.z_min=0.0;
        TakeshiVision::objectCoordinates.z_max=2.0;

        TakeshiVision::is_node_set=true;
        return true;
}

void TakeshiVision::printTakeshiMessage(std::string message){
        cout << "\033[1;34m     TakeshiVision.->"<< message <<"\033[0m" << endl;
}

void TakeshiVision::printTakeshiError(string message){
        cout << "\033[1;31m     TakeshiVision.->"<< message <<"\033[0m" << endl;
}

void trackbar_hh( int, void* ){}
void trackbar_hl( int, void* ){}
void trackbar_sh( int, void* ){}
void trackbar_sl( int, void* ){}
void trackbar_vh( int, void* ){}
void trackbar_vl( int, void* ){}

//##################################################################//
// Please, for software good practices put the callbacks functions  //
//                       HERE                                       //
//              callbacks  functions                                //

void TakeshiVision::callbackGestures(const vision_msgs::GestureSkeletons::ConstPtr& msg){
        TakeshiVision::lastGestureRecog.clear();
        for(int i = 0; i < msg->recog_gestures.size(); i++)
                TakeshiVision::lastGestureRecog.push_back(msg->recog_gestures[i]);
}

//callbacks for pano maker
void TakeshiVision::callbackPanoRecived(const sensor_msgs::Image msg){
        TakeshiVision::panoImageRecived = true;
        TakeshiVision::lastImage = msg;
}

//calbacks for the skeletons and gestures
void TakeshiVision::callbackSkeletons(const vision_msgs::Skeletons::ConstPtr& msg){
        TakeshiVision::lastSkeletons.clear();
        for(int i = 0; i < msg->skeletons.size(); i++)
                TakeshiVision::lastSkeletons.push_back(msg->skeletons[i]);
}

void TakeshiVision::callbackLeftHandPositions(const vision_msgs::HandSkeletonPos leftHandPositions){
        TakeshiVision::lastLeftHandPos.clear();
        for(int i = 0; i < leftHandPositions.hands_position.size(); i++)
                TakeshiVision::lastLeftHandPos.push_back(leftHandPositions.hands_position[i]);
}

void TakeshiVision::callbackRightHandPositions(const vision_msgs::HandSkeletonPos rightHandPositions){
        TakeshiVision::lastRightHandPos.clear();
        for(int i = 0; i < rightHandPositions.hands_position.size(); i++)
                TakeshiVision::lastRightHandPos.push_back(rightHandPositions.hands_position[i]);
}

void TakeshiVision::callbackFaces(const vision_msgs::VisionFaceObjects::ConstPtr& msg)
{
        TakeshiVision::lastRecognizedFaces = msg->recog_faces;
}

void TakeshiVision::callbackRead_QR(const std_msgs::String::ConstPtr &msg)
{
        TakeshiVision::QRString=msg->data;
}

void TakeshiVision::callbackIsObjectTrained(const std_msgs::Bool::ConstPtr& msg)
{
        TakeshiVision::_isObjectTrained=msg->data;
        callbackObjectTrained=true;
}

void TakeshiVision::callbackArmCameraImage(const sensor_msgs::Image msg)
{
        TakeshiVision::armCameraImage=msg;
        TakeshiVision::is_arm_image=true;
}
//#####################  END  CALLBACKS ZONE    ######################//


std::string TakeshiVision::getJesusObjectCategory(std::string object){}

cv::Scalar TakeshiVision::getColorBoundingBoxes(std::string category){
        bool found=false;
        cv::Scalar color;
        int i=0;
        for(i=0;i<categories.size();i++)
                if(categories[i].compare(category)==0)
                        return colors[i];
        categories.push_back(category);
        return colors[i];
}

bool TakeshiVision::detectSpecificYoloObjectsCategories(std::vector<std::string> objectsName){
        return TakeshiVision::detectYoloObjectsCategories(objectsName,false);
}

bool TakeshiVision::detectAllYoloObjectsCategories(){
        std::vector<std::string> objectsName;
        return TakeshiVision::detectYoloObjectsCategories(objectsName,true);
}

bool TakeshiVision::detectYoloObjectsCategories(std::vector<std::string> objectsName,bool allObjects){
        std::vector<vision_msgs::VisionObject> specificYoloObjects;
        cv::Mat imaBGR,imaPCL;
        cv::Scalar color;

        if(!TakeshiVision::getImagesFromTakeshi(imaBGR,imaPCL)){
                TakeshiVision::printTakeshiError("Can not get images from Takeshi");
                return false;
        }

        allObjects ? TakeshiVision::detectAllYoloObjects(specificYoloObjects,4000):
                     TakeshiVision::detectSpecificYoloObject(objectsName,specificYoloObjects,4000);

        if(specificYoloObjects.size() < 1){
                TakeshiVision::printTakeshiError("Can not detected yolo objects");
                return false;
        }

        for(int i=0;i<specificYoloObjects.size();i++){
                color=TakeshiVision::getColorBoundingBoxes(specificYoloObjects[i].category);
                cv::putText(imaBGR,specificYoloObjects[i].category,
                        cv::Point(specificYoloObjects[i].bounding_box.xmin,specificYoloObjects[i].bounding_box.ymin-5),
                        cv::FONT_HERSHEY_DUPLEX,0.8,color,1,cv::LINE_8);
                rectangle(imaBGR,cv::Point(specificYoloObjects[i].bounding_box.xmin,specificYoloObjects[i].bounding_box.ymin),
                                 cv::Point(specificYoloObjects[i].bounding_box.xmax,specificYoloObjects[i].bounding_box.ymax), 
                                 color, 2, 8, 0 );
        }
        cv::imshow("Objects Categories",imaBGR);
        cv::waitKey(5000);   
}

bool TakeshiVision::detectYoloObject(std::string objectName,vision_msgs::VisionObject& recognizedYoloObject, int timeOut_ms, vision_msgs::ObjectCoordinatesForDetection objectCoordinates){
        std::vector<vision_msgs::VisionObject> recognizedYoloObjects;
        printTakeshiMessage("Searching for: "+ objectName);
        if(!TakeshiVision::detectAllYoloObjects(recognizedYoloObjects,timeOut_ms,objectCoordinates))
                return false;

        for(int i=0; i<recognizedYoloObjects.size(); i++) {
                if(objectName.compare(recognizedYoloObjects[i].id)==0) {
                        cout << "\033[1;34m     TakeshiVision.->Yolo Objects detected: "<< objectName <<"\033[0m" << endl;
                        recognizedYoloObject=recognizedYoloObjects[i];
                        return true;
                }
        }
        cout << "\033[1;34m     TakeshiVision.->Yolo Objects detected: Nothing!!!\033[0m" << endl;
        return false;
}

bool TakeshiVision::detectSpecificYoloObject(std::vector<std::string> objectsName,std::vector<vision_msgs::VisionObject>& specificYoloObjects, int timeOut_ms, vision_msgs::ObjectCoordinatesForDetection objectCoordinates){
        std::vector<vision_msgs::VisionObject> recognizedYoloObjects;
        specificYoloObjects.clear();
        if(!TakeshiVision::detectAllYoloObjects(recognizedYoloObjects,timeOut_ms,objectCoordinates))
                return false;

        for(int i=0; i<recognizedYoloObjects.size(); i++) {
                for(int j=0; j<objectsName.size(); j++) {
                        if(objectsName[j].compare(recognizedYoloObjects[i].id)==0) {
                                cout << "\033[1;34m     TakeshiVision.->Specific Yolo Object detected: "<< recognizedYoloObjects[i].id <<"\033[0m" << endl;
                                specificYoloObjects.push_back(recognizedYoloObjects[i]);
                        }
                }
        }

        if(specificYoloObjects.size() < 1) {
                cout << "\033[1;34m     TakeshiVision.->No specific yolo objects were detected\033[0m" << endl;
                return false;
        }
        return true;
}

bool TakeshiVision::detectAllYoloObjects(std::vector<vision_msgs::VisionObject>& recognizedYoloObjects, int timeOut_ms,vision_msgs::ObjectCoordinatesForDetection objectCoordinates){
        vision_msgs::Yolov3_detector srv;
        srv.request.timeOut_ms.data=timeOut_ms;
        srv.request.objectCoordinates=objectCoordinates;
        if(cltDetectAllYoloObjects.call(srv)){
            printTakeshiMessage("Calling Yolov3_detector service detect all objects");
            recognizedYoloObjects=srv.response.recognizedYoloObjects;
        }
        else
            printTakeshiError("Failed in call service Yolov3 Detector");

        if(recognizedYoloObjects.size() < 1){
            printTakeshiError("Can not detect yolo objects");
            return false;
        }
        return true;
}

bool TakeshiVision::detectAllYoloObjectsWithArmCamera(std::vector<vision_msgs::VisionObject>& recognizedYoloObjects, int timeOut_ms){
        vision_msgs::Yolov3_detector srv;
        srv.request.timeOut_ms.data=timeOut_ms;
        if(cltDetectAllYoloObjectsWithArmCamera.call(srv)){
            printTakeshiMessage("Calling Yolov3_detector service with arm camera detect all objects");
            recognizedYoloObjects=srv.response.recognizedYoloObjects;
        }
        else
            printTakeshiError("Failed in call service Yolov3 Detector");

        if(recognizedYoloObjects.size() < 1){
            printTakeshiError("Can not detect yolo objects");
            return false;
        }
        return true;
}


bool TakeshiVision::getImagesFromTakeshi( cv::Mat& imaBGR, cv::Mat& imaPCL)
{
        point_cloud_manager::GetRgbd srv;
        if(!cltRgbdRobot.call(srv))
        {
                std::cout << "TakeshiVision.->Cannot get point cloud" << std::endl;
                return false;
        }
        TakeshiTools::PointCloud2Msg_ToCvMat(srv.response.point_cloud, imaBGR, imaPCL);
        return true;
}

bool TakeshiVision::object_is_graspeable(cv::Vec3f centroid_3d, vision_msgs::ObjectCoordinatesForDetection object_coordinates){
        return TakeshiVision::object_is_graspeable(centroid_3d.val[0],centroid_3d.val[1],centroid_3d.val[2], object_coordinates);
}

bool TakeshiVision::object_is_graspeable(float x, float y, float z, vision_msgs::ObjectCoordinatesForDetection object_coordinates){
        if( x < object_coordinates.x_max &&
            x > object_coordinates.x_min &&
            y < object_coordinates.y_max &&
            y > object_coordinates.y_min &&
            z < object_coordinates.z_max &&
            z > object_coordinates.z_min
            )
                return true;
        else
                return false;
}

bool TakeshiVision::detectObjectByColor(string color, vision_msgs::VisionObject& object,bool bag){
        cv::Mat imaBGR,imaPCL,HSV_image, segmentedImage,segmentedImageRed;
        cv::Rect boundRect;
        cv::Vec3f imageCentroid;
        int min_area=2000;

        printTakeshiMessage("Detect Object By Color: " + color);

        if(!TakeshiVision::getImagesFromTakeshi(imaBGR,imaPCL)) {
                TakeshiVision::printTakeshiError("Can not get images from Takeshi");
                return false;
        }
        std::vector<cv::Vec4i> hierarchy;
        std::vector<vector<cv::Point> > contours;

       if(!debug_hsv_segmentation){
            if(color.compare("blue")==0)
                    HSV=HSV_blueBag;

            else if(color.compare("red")==0)
                    HSV=HSV_redBin;

            else if(color.compare("green")==0)
                    HSV=HSV_greenBin;

            else if(color.compare("yellow")==0)
                    HSV=HSV_yellowBag;

            else if(color.compare("brown")==0)
                    HSV=HSV_brownBag;
            else{
                    TakeshiVision::printTakeshiError("No valid color");
                    return false;
            }
        }
        cv::cvtColor(imaBGR,HSV_image, cv::COLOR_BGR2HSV);

            
        cv::inRange(HSV_image,cv::Scalar(HSV[0],HSV[1],HSV[2]), cv::Scalar(HSV[3],HSV[4],HSV[5]),segmentedImage);
        if(color.compare("red")==0) {
                cv::inRange(HSV_image,cv::Scalar(0,HSV[1],HSV[2]), cv::Scalar(5,HSV[4],HSV[5]),segmentedImageRed);
                cv::bitwise_or(segmentedImage, segmentedImageRed,segmentedImage);
        }
        if(debug_hsv_segmentation){
            namedWindow("segmentedImage", cv::WINDOW_AUTOSIZE); // Create Window
            cv::createTrackbar("H Hight","segmentedImage", &HSV[3], hsv_max, trackbar_hh );
            cv::createTrackbar("H Low","segmentedImage", &HSV[0], hsv_max, trackbar_hl );
            cv::createTrackbar("S Hight","segmentedImage", &HSV[4], hsv_max, trackbar_sh );
            cv::createTrackbar("S Low","segmentedImage", &HSV[1], hsv_max, trackbar_sl );
            cv::createTrackbar("V Hight","segmentedImage", &HSV[5], hsv_max, trackbar_vh );
            cv::createTrackbar("V Low","segmentedImage", &HSV[2], hsv_max, trackbar_vl );
            cv::imshow("HSVImage",HSV_image);
            cv::imshow("segmentedImage",segmentedImage);
            cv::waitKey(500);
        }
        cv::Mat element = getStructuringElement(0,cv::Size(2*7+1, 2*7+1 ),cv::Point(7,7));
        cv::morphologyEx(segmentedImage,segmentedImage,cv::MORPH_CLOSE,element);

        cv::findContours(segmentedImage,contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE );
        int area=0;
        size_t best_contour=0;
        cv::Point p1;

        if(contours.size() > 0) {
                for(size_t i = 0; i< contours.size(); i++) {
                        if(contourArea(contours[i]) >= area) {
                                area=contourArea(contours[i]);
                                best_contour=i;
                        }
                }
                cv::Moments m = moments(contours[best_contour], false);
                p1.x =m.m10/m.m00;
                p1.y =m.m01/m.m00;
                boundRect =cv::boundingRect(cv::Mat(contours[best_contour]));
                if(bag)
                        p1.y=boundRect.tl().y+65;
                cv::rectangle(imaBGR,boundRect.tl(),boundRect.br(),cv::Scalar(255,255,255), 2, 8, 0 );
                circle(imaBGR, p1, 10, cv::Scalar(255,255,255), -1);
        }

        else{
                TakeshiVision::printTakeshiError("No contours detected");
                return false;
        }
        std::cout << "Area bag: " << area << std::endl;
        if(area < min_area) {
                TakeshiVision::printTakeshiError("The area of the object is very less: "+ std::to_string(area));
                return false;
        }

        bool centroid=false;

        for(int i=p1.x-3; i<=p1.x+3 && centroid==false; i++) {
                for(int j=p1.y-3; j<=p1.y+3 && centroid==false; j++) {
                        imageCentroid=imaPCL.at<cv::Vec3f>(j,i);
                        if(imageCentroid.val[0] !=0 && imageCentroid.val[1] !=0 && imageCentroid.val[2] !=0) {
                                centroid=true;
                        }
                }
        }

        if(centroid) {
                object.bounding_box.xmin=boundRect.tl().x;
                object.bounding_box.ymin=boundRect.tl().y;
                object.bounding_box.xmax=boundRect.br().x;
                object.bounding_box.ymax=boundRect.br().y;
                object.pose.position.x=imageCentroid.val[0];
                object.pose.position.y=imageCentroid.val[1];
                object.pose.position.z=imageCentroid.val[2];
                printTakeshiMessage("Category: " + color );
                printTakeshiMessage("Centroid 3D  X: " + std::to_string(object.pose.position.x) + " Y: " + std::to_string(object.pose.position.y) + "Z: " + std::to_string(object.pose.position.z));
        }
        else{
                printTakeshiError("Can not get the object 3D centroid ");
                return false;
        }

        cv::imshow("Segmented Image", imaBGR);
        cv::waitKey(100);
        return true;
}


bool TakeshiVision::detectCircles(vision_msgs::VisionObject& object){
        cv::Mat imaBGR,imaPCL,imaGray,imaBlur;
        cv::Vec3f imageCentroid;

        printTakeshiMessage("Detect circle");

        if(!TakeshiVision::getImagesFromTakeshi(imaBGR,imaPCL)) {
                TakeshiVision::printTakeshiError("Can not get images from Takeshi");
                return false;
        }
        cv::cvtColor(imaBGR,imaGray, cv::COLOR_BGR2GRAY);
        GaussianBlur(imaGray,imaBlur,cv::Size(11,11), 0);
        Canny(imaBlur,imaBlur,100,100*3,3);
        vector<vector<cv::Point> > contours;
        vector<cv::Vec4i> hierarchy;
        findContours(imaBlur, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

        cv::Mat drawing = cv::Mat::zeros( imaBlur.size(), CV_8UC1 );
        for( int i = 0; i< contours.size(); i++ ){
            if(contourArea(contours[i])>700){
               
               drawContours( drawing, contours, i, 255, 2, 4, hierarchy, 0, cv::Point() );
            }}
        
        vector<cv::Vec3f> circles;
        
        HoughCircles(drawing, circles, CV_HOUGH_GRADIENT, 1.2, drawing.rows/8, 50, 30, 10, 40 );

        for( size_t i = 0; i < circles.size(); i++ ){
            cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle( imaBGR, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
            circle( imaBGR, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
            object.x=center.x;
            object.y=center.y;
            cv::namedWindow( "Hough Circle", CV_WINDOW_AUTOSIZE );
            cv::imshow( "Hough Circle", imaBGR);
            cv::waitKey(100);
            std::cout << center.x+(radius*2) << std::endl;
            imageCentroid=imaPCL.at<cv::Vec3f>(center.y,center.x+(radius*2));
            std::cout << imageCentroid.val[0] << " " << imageCentroid.val[1] << " " << imageCentroid.val[2] << std::endl;
            object.pose.position.x=imageCentroid.val[0];
            object.pose.position.y=imageCentroid.val[1];
            object.pose.position.z=imageCentroid.val[2];
            return true;
        } 

        cv::namedWindow( "Hough Circle", CV_WINDOW_AUTOSIZE );
        cv::imshow( "Hough Circle", imaBGR);
        cv::waitKey(100);
        return false;
}





/////////////////////////////////////////////////////////////////
//#############################################################//
//                METHODS  FOR  FACE RECOGNITION               //
vision_msgs::VisionFaceObjects TakeshiVision::getFaces(std::string id){
        vision_msgs::VisionFaceObjects faces;
        vision_msgs::FaceRecognition srv;
        srv.request.id = id;
        if(cltGetFaces.call(srv)) {
                faces = srv.response.faces;
                cout << "\033[1;34m     TakeshiVision.->Detect " << faces.recog_faces.size() << " faces\033[0m" << endl;
        }
        else
                cout << "\033[1;34m     TakeshiVision.->Failed in call service FaceRecognition\033[0m" << endl;

        return faces;
}

void TakeshiVision::stopFaceRecognition()
{
        cout << "\033[1;34m     TakeshiVision.->Stopping face recognition.\033[0m" << endl;
        std_msgs::Empty msg;
        TakeshiVision::pubFacStopRecog.publish(msg);
}

void TakeshiVision::facRecognize()
{
        cout << "\033[1;34m     TakeshiVision.->Starting face recognition without id.\033[0m" << endl;
        std_msgs::Empty msg;
        TakeshiVision::pubRecFace.publish(msg);
}

void TakeshiVision::facRecognize(std::string id)
{
        cout << "\033[1;34m     TakeshiVision.->Starting face recognition of id: " << id <<"\033[0m" << endl;
        std_msgs::String msg;
        msg.data = id;
        TakeshiVision::pubRecFaceByID.publish(msg);
}

bool TakeshiVision::getLastRecognizedFaces(std::vector<vision_msgs::VisionFaceObject>& faces)
{
        if(TakeshiVision::lastRecognizedFaces.size() < 1)
                return false;

        faces.clear();
        for(size_t i=0; i < TakeshiVision::lastRecognizedFaces.size(); i++)
                faces.push_back(TakeshiVision::lastRecognizedFaces[i]);
        TakeshiVision::lastRecognizedFaces.clear();
        return true;
}

vision_msgs::VisionFaceObjects TakeshiVision::facenetRecognize(std::string id)
{
        //Calls facenet and returns recognized faces
        vision_msgs::VisionFaceObjects faces;
        vision_msgs::FaceRecognition srv;
        srv.request.id = id;
        if(cltRecognizeFaceNet.call(srv)) {
                faces = srv.response.faces;
                cout << "\033[1;34m     TakeshiVision.->Facenet Detect " << faces.recog_faces.size() << " faces\033[0m" << endl;
        }
        else{
                cout << "\033[1;34m     TakeshiVision.->Failed in call service FaceNetRecognition\033[0m" << endl;
        }
        return faces;

}

bool TakeshiVision::facenetTrain(std::string id)
{
        //Add new embedding to facenet node on runtime
        vision_msgs::VisionFaceObjects faces;
        vision_msgs::FaceRecognition srv;
        srv.request.id = id;
        if(cltTrainFaceNet.call(srv)) {
                cout << "\033[1;34m     TakeshiVision.->Facenet Trained " << id << " \033[0m" << std::endl;
        }
        else{
                cout << "\033[1;34m     TakeshiVision.->Failed in call service FaceNetTrain\033[0m" << endl;
                return false;
        }
        return true;
}

//Methods for operating face recognizer
void TakeshiVision::startFaceRecognition()
{
        cout << "\033[1;34m     TakeshiVision.->Starting face recognition.\033[0m" << endl;
        std_msgs::Empty msg;
        TakeshiVision::pubFacStartRecog.publish(msg);
}

void TakeshiVision::startFaceRecognitionOld()
{
        cout << "\033[1;34m     TakeshiVision.->Starting face recognition old. \033[0m" << endl;
        std_msgs::Empty msg;
        TakeshiVision::pubFacStartRecogOld.publish(msg);
}

vision_msgs::VisionFaceObjects TakeshiVision::getRecogFromPano(sensor_msgs::Image image){
        vision_msgs::VisionFaceObjects faces;
        vision_msgs::GetFacesFromImage srv;
        srv.request.panoramic_image = image;
        if(cltPanoFaceReco.call(srv)) {
                faces = srv.response.faces;
                cout << "\033[1;34m     TakeshiVision.->Detect " << faces.recog_faces.size() << " faces\033[0m" << endl;
        }
        else
                cout << "\033[1;34m     TakeshiVision.->Failed in call service GetFacesFromImage\033[0m" << endl;
        return faces;
}

// this is justina implementation.
// Is strongly recommend replace it whit FaceNet function
void TakeshiVision::facTrain(std::string id)
{
    std::cout << "TakeshiVision::facTrain[Do nothing] face with id: " << id << std::endl;
    std::cout << "This is a justina implementation. It should be replaced..." << std::endl;
}

// this is justina implementation.
// Is strongly recommend replace it whit FaceNet function
void TakeshiVision::facTrain(std::string id, int numOfFrames)
{
    std::cout << "TakeshiVision::facTrain[Do nothing] face with id: " << id << std::endl;
    std::cout << "This is a justina implementation. It should be replaced..." << std::endl;
}

// this is justina implementation.
// Is strongly recommend replace it whit FaceNet function
void TakeshiVision::facClearByID(std::string id)
{
        std::cout << "TakeshiVision::facTrain[Do nothing] face with id: " << id << std::endl;
    std::cout << "This is a justina implementation. It should be replaced..." << std::endl;
}

// this is justina implementation.
// Is strongly recommend replace it whit FaceNet function
void TakeshiVision::facClearAll()
{
    std::cout << "TakeshiVision::facTrain[Do nothing] face with id: " << std::endl;
    std::cout << "This is a justina implementation. It should be replaced..." << std::endl;
}



/////////////////////////////////////////////////////////////////
//#############################################################//
//            METHODS   FOR   SKELETON  RECOGNITION            //
void TakeshiVision::startSkeletonFinding(){
        TakeshiVision::lastSkeletons.clear();
        TakeshiVision::lastGestureRecog.clear();
        TakeshiVision::lastLeftHandPos.clear();
        TakeshiVision::lastRightHandPos.clear();
        std_msgs::Bool msg;
        msg.data = true;
        TakeshiVision::pubSktEnableRecog.publish(msg);
}

void TakeshiVision::getLastGesturesRecognize(std::vector<vision_msgs::GestureSkeleton> &gestures){
        gestures = TakeshiVision::lastGestureRecog;
        //TakeshiVision::lastGestureRecog.clear();
}


void TakeshiVision::stopSkeletonFinding()
{
        TakeshiVision::lastSkeletons.clear();
        TakeshiVision::lastGestureRecog.clear();
        TakeshiVision::lastLeftHandPos.clear();
        TakeshiVision::lastRightHandPos.clear();
        std_msgs::Bool msg;
        msg.data = false;
        TakeshiVision::pubSktEnableRecog.publish(msg);
}

/////////////////////////////////////////////////////////////////
//#############################################################//
//            METHODS   FOR  PANO-MAKER                        //
void TakeshiVision::takePano(){
        std_msgs::Empty msg;
        TakeshiVision::pubTakePanoMaker.publish(msg);
}

void TakeshiVision::clearPano(){
        std_msgs::Empty msg;
        TakeshiVision::panoImageRecived = false;
        TakeshiVision::pubClearPanoMaker.publish(msg);
}

void TakeshiVision::makePano(){
        std_msgs::Empty msg;
        TakeshiVision::pubMakePanoMaker.publish(msg);
}

bool TakeshiVision::isPanoImageRecived(){
        return TakeshiVision::panoImageRecived;
}

sensor_msgs::Image TakeshiVision::getLastPanoImage(){
        TakeshiVision::panoImageRecived = false;
        return TakeshiVision::lastImage;
}

//Methods for the arm image
sensor_msgs::Image TakeshiVision::getArmImage(){
        printTakeshiMessage("Get arm image");
        ros::Rate loop(10);
        while(ros::ok() && !TakeshiVision::is_arm_image){
            ros::spinOnce();
            loop.sleep();
        }
        TakeshiVision::is_arm_image=false;
        return TakeshiVision::armCameraImage;
}

//Methods for the qr reader
void TakeshiVision::startQRReader(){
        cout << "\033[1;34m     TakeshiVision.->Start QR reader\033[0m" << endl;
        std_msgs::Bool msg;
        msg.data = true;
        pubQRReaderStart.publish(msg);
}

void TakeshiVision::stopQRReader(){
        cout << "\033[1;34m     TakeshiVision.->Stop QR reader\033[0m" << endl;
        std_msgs::Bool msg;
        msg.data = false;
        pubQRReaderStart.publish(msg);
}


bool TakeshiVision::read_QR(std::string &out_string)
{
        bool success=false;
        int nextState=0;
        ros::Rate loop(10);
        TakeshiVision::QRString.clear();

        while (!success) {
                switch (nextState) {
                case 0:
                        TakeshiVision::startQRReader();
                        nextState=1;
                        break;
                case 1:
                        out_string=TakeshiVision::QRString;
                        if(out_string != "")
                                nextState=2;
                        break;
                case 2:
                        TakeshiVision::stopQRReader();
                        success=true;
                        break;
                }

                ros::spinOnce();
                loop.sleep();
        }

        return true;
}

//Methods for line finding
bool TakeshiVision::findLine(float& x1, float& y1, float& z1, float& x2, float& y2, float& z2)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to find a straight line.\033[0m" << endl;
        point_cloud_manager::GetRgbd srvGetCloud;
        if(!TakeshiVision::cltGetRgbdWrtRobot.call(srvGetCloud))
        {
                cout << "\033[1;34m     TakeshiVision.->Cannot find line: cannot get point cloud :'(\033[0m" << endl;
                return false;
        }

        vision_msgs::FindLines srvFindLines; //It really finds only one line
        srvFindLines.request.point_cloud = srvGetCloud.response.point_cloud;

        if(!TakeshiVision::cltFindLines.call(srvFindLines) || srvFindLines.response.lines.size() < 2)
        {
                cout << "\033[1;34m     TakeshiVision.->Cannot find lines. \033[0m" << endl;
                return false;
        }

        x1 = srvFindLines.response.lines[0].x;
        y1 = srvFindLines.response.lines[0].y;
        z1 = srvFindLines.response.lines[0].z;
        x2 = srvFindLines.response.lines[1].x;
        y2 = srvFindLines.response.lines[1].y;
        z2 = srvFindLines.response.lines[1].z;

        return true;
}

//Methods for plane findinig
bool TakeshiVision::findPlane(){
        std::cout << "TakeshiVision.->Trying to find a plane" << std::endl;
        vision_msgs::FindPlane fp;
        fp.request.name = "";
        if(!TakeshiVision::cltFindPlane.call(fp)) {
                std::cout << "TakeshiVision.->Cannot find a plane" << std::endl;
                return false;
        }
        std::cout << "TakeshiVision.->Find a plane" << std::endl;
        return true;
}

//Methods for find plane
bool TakeshiVision::findVacantPlane(std::vector<float>& vacantPlane, std::vector<int>& inliersOnPlane, bool inFront)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to find a vacantPlane \033[0m" << endl;
        vision_msgs::FindPlane fp;
        fp.request.inFront=inFront;
        fp.request.name="";
        if(!TakeshiVision::cltFindVacantPlane.call(fp))
        {
                cout << "\033[1;34m     TakeshiVision.->Cannot a vacantPlane \033[0m" << endl;
                return false;
        }

        for (int i = 0; i < (int)fp.response.centroidFreeSpace.size(); ++i)
        {
                vacantPlane.push_back(fp.response.centroidFreeSpace[i].x);
                vacantPlane.push_back(fp.response.centroidFreeSpace[i].y);
                vacantPlane.push_back(fp.response.centroidFreeSpace[i].z);
                inliersOnPlane.push_back(fp.response.inliers[i].data);
        }
        return true;
}

//Methods for find plane
bool TakeshiVision::findVacantPlaneAtHeight(std::vector<float>& vacantPlane, std::vector<int>& inliersOnPlane,
                                            double minHeight, double maxHeight)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to find a vacantPlane \033[0m" << endl;
        vision_msgs::FindPlaneAtHeight fp;
        fp.request.name="";
        fp.request.minH.data=minHeight;
        fp.request.maxH.data=maxHeight;
        if(!TakeshiVision::cltFindVacantPlaneAtHeight.call(fp))
        {
                cout << "\033[1;34m     TakeshiVision.->Cannot a vacantPlane \033[0m" << endl;
                return false;
        }

        for (int i = 0; i < (int)fp.response.centroidFreeSpace.size(); ++i)
        {
                vacantPlane.push_back(fp.response.centroidFreeSpace[i].x);
                vacantPlane.push_back(fp.response.centroidFreeSpace[i].y);
                vacantPlane.push_back(fp.response.centroidFreeSpace[i].z);
                inliersOnPlane.push_back(fp.response.inliers[i].data);
        }
        return true;
}

bool TakeshiVision::detectObjects(std::vector<vision_msgs::VisionObject>& recoObjList, bool saveFiles)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to detect objects...  \033[0m" << endl;
        vision_msgs::DetectObjects srv;
        srv.request.saveFiles = saveFiles;

        if(!cltDetectObjects.call(srv))
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> Service: can't detect anything\033[0m" << endl;
                return false;
        }

        recoObjList=srv.response.recog_objects;

        if(recoObjList.size() < 1)
        {
                cout << "\033[1;34m     TakeshiVision.-> Can't detect anything\033[0m" << endl;
                return false;
        }

        cout << "\033[1;34m     TakeshiVision.->Detected objects: " << recoObjList.size() << "\033[0m" << endl;
        return true;
}

bool TakeshiVision::detectAllObjects(std::vector<vision_msgs::VisionObject>& recoObjList, bool saveFiles)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to detect all objects...  \033[0m" << endl;

        vision_msgs::DetectObjects srv;
        srv.request.saveFiles = saveFiles;
        if(!cltDetectAllObjects.call(srv))
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                return false;
        }
        recoObjList=srv.response.recog_objects;
        if(recoObjList.size() < 1)
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                return false;
        }
        cout << "\033[1;34m     TakeshiVision.->Detected " << int(recoObjList.size()) << " objects\033[0m" << endl;
        return true;
}




//Methods for move the train object and move the tranining base
void TakeshiVision::trainObject(const std::string name)
{
        int attempts = 0;
        cout << "\033[1;34m     TakeshiVision.->trainObject\033[0m" << endl;
        vision_msgs::TrainObject srv;
        ros::Rate loop(10);
        srv.request.name = name;
        TakeshiVision::_isObjectTrained=false;
        srvTrainObject.call(srv);
        while(!callbackObjectTrained && attempts < 10) {
                ros::spinOnce();
                loop.sleep();
		++attempts;
	        if(attempts == 9)
		{
		  std::cout << "\033[1;34m    TakeshiVision.->trainObject: Attempts have been exceeded \033[0m" << std::endl;
		  return;
		}
        }
        callbackObjectTrained=false;
}

bool TakeshiVision::isObjectTrained(){
        cout << "\033[1;34m     TakeshiVision.->isObjectTrained: "<< TakeshiVision::_isObjectTrained <<"\033[0m" << endl;
        return TakeshiVision::_isObjectTrained;
}

bool TakeshiVision::loadObjectTrainDir(){
        cout << "\033[1;34m     TakeshiVision.->Load object train dir \033[0m" << endl;
        std_msgs::Bool msg;
        msg.data=true;
        pubLoadTrainDir.publish(msg);
        return true;
}

bool TakeshiVision::loadSpecificTrainingDir(std::string dir){
        cout << "\033[1;34m     TakeshiVision.->Load object train dir toys \033[0m" << endl;
        std_msgs::String msg;
        msg.data=dir;
        pubLoadSpecificTrainingDir.publish(msg);
        return true;
}


//detection on the floor
bool TakeshiVision::detectObjectsFloor(std::vector<vision_msgs::VisionObject>& recoObjList, bool saveFiles)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to detect objects...  \033[0m" << endl;

        vision_msgs::DetectObjects srv;
        srv.request.saveFiles = saveFiles;
        recoObjList.clear();
        ros::Duration(1).sleep();

        if(!cltDetectObjectsFloor.call(srv))
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                //continue;
                return false;
        }
        recoObjList=srv.response.recog_objects;

        if(recoObjList.size() < 1)
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything:" << "\033[0m" << endl;
                //continue;
                return false;
        }
        cout << "\033[1;34m     TakeshiVision.->Detected " << int(recoObjList.size()) << " objects\033[0m" << endl;
        return true;
}

bool TakeshiVision::detectAllObjectsFloor(std::vector<vision_msgs::VisionObject>& recoObjList, bool saveFiles)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to detect all objects...  \033[0m" << endl;

        vision_msgs::DetectObjects srv;
        srv.request.saveFiles = saveFiles;
        if(!cltDetectAllObjectsFloor.call(srv))
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                return false;
        }
        recoObjList=srv.response.recog_objects;
        if(recoObjList.size() < 1)
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                return false;
        }
        cout << "\033[1;34m     TakeshiVision.->Detected " << int(recoObjList.size()) << " objects\033[0m" << endl;
        return true;
}

bool TakeshiVision::detectObjectsOnPlane(std::vector<vision_msgs::VisionObject>& recoObjList, double height)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to detect all objects on plane @"  << height<<"\033[0m" << endl;

        vision_msgs::DetectObjectsInPlane srv;
        srv.request.plane_height.data = height;
        if(!cltDetectObjectsOnPlane.call(srv))
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                return false;
        }
        recoObjList=srv.response.recog_objects;
        if(recoObjList.size() < 1)
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                return false;
        }
        cout << "\033[1;34m     TakeshiVision.->Detected " << int(recoObjList.size()) << " objects\033[0m" << endl;
        return true;
}

bool TakeshiVision::detectAllObjectsOnPlane(std::vector<vision_msgs::VisionObject>& recoObjList, double height)
{
        cout << "\033[1;34m     TakeshiVision.->Trying to detect all objects on plane @"  << height<<"\033[0m" << endl;

        vision_msgs::DetectObjectsInPlane srv;
        srv.request.plane_height.data = height;
        if(!cltDetectAllObjectsOnPlane.call(srv))
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                return false;
        }
        recoObjList=srv.response.recog_objects;
        if(recoObjList.size() < 1)
        {
                cout << std::endl << "\033[1;34m     TakeshiVision.-> can't detect anything\033[0m" << endl;
                return false;
        }
        cout << "\033[1;34m     TakeshiVision.->Detected " << int(recoObjList.size()) << " objects\033[0m" << endl;
        return true;
}

//Flat detector
bool TakeshiVision::detectFlattenedObjects(vision_msgs::VisionFlattenedObjectList& recoObjList,
                                           bool saveFiles)
{
        std::cout << "TakeshiVision.->Trying to detect flattened objects... " << std::endl;
        vision_msgs::RecognizeFlattenedObjects srv;

        if(!cltFlattenedSeg.call(srv))
        {
                std::cout << std::endl << "Takeshi::Vision can't detect any flattened object" << std::endl << std::endl;
                return false;
        }

        // Fill message....
        recoObjList = srv.response.recog_objects;
        if(recoObjList.objectList.size() < 1)
        {
                std::cout << std::endl << "Takeshi::Vision can't detect any flattened object" << std::endl << std::endl;
                return false;
        }
        std::cout << "TakeshiVision.->Detected " << int(recoObjList.objectList.size()) << "flattened objects" << std::endl;
        return true;

}
//openpose stuff coyo was here
bool TakeshiVision::getSkeletons(vision_msgs::Skeletons &skl, float timeOut)
{
        cout << "\033[1;34m     TakeshiVision.->Get Skeletons\033[0m" << endl;
        //Gets all visible skeletons and return in skl
        std_msgs::Bool msg; msg.data=true;
        TakeshiVision::pubSktEnableRecog.publish(msg);
        //Esto queda harcodead :(
        std::string skeletonTopic = "/vision/skeleton_finder/skeleton_recog";
        //The library asked for boost::sharedPtr
        boost::shared_ptr<vision_msgs::Skeletons const> sharedPtr;
        sharedPtr = ros::topic::waitForMessage<vision_msgs::Skeletons> (skeletonTopic, ros::Duration(timeOut) );
        if (sharedPtr==NULL)
        {
                msg.data=false;
                TakeshiVision::pubSktEnableRecog.publish(msg);
                ros::spinOnce();
                ROS_ERROR("Timed Out!, failed to call %s", skeletonTopic.c_str());
                cout << "\033[1;34m     TakeshiVision.->Timed Out!, failed to call " << skeletonTopic.c_str() << "\033[0m" << endl;
                return false;
        }

        skl = *sharedPtr;
        msg.data=false;
        TakeshiVision::pubSktEnableRecog.publish(msg);
        return true;
}

bool TakeshiVision::getBothWrists(geometry_msgs :: PointStamped &left_wrist,
                                 geometry_msgs::PointStamped &right_wrist)
{
        //Tries to get both wrist.
        // In case one is missing or too far away point is set to x , y ,z =(0,0,0)
        bool success = false;
        std::string wristName;
        TakeshiVision::startSkeletonFinding();
        ros::Duration(1.0).sleep();
        ros::spinOnce();
        //vision_msgs::Skeletons skls;
        vision_msgs::Skeleton skeletonZero;
        //if(getSkeletons(skls,10.0))
        if(TakeshiVision::lastSkeletons.size() > 0)
        {
                TakeshiVision::stopSkeletonFinding();
                ros::Duration(1.0).sleep();
                ros::spinOnce();
                if (TakeshiVision::lastSkeletons.size()>0)
                {
                        int closestSkl =TakeshiVision::getClosestSkeleton(TakeshiVision::lastSkeletons);
                        skeletonZero = TakeshiVision::lastSkeletons[closestSkl];
                        cout << "\033[1;34m     TakeshiVision.->Got: " << TakeshiVision::lastSkeletons.size()
                             << " closest is "<< closestSkl <<"\033[0m" << endl;
                }
                else
                {
                        cout << "\033[1;34m     TakeshiVision.->Got no Skeleton\033[0m" << endl;
                        success=false;
                }
        }
        else
        {
                success = false;
                cout << "\033[1;34m     TakeshiVision.->Could not get skeletons\033[0m" << endl;
        }

        cout << "\033[1;34m     TakeshiVision.->Found " << skeletonZero.joints.size() << "joints\033[0m" << endl;

        //For error checking
        right_wrist.point.x = 0;
        left_wrist.point.x = 0;
        bool left_fnd=false, right_fnd=false;
        for (int i = 0; i < skeletonZero.joints.size(); i++)
        {
                std::string jointName = skeletonZero.joints[i].name_joint.data;
                cout << "\033[1;34m     TakeshiVision.->Joint: " << jointName << "\033[0m" << endl;
                if (left_fnd && right_fnd)
                {
                        //If both wrist found stop
                        break;
                }
                if (!jointName.compare("right_wrist")) {
                        //if wrist if found save and break

                        if(skeletonZero.joints[i].position.x > 1.0)
                        {
                                //Wrist too far!
                                geometry_msgs::Point zero;
                                zero.x=0; zero.y=0; zero.z=0;
                                right_wrist.point = zero;
                                continue;
                        }

                        right_wrist.point.x = skeletonZero.joints[i].position.x-0.13;
                        right_wrist.point.y = skeletonZero.joints[i].position.y;
                        right_wrist.point.z = skeletonZero.joints[i].position.z+0.15;

                        cout << "\033[1;34m     TakeshiVision.->Found right wrist at" <<
                        right_wrist.point.x<< " " <<
                        right_wrist.point.y<< " " <<
                        right_wrist.point.z<< "\033[0m" << endl;
                        //Found wrist flag
                        right_fnd = true;

                }

                if (!jointName.compare("left_wrist")) {
                        //if wrist if found save and break

                        if(skeletonZero.joints[i].position.x > 1.0)
                        {
                                //Wrist too far!
                                geometry_msgs::Point zero;
                                zero.x=0; zero.y=0; zero.z=0;
                                left_wrist.point = zero;
                                continue;
                        }

                        left_wrist.point.x = skeletonZero.joints[i].position.x-0.13;
                        left_wrist.point.y = skeletonZero.joints[i].position.y;
                        left_wrist.point.z = skeletonZero.joints[i].position.z+0.15;

                        cout << "\033[1;34m     TakeshiVision.->Found left wrist at" <<
                        left_wrist.point.x<< " " <<
                        left_wrist.point.y<< " " <<
                        left_wrist.point.z<< "\033[0m" << endl;
                        left_fnd = true;

                }
        }

        if (left_fnd || right_fnd)
        {
                // if any wrist found return true
                success = true;
        }
        return success;


}

bool TakeshiVision::getWrist(geometry_msgs :: PointStamped &wrist, bool right /*=true*/)
{
        //get the wirst of the first skeelton
        //right if true choose right writst otherwise choose left
        bool success = false;
        std::string wristName;
        if (right) {
                wristName = "right_wrist";
        }
        else   {
                wristName = "left_wrist";
        }
        TakeshiVision::startSkeletonFinding();
        ros::Duration(1.0).sleep();
        ros::spinOnce();
        //vision_msgs::Skeletons skls;
        vision_msgs::Skeleton skeletonZero;
        //if(getSkeletons(skls,10.0))
        if(TakeshiVision::lastSkeletons.size() > 0)
        {
                TakeshiVision::stopSkeletonFinding();
                ros::Duration(1.0).sleep();
                ros::spinOnce();
                if (TakeshiVision::lastSkeletons.size()>0)
                {
                        int closestSkl =TakeshiVision::getClosestSkeleton(TakeshiVision::lastSkeletons);
                        skeletonZero = TakeshiVision::lastSkeletons[closestSkl];
                        cout << "\033[1;34m     TakeshiVision.->Got: " << TakeshiVision::lastSkeletons.size()
                             << " closest is "<< closestSkl <<"\033[0m" << endl;
                }
                else
                {
                        cout << "\033[1;34m     TakeshiVision.->Got no Skeleton\033[0m" << endl;
                        success=false;
                }
        }
        else
        {
                success = false;
                cout << "\033[1;34m     TakeshiVision.->Could not get skeletons\033[0m" << endl;
        }

        cout << "\033[1;34m     TakeshiVision.->Found " << skeletonZero.joints.size() << "joints\033[0m" << endl;

        for (int i = 0; i < skeletonZero.joints.size(); i++)
        {
                std::string jointName = skeletonZero.joints[i].name_joint.data;
                cout << "\033[1;34m     TakeshiVision.->Joint: " << jointName << "\033[0m" << endl;
                if (!jointName.compare(wristName)) {
                        //if wrist if found save and break

                        wrist.point.x=skeletonZero.joints[i].position.x-0.13;
                        wrist.point.y=skeletonZero.joints[i].position.y;
                        wrist.point.z=skeletonZero.joints[i].position.z+0.15;


                        cout << "\033[1;34m     TakeshiVision.->Found wrist at" <<
                        wrist.point.x<< " " <<
                        wrist.point.y<< " " <<
                        wrist.point.z<< "\033[0m" << endl;

                        if(wrist.point.x > 1.0)
                                return false;
                        success = true;
                        break;
                }
        }

        return success;

}

bool TakeshiVision::getArm(
        std::vector<geometry_msgs :: PointStamped> &arm,
        bool right /*=true*/ )
{
        //get the arm of the first skeleton
        //right if true choose right writst otherwise choose left
        //elbow is on arm[0]
        //wrist on arm[1]
        bool success = false;
        std::string wristName, elbowName;
        if (right) {
                wristName = "right_wrist";
                elbowName = "right_elbow";
        }
        else
        {
                wristName = "left_wrist";
                elbowName = "left_elbow";
        }

        vision_msgs::Skeletons skls;
        vision_msgs::Skeleton skeletonZero;
        std_msgs::Header skel_head;
        if(getSkeletons(skls,10.0))
        {
                if (skls.skeletons.size()>=1)
                {
                        skel_head=skls.header;
                        skeletonZero = skls.skeletons[0];
                }
                else
                {
                        std::cout << "Got no skeleton" << '\n';
                        success=false;
                }
        }
        else
        {
                success = false;
                std::cout << "Could not get skeletons" << '\n';
        }

        arm.resize(2);
        for (int i = 0; i < skeletonZero.joints.size(); i++)
        {
                std::string jointName = skeletonZero.joints[i].name_joint.data;
                geometry_msgs::Point p;
                if (!jointName.compare(wristName)) {
                        //if wrist if found save and break
                        p.x=skeletonZero.joints[i].position.x;
                        p.y=skeletonZero.joints[i].position.y;
                        p.z=skeletonZero.joints[i].position.z;
                        arm[1].header=skel_head;
                        arm[1].point=p;

                        success = true;

                }
                else if (!jointName.compare(elbowName)) {
                        //if wrist if found save and break
                        p.x=skeletonZero.joints[i].position.x;
                        p.y=skeletonZero.joints[i].position.y;
                        p.z=skeletonZero.joints[i].position.z;
                        arm[0].header=skel_head;
                        arm[0].point=p;
                        success = true;

                }
        }

        return success;

}

double TakeshiVision::distanceToPerson(vision_msgs::Skeleton person)
{
        //get distance to hopefully nose or neck of the person
        double x = person.joints[0].position.x;
        double y = person.joints[0].position.y;
        double z = person.joints[0].position.z;
        return sqrt(x*x+y*y+z*z);
}

int TakeshiVision::getClosestSkeleton(std::vector< vision_msgs::Skeleton> &esqueletos)
{
        cout << "\033[1;34m     TakeshiVision.->Get Closest Skeleton\033[0m" << endl;
        int closestSkeletonIdx =0;
        double minDist = distanceToPerson(esqueletos[closestSkeletonIdx]);

        for (int j = 0; j < esqueletos.size(); j++)
        {
                double personDistance = distanceToPerson(esqueletos[j]);

                if (minDist>personDistance)
                {
                        minDist=personDistance;
                        closestSkeletonIdx = j;
                }
        }
        return closestSkeletonIdx;
}

bool TakeshiVision::getHandles(std::vector<geometry_msgs::Point> &handles)
{
        vision_msgs::DetectHandles srv;
        if(!srvDetectHandles.call(srv))
        {
                std::cout << "Cloud not get handles: Service call failed" << std::endl;
                return false;
        }
        handles=srv.response.handle_centroids;
        if(handles.size()<1)
        {
                std::cout << "Cloud not get any handles on scene" << '\n';
                return false;
        }
        return true;
}

/*
   bool TakeshiVision::isAPerson(){

   }
 */
