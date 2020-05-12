#include <std_msgs/Float32MultiArray.h>
#include <ros/ros.h>
#include <sstream>
#include <string>
#include <sensor_msgs/Image.h>

sensor_msgs::Image arm_camera_image;

void printHardwareMessage(std::string message){std::cout << "\033[1;90m     Hardware.->"<< message <<"\033[0m" << std::endl;}

void printHardwareError(std::string message){std::cout << "\033[1;31m     Hardware.->"<< message <<"\033[0m" << std::endl;}

void arm_camera_callback(const sensor_msgs::Image::ConstPtr& arm_camera_msg){
    arm_camera_image = *arm_camera_msg; 
}

int main(int argc, char **argv){
        printHardwareMessage("--------------------->");
        printHardwareMessage("INITIALIZING ARM_CAMERA_NODE BY EDD-I");
        ros::init(argc, argv, "arm_camera_node");
        
        ros::NodeHandle nh;
        ros::Rate loop(30);

        ros::Subscriber subArmCamera;
        ros::Publisher pubArmCamera;

        subArmCamera = nh.subscribe("/hsrb/hand_camera/image_raw", 1, arm_camera_callback);
        pubArmCamera = nh.advertise<sensor_msgs::Image>("/hardware/arm/arm_camera",1);

        while(ros::ok()){
            if(pubArmCamera.getNumSubscribers() > 0){
              pubArmCamera.publish(arm_camera_image);
            }

            ros::spinOnce();
            loop.sleep();
        }
        return 0;
}