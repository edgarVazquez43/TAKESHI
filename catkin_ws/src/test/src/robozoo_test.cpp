#include <iostream>
#include "ros/ros.h"
#include "hri_msgs/RecognizedSpeech.h"
#include "hri_msgs/RecognitionResult.h"
#include "sp_rec/TakeshiHRI.h"
#include "sp_rec/ActivateDictionaries.h"

using namespace std;

int main(int argc, char** argv)
{
    std::cout << "INITIALIZING ROBOZOO TEST BY EDD-I..." << std::endl;
    ros::init(argc, argv, "acl_pln");
    ros::NodeHandle    n;
    std::vector<std::string> options;
    options.push_back("robot no");
    options.push_back("follow me");
    hri_msgs::RecognitionResult recognized;
    ros::Rate loop(10);

    while(ros::ok())
    {
      	if(TakeshiHRI::waitForSpecificSentence(options, recognized, 10000))
            cout<<"Recognized Sentences: "<< recognized.scores[0] << "  " << recognized.sentences[0] << endl; 
        
        ros::spinOnce();
        loop.sleep();
    }
    return 0;
}