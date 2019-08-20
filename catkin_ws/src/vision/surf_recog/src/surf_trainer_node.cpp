#include "surf_trainer.h"

void surfConverter(const sensor_msgs::ImageConstPtr& msg)
{
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
                cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
                ROS_ERROR("cv_bridge exception: %s", e.what());
                return;
        }
        cv::Mat image=cv_ptr->image;

        cv::Ptr<cv::Feature2D> surf = cv::xfeatures2d::SURF::create();
        std::vector<cv::KeyPoint> keypoints_surf;
        surf->detect(image,keypoints_surf);
        cv::drawKeypoints(image,keypoints_surf,image);

        cv::imshow(OPENCV_WINDOW, image);
        cv::waitKey(3);
}

void set_points(int event, int x, int y, int, void*)
{
        if( event != cv::EVENT_LBUTTONDOWN )
                return;
        cv::Point loc = cv::Point(x,y);
        return;

}


int main(int argc, char** argv)
{
        ros::init(argc, argv, "surf_trainer");
        ros::NodeHandle nh_priv("~");
        ros::NodeHandle nh;

        //image_transport::Subscriber image_sub=it.subscribe("image",1,&surf_trainer::surfCallBack,&sf);
        //image_transport::Publisher image_pub=it.advertise();

        std::string outFile;
        std::string configDir = ros::package::getPath("surf_recog") + "/config/";
        nh_priv.param<std::string>("outFile",outFile,"trainer.xml");
        printf("File to outp: %s\n", outFile.c_str() );

        int minHessian;
        nh_priv.param<int>("minHessian",minHessian,400);
        std::cout << "Starting" << '\n';
        surf_trainer sf(configDir+outFile,minHessian);

        ros::Rate loop_rate(5);
        while(ros::ok())
        {
                loop_rate.sleep();
                ros::spinOnce();
        }


        return 0;
}
