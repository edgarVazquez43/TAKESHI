#include <ros/ros.h>
#include <ros/package.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/calib3d.hpp"
#include "opencv2/xfeatures2d.hpp"

static const std::string OPENCV_WINDOW = "Recognition window";

class surf_detector
{
ros::NodeHandle nh_;
image_transport::ImageTransport it_;
image_transport::Subscriber image_sub_;

ros::Publisher point_pub;
ros::Subscriber enable_sub;
ros::Subscriber load_sub;
cv::Mat image;
std::vector<cv::Point> train_corners;
int counter; //for corner
int minHessian;
int ransacTHR;
float good_ratio;
bool enable,show_img;
std::string filename;
cv::Mat descriptors_train;
std::vector<cv::KeyPoint> keypoints_train;

cv::Mat descriptors_query;
std::vector<cv::KeyPoint> keypoints_query;

std::vector< cv::DMatch > good_matches;

cv::Mat cameraMatrix;
cv::Mat rectCoeff;

public:
surf_detector(std::string file,std::string camera_parameters,int minHessian,float goodRatio, int ransacTHR);
surf_detector(std::string file, int minHessian,float goodRatio,
              int ransacTHR,bool show_img);

void callBack(const sensor_msgs::ImageConstPtr& msg);
void enable_cb(const std_msgs::Bool& en);
void load_cb(const std_msgs::String& filename);
void Converter(const sensor_msgs::ImageConstPtr& msg);
void surf_extractor();
void locate();
void match();

// surf_trainer(std::string file);
cv::Point2f get_center(std::vector<cv::Point2f> scene_corners);
double get_area(std::vector<cv::Point2f> scene_corners);
~surf_detector();
// void surfCallBack(const sensor_msgs::ImageConstPtr& msg);
// void surfConverter(const sensor_msgs::ImageConstPtr& msg);
// void surf_extractor();
// static void onClick(int event, int x, int y, int, void* ptr);
// void set_ROI_points( int x, int y);
// void save_keypoints();


};
