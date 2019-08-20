
#include "std_msgs/Bool.h"
#include "string"
#include "vision_msgs/FindPlane.h"


#include "ros/ros.h"
#include "takeshi_tools/TakeshiHardware.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTasks.h"
#include "takeshi_tools/TakeshiRepresentation.h"




enum state {
    SM_INIT, 
    SM_WAIT_FOR_INIT_COMMAND,
    SM_SEARCH_BAR,
    SM_SEARCH_WAVING,
    SM_WAIT_FOR_TAKE_ORDER,
    SM_CLOSE_TO_CLIENT,
    SM_ASK_FOR_NUMBER_OF_ITEMS,
    SM_WAIT_FOR_NUMBER,
    SM_ASK_FOR_ITEM,
    SM_WAIT_FOR_ITEM,
    SM_COMFIRM_ITEM,
    SM_WAIT_CONFIRMATION_ITEM,
    SM_RETURN_BAR,
    SM_ASK_FOR_ORDER_TO_BARTENDER,
    SM_GRASP_ORDER,
    SM_GOTO_ORDER_TABLE,
    SM_HANDOVER_OBJECT,
    SM_RELEASE_THE_ORDER,
    SM_WAIT_FOR_COMMAND_TO_BRING_THE_ORDER,
    SM_GO_TO_ORDER_TABLE_TO_DELIVER,
    SM_HANDOVER_OBJECT_WITH_WAITER,
    SM_RETURN_KITCHEN,     
    SM_FINISH_TEST  
};

void initialize_list(std::vector<string>& v){
    v.push_back("beer");
    v.push_back("chocolate milk");
    v.push_back("coke");
    v.push_back("juice");
    v.push_back("lemonade");
    v.push_back("tea bag");
    v.push_back("water"); 
    v.push_back("biscuit"); 
    v.push_back("frosty fruits"); 
    v.push_back("snakes"); 
    v.push_back("carrot"); 
    v.push_back("cereals"); 
    v.push_back("noodles"); 
    v.push_back("onion"); 
    v.push_back("vegemite"); 
    v.push_back("apple"); 
    v.push_back("kiwi"); 
    v.push_back("lemon"); 
    v.push_back("orange"); 
    v.push_back("pear"); 
    v.push_back("cheetos"); 
    v.push_back("doritos"); 
    v.push_back("shapes chicken"); 
    v.push_back("shapes pizza"); 
    v.push_back("twisties"); 
}

void erase_item(std::string s, std::vector<std::string>& v){
    for (size_t i=0; i<v.size(); i++){
        if(s.compare(v[i])==0){
            v.erase(v.begin()+i);
        }
    }
}

void printState(std::string st)
{
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "\033[1;35m        CASE: "<< st << "\033[0m" << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "INITIALIZING RESTAURANT TEST..." << std::endl;
    ros::init(argc, argv, "act_pln");
    ros::NodeHandle n;

    TakeshiHRI::setNodeHandle(&n);
    TakeshiHardware::setNodeHandle(&n);
    TakeshiKnowledge::setNodeHandle(&n);
    TakeshiNavigation::setNodeHandle(&n);
    TakeshiManip::setNodeHandle(&n);
    TakeshiTasks::setNodeHandle(&n);
    TakeshiTools::setNodeHandle(&n);
    TakeshiVision::setNodeHandle(&n);
    TakeshiRepresentation::setNodeHandle(&n);
   
    ros::Rate loop(10);
    
    int nextState = 0;
    bool fail     = false;
    bool success  = false;
    bool stop     = false;
    bool findGesture = false;

    std::string lastRecoSpeech;
    std::string lastInteSpeech;
    std::string object_aux;
    int timeoutspeech = 10000;

    float robot_y, robot_x, robot_a;    
    float gx_w, gy_w, gz_w;    
    float goalx, goaly, goala, angleError;    
    float dist_to_head;

    std::vector<std::string> order_items;
    
    std::stringstream ss;

    Eigen::Vector3d centroidGesture;

    bool findGestureOrAttendOrder = false;
    bool validateCombo = true;
    bool isCombo = false;
    bool userConfirmation=false;

    int attempsNavigation    = 1;
    int maxAttempsNavigation = 2;
    int attempsSpeechReco    = 1;
    int maxAttempsSpeechReco = 4;
    int attempsSpeechInt     = 1;
    int maxAttempsSpeechInt  = 2;
    int attempsWaitConfirmation    = 1;
    int maxAttempsWaitConfirmation = 3;
    int attempsConfirmation        = 1;
    int maxAttempsConfirmation     = 3;

    int length_order=0;
    int item_counter=0;
    bool grasp_succes=false;

    std::vector<vision_msgs::VisionObject> recognizedYoloObjects;  
    vision_msgs::ObjectCoordinatesForDetection objectCoordinates;
    objectCoordinates=TakeshiVision::objectCoordinates;
    objectCoordinates.x_max=1.5;

    std::string bar_search="";
    
    std::vector<std::string> tokens;
    std::vector<std::string> validitems;
    std::vector<std::string> order;

    initialize_list(validitems);
    
    std::string grammarCommands = "grammars/pre_sydney/restaurant/restaurant_commands.jsgf";
    std::string grammarOrder = "grammars/pre_sydney/restaurant/restaurant_order.jsgf";
    std::string grammarNumber = "grammars/pre_sydney/restaurant/restaurant_numbers.jsgf";
    std::vector<vision_msgs::GestureSkeleton> gestures;
    vision_msgs::GestureSkeleton gesture;

    std::vector<std::string> specificGestures;
    specificGestures.push_back("right_hand_rised");
    specificGestures.push_back("left_hand_rised");
    specificGestures.push_back("left_hand_rised");
    specificGestures.push_back("left_waving");
    specificGestures.push_back("right_waving");
    
    //TakeshiHRI::setInputDevice(TakeshiHRI::KINECT);
    //TakeshiHRI::loadGrammarSpeechRecognized(grammarCommands);//load the grammar
    TakeshiHRI::loadJSGFGrammar(grammarCommands,"restaurant");

    nextState = SM_INIT;

    while(ros::ok() && !fail && !success){
        switch(nextState){
            case SM_INIT:
                std::cout << "State machine: SM_INIT" << std::endl;	
                TakeshiManip::hdGoTo(0, 0, 2000);
                TakeshiHRI::waitAfterSay("I'm ready for the restaurant test, say takeshi start and I'll begin", 3000);
                //TakeshiHRI::enableSpeechRecognized(true);
                TakeshiHRI::enableSphinxMic(true);
                nextState = SM_WAIT_FOR_INIT_COMMAND;
                break;

            case SM_WAIT_FOR_INIT_COMMAND:
                std::cout << "State machine: SM_WAIT_FOR_INIT_COMMAND" << std::endl;
                TakeshiKnowledge::addUpdateKnownLoc("robot_init_pose", robot_a);

				if(TakeshiHRI::waitForSpecificSentence("takeshi start", timeoutspeech)){
                    //TakeshiHRI::enableSpeechRecognized(false);
                    TakeshiHRI::enableSphinxMic(false);
                    TakeshiHRI::waitAfterSay("I will look for the bar", 3500);
                    nextState = SM_SEARCH_BAR;
                }else
                    nextState = SM_WAIT_FOR_INIT_COMMAND;
                break;

            case SM_SEARCH_BAR:
                std::cout << "State machine: SM_SERACH_BAR" << std::endl;
                TakeshiTasks::findTable(bar_search);  
                // TODO delimited the table to find
                TakeshiKnowledge::getRobotPose(robot_x, robot_y, robot_a);

                if (bar_search.compare("right") == 0){
                    TakeshiHRI::waitAfterSay("I see the bar in my right side", 4000);
                    //robot_a+M_PI;
                }else if (bar_search.compare("left") == 0){
                    TakeshiHRI::waitAfterSay("I see the bar in my left side", 10000);
                }
                else{
                    std::cout << "SM_SERACH_BAR: Bar default" << std::endl;
                    TakeshiHRI::waitAfterSay("I see the bar in my left side", 10000);       
                }

                TakeshiKnowledge::addUpdateKnownLoc("kitchen_bar");
                TakeshiManip::hdGoTo(0.0, 0.0, 3000);    
                findGestureOrAttendOrder = true;
                TakeshiNavigation::getClose("robot_init_pose",10000);
                TakeshiManip::hdGoTo(0.0,0.0,3000);
                TakeshiHRI::waitAfterSay("I will find the client", 4000);
                nextState = SM_SEARCH_WAVING;     
                
                break;

            case SM_SEARCH_WAVING:
                std::cout << "State machine: SM_SEARCH_WAVING" << std::endl;
                TakeshiVision::startSkeletonFinding();
                TakeshiManip::hdGoTo(0.0,0.0,3000);
                TakeshiHRI::waitAfterSay("looking for somebody waving",2000);
                if(!TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000))
                    if(!TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000))
                        TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000);

                if(gesture.gesture.size() > 0){ 
                    if(gesture.gesture.compare("right_waving")==0 || gesture.gesture.compare("left_waving")==0) {
                    
                    //if(gesture.gesture.compare(/*"right_hand_rised")==0 || */gesture.gesture.compare("right_waving")==0 || /*gesture.gesture.compare("left_hand_rised")==0 ||*/ gesture.gesture.compare("left_waving")==0) {
                        TakeshiHRI::waitAfterSay("I noticed that somebody are asking for my service", 4000);
                        TakeshiHRI::waitAfterSay("Tell me... take the order... for confirmation", 4000);
                        ros::Duration(1.0).sleep();
                        TakeshiVision::stopSkeletonFinding();
                        ros::Duration(1.0).sleep();
                        TakeshiHRI::loadJSGFGrammar(grammarCommands,"restaurant");
                        TakeshiHRI::enableSphinxMic(true);
                        nextState=SM_WAIT_FOR_TAKE_ORDER;                        
                    }
                        ros::Duration(1.0).sleep();
                        TakeshiVision::stopSkeletonFinding();
                        ros::Duration(1.0).sleep();

                }        

                else{
                    ros::Duration(1.0).sleep();
                    TakeshiVision::stopSkeletonFinding();
                    ros::Duration(1.0).sleep();
                    nextState = SM_SEARCH_WAVING;
                }
                break;

            case SM_WAIT_FOR_TAKE_ORDER:
                std::cout << "State machine: SM_WAIT_FOR_TAKE_ORDER" << std::endl;
                
                if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                    if(TakeshiHRI::find_in_sentence(lastRecoSpeech,"take the order")){
                        TakeshiHRI::waitAfterSay("Ok, I am going to approach to the client", 4000);
                        TakeshiHRI::enableSphinxMic(false);
                        nextState = SM_CLOSE_TO_CLIENT;
                        break;
                    }
                    else if(TakeshiHRI::find_in_sentence(lastRecoSpeech,"wait") == 0){
                        
                        TakeshiVision::startSkeletonFinding();
                        nextState = SM_SEARCH_WAVING;
                        break;
                    }
                }
                else{
                    TakeshiHRI::waitAfterSay("I will find to the another client", 5000);
                    //TakeshiHRI::enableSpeechRecognized(false);
                    TakeshiHRI::enableSphinxMic(true);
                    nextState=SM_SEARCH_WAVING;
                }
                break;

            case SM_CLOSE_TO_CLIENT:
                std::cout << "State machine: SM_CLOSE_TO_CLIENT" << std::endl;

                TakeshiTools::transformPoint("/base_link", gesture.gesture_centroid.x,gesture.gesture_centroid.y ,gesture.gesture_centroid.z, "/map", gx_w, gy_w, gz_w);
                TakeshiTasks::closeToGoalWithDistanceTHR(gx_w, gy_w, 1.5, 120000);
                dist_to_head = sqrt( pow(gx_w, 2) + pow(gy_w, 2));
                TakeshiKnowledge::getRobotPose(robot_x, robot_y, robot_a);
                // TakeshiManip::startHdGoTo(atan2(gy_w, gx_w) - robot_a, atan2(gz_w - 1.6, dist_to_head)); 
                TakeshiManip::startHdGoTo(0, atan2(gz_w - 1.6, dist_to_head));
                TakeshiKnowledge::addUpdateKnownLoc("table_1", robot_a);
                TakeshiHRI::enableSphinxMic(true);   
                
                // TakeshiHRI::waitAfterSay("Hello my name is Justina, and for today I will take your order, please tell me what order do you want me to bring", 12000);
                TakeshiHRI::waitAfterSay("Hello my name is takeshi, and for today I will take your order", 7000);
                attempsConfirmation = 1;
                attempsWaitConfirmation = 1;
                attempsSpeechReco = 1;
                attempsSpeechInt = 1;
                validateCombo = false;
                nextState = SM_ASK_FOR_NUMBER_OF_ITEMS;
                break;

            case SM_ASK_FOR_NUMBER_OF_ITEMS:
                printState("ask for length order length");
                TakeshiHRI::waitAfterSay("How many items are you going to order?",2000);
                TakeshiHRI::loadJSGFGrammar(grammarNumber,"restaurant");
                TakeshiHRI::enableSphinxMic(true);
                nextState = SM_WAIT_FOR_NUMBER;
                break;
            case SM_WAIT_FOR_NUMBER:
                printState("waiting for the number of items");
                 if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, timeoutspeech)){
                    if(lastRecoSpeech=="one"){
                        length_order=1;
                    }else if(lastRecoSpeech=="two"){
                        length_order=2;
                    }
                    else if(lastRecoSpeech=="three"){
                        length_order=3;
                    }
                    else if(lastRecoSpeech=="four"){
                        length_order=4;
                    }else{
                        length_order=5;
                    }
                    nextState=SM_ASK_FOR_ITEM;
                 }
                break;

            case SM_ASK_FOR_ITEM:
                std::cout << "State machine: SM_TAKE_TYPE_ORDER" << std::endl;
                if(length_order>item_counter){
                    //TakeshiHRI::enableSpeechRecognized(false);
                    TakeshiHRI::enableSphinxMic(false);
                    TakeshiHRI::waitAfterSay("tell me the element number "+std::to_string(item_counter+1)+ " , please",2000);
                    TakeshiHRI::loadJSGFGrammar(grammarOrder,"restaurant");
                    TakeshiHRI::enableSphinxMic(true);
                    nextState = SM_WAIT_FOR_ITEM;
                }
                else{
                    TakeshiHRI::waitAfterSay("the order is the next one",2000);
                    for(size_t i=0;i<order_items.size();i++){
                        TakeshiHRI::waitAfterSay(order_items[i],2000);
                    }
                    TakeshiHRI::waitAfterSay("I will return with it",2000);
                    nextState=SM_RETURN_BAR;
                }
                break;

            case SM_WAIT_FOR_ITEM:
                printState("wait for item");
                if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                       std::cout << "PARSING WORD..." << std::endl;
                       if(TakeshiHRI::find_in_sentence(lastRecoSpeech,validitems,object_aux)){
                           nextState = SM_COMFIRM_ITEM;
                        }
                    }
                break;

            case SM_COMFIRM_ITEM:
                TakeshiHRI::enableSphinxMic(false);
                printState("confirm items");
                TakeshiHRI::waitAfterSay("Did you say",1000);
                TakeshiHRI::waitAfterSay(object_aux,1000);
                nextState=SM_WAIT_CONFIRMATION_ITEM;
                TakeshiHRI::enableSphinxMic(true);
                break;

            case SM_WAIT_CONFIRMATION_ITEM:
                printState("wait confirmation for item");

                if(TakeshiHRI::waitForUserConfirmation(userConfirmation, 5000)){
                    if(userConfirmation){
                        userConfirmation=false;
                        item_counter++; /////////////////////////////////debe de aumentar cuando acepta el item
                        order_items.push_back(object_aux);
                        TakeshiHRI::enableSphinxMic(false);

                    }
                    else{
                        TakeshiHRI::enableSphinxMic(false);
                        TakeshiHRI::waitAfterSay("Could you repeat the item",1000);
                        TakeshiHRI::loadJSGFGrammar(grammarOrder,"restaurant");
                        TakeshiHRI::enableSphinxMic(true);
                    }
                    nextState=SM_ASK_FOR_ITEM;
                }
                break;

            case SM_RETURN_BAR:
                std::cout << "State machine: SM_RETURN_BAR" << std::endl;
                //TakeshiHRI::loadGrammarSpeechRecognized(grammarCommands);//load the grammar
                TakeshiHRI::loadJSGFGrammar(grammarCommands,"restaurant");
                //TakeshiHRI::enableSpeechRecognized(false);
                TakeshiHRI::enableSphinxMic(false);
                if(!TakeshiNavigation::getClose("kitchen_bar", 120000)){
                    attempsNavigation++;
                    if(attempsNavigation <= maxAttempsNavigation)
                        break;
                    else{
                        TakeshiKnowledge::getRobotPose(robot_x, robot_y, robot_a);
                        TakeshiKnowledge::getKnownLocation("kitchen_bar", goalx, goaly, goala);
                        angleError = goala - robot_a;
                        if(angleError > M_PI) angleError -= 2*M_PI;
                        if(angleError <= -M_PI) angleError += 2*M_PI;
                        TakeshiNavigation::moveDistAngle(0.0, angleError, 3000);
                    }
                }
                TakeshiHRI::waitAfterSay("I arrived to the kitchen bar", 2000);
                nextState=SM_GRASP_ORDER;
                break;

            case SM_GRASP_ORDER:
                TakeshiHRI::waitAfterSay("I will seach the order items", 2000);
                grasp_succes=TakeshiTasks::graspYoloObject(order_items,recognizedYoloObjects,3,3000,true,objectCoordinates);
                if(!grasp_succes){
                            TakeshiHRI::waitAfterSay("Bar man, i cant detect folowing objects in the order,please take them and i will guide you to the table", 2000);
                            nextState=SM_HANDOVER_OBJECT;
                        }
                else{
                    if(order_items.size()>1){
                        TakeshiHRI::waitAfterSay("Bar man, take the others objects and follow me to the order table", 2000);
                        erase_item(recognizedYoloObjects[0].id, order_items);
                        nextState=SM_HANDOVER_OBJECT;
                    }
                    nextState=SM_GOTO_ORDER_TABLE;
                }
            break;

            case SM_GOTO_ORDER_TABLE:
                    if(!TakeshiNavigation::getClose("table_1",60000))
                        if(!TakeshiNavigation::getClose("table_1",40000))
                            TakeshiNavigation::getClose("table_1",40000);
                    
                    TakeshiNavigation::getClose("table_1",5000);               
                    nextState=SM_RELEASE_THE_ORDER;
            break;

            case SM_RELEASE_THE_ORDER:
                printState("SM_RELEASE_THE_ORDER");    
                    TakeshiHRI::waitAfterSay("I will give you the object", 3500);
                    if(!TakeshiTasks::giveObjectToHuman()){
                        //if(!TakeshiTasks::giveObjectToHuman())
                          //  if(!TakeshiTasks::giveObjectToHuman()){
                                TakeshiManip::armGoToGetObjects(4000);
                                TakeshiHRI::waitAfterSay("Take the object", 2000);
                                TakeshiManip::openGripper(1.0);
                                ros::Duration(7).sleep();
                                TakeshiManip::navigationPose(4000);
                          //
                            }
                    TakeshiManip::navigationPose(4000);
                    TakeshiManip::openGripper(0.0);

                    ////////////////////////////decir que el otro wey trae los demas objetos y que se los va a dar
                    nextState=SM_RETURN_KITCHEN;
            break;


            case SM_HANDOVER_OBJECT:
                for(int i=0; i<order_items.size();i++)
                    TakeshiHRI::waitAfterSay(order_items[i],2000);
                TakeshiHRI::waitAfterSay("When you grab them tell me lets go", 2000);
                TakeshiHRI::loadJSGFGrammar(grammarCommands,"restaurant");
                TakeshiHRI::enableSphinxMic(true);
                nextState=SM_WAIT_FOR_COMMAND_TO_BRING_THE_ORDER;
            break;

            case SM_WAIT_FOR_COMMAND_TO_BRING_THE_ORDER:
                //aqui va lo de comenzar a cacahr el lets go Y avisar que el barman lleva la orden, y de regreso a la kitchen
                printState("State machine: SM_WAIT_FOR_TAKE_ORDER");
                if(TakeshiHRI::waitForSpeechRecognized(lastRecoSpeech, 5000)){
                    if(TakeshiHRI::find_in_sentence(lastRecoSpeech,"lets go")){
                        TakeshiHRI::waitAfterSay("Ok, I'm going to the table", 4000);
                        TakeshiHRI::enableSphinxMic(false);
                        nextState = SM_GO_TO_ORDER_TABLE_TO_DELIVER;
                    }
                }
            break;

            case SM_GO_TO_ORDER_TABLE_TO_DELIVER:
                if(!TakeshiNavigation::getClose("table_1", 40000))
                    if(!TakeshiNavigation::getClose("table_1", 40000))
                        TakeshiNavigation::getClose("table_1", 40000);
                TakeshiNavigation::getClose("table_1", 5000);
                nextState=SM_HANDOVER_OBJECT_WITH_WAITER;
            break;

            case SM_HANDOVER_OBJECT_WITH_WAITER:
                 printState("SM_RELEASE_THE_ORDER_WITH_WAITER");    
                 if(grasp_succes){
                    TakeshiHRI::waitAfterSay("we will give you the object", 3500); //THE waiter lo dará no??????
                    if(!TakeshiTasks::giveObjectToHuman()){
                        //if(!TakeshiTasks::giveObjectToHuman())
                          //  if(!TakeshiTasks::giveObjectToHuman()){
                                TakeshiManip::armGoToGetObjects(4000);
                                TakeshiHRI::waitAfterSay("Take the object", 2000);
                                TakeshiManip::openGripper(1.0);
                                ros::Duration(7).sleep();
                                TakeshiManip::navigationPose(4000);
                          //
                            }
                    TakeshiManip::navigationPose(4000);
                    TakeshiManip::openGripper(0.0);
                    if(order_items.size()>1){
                        TakeshiHRI::waitAfterSay("the rest of the order will be deliver for the waiter",5000);
                        TakeshiHRI::waitAfterSay("Barman, please give the rest to the human",3000);
                    }
                }else{
                    TakeshiHRI::waitAfterSay("waiter please give the order in this table",2000);
                    ros::Duration(10).sleep();
                }

                    nextState=SM_RETURN_KITCHEN;
                
            break;

    /*            
                if(findGestureOrAttendOrder){
                    TakeshiHRI::waitAfterSay("I will find to the client", 5000);
                    TakeshiVision::startSkeletonFinding();
                    nextState=SM_SEARCH_WAVING;
                }
                else{
                    // TODO This is for attend the order in kitchen bar
                    nextState = SM_FINISH_TEST;
                }
                break;
                */
            case SM_RETURN_KITCHEN:
                if(!TakeshiNavigation::getClose("robot_init_pose", 60000))
                    if(!TakeshiNavigation::getClose("robot_init_pose", 40000))
                        TakeshiNavigation::getClose("robot_init_pose", 40000);
                TakeshiNavigation::getClose("robot_init_pose", 5000);
                TakeshiHRI::loadJSGFGrammar(grammarCommands);
                TakeshiHRI::enableSphinxMic(true);
                nextState=SM_SEARCH_WAVING;
            break;

            case SM_FINISH_TEST:
                TakeshiHRI::waitAfterSay("I have finished the test", 5000);
                success = true;
            break;    
        }
        ros::spinOnce();
        loop.sleep();
    }

    return 1;
}

