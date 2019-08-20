#pragma once
//You could also define include guards
#include "ros/ros.h"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "env_msgs/AddUpdateObjectViz.h"
#include "knowledge_msgs/AddUpdateKnownLoc.h"
#include "knowledge_msgs/KnownLocations.h"
#include "knowledge_msgs/GetPredefinedQuestions.h"
#include "knowledge_msgs/IsPointInKnownArea.h"

#include "tf/transform_listener.h"
#include <boost/algorithm/string/replace.hpp>



typedef struct _loc3D {
        std::string name;
        double height;
}loc3D;

typedef std::vector<float> joints;

class TakeshiKnowledge {
 private:
  ros::NodeHandle * nh;
  static bool is_node_set;
  static bool is_stopped;
  static bool updateKnownLoc;
  static bool initKnownLoc;

  static ros::Subscriber subStopButton;
  static ros::ServiceClient * cliKnownLoc;
  static ros::ServiceClient * cliAddUpKnownLoc;
  static ros::Subscriber * subUpdateKnowmLoc;
  static ros::Subscriber * subInitKnowmLoc;
  static ros::Publisher * pubEnableEdit;
  static ros::Publisher * pubLoadFromFile;
  static ros::Publisher * pubDeleteKnownLoc;
  static ros::Publisher * pubSaveInFile;
  static ros::ServiceClient * cliGetPredQues;
  static ros::ServiceClient * cliGetPredLaArmPose;
  static ros::ServiceClient * cliGetPredRaArmPose;
  static ros::ServiceClient * cliAddUpdateObjectViz;
  static ros::ServiceClient * cliIsInArea;
  static tf::TransformListener* tf_listener;

 private:
  static void callBackUpdateKnownLoc(const std_msgs::Bool::ConstPtr updateKnownLoc);
  static void callBackInitKnownLoc(const std_msgs::Bool::ConstPtr initKnownLoc);
                                                                                          

 public:
  ~TakeshiKnowledge();
  static bool setNodeHandle(ros::NodeHandle * nh);
  static void addUpdateKnownLoc(std::string name);
  static void addUpdateKnownLoc(std::string name, float ori);
  static void addUpdateKnownLoc(std::string name, float x, float y);
  static void addUpdateKnownLoc(std::string name, float x, float y, float th);
  static void deleteKnownLoc(const std::string name);
  static void loadFromFile(const std::string filePath);
  static void getRobotPose(float &currentX, float &currentY, float &currentTheta);
  static bool existKnownLocation(std::string location);
  static void getUpdateKnownLoc(bool& updateKnownLoc);
  static void getInitKnownLoc(bool& initKnownLoc);
  static void enableInteractiveUpdate(bool enable);
  static void getKnownLocations(std::map<std::string, std::vector<float> >& locations);
  static void getPredQuestions(std::map<std::string, std::string> &predQues);
  static void getPredQuestions(std::vector<std::string> &questions);
  static bool comparePredQuestion(std::string question, std::string &answer);
  static void addUpdateObjectViz(std::string id, float minX, float minY, float minZ,
				 float maxX, float maxY, float maxZ, float centroidX,
				 float centroidY, float centroidZ, float colorR, float colorG,
				 float colorB, std::string frame_original,
				 std::string frame_goal);
  static bool saveObjToLTM(std::string name,std::string path, float x, float y,float th);
  static bool saveObjToLTM(std::string name,  float x, float y, float theta);
  static bool getKnownObjectsLocation(std::map<std::string, std::vector<float> >& locations);
  static bool getKnownObjectsLocationFromFile(std::string pth,std::map<std::string, std::vector<float> >& locations);
  static bool getKnownObjectsLocationFromFile(std::string pth,std::map<std::string, std::string >& locations);
  static void saveNameUnknownObject(std::string objectName, std::string objectPath);
  static bool loadNameUnknownObject(std::string& objectName, std::string objectPath);
  static bool getKnownObjectsLocationFromFile(std::string pth,std::map<std::string, loc3D >& locations);
  static bool getKnownPosesFromFile( std::string pth,std::map<std::string, joints >& poses);
  static void saveInFile(const std::string filePath);
  static void addUpdateKnownLoc(std::string name, std::vector<float> values); 
  static bool isPointInKnownArea(float x, float y, std::string location);
  static void getKnownLocation(std::string location, float &x, float &y, float &a);

 private:
  static void callbackStop_AndSaveLocation(const std_msgs::Bool::ConstPtr& msg);
};
