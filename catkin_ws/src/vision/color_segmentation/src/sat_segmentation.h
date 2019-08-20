#include <ros/ros.h>
#include <ros/package.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW="Dbg";

class satSegmentation {
int minSat,maxSat;
bool dbg,enable;
//images
cv::Mat bgr,hsv;
//cv vars
cv::Point2f img_center;
ros::NodeHandle nh_;
ros::Subscriber en_sub;
ros::Publisher obj_publisher;
image_transport::ImageTransport it_;
image_transport::Subscriber image_sub_;

public:
satSegmentation(ros::NodeHandle nh);
~satSegmentation();
void callBack(const sensor_msgs::ImageConstPtr& msg);
void enable_cb(const std_msgs::Bool& en);
cv::Mat Convert(cv::Mat &tmp);
void Contouring(cv::Mat mask,  std::vector<cv::RotatedRect> & rotatedRects);
void drawRotatedRects(std::vector<cv::RotatedRect> &rotated);
cv::RotatedRect closestToCenter ( std::vector<cv::RotatedRect> &r );
void findClosestAndPublish(std::vector<cv::RotatedRect> &rRects);

};
