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

static const std::string OPENCV_WINDOW_D = "Distance window";
static const std::string OPENCV_WINDOW_S = "Segmentation window";
class color_segmentation
{
ros::NodeHandle nh;
image_transport::ImageTransport it_;
image_transport::Subscriber image_sub_;


ros::Subscriber enable_sub;
ros::Subscriber load_sub;
cv::Mat image_lab,image_bgr;
bool enable,train,debug;

std::vector<cv::Vec3f> color_space;
std::vector<int> optimalLabels;
std::vector<cv::Vec3f> optimalCodebook;

int codebookSize;
int cacheImages, imgToUse;
int regToSegment;
unsigned int maxIter;
float epsilon, termDistance;
float max_distance, min_distance;

void toVector(const cv ::Mat &img);
void toVector(const cv ::Mat &img, std::vector<cv::Vec3f> &v );
void LBG(std::vector<cv::Vec3f> &codebook, std::vector<int> &labels);
void k_medias(std::vector<cv::Vec3f> &codebook, std::vector<int> &labels);
void printCodebook(const std::vector<cv::Vec3f> &codebook);
cv::Vec3f getCentroid(const std::vector<cv::Vec3f> &region);
cv::Mat getCentroid(const cv::Mat &region);
double getDistances(std::vector<cv::Vec3f> &codebook,
                    const std::vector<cv::Vec3f> &color_samples,
                    std::vector<std::vector<cv::Vec3f> > &regions,
                    std::vector<int> &labels);
void clearRegions(std::vector<std::vector<cv::Vec3f> > &regions);
void dropWhitesAndBlacks();
cv::Mat quantize(const cv::Mat & img,const std::vector<cv::Vec3f> codebook);
public:
color_segmentation(float termDistance, float epsilon,
                   int codebookSize,unsigned int maxIter, float mx_dst, float mn_dst,
                   bool dbg);
~color_segmentation();
void callBack(const sensor_msgs::ImageConstPtr& msg);
void enable_cb(const std_msgs::Bool& en);
void load_cb(const std_msgs::Int16& msg);
void Converter(const sensor_msgs::ImageConstPtr& msg);
cv::Mat1f getNorm(const cv::Mat3f &inputImg);
void getContours(cv::Mat &segImg,std::vector<cv::Rect> &outContours);
};
