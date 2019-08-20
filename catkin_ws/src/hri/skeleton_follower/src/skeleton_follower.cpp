#include "skeleton_follower.h"

skeleton_follower::skeleton_follower(ros::NodeHandle &nh)
{
        nh_=nh;
        std::cout << "Starting skeleton follower by Coyo-Soft" << '\n';
        enableSubscriber = nh_.subscribe("/hri/skeleton_follower/enable",1,&skeleton_follower::enableCallback,this);
        ros::NodeHandle nh_priv("~");
        nh_priv.param<double>("setpoint_y",setpointY,0.0);
        nh_priv.param<double>("setpoint_x",setpointX,1.0);
        nh_priv.param<double>("k_y",ky,0.5);
        nh_priv.param<double>("k_x",kx,0.5);

        twistPublisher = nh_.advertise<geometry_msgs::Twist>("/hsrb/command_velocity",1);
        control_pub = nh_.advertise<trajectory_msgs::JointTrajectory>("/hsrb/arm_trajectory_controller/command", 5);

}

void skeleton_follower::enableCallback(const std_msgs::Bool &msg)
{
        if (msg.data)
        {
                std::cout << "Enabling callback" << '\n';
                skeletonSubscriber =
                        nh_.subscribe(
                                "/vision/skeleton_finder/skeleton_recog",
                                1,&skeleton_follower::skeletonCallback,this);
        }
        else
        {
                std::cout << "Disabling callback" << '\n';
                skeletonSubscriber.shutdown();
        }
}
void skeleton_follower::skeletonCallback(const vision_msgs::Skeletons &skl)
{
        std::cout << "Got skeletons: " << skl.skeletons.size()<< '\n';
        geometry_msgs::Twist controlTwist;
        if (skl.skeletons.size() <1) {
                controlTwist.linear.x = 0;
                controlTwist.angular.z = 0;
                twistPublisher.publish(controlTwist);
                return;
        }
        //Take First skeleton and the first joint
        //Found in general it is the neck
        //But anything goes here ;)
        vision_msgs::Skeleton skel = skl.skeletons[0];
        geometry_msgs::Vector3 jointToTrack = skel.joints[0].position;
        //control law
        double error_x = jointToTrack.x-setpointX;
        double error_y = jointToTrack.y-setpointY;
        controlTwist.linear.x = error_x*kx;
        //controlTwist.angular.z = error_y*ky;
        controlTwist.linear.y = error_y*ky;
          std::cout << "Control law:" << '\n';
        std::cout << "x "<<controlTwist.linear.x << '\n';
        std::cout << "y "<<controlTwist.linear.y << '\n';
        //std::cout << "z "<<controlTwist.linear.z << '\n';
        //std::cout << "theta "<<controlTwist.angular.z << '\n';
        twistPublisher.publish(controlTwist);
}

void skeleton_follower::headCtrl(double error, double kp)
{
        //get current head state and control the pan joint
        trajectory_msgs::JointTrajectory ctrl;
        ctrl.joint_names.push_back("head_pan_joint");
        ctrl.joint_names.push_back("head_tilt_joint");
        sensor_msgs::JointState headState;
        getHeadPose(headState);
        ctrl.points[0].positions.resize(2);
        ctrl.points[0].velocities.resize(2);
        ctrl.points[0].positions[0] = headState.position[0]+kp*error;
        control_pub.publish(ctrl);
}

bool skeleton_follower::getHeadPose(sensor_msgs::JointState &hdState)
{
        // hdState.name.clear();
        // hdState.position.clear();
        hdState.name.push_back("head_pan_joint");
        hdState.name.push_back("head_tilt_joint");
        hdState.position.resize(2);
        boost::shared_ptr<sensor_msgs::JointState const> sharedPtr=
                ros::topic::waitForMessage<sensor_msgs::JointState>
                        ("/hsrb/joint_states",nh_,ros::Duration(1.0));
        if (sharedPtr == NULL) {
                std::cout << "Could not get joint states message" << '\n';
                return false;
        }
        sensor_msgs::JointState fullState = *sharedPtr;
        for(int i = 0; i< fullState.name.size(); i++)
        {
                for (int k = 0; k < hdState.name.size(); k++)
                {
                        if(fullState.name[i]==hdState.name[k])
                        {

                                hdState.position[k]=fullState.position[i];
                                printf("Joint %s: %f\n", hdState.name[k].c_str(),hdState.position[k]);
                                //save values on inernal message
                        }
                }

        }
        return true;
}
