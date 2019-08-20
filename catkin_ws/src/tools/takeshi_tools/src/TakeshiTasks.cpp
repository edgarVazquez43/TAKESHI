#include "takeshi_tools/TakeshiTasks.h"

bool TakeshiTasks::_tasksStop = false;
ros::Subscriber TakeshiTasks::subTasksStop;

bool TakeshiTasks::is_node_set = false;
string message;

bool TakeshiTasks::setNodeHandle(ros::NodeHandle* nh) {
        if (TakeshiTasks::is_node_set)
                return true;
        if (nh == 0)
                return false;
        TakeshiTasks::printTakeshiTaskMessage("Setting ros node...");

        TakeshiHardware::setNodeHandle(nh);
        TakeshiManip::setNodeHandle(nh);
        TakeshiNavigation::setNodeHandle(nh);
        TakeshiHRI::setNodeHandle(nh);
        TakeshiKnowledge::setNodeHandle(nh);
        TakeshiVision::setNodeHandle(nh);
        TakeshiTools::setNodeHandle(nh);

        TakeshiTasks::is_node_set = true;
        return true;
}

void TakeshiTasks::printTakeshiTaskMessage(std::string message){
        cout << "\033[1;36m     TakeshiTasks.->"<< message <<"\033[0m" << endl;
}

void TakeshiTasks::printTakeshiTaskError(string message){
        cout << "\033[1;31m     TakeshiTasks.->"<< message <<"\033[0m" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Manipulation Tasks/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TakeshiTasks::placeObjectInFront(float objectHeight, float planeHeight){
        cout << planeHeight << endl;
        return TakeshiTasks::placeObject(objectHeight, planeHeight, true);
}

bool TakeshiTasks::placeObject(float objectHeight, float planeHeight, bool inFront)
{

        TakeshiTasks::printTakeshiTaskMessage("Place object");
        TakeshiTasks::printTakeshiTaskMessage("In front: " + to_string(inFront));
        std::vector<float> vacantPlane;
        std::vector<int> inliers;
        std::vector<float> x;
        std::vector<float> y;
        std::vector<float> z;
        std::vector<float> distance;

        int maxInliersIndex;

        float maximunInliers = 0;
        float XtoPlace;
        float YtoPlace;
        float ZtoPlace;

        bool isFreeSpace = false;

// Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        geometry_msgs::Pose2D base_correction;

        float torso;
        float x_correction;
        float x_error;

        if(inFront) {
                if(!TakeshiTasks::alignWithFrontTable(0.58))
                        TakeshiTasks::alignWithFrontTable();
                if(!TakeshiVision::findVacantPlane(vacantPlane, inliers, true)) {

                        TakeshiNavigation::moveDist(0.1, 1000);
                        boost::this_thread::sleep(boost::posix_time::milliseconds(3000));

                        if(!TakeshiVision::findVacantPlane(vacantPlane, inliers, true)) {

                                TakeshiNavigation::moveDist(-0.2, 1000);
                                boost::this_thread::sleep(boost::posix_time::milliseconds(3000));

                                if(!TakeshiTasks::alignWithTable(0.4)) {
                                        if(!TakeshiVision::findVacantPlane(vacantPlane, inliers, true)) {
                                                TakeshiTasks::printTakeshiTaskError("PlaceObject: I CANNOT FIND A VACANT PLANE");
                                                return false;
                                        }
                                }
                                else{
                                        if(!TakeshiVision::findVacantPlane(vacantPlane, inliers, true)) {
                                                TakeshiTasks::printTakeshiTaskError("PlaceObject: I CANNOT FIND A VACANT PLANE");
                                                return false;
                                        }
                                }
                        }
                }
        }
        else{
                if(!TakeshiTasks::alignWithTable(0.50))
                        TakeshiTasks::alignWithTable(0.50);
                boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
                if(!TakeshiVision::findVacantPlane(vacantPlane, inliers)) {

                        TakeshiNavigation::moveLateral(0.1, 1000);
                        boost::this_thread::sleep(boost::posix_time::milliseconds(3000));

                        if(!TakeshiVision::findVacantPlane(vacantPlane, inliers)) {

                                TakeshiNavigation::moveLateral(-0.2, 1000);
                                boost::this_thread::sleep(boost::posix_time::milliseconds(3000));

                                if(!TakeshiTasks::alignWithTable(0.5)) {
                                        if(!TakeshiVision::findVacantPlane(vacantPlane, inliers)) {
                                                TakeshiTasks::printTakeshiTaskError("PlaceObject: I CANNOT FIND A VACANT PLANE");
                                                return false;
                                        }
                                }
                                else{
                                        if(!TakeshiVision::findVacantPlane(vacantPlane, inliers)) {
                                                TakeshiTasks::printTakeshiTaskError("PlaceObject: I CANNOT FIND A VACANT PLANE");
                                                return false;
                                        }
                                }
                        }
                }
        }
        // Find a vacant plane
        // Reorganizing points in diferents lists
        // x, y, z --- Are list of diferents centroids of clear spaces
        for(int i = 0; i < (vacantPlane.size()); i=i+3)
        {
                x.push_back( vacantPlane[ i ] );
                y.push_back( vacantPlane[i+1] );
                z.push_back( vacantPlane[i+2] );
        }


        TakeshiTasks::printTakeshiTaskMessage("The free space is reorganizing");
        for(int i = 0; i < x.size(); i++)
        {
                // std::cout << "P[" << i << "]:  ("
                //        << x[i] << ", "
                //        << y[i] << ", "
                //        << z[i] << ")"
                //        << std::endl;
                //std::cout << "inliers[" << i << "]:  " << inliers[i] << std::endl;
                //std::cout << "  z[" << i << "]:  " << z[i] << std::endl;
                //std::cout << "  planeHeight " << planeHeight << std::endl;
                if(z[i] < planeHeight) {
                        if(inliers[i] > maximunInliers) {
                                maximunInliers = inliers[i];
                                maxInliersIndex = i;
                        }
                        isFreeSpace = true;
                }
        }

        if(!isFreeSpace) {
                TakeshiTasks::printTakeshiTaskError("PlaceObject:  CANNOT FIND A FREE SPACE");
                return false;
        }

        // This the point of maximun number of inliers
        TakeshiTasks::printTakeshiTaskMessage("P_max["+to_string(maxInliersIndex) + "]:  ("
                                              + to_string(x[maxInliersIndex]) + ", "
                                              + to_string(y[maxInliersIndex]) + ", "
                                              + to_string(z[maxInliersIndex]) + " + " + to_string(objectHeight) + ")");
        TakeshiTasks::printTakeshiTaskMessage("PlaceObject  inliers_max[" + to_string(maxInliersIndex) + "]: "
                                              + to_string(inliers[maxInliersIndex]));

        XtoPlace = x[maxInliersIndex];
        YtoPlace = y[maxInliersIndex];
        ZtoPlace = z[maxInliersIndex] + objectHeight;

        TakeshiTasks::printTakeshiTaskMessage("PlaceObject: Correct X displacement.");
        if(!inFront && XtoPlace > 0.08)
                x_correction = XtoPlace + 0.08;  //  is the distance from base_arm to robot_base in axis Y
        else
                x_correction = XtoPlace - 0.08;
        TakeshiTasks::printTakeshiTaskMessage("X[diff]:  " + to_string(x_correction));
        TakeshiManip::startHdGoTo(0.0, 0.0);
        if(inFront)
                TakeshiNavigation::moveLateral(YtoPlace-0.08, 4000);
        else
        {
                TakeshiNavigation::moveDistAngle(0.0, 1.563,  4000);
                TakeshiNavigation::moveLateral(-x_correction, 4000);
        }

        if(!inFront) {
                //       FIST STEP OF MOVEMENT ARM        //
                cartesian.resize(3);
                cartesian[0] = YtoPlace - 0.08;
                cartesian[1] = XtoPlace;
                cartesian[2] = ZtoPlace + 0.04;
        }

        else{
                cartesian.resize(3);
                cartesian[0] = XtoPlace - 0.08;
                cartesian[1] = YtoPlace;
                cartesian[2] = ZtoPlace + 0.04;
        }
        TakeshiTasks::printTakeshiTaskMessage("[Before correction]  try calculate Inverse Kinematic "
                                              + to_string(cartesian[0]) + "  "
                                              + to_string(cartesian[1]) + "  "
                                              + to_string(cartesian[2]) );

// Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) ) {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        TakeshiTasks::printTakeshiTaskMessage("OmniBase correction: " + to_string(base_correction.x) + " " + to_string(base_correction.y) + " " +to_string(base_correction.theta));
        TakeshiTasks::printTakeshiTaskMessage("Torso correction: " + to_string(torso));

        TakeshiManip::torsoGoTo(torso + 0.02, 2000);
        ros::Duration(0.5).sleep();
        TakeshiManip::armGoToArticular(articular, 4000);
        ros::Duration(1.0).sleep();

//       SECOND STEP OF MOVEMENT ARM        //
        if(!inFront) {
                cartesian.resize(3);
                cartesian[0] = YtoPlace;
                cartesian[1] = XtoPlace;
                cartesian[2] = ZtoPlace - 0.05;
        }
        else{
                cartesian.resize(3);
                cartesian[0] = XtoPlace;
                cartesian[1] = YtoPlace;
                cartesian[2] = ZtoPlace - 0.05;
        }

        TakeshiTasks::printTakeshiTaskMessage("[Before correction]  try calculate Inverse Kinematic "
                                              + to_string(cartesian[0]) + "  "
                                              + to_string(cartesian[1]) + "  "
                                              + to_string(cartesian[2]) );

// Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) ) {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        TakeshiTasks::printTakeshiTaskMessage("OmniBase correction: " + to_string(base_correction.x) + " " + to_string(base_correction.y) + " " +to_string(base_correction.theta));
        TakeshiTasks::printTakeshiTaskMessage("Torso correction: " + to_string(torso));

        TakeshiNavigation::moveDist(0.08,4000);
        TakeshiManip::torsoGoTo(torso, 4000);
        ros::Duration(1.0).sleep();
        TakeshiManip::armGoToArticular(articular, 2000);

        TakeshiManip::openGripper(1.0);
        ros::Duration(2.5).sleep();

        TakeshiManip::torsoGoTo(torso, 1000);
        TakeshiNavigation::moveDist(-0.15,4000);
        TakeshiManip::armGoToAfterPlaceInShelf();

        TakeshiManip::armGoToNavigation();
        TakeshiManip::openGripper(0.0);
        TakeshiManip::torsoGoTo(0.0, 2000);

        return true;
}

bool TakeshiTasks::placeObjectLateralAtPoint(float x, float y, float z)
{
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;

        float torso;
        float x_correction;
        float x_error;

        if(fabs(x) > 0.55 || fabs(y) > 1.0) {
                TakeshiHRI::say("The empty space is too far from me...");
                return false;
        }

        cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: Correct X displacement.\033[0m" << endl;
        //Correction coordinates for objects in left side
        if(x > 0)
                x_correction = x + 0.10;  // 0.10 is the distance from base_arm to robot_base in axis Y
        else
                x_correction = x + 0.03;  //10 //Correction coordinates for objects in right side
        std::cout << "   X[diff]:  " << x_correction << std::endl;
        cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: X[diff]: " << x_correction << "\033[0m" << endl;

        TakeshiNavigation::moveDistAngle(x_correction, 0.0,  4000);
        TakeshiManip::hdGoTo(0.0, 0.0, 4000);
        TakeshiManip::armGoToArticular(0.0, -1.5707, 0.0, 0.0, 4000);

        if(y > 0)
                TakeshiNavigation::moveDistAngle(0.0, 1.5707, 2000);  // Correction coordinates for objects in left side
        else
                TakeshiNavigation::moveDistAngle(0.0, -1.5707, 2000);  // Correction coordinates for objects in right side

        TakeshiManip::armGoToArticular(0.0, -1.5707, -1.5707, 0.0, 4000);
        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = abs(y) - 0.05;
        cartesian[1] = x;
        cartesian[2] = z;

        cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: [Before correction]  try calculate Inverse Kinematic "
             << cartesian[0] << "  "
             << cartesian[1] << "  "
             << cartesian[2] << "\033[0m" << endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: " << "   " << articular[i] << "\033[0m" << endl;

        cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: OmniBase correction: " << base_correction <<"\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: Torso correction: " << torso <<"\033[0m" << endl;

        
        TakeshiManip::torsoGoTo(torso + 0.05, 2000);
        TakeshiManip::armGoToArticular(articular, 2000);

        //       SECOND STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = abs(y) + 0.02;
        cartesian[1] = x;
        cartesian[2] = z;

        cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: [Before correction]  try calculate Inverse Kinematic "
             << cartesian[0] << "  "
             << cartesian[1] << "  "
             << cartesian[2] << "\033[0m" << endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: " << "   " << articular[i] << "\033[0m" << endl;

        cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: OmniBase correction: " << base_correction <<"\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks.->Place Object Specific lateral: Torso correction: " << torso <<"\033[0m" << endl;

        TakeshiManip::torsoGoTo(torso - 0.01, 1500);
        TakeshiManip::armGoToArticular(articular, 2500);
        ros::Duration(1.0).sleep();
        TakeshiNavigation::moveDistAngle(0.1, 0.0, 4000);
        ros::Duration(1.0).sleep();
        TakeshiManip::openGripper(1.0);

        TakeshiManip::torsoGoTo(torso + 0.10, 1500);

        articular[0] =  0.0;
        articular[1] =  0.0;
        articular[2] = -1.57;
        articular[3] =  0.0;

        TakeshiManip::hdGoTo(0.0, 0.0, 6000);
        TakeshiNavigation::moveDistAngle(-0.1, 0.0, 3000);
        TakeshiManip::armGoToArticular(articular, 1000);
        TakeshiManip::waitForArmGoToNavigation(3000);
        TakeshiManip::torsoGoTo(0.0, 2000);

        return true;
}

bool TakeshiTasks::placeObjectInShelf(int pose, bool inFront)
{
        TakeshiTasks::printTakeshiTaskMessage("Place object in Shelf. Pose: " + to_string(pose));
        TakeshiTasks::printTakeshiTaskMessage("In front: " + to_string(inFront));
        std::vector<float> articular;
        float distanceToMove=0.07;
        float distanceToAlign=0.0;
        if(pose==2) {
                distanceToAlign=0.8;
                distanceToMove=0.30;
        }
        else
                distanceToAlign=0.4;

        if(inFront) {
                if(!TakeshiTasks::alignWithFrontTable(distanceToAlign))
                        TakeshiTasks::alignWithFrontTable(distanceToAlign);
        }

        TakeshiManip::hdGoTo(0.0,0.0,3000);
        TakeshiManip::armGoToShelf(pose);
        TakeshiNavigation::moveDist(distanceToMove, 2000);
        TakeshiManip::openGripper(1.0);
        ros::Duration(3.5).sleep();
        TakeshiNavigation::moveDist(-distanceToMove, 2000);
        ros::Duration(2.0).sleep();
        TakeshiManip::armGoToAfterPlaceInShelf();
        TakeshiManip::armGoToNavigation();
        TakeshiManip::openGripper(0.0);
        TakeshiManip::torsoGoTo(0.0, 2000);
        return true;

}

bool TakeshiTasks::placeObjectInColorBin(string color){
        vision_msgs::VisionObject object;
        float distToGrasp=0.55;
        float y_correction, x_correction;
        TakeshiManip::hdGoTo(0.0, -0.9, 4000);
        ros::Duration(1).sleep();

        if(!TakeshiVision::detectObjectByColor(color, object))
                return false;

        std::cout << "\033[1;34m     TakeshiTasks.->Place object in color bin: Object Location x: " << object.pose.position.x << " y: " << object.pose.position.y << " z:" << object.pose.position.z <<".\033[0m" << std::endl;
        if(fabs(object.pose.position.x) > 1.8 || fabs(object.pose.position.y) > 0.5) {
                TakeshiHRI::say("I can not detect the object in front of me.");
                return false;
        }

        if(object.pose.position.y > 0)
                y_correction = object.pose.position.y -0.07;
        else
                y_correction = object.pose.position.y -0.15;
        TakeshiManip::hdGoTo(0.0, 0.0, 4000);
        TakeshiNavigation::moveLateral(y_correction, 4000);

        if(x_correction-0.02 < 0)
                x_correction=object.pose.position.x-distToGrasp-0.08;
        else
                x_correction=object.pose.position.x-distToGrasp;

        TakeshiNavigation::moveDist(x_correction, 4000);
        TakeshiManip::torsoGoTo(0.05,4000);
        TakeshiManip::waitForArmGoToColorBin(4000);
        TakeshiManip::openGripper(1.0);
        ros::Duration(2).sleep();
        TakeshiManip::navigationPose(4000);
        TakeshiNavigation::moveDist(-0.1, 4000);
        return true;
}

bool TakeshiTasks::graspBagInFloor(string color,vision_msgs::ObjectCoordinatesForDetection& bagsCoordinates){
        vision_msgs::VisionObject object;
        float distToGrasp=0.38, torso=0.27;
        float y_correction,x_correction,torso_correction;

        if(bagsCoordinates.y_min==-1.0 && bagsCoordinates.y_max==1.0)
                TakeshiManip::hdGoTo(0.0, -0.8, 1000);
        ros::Duration(1).sleep();

        if(TakeshiVision::detectObjectByColor(color,object,true)) {
                if(!TakeshiVision::isGraspeable(object.pose.position.x,object.pose.position.y,object.pose.position.z,bagsCoordinates)){
                    printTakeshiTaskError("The bag in not graspeable");
                    return false;    
                }
                geometry_msgs::Vector3 pre_force, post_force;
                double weight;
                TakeshiManip::getCurrentForce(pre_force);

                std::stringstream ss;
                ss << "I detected the " << color << "bag, I'm going to take it.";
                TakeshiHRI::say(ss.str());
                torso_correction=object.pose.position.z-0.27;
                TakeshiManip::hdGoTo(0.0, 0.0, 1000);
                if(torso_correction > 0)
                        TakeshiManip::torsoGoTo(torso_correction, 2000);
                if(object.pose.position.y > 0)
                        y_correction = object.pose.position.y -0.05;
                else
                        y_correction = object.pose.position.y -0.13;
                TakeshiNavigation::moveLateral(y_correction, 4000);

                if(x_correction-0.02 < 0) {
                        x_correction=object.pose.position.x-distToGrasp-0.08;
                }
                else{
                        x_correction=object.pose.position.x-distToGrasp;
                }
                TakeshiNavigation::moveDist(x_correction, 4000);
                ros::Duration(3).sleep(); ///corregir sleep

                if((object.bounding_box.xmax-object.bounding_box.xmin) < (object.bounding_box.ymax-object.bounding_box.ymin)/1.5){
                    printTakeshiTaskMessage("Bag mode: lateral");
                    TakeshiManip::armGoToGraspBag(0.0);
                }
                else{
                    printTakeshiTaskMessage("Bag mode: normal");
                    TakeshiManip::armGoToGraspBag(-1.5);
                }


                
                ros::Duration(1).sleep();
                TakeshiManip::closeGripper(0.5);
                ros::Duration(1).sleep();
                TakeshiManip::navigationPose(4000);
                ros::Duration(2).sleep();

                TakeshiManip::getCurrentForce(post_force);
                weight=TakeshiManip::computeWeight(pre_force,post_force);
                TakeshiTasks::printTakeshiTaskMessage("Object weight: " + to_string(weight));

                if(weight < 70) {
                        TakeshiNavigation::moveDist(-0.2, 3000);
                        TakeshiManip::hdGoTo(0.0, -0.8, 1000);
                        if(TakeshiVision::detectObjectByColor(color,object,true)) {
                            TakeshiTasks::printTakeshiTaskMessage("Can not take the bag");
                            
                            bagsCoordinates=TakeshiVision::objectCoordinates;
                            return false;
                        }
                        else{
                            TakeshiHRI::waitAfterSay("I taked the bag", 2000);
                            return true;
                        }
                }
                else{
                        TakeshiHRI::waitAfterSay("I taked the bag", 2000);
                        return true;
                }
        }

        else{
                TakeshiTasks::printTakeshiTaskError("I can not detect the bag");
                return false;
        }

}

bool TakeshiTasks::graspThePointingBag(int attempts){
        bool findBagRightSide=true;
        vision_msgs::GestureSkeleton gesture;
        std::vector<std::string> specificGestures;
        std::vector<std::string> colored_bags;
        vision_msgs::ObjectCoordinatesForDetection bagsCoordinates;
        bagsCoordinates=TakeshiVision::objectCoordinates;
        bagsCoordinates.y_min=-0.6;
        bagsCoordinates.y_max=0.6   ;
        bagsCoordinates.x_max=1.5;

        specificGestures.push_back("pointing_left_down");
        specificGestures.push_back("pointing_right_down");
        colored_bags.push_back("red");
        colored_bags.push_back("yellow");
        colored_bags.push_back("blue");
        colored_bags.push_back("green");
        colored_bags.push_back("brown");
        bool graspBag=false;

        TakeshiManip::hdGoTo(0.0,0.0,3000);
        TakeshiHRI::say("Human, point with the closest hand to the bag");
        ros::Duration(2).sleep();
        TakeshiVision::startSkeletonFinding();

        if(!TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000))
                if(!TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000))
                        TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000);

        if(gesture.gesture.size() > 0) {
                if(gesture.gesture.compare("pointing_right_down")==0) {
                        TakeshiHRI::say("I will find the bag in your right side");
                        TakeshiManip::hdGoTo(0.4,-0.7,3000);
                        findBagRightSide=true;
                        bagsCoordinates.y_min=gesture.gesture_centroid.y;
                        bagsCoordinates.z_max=0.7;
                }
                else if(gesture.gesture.compare("pointing_left_down")==0) {
                        TakeshiHRI::say("I will find the bag in your left side");
                        TakeshiManip::hdGoTo(-0.4,-0.7,3000);
                        findBagRightSide=false;
                        bagsCoordinates.y_max=gesture.gesture_centroid.y;
                        bagsCoordinates.z_max=0.7;
                }
                ros::Duration(1.0).sleep();
                TakeshiVision::stopSkeletonFinding();
                ros::Duration(1.0).sleep();
        }
        else{
                TakeshiHRI::say("I can not see your arm pointing");
                ros::Duration(1.0).sleep();
                TakeshiVision::stopSkeletonFinding();
                ros::Duration(1.0).sleep();
                return false;
        }

        for(int j=0; j<attempts && !graspBag; j++) {
                //for(int i=0; i<colored_bags.size() && !graspBag; i++) {
                        graspBag=TakeshiTasks::graspBagInFloor(colored_bags[4],bagsCoordinates);
                //}
                if(!graspBag)
                        TakeshiHRI::say("I could not take the bag, I will trying again");
        }
        if(!graspBag) {
                TakeshiHRI::say("I could not take any bag");
                TakeshiManip::hdGoTo(0.0,0.0,2000);
                return false;
        }
        return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Vision Tasks/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TakeshiTasks::alignWithTable(){
        return TakeshiTasks::alignWithTable(0.4, false);
}

bool TakeshiTasks::alignWithTable(float distToTable){
        return TakeshiTasks::alignWithTable(distToTable, false);
}

bool TakeshiTasks::alignWithFrontTable()
{
        return TakeshiTasks::alignWithTable(0.45, true);
}

bool TakeshiTasks::alignWithFrontTable(float distToTable){
        return TakeshiTasks::alignWithTable(distToTable, true);
}

bool TakeshiTasks::alignWithTable(float distToTable, bool inFront)
{
        if(inFront)
        {
                TakeshiTasks::printTakeshiTaskMessage("Aligning with table [FRONT]: ");
                TakeshiTasks::printTakeshiTaskMessage("Low table: " + to_string(inFront));
        }
        else{
                TakeshiNavigation::moveDistAngle(0.0, -1.5707, 3000);
                TakeshiTasks::printTakeshiTaskMessage("Aligning with table [LEF_SIDE]: ");
            }
        TakeshiTasks::printTakeshiTaskMessage("Distance to table: " + to_string(distToTable));


        TakeshiManip::findObjectsPose(inFront);
        TakeshiTasks::printTakeshiTaskMessage("Requesting line to line_finder");

        float x1, y1, z1, x2, y2, z2;

        for(int i=1; i<6; i++) {
                if(TakeshiVision::findLine(x1, y1, z1, x2, y2, z2))
                        break;
                TakeshiTasks::printTakeshiTaskError("Cannot find line. Attempt " + to_string(i) + "Trying again...");
                ros::Duration(0.5).sleep();
                if(i==5) {
                        //TakeshiHRI::say("I can't find the table");
                        return false;
                }
        }

        if (fabs(z1 - z2) > 0.3) {
                TakeshiTasks::printTakeshiTaskError("Found line is not confident. ");
                return false;
        }

        if(x1 == x2 && y1 == y2 && z1 == z2)
                return false;

        float robotX = 0, robotY = 0, robotTheta = 0;
        float A,B,C;
        //std::cout << "JustinaTasks.->Getting robot position.." << std::endl;
        //Since line is give wrt robot, we can consider that robot is at zero
        if(inFront) {
                B = y1 - y2;
                A = x2 - x1;
                C = -(B * x1 + A * y1);
        }
        else{
                A = y1 - y2;
                B = x2 - x1;
                C = -(A * x1 + B * y1);

        }
        //The robot center should be 0.4 m away of the table
        float distance = fabs(A * robotX + B * robotY + C) / sqrt(A * A + B * B)
                         - distToTable;
        float angle = atan2(y2 - y1, x2 - x1) - M_PI / 2;
        if (angle < 0)
                angle += M_PI;

        TakeshiTasks::printTakeshiTaskMessage("Moving base: dist=" + to_string(distance) + " angle=" + to_string(angle));
        if(!inFront) {
                angle = angle - M_PI/2;
                TakeshiNavigation::moveLateral(distance, 6000);
                TakeshiNavigation::moveDistAngle(0.0, angle, 10000);
        }
        else
                TakeshiNavigation::moveDistAngle(distance, angle, 10000);

        return true;
}




bool TakeshiTasks::placeObjectAtHeight(float objectHeight, float planeHeight, bool inFront)
{
        TakeshiTasks::printTakeshiTaskMessage("Place object at height");
        std::vector<float> vacantPlane;
        std::vector<int> inliers;
        std::vector<float> x;
        std::vector<float> y;
        std::vector<float> z;
        std::vector<float> distance;

        int maxInliersIndex;

        float maximunInliers = 0;
        float XtoPlace;
        float YtoPlace;
        float ZtoPlace;

        bool isFreeSpace = false;

// Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        geometry_msgs::Pose2D base_correction;

        float torso;
        float x_correction;
        float x_error;

        if(!TakeshiTasks::alignWithFrontTable())
        {
                TakeshiTasks::alignWithFrontTable();
        }
        float tolerance=0.1;
        if(!TakeshiVision::findVacantPlaneAtHeight(vacantPlane, inliers, planeHeight-tolerance,planeHeight+tolerance))
        {
                TakeshiNavigation::moveDist(0.1, 1000);
                ros::Duration(3.0).sleep();

                if(!TakeshiVision::findVacantPlaneAtHeight(vacantPlane, inliers, planeHeight-tolerance,planeHeight+tolerance))
                {

                        TakeshiNavigation::moveDist(-0.2, 1000);
                        ros::Duration(3.0).sleep();

                        if(!TakeshiTasks::alignWithTable(0.4)) {
                                if(!TakeshiVision::findVacantPlaneAtHeight(vacantPlane, inliers, planeHeight-tolerance,planeHeight+tolerance)) {
                                        TakeshiTasks::printTakeshiTaskError("PlaceObject: I CANNOT FIND A VACANT PLANE");
                                        return false;
                                }
                        }
                        else{
                                if(!TakeshiVision::findVacantPlaneAtHeight(vacantPlane, inliers, planeHeight-tolerance,planeHeight+tolerance)) {
                                        TakeshiTasks::printTakeshiTaskError("PlaceObject: I CANNOT FIND A VACANT PLANE");
                                        return false;
                                }
                        }
                }
        }
        // Find a vacant plane
        // Reorganizing points in diferents lists
        // x, y, z --- Are list of diferents centroids of clear spaces
        for(int i = 0; i < (vacantPlane.size()); i=i+3)
        {
                x.push_back( vacantPlane[ i ] );
                y.push_back( vacantPlane[i+1] );
                z.push_back( vacantPlane[i+2] );
        }

        for(int i = 0; i < x.size(); i++)
        {
                if(inliers[i] > maximunInliers) {
                        maximunInliers = inliers[i];
                        maxInliersIndex = i;
                }
                isFreeSpace = true;
        }

        if(!isFreeSpace) {
                TakeshiTasks::printTakeshiTaskError("PlaceObject:  CANNOT FIND A FREE SPACE");
                return false;
        }

// This the point of maximun number of inliers
        TakeshiTasks::printTakeshiTaskMessage("P_max["+to_string(maxInliersIndex) + "]:  ("
                                              + to_string(maxInliersIndex) + ", "
                                              + to_string(maxInliersIndex) + ", "
                                              + to_string(maxInliersIndex) + " + " + to_string(objectHeight) + ")");
        TakeshiTasks::printTakeshiTaskMessage("PlaceObject  inliers_max[" + to_string(maxInliersIndex) + "]: "
                                              + to_string(inliers[maxInliersIndex]));

        XtoPlace = x[maxInliersIndex];
        YtoPlace = y[maxInliersIndex];
        ZtoPlace = z[maxInliersIndex] + objectHeight;

        TakeshiTasks::printTakeshiTaskMessage("PlaceObject: Correct X displacement.");
        x_correction = YtoPlace + 0.10; // 0.08 is the distance from base_arm to robot_base in axis Y
        TakeshiTasks::printTakeshiTaskMessage("X[diff]:  " + to_string(x_correction));

        TakeshiManip::startHdGoTo(0.0, 0.0);

        if(!inFront) {
                TakeshiNavigation::moveDistAngle(x_correction, 0.0,  4000);
                TakeshiNavigation::moveDistAngle(0.0, 1.5707, 4000);
                //       FIST STEP OF MOVEMENT ARM        //
                cartesian.resize(3);
                cartesian[0] = YtoPlace;
                cartesian[1] = XtoPlace;
                cartesian[2] = ZtoPlace + 0.04;
        }

        else{
                TakeshiNavigation::moveLateral(-x_correction, 4000);
                cartesian.resize(3);
                cartesian[0] = XtoPlace;
                cartesian[1] = YtoPlace;
                cartesian[2] = ZtoPlace + 0.04;
        }
        TakeshiTasks::printTakeshiTaskMessage("[Before correction]  try calculate Inverse Kinematic "
                                              + to_string(cartesian[0]) + "  "
                                              + to_string(cartesian[1]) + "  "
                                              + to_string(cartesian[2]) );

// Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) ) {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        TakeshiTasks::printTakeshiTaskMessage("OmniBase correction: " + to_string(base_correction.x) + " " + to_string(base_correction.y) + " " +to_string(base_correction.theta));
        TakeshiTasks::printTakeshiTaskMessage("Torso correction: " + to_string(torso));

        TakeshiManip::torsoGoTo(torso, 2000);
        TakeshiManip::armGoToArticular(articular, 4000);

//       SECOND STEP OF MOVEMENT ARM        //
        if(!inFront) {
                TakeshiNavigation::moveDistAngle(0.0, 1.5707, 4000);
                //       FIST STEP OF MOVEMENT ARM        //
                cartesian.resize(3);
                cartesian[0] = YtoPlace;
                cartesian[1] = XtoPlace;
                cartesian[2] = ZtoPlace + 0.05;
        }

        else{
                cartesian.resize(3);
                cartesian[0] = XtoPlace;
                cartesian[1] = YtoPlace;
                cartesian[2] = ZtoPlace - 0.02;
        }

        TakeshiTasks::printTakeshiTaskMessage("[Before correction]  try calculate Inverse Kinematic "
                                              + to_string(cartesian[0]) + "  "
                                              + to_string(cartesian[1]) + "  "
                                              + to_string(cartesian[2]) );

// Calculate inverse kinematic in geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) ) {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        TakeshiTasks::printTakeshiTaskMessage("OmniBase correction: " + to_string(base_correction.x) + " " + to_string(base_correction.y) + " " +to_string(base_correction.theta));
        TakeshiTasks::printTakeshiTaskMessage("Torso correction: " + to_string(torso));

        TakeshiManip::armGoToArticular(articular, 2000);
        TakeshiManip::torsoGoTo(torso, 4000);

        TakeshiManip::openGripper(1.0);
        ros::Duration(2.5).sleep();

        TakeshiManip::torsoGoTo(torso, 1000);
        TakeshiNavigation::moveDist(-0.1,4000);
        articular[0] =  0.0;
        articular[1] =  0.0;
        articular[2] = -1.57;
        articular[3] =  0.0;
        TakeshiManip::armGoToArticular(articular, 1500);

        TakeshiManip::armGoToNavigation();
        TakeshiManip::openGripper(0.0);
        TakeshiManip::torsoGoTo(0.0, 2000);

        return true;

}


bool TakeshiTasks::findPerson(std::string person, int gender, POSE pose, bool recogByID) {

        TakeshiTasks::printTakeshiTaskMessage("Find person");
        TakeshiManip::navigationPose(4000);
        TakeshiVision::startFaceRecognition();
        std::vector<int> facesDistances;
        std::stringstream ss;
        std::string personID = "";

        TakeshiManip::hdGoTo(0,0.5, 3000);
        ss << person << ", I am going to find you";
        //JustinaHRI::waitAfterSay(ss.str(), 2000);
        TakeshiHRI::waitAfterSay(ss.str(), 3000);

        Eigen::Vector3d centroidFace;
        int genderRecog;
        if (recogByID) personID = person;
        bool recog = turnAndRecognizeFace(personID, gender, pose, -M_PI_4, M_PI_4 / 2.0, M_PI_4, 0.4, -M_PI_4, -M_PI_4, M_PI_2, M_PI/2, centroidFace, genderRecog);
        cout << "\033[1;34m     TakeshiTasks.->Centroid Face in coordinates of robot:" << centroidFace(0, 0)
             << "," << centroidFace(1, 0) << "," << centroidFace(2, 0) << ")\033[0m" << endl;
        //personLocation.clear();
        TakeshiVision::stopFaceRecognition();

        ss.str("");
        if (!recog) {

                cout << "\033[1;36m     TakeshiTasks.->I have not found a person \033[0m" << endl;
                (recogByID) ? ss << "I did not find you " << person : ss << "I did not find a person";
                //JustinaHRI::waitAfterSay(ss.str(), 2000);
                TakeshiHRI::say(ss.str());
                return false;
        }

        cout << "\033[1;36m     TakeshiTasks.->I have found a person " << person << "\033[0m" << endl;
        //ss << person << ", I found you";
        (recogByID) ? ss << person << ", I found you" : ss << ", I find a person";
        TakeshiManip::torsoGoTo(0.0,2000);
        TakeshiHRI::say(ss.str());
        TakeshiHRI::say("I am getting close to you");


        float cx, cy, cz;
        cx = centroidFace(0, 0);
        cy = centroidFace(1, 0);
        cz = centroidFace(2, 0);
        float dis = sqrt( pow(cx, 2) + pow(cy, 2) );
        TakeshiTools::transformPoint("/base_link", cx, cy, cz, "/map", cx, cy, cz);
        tf::Vector3 worldFaceCentroid(cx, cy, cz);

        int waitToClose = (int) (dis * 10000);

        cout << "\033[1;36m     TakeshiTasks.->dis:" << dis <<"\033[0m" << endl;
        cout << "\033[1;36m     TakeshiTasks.->waitToClose:" << waitToClose <<"\033[0m" << endl;


        //JustinaHRI::waitAfterSay("I am getting close to you", 2000);
        closeToGoalWithDistanceTHR(worldFaceCentroid.x(), worldFaceCentroid.y(), 1.0, waitToClose);
        TakeshiNavigation::enableObstacleDetection(false);
        return true;
}

bool TakeshiTasks::findPersonFacenet(std::string name, float anghd, bool get_close){
    vision_msgs::VisionFaceObjects vfo;
    float cx, cy, cz,cxr,cyr,ctheta; 
   

    for (size_t i = 0; i < 3; i++){
        vfo = TakeshiVision::facenetRecognize(name);   
        if(vfo.recog_faces.size()>0){

             //TakeshiTasks::turnAndRecognizeFacenet("unknown");
                    TakeshiHRI::waitAfterSay("I found you ! ",3000);
            TakeshiManip::torsoGoTo(0.0,2000);
            cx = vfo.recog_faces[0].face_centroid.x;
            cy = -vfo.recog_faces[0].face_centroid.y;
            cz = vfo.recog_faces[0].face_centroid.z;
           

            cxr= cos(anghd)*cx   -   cy* sin(anghd);
            cyr= sin(anghd)*cx   +   cy* cos(anghd);
            ctheta = atan2 (cyr,cxr);
           
            cx=cxr;
            cy=cyr;
            Eigen::Vector2d coordface(cx,cy);

            Eigen::Vector2d coordfacecorr(cx,cy);
            coordfacecorr = coordface - .8* coordface.normalized();
            cx= coordfacecorr(0);
            cy= coordfacecorr(1);

            
              float currtakx, currtaky, currtaktheta;
            TakeshiNavigation::getRobotPose(currtakx, currtaky, currtaktheta);
            TakeshiTools::transformPoint("/base_link", cx, cy, cz, "/map", cx, cy, cz);
            tf::Vector3 worldFaceCentroid(cx, cy, cz);
            ctheta= atan2 (currtaky- cy,currtakx-cx);

           
            TakeshiKnowledge::addUpdateKnownLoc(name, worldFaceCentroid.x(), worldFaceCentroid.y(),ctheta -3.1416  );
           

            if(get_close){
                TakeshiHRI::say("I am getting close to you");
                TakeshiManip::torsoGoTo(0,1000);
                    if(!TakeshiNavigation::getClose(name, 10000))
                       if(!TakeshiNavigation::getClose(name, 10000))
                            TakeshiNavigation::getClose(name, 10000);


                TakeshiManip::hdGoTo(0,0,3000);        
                if   (cz > 1.1)
                TakeshiManip::hdGoTo(0,.4,3000);
         
            }
            return true;
        }
    } 
    return false;   
}

bool TakeshiTasks::findPersonLoc(std::string person, int gender, POSE pose, bool recogByID, std::string location) {

        TakeshiTasks::printTakeshiTaskMessage("Find person");
        TakeshiManip::navigationPose(4000);
        TakeshiVision::startFaceRecognition();
        std::vector<int> facesDistances;
        std::stringstream ss;
        std::string personID = "";

        TakeshiManip::hdGoTo(0,0.5, 3000);
        ss << person << ", I am going to find you";
        //JustinaHRI::waitAfterSay(ss.str(), 2000);
        TakeshiHRI::waitAfterSay(ss.str(), 3000);

        Eigen::Vector3d centroidFace;
        int genderRecog;
        if (recogByID) personID = person;
        bool recog = turnAndRecognizeFaceGPSR(personID, gender, pose, -M_PI_4, M_PI_4 / 2.0, M_PI_4, 0.4, -M_PI_4, -M_PI_4, M_PI_2, M_PI/2, centroidFace, genderRecog, location);
        cout << "\033[1;34m     TakeshiTasks.->Centroid Face in coordinates of robot:" << centroidFace(0, 0)
             << "," << centroidFace(1, 0) << "," << centroidFace(2, 0) << ")\033[0m" << endl;
        //personLocation.clear();
        TakeshiVision::stopFaceRecognition();

        ss.str("");
        if (!recog) {

                cout << "\033[1;36m     TakeshiTasks.->I have not found a person \033[0m" << endl;
                (recogByID) ? ss << "I did not find you " << person : ss << "I did not find a person";
                //JustinaHRI::waitAfterSay(ss.str(), 2000);
                TakeshiHRI::say(ss.str());
                return false;
        }

        cout << "\033[1;36m     TakeshiTasks.->I have found a person " << person << "\033[0m" << endl;
        //ss << person << ", I found you";
        (recogByID) ? ss << person << ", I found you" : ss << ", I find a person";
        TakeshiManip::torsoGoTo(0.0,2000);
        TakeshiHRI::say(ss.str());
        TakeshiHRI::say("I am getting close to you");


        float cx, cy, cz;
        cx = centroidFace(0, 0);
        cy = centroidFace(1, 0);
        cz = centroidFace(2, 0);
        float dis = sqrt( pow(cx, 2) + pow(cy, 2) );
        TakeshiTools::transformPoint("/base_link", cx, cy, cz, "/map", cx, cy, cz);
        tf::Vector3 worldFaceCentroid(cx, cy, cz);

        int waitToClose = (int) (dis * 10000);

        cout << "\033[1;36m     TakeshiTasks.->dis:" << dis <<"\033[0m" << endl;
        cout << "\033[1;36m     TakeshiTasks.->waitToClose:" << waitToClose <<"\033[0m" << endl;


        //JustinaHRI::waitAfterSay("I am getting close to you", 2000);
        closeToGoalWithDistanceTHR(worldFaceCentroid.x(), worldFaceCentroid.y(), 1.0, waitToClose);
        TakeshiNavigation::enableObstacleDetection(false);
        return true;
}

bool TakeshiTasks::turnAndRecognizeFace(std::string id, int gender, POSE pose, float initAngPan, float incAngPan, float maxAngPan, float initAngTil, float incAngTil, float maxAngTil, float incAngleTurn, float maxAngleTurn, Eigen::Vector3d &centroidFace, int &genderRecog) {

        bool recog = false;
        bool moveBase = false;
        float initTil = initAngTil;
        float incTil = incAngTil;
        bool direction = false;
        centroidFace = Eigen::Vector3d::Zero();

        if(pose == STANDING)
                maxAngTil = initAngTil;

        for(float baseTurn = incAngleTurn; ros::ok() && baseTurn <= maxAngleTurn && !recog; baseTurn+=incAngleTurn) {
                for(float headPanTurn = initAngPan; ros::ok() && headPanTurn <= maxAngPan && !recog; headPanTurn+=incAngPan) {
                        float currTil;
                        for (float headTilTurn = initTil; ros::ok() && ((!direction && headTilTurn >= maxAngTil) || (direction && headTilTurn <= initAngTil)) && !recog; headTilTurn+=incTil) {
                                currTil = headTilTurn;
                                TakeshiManip::startHdGoTo(headPanTurn, headTilTurn);
                                if(moveBase) {
                                        TakeshiNavigation::moveDistAngle(0.0, incAngleTurn, 4000);
                                        moveBase = false;
                                }
                                TakeshiManip::waitForHdGoalReached(3000);
                                boost::this_thread::sleep(boost::posix_time::milliseconds(500));
                                std::vector<vision_msgs::VisionFaceObject> facesObject;
                                recog = waitRecognizedFace(2000, id, gender, pose, facesObject);
                                if(recog)
                                        //recog = getNearestRecognizedFace(facesObject, 4.0, centroidFace, genderRecog);
                                        recog = getNearestRecognizedFace(facesObject, 4.0, centroidFace, genderRecog);
                        }
                        initTil = currTil;
                        direction ^= true;
                        incTil *= -1;
                }
                moveBase = true;
        }
        return recog;
}

bool TakeshiTasks::turnAndRecognizeFacenet(std::string name, bool get_close){

    std::vector<float> arm;
    int hdposestate=1;
    float anghd;
    arm.push_back(-0.3);
    arm.push_back(-1.7);
    arm.push_back(-1.5);
    arm.push_back(0.0);

    TakeshiManip::armGoToArticular(arm,3000);
    while(hdposestate!=0){
        switch (hdposestate){
            case 1:
            anghd=0;
            TakeshiManip::torsoGoTo(.2,1000);
            TakeshiManip::hdGoTo(anghd, 0, 3000);
            std::cout << "hdposestat "<<hdposestate<<std::endl;
            findPersonFacenet(name, anghd,get_close)? hdposestate=0: hdposestate++;
            break;

         
            case 2:
            anghd= -0.70;
            TakeshiManip::torsoGoTo(.2,1000);
            TakeshiManip::hdGoTo(anghd, 0, 3000);                   
            std::cout << "hdposestat "<<hdposestate<<std::endl;
            findPersonFacenet(name, anghd,get_close)? hdposestate=0: hdposestate++;
            break;

            case 3:
            anghd= 0.70;
            TakeshiManip::torsoGoTo(.2,1000);
            TakeshiManip::hdGoTo(anghd, 0, 3000);                   
            std::cout << "hdposestat "<<hdposestate<<std::endl;
            if(findPersonFacenet(name, anghd,get_close)) hdposestate=0;
            else return false;
            break;
        }
    }
    return true;
}

bool TakeshiTasks::getNearestRecognizedFace(std::vector<vision_msgs::VisionFaceObject> facesObject, float distanceMax, Eigen::Vector3d &faceCentroid, int &genderRecog) {
        int indexMin;
        float distanceMin = 99999999.0;
        faceCentroid = Eigen::Vector3d::Zero();
        bool found = false;
        for (int i = 0; i < facesObject.size(); i++) {
                vision_msgs::VisionFaceObject vro = facesObject[i];
                Eigen::Vector3d centroid = Eigen::Vector3d::Zero();
                centroid(0, 0) = vro.face_centroid.x;
                centroid(1, 0) = vro.face_centroid.y;
                centroid(2, 0) = vro.face_centroid.z;
                float dist = centroid.norm();
                if (dist < distanceMax && dist < distanceMin) {
                        indexMin = i;
                        distanceMin = dist;
                        found = true;
                }
        }
        if (found) {

                cout << "\033[1;36m     TakeshiTasks.->I found the centroid nearest to robot\033[0m" << endl;

                faceCentroid(0, 0) = facesObject[indexMin].face_centroid.x;
                faceCentroid(1, 0) = facesObject[indexMin].face_centroid.y;
                faceCentroid(2, 0) = facesObject[indexMin].face_centroid.z;
                genderRecog = facesObject[indexMin].gender;
        }
        cout << "\033[1;34m     TakeshiTasks.->Face centroid:" << faceCentroid(0, 0) << ","
             << faceCentroid(1, 0) << "," << faceCentroid(2, 0)<< "\033[0m" << endl;
        return found;
}

void TakeshiTasks::closeToGoalWithDistanceTHR(float goalX, float goalY, float thr, float timeout){
        float currx, curry, currtheta;
        bool finishReachedPerson = false;

        float distanceToGoal;
        TakeshiKnowledge::getRobotPose(currx, curry, currtheta);
        distanceToGoal = sqrt(
                pow(goalX - currx, 2)
                + pow(goalY - curry, 2));
        if (distanceToGoal > thr) {
                TakeshiNavigation::startGetClose(goalX, goalY);
                boost::posix_time::ptime prev = boost::posix_time::second_clock::local_time();
                boost::posix_time::ptime curr = prev;
                do {
                        TakeshiKnowledge::getRobotPose(currx, curry, currtheta);
                        distanceToGoal = sqrt(pow(goalX - currx, 2) + pow(goalY - curry, 2));
                        if ((TakeshiNavigation::obstacleInFront() && distanceToGoal < thr) || distanceToGoal < thr)
                                finishReachedPerson = true;
                        else
                                boost::this_thread::sleep(boost::posix_time::milliseconds(100));
                        ros::spinOnce();
                        curr = boost::posix_time::second_clock::local_time();
                } while (ros::ok() && !finishReachedPerson && ((curr - prev).total_milliseconds() < timeout || timeout == 0));
                cout << "\033[1;36m     TakeshiTasks.->I have the reached position.\033[0m" << endl;

                TakeshiHardware::stopRobot();
                boost::this_thread::sleep(boost::posix_time::milliseconds(500));
                ros::spinOnce();
        } else
                cout << "\033[1;36m     TakeshiTasks.->Robot dont need to move..\033[0m" << endl;

        float thetaToGoal = atan2(goalY - curry, goalX - currx);
        if (thetaToGoal < 0.0f)
                thetaToGoal = 2 * M_PI + thetaToGoal;
        float theta = thetaToGoal - currtheta;
        cout << "\033[1;34m     TakeshiTasks.->Turn in direction of robot:" << theta <<"\033[0m" << endl;
        TakeshiNavigation::moveDistAngle(0, theta, 2000);

        TakeshiManip::startHdGoTo(0, 0);
        TakeshiManip::waitForHdGoalReached(5000);
}

bool TakeshiTasks::waitRecognizedGesture(std::vector<vision_msgs::GestureSkeleton> &gestures, float timeout){
        printTakeshiTaskMessage("Wait For Recognized Gesture");
        boost::posix_time::ptime curr;
        boost::posix_time::ptime prev = boost::posix_time::second_clock::local_time();
        boost::posix_time::time_duration diff;
        bool recognized;
        do {
                boost::this_thread::sleep(boost::posix_time::milliseconds(200));
                ros::spinOnce();
                TakeshiVision::getLastGesturesRecognize(gestures);
                curr = boost::posix_time::second_clock::local_time();
        } while (ros::ok() && (curr - prev).total_milliseconds() < timeout
                 && gestures.size() == 0);

        if (gestures.size() > 0)
                recognized = true;
        else
                recognized = false;
        printTakeshiTaskMessage("Gestures Recognized: " + to_string(gestures.size()));
        return recognized;
}

bool TakeshiTasks::waitForSpecificGesture(vision_msgs::GestureSkeleton &gesture, std::vector<std::string> specificGesture, float timeout){
        boost::posix_time::ptime curr;
        boost::posix_time::ptime prev = boost::posix_time::second_clock::local_time();
        boost::posix_time::time_duration diff;
        std::vector<vision_msgs::GestureSkeleton> gestures;
        bool recognized;
        int indexGesture;

        do {
                boost::this_thread::sleep(boost::posix_time::milliseconds(200));
                ros::spinOnce();
                TakeshiVision::getLastGesturesRecognize(gestures);
                recognized=TakeshiTasks::findGesture(gestures, specificGesture, indexGesture);
                curr = boost::posix_time::second_clock::local_time();
        } while (ros::ok() && (curr - prev).total_milliseconds() < timeout
                 && !recognized);

        if (recognized) {
                gesture=gestures[indexGesture];
                printTakeshiTaskMessage("Specific Gesture was recognized");
        }
        else
                printTakeshiTaskError("Specific gesture was not recognized");
        return recognized;
}

bool TakeshiTasks::findGesture(std::vector<vision_msgs::GestureSkeleton> gestures, std::vector<std::string> specificGesture, int& indexGesture){
        for(int i=0; i< specificGesture.size(); i++)
                printTakeshiTaskMessage("Find gesture: " + specificGesture[i]);
        for(int i=0; i< gestures.size(); i++) {
                for(int j=0; j<specificGesture.size(); j++) {
                        if(gestures[i].gesture.compare(specificGesture[j])==0 && gestures[i].gesture_centroid.x < 10 && fabs(gestures[i].gesture_centroid.y) < 5) {
                                printTakeshiTaskMessage("Gesture was recognized: " + gestures[i].gesture);
                                indexGesture=i;
                                return true;
                        }
                }
        }
        printTakeshiTaskError("Gesture was not recognized");
        return false;
}

bool TakeshiTasks::getPanoramic(float initAngTil, float incAngTil, float maxAngTil, float initAngPan, float incAngPan, float maxAngPan, sensor_msgs::Image &image, float timeout){
        bool genPano = false;
        float initTil = initAngTil;
        float incTil = incAngTil;
        bool direction = false;
        ros::Rate rate(20);
        boost::posix_time::ptime curr;
        boost::posix_time::ptime prev = boost::posix_time::second_clock::local_time();
        TakeshiVision::clearPano();
        for(float headPanTurn = initAngPan; ros::ok() && headPanTurn <= maxAngPan; headPanTurn+=incAngPan) {
                float currTil;
                float headTilTurn;
                for (headTilTurn = initTil; ros::ok() && ((!direction && headTilTurn >= maxAngTil) || (direction && floor(headTilTurn) <= floor(initAngTil))); headTilTurn+=incTil) {
                        currTil = headTilTurn;
                        TakeshiManip::startHdGoTo(headPanTurn, headTilTurn);
                        TakeshiManip::waitForHdGoalReached(3000);
                        boost::this_thread::sleep(boost::posix_time::milliseconds(1500));
                        TakeshiVision::takePano();
                        boost::this_thread::sleep(boost::posix_time::milliseconds(500));
                }
                bool bandera = headTilTurn <= initAngTil + 0.00001;
                initTil = currTil;
                direction ^= true;
                incTil *= -1.0f;
        }

        TakeshiManip::startHdGoTo(0.0, 0.0);
        TakeshiManip::waitForHdGoalReached(3000);
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

        TakeshiVision::makePano();
        do {
                rate.sleep();
                ros::spinOnce();
                curr = boost::posix_time::second_clock::local_time();
                genPano = TakeshiVision::isPanoImageRecived();
        } while(ros::ok() && (curr - prev).time_duration::total_milliseconds() <= timeout && !genPano);
        if(genPano)
                image = TakeshiVision::getLastPanoImage();
        return genPano;
}


bool TakeshiTasks::waitRecognizedFace(
        float timeout, std::string id, int gender, POSE pose, std::vector<vision_msgs::VisionFaceObject> &facesRecog) {
        boost::posix_time::ptime curr;
        boost::posix_time::ptime prev = boost::posix_time::second_clock::local_time();
        boost::posix_time::time_duration diff;
        bool recognized;
        std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
        do {
                lastRecognizedFaces = TakeshiVision::getFaces(id).recog_faces;
                curr = boost::posix_time::second_clock::local_time();
        } while (ros::ok() && (curr - prev).total_milliseconds() < timeout
                 && lastRecognizedFaces.size() == 0);

        if(pose != NONE) {
                for(int i = 0; i < lastRecognizedFaces.size(); i++) {
                        if(pose == STANDING && lastRecognizedFaces[i].face_centroid.z > 1.2)
                                facesRecog.push_back(lastRecognizedFaces[i]);
                        else if(pose == SITTING && lastRecognizedFaces[i].face_centroid.z > 0.8 && lastRecognizedFaces[i].face_centroid.z <= 1.2)
                                facesRecog.push_back(lastRecognizedFaces[i]);
                        else if(pose == LYING && lastRecognizedFaces[i].face_centroid.z > 0.1 && lastRecognizedFaces[i].face_centroid.z <= 0.8)
                                facesRecog.push_back(lastRecognizedFaces[i]);
                }
                lastRecognizedFaces = facesRecog;
                facesRecog.clear();
        }

        if(gender != -1) {
                for(int i = 0; i < lastRecognizedFaces.size(); i++) {
                        if(lastRecognizedFaces[i].gender == gender)
                                facesRecog.push_back(lastRecognizedFaces[i]);
                }
        }
        else
                facesRecog = lastRecognizedFaces;

        if (facesRecog.size() > 0)
                recognized = true;
        else
                recognized = false;

        cout << "\033[1;36m     TakeshiTasks.->Recognized:" << recognized <<"\033[0m" << endl;

        return recognized;
}


bool TakeshiTasks::waitRecognizedFacenet(
        float timeout, std::string id, int gender, POSE pose, std::vector<vision_msgs::VisionFaceObject> &facesRecog) {
        boost::posix_time::ptime curr;
        boost::posix_time::ptime prev = boost::posix_time::second_clock::local_time();
        boost::posix_time::time_duration diff;
        bool recognized;
        vision_msgs::VisionFaceObjects vfo;
        std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
        do {
                vfo = TakeshiVision::facenetRecognize(id);
                lastRecognizedFaces = vfo.recog_faces;
                curr = boost::posix_time::second_clock::local_time();
        } while (ros::ok() && (curr - prev).total_milliseconds() < timeout
                 && lastRecognizedFaces.size() == 0);

        if(pose != NONE) {
                for(int i = 0; i < lastRecognizedFaces.size(); i++) {
                        if(pose == STANDING && lastRecognizedFaces[i].face_centroid.z > 1.2)
                                facesRecog.push_back(lastRecognizedFaces[i]);
                        else if(pose == SITTING && lastRecognizedFaces[i].face_centroid.z > 0.8 && lastRecognizedFaces[i].face_centroid.z <= 1.2)
                                facesRecog.push_back(lastRecognizedFaces[i]);
                        else if(pose == LYING && lastRecognizedFaces[i].face_centroid.z > 0.1 && lastRecognizedFaces[i].face_centroid.z <= 0.8)
                                facesRecog.push_back(lastRecognizedFaces[i]);
                }
                lastRecognizedFaces = facesRecog;
                facesRecog.clear();
        }

        if(gender != -1) {
                for(int i = 0; i < lastRecognizedFaces.size(); i++) {
                        if(lastRecognizedFaces[i].gender == gender)
                                facesRecog.push_back(lastRecognizedFaces[i]);
                }
        }
        else
                facesRecog = lastRecognizedFaces;

        if (facesRecog.size() > 0)
                recognized = true;
        else
                recognized = false;

        cout << "\033[1;36m     TakeshiTasks.->Recognized:" << recognized <<"\033[0m" << endl;

        return recognized;
}


bool TakeshiTasks::guidePerson(std::string location, int timeOut_ms){

        cout << "\033[1;36m     TakeshiTasks.->Guide Person\033[0m" << endl;

        int counter;
        counter = 0;
        while(!TakeshiNavigation::getClose(location, timeOut_ms) && ros::ok()) {
                cout << "\033[1;34m     TakeshiTasks.->Guide Person\033[0m" << endl;

                TakeshiHardware::stopRobot();
                TakeshiManip::hdGoTo(-3.14159, 0.7, 3000);
                ros::spinOnce();
                ros::Duration(2.0).sleep();
                TakeshiManip::hdGoTo(-3.14159, 0.7, 3000);

                std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
                lastRecognizedFaces = TakeshiVision::getFaces("").recog_faces;

                while(lastRecognizedFaces.size() < 1 && ros::ok())
                {
                        TakeshiHRI::waitAfterSay("Please, stand behind me",3000);
                        ros::spinOnce();
                        ros::Duration(2.0).sleep();
                        lastRecognizedFaces = TakeshiVision::getFaces("").recog_faces;
                        if(counter > 5)
                                break;
                        counter++;
                }

                TakeshiHRI::waitAfterSay("ok, i see you",1500);
                TakeshiVision::stopFaceRecognition();

                /*
                   Eigen::Vector3d centroidFace;
                   int genderRecog;
                   bool recog = recognizeFace(-1, TakeshiTasks::STANDING,-M_PI_4, M_PI_4/2.0, M_PI_4, 0, -M_PI_4, -M_PI_4,centroidFace, genderRecog);
                   if(recog){
                    TakeshiHRI::say("You are behind me, lets go");

                    cout << "\033[1;36m     TakeshiTasks.->Guide Person: PERSON OK\033[0m" << endl;
                   }
                   else{
                    TakeshiHRI::say("Please, stand behind me");
                    cout << "\033[1;36m     TakeshiTasks.->Guide Person: NO PERSON\033[0m" << endl;

                    while(!recog){
                        recog = recognizeFace(-1, TakeshiTasks::STANDING,-M_PI_4, M_PI_4/2.0, M_PI_4, 0, -M_PI_4, -M_PI_4,centroidFace, genderRecog);
                        TakeshiHRI::waitAfterSay("Please, stand behind me",3000);
                    }
                 */

        }
    return true;

}
bool TakeshiTasks::guidePersonFacenet(std::string location,std::string id, int timeOut_ms){

        cout << "\033[1;36m     TakeshiTasks.->Guide Person Facenet\033[0m" << endl;

        int counter;
        counter = 0;
        std::vector<float> arm;
    //arm pointing
        arm.push_back(-0.4);
        arm.push_back(-1.57);
        arm.push_back(-1.57);
        arm.push_back(0.0);
        while(!TakeshiNavigation::getClose(location, timeOut_ms) && ros::ok()) {
                cout << "\033[1;34m     TakeshiTasks.->Guide Person\033[0m" << endl;

                TakeshiHardware::stopRobot();
                TakeshiManip::armGoToArticular(arm,3000);
                TakeshiManip::torsoGoTo(.4,1000);
                TakeshiManip::hdGoTo(-3.14159, 0.3, 3000);
                ros::spinOnce();
                ros::Duration(2.0).sleep();
                TakeshiManip::armGoToArticular(arm,3000);
                TakeshiManip::torsoGoTo(.4,1000);
                TakeshiManip::hdGoTo(-3.14159, 0.3, 3000);

                //std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;
                //lastRecognizedFaces = TakeshiVision::getFaces("").recog_faces;
                vision_msgs::VisionFaceObjects vfo;
                vfo = TakeshiVision::facenetRecognize(id);

                while(vfo.recog_faces.size()<1 && ros::ok())
                {
                        if(id==""||id=="unknown") TakeshiHRI::waitAfterSay("Please, stand behind me",3000);
                        else TakeshiHRI::waitAfterSay(id+" stand behind me",3000);
                        ros::spinOnce();
                        ros::Duration(2.0).sleep();
                        vfo = TakeshiVision::facenetRecognize(id);
                        if(counter > 5)
                                break;
                        counter++;
                }

                TakeshiHRI::waitAfterSay("ok, i see you",1500);
                //TakeshiVision::stopFaceRecognition();

        }
    return true;
}

bool TakeshiTasks::followAPerson(std::string stopRecog)
{
        //STATE machine to follow a person
        followState nextState = SM_WAIT_FOR_OPERATOR;
        bool succes = false;
        ros::Rate rate(10);
        std::string lastRecoSpeech;
        std::vector<std::string> validCommandsStop;
        validCommandsStop.push_back(stopRecog);

        while (ros::ok() && !succes)
        {
                switch (nextState) {
                case SM_WAIT_FOR_OPERATOR:
                        std::cout << "SM_WAIT_FOR_OPERATOR" << '\n';
                        TakeshiHRI::waitAfterSay("Please say, follow me, to start following you", 3000);
                        if(TakeshiHRI::waitForSpecificSentence("follow me",15000))
                        {
                                nextState = SM_MEMORIZING_OPERATOR;
                        }
                        break;
                case SM_MEMORIZING_OPERATOR:
                        std::cout << "SM_MEMORIZING_OPERATOR" << '\n';
                        TakeshiHRI::waitAfterSay("Human I will follow you.",4000);
                        TakeshiHRI::enableLegFinder(true);
                        nextState = SM_WAIT_FOR_LEGS_FOUND;
                        break;
                case SM_WAIT_FOR_LEGS_FOUND:
                        std::cout << "SM_WAIT_FOR_LEGS_FOUND"  << '\n';
                        if (TakeshiHRI::frontalLegsFound())
                        {
                                TakeshiHRI::waitAfterSay("I found you, please walk. Tell me: stop follow me, when we reach the goal", 4000);
                                TakeshiHRI::startFollowHuman();
                                nextState = SM_FOLLOWING_PHASE;
                        }
                        break;
                case SM_FOLLOWING_PHASE:
                        std::cout << "SM_FOLLOWING_PHASE" << '\n';
                        if(TakeshiHRI::waitForSpecificSentence(validCommandsStop, lastRecoSpeech, 7000))
                        {
                                TakeshiHRI::stopFollowHuman();
                                TakeshiHRI::enableLegFinder(false);
                                TakeshiHRI::waitAfterSay("I stopped", 1500);
                                nextState = SM_FOLLOWING_FINISHED;
                                break;
                        }
                        if (!TakeshiHRI::frontalLegsFound())
                        {
                                std::cout << "Lost target" << '\n';
                                TakeshiHRI::waitAfterSay("I lost you",1500);
                        }
                case SM_FOLLOWING_FINISHED:
                        std::cout << "SM_FOLLOWING_FINISHED" << '\n';
                        TakeshiHRI::waitAfterSay("Ok i will stop following you.",3000);
                        succes = true;
                        break;
                }
                rate.sleep();
                ros::spinOnce();
        }
        return succes;
}

bool TakeshiTasks::recognizeFace(int gender, POSE pose, float initAngPan, float incAngPan, float maxAngPan, float initAngTil, float incAngTil, float maxAngTil, Eigen::Vector3d &centroidFace, int &genderRecog) {

        bool recog = false;
        bool moveBase = false;
        float initTil = initAngTil;
        float incTil = incAngTil;
        bool direction = false;
        std::string id="";

        centroidFace = Eigen::Vector3d::Zero();

        if(pose == STANDING)
                maxAngTil = initAngTil;

        for(float headPanTurn = initAngPan; ros::ok() && headPanTurn <= maxAngPan && !recog; headPanTurn+=incAngPan) {
                float currTil;
                for (float headTilTurn = initTil; ros::ok() && ((!direction && headTilTurn >= maxAngTil) || (direction && headTilTurn <= initAngTil)) && !recog; headTilTurn+=incTil) {
                        currTil = headTilTurn;
                        TakeshiManip::hdGoTo(headPanTurn, headTilTurn,3000);
                        boost::this_thread::sleep(boost::posix_time::milliseconds(500));
                        std::vector<vision_msgs::VisionFaceObject> facesObject;
                        recog = waitRecognizedFace(2000, id, gender, pose, facesObject);

                        if(recog)
                                recog = getNearestRecognizedFace(facesObject, 2.0, centroidFace, genderRecog);
                }

                initTil = currTil;
                direction ^= true;
                incTil = -incTil;
        }

        return recog;
}

bool TakeshiTasks::trainObjectOnline(std::string objectName, std::string& unknownObject1){

        std::vector<vision_msgs::VisionObject> recognizedObjects;
        std::vector<std::string> validCommands;
        std::vector<std::string> validObjects;
        string lastRecoSpeech;
        ros::Rate loop(10);

        validCommands.push_back("takeshi train");
        validCommands.push_back("takeshi train the object");
        validCommands.push_back("train the object");

        validCommands.push_back("yellow towel");
        validCommands.push_back("table cloth");
        validCommands.push_back("mitten");
        validCommands.push_back("sponge");
        validCommands.push_back("stationery holder");
        validCommands.push_back("kitchen brush");
        validCommands.push_back("mustard");
        validCommands.push_back("soap bottle");

        TakeshiVision::startQRReader();

        bool foundObject=false;
        bool waitCommand=false;
        bool fail=false;
        bool success=false;
        int nextState=0;
        int numberOfTraining=0;
        string sayObject;

        cout << "\033[1;34m     TakeshiTasks.->Train Object Online\033[0m" << endl;

        while(ros::ok() && !fail && !success && !TakeshiHardware::isTaskStop()) {
                switch (nextState) {
                case 0:
                        TakeshiTasks::alignWithTable(0.35, false);
                        TakeshiHRI::enableSpeechRecognized(true);
                        TakeshiHRI::loadGrammarSpeechRecognized("tokio_train_online_test");
                        nextState=1;
                        break;

                case 1:
                        TakeshiVision::trainObject(objectName);
                        if(TakeshiVision::isObjectTrained()) {
                                TakeshiHRI::waitAfterSay("I found the object",1000);
                                TakeshiHRI::enableSpeechRecognized(true);
                                numberOfTraining++;
                                cout << "\033[1;34m     TakeshiTasks.->Numbre of training: "<<numberOfTraining <<"\033[0m" << endl;
                                TakeshiHRI::waitAfterSay("For training the object, you can rotate the object about 45 degrees. After that, tell me, Takeshi train. Let's start",1000);
                                nextState=2;
                        }
                        else{
                                TakeshiHRI::waitAfterSay("human, i can't detect the object",1000);
                        }

                        break;
                case 2:
                        if(TakeshiHRI::waitForSpecificSentence(validCommands, lastRecoSpeech, 4000)) {
                                if(lastRecoSpeech.find("takeshi train the object") != std::string::npos || lastRecoSpeech.find("train the object") != std::string::npos || lastRecoSpeech.find("takeshi train") != std::string::npos)
                                        TakeshiHRI::waitAfterSay("wait", 1000);
                                ros::Duration(2.0).sleep();
                                nextState=3;
                        }
                        break;

                case 3:
                        TakeshiVision::trainObject(objectName);
                        if(TakeshiVision::isObjectTrained()) {
                                if(numberOfTraining >= 10) {
                                        nextState=4;
                                        break;
                                }
                                TakeshiHRI::waitAfterSay("I've saved the pattern", 5000);
                                numberOfTraining++;
                                cout << "\033[1;34m     TakeshiTasks.->Number of training: "<<numberOfTraining <<"\033[0m" << endl;

                        }
                        else{
                                TakeshiHRI::waitAfterSay("human, i can't detect the object",1000);

                        }
                        nextState=2;
                        break;

                case 4:
                        TakeshiHRI::waitAfterSay("that's it all",1000);
                        TakeshiHRI::say("please, put the QR code with the name of the object in front of me");
                        TakeshiManip::hdGoTo(1.5707, 0.0, 5000);
                        nextState=5;
                        break;

                case 5:
                        TakeshiVision::read_QR(unknownObject1);
                        cout << "\033[1;34m     TakeshiTasks.->Object trained: "<<unknownObject1 <<"\033[0m" << endl;
                        nextState=6;
                        break;

                case 6:
                        sayObject="the object is " + unknownObject1 + " . Thank You";
                        TakeshiHRI::waitAfterSay(sayObject,5000);
                        TakeshiVision::loadObjectTrainDir();
                        TakeshiHardware::restartTime();
                        TakeshiVision::stopQRReader();
                        success=true;
                        break;
                }

                ros::spinOnce();
                loop.sleep();
        }

        if (TakeshiHardware::isTaskStop()) {
                TakeshiHardware::restartTime();
                ros::spinOnce();
                loop.sleep();
                TakeshiHRI::waitAfterSay("My time is over",1000);
                ros::spinOnce();
                loop.sleep();
                return false;
        }
        return true;
}

/////////////////////////////////////////////////////////
//*****************************************************//
//        ********    GRASPFUNCTIONS   ******          //

///////////////////////////////////
//****  Takeshi verified   ******//
bool TakeshiTasks::graspYoloObject(std::vector<std::string> idObjects,std::vector<vision_msgs::VisionObject>& recognizedYoloObjects,int attempts, int timeOut, bool verify, vision_msgs::ObjectCoordinatesForDetection objectCoordinates){
        geometry_msgs::Pose pose;
        float x,y,z;
        int nextState=1;
        bool fail=false;
        ros::Rate loop(30);
        TakeshiTasks::alignWithFrontTable();

        if(idObjects.size() > 0){
            
            while(ros::ok() && attempts > 0){
                switch(nextState){
                    case 1:
                        printTakeshiTaskMessage("\n\nGrasp Specific objects");
                        
                        if(!TakeshiVision::detectSpecificYoloObject(idObjects,recognizedYoloObjects,4000,objectCoordinates)){
                            TakeshiHRI::say("I can not detect the object");
                            printTakeshiTaskError("Can not detect yolo objects");
                            if(attempts > 0){
                                attempts--;
                                nextState=1; 
                                break;
                            }
                            else
                                return false;
                            break;
                        }    
                        TakeshiHRI::say("I will grasp the " + recognizedYoloObjects[0].id);
                        printTakeshiTaskMessage("Object ID" + recognizedYoloObjects[0].id);
                        nextState=2;
                        break;

                    case 2:
                        x = recognizedYoloObjects[0].pose.position.x;
                        y = recognizedYoloObjects[0].pose.position.y;
                        z = recognizedYoloObjects[0].pose.position.z;
                        printTakeshiTaskMessage("Attempt: "+ std::to_string(attempts));
                        attempts--;
                        if(TakeshiTasks::graspObject(x, y, z, verify, fail))
                            return true;
                        else{
                            if(fail){
                                printTakeshiTaskError("Grasp fail");
                                nextState=1;
                                break;
                            }
                            else{
                                TakeshiHRI::say("I'm verifying if I grasped the object");  
                                if(!TakeshiVision::detectYoloObject(recognizedYoloObjects[0].id,recognizedYoloObjects[0],4000,objectCoordinates)){
                                    TakeshiHRI::say( "I took the object");
                                    TakeshiManip::navigationPose(4000);
                                    return true;
                                }
                                else{
                                    TakeshiHRI::say("I can not grasp the object");  
                                    printTakeshiTaskError("Can not grasp object: vision verify");
                                    
                                    if(attempts > 0)
                                        TakeshiHRI::say("I will try again"); 
                                        nextState=2;     
                                    }
                                }
                            }
                        break;
                        }
                ros::spinOnce();
                loop.sleep();
                }
            TakeshiManip::navigationPose(4000);
            return false;
        }
        else{
            while(ros::ok() && attempts > 0){
                switch(nextState){
                    case 1:
                        printTakeshiTaskMessage("\n\nGrasp Yolo Object");
                        
                        if(!TakeshiVision::detectAllYoloObjects(recognizedYoloObjects,timeOut,objectCoordinates)){
                            TakeshiHRI::say("I can not detect the object");
                            printTakeshiTaskError("Can not detect yolo objects");
                            if(attempts > 0){
                                attempts--;
                                nextState=1; 
                            }
                            else
                                return false;
                            break;
                        }    
                        TakeshiHRI::say("I will grasp the " + recognizedYoloObjects[0].id);
                        printTakeshiTaskMessage("Object ID" + recognizedYoloObjects[0].id);
                        nextState=2;
                        break;

                    case 2:
                        x = recognizedYoloObjects[0].pose.position.x;
                        y = recognizedYoloObjects[0].pose.position.y;
                        z = recognizedYoloObjects[0].pose.position.z;
                        printTakeshiTaskMessage("Attempt: "+ std::to_string(attempts));
                        attempts--;
                        if(TakeshiTasks::graspObject(x, y, z, verify, fail))
                            return true;
                        else{
                            if(fail){
                                printTakeshiTaskError("Grasp fail");
                                nextState=1;
                                break;
                            }
                            else{
                                TakeshiHRI::say("I'm verifying if I grasped the object");  
                                if(!TakeshiVision::detectYoloObject(recognizedYoloObjects[0].id,recognizedYoloObjects[0],4000,objectCoordinates)){
                                    TakeshiHRI::say( "I took the object");
                                    TakeshiManip::navigationPose(4000);
                                    return true;
                                }
                                else{
                                    TakeshiHRI::say("I can not grasp the object");  
                                    printTakeshiTaskError("Can not grasp object: vision verify");
                                    
                                    if(attempts > 0)
                                        TakeshiHRI::say("I will try again"); 
                                        nextState=2;     
                                    }
                                }
                            }
                        break;
                        }
                ros::spinOnce();
                loop.sleep();
                }
            TakeshiManip::navigationPose(4000);
            return false;
        }        
}


bool TakeshiTasks::graspObject(std::string idObject, bool verify)
{
        geometry_msgs::Pose pose;
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        float x,y,z;

        ///?????????????????????
        TakeshiManip::torsoGoTo(0.15, 4000);

        // If NO id object, grap the nearest object
        if(idObject.compare("") != 0)
        {
                std::cout << "Look for specific object...  " << '\n';
                while (!TakeshiTasks::findObject(idObject, pose, TakeshiTasks::CENTERDOWN) && ros::ok())
                        cout << "No object!!!!" << endl;

                // Variables for inverse kinematic calculate
                x = pose.position.x;
                y = pose.position.y;
                z = pose.position.z;
        }
        else
        {
                std::cout << "Look for NO-SPECIFIC object... " << '\n';
                // // Find object again and correct the new angle
                while (!TakeshiVision::detectObjects(recognizedObjects, false) && ros::ok())
                        cout << "Nothing detected!!!!" << endl;

                //Supouse first objReco is the nearest object
                std::cout << "Obj_position:" << recognizedObjects[0].pose.position
                          << std::endl;
                x = recognizedObjects[0].pose.position.x;
                y = recognizedObjects[0].pose.position.y;
                z = recognizedObjects[0].pose.position.z;
        }

        return TakeshiTasks::graspObject(x, y, z, verify);
}

bool TakeshiTasks::graspObject(float x, float y, float z, bool verify){
    bool fail=false;
    return TakeshiTasks::graspObject(x,y,z,verify,fail);
} 

bool TakeshiTasks::graspObject(float x, float y, float z, bool verify, bool& fail)
{
        // Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;
        vision_msgs::ObjectCoordinatesForDetection graspObjectCoordinates;
        float torso;
        float y_correction;

        printTakeshiTaskMessage("\n\nGrasp Object: Object Position x: "+ std::to_string(x) + " y: " + std::to_string(y) + " z:" + std::to_string(z));

        graspObjectCoordinates=TakeshiVision::objectCoordinates;
        graspObjectCoordinates.x_max=0.7;
        graspObjectCoordinates.y_min=-0.5;
        graspObjectCoordinates.y_max=0.5;

        if(!TakeshiVision::isGraspeable(x,y,z,graspObjectCoordinates)){
                TakeshiHRI::say("I can not detect the object in front of me.");
                printTakeshiTaskError("I can not detect the object in front of me.");
                fail=true;
                return false;
        }

        if((y - 0.10) < 0)
                y_correction = y - 0.10;  // 0.10 is the distance from base_arm to robot_base in axis Y //yo digo que 12
        else
                y_correction = y - 0.02;

        printTakeshiTaskMessage("Grasp Object: Y correction: " + std::to_string(y_correction));
        TakeshiNavigation::moveLateral(y_correction, 4000);

        ////////////////////////////////////////////
        //       FIST STEP OF MOVEMENT ARM        //
        //Pre-grasp pose
        cartesian.resize(3);
        cartesian[0] = x - 0.15;
        cartesian[1] = 0.10;
        cartesian[2] = z + 0.05;

        printTakeshiTaskMessage("Grasp Object:[Before correction]  try calculate Inverse Kinematic "
                  + std::to_string(cartesian[0]) + "  "
                  + std::to_string(cartesian[1]) + "  "
                  + std::to_string(cartesian[2]));

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) ){
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                printTakeshiTaskError("I can not calculate the Inverse Kinematic.");
                fail=true;
                return false;
        }

        for (int i=0; i < articular.size(); i++)
            printTakeshiTaskMessage("Articular: " + std::to_string(i) + ": " + std::to_string(articular[i]));
        printTakeshiTaskMessage("OmniBase correction: " + std::to_string(base_correction.x) + " " + std::to_string(base_correction.y) + " " + std::to_string(base_correction.theta));
        printTakeshiTaskMessage("Torso correction: " + std::to_string(torso));

        geometry_msgs::Vector3 pre_force, post_force;
        double weight;
        TakeshiManip::getCurrentForce(pre_force);

        TakeshiManip::hdGoTo(0.0,0.0,2000);
        TakeshiManip::torsoGoTo(torso + 0.08, 6000);
        //ros::Duration(0.5).sleep();
        TakeshiManip::armGoToArticular(articular, 4000);
        //ros::Duration(1.5).sleep();
        TakeshiManip::openGripper(1.0);
        ////////////////////////////////////////////
        //       SECOND STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        printTakeshiTaskMessage("Grasp Object:[Before correction]  try calculate Inverse Kinematic "
                  + std::to_string(cartesian[0]) + "  "
                  + std::to_string(cartesian[1]) + "  "
                  + std::to_string(cartesian[2]));

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) ){
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                printTakeshiTaskError("I can not calculate the Inverse Kinematic.");
                fail=true;
                return false;
        }

        for (int i=0; i < articular.size(); i++)
            printTakeshiTaskMessage("Articular: " + std::to_string(i) + ": " + std::to_string(articular[i]));
        printTakeshiTaskMessage("OmniBase correction: " + std::to_string(base_correction.x) + " " + std::to_string(base_correction.y) + " " + std::to_string(base_correction.theta));
        printTakeshiTaskMessage("Torso correction: " + std::to_string(torso));

        TakeshiManip::torsoGoTo(torso, 6000);
        //ros::Duration(0.8).sleep();

	//This is for pitch angle
	articular[2] = articular[2] - 0.15;
        TakeshiManip::armGoToArticular(articular, 6000);
        //ros::Duration(1.5).sleep();

        TakeshiManip::closeGripper(0.1);
        ros::Duration(1.0).sleep();

        TakeshiManip::torsoGoTo(torso + 0.10, 6000);
        ros::Duration(2.0).sleep();

        TakeshiManip::getCurrentForce(post_force);
        weight=TakeshiManip::computeWeight(pre_force,post_force);
        printTakeshiTaskMessage("Object Weight: "+ std::to_string(weight));

        if(verify)
            if(weight > 90){
               TakeshiHRI::say("I took the object"); 
               TakeshiManip::armGoToNavigation();
               ros::Duration(2.0).sleep();
               TakeshiManip::torsoGoTo(0.0, 4000);
               return true;                
            }
            else{
                TakeshiTasks::alignWithFrontTable();
                printTakeshiTaskError("Can not grasp object: force verify");
                return false;
            }
        else{
            TakeshiManip::armGoToNavigation();
            ros::Duration(2.0).sleep();
            TakeshiManip::torsoGoTo(0.0, 4000);
            return true;
        }

}

bool TakeshiTasks::graspObjectLateral(float x, float y, float z, bool verify){
    bool fail;
    return TakeshiTasks::graspObjectLateral(x,y,z,verify,fail);
}

bool TakeshiTasks::graspObjectLateral(float x, float y, float z, bool verify, bool& fail)
{
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;
        vision_msgs::ObjectCoordinatesForDetection graspObjectCoordinates;
        float torso;
        float x_correction;
        float x_error;
        printTakeshiTaskMessage("\n\nGrasp Object Lateral: Object Position x: "+ std::to_string(x) + " y: " + std::to_string(y) + " z:" + std::to_string(z));

        graspObjectCoordinates=TakeshiVision::objectCoordinates;
        graspObjectCoordinates.x_min=-0.4;
        graspObjectCoordinates.x_max=0.4;
        graspObjectCoordinates.y_min=-1.0;
        graspObjectCoordinates.y_max=1.0;

        // if(!TakeshiVision::isGraspeable(x,y,z,graspObjectCoordinates)){
        //        TakeshiHRI::say("I can not detect the object in front of me.");
        //        printTakeshiTaskError("I can not detect the object in front of me.");
        //        fail=true;
        //        return false;
        // }  //???????????? commented by edd2

       //Correction coordinates for objects in left side
        if(x > 0)
                x_correction = x + 0.10;  // 0.10 is the distance from base_arm to robot_base in axis Y
        else
                x_correction = x + 0.03;  //10 //Correction coordinates for objects in right side
        printTakeshiTaskMessage("Grasp Object: X correction: " + std::to_string(x_correction));
        TakeshiNavigation::moveDistAngle(x_correction, 0.0,  4000);

        TakeshiManip::startHdGoTo(0.0, 0.0);
        if(y > 0)
                TakeshiNavigation::moveDistAngle(0.0, 1.5707, 2000);  // Correction coordinates for objects in left side
        else
                TakeshiNavigation::moveDistAngle(0.0, -1.5707, 2000);  // Correction coordinates for objects in right side

        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = abs(y) - 0.05;
        cartesian[1] = x;
        cartesian[2] = z;

        printTakeshiTaskMessage("Grasp Object Lateral:[Before correction]  try calculate Inverse Kinematic "
                  + std::to_string(cartesian[0]) + "  "
                  + std::to_string(cartesian[1]) + "  "
                  + std::to_string(cartesian[2]));
        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) ) {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                printTakeshiTaskError("I can not calculate the Inverse Kinematic.");
                fail=true;
                return false;
        }

        for (int i=0; i < articular.size(); i++)
            printTakeshiTaskMessage("Articular: " + std::to_string(i) + ": " + std::to_string(articular[i]));
        printTakeshiTaskMessage("OmniBase correction: " + std::to_string(base_correction.x) + " " + std::to_string(base_correction.y) + " " + std::to_string(base_correction.theta));
        printTakeshiTaskMessage("Torso correction: " + std::to_string(torso));

        geometry_msgs::Vector3 pre_force, post_force;
        double weight;
        TakeshiManip::getCurrentForce(pre_force);

        TakeshiManip::openGripper(1.0);
        if(articular[0] < -1.5707)
            TakeshiManip::torsoGoTo(torso + 0.18, 2000);
        else
            TakeshiManip::torsoGoTo(torso + 0.10, 2000);
        TakeshiManip::armGoToArticular(articular, 2000);

        //       SECOND STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = abs(y) + 0.02;
        cartesian[1] = x;
        cartesian[2] = z;

        printTakeshiTaskMessage("Grasp Object:[Before correction]  try calculate Inverse Kinematic "
                  + std::to_string(cartesian[0]) + "  "
                  + std::to_string(cartesian[1]) + "  "
                  + std::to_string(cartesian[2]));

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) ) {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                printTakeshiTaskError("I can not calculate the Inverse Kinematic.");
                fail=true;
                return false;
        }

        for (int i=0; i < articular.size(); i++)
            printTakeshiTaskMessage("Articular: " + std::to_string(i) + ": " + std::to_string(articular[i]));
        printTakeshiTaskMessage("OmniBase correction: " + std::to_string(base_correction.x) + " " + std::to_string(base_correction.y) + " " + std::to_string(base_correction.theta));
        printTakeshiTaskMessage("Torso correction: " + std::to_string(torso));

        TakeshiManip::torsoGoTo(torso + 0.02, 1500);
	   
       //This is for pitch angle
	   articular[2] = articular[2] - 0.20;
        TakeshiManip::armGoToArticular(articular, 2500);
        //ros::Duration(1.0).sleep();
        TakeshiManip::closeGripper(0.08);

        TakeshiManip::torsoGoTo(torso + 0.15, 3000);

        TakeshiManip::getCurrentForce(post_force);
        weight=TakeshiManip::computeWeight(pre_force,post_force);
        printTakeshiTaskMessage("Object Weight: "+ std::to_string(weight));

        if(verify)
            if(weight > 90){
               TakeshiHRI::say("I took the object"); 
               TakeshiManip::armGoToNavigation();
               ros::Duration(2.0).sleep();
               TakeshiManip::torsoGoTo(0.0, 4000);
               return true;                
            }
            else{
                TakeshiTasks::alignWithTable();
                printTakeshiTaskError("Can not grasp object: force verify");
                return false;
            }
        else{
            TakeshiManip::armGoToNavigation();
            ros::Duration(2.0).sleep();
            TakeshiManip::torsoGoTo(0.0, 4000);
        }
/*
        articular[0] =  0.0;
        articular[1] =  0.0;
        articular[2] = -1.57;
        articular[3] =  0.0;

        TakeshiManip::hdGoTo(0.0, 0.0, 6000);
        TakeshiManip::armGoToArticular(articular, 1000);
        TakeshiManip::waitForArmGoToNavigation(3000);
        TakeshiManip::torsoGoTo(0.0, 2000);

        return TakeshiManip::isTheObjectTaken(verify);*/
}

bool TakeshiTasks::graspObjectOnFloor(float x, float y, float z, bool verify)
{
        // Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;

        float torso;
        float y_correction;
        float x_correction;

        geometry_msgs::Vector3 pre_force, post_force;
        double weight;
        TakeshiManip::getCurrentForce(pre_force);

        x_correction = 0.0;
        std::cout << "\033[1;34m     TakeshiTasks.->Grasp Object: Object Location x: "
                  << x
                  <<" y: " << y
                  << " z:" << z <<".\033[0m" << std::endl;
        // if(fabs(x) > 0.56 || fabs(y) > 0.4) {
        //         TakeshiHRI::say("The object is too far of me. I am going to close it.");
        //         return false;
        // }

        if(fabs(x) > 0.56) {
                x_correction = x - 0.56;
                x = x - x_correction;
                TakeshiHRI::say("I am getting close to it.");
        }

        std::cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: Correct X displacement.\033[0m" << std::endl;
        y_correction = y - 0.10; // 0.10 is the distance from base_arm to robot_base in axis Y
        std::cout << "\033[1;34m   Y[diff]:  " << y_correction << "\033[0m" << std::endl;

        //TakeshiNavigation::moveLateral(y_correction, 4000);
        //TakeshiNavigation::moveDist(x_correction + 0.05, 3000);


        ////////////////////////////////////////////
        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x - 0.15;
        cartesian[1] = 0.10;
        cartesian[2] = z + 0.06;

        std::cout << "\033[1;34m TakeshiTasks::GraspObj:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                std::cout << "   " << articular[i] << std::endl;
        std::cout << "OmniBase correction: " << base_correction << std::endl;
        std::cout << "Torso correction: " << torso << std::endl;

        TakeshiManip::openGripper(1.0);
        TakeshiManip::torsoGoTo(torso, 3000);
        ros::Duration(0.5).sleep();
        TakeshiManip::armGoToArticular(articular, 4000);
        ros::Duration(0.5).sleep();



        ////////////////////////////////////////////
        //       SECOND STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        //cartesian[2] = z + 0.04;

        std::cout << "\033[1;34m TakeshiTasks::GraspObj:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                std::cout << "   " << articular[i] << std::endl;
        std::cout << "\033[1;34m OmniBase correction: " << base_correction << "\033[0m" << std::endl;
        std::cout << "\033[1;43m Torso correction: " << torso << "\033[0m" << std::endl;

        articular[2]=articular[2]-0.15;
        TakeshiManip::armGoToArticular(articular, 6000);
        ros::Duration(0.5).sleep();

        TakeshiManip::torsoGoTo(torso, 6000);
        ros::Duration(0.5).sleep();

        TakeshiNavigation::moveLateral(y_correction, 5000);
        TakeshiNavigation::moveDist(x_correction + 0.05, 5000);
        ros::Duration(3.0).sleep();

        TakeshiManip::closeGripper(0.08);
        ros::Duration(2.0).sleep();



        TakeshiManip::torsoGoTo(torso + 0.10, 6000);
        ros::Duration(2.0).sleep();
        TakeshiNavigation::moveDist(-0.2,4000);

        TakeshiManip::armGoToNavigation();
        ros::Duration(2.0).sleep();
        TakeshiManip::torsoGoTo(0.0, 4000);

        ros::Duration(2.0).sleep();
        TakeshiManip::getCurrentForce(post_force);
        weight=TakeshiManip::computeWeight(pre_force,post_force);

        cout << "weight" << weight << endl;

        std::stringstream takeshi_say;
        takeshi_say.str(std::string());
        takeshi_say << "This object weights  " << weight << " grams";

        //TakeshiHRI::say(takeshi_say.str());

        if(!TakeshiManip::isTheObjectTaken(verify)) {
                //        TakeshiHRI::say("I could not take the object ");
                return false;
        }
        else{
                //      TakeshiHRI::say("i take the object");
                return true;
        }
}

//This is a test for HSR-CHALLENGE
bool TakeshiTasks::graspRopeOnFloor(float x, float y, float z, bool verify)
{
        // Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
	std::vector<string> idObjects;
        geometry_msgs::Pose2D base_correction;
	std::vector<vision_msgs::VisionObject> recognizedYoloObjects;
	std::vector<vision_msgs::VisionObject> recognizedObjects;
	vision_msgs::ObjectCoordinatesForDetection objectCoordinates;

	int attempts;
        float torso;
        float y_correction;
        float x_correction;

        geometry_msgs::Vector3 pre_force, post_force;
        double weight;
        TakeshiManip::getCurrentForce(pre_force);

	attempts = 0;
	idObjects.resize(1);
	idObjects[0] = "rope";

	while(attempts < 3)
	{
	  if(!TakeshiVision::detectSpecificYoloObject(idObjects,recognizedYoloObjects,4000,objectCoordinates))
	  {
	    TakeshiHRI::say("I can not detect the rope");
	    printTakeshiTaskError("Can not detect any yolo object");
	    attempts++;
	  }
	  else
	  {
	    TakeshiHRI::say("I will grasp the " + recognizedYoloObjects[0].id);
	    printTakeshiTaskMessage("Object ID" + recognizedYoloObjects[0].id);
	    printTakeshiTaskMessage("Segmenting objects by depth information...");
	    if(TakeshiVision::detectObjects(recognizedObjects, false))
	    {
	      x = recognizedObjects[0].pose.position.x;
	      y = recognizedObjects[0].pose.position.y;
	      z = recognizedObjects[0].pose.position.z;
	    }
	    else
	    {
	      x = recognizedYoloObjects[0].pose.position.x;
	      y = recognizedYoloObjects[0].pose.position.y;
	      z = recognizedYoloObjects[0].pose.position.z;
	    }
	    break;
	  }
	  
	}
 
        x_correction = 0.0;
        std::cout << "\033[1;34m     TakeshiTasks.->Grasp Object: Object Location x: "
                  << x
                  <<" y: " << y
                  << " z:" << z <<".\033[0m" << std::endl;
        // if(fabs(x) > 0.56 || fabs(y) > 0.4) {
        //         TakeshiHRI::say("The object is too far of me. I am going to close it.");
        //         return false;
        // }

        if(fabs(x) > 0.56) {
                x_correction = x - 0.56;
                x = x - x_correction;
                TakeshiHRI::say("The object is too far from me. I am getting close to it.");
        }

        std::cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: Correct X displacement.\033[0m" << std::endl;
        y_correction = y - 0.10; // 0.10 is the distance from base_arm to robot_base in axis Y
        std::cout << "\033[1;34m   Y[diff]:  " << y_correction << "\033[0m" << std::endl;

        //TakeshiNavigation::moveLateral(y_correction, 4000);
        //TakeshiNavigation::moveDist(x_correction + 0.05, 3000);


        ////////////////////////////////////////////
        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x - 0.15;
        cartesian[1] = 0.10;
        cartesian[2] = z + 0.06;

        std::cout << "\033[1;34m TakeshiTasks::GraspObj:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                std::cout << "   " << articular[i] << std::endl;
        std::cout << "OmniBase correction: " << base_correction << std::endl;
        std::cout << "Torso correction: " << torso << std::endl;

        TakeshiManip::openGripper(1.0);
        TakeshiManip::torsoGoTo(torso, 6000);
        ros::Duration(0.5).sleep();
        TakeshiManip::armGoToArticular(articular, 4000);
        ros::Duration(1.5).sleep();



        ////////////////////////////////////////////
        //       SECOND STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        //cartesian[2] = z + 0.04;

        std::cout << "\033[1;34m TakeshiTasks::GraspObj:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                std::cout << "   " << articular[i] << std::endl;
        std::cout << "\033[1;34m OmniBase correction: " << base_correction << "\033[0m" << std::endl;
        std::cout << "\033[1;43m Torso correction: " << torso << "\033[0m" << std::endl;

        articular[2]=articular[2]-0.15;
        TakeshiManip::armGoToArticular(articular, 6000);
        ros::Duration(1.5).sleep();

        TakeshiManip::torsoGoTo(torso, 6000);
        ros::Duration(0.5).sleep();

        TakeshiNavigation::moveLateral(y_correction, 5000);
        TakeshiNavigation::moveDist(x_correction + 0.05, 5000);
        ros::Duration(3.0).sleep();

        TakeshiManip::closeGripper(0.08);
        ros::Duration(2.0).sleep();



        TakeshiManip::torsoGoTo(torso + 0.10, 6000);
        ros::Duration(2.0).sleep();
        TakeshiNavigation::moveDist(-0.2,4000);

        TakeshiManip::armGoToNavigation();
        ros::Duration(2.0).sleep();
        TakeshiManip::torsoGoTo(0.0, 4000);

        ros::Duration(2.0).sleep();
        TakeshiManip::getCurrentForce(post_force);
        weight=TakeshiManip::computeWeight(pre_force,post_force);

        cout << "weight" << weight << endl;

        std::stringstream takeshi_say;
        takeshi_say.str(std::string());
        takeshi_say << "This object weights  " << weight << " grams";

        //TakeshiHRI::say(takeshi_say.str());

        if(!TakeshiManip::isTheObjectTaken(verify)) {
                //        TakeshiHRI::say("I could not take the object ");
                return false;
        }
        else{
                //      TakeshiHRI::say("i take the object");
                return true;
        }
}



bool TakeshiTasks::graspObjectOnFloorFromAbove(float x, float y, float z, float height, bool verify)
{
        // Variables for inverse kinematic calculate
        // Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;

        float distToGrasp=0.38, x_correction=0;;

        float torso;
        float y_correction;

        std::cout << "\033[1;34m     TakeshiTasks.->Grasp Object: Object Location x: " << x << " y: " << y << " z:" << z <<".\033[0m" << std::endl;
        if(fabs(x) > 1.8 || fabs(y) > 0.5) {
                TakeshiHRI::say("I can not detect the object in front of me.");
                return false;
        }

        if(y > 0)
                y_correction = y -0.05;
        else
                y_correction = y -0.13;

        TakeshiNavigation::moveLateral(y_correction, 4000);

        if(x_correction-0.02 < 0) {
                x_correction=x-distToGrasp-0.08;
                cout << "menor" << endl;
        }
        else{
                x_correction=x-distToGrasp;
                cout << "mayor" << endl;
        }
        TakeshiNavigation::moveDist(x_correction, 4000);

        /*
           ////////////////////////////////////////////
           //       FIST STEP OF MOVEMENT ARM        //
           cartesian.resize(3);
           cartesian[0] = x - 0.1;
           cartesian[1] = 0.10;
           cartesian[2] = z;

           std::cout << "\033[1;34m TakeshiTasks::GraspObj:[Before correction]  try calculate Inverse Kinematic "
              << cartesian[0] << "  "
              << cartesian[1] << "  "
              << cartesian[2] << "\033[0m" << std::endl;

           // Calculate inverse kinematic for geometric way
           /*
           if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
           {
            TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
            //return false;
           }

           for (int i=0; i < articular.size(); i++)
            std::cout << "   " << articular[i] << std::endl;
           std::cout << "OmniBase correction: " << base_correction << std::endl;
           std::cout << "Torso correction: " << torso << std::endl;
         */
        TakeshiManip::openGripper(1.0);
        //TakeshiManip::torsoGoTo(torso, 6000);
        ros::Duration(0.5).sleep();
        //TakeshiManip::armGoToArticular(articular, 4000);
        ros::Duration(1.5).sleep();


        /*
           ////////////////////////////////////////////
           //       SECOND STEP OF MOVEMENT ARM        //
           cartesian.resize(3);
           cartesian[0] = x;
           cartesian[1] = 0.10;
           cartesian[2] = z;

           std::cout << "\033[1;34m TakeshiTasks::GraspObj:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;
           /*
           // Calculate inverse kinematic for geometric way
           if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
           {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                //return false;
           }

           for (int i=0; i < articular.size(); i++)
                std::cout << "   " << articular[i] << std::endl;
           std::cout << "\033[1;34m OmniBase correction: " << base_correction << "\033[0m" << std::endl;
           std::cout << "\033[1;43m Torso correction: " << torso << "\033[0m" << std::endl;

           articular[2]=articular[2]-0.6;
         */
        //TakeshiManip::armGoToArticular(articular, 6000);

        TakeshiManip::torsoGoTo(height+0.02, 6000);
        ros::Duration(0.5).sleep();

        TakeshiManip::waitForArmGraspFloor(6000);
        ros::Duration(1.5).sleep();

        TakeshiManip::closeGripper(0.08);
        ros::Duration(3.0).sleep();

        TakeshiManip::torsoGoTo(height+0.15, 6000);
        ros::Duration(2.0).sleep();


        TakeshiManip::armGoToNavigation();
        ros::Duration(2.0).sleep();
        TakeshiManip::torsoGoTo(0.0, 4000);

        if(!TakeshiManip::isTheObjectTaken(verify)) {
                //TakeshiHRI::say("I could not take the object ");
                return false;
        }
        else{
                //TakeshiHRI::say("i take the object");
                return true;
        }

}

bool TakeshiTasks::graspObjectOnFloorFromAbove(vision_msgs::VisionObject detectedObject, float height, bool verify)
{
        // Variables for inverse kinematic calculate
        float x = detectedObject.pose.position.x;
        float y = detectedObject.pose.position.y;
        float z = detectedObject.pose.position.z;
        float articular3=0.0;
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;

        float distToGrasp=0.38, x_correction=0;;
        float boundingBoxRelation=0;
        float torso;
        float y_correction;

        std::cout << "\033[1;34m     TakeshiTasks.->Grasp Object: Object Location x: " << x << " y: " << y << " z:" << z <<".\033[0m" << std::endl;
        if(fabs(x) > 1.8 || fabs(y) > 0.4) {
                TakeshiHRI::say("I can not detect the object in front of me.");
                return false;
        }

        if(y > 0)
                y_correction = y -0.05;
        else
                y_correction = y -0.13;

        TakeshiNavigation::moveLateral(y_correction, 4000);

        if(x_correction-0.02 < 0) {
                x_correction=x-distToGrasp-0.08;
                cout << "menor" << endl;
        }
        else{
                x_correction=x-distToGrasp;
                cout << "mayor" << endl;
        }
        TakeshiNavigation::moveDist(x_correction, 4000);


        ////////////////////////////////////////////
        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x - 0.1;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        std::cout << "\033[1;34m TakeshiTasks::GraspObj:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;

        // Calculate inverse kinematic for geometric way
        /*
           if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
           {
           TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
           return false;
           }

           for (int i=0; i < articular.size() ; i++)
           std::cout << "   " << articular[i] << std::endl;
           std::cout << "OmniBase correction: " << base_correction << std::endl;
           std::cout << "Torso correction: " << torso << std::endl;
         */
        TakeshiManip::openGripper(1.0);
        //TakeshiManip::torsoGoTo(torso, 6000);
        ros::Duration(0.5).sleep();
        //TakeshiManip::armGoToArticular(articular, 4000);
        ros::Duration(1.5).sleep();



        ////////////////////////////////////////////
        //       SECOND STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        std::cout << "\033[1;34m TakeshiTasks::GraspObj:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;
/*
   // Calculate inverse kinematic for geometric way
   if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
    {
      TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
      return false;
    }
 */
        for (int i=0; i < articular.size(); i++)
                std::cout << "   " << articular[i] << std::endl;
        std::cout << "\033[1;34m OmniBase correction: " << base_correction << "\033[0m" << std::endl;
        std::cout << "\033[1;43m Torso correction: " << torso << "\033[0m" << std::endl;

        boundingBoxRelation=float(detectedObject.width)/float(detectedObject.height);
        TakeshiTasks::printTakeshiTaskMessage("WIDTH: "+ to_string(detectedObject.width) + "Heigth: " + to_string(detectedObject.height) + "data: " + to_string(boundingBoxRelation));
        if(boundingBoxRelation > 1)
                articular3=-1.57;
        else
                articular3=0.0;

        TakeshiManip::torsoGoTo(height+0.02, 6000);
        ros::Duration(0.5).sleep();

        TakeshiManip::waitForArmGraspFloor(6000, articular3);
        ros::Duration(1.5).sleep();        

        TakeshiManip::closeGripper(0.04);
        ros::Duration(3.0).sleep();

        TakeshiManip::torsoGoTo(height+0.15, 6000);
        ros::Duration(2.0).sleep();


        TakeshiManip::armGoToNavigation();
        ros::Duration(2.0).sleep();
        TakeshiManip::torsoGoTo(0.0, 4000);

        if(!TakeshiManip::isTheObjectTaken(verify)) {
                TakeshiHRI::say("I could not take the object ");
                return false;
        }
        else{
                TakeshiHRI::say("i take the object");
                return true;
        }
}

bool TakeshiTasks::giveObject(float x, float y, float z)
{
        // Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;

        float torso;
        float y_correction;

        std::cout << "\033[1;34m     TakeshiTasks.->Give Object: Correct X displacement.\033[0m" << std::endl;
        y_correction = y - 0.10; // 0.10 is the distance from base_arm to robot_base in axis Y
        std::cout << "\033[1;34m     TakeshiTasks.->Give Object:  Y correction:  " << y_correction << "\033[0m" << std::endl;
        TakeshiNavigation::moveLateral(y_correction, 4000);

        ////////////////////////////////////////////
        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        //cartesian[0] = x - 0.15;
        cartesian[0] = x - 0.15;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        std::cout << "\033[1;34m TakeshiTasks::Give Object:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::waitAfterSay("I am sorry, approach to me.",4000);
                ros::Duration(2.0).sleep();
                TakeshiManip::openGripper(1.0);
                TakeshiManip::navigationPose(4000);
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                std::cout << "   " << articular[i] << std::endl;
        std::cout << "OmniBase correction: " << base_correction << std::endl;
        std::cout << "Torso correction: " << torso << std::endl;

        TakeshiManip::torsoGoTo(torso + 0.05, 3000);
        TakeshiManip::armGoToArticular(articular, 4000);
/*
        ////////////////////////////////////////////
        //       SECOND STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x + 0.05;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        std::cout << "\033[1;34m TakeshiTasks::Give Object:[Before correction]  try calculate Inverse Kinematic "
                  << cartesian[0] << "  "
                  << cartesian[1] << "  "
                  << cartesian[2] << "\033[0m" << std::endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry");
                ros::Duration(2.0).sleep();
                
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                std::cout << "   " << articular[i] << std::endl;
        std::cout << "\033[1;34m OmniBase correction: " << base_correction << "\033[0m" << std::endl;
        std::cout << "\033[1;43m Torso correction: " << torso << "\033[0m" << std::endl;

        TakeshiManip::torsoGoTo(torso, 3000);
        TakeshiManip::armGoToArticular(articular, 4000);
        */
        TakeshiHRI::say("Take the object");
        ros::Duration(2.0).sleep();
        TakeshiManip::openGripper(1.0);
        ros::Duration(4.0).sleep();

        TakeshiManip::armGoToNavigation();
        TakeshiManip::openGripper(0.1);
        TakeshiManip::torsoGoTo(0.0, 4000);
        return true;
}

bool TakeshiTasks::takeHandle(float x, float y, float z, float & height, bool fridge)
{
        // Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;
        float distArm = 0.68-0.17;
        float distToGrasp;
        if(fridge)
                distToGrasp = 0.75-0.19;
        else
                distToGrasp = 0.8;
        float x_correction;
        float torso;
        float y_correction;

        std::cout << "\033[1;34m     TakeshiTasks.->Take Handle: Correct X displacement.\033[0m" << std::endl;
        if (fridge)
                y_correction = y - 0.05;  // 0.10 is the distance from base_arm to robot_base in axis Y
        else
                y_correction = y - 0.10;  // 0.10 is the distance from base_arm to robot_base in axis Y
        std::cout << "\033[1;34m   Y[diff]:  " << y_correction << "\033[0m" << std::endl;
        TakeshiNavigation::moveLateral(y_correction, 4000);

        x_correction=x-distToGrasp;
        TakeshiNavigation::moveDist(x_correction, 4000);

        ////////////////////////////////////////////
        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x - 0.18;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        cout << "\033[1;34m     TakeshiTasks::Take Hanlde:[Before correction]  try calculate Inverse Kinematic "
             << cartesian[0] << "  "
             << cartesian[1] << "  "
             << cartesian[2] << "\033[0m" << endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        cout << "\033[1;34m     TakeshiTasks::Take Hanlde: Articular: ";
        for (int i=0; i < articular.size(); i++)
                cout << " " << articular[i];
        cout << "\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks::Take Hanlde:OmniBase correction: " << base_correction << "\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks::Take Hanlde:Torso correction: " << torso  << "\033[0m" << endl;

        if(fridge) {
                articular[0] =  -0.5;
                articular[1] =  0.0;
                articular[2] =  -1.1;
                articular[3] =  0.0;
                height=z-0.4-0.22;
        }
        else{
                articular[0] =  -2.0;
                articular[1] =  0.0;
                articular[2] =  0.5;
                articular[3] =  -1.5;
                height=z-0.20;
        }

        TakeshiManip::torsoGoTo(height, 6000);

        TakeshiManip::armGoToArticular(articular, 4000);
        TakeshiManip::openGripper(1.0);
        ros::Duration(1.0).sleep();

        if(!fridge)
                x_correction=x_correction+0.21;

        if(x_correction > 0)
                x_correction=x-distArm+(x_correction* -1)+0.08;
        else
                x_correction=x-distArm+(x_correction* -1)+0.08;
        TakeshiNavigation::moveDist(x_correction, 4000);
        ros::Duration(2.0).sleep();
        TakeshiManip::closeGripper(0.2);
        ros::Duration(2.0).sleep();

        return true;
}

bool TakeshiTasks::moveHandle(float x, float y, float z, float & height)
{
        // Variables for inverse kinematic calculate
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;
        float distArm = 0.68-0.17;
        float distToGrasp;
        distToGrasp = 0.75-0.19;
        float x_correction;
        float torso;
        float y_correction;

        std::cout << "\033[1;34m     TakeshiTasks.->Move Handle: Correct X displacement.\033[0m" << std::endl;
        y_correction = y - 0.06; // 0.10 is the distance from base_arm to robot_base in axis Y
        cout << "y: " << y << endl;
        TakeshiNavigation::moveLateral(y_correction, 4000);

        x_correction=x-distToGrasp;
        TakeshiNavigation::moveDist(x_correction, 4000);

        ////////////////////////////////////////////
        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = x - 0.18;
        cartesian[1] = 0.10;
        cartesian[2] = z;

        cout << "\033[1;34m     TakeshiTasks::Move Hanlde:[Before correction]  try calculate Inverse Kinematic "
             << cartesian[0] << "  "
             << cartesian[1] << "  "
             << cartesian[2] << "\033[0m" << endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        cout << "\033[1;34m     TakeshiTasks::Move Hanlde: Articular: ";
        for (int i=0; i < articular.size(); i++)
                cout << " " << articular[i];
        cout << "\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks::Move Handle:OmniBase correction: " << base_correction << "\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks::Move Hanlde:Torso correction: " << torso  << "\033[0m" << endl;


        height=z-0.4-0.15;
        TakeshiManip::closeGripper(0.1);
        TakeshiManip::torsoGoTo(height, 6000);
        TakeshiManip::waitForArmGoToGraspFridge(4000);

        if(x_correction > 0)
                x_correction=x-distArm+(x_correction* -1)+0.1;
        else
                x_correction=x-distArm+(x_correction* -1);
        TakeshiNavigation::moveDist(x_correction, 4000);

        return true;
}

bool TakeshiTasks::graspObjectOnTheDrawer(std::string idObject, double planeHeight, bool verify)
{
        geometry_msgs::Pose pose;
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        float x,y,z;
        float y_correction=0, torso_correction=0, x_correction=0;
        bool findObject;

        TakeshiManip::navigationPose(4000);
        TakeshiManip::openGripper(0.1);

        std::cout << "Look for specific object...  " << '\n';
        for(int i=0; i<7; i++) {
                findObject=TakeshiTasks::findObjectOnPlane(idObject, pose, TakeshiTasks::CENTERDOWN, planeHeight);
                if(findObject)
                        break;
                else
                        cout << "No object!!!!" << endl;

        }

        if(!findObject) {
                TakeshiHRI::waitAfterSay("I can not find the object", 3000);
                return false;
        }

        x = pose.position.x;
        y = pose.position.y;
        z = pose.position.z;

        return TakeshiTasks::graspObjectOnFloorFromAbove(x,y,z,planeHeight,verify);

}

bool TakeshiTasks::graspObjectOnPlane(std::string idObject, double planeHeight, bool verify)
{
        geometry_msgs::Pose pose;
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        float x,y,z;

        // If NO id object, grap the nearest object
        if(idObject.compare("") != 0)
        {
                std::cout << "Look for specific object...  " << '\n';
                while (!TakeshiTasks::findObjectOnPlane(idObject, pose, TakeshiTasks::CENTERDOWN, planeHeight) && ros::ok())
                        cout << "No object!!!!" << endl;

                // Variables for inverse kinematic calculate
                x = pose.position.x;
                y = pose.position.y;
                z = pose.position.z;
        }
        else
        {
                std::cout << "Look for NO-SPECIFIC object... " << '\n';
                // // Find object again and correct the new angle
                while (!TakeshiVision::detectObjectsOnPlane(recognizedObjects, planeHeight) && ros::ok())
                        cout << "Nothing detected!!!!" << endl;

                //Supouse first objReco is the nearest object
                std::cout << "Obj_position:" << recognizedObjects[0].pose.position
                          << std::endl;
                x = recognizedObjects[0].pose.position.x;
                y = recognizedObjects[0].pose.position.y;
                z = recognizedObjects[0].pose.position.z;
        }

        return TakeshiTasks::graspObject(x, y, z, verify);
}

bool TakeshiTasks::graspObjectLateralRight(float x, float y, float z, bool verify)
{
        std::vector<float> cartesian;
        std::vector<float> articular;
        geometry_msgs::Pose2D base_correction;

        float torso;
        float x_correction;
        float x_error;

        if(fabs(x) > 0.4 || fabs(y) > 1.0) {
                TakeshiHRI::say("I can not detect the object in front of me.");
                return false;
        }

        cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: Correct X displacement.\033[0m" << endl;
        //Correction coordinates for objects in left side
        if(x > 0)
                x_correction = x + 0.10;  // 0.10 is the distance from base_arm to robot_base in axis Y
        else
                x_correction = x + 0.03;  //10 //Correction coordinates for objects in right side
        std::cout << "   X[diff]:  " << x_correction << std::endl;
        cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: X[diff]: " << x_correction << "\033[0m" << endl;

        TakeshiNavigation::moveDistAngle(x_correction, 0.0,  4000);

        // // Find object again and correct the new angle
        // if (JustinaVision::detectObjects(recognizedObjects, false) )
        // {
        //   //Supouse first objReco is the nearest object
        //   std::cout << "Obj_position:" << recognizedObjects[0].pose.position
        //        << std::endl;
        //   x_error = recognizedObjects[0].pose.position.x + 0.10;
        //   if( x_error > 0.02)
        //   {
        //     std::cout << "   X[diff]:  " << x_error << std::endl;
        //     JustinaNavigation::moveDistAngle(x_error, 0.0, 4000);
        //   }
        // }

        TakeshiManip::startHdGoTo(0.0, 0.0);
        if(y > 0)
                TakeshiNavigation::moveDistAngle(0.0, 1.5707, 2000);  // Correction coordinates for objects in left side
        else
                TakeshiNavigation::moveDistAngle(0.0, -1.5707, 2000);  // Correction coordinates for objects in right side

        //       FIST STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = abs(y) - 0.05;
        cartesian[1] = x;
        cartesian[2] = z;

        cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: [Before correction]  try calculate Inverse Kinematic "
             << cartesian[0] << "  "
             << cartesian[1] << "  "
             << cartesian[2] << "\033[0m" << endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: " << "   " << articular[i] << "\033[0m" << endl;

        cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: OmniBase correction: " << base_correction <<"\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: Torso correction: " << torso <<"\033[0m" << endl;

        TakeshiManip::openGripper(1.0);
        TakeshiManip::torsoGoTo(torso + 0.05, 2000);
        TakeshiManip::armGoToArticular(articular, 2000);

        //       SECOND STEP OF MOVEMENT ARM        //
        cartesian.resize(3);
        cartesian[0] = abs(y) + 0.02;
        cartesian[1] = x;
        cartesian[2] = z;

        cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: [Before correction]  try calculate Inverse Kinematic "
             << cartesian[0] << "  "
             << cartesian[1] << "  "
             << cartesian[2] << "\033[0m" << endl;

        // Calculate inverse kinematic for geometric way
        if(!TakeshiManip::inverseKinematicsGeometric(cartesian, articular, torso, base_correction) )
        {
                TakeshiHRI::say("I am sorry, I can not calculate the Inverse Kinematic.");
                return false;
        }

        for (int i=0; i < articular.size(); i++)
                cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: " << "   " << articular[i] << "\033[0m" << endl;

        cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: OmniBase correction: " << base_correction <<"\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks.->Grasp Object lateral: Torso correction: " << torso <<"\033[0m" << endl;

        TakeshiManip::torsoGoTo(torso - 0.01, 1500);
	//This is for pitch angle
	articular[2] = articular[2] - 0.15;
        TakeshiManip::armGoToArticular(articular, 2500);
        ros::Duration(1.0).sleep();
        TakeshiManip::closeGripper(0.02);

        TakeshiManip::torsoGoTo(torso + 0.10, 1500);

        articular[0] =  0.0;
        articular[1] =  0.0;
        articular[2] = -1.57;
        articular[3] =  0.0;

        TakeshiManip::hdGoTo(0.0, 0.0, 6000);
        TakeshiManip::armGoToArticular(articular, 1000);
        TakeshiManip::waitForArmGoToNavigation(3000);
        TakeshiManip::torsoGoTo(0.0, 2000);

        return TakeshiManip::isTheObjectTaken(verify);
}



//****  Takeshi verified   ******//
bool TakeshiTasks::graspObjectLateral(std::string idObject, bool verify)
{
        geometry_msgs::Pose pose;
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        std::stringstream takeshi_say;

        float x,y,z;

        // If NO id object, grap the nearest object
        if(idObject.compare("") != 0)
        {
                cout << "\033[1;34m     TakeshiTasks.->Look for specific object: " << idObject << "\033[0m" << endl;
                if(!TakeshiTasks::findObject(idObject, pose,TakeshiTasks::LATERAL)) {
                        //while (!TakeshiTasks::findObject(idObject, pose, TakeshiTasks::LATERAL) && ros::ok())
                        cout << "No object!!!!" << endl;
                        return false;
                }
                cout << "\033[1;34m     TakeshiTasks.->Object " << idObject << " position: " << pose.position << "\033[0m" << endl;
                // Variables for inverse kinematic calculate
                x = pose.position.x;
                y = pose.position.y;
                z = pose.position.z;
        }
        else
        {
                cout << "\033[1;34m     TakeshiTasks.->Look for NO SPECIFIC OBJECT\033[0m" << endl;

                // // Find object again and correct the new angle
                while (!TakeshiVision::detectObjects(recognizedObjects, false) && ros::ok())
                        cout << "Nothing detected!!!!" << endl;

                //Supouse first objReco is the nearest object
                cout << "\033[1;34m     TakeshiTasks.->Object position:" << recognizedObjects[0].pose.position << "\033[0m" << endl;
                x = recognizedObjects[0].pose.position.x;
                y = recognizedObjects[0].pose.position.y;
                z = recognizedObjects[0].pose.position.z;
        }

        if(!TakeshiTasks::graspObjectLateral(x, y, z, verify)) {
                takeshi_say << "I could not take the object " << idObject;
                TakeshiHRI::say( takeshi_say.str());
                return false;
        }
        else{
                takeshi_say << "I take the object " << idObject;
                TakeshiHRI::say( takeshi_say.str());
                return true;
        }
}


bool TakeshiTasks::findObject(std::string idObject, geometry_msgs::Pose & pose){

        return TakeshiTasks::findObject(idObject,  pose, headPose::LATERAL);
}

bool TakeshiTasks::findObject(std::string idObject, geometry_msgs::Pose & pose, headPose headpose)
{

        std::vector<vision_msgs::VisionObject> recognizedObjects;
        std::stringstream ss;
        std::string toSpeech = idObject;

        //boost::replace_all(idObject, "_", "-");
        //boost::replace_all(toSpeech, "_", " ");

        cout << "\033[1;34m     TakeshiTasks.->Find a object with pose: " << headpose <<"\033[0m" << endl;

        if(headpose == LATERAL)
                TakeshiManip::hdGoTo(1.5707, -0.8, 5000);
        else if(headpose == CENTER)
                TakeshiManip::hdGoTo(0.0, -0.3, 5000);
        else if(headpose == CENTERDOWN)
                TakeshiManip::hdGoTo(0.0, -0.8, 5000);
        else if(headpose == LATERALUP)
                TakeshiManip::hdGoTo(1.5707, -0.3, 5000);
        else
                TakeshiManip::hdGoTo(0.0, -0.8, 5000);

        cout << "\033[1;34m     TakeshiTasks.->Find a object " << idObject <<"\033[0m" << endl;

        bool found = TakeshiVision::detectObjects(recognizedObjects);
        int indexFound = 0;
        if (found) {
                found = false;
                for (int i = 0; i < recognizedObjects.size(); i++) {
                        vision_msgs::VisionObject vObject = recognizedObjects[i];
                        if (vObject.id.compare(idObject) == 0) {
                                found = true;
                                indexFound = i;
                                break;
                        }
                }
        }

        ss.str("");
        if (!found || recognizedObjects.size() == 0) {
                ss << "I can not find the " << toSpeech;
                //JustinaHRI::waitAfterSay(ss.str(), 2000);
                TakeshiHRI::say(ss.str());
                return false;
        }

        ss << "I found the " << toSpeech;
        //JustinaHRI::waitAfterSay(ss.str(), 2000);
        TakeshiHRI::say(ss.str());

        pose = recognizedObjects[indexFound].pose;
        cout << "\033[1;34m     TakeshiTasks.->Find a object: Position: " << pose.position.x << "," << pose.position.y << "," << pose.position.z << "\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks.->Find a object: Orientation: " << pose.orientation.x << "," << pose.orientation.y << "," << pose.orientation.z << ","<< pose.orientation.w << "\033[0m" << endl;

        return true;
}

bool TakeshiTasks::findObjectAndLateralMove(std::string idObject, geometry_msgs::Pose & pose,headPose headpose)
{

        float moves[3]={0.0,-0.3,0.6};
        float timeout=4000;

        cout << "\033[1;34m     TakeshiTasks.->Running detectObjectAndTilt " <<"\033[0m" << endl;

        for (unsigned int i=0; i<3; i++)
        {

                TakeshiNavigation::moveDist(moves[i], timeout);
                cout << "\033[1;34m     TakeshiTasks.->Attemp  "<<i<<"is running...\033[0m" << endl;

                for (unsigned int i=0; i<3; i++)
                        if (TakeshiTasks::findObject(idObject, pose, headpose))
                                return true;

        }
        TakeshiNavigation::moveDist(-0.3, timeout);

        return false;
}

bool TakeshiTasks::findObjectOnPlane(std::string idObject, geometry_msgs::Pose & pose, headPose headpose, double planeHeight)
{

        std::vector<vision_msgs::VisionObject> recognizedObjects;
        std::stringstream ss;
        std::string toSpeech = idObject;

        //boost::replace_all(idObject, "_", "-");
        //boost::replace_all(toSpeech, "_", " ");

        cout << "\033[1;34m     TakeshiTasks.->Find a object on plane with pose: " << headpose <<"\033[0m" << endl;

        if(headpose == LATERAL)
                TakeshiManip::hdGoTo(1.5707, -0.8, 5000);
        else if(headpose == CENTER)
                TakeshiManip::hdGoTo(0.0, -0.3, 5000);
        else if(headpose == CENTERDOWN)
                TakeshiManip::hdGoTo(0.0, -0.8, 5000);
        else
                TakeshiManip::hdGoTo(0.0, -0.8, 5000);

        cout << "\033[1;34m     TakeshiTasks.->Find a object " << idObject <<"\033[0m" << endl;

        bool found = TakeshiVision::detectObjectsOnPlane(recognizedObjects, planeHeight);
        int indexFound = 0;
        if (found) {
                found = false;
                for (int i = 0; i < recognizedObjects.size(); i++) {
                        vision_msgs::VisionObject vObject = recognizedObjects[i];
                        if (vObject.id.compare(idObject) == 0) {
                                found = true;
                                indexFound = i;
                                break;
                        }
                }
        }

        ss.str("");
        if (!found || recognizedObjects.size() == 0) {
                ss << "I can not find the " << toSpeech;
                //JustinaHRI::waitAfterSay(ss.str(), 2000);
                TakeshiHRI::say(ss.str());
                return false;
        }

        ss << "I found the " << toSpeech;
        //JustinaHRI::waitAfterSay(ss.str(), 2000);
        TakeshiHRI::say(ss.str());

        pose = recognizedObjects[indexFound].pose;
        cout << "\033[1;34m     TakeshiTasks.->Find a object: Position: " << pose.position.x << "," << pose.position.y << "," << pose.position.z << "\033[0m" << endl;
        cout << "\033[1;34m     TakeshiTasks.->Find a object: Orientation: " << pose.orientation.x << "," << pose.orientation.y << "," << pose.orientation.z << ","<< pose.orientation.w << "\033[0m" << endl;
        TakeshiManip::hdGoTo(0.0, 0.0, 5000);
        return true;
}

bool TakeshiTasks::placeObjectInShelfByCategory(string category)
{
  std::vector<vision_msgs::VisionObject> recoObjList;
  std::stringstream takeshi_say;
  ros::Rate loop(10);

  float objX, objY, objZ;
  bool  category_found;
  bool  success;
  bool  isLowerShelf;
  int   nextState;
  int   foundObject_attempts;

  category_found = false;
  success        = false;
  isLowerShelf   = false;
  nextState = 0;
  foundObject_attempts = 0;
  objX = 0.0;
  objY = 0.0;
  objZ = 0.0;
  
  // ===========================================================
  // This task if for search gradually on shelf
  // First turn right the robot an search for specific category

  // TakeshiNavigation::startMoveDistAngle(0.0, -1.5707);
  // TakeshiManip::torsoGoTo(0.70, 2000);
  // TakeshiManip::armGoToArticular(-0.3, -1.5707, -1.5707, 2000);
  // TakeshiManip::findObjectsPose(false);
  TakeshiTasks::alignWithTable(0.7);
  TakeshiManip::hdGoTo(1.5707, -0.6, 3000);
  ros::Duration(2.0).sleep();

  while(ros::ok() && !success) {
    switch (nextState) {  
    case 0:
      // =========================================
      //   STATE:   SEARCHING CATEGORIES OBJECTS
      category_found = false;
      
      // Robot search for category of objects locate
      // TakeshiVision::detectYoloObjectsCategories(std::vector<std::string> objectsName,bool allObjects)

      // if(!TakeshiVision::detectAllYoloObjects(recoObjList, 2000))
      // 	if(!TakeshiVision::detectAllYoloObjects(recoObjList, 2000))
      // 	  {}
      
      std::cout << "Takeshi is detecting objects whit Yisus...   " << std::endl;
      if(!TakeshiVision::detectAllObjects(recoObjList, false))
        if(!TakeshiVision::detectAllObjects(recoObjList, false))
      	 break;
      
      // if(recoObjList.size() > 0)
      //   TakeshiHRI::waitAfterSay("I have found the categories...", 2000);
      // else
      // {
      // 	TakeshiHRI::waitAfterSay("No categories found...", 2000);
      // 	TakeshiHRI::waitAfterSay("I am searching again..", 2000);
      // }

      for(int i = 0; i < recoObjList.size(); i++)
      {
	  std::cout << "  -> Obj[" << i << "]: " << recoObjList[i].id
		    << " - category: " << recoObjList[i].category << std::endl;
	  takeshi_say.str(std::string());

	  // takeshi_say << recoObjList[i].category;
	  // TakeshiHRI::waitAfterSay(takeshi_say.str(), 2000);
	  if(recoObjList[i].category.compare(category) == 0)
	  {
	      TakeshiHRI::waitAfterSay("I have found the category...", 2000);
	      TakeshiHRI::waitAfterSay(recoObjList[i].category, 2000);
	      std::cout << " -> Object " << recoObjList[i].id << " belong to category "
			<< recoObjList[i].category << std::endl << std::endl;
	      std::cout << "ObjectPosition: " << recoObjList[i].pose.position;
	      objX = recoObjList[i].pose.position.x;
	      objY = recoObjList[i].pose.position.y;
	      objZ = recoObjList[i].pose.position.z;
	      category_found = true;
	  }
      }
      ros::Duration(2.0).sleep();

      // If bool category_found is false, goDown Torso
      // If bool category_found is true then place object beside that category 
      if(category_found)
	nextState=1;
      else if(!isLowerShelf)
	nextState=2;
      else
	nextState=3;

      if(foundObject_attempts < 3 && !category_found )
      {
	nextState = 0;
	foundObject_attempts++;
      }
      
      break;

      
    case 1:
      // ================================
      // ==    STATE:   Place Objetc
      if(TakeshiTasks::placeObjectLateralAtPoint(objX, objY, objZ + 0.08))
	   success = true;
        else
        {
            nextState = 3;
        }
      break;

      
    case 2:
      // ================================
      // ==    STATE:  Torso Go Down 
      TakeshiManip::torsoGoTo(0.30, 3000);
      TakeshiManip::hdGoTo(1.5707, -0.6, 3000);
      foundObject_attempts = 0; 
      isLowerShelf = true;
      nextState = 0;
      break;

      
    case 3:
      //place objec in default pose
      // TakeshiHRI::waitAfterSay("I have not found category for this product...", 2000);
      TakeshiNavigation::moveDistAngle(0.0, 1.5707, 2000);
      TakeshiManip::torsoGoTo(0.55, 3000);
      TakeshiManip::armGoToArticular(-0.5, 0.0, -1.1, 0.0, 4000);
      TakeshiNavigation::moveDist(0.10, 3000);
      ros::Duration(2.0).sleep();


      TakeshiManip::openGripper(0.8);
      ros::Duration(2.0).sleep();
      TakeshiNavigation::moveDist(-0.20, 3000);
      
      // place objec in default pose
      // TakeshiHRI::waitAfterSay("I have not found category for this product...", 2000);
      // TakeshiNavigation::moveDistAngle(0.0, 1.5707, 2000);
      // TakeshiTasks::placeObject(0.06, 0.9 ,false);
      success = true;
      break;
    }
    ros::spinOnce();
    loop.sleep();
  }
  
  return true;
}



bool TakeshiTasks::detectObjectsNtimes(std::vector<vision_msgs::VisionObject>& recoObjList, int times)
{
        ros::Rate loop(10);
        bool saveFiles = false;
        std::vector<vision_msgs::VisionObject> recoObjListTemp;
        recoObjList.clear();
        cout << "\033[1;34m     TakeshiTasks.->Detect Objects N times " <<"\033[0m" << endl;

        for (unsigned int i=0; i<times; i++)
        {
                cout << "\033[1;34m     TakeshiTasks.->Attemp  "<<i<<"is running...\033[0m" << endl;
                TakeshiVision::detectObjects(recoObjListTemp, saveFiles);
                if(recoObjListTemp.size() > recoObjList.size()) {
                        recoObjList=recoObjListTemp;
                        ros::spinOnce();
                        loop.sleep();
                }
        }

        if(recoObjList.size() > 0)
                return true;
        else
                return false;
}

bool TakeshiTasks::detectObjectsOnPlaneNtimes(std::vector<vision_msgs::VisionObject>& recoObjList, int times, double height)
{
        ros::Rate loop(10);
        bool saveFiles = false;
        std::vector<vision_msgs::VisionObject> recoObjListTemp;
        recoObjList.clear();
        cout << "\033[1;34m     TakeshiTasks.->Detect Objects N times " <<"\033[0m" << endl;

        for (unsigned int i=0; i<times; i++)
        {
                cout << "\033[1;34m     TakeshiTasks.->Attemp  "<<i<<"is running...\033[0m" << endl;
                TakeshiVision::detectObjectsOnPlane(recoObjListTemp, height);
                if(recoObjListTemp.size() > recoObjList.size()) {
                        recoObjList=recoObjListTemp;
                        ros::spinOnce();
                        loop.sleep();
                }
        }

        if(recoObjList.size() > 0)
                return true;
        else
                return false;
}

//coyo was here
bool TakeshiTasks::detectAllObjectsOnPlaneAndMove(std::vector<vision_msgs::VisionObject>& recoObjList, double height)
{
        ros::Rate loop(10);
        bool saveFiles = false;
        std::vector<vision_msgs::VisionObject> recoObjListTemp;
        recoObjList.clear();
        cout << "\033[1;34m     TakeshiTasks.->Detect Objects N times " <<"\033[0m" << endl;
        int times = 3;
        float adv = 0.30;
        for (unsigned int i=0; i<times; i++)
        {
                cout << "\033[1;34m     TakeshiTasks.->Attemp  "<<i<<"is running...\033[0m" << endl;
                if (  TakeshiVision::detectAllObjectsOnPlane(recoObjListTemp, height)) {
                        TakeshiNavigation::moveDist(adv,4000);
                }
                else
                {
                        recoObjList = recoObjListTemp;
                        break;
                }
        }

        if(recoObjList.size() > 0)
                return true;
        else
                return false;
}


bool TakeshiTasks::giveObjectToHuman(){

        ros::Rate loop(10);
        bool success=false;
        int nextState=0;
        string lastRecoSpeech;
        geometry_msgs::PointStamped wrist;
        std::vector<std::string> specificGestures;
        vision_msgs::GestureSkeleton gesture;
        int attempts=0;
        specificGestures.push_back("hand_right_extended");
        specificGestures.push_back("hand_left_extended");

        cout << "\033[1;34m     TakeshiTasks.->Give Object to the human\033[0m" << endl;

        while(ros::ok() && !success) {
                switch (nextState) {

                case 0:
                        TakeshiHRI::waitAfterSay("To give you the object, extend your arm infront of you and do not move", 1000);
                        TakeshiVision::startSkeletonFinding();
                        ros::Duration(1).sleep();
                        nextState=1;
                        break;

                case 1:
                        //BUG:
                        //Hello MR Edgar I created a different function getBothWrists
                        //You can now request both wrist and th eprogram will try to sense
                        //Both using openpose, in case you want to use it!
                        //If it fails to find any wrist the point is set  to(0,0,0)
                        if(attempts > 5) {
                                TakeshiTasks::printTakeshiTaskMessage("can not detect gestures");
                                TakeshiHRI::say("I can not detect your hand");
                                TakeshiVision::stopSkeletonFinding();
                                ros::Duration(1.0).sleep();
                                return false;
                        }
                        if(TakeshiTasks::waitForSpecificGesture(gesture, specificGestures, 4000)) {
                                if(gesture.gesture.compare("hand_left_extended")==0)
                                        TakeshiHRI::say("I will give you the object in your left hand");
                                if(gesture.gesture.compare("hand_right_extended")==0)
                                        TakeshiHRI::say("I'll give you the object in your right hand");
                                TakeshiVision::stopSkeletonFinding();
                                ros::Duration(1.0).sleep();
                                nextState=3;
                        }
                        else{
                                attempts++;
                        }

                        break;
                case 2:
                        cout << "\033[1;34m     TakeshiTasks.->Give Object to the human: Find Wrist\033[0m" << endl;
                        if(TakeshiVision::getWrist(wrist))
                        {
                                nextState=3;
                        }
                        break;

                case 3:
                        cout << "\033[1;34m     TakeshiTasks.->Give Object to the human: HandOver\033[0m" << endl;
                        if(!TakeshiTasks::giveObject(gesture.gesture_centroid.x,gesture.gesture_centroid.y,gesture.gesture_centroid.z))
                            return false;    
                        success=true;
                        break;
                }
                ros::spinOnce();
                loop.sleep();
        }
        return true;
}

bool TakeshiTasks::openFridge(){

        ros::Rate loop(10);
        bool success=false, open=false;
        int nextState=0, attempts=0;
        float x,y,z,error, height;
        float distToFridge=0.75;
        std::vector<geometry_msgs::Point> handles;

        cout << "\033[1;34m     TakeshiTasks.->Openfridge\033[0m" << endl;

        while(ros::ok() && !success) {
                switch (nextState) {

                case 0:
                        TakeshiManip::openGripper(0.1);
                        TakeshiManip::navigationPose(4000);
                        nextState=1;
                        break;

                case 1:
                        TakeshiManip::hdGoTo(0.0, 0.0, 2000);
                        nextState=2;
                        break;

                case 2:
                        attempts++;
                        TakeshiVision::getHandles(handles);
                        for(int i=0; i<handles.size(); i++) {
                                if(fabs(handles[i].x) < 1.2 && fabs(handles[i].y) < 0.3) {
                                        x=handles[i].x;
                                        y=handles[i].y;
                                        z=handles[i].z;

                                        cout << "x :" << x << endl;
                                        cout << "y :" << y << endl;
                                        cout << "z :" << z << endl;
                                        attempts=0;
                                        nextState=3;
                                        break;
                                }
                                else{
                                        cout << "nel" << endl;
                                        cout << "x :" << handles[i].x << endl;
                                        cout << "y :" << handles[i].y << endl;
                                        cout << "z :" << handles[i].z << endl;

                                }
                        }

                        if(attempts > 5) {
                                TakeshiHRI::waitAfterSay("Sorry, I can not detected the fridge",3000);
                                return false;
                        }

                        break;

                case 3:
                        TakeshiManip::startHdGoTo(0.0, 0.0);
                        TakeshiTasks::takeHandle(x, y, z, height, true);
                        nextState=4;
                        break;

                case 4:
                        TakeshiNavigation::moveDist(-0.12, 2000);
                        TakeshiManip::openGripper(1.0);
                        ros::Duration(4.0).sleep();
                        nextState=5;
                        break;

                case 5:
                        TakeshiNavigation::moveDist(-0.15, 2000);
                        TakeshiManip::openGripper(0.1);
                        TakeshiManip::navigationPose(5000);
                        TakeshiNavigation::moveDist(0.20, 2000);
                        TakeshiManip::hdGoTo(0.0, 0.0, 2000);
                        nextState=6;
                        break;

                case 6:
                        TakeshiVision::getHandles(handles);
                        attempts++;
                        for(int i=0; i<handles.size(); i++) {
                                cout << "x :" << handles[i].x << endl;
                                cout << "y :" << handles[i].y << endl;
                                cout << "z :" << handles[i].z << endl;
                                error=pow((distToFridge-handles[i].x),2)+pow((z-handles[i].z),2);
                                cout << "error :" << error << endl;

                                if(error < 0.005) {
                                        cout << "Open : false "<< endl;
                                        open=false;
                                        nextState=7;
                                        break;
                                }

                        }

                        if(attempts > 5) {
                                open=true;
                                nextState=7;
                        }
                        break;

                case 7:
                        if (open) {
                                TakeshiHRI::waitAfterSay("I opened the fridge",3000);
                                nextState=8;
                        }
                        else{
                                TakeshiHRI::waitAfterSay("Sorry, I did not open the fridge",3000);
                                return false;
                        }

                        break;

                case 8:
                        TakeshiNavigation::moveLateral(0.3, 6000);
                        TakeshiNavigation::moveDist(-0.05, 2000);
                        TakeshiManip::waitForArmGoToAxiSZ(4000);
                        TakeshiManip::torsoGoTo(0.7, 4000);
                        TakeshiManip::closeGripper(1.0);
                        TakeshiManip::waitForArmGoToAxiSX(4000);
                        ros::Duration(1.0).sleep();
                        TakeshiManip::waitForArmGoToOpenFridge(4000);
                        TakeshiManip::waitForArmGoToOpenFridge2(4000);
                        TakeshiManip::waitForArmGoToOpenFridge(4000);
                        TakeshiNavigation::moveLateral(-0.20, 6000);
                        nextState=9;
                        break;

                case 9:
                        TakeshiNavigation::moveDistAngle(0.0,-0.35,4000);
                        nextState=10;
                        break;

                case 10:
                        TakeshiNavigation::moveDistAngle(0.0,0.35,4000);
                        TakeshiNavigation::moveLateral(-0.20, 6000);
                        nextState=11;
                        break;

                case 11:
                        TakeshiNavigation::moveDistAngle(0.0,-0.35,4000);
                        TakeshiManip::waitForArmGoToOpenFridge(5000);
                        ros::spinOnce();
                        loop.sleep();
                        nextState=12;
                        break;


                case 12:
                        TakeshiNavigation::moveDistAngle(0.0,0.35,4000);
                        TakeshiManip::navigationPose(4000);
                        success=true;
                        break;

                }
                ros::spinOnce();
                loop.sleep();
        }
        return true;
}

bool TakeshiTasks::closeFridge(){

        ros::Rate loop(10);
        bool success=false, open=false;
        int nextState=0, attempts=0;

        cout << "\033[1;34m     TakeshiTasks.->Closefridge\033[0m" << endl;

        while(ros::ok() && !success) {
                switch (nextState) {

                case 0:
                        TakeshiNavigation::getClose("fridge_close", 100000);
                        nextState=2;
                        break;

                case 2:
                        TakeshiManip::waitForArmGoToCloseFridge(4000);
                        TakeshiManip::torsoGoTo(0.35, 4000);
                        ros::Duration(2.0).sleep();
                        break;

                case 3:
                        TakeshiNavigation::moveDistAngle(0.0, 0.4, 2000);
                        nextState=4;
                        break;

                case 4:
                        TakeshiManip::navigationPose(4000);
                        break;

                }
                ros::spinOnce();
                loop.sleep();
        }
        return true;
}

bool TakeshiTasks::openDoor(){

        ros::Rate loop(10);
        bool success=false, open=false;
        int nextState=0, attempts=0;
        float x,y,z,error, height;
        float distToFridge=0.75;
        std::vector<geometry_msgs::Point> handles;

        cout << "\033[1;34m     TakeshiTasks.->Openfridge\033[0m" << endl;

        while(ros::ok() && !success) {
                switch (nextState) {

                case 0:
                        TakeshiManip::openGripper(0.1);
                        TakeshiManip::navigationPose(4000);
                        nextState=1;
                        break;

                case 1:
                        TakeshiManip::hdGoTo(0.0, 0.0, 2000);
                        nextState=2;
                        break;

                case 2:
                        attempts++;
                        TakeshiVision::getHandles(handles);
                        for(int i=0; i<handles.size(); i++) {
                                if(fabs(handles[i].x) < 1.2 && fabs(handles[i].y) < 0.3) {
                                        x=handles[i].x;
                                        y=handles[i].y;
                                        z=handles[i].z;

                                        cout << "x :" << x << endl;
                                        cout << "y :" << y << endl;
                                        cout << "z :" << z << endl;
                                        attempts=0;
                                        nextState=3;
                                        break;
                                }
                                else{
                                        cout << "nel" << endl;
                                        cout << "x :" << handles[i].x << endl;
                                        cout << "y :" << handles[i].y << endl;
                                        cout << "z :" << handles[i].z << endl;

                                }
                        }

                        if(attempts > 5) {
                                TakeshiHRI::waitAfterSay("Sorry, I can not detected the door",3000);
                                return false;
                        }

                        break;

                case 3:
                        TakeshiManip::startHdGoTo(0.0, 0.0);
                        TakeshiTasks::moveHandle(x,y,z, height);
                        nextState=4;
                        break;

                case 4:
                        TakeshiManip::torsoGoTo(height-0.2, 2000);
                        //TakeshiNavigation::moveDist(0.1, 2000);
                        TakeshiNavigation::moveLateral(0.1, 2000);
                        //TakeshiNavigation::moveDist(-0.1, 2000);
                        TakeshiManip::navigationPose(5000);

                        nextState=6;
                        break;

                case 6:
                        TakeshiVision::getHandles(handles);
                        attempts++;
                        for(int i=0; i<handles.size(); i++) {
                                cout << "x :" << handles[i].x << endl;
                                cout << "y :" << handles[i].y << endl;
                                cout << "z :" << handles[i].z << endl;
                                error=pow((distToFridge-handles[i].x),2)+pow((z-handles[i].z),2);
                                cout << "error :" << error << endl;

                                if(error < 0.005) {
                                        cout << "Open : false "<< endl;
                                        open=false;
                                        nextState=7;
                                        break;
                                }

                        }

                        if(attempts > 5) {
                                open=true;
                                nextState=7;
                        }
                        break;

                case 7:
                        if (open) {
                                TakeshiHRI::waitAfterSay("I opened the door",3000);
                                TakeshiNavigation::moveLateral(-0.3, 6000);
                                nextState=8;
                        }
                        else{
                                TakeshiHRI::waitAfterSay("Sorry, I did not open the door",3000);
                                TakeshiNavigation::moveLateral(-0.3, 6000);
                                return false;
                        }

                        break;

                case 8:

                        TakeshiManip::waitForArmGoToOpenDoor(5000);
                        ros::Duration(5.0).sleep();
                        TakeshiNavigation::moveDist(0.5, 3000);
                        nextState=12;
                        break;


                case 12:
                        TakeshiManip::navigationPose(4000);
                        success=true;
                        break;

                }
                ros::spinOnce();
                loop.sleep();
        }
        return true;
}

bool TakeshiTasks::openShelfDoor(){

        ros::Rate loop(10);
        bool success=false, open=false;
        int nextState=0, attempts=0;
        float x,y,z,error, height;
        float distToFridge=0.75;
        std::vector<geometry_msgs::Point> handles;
        std::vector<float> articular;

        cout << "\033[1;34m     TakeshiTasks.->OpenShelfDoor\033[0m" << endl;

        while(ros::ok() && !success) {
                switch (nextState) {
		case 0:
		  TakeshiManip::hdGoTo(0.0, -0.3, 2000);
		        articular.push_back( -0.8);
                        articular.push_back( 0.0);
                        articular.push_back( 0.0);
			articular.push_back( 0.0);
			TakeshiManip::startArmGoToArticular(articular);
                        TakeshiManip::startTorsoGoTo(0.25);
                        ros::Duration(2.0).sleep();
			TakeshiManip::hdGoTo(-0.5, -0.3, 2000);
			TakeshiNavigation::moveDist(0.35, 3000);
			ros::Duration(2.0).sleep();
			TakeshiNavigation::moveLateral(-0.18, 2000);
			ros::Duration(0.5).sleep();
			TakeshiNavigation::moveLateral(-0.05, 2000);
			ros::Duration(0.5).sleep();
			nextState=1;
                        break;

                case 1:
		  //Turn the wrist behind door shelf
                        articular[0] = -0.6;
                        articular[1] = -1.5707;
                        articular[2] = -1.5707;
                        articular[3] = 0.0;
                        TakeshiManip::armGoToArticular(articular, 2000);
                        ros::Duration(1.0).sleep();
                        nextState=2;
                        break;

                case 2:
                        
                        TakeshiManip::hdGoTo(0.0, -0.3, 2000);
                        TakeshiNavigation::moveDist(-0.1, 3000);
                        ros::Duration(1.0).sleep();
                        nextState=3;
                        break;

                case 3:
                        //Movement to open door
                        TakeshiManip::startHdGoTo(0.0, 0.0);
                        TakeshiNavigation::moveLateral(-0.08, 2000);
                        ros::Duration(0.5).sleep();
                        TakeshiNavigation::moveDistAngle(0.0, -0.9, 3000);
                        ros::Duration(1.0).sleep();
                        TakeshiNavigation::moveDistAngle(0.0, 0.9, 3000);
                        ros::Duration(1.0).sleep();
                        nextState=4;
                        break;

                case 4:
                        TakeshiNavigation::moveDist(-0.10, 2000);
                        TakeshiManip::torsoGoTo(0.0, 2000);
                        articular[0] =  0.0;
                        articular[1] = -1.5;
                        articular[2] = -1.5;
                        articular[3] =  0.0;
                        TakeshiManip::startArmGoToArticular(articular);
                        nextState=6;
                        break;

                case 6:

                        TakeshiManip::navigationPose(5000);
                        success = true;
                        break;

                }
                ros::spinOnce();
                loop.sleep();
        }
        return true;
}




bool TakeshiTasks::openDrawer(){

        bool success=false, open=false;
        int nextState=0, attempts=0;
        float x,y,z, error, height;
        float distToDrawer=0.8;
        float sizeDrawer=0.25;
        ros::Rate loop(10);

        std::vector<geometry_msgs::Point> handles;

        cout << "\033[1;34m     TakeshiTasks.->Give Object to the human\033[0m" << endl;

        while(ros::ok() && !success) {
                switch (nextState) {

                case 0:
                        TakeshiManip::openGripper(0.1);
                        TakeshiManip::navigationPose(6000);
                        nextState=1;
                        break;

                case 1:
                        TakeshiManip::hdGoTo(0.0, -0.8, 2000);
                        nextState=3;
                        break;

                case 3:
                        attempts++;
                        TakeshiVision::getHandles(handles);

                        for(int i=0; i<handles.size(); i++) {
                                if(fabs(handles[i].x) < 1.2 && fabs(handles[i].y) < 0.3) {
                                        x=handles[i].x;
                                        y=handles[i].y;
                                        z=handles[i].z;

                                        cout << "x :" << x << endl;
                                        cout << "y :" << y << endl;
                                        cout << "z :" << z << endl;
                                        nextState=4;
                                        break;
                                }
                                else{
                                        cout << "nel" << endl;
                                        cout << "x :" << handles[i].x << endl;
                                        cout << "y :" << handles[i].y << endl;
                                        cout << "z :" << handles[i].z << endl;
                                }
                        }

                        if(attempts > 5) {
                                TakeshiHRI::waitAfterSay("Sorry, I can not detected the fridge",3000);
                                return false;
                        }
                        break;

                case 4:
                        TakeshiManip::startHdGoTo(0.0, 0.0);
                        TakeshiTasks::takeHandle(x, y, z, height, false);
                        nextState=5;
                        break;

                case 5:
                        TakeshiNavigation::moveDist(-sizeDrawer, 4000);
                        ros::spinOnce();
                        ros::Duration(3.0).sleep();
                        TakeshiManip::openGripper(1.0);
                        ros::spinOnce();
                        ros::Duration(3.0).sleep();
                        TakeshiNavigation::moveDist(-0.15, 2000);
                        nextState=6;
                        break;

                case 6:
                        TakeshiManip::navigationPose(4000);
                        ros::Duration(3.0).sleep();
                        nextState=7;
                        break;

                case 7:
                        TakeshiManip::hdGoTo(0.0, -0.8, 2000);
                        TakeshiVision::getHandles(handles);
                        attempts++;
                        for(int i=0; i<handles.size(); i++) {
                                cout << "x :" << handles[i].x << endl;
                                cout << "y :" << handles[i].y << endl;
                                cout << "z :" << handles[i].z << endl;
                                error=pow((distToDrawer-handles[i].x),2)+pow((z-handles[i].z),2);
                                cout << "error :" << error << endl;

                                if(error < 0.005) {
                                        cout << "Open : true "<< endl;
                                        open=true;
                                        nextState=8;
                                        break;
                                }
                        }

                        if(attempts > 5)
                                nextState=8;

                        break;

                case 8:
                        if (open)
                                TakeshiHRI::waitAfterSay("I opened the drawer",3000);
                        else
                                TakeshiHRI::waitAfterSay("Sorry, I did not open the drawer",3000);

                        TakeshiManip::navigationPose(6000);
                        TakeshiNavigation::moveDist(0.45, 2000);
                        success=true;

                        break;

                }
                ros::spinOnce();
                loop.sleep();
        }
        return open;
}

bool TakeshiTasks::graspObjectOnTheFridge(std::string idObject, bool verify){
        geometry_msgs::Pose pose;
        std::vector<vision_msgs::VisionObject> recognizedObjects;
        std::stringstream takeshi_say;
        bool isDetected=false;
        TakeshiNavigation::moveDistAngle(0.0, -1.5707, 4000);
        TakeshiTasks::alignWithTable(0.3, false);

        float x,y,z;

        // If NO id object, grap the nearest object
        if(idObject.compare("") != 0)
        {
                cout << "\033[1;34m     TakeshiTasks.->Look for specific object: " << idObject << "\033[0m" << endl;
                for(int i=0; i<4; i++) {
                        isDetected=TakeshiTasks::findObject(idObject, pose,TakeshiTasks::LATERALUP);
                        if(isDetected)
                                break;
                }
                if(!isDetected) {
                        //while (!TakeshiTasks::findObject(idObject, pose, TakeshiTasks::LATERAL) && ros::ok())
                        cout << "No object!!!!" << endl;
                        return false;
                }
                cout << "\033[1;34m     TakeshiTasks.->Object " << idObject << " position: " << pose.position << "\033[0m" << endl;
                // Variables for inverse kinematic calculate
                x = pose.position.x;
                y = pose.position.y;
                z = pose.position.z;
        }
        else
        {
                cout << "\033[1;34m     TakeshiTasks.->Look for NO SPECIFIC OBJECT\033[0m" << endl;

                // // Find object again and correct the new angle
                if (!TakeshiVision::detectObjects(recognizedObjects, false))
                        cout << "Nothing detected!!!!" << endl;

                //Supouse first objReco is the nearest object
                cout << "\033[1;34m     TakeshiTasks.->Object position:" << recognizedObjects[0].pose.position << "\033[0m" << endl;
                x = recognizedObjects[0].pose.position.x;
                y = recognizedObjects[0].pose.position.y;
                z = recognizedObjects[0].pose.position.z;
        }

        if(!TakeshiTasks::graspObjectLateral(x, y, z, verify)) {
                takeshi_say << "I could not take the object " << idObject;
                TakeshiHRI::say( takeshi_say.str());
                return false;
        }
        else{
                takeshi_say << "I take the object " << idObject;
                TakeshiHRI::say( takeshi_say.str());
                return true;
        }
}

void TakeshiTasks::sayAndAsyncNavigateToLoc(std::string location, bool say)
{
        /// This wrappers makes takeshi say where he is planning to go and then
        /// goes there, it is nono blocking and does not provide any feedback
        std::cout << "Navigation to " << location << std::endl;
        if (say) {
                std::stringstream ss;
                ss << "I will navigate to the " << location;
                TakeshiHRI::say(ss.str());
        }
        TakeshiNavigation::startGetClose(location);
}

bool TakeshiTasks::sayAndSyncNavigateToLoc(std::string location, int timeout, bool say)
{
        //Makes takeshi state its destination and request  navigation to said location
        // on specified timeout Returns true if succesfully arrived at location
        std::cout << "Navigation to " << location << std::endl;
        std::stringstream ss;
        if (say) {
                ss << "I will navigate to the " << location;
                TakeshiHRI::say(ss.str());
        }
        bool reached = TakeshiNavigation::getClose(location,timeout);

        ss.str("");
        if (say)
        {
                if (reached)
                {
                        ss << "I reached the" << location;
                }
                else
                {
                        ss << "I did not reached the " << location;
                }
                TakeshiHRI::say(ss.str());
        }
        return reached;
}

std::vector<vision_msgs::VisionFaceObject> TakeshiTasks::recognizeAllFaces(float timeOut, bool &recognized)
{
        TakeshiVision::startFaceRecognition();
        recognized = false;
        int previousSize = 20;
        int sameValue = 0;
        boost::posix_time::ptime curr;
        boost::posix_time::ptime prev = boost::posix_time::second_clock::local_time();
        boost::posix_time::time_duration diff;
        std::vector<vision_msgs::VisionFaceObject> lastRecognizedFaces;

        do
        {
                boost::this_thread::sleep(boost::posix_time::milliseconds(100));
                TakeshiVision::getLastRecognizedFaces(lastRecognizedFaces);
                ros::Duration(1.0).sleep();

                if(lastRecognizedFaces.size() == previousSize && lastRecognizedFaces.size() > 0)
                        sameValue++;
                if(sameValue == 3)
                        recognized = true;
                else
                {
                        previousSize = lastRecognizedFaces.size();
                        recognized = false;
                }
                curr = boost::posix_time::second_clock::local_time();
                ros::spinOnce();
        } while(ros::ok() && (curr - prev).total_milliseconds()< timeOut && !recognized);

        std::cout << "recognized:" << recognized << std::endl;
        return lastRecognizedFaces;
}

bool TakeshiTasks::findCrowd(int &men, int &women, int &sitting, int &standing, int &lying, std::string location) {

        std::vector<int> facesDistances;
        std::stringstream ss;
        std::string personID = "";

        TakeshiManip::startHdGoTo(0, 0.0);
        TakeshiManip::waitForHdGoalReached(5000);
        ros::Time time;

        std::cout << "Find the crowd " << std::endl;

        ss << ", I am going to find the crowd";
        time = ros::Time::now();
        //JustinaHRI::insertAsyncSpeech(ss.str(), 500, time.sec, 10);
        TakeshiHRI::say(ss.str());

        Eigen::Vector3d centroidFace;
        int genderRecog;

        bool recog = turnAndRecognizeFace(personID, -1, NONE, -M_PI_4, M_PI_4 / 2.0, M_PI_4, 0, -M_PI_4, -M_PI_4, M_PI_2, 2 * M_PI, centroidFace, genderRecog); //, location);
        std::cout << "Centroid Face in coordinates of robot:" << centroidFace(0, 0)
                  << "," << centroidFace(1, 0) << "," << centroidFace(2, 0) << ")";
        std::cout << std::endl;
        //personLocation.clear();

        ss.str("");
        if (!recog) {
                std::cout << "I have not found the crowd "<< std::endl;
                ss << "I did not find a the crowd";
                time = ros::Time::now();
                //JustinaHRI::insertAsyncSpeech(ss.str(), 500, time.sec, 10);
                //JustinaHRI::waitAfterSay(ss.str(), 2000);
                TakeshiHRI::say(ss.str());
                return false;
        }

        std::cout << "I found the crowd " << std::endl;
        //ss << person << ", I found you";
        ss << ", I find a person";
        time = ros::Time::now();
        //JustinaHRI::insertAsyncSpeech(ss.str(), 500, time.sec, 10);
        TakeshiHRI::say(ss.str());
        TakeshiHRI::say("please do not move, I am going to count the number of people");
        //JustinaHRI::waitAfterSay(ss.str(), 2000);

        float cx, cy, cz;
        cx = centroidFace(0, 0);
        cy = centroidFace(1, 0);
        cz = centroidFace(2, 0);
        TakeshiTools::transformPoint("/base_link", cx, cy, cz, "/map", cx, cy, cz);
        tf::Vector3 worldFaceCentroid(cx, cy, cz);

        //JustinaHRI::waitAfterSay("I am getting close to you", 2000);
        //closeToGoalWithDistanceTHR(worldFaceCentroid.x(), worldFaceCentroid.y(), 1.0, 40000);
        float currx, curry, currtheta;

        TakeshiKnowledge::getRobotPose(currx, curry, currtheta);

        float thetaToGoal = atan2(worldFaceCentroid.y() - curry, worldFaceCentroid.x() - currx);
        if (thetaToGoal < 0.0f)
                thetaToGoal = 2 * M_PI + thetaToGoal;
        float theta = thetaToGoal - currtheta;
        std::cout << "JustinaTasks.->Turn in direction of robot:" << theta << std::endl;
        TakeshiNavigation::moveDistAngle(0, theta, 2000);

        TakeshiManip::startHdGoTo(0, 0.0);
        TakeshiManip::waitForHdGoalReached(5000);

        int contChances = 0;
        std::vector<vision_msgs::VisionFaceObject> dFaces;
        recog = false;

        //JustinaHRI::say("please do not move, I am going to count the number of people");
        ros::Duration(1.5).sleep();
        while(!recog && contChances < 2) {
                dFaces = recognizeAllFaces(10000,recog);
                boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
                //JustinaVision::startFaceDetection(false);
                TakeshiVision::stopFaceRecognition();
                contChances++;
        }

        std::cout << "size of array is: " << dFaces.size() << std::endl;

        for(int i=0; i<dFaces.size(); i++)
        {
                if(dFaces[i].face_centroid.z < 0.8) {
                        lying++;
                }
                if(dFaces[i].face_centroid.z >= 0.8 && dFaces[i].face_centroid.z <1.20) {
                        sitting++;
                }
                if(dFaces[i].face_centroid.z >= 1.20) {
                        standing++;
                }
                if(dFaces[i].gender==0) {
                        women++;
                }
                if(dFaces[i].gender==1) {
                        men++;
                }
        }


        return true;
}

bool TakeshiTasks::getNearestRecognizedFaceGPSR(std::vector<vision_msgs::VisionFaceObject> facesObject, float distanceMax, Eigen::Vector3d &faceCentroid, int &genderRecog, std::string location) {
        int indexMin;
        float distanceMin = 99999999.0;
        faceCentroid = Eigen::Vector3d::Zero();
        bool found = false;
        for (int i = 0; i < facesObject.size(); i++) {
                vision_msgs::VisionFaceObject vro = facesObject[i];
                float cx, cy, cz;
                cx = vro.face_centroid.x;
                cy = vro.face_centroid.y;
                cz = vro.face_centroid.z;
                TakeshiTools::transformPoint("/base_link", cx, cy, cz, "/map", cx, cy, cz);
                if(!TakeshiKnowledge::isPointInKnownArea(cx, cy, location))
                        continue;
                Eigen::Vector3d centroid = Eigen::Vector3d::Zero();
                centroid(0, 0) = vro.face_centroid.x;
                centroid(1, 0) = vro.face_centroid.y;
                centroid(2, 0) = vro.face_centroid.z;
                float dist = centroid.norm();
                if (dist < distanceMax && dist < distanceMin) {
                        indexMin = i;
                        distanceMin = dist;
                        found = true;
                }
        }
        if (found) {
                std::cout << "I found the centroid nearest to robot" << std::endl;
                faceCentroid(0, 0) = facesObject[indexMin].face_centroid.x;
                faceCentroid(1, 0) = facesObject[indexMin].face_centroid.y;
                faceCentroid(2, 0) = facesObject[indexMin].face_centroid.z;
                genderRecog = facesObject[indexMin].gender;
        }
        std::cout << "Face centroid:" << faceCentroid(0, 0) << ","
                  << faceCentroid(1, 0) << "," << faceCentroid(2, 0);
        std::cout << std::endl;
        return found;
}

bool TakeshiTasks::turnAndRecognizeFaceGPSR(std::string id, int gender, POSE pose, float initAngPan, float incAngPan, float maxAngPan, float initAngTil, float incAngTil, float maxAngTil, float incAngleTurn, float maxAngleTurn, Eigen::Vector3d &centroidFace, int &genderRecog, std::string location) {

        bool recog = false;
        bool moveBase = false;
        float initTil = initAngTil;
        float incTil = incAngTil;
        bool direction = false;
        bool taskStop = false;
        centroidFace = Eigen::Vector3d::Zero();

        if(pose == STANDING)
                maxAngTil = initAngTil;

        for(float baseTurn = incAngleTurn; ros::ok() && baseTurn <= maxAngleTurn && !recog; baseTurn+=incAngleTurn) {
                for(float headPanTurn = initAngPan; ros::ok() && headPanTurn <= maxAngPan && !recog; headPanTurn+=incAngPan) {
                        float currTil;
                        for (float headTilTurn = initTil; ros::ok() && ((!direction && headTilTurn >= maxAngTil) || (direction && headTilTurn <= initAngTil)) && !recog; headTilTurn+=incTil) {
                                currTil = headTilTurn;
                                TakeshiManip::startHdGoTo(headPanTurn, headTilTurn);
                                if(moveBase) {
                                        TakeshiNavigation::moveDistAngle(0.0, incAngleTurn, 4000);
                                        moveBase = false;
                                }
                                TakeshiManip::waitForHdGoalReached(3000);
                                boost::this_thread::sleep(boost::posix_time::milliseconds(500));
                                std::vector<vision_msgs::VisionFaceObject> facesObject;
                                recog = waitRecognizedFace(2000, id, gender, pose, facesObject);
                                if(recog)
                                        recog = getNearestRecognizedFaceGPSR(facesObject, 4.5, centroidFace, genderRecog, location);
                                ros::spinOnce();
                                taskStop = TakeshiTasks::tasksStop();
                                if(taskStop)
                                        return false;
                        }
                        initTil = currTil;
                        direction ^= true;
                        incTil = -incTil;
                }
                moveBase = true;
        }
        return recog;
}

//function just for compatibility and debuging
void TakeshiTasks::callbackTasksStop(const std_msgs::Empty::ConstPtr& msg)
{
        _tasksStop = true;
}

bool TakeshiTasks::tasksStop(){
        bool tasksStop = _tasksStop;
        _tasksStop = false;
        return tasksStop;
}

bool TakeshiTasks::findTable(std::string &ss)
{
        std::cout << "TakeshiTasks::findTable" << std::endl;

        TakeshiHRI::say("I am going to search the closes table");
        TakeshiManip::hdGoTo(0.0, -0.7, 4000);
        //TakeshiHRI::waitAfterSay("I am serching table in front of me", 1500);
        if(TakeshiVision::findPlane())
        {
                TakeshiHRI::say("I found a table");
                ss = "center";
                return true;
        }

        //Turn head to left
        TakeshiManip::hdGoTo(1.57, -0.7, 4000);
        //JustinaHRI::waitAfterSay("I am serching table on my left side", 2500);
        if(TakeshiVision::findPlane())
        {
                TakeshiHRI::say("I found a table");
                //JustinaHRI::waitAfterSay("I have found a table", 1500);
                TakeshiNavigation::startMoveDistAngle(0.0, M_PI / 2.0);
                //TakeshiManip::hdGoTo(0.0, -0.7, 4000);
                ss = "left";
                return true;
        }

        //Turn head to right
        TakeshiManip::hdGoTo(-1.57, -0.7, 4000);
        //JustinaHRI::waitAfterSay("I am serching table on my right side", 1500);
        if(TakeshiVision::findPlane())
        {
                TakeshiHRI::say("I found a table");
                //JustinaHRI::waitAfterSay("I have found a table", 1500);
                TakeshiNavigation::startMoveDistAngle(0.0, -M_PI / 2.0);
                //TakeshiManip::hdGoTo(0.0, -1.57, 4000);
                ss = "right";
                return true;
        }

        return false;
}

bool TakeshiTasks::turnAndRecognizeGesture(std::string typeGesture, float initAngPan, float incAngPan, float maxAngPan, float initAngTil, float incAngTil, float maxAngTil, float incAngleTurn, float maxAngleTurn, float maxDistance, Eigen::Vector3d &gesturePos, std::string location){

        bool recog = false;
        bool moveBase = false;
        float initTil = initAngTil;
        float incTil = incAngTil;
        bool direction = false;
        Eigen::Vector3d centroidGesture = Eigen::Vector3d::Zero();

        for(float baseTurn = incAngleTurn; ros::ok() && baseTurn <= maxAngleTurn && !recog; baseTurn+=incAngleTurn) {
                for(float headPanTurn = initAngPan; ros::ok() && headPanTurn <= maxAngPan && !recog; headPanTurn+=incAngPan) {
                        float currTil;
                        for (float headTilTurn = initTil; ros::ok() && ((!direction && headTilTurn >= maxAngTil) || (direction && headTilTurn <= initAngTil)) && !recog; headTilTurn+=incTil) {
                                currTil = headTilTurn;
                                TakeshiManip::startHdGoTo(headPanTurn, headTilTurn);
                                if(moveBase) {
                                        TakeshiNavigation::moveDistAngle(0.0, incAngleTurn, 4000);
                                        moveBase = false;
                                }
                                TakeshiManip::waitForHdGoalReached(3000);
                                std::vector<vision_msgs::GestureSkeleton> gestures;
                                recog = waitRecognizedGesture(gestures, 3000);
                                if(recog)
                                        recog = getNearestRecognizedGesture(typeGesture, gestures, maxDistance, centroidGesture, location);
                                boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
                        }
                        initTil = currTil;
                        direction ^= true;
                        incTil = -incTil;
                }
                moveBase = true;
        }
        if(recog)
                gesturePos = centroidGesture;
        return recog;
}

bool TakeshiTasks::getNearestRecognizedGesture(std::string typeGesture, std::vector<vision_msgs::GestureSkeleton> gestures, float distanceMax, Eigen::Vector3d &nearestGesture, std::string location){
        int indexMin;
        float distanceMin = 99999999.0;
        bool found = false;
        for (int i = 0; i < gestures.size(); i++) {
                vision_msgs::GestureSkeleton g = gestures[i];

                if(typeGesture.compare("waving") != 0) {
                        if(g.gesture.compare(typeGesture) != 0)
                                continue;
                }
                else if(!(g.gesture.compare("left_waving") == 0 || g.gesture.compare("right_waving") == 0)) {
                        continue;
                }
                float cx, cy, cz;
                cx = g.gesture_centroid.x;
                cy = g.gesture_centroid.y;
                cz = g.gesture_centroid.z;
                TakeshiTools::transformPoint("/base_link", cx, cy, cz, "/map", cx, cy, cz);
                if(!TakeshiKnowledge::isPointInKnownArea(cx, cy, location))
                        continue;
                Eigen::Vector3d pos = Eigen::Vector3d::Zero();
                pos(0, 0) = g.gesture_centroid.x;
                pos(1, 0) = g.gesture_centroid.y;
                pos(2, 0) = g.gesture_centroid.z;
                float dist = pos.norm();
                if (dist < distanceMax && dist < distanceMin) {
                        indexMin = i;
                        distanceMin = dist;
                        found = true;
                }
        }
        if(!found)
                return false;
        std::cout << "I found the gesture nearest to robot" << std::endl;
        nearestGesture(0, 0) = gestures[indexMin].gesture_centroid.x;
        nearestGesture(1, 0) = gestures[indexMin].gesture_centroid.y;
        nearestGesture(2, 0) = gestures[indexMin].gesture_centroid.z;
        std::cout << "Gesture centroid:" << nearestGesture(0, 0) << "," << nearestGesture(1, 0) << "," << nearestGesture(2, 0);
        std::cout << std::endl;
        return true;
}
