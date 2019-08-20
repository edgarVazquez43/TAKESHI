#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Bool.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/thread/thread.hpp"

using namespace std;

bool startTimeRecived = false;
bool stopPub = false;
int timeout = 0;
boost::posix_time::ptime curr;
boost::posix_time::ptime prev;

void callbackStartTime(const std_msgs::Int32::ConstPtr& msg){
    cout << "\033[1;90m     TakeshiHardware.-> Recived start time:" << msg->data << "\033[0m" << endl;
    timeout = msg->data;
    startTimeRecived = true;
    stopPub = false;
    curr = boost::posix_time::second_clock::local_time();
    prev = curr;
}

void callbackRestartTime(const std_msgs::Empty::ConstPtr& msg){
    cout << "\033[1;90m     TakeshiHardware.-> Recived restart time\033[0m" << endl;
    cout << "\033[1;90m     TakeshiHardware.-> Monitor: Restart time: " << (curr - prev).total_milliseconds() << "\033[0m" << endl;
    stopPub = false;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "monitor");
    ros::NodeHandle n;
    ros::Rate rate(10);

    ros::Publisher pubTasksStop = n.advertise<std_msgs::Bool>("/planning/tasks_stop", 1);
    ros::Subscriber subStartTime = n.subscribe("/planning/start_time", 1, callbackStartTime);
    ros::Subscriber subRestartTime = n.subscribe("/planning/restart_time", 1, callbackRestartTime);
    cout << "\033[1;90m     TakeshiHardware.-> Monitor: Start Node\033[0m" << endl;

    while(ros::ok()){

        if(startTimeRecived){
            curr = boost::posix_time::second_clock::local_time();
            // std::cout << "monitor.->" << (curr - prev).total_milliseconds() << std::endl;
            if((curr - prev).total_milliseconds() > timeout){
                startTimeRecived = false;
                stopPub = true;
            }
        }

        if(stopPub){
            cout << "\033[1;90m     TakeshiHardware.-> Monitor: Stop Pub\033[0m" << endl;
            std_msgs::Bool msg;
            msg.data=true;
            pubTasksStop.publish(msg);
            startTimeRecived = false;
        }

        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}
