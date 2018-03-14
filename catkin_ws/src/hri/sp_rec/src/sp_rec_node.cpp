#include <iostream>
#include "ros/ros.h"
#include "sp_rec/ActivateDictionaries.h"
#include "sp_rec/TakeshiHRI.h"

using namespace std;

vector<string> init_dictionaries; 
hri_msgs::RecognitionResult _lastRecoSpeech;

bool newSprRecognizedReceived = false;


void load_dictionaries(){
    init_dictionaries.push_back("julius-gpsr-en");
    init_dictionaries.push_back("followMeGrammar");
    init_dictionaries.push_back("grammar_sample");
}

int TakeshiHRI::activateDictionaries(std::vector<std::string> dictionaries){
    ros::NodeHandle n;
    ros::ServiceClient activate_dictionaries_client = n.serviceClient<sp_rec::ActivateDictionaries>("/hsrb/voice/activate_dictionaries");
    sp_rec::ActivateDictionaries activate_dictionaries_srv;
    activate_dictionaries_srv.request.names = dictionaries;
    activate_dictionaries_srv.request.active = true;
    
    if (activate_dictionaries_client.call(activate_dictionaries_srv))
     {
       ROS_INFO("Response: %ld", (long int) activate_dictionaries_srv.response.result);
     }
    else
     {
       ROS_ERROR("Failed to call service /hsrb/voice/activate_dictionaries");
       return 1;
     }
}

int TakeshiHRI::disableDictionaries(std::vector<std::string> dictionaries){
    ros::NodeHandle n;
    ros::ServiceClient activate_dictionaries_client = n.serviceClient<sp_rec::ActivateDictionaries>("/hsrb/voice/activate_dictionaries");
    sp_rec::ActivateDictionaries activate_dictionaries_srv;
    activate_dictionaries_srv.request.names = dictionaries;
    activate_dictionaries_srv.request.active = false;
    
    if (activate_dictionaries_client.call(activate_dictionaries_srv))
     {
       ROS_INFO("Response: %ld", (long int) activate_dictionaries_srv.response.result);
     }
    else
     {
       ROS_ERROR("Failed to call service /hsrb/voice/disable_dictionaries");
       return 1;
     }
}


void TakeshiHRI::activateDictionaries_callback(const std_msgs::String::ConstPtr& msg){
    
    cout<<msg->data<<endl;
    std::vector<std::string> dictionaries;

    for(int i=0; i<init_dictionaries.size();i++ ){

        if(init_dictionaries[i].compare(msg->data) != 0)
            dictionaries.push_back(init_dictionaries[i]);
        else    
            cout << "Active Dictionaries: " << init_dictionaries[i] << endl;
        
    }
    
    disableDictionaries(dictionaries);
}

bool TakeshiHRI::waitForSpeechHypothesis(hri_msgs::RecognitionResult& recognized_sentences, int timeOut_ms)
{
    newSprRecognizedReceived = false;
    int attempts = timeOut_ms / 100;
    ros::Rate loop(10);
    while(ros::ok() && !newSprRecognizedReceived && --attempts > 0)
    {
        ros::spinOnce();
        loop.sleep();
    }
    if(newSprRecognizedReceived)
    {
        recognized_sentences = _lastRecoSpeech;
        return true;
    }
    else
    {
        recognized_sentences.sentences.clear();
        recognized_sentences.scores.clear();
        return false;
    }
}

bool TakeshiHRI::waitForSpecificSentence(std::vector<std::string> options, hri_msgs::RecognitionResult& recognized, int timeOut_ms)
{
    hri_msgs::RecognitionResult recognized_sentences;
    if(!waitForSpeechHypothesis(recognized_sentences, timeOut_ms))
        return false;
    for(size_t i=0; i<recognized_sentences.sentences.size(); i++)
        for(size_t j=0; j<options.size(); j++)
            if(options[j].compare(recognized_sentences.sentences[i]) == 0)
            {
                recognized.sentences.push_back(recognized_sentences.sentences[i]);
                recognized.scores.push_back(recognized_sentences.scores[i]);
                return true;
            }
    return false;
}

void TakeshiHRI::recognizedSpeech_callback(const hri_msgs::RecognitionResult msg)
{

    _lastRecoSpeech = msg;

    if(msg.sentences.size() < 1 || msg.scores.size() < 1)
    {
        cout << "JustinaHRI.->Invalid speech recog hypothesis: msg is empty" << endl;
        return;
    }

    newSprRecognizedReceived = true;
    for(int i=0; i<msg.sentences.size();i++ ){
        cout << "JustinaHRI.->Received recognized speech: "<<msg.scores[i]<<"  "<< msg.sentences[i] << endl;
    }
    cout << std::endl;
}



int main(int argc, char** argv){
    cout << "INITIALIZING SPEECH RECOGNITION BY EDD I..." <<endl;
    ros::init(argc, argv, "speech_recognition_client");
    ros::NodeHandle n;
    load_dictionaries();
    ros::Publisher activate_dictionaries = n.advertise<std_msgs::String>("hri/speech_recognition/activate_dictionaries", 1000);
    ros::Publisher pub_recognizedSpeech = n.advertise<hri_msgs::RecognizedSpeech>("hri/speech_recognition/recognizedSpeech", 1);
    std::vector<std::string> options;
    options.push_back("robot no");
    options.push_back("follow me");
    hri_msgs::RecognitionResult recognized;
    ros::Rate loop_rate(10);

    ros::Subscriber sub_activate_dictionaries = n.subscribe("hri/speech_recognition/activate_dictionaries", 1000, &TakeshiHRI::activateDictionaries_callback);
    ros::Subscriber sub_voiceText = n.subscribe("hsrb/voice/text",1000, &TakeshiHRI::recognizedSpeech_callback);
    //std::vector<std::string> dictionaries; 
    //dictionaries.push_back("julius-gpsr-en");
    //activateDictionaries(dictionaries);
    //disableDictionaries(dictionaries);
     while(ros::ok())
    {     
        if(TakeshiHRI::waitForSpecificSentence(options, recognized, 10000))
            cout<<"Recognized Sentences: "<< recognized.scores[0] << "  " << recognized.sentences[0] << endl; 
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
    
}