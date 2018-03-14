#include "sp_rec/ActivateDictionaries.h"
#include "hri_msgs/RecognizedSpeech.h"
#include "hri_msgs/RecognitionResult.h"
#include "std_msgs/String.h"
#include "string.h"
#include "ros/ros.h"
#include <iostream>



class TakeshiHRI{
    public:

      static bool waitForSpecificSentence(std::vector<std::string> options, hri_msgs::RecognitionResult& recognized, int timeOut_ms);
      static int disableDictionaries(std::vector<std::string> dictionaries);
      static bool waitForSpeechHypothesis(hri_msgs::RecognitionResult& recognized_sentences, int timeOut_ms);
      static int activateDictionaries(std::vector<std::string> dictionaries);
      static void recognizedSpeech_callback(const hri_msgs::RecognitionResult msg);
      static void activateDictionaries_callback(const std_msgs::String::ConstPtr& msg);
      
      
};


