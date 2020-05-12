#include <ros/ros.h>
#include "vision_msgs/Yolov3_detector.h"
#include "vision_msgs/ObjectCoordinatesForDetection.h"
#include "vision_msgs/VisionObject.h"
#include "point_cloud_manager/GetRgbd.h"
#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/BoundingBox.h>
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiVision.h"

darknet_ros_msgs::BoundingBoxes lastBounding_boxes;
ros::ServiceClient cltRgbdRobot;
ros::ServiceServer srvDetectAllYoloObjects;
ros::ServiceServer srvDetectAllYoloObjectsWithArmCamera;

bool yoloBoundingBoxesRecived=false;
bool read_objects_categories=true;
std::string object_categories_file;
std::vector<std::vector<std::string> >object_categories;
vision_msgs::ObjectCoordinatesForDetection objectCoordinates;
ros::Subscriber subYoloBoundingBoxes;
ros::Publisher pubYoloImage;


void printMessage(std::string message){std::cout << "\033[1;34m     YOLOv3 node.->" << message << "\033[0m" << std::endl;}
void printErrorMessage(std::string message){std::cout << "\033[1;31m     YOLOv3 node ->" << message << "\033[0m" << std::endl;}

void print_object_coordinates(vision_msgs::ObjectCoordinatesForDetection object_coordinates){

        printMessage("\nLooking for objects in: ");
        printMessage("x: " + std::to_string(object_coordinates.x_min) + "->" + std::to_string(object_coordinates.x_max));
        printMessage("y: " + std::to_string(object_coordinates.y_min) + "->" + std::to_string(object_coordinates.y_max));
        printMessage("z: " + std::to_string(object_coordinates.z_min) + "->" + std::to_string(object_coordinates.z_max) + "\n");
}

bool getImagesFromTakeshi(cv::Mat& imaBGR, cv::Mat& imaPCL){

    point_cloud_manager::GetRgbd srv;
    if(!cltRgbdRobot.call(srv)){
        printErrorMessage("Can not get the image from Takeshi");
        return false;
    }
    TakeshiTools::PointCloud2Msg_ToCvMat(srv.response.point_cloud, imaBGR, imaPCL);
    return true; 
}

void callback_darknet_ros_boundig_boxes(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg){

        lastBounding_boxes.header = msg->header;
        lastBounding_boxes.image_header = msg->image_header;
        lastBounding_boxes.bounding_boxes = msg->bounding_boxes;
        if(lastBounding_boxes.bounding_boxes.size() > 0)
                yoloBoundingBoxesRecived=true;
}

bool get_3d_bb_centroid(cv::Mat &imaPCL,cv::Vec3f& centroid_3d, int i){
	cv::Vec3f imagePoint;
	int point_count=0;
	centroid_3d.val[0]=centroid_3d.val[1]=centroid_3d.val[2]=0.0;
	
	for(int k=lastBounding_boxes.bounding_boxes[i].xmin; k<=lastBounding_boxes.bounding_boxes[i].xmax; k++) {
        for(int j=lastBounding_boxes.bounding_boxes[i].ymin; j<=lastBounding_boxes.bounding_boxes[i].ymax; j++) {
            imagePoint=imaPCL.at<cv::Vec3f>(j,k);
                                        
            if(imagePoint.val[0] != 0.0 && imagePoint.val[2] != 0.0) {
                centroid_3d.val[0]+=imagePoint[0];
                centroid_3d.val[1]+=imagePoint[1];
                centroid_3d.val[2]+=imagePoint[2];
                point_count++;
            }
        }
    }
    centroid_3d.val[0]/=point_count;
    centroid_3d.val[1]/=point_count;
    centroid_3d.val[2]/=point_count;
    if(point_count < 100)
    	return false;
    return true;
}

bool readObjectsCategories(std::string obj_file){
        object_categories_file+=obj_file;
        printMessage("Loading objects categories from: " + object_categories_file);
        std::ifstream file(object_categories_file.c_str());
        if (!file.is_open()) {
                printErrorMessage("Could not open file");
                file.close();
                return false;
        }
        std::vector<std::string> object_c(2);
        std::string line;
        while (std::getline(file,line)) {
                std::istringstream iss(line);
                if (!(iss >> object_c[0] >> object_c[1])) {
                        printErrorMessage("Parsing Error");
                        return false;
                }
                object_categories.push_back(object_c);
        }
        file.close();
        return true;
}

std::string getObjectCategory(std::string object){
        if(read_objects_categories) {
                readObjectsCategories("objects_abril_categories.txt");
                read_objects_categories=false;
        }
        for(int i=0; i< object_categories.size(); i++)
                if(object_categories[i][0].compare(object)==0)
                        return object_categories[i][1];
        printErrorMessage("Unknown Category to: " + object);
        return "unknown_category";
}

std::vector<vision_msgs::VisionObject> sort_nearest_object(std::vector<vision_msgs::VisionObject> recognizedYoloObjectsAux){
		float euclideanDistance, minEuclidenDistance=100;
        int index;
        for(int i=0; i<recognizedYoloObjectsAux.size(); i++) {
            euclideanDistance=sqrt(pow(0 - recognizedYoloObjectsAux[i].pose.position.x, 2) + pow(0 - recognizedYoloObjectsAux[i].pose.position.y, 2));
                if(euclideanDistance <= minEuclidenDistance) {
                    minEuclidenDistance=euclideanDistance;
                    index=i;
                }
            }
        std::vector<vision_msgs::VisionObject> recognizedYoloObjects;
        recognizedYoloObjects.clear();
        recognizedYoloObjects.push_back(recognizedYoloObjectsAux[index]);
        for(int i=0; i<recognizedYoloObjectsAux.size(); i++)
                if(i != index)
                    recognizedYoloObjects.push_back(recognizedYoloObjectsAux[i]);
        return recognizedYoloObjects;
}

bool detect_all_yolo_objects(std::vector<vision_msgs::VisionObject>& recognizedYoloObjects, int timeOut_ms,vision_msgs::ObjectCoordinatesForDetection object_coordinates){

        int attempts = timeOut_ms / 100;
        cv::Mat imaBGR,imaPCL;
        sensor_msgs::Image img_msg;
        std_msgs::Header header;
        header.seq = 1;
        header.stamp = ros::Time::now();
        cv_bridge::CvImage img_bridge;        
        vision_msgs::VisionObject yoloObject;
        std::vector<vision_msgs::VisionObject> recognizedYoloObjectsAux;
        
        
        recognizedYoloObjects.clear();       
        ros::Rate loop(10);
        
        print_object_coordinates(object_coordinates);

        if(!getImagesFromTakeshi(imaBGR,imaPCL))
            return false;
        
        img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, imaBGR);
        img_bridge.toImageMsg(img_msg);

        for(int i=0; i<4; i++) {
            //we have a problem with the darknetros subscriber 
            pubYoloImage.publish(img_msg);
            ros::spinOnce();
            loop.sleep();
        }

        yoloBoundingBoxesRecived=false;
        //wait for the response of darknet-ros        
        while(ros::ok() && !yoloBoundingBoxesRecived && --attempts > 0) {
                ros::spinOnce();
                loop.sleep();
        }

        if(yoloBoundingBoxesRecived) {
                printMessage("\n\nYolo Objects: ");
                printMessage("Yolo Objects detected: "+ std::to_string(lastBounding_boxes.bounding_boxes.size()));
                
                for(int i=0; i<lastBounding_boxes.bounding_boxes.size(); i++) {
                        cv::Vec3f centroid_3d;                        
                        if(get_3d_bb_centroid(imaPCL,centroid_3d,i)) {
                                yoloObject.id = lastBounding_boxes.bounding_boxes[i].Class;
                                yoloObject.category = getObjectCategory(yoloObject.id);
                                yoloObject.confidence = lastBounding_boxes.bounding_boxes[i].probability;
                                yoloObject.pose.position.x = centroid_3d.val[0];
                                yoloObject.pose.position.y = centroid_3d.val[1];
                                yoloObject.pose.position.z = centroid_3d.val[2]+0.03;
                                yoloObject.bounding_box.xmin=lastBounding_boxes.bounding_boxes[i].xmin;
                                yoloObject.bounding_box.ymin=lastBounding_boxes.bounding_boxes[i].ymin;
                                yoloObject.bounding_box.xmax=lastBounding_boxes.bounding_boxes[i].xmax;
                                yoloObject.bounding_box.ymax=lastBounding_boxes.bounding_boxes[i].ymax;
                                    
                                if(TakeshiVision::object_is_graspeable(centroid_3d, object_coordinates)){
                                    recognizedYoloObjectsAux.push_back(yoloObject);
                                    printMessage("Class: " + yoloObject.id + " - Confidence: " + std::to_string(yoloObject.confidence));
                                    printMessage("Centroid 3D  X: " + std::to_string(yoloObject.pose.position.x) + " Y: " + std::to_string(yoloObject.pose.position.y) + " Z: " + std::to_string(yoloObject.pose.position.z)+ "\n");
                                }
                                else{
                                    printMessage("Class: " + lastBounding_boxes.bounding_boxes[i].Class + " - Confidence: " + std::to_string(lastBounding_boxes.bounding_boxes[i].probability));
                                    printMessage("Centroid 3D  X: " + std::to_string(yoloObject.pose.position.x) + " Y: " + std::to_string(yoloObject.pose.position.y) + " Z: " + std::to_string(yoloObject.pose.position.z));
                                    printErrorMessage("The Object does not satisfy the objectCoordinates \n");
                                }
                        }

                        else{
                                printMessage("Class: " + lastBounding_boxes.bounding_boxes[i].Class + " - Confidence: " + std::to_string(lastBounding_boxes.bounding_boxes[i].probability));
                                printErrorMessage("Can not get the object 3D centroid");
                        }
                }
                if(recognizedYoloObjectsAux.size() > 0){
                    recognizedYoloObjects=sort_nearest_object(recognizedYoloObjectsAux);
                    yoloBoundingBoxesRecived=false;
                }
                
        }
        else{
                yoloBoundingBoxesRecived=false;  
                printErrorMessage("Can not detect yolo objects");   
                recognizedYoloObjects.clear(); 

        }

        return true;
}

bool detect_all_yolo_objects_with_arm_camera(std::vector<vision_msgs::VisionObject>& recognizedYoloObjects, int timeOut_ms){

        int attempts = timeOut_ms / 100;
        sensor_msgs::Image img_msg;
        ros::Rate loop(10);
        vision_msgs::VisionObject yoloObject;
        recognizedYoloObjects.clear();  
        
        img_msg=TakeshiVision::getArmImage();
        
        for(int i=0; i<5; i++) {
        //we have a problem with the darknetros subscriber 
            pubYoloImage.publish(img_msg);
            ros::spinOnce();
            loop.sleep();
        }
        
        yoloBoundingBoxesRecived=false;
        //wait for the response of darknet-ros        
        while(ros::ok() && !yoloBoundingBoxesRecived && --attempts > 0) {
                ros::spinOnce();
                loop.sleep();
        }

        if(yoloBoundingBoxesRecived) {
                printMessage("\n\nYolo Hand Objects: ");
                printMessage("Yolo Hand Objects detected: "+ std::to_string(lastBounding_boxes.bounding_boxes.size()));
                
                for(int i=0; i<lastBounding_boxes.bounding_boxes.size(); i++) {
                        yoloObject.id = lastBounding_boxes.bounding_boxes[i].Class;
                        yoloObject.category = getObjectCategory(yoloObject.id);
                        yoloObject.confidence = lastBounding_boxes.bounding_boxes[i].probability;
                        yoloObject.bounding_box.xmin=lastBounding_boxes.bounding_boxes[i].xmin;
                        yoloObject.bounding_box.ymin=lastBounding_boxes.bounding_boxes[i].ymin;
                        yoloObject.bounding_box.xmax=lastBounding_boxes.bounding_boxes[i].xmax;
                        yoloObject.bounding_box.ymax=lastBounding_boxes.bounding_boxes[i].ymax;            
                        recognizedYoloObjects.push_back(yoloObject);
                        printMessage("Class: " + lastBounding_boxes.bounding_boxes[i].Class + " - Confidence: " + std::to_string(lastBounding_boxes.bounding_boxes[i].probability));
                        printErrorMessage("Can not get the object 3D centroid"); 
                }
                
        }
        else{
                yoloBoundingBoxesRecived=false;  
                printErrorMessage("Can not detect yolo hand objects");   
                recognizedYoloObjects.clear(); 

        }

        return true;
}

bool callback_srvDetectAllYoloObjects(vision_msgs::Yolov3_detector::Request &req, vision_msgs::Yolov3_detector::Response &resp){
        return detect_all_yolo_objects(resp.recognizedYoloObjects,req.timeOut_ms.data,req.objectCoordinates);
}

bool callback_srvDetectAllYoloObjectsWithArmCamera(vision_msgs::Yolov3_detector::Request &req, vision_msgs::Yolov3_detector::Response &resp){
        return detect_all_yolo_objects_with_arm_camera(resp.recognizedYoloObjects,req.timeOut_ms.data);
}