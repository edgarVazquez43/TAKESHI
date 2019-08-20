#include "color_segmentation.h"

int main(int argc, char** argv)
{
        ros::init(argc, argv, "color_segmentation_node");
        ros::NodeHandle nh_priv("~");
        ros::NodeHandle nh;
        float termDistance,epsilon;
        int codebookSize;
        int maxIter;
        bool dbg;
        nh_priv.param<float>("term_distance",termDistance,1000);
        nh_priv.param<float>("epsilon",epsilon,1.1);
        nh_priv.param<int>("codebookSize",codebookSize,4);
        nh_priv.param<int>("maxIter",maxIter,10);
        nh_priv.param<bool>("debug",dbg,true);
        float max_dst,min_dst;
        nh_priv.param<float>("max_distance",max_dst,200);
        nh_priv.param<float>("min_distance",min_dst,100);

        //image_transport::Subscriber image_sub=it.subscribe("image",1,&surf_trainer::surfCallBack,&sf);
        //image_transport::Publisher image_pub=it.advertise();

        color_segmentation cs(termDistance,epsilon,codebookSize,maxIter,max_dst,min_dst,dbg);

        ros::Rate loop_rate(30);
        while(ros::ok())
        {
                loop_rate.sleep();
                ros::spinOnce();
        }


        return 0;
}
