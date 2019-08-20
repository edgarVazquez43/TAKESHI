#include "takeshi_tools/TakeshiHardware.h"

bool TakeshiHardware::is_node_set = false;

bool TakeshiHardware::stopSub = false;

//Publishers and subscribers for checking robot state
ros::Publisher TakeshiHardware::pubRobotStop;

//Publishers and subscribers for time monitor
ros::Publisher TakeshiHardware::pubInitTimeMonitor;
ros::Publisher TakeshiHardware::pubRestartTimeMonitor;
ros::Subscriber TakeshiHardware::subTasksStop;

using namespace std;


bool TakeshiHardware::setNodeHandle(ros::NodeHandle *nh)
{
        if(TakeshiHardware::is_node_set)
        {
                return true;
        }
        if(nh == 0)
        {
                return false;
        }

        cout << "\033[1;90m     TakeshiHardware.->Setting ros node...\033[0m" << endl;
        //Publishers and subscribers for checking robot state
        TakeshiHardware::pubRobotStop = nh->advertise<std_msgs::Empty>("/hardware/robot_state/stop", 1);
        //Publishers and subscribers for time monitor
        TakeshiHardware::pubInitTimeMonitor = nh->advertise<std_msgs::Int32>("/planning/start_time", 1);
        TakeshiHardware::pubRestartTimeMonitor = nh->advertise<std_msgs::Empty>("/planning/restart_time", 1);
        TakeshiHardware::subTasksStop = nh->subscribe("/planning/tasks_stop", 1, &TakeshiHardware::taskStop);

        TakeshiHardware::is_node_set = true;
        return true;
}


//Methods for operating robot state
void TakeshiHardware::stopRobot()
{
        cout << "\033[1;90m     TakeshiHardware.->Sending stop robot... \033[0m" << endl;
        std_msgs::Empty msg;
        TakeshiHardware::pubRobotStop.publish(msg);
}

void TakeshiHardware::initTimeMonitor(int timeout){
        cout << "\033[1;90m     TakeshiHardware.-> Init time monitor: " << timeout << "\033[0m" << endl;
        std_msgs::Int32 msg;
        msg.data=timeout;
        TakeshiHardware::pubInitTimeMonitor.publish(msg);
}

void TakeshiHardware::restartTime(){
        std_msgs::Empty msg;
        TakeshiHardware::stopSub=false;
        TakeshiHardware::pubRestartTimeMonitor.publish(msg);
}

bool TakeshiHardware::isTaskStop(){
        return TakeshiHardware::stopSub;
}

void TakeshiHardware::taskStop(const std_msgs::Bool::ConstPtr& msg){
        TakeshiHardware::stopSub = msg->data;
        cout << "\033[1;90m     TakeshiHardware.-> Monitor: Task Stop: " << TakeshiHardware::stopSub << "\033[0m" << endl;
}

//Methods for operating head
bool TakeshiHardware::getHeadCurrentPose(float& pan, float& tilt)
{
        std::string headTopic = "/hardware/head/current_pose";
        boost::shared_ptr<std_msgs::Float32MultiArray const> sharedArrayPtr;
        sharedArrayPtr = ros::topic::waitForMessage<std_msgs::Float32MultiArray>
                                 (headTopic, ros::Duration(1));
        if (sharedArrayPtr==NULL)
        {
                pan = 0; tilt=0;
                cout << "\033[1;34m     TakeshiHardware.->Timed Out!, failed to call " << headTopic.c_str() << "\033[0m" << endl;
                return false;
        }

        pan=sharedArrayPtr->data[0];
        tilt = sharedArrayPtr->data[1];
        return true;
}
