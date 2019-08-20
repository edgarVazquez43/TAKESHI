#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

const std::string win_name= "Debug Window";
class pgSegmentation
{
//Class for the P&G test, mostly a port of obj_reco_flattened
//By Abel used to recognize Ikea cutlery


private:
enum segMethod {
        METHOD_BGR,
        METHOD_HSV,
        METHOD_HLS

};
struct models {
        std::string name;
        cv::Scalar min;
        cv::Scalar max;
        float avgArea;
        segMethod mtd;
};


std::vector<models> color_models;

ros::NodeHandle nh_;
image_transport::ImageTransport it_;
image_transport::Subscriber image_sub_;

ros::Publisher point_pub;
ros::Subscriber enable_sub;
ros::Subscriber load_sub;

bool debug, enable;
cv::Mat frame;

cv::Mat segmentColor(models model,cv::Mat & bgr,cv::Mat & element);
void setObject(std::string name, segMethod nameMethodSegmentation,cv::Scalar minScalarSegmentation,
               cv::Scalar maxScalarSegmentation, float averageAreaPixels);
void loadKnowledgeBase();
void loadKnowledgeBase(int i);
void printKnowledgeBase();
void Converter(const sensor_msgs::ImageConstPtr& msg);
cv::Rect contouring(cv::Mat mask);
static bool compareContourAreas( std::vector<cv::Point> contour1, std::vector<cv::Point> contour2 );
public:
pgSegmentation(ros::NodeHandle & nodeHandle_, bool debug);
~pgSegmentation();
void callBack(const sensor_msgs::ImageConstPtr& msg);


};
