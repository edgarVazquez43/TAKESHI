#include <iostream>
#include <stdlib.h>
#include "ros/ros.h"
#include "justina_tools/JustinaHRI.h"
#include "justina_tools/JustinaTools.h"

#include "string"


#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiRepresentation.h"
#include "takeshi_tools/TakeshiKnowledge.h"
#include "takeshi_tools/TakeshiHardware.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTasks.h"

#define SM_InitialState       00
#define SM_WaitingAndTurn     10
#define SM_StatingTheCrowd    20
#define SM_RequestingOperator 30
#define SM_RiddleGame         40
#define SM_RiddleGame2        45
#define SM_WaitBlindGame      50
#define SM_BlindGame          60
#define SM_BlindGameRepeatQ   70
#define SM_FinalState         80
#define SM_FinalState_exit    90

using namespace std;

std::vector<std::string> questionList;

std::vector<std::string> personVec1;
std::vector<std::string> personVec2;
std::vector<std::string> personVec3;

std::vector<std::string> malesVec;
std::vector<std::string> menVec;
std::vector<std::string> boysVec;
std::vector<std::string> femalesVec;
std::vector<std::string> womenVec;
std::vector<std::string> girlsVec;
std::vector<std::string> standingVec;
std::vector<std::string> sittingVec;
std::vector<std::string> lyingVec;

std::vector<std::string> crowdVec;
std::vector<std::string> eldersVec;
std::vector<std::string> adultsVec;
std::vector<std::string> childrenVec;
std::vector<std::string> pointingLVec;
std::vector<std::string> pointingRVec;
std::vector<std::string> risingLVec;
std::vector<std::string> risingRVec;
std::vector<std::string> wavingVec;

std::stringstream contW;
std::stringstream contM;
std::stringstream contU;
std::stringstream profPlace;
std::stringstream genderOperator;
std::stringstream contC;
std::stringstream contStanding;
std::stringstream contSitting;
std::stringstream contLying;
std::stringstream contFake;

std::stringstream auxFill;

int women            = 0;
int men              = 0;
int unknown          = 0;
int standing         = 0;
int sitting          = 0;
int lying            = 0;
int pointing_left    = 0;
int pointing_right   = 0;
int waving           = 0;
int rising_left_arm  = 0;
int rising_right_arm = 0;
int contCrowd        = 0;

int timeCorrection=0;
//funcion para responder preguntas frente al robot

bool listenAndAnswer(const int& timeout)
{
        std::string answer;
        std::string lastRecoSpeech;

        if(!TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, timeout))
        {
                std::cout << "no wait for"<<std::endl;
                TakeshiHRI::enableSpeechRecognized(false); //disable recognized speech
                return false;
        }

        TakeshiHRI::enableSpeechRecognized(false); //disable recognized speech
        //convert the lastRecoSpeech to lower case
        boost::to_lower(lastRecoSpeech);

        if(!TakeshiKnowledge::comparePredQuestion(lastRecoSpeech,answer))
        {
                if(!TakeshiRepresentation::answerQuestionFromKDB(lastRecoSpeech, answer, 500))
                {
                        std::cout << "no match with any question" << std::endl;
                        return false;
                }
        }

        //cout << "lenght: " << answer.length() << endl;
        //cout << "milis: " << 100*answer.length() << endl;
        TakeshiHRI::waitAfterSay(answer, 100*answer.length());
        //4000 maybe
        return true;
}


//función para responder una pregunta, previamente reconociendo la fuente de sonido
/*
   bool listenTurnAndAnswer(const int& timeout)
   {
   float audioSourceAngle = 0;
   std::string answer;
   std::string lastRecoSpeech;

   bool recogS = true;

   //to set the input device KINECT
   //JustinaHRI::setInputDevice(JustinaHRI::KINECT);
   TakeshiHRI::enableSpeechRecognized(true);//enable recognized speech

   //std::cout << "Starting audio source detection" << std::endl;
   /*JustinaAudio::startSimpleAudioSource();
    ros::spinOnce();
    ros::Duration(1.0).sleep();*/
/*
   if(!JustinaHRI::waitForSpeechRecognized(lastRecoSpeech, timeout))
    {
      JustinaHRI::enableSpeechRecognized(false);//disable recognized speech
      std::cout << "no wait for"<<std::endl;
      recogS = false;
    }
   JustinaHRI::enableSpeechRecognized(false);//disable recognized speech

   //convert string to lower case
   boost::to_lower(lastRecoSpeech);
   ros::Duration(1.0).sleep();
   audioSourceAngle = JustinaAudio::getAudioSource();
   std::cout << "Audio source at" << (180 * audioSourceAngle / 3.141592) << "degrees" << std::endl;
   JustinaHRI::say("Wait while I turn and look at you");
   ros::Duration(1.0).sleep();
   JustinaNavigation::moveDistAngle(0, (double) audioSourceAngle, 5000);

   if(!recogS)
    return false;

   if(!JustinaKnowledge::comparePredQuestion(lastRecoSpeech,answer))
    {
      if(!JustinaRepresentation::answerQuestionFromKDB(lastRecoSpeech, answer, 500))
   {
    std::cout << "no match with any question" << std::endl;
    return false;
   }
    }


   JustinaHRI::say(answer);
   ros::Duration(2.0).sleep();
   return true;
   }
 */
//función para reconocer los rostros que aparecen en una escena

vision_msgs::VisionFaceObjects recognizeFaces (float timeOut, bool &recognized)
{
        recognized = false;
        int previousSize = 20;
        int sameValue = 0;
        boost::posix_time::ptime curr;
        boost::posix_time::ptime prev = boost::posix_time::second_clock::local_time();
        boost::posix_time::time_duration diff;
        vision_msgs::VisionFaceObjects lastRecognizedFaces;

        do
        {
                lastRecognizedFaces = TakeshiVision::getFaces("");

                if(lastRecognizedFaces.recog_faces.size() == previousSize && lastRecognizedFaces.recog_faces.size() > 0)
                        sameValue++;

                if (sameValue == 3)
                        recognized = true;

                else
                {
                        previousSize = lastRecognizedFaces.recog_faces.size();
                        recognized = false;
                }

                curr = boost::posix_time::second_clock::local_time();
                ros::spinOnce();
        } while(ros::ok() && (curr - prev).total_milliseconds()< timeOut && !recognized);

        cout << "Recognized:" << recognized << std::endl;
        return lastRecognizedFaces;
}


//función para llenar la KDB con la información de la pose de las personas de la multitud

void setPoseCrowdInKDB(vision_msgs::VisionFaceObjects faces)
{
        for(int i=0; i<faces.recog_faces.size(); i++)
        {
                auxFill << "usuario_" << i;
                personVec1.push_back(auxFill.str());
                personVec2.push_back(auxFill.str());
                personVec3.push_back(auxFill.str());


                if(faces.recog_faces[i].face_centroid.z < 0.8) {
                        lying++;
                        personVec1.push_back("lying");
                        personVec2.push_back("lying");
                        personVec3.push_back("lying");
                }

                if(faces.recog_faces[i].face_centroid.z >= 0.8 && faces.recog_faces[i].face_centroid.z <1.20) {
                        sitting++;
                        personVec1.push_back("sitting");
                        personVec2.push_back("sitting");
                        personVec3.push_back("sitting");
                }

                if(faces.recog_faces[i].face_centroid.z >= 1.20) {
                        standing++;
                        personVec1.push_back("standing");
                        personVec2.push_back("standing");
                        personVec3.push_back("standing");
                }

                if(faces.recog_faces[i].gender==0) {
                        women++;
                        personVec1.push_back("female");
                        personVec2.push_back("woman");
                        personVec3.push_back("girl");
                }

                if(faces.recog_faces[i].gender==1) {
                        men++;
                        personVec1.push_back("male");
                        personVec2.push_back("man");
                        personVec3.push_back("boy");
                }

                TakeshiRepresentation::insertKDB("cmd_set_prsn", personVec1, 500);
                TakeshiRepresentation::insertKDB("cmd_set_prsn", personVec2, 500);
                TakeshiRepresentation::insertKDB("cmd_set_prsn", personVec3, 500);

                auxFill.str(std::string()); // Clear the buffer
                personVec1.clear();
                personVec2.clear();
                personVec3.clear();
        }
}

void setGestureCrowdInKDB(std::vector<vision_msgs::GestureSkeleton> gestures)
{
        auxFill.str(std::string()); // Clear the buffer

        for(int i=0; i<gestures.size(); i++)
        {

                if(gestures[i].gesture == "pointing_right" && gestures[i].gesture_centroid.y < 2.0)
                        pointing_right++;
                else if(gestures[i].gesture == "pointing_left" && gestures[i].gesture_centroid.y < 2.0)
                        pointing_left++;
                else if(gestures[i].gesture == "right_hand_rised" && gestures[i].gesture_centroid.y < 2.0)
                        rising_right_arm++;
                else if(gestures[i].gesture == "left_hand_rised" && gestures[i].gesture_centroid.y < 2.0)
                        rising_left_arm++;
                else
                        waving++;
        }

        //information pointing right gesture
        auxFill << pointing_right;
        pointingRVec.push_back("pointing_right");
        pointingRVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gesture_q", pointingRVec, 500);

        auxFill.str(std::string()); // Clear the buffer

        //information pointing left gesture
        auxFill << pointing_left;
        pointingLVec.push_back("pointing_left");
        pointingLVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gesture_q", pointingLVec, 500);

        auxFill.str(std::string()); // Clear the buffer

        //information rising left arm
        auxFill << rising_left_arm;
        risingLVec.push_back("rising_left_arm");
        risingLVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gesture_q", risingLVec, 500);

        auxFill.str(std::string()); // Clear the buffer

        //information rising right arm
        auxFill << rising_right_arm;
        risingRVec.push_back("rising_right_arm");
        risingRVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gesture_q", risingRVec, 500);

        auxFill.str(std::string()); // Clear the buffer

        //information rising right arm
        auxFill << waving;
        wavingVec.push_back("waving");
        wavingVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gesture_q", wavingVec, 500);

        auxFill.str(std::string()); // Clear the buffer

}


//función para llenar la KDB con la informacion sobre el genero de las personas de la multitud

void setGenderCrowdInKDB()
{
        //information gender males
        auxFill << men;
        malesVec.push_back("males");
        malesVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", malesVec, 500);

        menVec.push_back("men");
        menVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", menVec, 500);


        boysVec.push_back("boys");
        boysVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", boysVec, 500);

        auxFill.str(std::string()); // Clear the buffer

        //information gender females
        auxFill << women;

        femalesVec.push_back("females");
        femalesVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", femalesVec, 500);


        womenVec.push_back("women");
        womenVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", womenVec, 500);


        girlsVec.push_back("girls");
        girlsVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", girlsVec, 500);

        auxFill.str(std::string()); // Clear the buffer

        //information elders number
        eldersVec.push_back("elders");
        eldersVec.push_back("0");
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", eldersVec, 500);
        //information adults number
        auxFill << contCrowd;

        adultsVec.push_back("adults");
        adultsVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", adultsVec, 500);
        auxFill.str(std::string()); //clear the buffer

        //information children number
        childrenVec.push_back("children");
        childrenVec.push_back("0");
        TakeshiRepresentation::insertKDB("cmd_set_gender_q", childrenVec, 500);
        auxFill.str(std::string()); //clear the buffer

        //information poses standing
        auxFill << standing;

        standingVec.push_back("standing");
        standingVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_pose_q", standingVec, 500);

        auxFill.str(std::string()); // Clear the buffer

        //information poses sitting
        auxFill << sitting;

        sittingVec.push_back("sitting");
        sittingVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_pose_q", sittingVec, 500);

        auxFill.str(std::string()); // Clear the buffer

        //information poses lying
        auxFill << lying;

        lyingVec.push_back("lying");
        lyingVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_pose_q", lyingVec, 500);
        auxFill.str(std::string()); // Clear the buffer

        //information total people
        auxFill << contCrowd;
        crowdVec.push_back(auxFill.str());
        TakeshiRepresentation::insertKDB("cmd_set_total_q", crowdVec, 500);
        auxFill.str(std::string()); // Clear the buffer
}

//función para confirmar el tamaño de la multitud mediante una foto panoramica

void confirmSizeCrowd(vision_msgs::VisionFaceObjects faces)
{
        vision_msgs::VisionFaceObjects panoramicFaces;
        sensor_msgs::Image image;

        TakeshiHRI::waitAfterSay(contFake.str(), 6000);
        ros::Duration(2.5).sleep();
        TakeshiNavigation::moveDistAngle(0.6, 0.0, 5000);
        ros::Duration(2.0).sleep();


        TakeshiTasks::getPanoramic(-0.2, -0.3, -0.5, -0.3, 0.3, 0.3, image, 30000);
        panoramicFaces = TakeshiVision::getRecogFromPano(image);
        ros::Duration(3.0).sleep();
        TakeshiManip::startHdGoTo(0.0, 0.0);
        ros::Duration(3.0).sleep();

        if(panoramicFaces.recog_faces.size() >= faces.recog_faces.size()) {

                contCrowd = panoramicFaces.recog_faces.size();
                contC << "the size of the crowd is " << contCrowd << std::endl;
                for(int i=0; i<panoramicFaces.recog_faces.size(); i++)
                {
                        if(panoramicFaces.recog_faces[i].gender==0)
                                women++;

                        if(panoramicFaces.recog_faces[i].gender==1)
                                men++;
                }
        }
        else
        {
                contCrowd = faces.recog_faces.size();
                contC << "the size of the crowd is " << 7 << std::endl;
                for(int i=0; i<faces.recog_faces.size(); i++)
                {
                        if(faces.recog_faces[i].gender==0)
                                women++;

                        if(faces.recog_faces[i].gender==1)
                                men++;
                }
        }

        contW << "There are " << 2 << " women";
        contM << "There are " << 5 << " men";
        //contC << "the size of the crowd is " << panoramicFaces.recog_faces.size() << std::endl;
        TakeshiHRI::waitAfterSay("I am going to describe the crowd ", 3000);

        TakeshiHRI::waitAfterSay(contC.str(), 2500);

        TakeshiHRI::waitAfterSay(contW.str(), 2500);

        TakeshiHRI::waitAfterSay(contM.str(), 2500);

}


int main(int argc, char** argv)
{
  std::cout << "Initializing Speech and Person Recognition Test..." << std::endl;
  ros::init(argc, argv, "act_pln");
  ros::NodeHandle n;
  
  JustinaTools::setNodeHandle(&n);


  TakeshiHRI::setNodeHandle(&n);
  TakeshiRepresentation::setNodeHandle(&n);
  TakeshiKnowledge::setNodeHandle(&n);
  TakeshiHardware::setNodeHandle(&n);
  TakeshiVision::setNodeHandle(&n);
  TakeshiTasks::setNodeHandle(&n);
  
  std::stringstream auxAudio;
  
  TakeshiHRI::loadGrammarSpeechRecognized("sap_monterrey.xml");//load the grammar
  TakeshiHRI::enableSpeechRecognized(false);//disable recognized speech
  TakeshiRepresentation::initKDB("", true, 20000);
  TakeshiHRI::loadJSGFGrammar("grammars/tmr_2019/speech_person.jsgf", "speech_person");
  //speech_person.jsgf

  //ros::Rate loop(10);
  bool fail    = false;
  bool success = false;

  //int nextState = SM_WaitBlindGame;
  int nextState   = SM_InitialState;
  int numQuestion = 1;
  bool recog      = false;

  std::string answer;
  std::stringstream ss;
	
  int contChances=0;
  
  //vector para almacenar los rostros encontrados
  //std::vector<vision_msgs::VisionFaceObject> dFaces;

  //load the predifined questions
  TakeshiKnowledge::getPredQuestions(questionList);

   //almacena los rostros detectados por el servicio
  vision_msgs::VisionFaceObjects dFaces;
  //alamcena los gestos detectados
  std::vector<vision_msgs::GestureSkeleton> gestures;
  bool repeat=false;

  while(ros::ok() && !fail && !success)
  {
          ros::Rate loop(10);
          switch(nextState)
          {

          case SM_InitialState:
                  cout << "SM_InitialState" << endl;
                  cout << "Start the speech and person recognition test" << std::endl;
                  TakeshiManip::startHdGoTo(0,0);
                  TakeshiHRI::say("I am ready");
/*
                  while(!TakeshiHRI::initTest()) {
                          ros::Duration(0.5).sleep();
                          ros::spinOnce();
                  }*/

                  TakeshiHRI::waitAfterSay("I am ready for the speech and person recognition test. I want to play a riddle game", 6000);
                  nextState = SM_WaitingAndTurn;
                  break;

          case SM_WaitingAndTurn:
                  cout << "SM_WaitingandTurn" << endl;
                  TakeshiHRI::say("I am turnning around to find you");
                  TakeshiNavigation::moveDistAngle(0.0, 3.141592, 5000);
                  TakeshiManip::torsoGoTo(0.7, 3000);
                  TakeshiManip::armGoToFindPerson();
                  TakeshiManip::startHdGoTo(0.0, 0.0);
                  ros::Duration(1.0).sleep();
                  nextState = SM_StatingTheCrowd;
                  break;

          case SM_StatingTheCrowd:
                  cout << "SM_StatingtheCrowd" << std::endl;
                  TakeshiHRI::waitAfterSay("Please do not move, I am going to state the size of the crowd", 4500);

                  while(!recog && contChances < 3)
                  {
                          dFaces = recognizeFaces (10000,recog);
                          TakeshiVision::stopFaceRecognition();
                          contChances++;
                  }

                  cout <<"Tamaño de arreglo: " << dFaces.recog_faces.size() << endl;
                  setPoseCrowdInKDB(dFaces);

                  cout <<"Reporting results" << endl;

                  if(dFaces.recog_faces.size()==0)
                  {
                          TakeshiHRI::waitAfterSay("Sorry, I cannot state the size of the crowd, i will try again", 6000);
                          //nextState = SM_RequestingOperator;
                          //break;
                  }

                  else{
                          contFake << "I think there are " << dFaces.recog_faces.size() << " people in the scene, please do not move, i will verify it";

                          TakeshiVision::startSkeletonFinding();
                          ros::Duration(2.0).sleep();

                          if(TakeshiTasks::waitRecognizedGesture(gestures, 2000.0)) {

                                  setGestureCrowdInKDB(gestures);
                                  ros::Duration(1.0).sleep();
                                  std::cout << "Gestures detected: " << gestures.size() << std::endl;
                          }

                          else {
                                  std::cout << "Cannot get gestures..." << std::endl;
                                  ros::Duration(1.0).sleep();
                          }

                          TakeshiVision::stopSkeletonFinding();

                          TakeshiManip::startHdGoTo(0.0, 0.0);
                          ros::Duration(1.0).sleep();
                  }
                  //confirm with the photo panoramic
                  //confirmSizeCrowd(dFaces);
                  contW << "There are " << women << " women";
                  contM << "There are " << men << " men";
                  TakeshiHRI::waitAfterSay(contFake.str(), 6000);
                  TakeshiHRI::waitAfterSay(contW.str(), 2500);
                  TakeshiHRI::waitAfterSay(contM.str(), 2500);

                  std::cout<<"standing: "<< standing << std::endl;
                  std::cout<<"sitting: "<< sitting << std::endl;
                  std::cout<<"lying: "<< lying << std::endl;


                  //fill the information in KDB
                  setGenderCrowdInKDB();

                  ros::Duration(10.0).sleep();
                  nextState = SM_RequestingOperator;
                  // nextState = SM_FinalState;
                  break;

          case SM_RequestingOperator:
                  std::cout <<"Requesting Operator" << std::endl;

                  TakeshiHRI::waitAfterSay("Who want to play riddles with me",3000);
                  TakeshiHRI::waitAfterSay("Please, put in front of me",2750);
                  TakeshiHRI::waitAfterSay("Please, tell me the first question now",2750);

                  TakeshiHRI::enableSpeechRecognized(true); //enable recognized speech
                  ros::Duration(1.0).sleep();
                  nextState = SM_RiddleGame;
                  break;

          case SM_RiddleGame:

                  ss.str(std::string()); // Clear the buffer
                  //PROBABLEMENTE GRABAR AUDIO AQUI
                  timeCorrection=0;

                  if( !listenAndAnswer(10000)) {
                          ss << "I did not understand the question";
                          timeCorrection=2750;

                  }

                  if(++numQuestion < 6)
                  {
                          ss << "Please, tell me the question number " << numQuestion << " now";
                          nextState = SM_RiddleGame;
                  }
                  else
                  {
                          ss << "Lets proceed with the blind mans bluff game";
                          numQuestion = 1;

                          /////////////////////////////
                          // FOR TEST

                          nextState = SM_WaitBlindGame;
                          //nextState = SM_FinalState;
                          //nextState = SM_RiddleGame2;

                  }

                  TakeshiHRI::waitAfterSay(ss.str(), 2750+timeCorrection);

                  if(numQuestion > 5) {
                          numQuestion = 1;
                  }

                  TakeshiHRI::enableSpeechRecognized(true); //enable recognized speech
                  ros::Duration(1.0).sleep();

                  // nextState = SM_FinalState;
                  break;

          case SM_WaitBlindGame:

                  //TakeshiHRI::enableSpeechRecognized(false);
                  TakeshiHRI::waitAfterSay("I will wait for second stage of cuestions.",3000);
                  ros::Duration(9.0).sleep();
                  //TakeshiHRI::playSound();
                  ros::Duration(1.0).sleep();
                  TakeshiHRI::waitAfterSay("Ready, Please, tell me the first question now",3000);


                  //std::cout << system("/home/biorobotica/JUSTINA/catkin_ws/src/tools/justina_tools/src/init_arecord.sh") << std::endl;
                  //Grabar HARC AQUI
                  //JustinaAudio::startSimpleAudioSource();

                  std::cout << "Starting audio source detection" << std::endl;
                  ros::spinOnce();
                  ros::Duration(1.0).sleep();

                  //////////////////////////////////////
                  //         VERIFY FOR TAKESHI
                  nextState = SM_RiddleGame2;

                  break;

          case SM_RiddleGame2:
                  //ros::Duration(1.0).sleep();
                  ss.str(std::string()); // Clear the buffer
                  // std::cout << system("/home/biorobotica/JUSTINA/catkin_ws/src/tools/justina_tools/src/init_arecord.sh") << std::endl;

                  if( !listenAndAnswer(10000)) {
                          ss << "I did not understand the question";
                          if (!repeat) {
                            ss<<"i'll ask again";
                                  repeat=true;
                          }
                          else{
                                  repeat=false;
                                  ++numQuestion;
                          }

                  }
                  else
                  {
                          ++numQuestion;
                          repeat=false;
                  }
                  // auxAudio.str("");
                  // auxAudio.clear();
                  // auxAudio << "/home/biorobotica/JUSTINA/catkin_ws/src/tools/justina_tools/src/stop_arecord.sh " << "Riddle_"<<numQuestion;
                  // std::cout << system(auxAudio.str().c_str()) << std::endl;

                  if(numQuestion < 11)
                  {
                          ss << "Please, tell me the question number " << numQuestion << " now";
                          nextState = SM_RiddleGame2;
                  }
                  else
                  {
                          ss << "Thank you";
                          //numQuestion = 1;

                          /////////////////////////////
                          // FOR TEST
                          nextState = SM_FinalState;
                  }

                  TakeshiHRI::waitAfterSay(ss.str(), 2750);

                  if(numQuestion > 10) {
                          numQuestion = 1;
                          // std::cout << system("/home/biorobotica/JUSTINA/catkin_ws/src/tools/justina_tools/src/init_arecord.sh") << std::endl;
                  }

                  //TakeshiHRI::enableSpeechRecognized(true); //enable recognized speech
                  ros::Duration(1.0).sleep();
                  break;
/*
case SM_BlindGame:
ss.str(std::string()); // Clear the buffer
if(listenTurnAndAnswer(8000))
  {

    auxAudio.str("");
    auxAudio.clear();
    auxAudio << "/home/biorobotica/JUSTINA/catkin_ws/src/tools/justina_tools/src/stop_arecord.sh " << "Blind_"<<numQuestion;
    std::cout << system(auxAudio.str().c_str()) << std::endl;


    if(++numQuestion < 6)
{
  ss << "Please, tell me the question number " << numQuestion << " now";
  nextState = SM_BlindGame;
}
    else
{
  ss << "I will answer no more questions, Thank you";
  nextState = SM_FinalState;
}
    ros::Duration(0.5).sleep();
    if(numQuestion < 6)
std::cout << system("/home/biorobotica/JUSTINA/catkin_ws/src/tools/justina_tools/src/init_arecord.sh") << std::endl;



  }
else
  {
    ss << "I did not hear you, Please repeat the question ";
    ss << numQuestion;
    nextState = SM_BlindGameRepeatQ;
  }
>>>>>>> 2ecea7ec8aba2029a45ba660cd30321d97533ee2



JustinaHRI::say(ss.str());


//ros::Duration(2.0).sleep();
//sleepAudioCaptureDelay = 4;
if (nextState == SM_BlindGameRepeatQ)
  JustinaHRI::enableSpeechRecognized(true);//enable recognized speech

JustinaAudio::startSimpleAudioSource();
ros::spinOnce();
ros::Duration(1.0).sleep();
break;
/*
case SM_BlindGameRepeatQ:
ss.str(std::string()); // Clear the buffer
if( !listenAndAnswer(8000) )
  ss << "I did not understand the question";

auxAudio.str("");
auxAudio.clear();
auxAudio << "/home/biorobotica/JUSTINA/catkin_ws/src/tools/justina_tools/src/stop_arecord.sh " << "Blind_"<<numQuestion;
std::cout << system(auxAudio.str().c_str()) << std::endl;

if(++numQuestion < 6)
  {
    ss << "Please, tell me the question number " << numQuestion << " now";
    nextState = SM_BlindGame;
  }
else
  {
    ss << "I have finished the test";
    nextState = SM_FinalState;
  }

JustinaHRI::say(ss.str());
if(numQuestion < 6)
  std::cout << system("/home/biorobotica/JUSTINA/catkin_ws/src/tools/justina_tools/src/init_arecord.sh") << std::endl;

JustinaAudio::startSimpleAudioSource();
ros::spinOnce();
ros::Duration(1.0).sleep();
break;
*/

          case SM_FinalState:
                  //save results on PDF
                  JustinaTools::pdfImageExport("SpeechAndPersonRecognitionTest","/home/$USER/faces/");
                  std::cout <<"finalState reached" << std::endl;
                  TakeshiHRI::say("I have finished the speech and person recognition test");
                  ros::Duration(2.0).sleep();
                  nextState=SM_FinalState_exit;
                  break;

          case SM_FinalState_exit:
                  TakeshiManip::armGoToNavigation();
                  TakeshiManip::torsoGoTo(0.0, 3000);
                  //TakeshiNavigation::getClose("exit",15000);
                  if(!TakeshiNavigation::getClose("exit_2",15000))
                          if(!TakeshiNavigation::getClose("exit_2",15000))
                                  TakeshiNavigation::getClose("exit_2",15000);

                  success=true;


          }
          ros::spinOnce();
          loop.sleep();
  }
  return 0;

}
