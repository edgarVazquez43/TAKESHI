#include "skeleton_follower.h"

int main(int argc, char** argv)
{
        ros::init(argc, argv, "skeleton_follower");
        ros::NodeHandle nh;
        skeleton_follower sf(nh);
        ros::Rate loop_rate(1);
        while(ros::ok())
        {
                loop_rate.sleep();
                ros::spinOnce();
        }
        return 0;
}
