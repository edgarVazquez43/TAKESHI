#include "surf_detector.h"

int main(int argc, char** argv)
{
        ros::init(argc, argv, "surf_trainer");
        ros::NodeHandle nh_priv("~");
        ros::NodeHandle nh;

        //image_transport::Subscriber image_sub=it.subscribe("image",1,&surf_trainer::surfCallBack,&sf);
        //image_transport::Publisher image_pub=it.advertise();

        std::string inFile;
        std::string configDir = ros::package::getPath("surf_recog") + "/config";
        nh_priv.param<std::string>("inFile",inFile,"/tin.xml");
        bool show_img;
        nh_priv.param<bool>("show_img",show_img, true);
        printf("File to source: %s\n", inFile.c_str() );
        std::cout << "Starting surf recognizer node" << '\n';
        std::cout << "Debug mode as :" << show_img << '\n';
        int minHessian;
        nh_priv.param<int>("minHessian",minHessian,400);
        float goodRatio;
        nh_priv.param<float>("good_ratio",goodRatio,0.8);
        int ransacTHR;
        nh_priv.param<int>("ransacTHR",ransacTHR,2);

        surf_detector sd(configDir+inFile,minHessian,goodRatio,ransacTHR,show_img);

        ros::Rate loop_rate(10);
        while(ros::ok())
        {
                loop_rate.sleep();
                ros::spinOnce();
        }


        return 0;
}
