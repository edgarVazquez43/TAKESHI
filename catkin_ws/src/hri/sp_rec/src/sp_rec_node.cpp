#include "sp_rec/TakeshiHRI.h"

using namespace std;

vector<string> init_dictionaries; 
hri_msgs::RecognitionResult _lastRecoSpeech;

bool newSprRecognizedReceived = false;
bool TakeshiHRI::is_node_set = false;

ros::Publisher TakeshiHRI::activate_dictionaries;
ros::Publisher TakeshiHRI::pub_recognizedSpeech;
ros::Subscriber TakeshiHRI::sub_activate_dictionaries;
ros::Subscriber TakeshiHRI::sub_voiceText;
    

void load_dictionaries(){
    init_dictionaries.push_back("julius-gpsr-en");
    init_dictionaries.push_back("followMeGrammar");
    init_dictionaries.push_back("grammar_sample");
    init_dictionaries.push_back("robozoo_grammar");
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


bool TakeshiHRI::setNodeHandle(ros::NodeHandle* nh)
{
    cout << "\033[1;32m     INITIALIZING SPEECH RECOGNITION NODE BY EDD I...\033[0m" <<endl;
    
    if(TakeshiHRI::is_node_set)
        return true;
    if(nh == 0)
        return false;

    activate_dictionaries = nh->advertise<std_msgs::String>("hri/speech_recognition/activate_dictionaries", 1000);
    pub_recognizedSpeech = nh->advertise<hri_msgs::RecognizedSpeech>("hri/speech_recognition/recognizedSpeech", 1);
    sub_activate_dictionaries = nh->subscribe("hri/speech_recognition/activate_dictionaries", 1000, &TakeshiHRI::activateDictionaries_callback);
    sub_voiceText = nh->subscribe("hsrb/voice/text",1000, &TakeshiHRI::recognizedSpeech_callback);
        
    cout << "\033[1;32m     TakeshiHRI.->Setting ros node...\033[0m" << endl;
    load_dictionaries();
    return true;
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
            cout << "\033[1;32m Active Dictionaries: " << init_dictionaries[i]<<"\033[0m" << endl;
        
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
        cout << "\033[1;32m     TakeshiHRI.->Invalid speech recog hypothesis: msg is empty\033[0m" << endl;
        return;
    }

    newSprRecognizedReceived = true;
    for(int i=0; i<msg.sentences.size();i++ ){
        cout << "\033[1;32m     TakeshiHRI.->Received recognized speech: "<<msg.scores[i]<<"  "<< msg.sentences[i] <<"\033[0m"<< endl;
    }
    cout << std::endl;
}

int main(){

}