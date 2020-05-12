#include <std_msgs/Empty.h>
#include <iostream>
#include <sstream>
#include <string>
#include "opencv2/opencv.hpp"
#include "yolo_node.h"


int main(int argc, char** argv)
{
    printMessage("INITIALIZING YOLO NODE... by Edd-I");
    ros::init(argc, argv, "yolov3_detector");
    ros::NodeHandle n;  
    ros::Rate loop(10);

    srvDetectAllYoloObjects = n.advertiseService("/vision/yolov3_detector/detect_all_yolo_objects", callback_srvDetectAllYoloObjects);
    srvDetectAllYoloObjectsWithArmCamera = n.advertiseService("/vision/yolov3_detector/detect_all_yolo_objects_with_arm_camera", callback_srvDetectAllYoloObjectsWithArmCamera);
    subYoloBoundingBoxes=n.subscribe("/darknet_ros/bounding_boxes",1,&callback_darknet_ros_boundig_boxes);
    pubYoloImage = n.advertise<sensor_msgs::Image>("/yolo_input", 1);
    cltRgbdRobot = n.serviceClient<point_cloud_manager::GetRgbd>("/hardware/point_cloud_man/get_rgbd_wrt_robot");
    TakeshiTools::setNodeHandle(&n);
    TakeshiVision::setNodeHandle(&n);
    
    n.getParam("/vision/obj_reco/object_categories_file", object_categories_file);
    printMessage("Running...");

    while(ros::ok()){        
        loop.sleep();
        ros::spinOnce();
    }

    return 0;
}