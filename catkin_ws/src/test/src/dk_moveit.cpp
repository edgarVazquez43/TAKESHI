#include <iostream>
#include "ros/ros.h"
#include <geometry_msgs/Vector3.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include "vision_msgs/DetectObjects.h"
#include "manip_msgs/DirectKinematicsFloatArray.h"

visualization_msgs::Marker endEffector_marker;
visualization_msgs::Marker centroid_marker, axis_list_marker;

bool markerSetup()
{

    centroid_marker.header.frame_id = "base_link";
    endEffector_marker.header.frame_id = "base_link";
    axis_list_marker.header.frame_id = "base_link";
    
    centroid_marker.header.stamp = ros::Time::now();
    endEffector_marker.header.stamp = ros::Time::now();
    axis_list_marker.header.stamp = ros::Time::now();

    centroid_marker.ns = "centroid";
    axis_list_marker.ns = "principal axis";
    endEffector_marker.ns = "endEffector_r";
    
    centroid_marker.pose.orientation.w = 1.0;
    endEffector_marker.pose.orientation.w = 1.0;
    axis_list_marker.pose.orientation.w = 1.0;

    centroid_marker.id = 0;
    endEffector_marker.id = 0;
    axis_list_marker.id = 1;

    centroid_marker.type = visualization_msgs::Marker::SPHERE;
    endEffector_marker.type = visualization_msgs::Marker::SPHERE;
    axis_list_marker.type = visualization_msgs::Marker::LINE_LIST;

    // POINTS markers use x and y scale for width/height respectively
    centroid_marker.scale.x = 0.035;
    centroid_marker.scale.y = 0.035;
    centroid_marker.scale.z = 0.035;

    endEffector_marker.scale.x = 0.040;
    endEffector_marker.scale.y = 0.040;
    endEffector_marker.scale.z = 0.040;

    axis_list_marker.scale.x = 0.03;
    axis_list_marker.scale.y = 0.03;
    axis_list_marker.scale.z = 0.03;

    centroid_marker.color.g = 1.0f;
    centroid_marker.color.a = 1.0;

    endEffector_marker.color.g = 1.0f;
    endEffector_marker.color.a = 1.0;

    axis_list_marker.color.r = 1.0f;
    axis_list_marker.color.a = 1.0;

    return true;
}

visualization_msgs::Marker buildMarkerAxis(geometry_msgs::Vector3 PCA_axis_0,
					   geometry_msgs::Vector3 PCA_axis_1,
					   geometry_msgs::Vector3 PCA_axis_2,
					   geometry_msgs::Pose centroid_pose)
{
    axis_list_marker.points.clear();
    geometry_msgs::Point px_centroid;
    geometry_msgs::Point p_0, p_1, p_2;

    px_centroid = centroid_pose.position;

    p_0.x = px_centroid.x + PCA_axis_0.x;
    p_0.y = px_centroid.y + PCA_axis_0.y;
    p_0.z = px_centroid.z + PCA_axis_0.z;

    p_1.x = px_centroid.x + PCA_axis_1.x;
    p_1.y = px_centroid.y + PCA_axis_1.y;
    p_1.z = px_centroid.z + PCA_axis_1.z;

    p_2.x = px_centroid.x + PCA_axis_2.x;
    p_2.y = px_centroid.y + PCA_axis_2.y;
    p_2.z = px_centroid.z + PCA_axis_2.z;

    axis_list_marker.points.push_back(px_centroid);
    axis_list_marker.points.push_back(p_0);

    axis_list_marker.points.push_back(px_centroid);
    axis_list_marker.points.push_back(p_1);

    axis_list_marker.points.push_back(px_centroid);
    axis_list_marker.points.push_back(p_2);

    return axis_list_marker;
}




int main(int argc, char** argv)
{
    std::cout << "INITIALIZING A DIRECT KINEMATIC TEST BY EDGAR-II..." << std::endl;
    ros::init(argc, argv, "DK_test_MoveIt");
    ros::NodeHandle    n;
    ros::Publisher     marker_pub;
    ros::ServiceClient cltDKinematicsArm;
    
    std::vector<float> articular;

    manip_msgs::DirectKinematicsFloatArray srv_kd;

    tf::TransformListener listener;
    tf::StampedTransform transform;

    geometry_msgs::Pose centroid, endEffector_pose;
    geometry_msgs::Vector3 axis_resp_0, axis_resp_1, axis_resp_2;

    

    cltDKinematicsArm = n.serviceClient<manip_msgs::DirectKinematicsFloatArray>("/manipulation/ik_moveit/gripper_direct_kinematics");

    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);


    // Data request to direct kinematic

    // OmniBase joints
    // articular.push_back(0.0);
    // articular.push_back(0.0);        
    // articular.push_back(0.0);
    
    articular.push_back(0.0);
    articular.push_back(0.0);
    articular.push_back(0.0);
    articular.push_back(0.0);
    articular.push_back(0.0);
    srv_kd.request.articular_pose.data = articular;

    markerSetup();

    ros::Rate loop(10);

    while(ros::ok())
    {
      
        if(!cltDKinematicsArm.call(srv_kd))
        {
            std::cout << std::endl <<
	      "Justina::Manip can't calling inverse kinematics service" << std::endl << std::endl;
            return false;
        }
        else
        {
            std::cout << "DirectKinematics.-> Calculated cartesian...." << std::endl;
	    std::cout << "[x, y, z, roll, pitch, yaw]" << std::endl;
	    for (int i=0; i < srv_kd.response.cartesian_pose.data.size(); i++)
	      std::cout << "   " << srv_kd.response.cartesian_pose.data[i] << std::endl;

	    // Response data is already respect to base_link frame
	    endEffector_pose.position.x = srv_kd.response.cartesian_pose.data[0];
            endEffector_pose.position.y = srv_kd.response.cartesian_pose.data[1];
            endEffector_pose.position.z = srv_kd.response.cartesian_pose.data[2];
	    
        }

    	endEffector_marker.pose.position = endEffector_pose.position;
        marker_pub.publish(endEffector_marker);

        std::cout << "---------------------------" << std::endl;
        ros::spinOnce();
        loop.sleep();
    }
    return 0;
}
