#include "handle_detector/handle_detector.h"

int main(int argc, char** argv)
{
        ros::init(argc, argv, "handle_detector");
        ros::NodeHandle nh;
        handleDetector hd(nh);
        hd.setCallback();
        ros::Rate loop_rate(1);
        while(ros::ok())
        {
                loop_rate.sleep();
                ros::spinOnce();
        }
        return 0;
}
