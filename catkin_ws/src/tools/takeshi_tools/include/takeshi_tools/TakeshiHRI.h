#pragma once
#include "ros/ros.h"
#include "tmc_msgs/Voice.h"
#include "tmc_msgs/TalkRequestActionResult.h"
#include "tmc_msgs/TalkRequestActionGoal.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/thread/thread.hpp"
#include "std_msgs/String.h"
#include "hri_msgs/RecognizedSpeech.h"
#include "knowledge_msgs/SphinxSetFile.h"
#include "std_msgs/Bool.h"
#include "bbros_bridge/Default_ROS_BB_Bridge.h"
#include <sound_play/sound_play.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/LaserScan.h>

class TakeshiHRI{
 private:
  static bool is_node_set;
  static bool _buttonY;
  static ros::Publisher pubFakeSprRecognized;
  static ros::Publisher pubFakeSprHypothesis;   
  static ros::Publisher pubSpgSay;
  static ros::ServiceClient cltSprStatus;
  static std::string _lastRecoSpeech;
  static bool newSprRecognizedReceived;
  static std::vector<std::string> _lastSprHypothesis;
  static std::vector<float> _lastSprConfidences;
  static ros::Subscriber subSprRecognized;
  static ros::Subscriber subSprHypothesis;
  static ros::ServiceClient cltSprGrammar;
  static ros::Publisher pubSphinxGrammar;
  static ros::Publisher pubEnSphinxMic;

  static sound_play::SoundClient * sc;

  static ros::Subscriber subJoyButton;

  static bool _legsFound;
  static ros::Publisher pubLegsEnable;
  static ros::Subscriber subLegsFound;
  static ros::Publisher pubFollowStartStop;
  static ros::Subscriber subTalkRequestAction;
  static ros::Publisher pubTalkRequestGoal;
  // static ros::ServiceClient cltSpgSay;

 public:

  static bool setNodeHandle(ros::NodeHandle* nh);
  static void enableDoorIsOpen(ros::NodeHandle* nh, bool enable);
  static bool waitAfterSay(std::string strToSay, int timeout);
  static bool waitAfterSay(std::string strToSay);
  static void enableSpeechRecognized(bool enable);
  static bool waitForSpecificSentence(std::string expectedSentence, int timeOut_ms);
  static bool waitForSpecificSentence(std::vector<std::string>& options, std::string& recognized, int timeOut_ms);
  static bool waitForSpeechHypothesis(std::vector<std::string>& sentences, std::vector<float>& confidences, int timeOut_ms);
  static bool waitForSpeechRecognized(std::string& recognizedSentence, int timeOut_ms);
  static std::string lastRecogSpeech();
  static void fakeSpeechRecognized(std::string sentence);
  static void enableLegFinder(bool enable);
  static bool frontalLegsFound();
  static void startFollowHuman();
  static void stopFollowHuman();
  static bool waitForUserConfirmation(bool& confirmation, int timeOut_ms);
   static bool waitForUserSimpleConfirmation(bool& confirmation, int timeOut_ms);
  static bool say(std::string strToSay);
  //Methods for speech synthesis and recognition
  static void loadGrammarSpeechRecognized(std::string grammar);		
  static void loadJSGFGrammar(std::string grammarFile, std::string grammarName="default" );
  static void enableSphinxMic(bool enable);
  static void playSound();
  static bool initTest();
  static bool isDoorOpen();
  static bool find_in_sentence(std::string s, std::vector<std::string>& delimiters, std::string& element_finded);
  static bool find_in_sentence(std::string s, std::string delimiter);

 private:
  //Speech recog and synthesis
  static void callbackSprRecognized(const std_msgs::String::ConstPtr& msg);
  static void callbackSprHypothesis(const hri_msgs::RecognizedSpeech::ConstPtr& msg);
  static void callbackLegsFound(const std_msgs::Bool::ConstPtr& msg);
  static void callbackButton(const sensor_msgs::Joy::ConstPtr& msg);
  static void callbackDoorIsOpen(const sensor_msgs::LaserScan::ConstPtr& msg);
  static void callbackTalkRequestAction(const tmc_msgs::TalkRequestActionResult& msg);
};
