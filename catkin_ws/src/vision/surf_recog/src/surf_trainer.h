#include <ros/ros.h>
#include <ros/package.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencv2/xfeatures2d.hpp"


static const std::string OPENCV_WINDOW = "Train window";

class surf_trainer
{
ros::NodeHandle nh_;
image_transport::ImageTransport it_;
image_transport::Subscriber image_sub_;
image_transport::Publisher image_pub_;
cv::Mat image;
std::vector<cv::Point> roi_corners;
int counter; //for corner

int minHessian;
std::string filename;
cv::Mat descriptors;
std::vector<cv::KeyPoint> keypoints;


public:
surf_trainer();
surf_trainer(std::string file,int minHessian);
~surf_trainer();
void surfCallBack(const sensor_msgs::ImageConstPtr& msg);
void surfConverter(const sensor_msgs::ImageConstPtr& msg);
void surf_extractor();
static void onClick(int event, int x, int y, int, void* ptr);
void set_ROI_points( int x, int y);
void save_keypoints();


};
