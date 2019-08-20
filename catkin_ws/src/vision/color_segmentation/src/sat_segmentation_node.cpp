#include "sat_segmentation.h"

int main(int argc, char** argv)
{
        ros::init(argc, argv, "color_segmentation_node");
        ros::NodeHandle nh_priv("~");

        satSegmentation ss(nh_priv);

        ros::Rate loop_rate(30);
        while(ros::ok())
        {
                loop_rate.sleep();
                ros::spinOnce();
        }


        return 0;
}
