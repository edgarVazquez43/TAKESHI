#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "ros/ros.h"
#include "std_msgs/Header.h"
#include "std_msgs/Bool.h"
#include <geometry_msgs/Pose2D.h>

//#include "vision_msgs/GetSkeleton.h"
#include "vision_msgs/Skeleton.h"
#include "vision_msgs/Skeletons.h"
#include "vision_msgs/SkeletonJoint.h"
#include "vision_msgs/VisionObject.h"
#include "tf/transform_listener.h"
#include "tf/transform_datatypes.h"
//#include <interactive_cleanup/InteractiveCleanupMsg.h>

//#include "takeshi_tools/TakeshiKnowledge.h"
typedef struct _locPose {
        float x,y,z,th;
}locPose;

class interactiveCleaner {
private:

ros::NodeHandle nh_;
ros::Publisher skeleton_enable,msgPublisher,followerEnable;
ros::Subscriber msgSubscriber;
ros::ServiceClient skel_client;
std_msgs::Header skelHeader;
tf::TransformListener tlistener;
tf::Stamped<tf::Vector3> wrist,elbow; //the arm
std::map<std::string,geometry_msgs::Point>  locations;
float angleAdjustment, distanceAdjustment, armAngleValid;

bool loadKnownLocations(std::string path);
double euclideanDistance(vision_msgs::Skeleton person);
double distanceToArm(
        std::vector<geometry_msgs::PointStamped>  &armOnMap,
        geometry_msgs::Point gp0);
double distanceToArmLoc(
        std::vector<geometry_msgs::PointStamped>  &armOnMap,
        geometry_msgs::Point gp0);
geometry_msgs::Point makePoint(float x, float y, float z);
//void messageCallback(const interactive_cleanup::InteractiveCleanupMsg::ConstPtr &msg);
//se me olvido el const
bool convertJoints(vision_msgs::SkeletonJoint joint,
                   std::string outLink,
                   geometry_msgs::PointStamped &outJointStamped);
bool convertArm(
        std::vector<vision_msgs::SkeletonJoint> &arm,
        std::vector<geometry_msgs::PointStamped> &armOnMap);

double norm(geometry_msgs::Point p);
public:
std::string receivedMessage;
interactiveCleaner(ros::NodeHandle &nh);
void sendMessage(std::string msg);
bool setKnownLocations(std::map<std::string, std::vector<float> > &locs);
void askForSkeleton();
bool returnSkeletons(vision_msgs::Skeletons &skl);
bool returnSkeletonsEnable(vision_msgs::Skeletons &skl);
bool getArmsByTopic(std::vector<vision_msgs::SkeletonJoint> &armLeft,
                    std::vector<vision_msgs::SkeletonJoint> &armRight,
                    vision_msgs::Skeleton &closestSkeleton);
bool getArmsByTopicOnMap(
        std::vector<geometry_msgs::PointStamped> &armLeftOnMap,
        std::vector<geometry_msgs::PointStamped> &armRightOnMap,
                vision_msgs::Skeleton &closestSkeleton);
std::string findPointedLocation(
        std::vector<geometry_msgs::PointStamped>  &armOnMap,
                vision_msgs::Skeleton &closestSkeleton,
                bool find_near_locations);
double angleOfArm(std::vector<geometry_msgs::PointStamped> &arm);
geometry_msgs::Point findPointedObj(
        std::vector<vision_msgs::VisionObject> objects,
        std::vector<geometry_msgs::PointStamped> &armOnMap);
geometry_msgs::Point floorIntersect(std::vector<geometry_msgs::PointStamped> &armOnMap);
bool getClose(float x, float y,float th, int timeOut_ms);
geometry_msgs::Pose2D floorLocation(std::vector<geometry_msgs::PointStamped> &armOnMap);
void enableFollower(bool enable);
void enableSkel(bool enable);
void startRoutine(bool enable);
bool validateArms(
        std::vector<geometry_msgs::PointStamped>  &armLeft,
        std::vector<geometry_msgs::PointStamped>  &armRight,
        std::vector<geometry_msgs::PointStamped> &validArm);
static void printArm(std::vector<geometry_msgs::PointStamped>  &arm);
double distance(vision_msgs::Skeleton &closestSkeleton,
    geometry_msgs::Point gp0);
double distanceXY(vision_msgs::Skeleton &closestSkeleton,
    geometry_msgs::Point gp0);
};
