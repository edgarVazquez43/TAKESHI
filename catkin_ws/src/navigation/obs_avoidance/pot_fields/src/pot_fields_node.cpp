#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/LaserScan.h"
#include "visualization_msgs/Marker.h"


visualization_msgs::Marker marker;
std::vector<float> Fr_array;
sensor_msgs::LaserScan laserReadings;
bool first_read=true;
std_msgs::Float32 Fr;

//constants
float Kr=5.7;
float d0=0.35;

float mean(){
	float Fr=0.0;
	for(size_t i=0; i<Fr_array.size(); i++)
	{
		Fr+=Fr_array[i];
	}
	Fr/=Fr_array.size();

	return Fr;
}


float rejective_force(){ //REPULSIVE
	for(size_t i=0; i<laserReadings.ranges.size(); i++) {
		if(laserReadings.ranges[i]>=d0) {
			Fr_array[i]=0;
		}
		else{
			Fr_array[i]=Kr*sqrt((1.0/laserReadings.ranges[i])-(1.0/d0))*(-sin(laserReadings.angle_min+(i*laserReadings.angle_increment)));
		}
		//std::cout<<"Fr_array "<<i<<" :"<<Fr_array[i]<<std::endl;
	}

	return mean();
}

void callbackLaserScan(const sensor_msgs::LaserScan::ConstPtr& msg){
	//std::cout<<"callback LaserScan"<<std::endl;
	laserReadings =*msg;

	if(first_read) {
		Fr_array.resize(laserReadings.ranges.size());
		first_read=false;
	}
	Fr.data=rejective_force();
	if(Fr.data>0) {
		marker.pose.orientation.z = 1.0;
		marker.pose.position.y = 0.225;
	}
	else{
		marker.pose.orientation.z = -1.0;
		marker.pose.position.y = -0.225;
	}
	marker.scale.x = fabs(Fr.data);
	//std::cout<<"fuerza reactiva: "<<Fr.data<<std::endl;
}

int main(int argc, char *argv[])
{
	std::cout<<"Initializing pot_fields"<<std::endl;
	ros::init(argc,argv,"pot_fields");
	ros::NodeHandle n;
	ros::Rate loop(20);
	ros::Subscriber subLaserScan = n.subscribe("/hsrb/base_scan", 1, callbackLaserScan);
	ros::Publisher visPub = n.advertise<visualization_msgs::Marker>( "/navigation/obs_avoid/pot_fields/visualization_marker/rejective_force", 1 );
	ros::Publisher potPub = n.advertise<std_msgs::Float32>( "/navigation/obs_avoid/pot_fields/rejective_force", 1 );

	//read constants from param server
	ros::NodeHandle nh_priv("~");
	nh_priv.param<float>("kr",Kr,5.7);
	nh_priv.param<float>("d0",d0,0.35);

	Fr.data=0.0;

	marker.header.frame_id = "base_link";
	marker.header.stamp = ros::Time();
	marker.ns = "navigation";
	marker.id = 0;
	marker.type = visualization_msgs::Marker::ARROW;
	marker.action = visualization_msgs::Marker::MODIFY;
	marker.color.a = 1.0; // Don't forget to set the alpha!
	marker.color.r = 0.0;
	marker.color.g = 1.0;
	marker.color.b = 0.0;
	marker.pose.position.x = 0;
	marker.pose.position.z = 0;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.w = 1.0;
	marker.scale.y = 0.1;
	marker.scale.z = 0.1;

	if (n.getParam("/navigation/pot_fields/d0", d0)) {
		ROS_INFO("Got param d0: %f", d0);
	}
	else{
		ROS_INFO("Param default d0: %f", d0);
	}



	while(ros::ok()) {
		potPub.publish(Fr);
		visPub.publish(marker);
		ros::spinOnce();
		loop.sleep();
	}
	return 0;
}
