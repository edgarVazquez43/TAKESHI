#include "pg_segmentation/pg_segmentation.h"



int main(int argc, char** argv)
{
        ros::init(argc, argv, "surf_trainer");
        ros::NodeHandle nh_priv("~");
        ros::NodeHandle nh;
        pgSegmentation pg(nh,true);
        ros::Rate loop_rate(10);
        while(ros::ok())
        {
                loop_rate.sleep();
                ros::spinOnce();
        }
        return 0;
}
