#include "takeshi_tools/TakeshiHRI.h"

bool TakeshiHRI::is_node_set = false;

bool TakeshiHRI::newSprRecognizedReceived = false;
std::string TakeshiHRI::_lastRecoSpeech = "";
ros::Publisher TakeshiHRI::pubSpgSay;
ros::Publisher TakeshiHRI::pubEnSphinxMic;
ros::Publisher TakeshiHRI::pubFakeSprRecognized;
ros::Publisher TakeshiHRI::pubFakeSprHypothesis;  
ros::ServiceClient TakeshiHRI::cltSprStatus;

std::vector<std::string> TakeshiHRI::_lastSprHypothesis;
std::vector<float> TakeshiHRI::_lastSprConfidences;
ros::Subscriber TakeshiHRI::subSprRecognized;
ros::Subscriber TakeshiHRI::subSprHypothesis;

ros::Publisher  TakeshiHRI::pubSphinxGrammar;
ros::ServiceClient TakeshiHRI::cltSprGrammar;
sound_play::SoundClient * TakeshiHRI::sc;

ros::Publisher TakeshiHRI::pubLegsEnable;
bool TakeshiHRI::_legsFound;
bool TakeshiHRI::_buttonY=false;

ros::Subscriber TakeshiHRI::subLegsFound;
ros::Subscriber TakeshiHRI::subJoyButton;

ros::Publisher TakeshiHRI::pubTalkRequestGoal;
ros::Subscriber TakeshiHRI::subTalkRequestAction;
bool talkRequestActionFinished=false;

ros::Subscriber subLaserScanDoor;
bool door_isopen=false;

bool legs_found_signal=false;
ros::Publisher TakeshiHRI::pubFollowStartStop;
// ros::ServiceClient JustinaHRI::cltSpgSay;

using namespace std;

bool TakeshiHRI::setNodeHandle(ros::NodeHandle* nh)
{

    if(TakeshiHRI::is_node_set)
        return true;
    if(nh == 0)
        return false;

    cout << "\033[1;32m     TakeshiHRI.->Setting ros node...\033[0m" << endl;
    
    pubFakeSprHypothesis = nh->advertise<hri_msgs::RecognizedSpeech>("/recognizedSpeech", 1);
    pubFakeSprRecognized = nh->advertise<std_msgs::String>("/hri/sp_rec/recognized", 1); 
    pubEnSphinxMic       = nh->advertise<std_msgs::Bool>("/pocketsphinx/mic",1);
    subSprHypothesis     = nh->subscribe("/recognizedSpeech", 1, &TakeshiHRI::callbackSprHypothesis);
    subSprRecognized     = nh->subscribe("/hri/sp_rec/recognized", 1, &TakeshiHRI::callbackSprRecognized);
    pubLegsEnable      = nh->advertise<std_msgs::Bool>("/hri/leg_finder/enable", 1);
    subLegsFound       = nh->subscribe("/hri/leg_finder/legs_found", 1, &TakeshiHRI::callbackLegsFound);
    pubFollowStartStop = nh->advertise<std_msgs::Bool>("/hri/human_following/start_follow", 1);
    // cltSpgSay            = nh->serviceClient<bbros_bridge::Default_ROS_BB_Bridge>("/spg_say");
    cltSprGrammar        = nh->serviceClient<bbros_bridge::Default_ROS_BB_Bridge>("/spr_grammar");
    cltSprStatus         = nh->serviceClient<bbros_bridge::Default_ROS_BB_Bridge>("/spr_status");
    pubSphinxGrammar = nh->advertise<knowledge_msgs::SphinxSetFile>("/pocketsphinx/set_jsgf",1);
    //callback joy button Y
    subJoyButton = nh->subscribe("/hardware/joy",1,&TakeshiHRI::callbackButton);
    pubSpgSay            = nh->advertise<tmc_msgs::Voice>("/talk_request", 1);
    pubTalkRequestGoal = nh->advertise<tmc_msgs::TalkRequestActionGoal>("/talk_request_action/goal",1);
    //callback for talkrequestaction
    subTalkRequestAction = nh->subscribe("/talk_request_action/result", 1, &TakeshiHRI::callbackTalkRequestAction);

    sc = new sound_play::SoundClient(*nh, "/hri/robotsound");

    TakeshiHRI::is_node_set = true;

    return true;
}

void printTakeshiMessage(std::string message){
        cout << "\033[1;32m     TakeshiHRI.->"<< message <<"\033[0m" << endl;
}

void printTakeshiError(string message){
        cout << "\033[1;31m     TakeshiHRI.->"<< message <<"\033[0m" << endl;
}
/*
bool TakeshiHRI::waitAfterSay(std::string strToSay, int timeout) {
  timeout=strToSay.size()*90;
  printTakeshiMessage("Saying: " +strToSay+ " and  wait for " +to_string(timeout) +" milliseconds");
  tmc_msgs::Voice msg_voice;
  msg_voice.queueing  = true;
  msg_voice.language  = 1;
  msg_voice.sentence = strToSay;
  pubSpgSay.publish(msg_voice);
  boost::this_thread::sleep(boost::posix_time::milliseconds(timeout));
  return true;
}
*/
bool TakeshiHRI::waitAfterSay(std::string strToSay) {
    TakeshiHRI::waitAfterSay(strToSay, 4000);
}

bool TakeshiHRI::waitAfterSay(std::string strToSay, int timeout) {
  timeout=strToSay.size()*90;
  talkRequestActionFinished=false;
  ros::Rate loop(10);
  printTakeshiMessage("Saying -> " +strToSay+ " <- and  wait for the talk request finish");
  tmc_msgs::TalkRequestActionGoal msg_voice;
  msg_voice.goal.data.queueing = true;
  msg_voice.goal.data.language  = 1;
  msg_voice.goal.data.sentence = strToSay;
  pubTalkRequestGoal.publish(msg_voice);
  while(ros::ok() && !talkRequestActionFinished){
        ros::spinOnce();
        loop.sleep();
  }
  printTakeshiMessage("Talk request action finished!");
  return true;
}

bool TakeshiHRI::say(std::string strToSay) {
  printTakeshiMessage("Saying: " +strToSay);
  tmc_msgs::Voice msg_voice;
  msg_voice.queueing  = true;
  msg_voice.language  = 1;
  msg_voice.sentence = strToSay;
  pubSpgSay.publish(msg_voice);
  return true;
}

std::string TakeshiHRI::lastRecogSpeech()
{
  return _lastRecoSpeech;
}

void TakeshiHRI::fakeSpeechRecognized(std::string sentence)
{
  std_msgs::String str;
  hri_msgs::RecognizedSpeech spr;
  str.data = sentence;
  spr.hypothesis.push_back(sentence);
  spr.confidences.push_back(0.9);
  pubFakeSprRecognized.publish(str);
  pubFakeSprHypothesis.publish(spr);
} 


void TakeshiHRI::enableSpeechRecognized(bool enable){
  printTakeshiMessage("Enable grammar: "+ enable);
  bbros_bridge::Default_ROS_BB_Bridge srv;
  if(enable)
    srv.request.parameters = "enable";
  else
    srv.request.parameters = "disable";
  srv.request.timeout = 10000;
  cltSprStatus.call(srv);
}

//Methos for speech synthesis and recognition
bool TakeshiHRI::waitForSpeechRecognized(std::string& recognizedSentence, int timeOut_ms)
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
        recognizedSentence = _lastRecoSpeech;
        return true;
    }
    else
    {
        recognizedSentence = "";
        return false;
    }
}

bool TakeshiHRI::waitForSpecificSentence(std::string expectedSentence, int timeOut_ms)
{
  std::vector<std::string> sentences;
  std::vector<float> confidences;
  if(!waitForSpeechHypothesis(sentences, confidences, timeOut_ms))
    return false;
  for(size_t i=0; i<sentences.size(); i++)
    if(expectedSentence.compare(sentences[i]) == 0)
      return true;
  return false;
}

bool TakeshiHRI::waitForSpecificSentence(std::vector<std::string>& options, std::string& recognized, int timeOut_ms)
{
  std::vector<std::string> sentences;
  std::vector<float> confidences;
  if(!waitForSpeechHypothesis(sentences, confidences, timeOut_ms))
    return false;
  for(size_t i=0; i<sentences.size(); i++)
    for(size_t j=0; j<options.size(); j++)
      if(options[j].compare(sentences[i]) == 0)
  {
    recognized = sentences[i];
    return true;
  }
  return false;
}

bool TakeshiHRI::waitForSpeechHypothesis(std::vector<std::string>& sentences, std::vector<float>& confidences, int timeOut_ms)
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
      sentences = _lastSprHypothesis;
      confidences = _lastSprConfidences;
      return true;
    }
  else
    {
      sentences.clear();
      confidences.clear();
      return false;
    }
}

void TakeshiHRI::playSound()
{
  printTakeshiMessage("Playing sound!");
  sound_play::Sound sound = sc->waveSoundFromPkg("knowledge", "sounds/R2D2a.wav");
  sound.play();
  sleep(3.0);
  sound.stop();
}

void TakeshiHRI::callbackSprRecognized(const std_msgs::String::ConstPtr& msg)
{
  _lastRecoSpeech = msg->data;
  newSprRecognizedReceived = true;
  cout << "\033[1;32m     TakeshiHRI.->Received recognized speech: " << msg->data << "\033[0m"<< endl;
}

void TakeshiHRI::callbackSprHypothesis(const hri_msgs::RecognizedSpeech::ConstPtr& msg)
{
  if(msg->hypothesis.size() < 1 || msg->confidences.size() < 1)
    {
      cout << "\033[1;32m     TakeshiHRI.->Invalid speech recog hypothesis: msg is empty\033[0m"<< endl;
      return;
    }
  _lastRecoSpeech = msg->hypothesis[0];
  _lastSprHypothesis = msg->hypothesis;
  _lastSprConfidences = msg->confidences;
  cout << "\033[1;32m     TakeshiHRI.->Last reco speech: " << _lastRecoSpeech << "\033[0m"<< endl;
  newSprRecognizedReceived = true;
}

void TakeshiHRI::enableLegFinder(bool enable)
{
  if(!enable)
    {
      TakeshiHRI::_legsFound = false;
      cout << "\033[1;32m     TakeshiHRI.->Leg_finder disabled. \033[0m"<< endl;
    }
  else
     cout << "\033[1;32m     TakeshiHRI.->Leg_finder enabled.\033[0m"<< endl;
  std_msgs::Bool msg;
  msg.data = enable;
  TakeshiHRI::pubLegsEnable.publish(msg);
}

void TakeshiHRI::callbackLegsFound(const std_msgs::Bool::ConstPtr& msg)
{
  TakeshiHRI::_legsFound = msg->data;
  if(TakeshiHRI::_legsFound && legs_found_signal){
     cout << "\033[1;32m     TakeshiHRI.->Legs found: Yes\033[0m"<< std::endl;
     legs_found_signal=false;
  }
  if(!legs_found_signal && !TakeshiHRI::_legsFound){
         cout << "\033[1;32m     TakeshiHRI.->Legs found: No\033[0m"<< std::endl;
         legs_found_signal=true;
  }
}

bool TakeshiHRI::frontalLegsFound()
{
  //cout << "\033[1;32m     TakeshiHRI.->Frontal Legs found!\033[0m"<< std::endl;
  return TakeshiHRI::_legsFound;
}

void TakeshiHRI::startFollowHuman()
{
  std_msgs::Bool msg;
  msg.data = true;
  TakeshiHRI::pubFollowStartStop.publish(msg);
}

void TakeshiHRI::stopFollowHuman()
{
  std_msgs::Bool msg;
  msg.data = false;
  TakeshiHRI::pubFollowStartStop.publish(msg);
}

bool TakeshiHRI::waitForUserConfirmation(bool& confirmation, int timeOut_ms)
{
  std::vector<std::string> sentences;
  std::vector<float> confidences;
  //TakeshiHRI::loadGrammarSpeechRecognized("tokio_takeshi_confirm.xml");
  TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/confirmation.jsgf","takeshi_confirmation");
  if(!TakeshiHRI::waitForSpeechHypothesis(sentences, confidences, timeOut_ms))
    return false;
  for(size_t i=0; i<sentences.size(); i++){
      if(sentences[i].compare("takeshi yes") == 0){
        confirmation = true;
        return true;
      }
      if(sentences[i].compare("takeshi no") == 0){
        confirmation = false;
        return true;
      }
  }
  return false;
}

bool TakeshiHRI::waitForUserSimpleConfirmation(bool& confirmation, int timeOut_ms)
{
  std::vector<std::string> sentences;
  std::vector<float> confidences;
  //TakeshiHRI::loadGrammarSpeechRecognized("tokio_takeshi_confirm.xml");
  TakeshiHRI::loadJSGFGrammar("grammars/pre_sydney/hand_me_that_grammar.jsgf","takeshi_confirmation");
  if(!TakeshiHRI::waitForSpeechHypothesis(sentences, confidences, timeOut_ms))
    return false;
  for(size_t i=0; i<sentences.size(); i++){
      if(sentences[i].compare("yes") == 0){
        confirmation = true;
        return true;
      }
      if(sentences[i].compare("no") == 0){
        confirmation = false;
        return true;
      }
  }
  return false;
}

void TakeshiHRI::loadGrammarSpeechRecognized(std::string grammar){
  cout << "\033[1;32m     TakeshiHRI.->Load grammar SPR: " << grammar << "\033[0m"<< endl;
  bbros_bridge::Default_ROS_BB_Bridge srv;
  srv.request.parameters = grammar;
  srv.request.timeout = 10000;
  cltSprGrammar.call(srv);
}

void TakeshiHRI::loadJSGFGrammar(std::string grammarFile,  std::string grammarName){
  //Loads a jsgf grammar file to cmusphinx, you shoudl really add
  //a grammarName but it also has a default name
  cout << "\033[1;32m     TakeshiHRI.->Load grammar JSGF File: " << grammarFile << "\033[0m"<< endl;
  cout << "\033[1;32m     TakeshiHRI.->Load grammar Name: " << grammarName << "\033[0m"<< endl;

  knowledge_msgs::SphinxSetFile msg;
  msg.id = grammarName;
  msg.file_path = grammarFile;
  pubSphinxGrammar.publish(msg);
  return;
}

void TakeshiHRI::enableSphinxMic(bool enable){
  
  std_msgs::Bool msg;
  msg.data=enable;
  pubEnSphinxMic.publish(msg);
  
  if(enable)
    cout << "\033[1;32m     TakeshiHRI.->Enable Mic" << "\033[0m"<< endl;
  else
    cout << "\033[1;32m     TakeshiHRI.->Disable Mic"<< "\033[0m"<< endl;

}

bool TakeshiHRI::initTest(){
    return _buttonY;
}

void TakeshiHRI::callbackButton(const sensor_msgs::Joy::ConstPtr& msg)
{
    if(msg->buttons[3]==1)
        _buttonY=true;
    else
        _buttonY=false;
}

void TakeshiHRI::callbackDoorIsOpen(const sensor_msgs::LaserScan::ConstPtr& msg){
    int range=0,range_i=0,range_f=0,range_c=0,cont_laser=0;
    float laser_l=0;

    range=msg->ranges.size();
    range_c=range/2;
    range_i=range_c-(range/10);
    range_f=range_c+(range/10);
    std::cout<<"Range Size: "<< range << "\n ";
    std::cout<<"Range Central: "<< range_c << "\n ";
    std::cout<<"Range Initial: "<< range_i << "\n ";
    std::cout<<"Range Final: "<< range_f << "\n ";

    cont_laser=0;
    laser_l=0;
    for(int i=range_c-(range/10); i < range_c+(range/10); i++)
    {
        if(msg->ranges[i] > 0 && msg->ranges[i] < 4){
            laser_l=laser_l+msg->ranges[i];
            cont_laser++;
        }
    }
    std::cout<<"Laser promedio: "<< laser_l/cont_laser << std::endl;
    if(laser_l/cont_laser > 2.0){
        door_isopen=true;
    }
    else{
        door_isopen=false;
    }
}

void TakeshiHRI::enableDoorIsOpen(ros::NodeHandle* nh, bool enable){
    if(enable){
      subLaserScanDoor = nh->subscribe("/hsrb/base_scan", 1, callbackDoorIsOpen);
      door_isopen=false;
      }

    else
    {
      subLaserScanDoor.shutdown();
    }
}

bool TakeshiHRI::isDoorOpen(){
   return door_isopen;
}

bool TakeshiHRI::find_in_sentence(std::string s, std::vector<std::string>& delimiters, std::string& element_finded){
    int prev_len=0;
    size_t pos = 0;
    std::string token;

    for(size_t i=0;i<delimiters.size();i++){
        while ((pos = s.find(delimiters[i])) != std::string::npos) {
            prev_len=s.length();
            token = s.substr(0, pos);
            //std::cout << token << std::endl;
            s.erase(0, pos + delimiters[i].length());
            if(s.length()<prev_len){
              element_finded=delimiters[i];
              return true;
            }
        }
    }
    element_finded="";
    return false;
}

void TakeshiHRI::callbackTalkRequestAction(const tmc_msgs::TalkRequestActionResult& msg){
  talkRequestActionFinished=true;
}

bool TakeshiHRI::find_in_sentence(std::string s, std::string delimiter){
    int prev_len=0;
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
      prev_len=s.length();
      token = s.substr(0, pos);
      //std::cout << token << std::endl;
      s.erase(0, pos + delimiter.length());
      if(s.length()<prev_len){
        return true;
      }
    }
    return false;
}
