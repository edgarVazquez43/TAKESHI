#include "MvnPln.h"
using namespace std;

MvnPln::MvnPln()
{
        this->newTask = false;
        this->correctFinalAngle = false;
        this->collisionDetected = false;
        this->stopReceived = false;
        this->isLastPathPublished = false;
        this->_allow_move_lateral = false;
        this->max_attempts = 0;
}

MvnPln::~MvnPln()
{
}

void MvnPln::initROSConnection(ros::NodeHandle* nh)
{
        this->nh = nh;
        //Publishers and subscribers for the commands executed by this node
        this->subGetCloseLoc = nh->subscribe("/navigation/mvn_pln/get_close_loc", 10, &MvnPln::callbackGetCloseLoc, this);
        this->subGetCloseXYA = nh->subscribe("/navigation/mvn_pln/get_close_xya", 10, &MvnPln::callbackGetCloseXYA, this);
        this->subClickedPoint = nh->subscribe("/clicked_point", 1, &MvnPln::callbackClickedPoint, this);
        this->subRobotStop = nh->subscribe("/hardware/robot_state/stop", 10, &MvnPln::callbackRobotStop, this);
        this->pubGlobalGoalReached = nh->advertise<std_msgs::Bool>("/navigation/global_goal_reached", 10);
        this->pubLastPath = nh->advertise<nav_msgs::Path>("/navigation/mvn_pln/last_calc_path", 1);
        this->srvPlanPath = nh->advertiseService("/navigation/mvn_pln/plan_path", &MvnPln::callbackPlanPath, this);
        this->subLaserScan = nh->subscribe("/hsrb/base_scan", 1, &MvnPln::callbackLaserScan, this);
        this->subCollisionRisk = nh->subscribe("/navigation/obs_avoid/collision_risk", 10, &MvnPln::callbackCollisionRisk, this);
        this->subCollisionPoint = nh->subscribe("/navigation/obs_avoid/collision_point", 10, &MvnPln::callbackCollisionPoint, this);

        this->cltGetMap = nh->serviceClient<nav_msgs::GetMap>("/navigation/localization/static_map");
        this->cltPathFromMapAStar = nh->serviceClient<navig_msgs::PathFromMap>("/navigation/path_planning/path_calculator/a_star_from_map");
        this->cltGetRgbdWrtRobot = nh->serviceClient<point_cloud_manager::GetRgbd>("/hardware/point_cloud_man/get_rgbd_wrt_robot");
        tf_listener.waitForTransform("map", "base_link", ros::Time(0), ros::Duration(5.0));
}

void MvnPln::spin()
{
        ros::Rate loop(10);
        int currentState = SM_INIT;
        float robotX, robotY, robotTheta;
        float angleError;
        std_msgs::Bool msgGoalReached;
        bool pathSuccess = false;
        float lateralMovement;
        int collision_detected_counter = 0;
        float reachThreshold = 0.10;
        while(ros::ok())
        {
                if(this->stopReceived)
                {
                        this->stopReceived = false;
                        currentState = SM_INIT;
                }
                switch(currentState)
                {
                case SM_INIT:
                        cout << "\033[1;37m     MvnPln.->Current state: " << currentState << ". Waiting for new task...\033[0m" << endl;
                        currentState = SM_WAITING_FOR_NEW_TASK;
                        break;
                case SM_WAITING_FOR_NEW_TASK:
                        if(this->newTask)
                        {
                                cout << "\033[1;37m     MvnPln.->New task received...\033[0m" << endl;
                                this->newTask = false;
                                currentState = SM_CALCULATE_PATH;
                                collision_detected_counter = 0;
                        }
                        break;
                case SM_CALCULATE_PATH:
                        cout << "\033[1;37m     MvnPln.->Current state: " << currentState << ". Calculating path using map, kinect and laser\033[0m" << endl;
                        cout << "\033[1;37m     MvnPl.->Moving backwards if there is an obstacle before calculating path\033[0m" << endl;
                        if(TakeshiNavigation::obstacleInFront())
                                TakeshiNavigation::moveDist(-0.2, 5000);
                        if(TakeshiNavigation::obstacleInFront())
                                TakeshiNavigation::moveDist(-0.2, 5000);
                        //if(JustinaNavigation::obstacleInFront())
                        //    JustinaNavigation::moveDist(-0.15, 5000);
                        //if(JustinaNavigation::obstacleInFront())
                        //    JustinaNavigation::moveDist(-0.15, 5000);
                        cout << "\033[1;37m     MvnPln.->Moving head to search for obstacles in front of the robot\033[0m" << endl;

                        TakeshiManip::hdGoTo(0, -0.9, 2500);
                        //TakeshiManip::hdGoTo(0, -0.9, 2500);
                        //TakeshiManip::hdGoTo(0, -0.9, 2500);
                        TakeshiKnowledge::getRobotPose(robotX, robotY, robotTheta);
                        pathSuccess = this->planPath(robotX, robotY, this->goalX, this->goalY, this->lastCalcPath);
                        if(!pathSuccess)
                        {
                                cout << "\033[1;37m     MvnPln.->Cannot calc path to "<<this->goalX<<" "<<this->goalY<<" after several attempts\033[0m" << endl;
                                TakeshiManip::hdGoTo(0, 0, 2500);
                                msgGoalReached.data = false;
                                this->pubGlobalGoalReached.publish(msgGoalReached);
                                currentState = SM_INIT;
                        }
                        else
                                currentState = SM_START_MOVE_PATH;
                        break;
                case SM_START_MOVE_PATH:
                        cout << "\033[1;37m     MvnPln.->Current state: " << currentState << ". Starting move path\033[0m" << endl;
                        cout << "\033[1;37m     MvnPln.->Turning on collision detection...\033[0m" << endl;
                        this->collisionDetected = false;
                        TakeshiNavigation::enableObstacleDetection(true);
                        TakeshiNavigation::startMovePath(this->lastCalcPath);
                        currentState = SM_WAIT_FOR_MOVE_FINISHED;
                        break;
                case SM_WAIT_FOR_MOVE_FINISHED:
                        if(TakeshiNavigation::isGoalReached())
                        {
                                cout << "\033[1;37m     MvnPln.->Move path finished succesfully. \033[0m" << endl;
                                TakeshiNavigation::enableObstacleDetection(false);
                                if(this->correctFinalAngle) //This flag is set in the callbacks
                                        currentState = SM_CORRECT_FINAL_ANGLE;
                                else
                                {
                                        cout << "\033[1;37m     MnvPln.->Goal point reached successfully!!!!!!! \033[0m" << endl;
                                        TakeshiNavigation::enableObstacleDetection(false);
                                        TakeshiManip::hdGoTo(0, 0, 2500);
                                        msgGoalReached.data = true;
                                        this->pubGlobalGoalReached.publish(msgGoalReached);
                                        currentState = SM_INIT;
                                }
                        }
                        else if(this->collisionDetected)
                        {
                                cout << "\033[1;37m     MvnPln.->COLLISION RISK DETECTED before goal is reached.\033[0m" << endl;
                                this->collisionDetected = false;
                                currentState = SM_COLLISION_DETECTED;
                        }
                        else if(this->stopReceived)
                        {
                                cout << "\033[1;37m     MvnPln.->Stop signal received...\033[0m" << endl;
                                TakeshiNavigation::enableObstacleDetection(false);
                                TakeshiManip::hdGoTo(0, 0, 2500);
                                msgGoalReached.data = false;
                                this->pubGlobalGoalReached.publish(msgGoalReached);
                                currentState = SM_INIT;
                        }
                        break;
                case SM_COLLISION_DETECTED:
                        cout << "\033[1;37m     MvnPln.->Current state: " << currentState << ". Stopping robot smoothly\033[0m" << endl;
                        TakeshiKnowledge::getRobotPose(robotX, robotY, robotTheta);
                        //If robot is 0.6 near the goal, it is considered that it has reached the goal

                        if(sqrt((robotX - this->goalX)*(robotX - this->goalX) + (robotY - this->goalY)*(robotY - this->goalY)) < reachThreshold)
                        {
                                if(this->correctFinalAngle) //This flag is set in the callbacks
                                        currentState = SM_CORRECT_FINAL_ANGLE;
                                else
                                {
                                        cout << "\033[1;37m     MnvPln.->Goal point reached successfully!!!!!!!\033[0m" << endl;
                                        TakeshiNavigation::enableObstacleDetection(false);
                                        TakeshiManip::hdGoTo(0, 0, 2500);
                                        msgGoalReached.data = true;
                                        this->pubGlobalGoalReached.publish(msgGoalReached);
                                        currentState = SM_INIT;
                                }
                        }
                        else
                        {
                                if(this->collisionDetected)
                                {
                                        TakeshiNavigation::moveDist(-0.10, 5000);
                                        if(this->collisionPointY < 0)
                                                lateralMovement = 0.25 + this->collisionPointY + 0.051;
                                        else
                                                lateralMovement = this->collisionPointY - 0.25 - 0.051;
                                        //if(lateralMovement > 0.15)
                                        //    lateralMovement = 0.15;
                                        //if(lateralMovement < -0.15)
                                        //    lateralMovement = -0.15;
                                        if(this->_allow_move_lateral)
                                                TakeshiNavigation::moveLateral(lateralMovement, 5000);
                                        //JustinaNavigation::moveDist(0.05, 2500);
                                }
                                currentState = SM_CALCULATE_PATH;
                                if(++collision_detected_counter > this->max_attempts)
                                {
                                        cout << "\033[1;37m     MnvPln.->Max attempts after collision detected reached!! max_attempts= " << this->max_attempts <<"\033[0m" << endl;
                                        TakeshiNavigation::enableObstacleDetection(false);
                                        TakeshiManip::hdGoTo(0, 0, 2500);
                                        msgGoalReached.data = true;
                                        this->pubGlobalGoalReached.publish(msgGoalReached);
                                        currentState = SM_INIT;
                                }
                        }
                        break;
                case SM_CORRECT_FINAL_ANGLE:
                        cout << "\033[1;37m     MvnPln.->CurrentState: " << currentState << ". Correcting final angle\033[0m" << endl;
                        TakeshiKnowledge::getRobotPose(robotX, robotY, robotTheta);
                        angleError = this->goalAngle - robotTheta;
                        if(angleError > M_PI) angleError -= 2*M_PI;
                        if(angleError <= -M_PI) angleError += 2*M_PI;
                        TakeshiNavigation::startMoveDistAngle(0.0, angleError);
                        currentState = SM_WAIT_FOR_ANGLE_CORRECTED;
                        break;
                case SM_WAIT_FOR_ANGLE_CORRECTED:
                        if(TakeshiNavigation::isGoalReached())
                        {
                                cout << "\033[1;37m     MvnPln.->Angle correction finished succesfully. \033[0m" << endl;
                                cout << "\033[1;37m     MnvPln.->Goal point reached successfully!!!!!!!\033[0m" << endl;
                                TakeshiNavigation::enableObstacleDetection(false);
                                msgGoalReached.data = true;
                                TakeshiManip::hdGoTo(0, 0, 2500);
                                this->pubGlobalGoalReached.publish(msgGoalReached);
                                currentState = SM_INIT;
                        }
                        break;
                }

                if(!this->isLastPathPublished)
                {
                        this->pubLastPath.publish(this->lastCalcPath);
                        this->isLastPathPublished = true;
                }
                ros::spinOnce();
                loop.sleep();
        }
}

void MvnPln::allow_move_lateral(bool _allow_move_lateral)
{
        this->_allow_move_lateral = _allow_move_lateral;
}

bool MvnPln::planPath(float startX, float startY, float goalX, float goalY, nav_msgs::Path& path)
{
        //bool pathSuccess =  this->planPath(startX, startY, goalX, goalY, path, true, true, true);
        //if(!pathSuccess)
        bool pathSuccess =  this->planPath(startX, startY, goalX, goalY, path, true, false, true);
        if(!pathSuccess)
                pathSuccess =  this->planPath(startX, startY, goalX, goalY, path, true, true, false);
        if(!pathSuccess)
                pathSuccess =  this->planPath(startX, startY, goalX, goalY, path, false, true, true);
        if(!pathSuccess)
                pathSuccess =  this->planPath(startX, startY, goalX, goalY, path, false, false, true);
        if(!pathSuccess)
                pathSuccess =  this->planPath(startX, startY, goalX, goalY, path, false, true, false);
        return pathSuccess;
}

bool MvnPln::planPath(float startX, float startY, float goalX, float goalY, nav_msgs::Path& path,
                      bool useMap, bool useLaser, bool useKinect)
{
        cout << "\033[1;37m     MvnPln.->Calculating path with augmented map...\033[0m" << endl;
        nav_msgs::OccupancyGrid augmentedMap;

        //
        //If use_map, then gets the map from map_server
        if(useMap)
        {
                nav_msgs::GetMap srvGetMap;
                cout << "\033[1;37m     MvnPln.->Getting occupancy grid from map server...\033[0m" << endl;
                if(!this->cltGetMap.call(srvGetMap))
                {
                        cout << "\033[1;37m     MvnPln.->Cannot get map from map_server.\033[0m" << endl;
                        return false;
                }
                augmentedMap = srvGetMap.response.map;
        }
        else
        {
                augmentedMap.header.frame_id = "base_link";
                augmentedMap.info.resolution = 0.05;
                augmentedMap.info.width = 1000;
                augmentedMap.info.height = 1000;
                augmentedMap.info.origin.position.x = -25.0;
                augmentedMap.info.origin.position.y = -25.0;
                augmentedMap.data.resize(augmentedMap.info.width*augmentedMap.info.height);
                for (size_t i=0; i < augmentedMap.data.size(); i++)
                        augmentedMap.data[i] = 0;
        }
        float mapOriginX = augmentedMap.info.origin.position.x;
        float mapOriginY = augmentedMap.info.origin.position.y;
        float mapResolution = augmentedMap.info.resolution;
        int mapWidth = augmentedMap.info.width;

        //
        //If use-laser, then set as occupied the corresponding cells
        if(useLaser)
        {
                cout << "\033[1;37m     MvnPln.->Merging laser scan with occupancy grid.\033[0m" << endl;
                float robotX, robotY, robotTheta;
                float angle, laserX, laserY;
                int idx;
                TakeshiKnowledge::getRobotPose(robotX, robotY, robotTheta);
                for(int i=0; i < lastLaserScan.ranges.size(); i++)
                {
                        if(lastLaserScan.ranges[i] > 0.8 ||  lastLaserScan.ranges[i] < 0.3)
                                continue;
                        angle = lastLaserScan.angle_min + i*lastLaserScan.angle_increment;
                        if(fabs(angle) > 1.5708)
                                continue;
                        //For each range, cells are free between the robot and the end of the ray
                        /*
                              for(float dist=0; dist < lastLaserScan.ranges[i]; dist+=0.05)
                              {
                                  laserX = robotX + dist*cos(angle + robotTheta);
                                  laserY = robotY + dist*sin(angle + robotTheta);
                                  idx = (int)((laserY - mapOriginY)/mapResolution) * mapWidth + (int)((laserX - mapOriginX)/mapResolution);
                                  if(idx >= augmentedMap.data.size() || idx < 0)
                                      continue;
                                  augmentedMap.data[idx] = 0;
                              }*/
                        //Only the end of the ray is occupied
                        laserX = robotX + lastLaserScan.ranges[i]*cos(angle + robotTheta);
                        laserY = robotY + lastLaserScan.ranges[i]*sin(angle + robotTheta);
                        idx = (int)((laserY - mapOriginY)/mapResolution) * mapWidth + (int)((laserX - mapOriginX)/mapResolution);
                        if(idx >= augmentedMap.data.size() || idx < 0)
                                continue;
                        augmentedMap.data[idx] = 100;
                }
        }

        if(useKinect)
        {
                cout << "\033[1;37m     MvnPln.->Using cloud to augment map\033[0m" << endl;
                point_cloud_manager::GetRgbd srvGetRgbd;
                if(!this->cltGetRgbdWrtRobot.call(srvGetRgbd))
                {
                        cout << "\033[1;37m     MvnPln.->Cannot get point cloud :'(\033[0m" << endl;
                        return false;
                }
                pcl::PointCloud<pcl::PointXYZRGBA> cloudWrtRobot;
                pcl::PointCloud<pcl::PointXYZRGBA> cloudWrtMap;
                pcl::fromROSMsg(srvGetRgbd.response.point_cloud, cloudWrtRobot);
                tf::StampedTransform transformTf;
                tf_listener.lookupTransform("map", "base_link", ros::Time(0), transformTf);
                Eigen::Affine3d transformEigen;
                tf::transformTFToEigen(transformTf, transformEigen);
                pcl::transformPointCloud(cloudWrtRobot, cloudWrtMap, transformEigen);
                //It augments the map using only a rectangle in front of the robot
                float minX = 0.25;
                float maxX = 0.9;
                float minY = -0.35;
                float maxY = 0.35;
                int counter = 0;
                int idx;
                for(size_t i=0; i<cloudWrtRobot.points.size(); i++)
                {
                        pcl::PointXYZRGBA pR = cloudWrtRobot.points[i];
                        pcl::PointXYZRGBA pM = cloudWrtMap.points[i];
                        idx = (int)((pM.y - mapOriginY)/mapResolution)*mapWidth + (int)((pM.x - mapOriginX)/mapResolution);
                        if(pR.x > minX && pR.x < maxX && pR.y > minY && pR.y < maxY && idx < augmentedMap.data.size() && idx >= 0)
                        {
                                if(pR.z > 0.05 && pR.z < 1.0)
                                        if((augmentedMap.data[idx]+=3) > 100)
                                                augmentedMap.data[idx] = 100;
                                //else
                                //augmentedMap.data[idx] = 0;
                        }
                }
        }

        navig_msgs::PathFromMap srvPathFromMap;
        srvPathFromMap.request.map = augmentedMap;
        srvPathFromMap.request.start_pose.position.x = startX;
        srvPathFromMap.request.start_pose.position.y = startY;
        srvPathFromMap.request.goal_pose.position.x = goalX;
        srvPathFromMap.request.goal_pose.position.y = goalY;

        bool success;
        if((success = this->cltPathFromMapAStar.call(srvPathFromMap)))
                cout << "\033[1;37m     MvnPln.->Path calculated succesfully by path_calculator using A* using map and laser\033[0m" << endl;
        else
                cout << "\033[1;37m     MvnPln.->Cannot calculate path by path_calculator using A* using map and laser\033[0m" << endl;
        ros::spinOnce();

        path = srvPathFromMap.response.path;
        this->lastCalcPath = path;
        this->isLastPathPublished = false;
        return success;
}

void MvnPln::callbackRobotStop(const std_msgs::Empty::ConstPtr& msg)
{
        this->stopReceived = true;
}

bool MvnPln::callbackPlanPath(navig_msgs::PlanPath::Request& req, navig_msgs::PlanPath::Response& resp)
{
        TakeshiKnowledge::getKnownLocations(locations);
        //If Id is "", then, the metric values are used
        cout << "\033[1;37m     MvnPln.->Plan Path from \033[0m" << endl;
        if(req.start_location_id.compare("") == 0)
                std::cout << req.start_pose.position.x << " " << req.start_pose.position.y << " to ";
        else std::cout << "\"" << req.start_location_id << "\" to ";
        if(req.goal_location_id.compare("") == 0)
                std::cout << req.goal_pose.position.x << " " << req.goal_pose.position.y << std::endl;
        else std::cout << "\"" << req.goal_location_id << "\"" << std::endl;

        float startX, startY, goalX, goalY;
        if(req.start_location_id.compare("") != 0) //Then, start location should be a known location
        {
                if(this->locations.find(req.start_location_id) == this->locations.end())
                {
                        cout << "\033[1;37m     MvnPln.->Cannot calculate path from \"" << req.start_location_id << "\". It is not a known location. \033[0m" << endl;
                        return false;
                }
                startX = this->locations[req.start_location_id][0];
                startY = this->locations[req.start_location_id][1];
        }
        else //Then, start location is given in coordinates
        {
                startX = req.start_pose.position.x;
                startY = req.start_pose.position.y;
        }

        if(req.goal_location_id.compare("") != 0) //Then, goal location should be a known location
        {
                if(this->locations.find(req.goal_location_id) == this->locations.end())
                {
                        cout << "\033[1;37m     MvnPln.->Cannot calculate path to \"" << req.goal_location_id << "\". It is not a known location. \033[0m" << endl;
                        return false;
                }
                goalX = this->locations[req.goal_location_id][0];
                goalY = this->locations[req.goal_location_id][1];
        }
        else //Then, goal location is given in coordinates
        {
                goalX = req.goal_pose.position.x;
                goalY = req.goal_pose.position.y;
        }

        return this->planPath(startX, startY, goalX, goalY, resp.path);
}

void MvnPln::callbackClickedPoint(const geometry_msgs::PointStamped::ConstPtr& msg)
{
        cout << "\033[1;37m     MvnPln.->Clicked point: " << msg->point.x << " " << msg->point.y << "\033[0m" << endl;
}

void MvnPln::callbackGetCloseLoc(const std_msgs::String::ConstPtr& msg)
{
        TakeshiKnowledge::getKnownLocations(locations);
        if(this->locations.find(msg->data) == this->locations.end())
        {
                cout << "\033[1;37m     MvnPln.->Cannot get close to \"" << msg->data << "\". It is not a known location. \033[0m" << endl;
                return;
        }
        this->goalX = this->locations[msg->data][0];
        this->goalY = this->locations[msg->data][1];
        if(this->correctFinalAngle = this->locations[msg->data].size() > 2)
                this->goalAngle = this->locations[msg->data][2];
        this->newTask = true;

        cout << "\033[1;37m     MvnPln.->Received desired goal pose: " << msg->data << ": " << this->goalX << " " << this->goalY;
        if(this->correctFinalAngle)
                std::cout << " " << this->goalAngle;

        std_msgs::Bool msgGoalReached;
        msgGoalReached.data = false;
        this->pubGlobalGoalReached.publish(msgGoalReached);
        std::cout << "\033[0m" << endl;
}

void MvnPln::callbackGetCloseXYA(const std_msgs::Float32MultiArray::ConstPtr& msg)
{

        //If msg has two values, the robot will try to reach the goal point without correcting the final angle
        //If it has three values, the third one will be the final desired angle.
        if(msg->data.size() < 2)
        {
                cout << "\033[1;37m     MvnPln.->Cannot get close to given coordinates. At least two values are required.\033[0m" << endl;
                return;
        }
        this->goalX = msg->data[0];
        this->goalY = msg->data[1];
        if(this->correctFinalAngle = msg->data.size() > 2)
                this->goalAngle = msg->data[2];
        this->newTask = true;

        cout << "\033[1;37m     MvnPln.->Received desired goal pose: " << this->goalX << " " << this->goalY;
        if(this->correctFinalAngle)
                std::cout << " " << this->goalAngle;

        std_msgs::Bool msgGoalReached;
        msgGoalReached.data = false;
        this->pubGlobalGoalReached.publish(msgGoalReached);
        std::cout << "\033[0m" << endl;
}

void MvnPln::callbackLaserScan(const sensor_msgs::LaserScan::ConstPtr& msg)
{
        this->lastLaserScan = *msg;
}

void MvnPln::callbackCollisionRisk(const std_msgs::Bool::ConstPtr& msg)
{
        //std::cout << "JustinaNvigation.-<CollisionRisk: " << int(msg->data) << std::endl;
        //Collision signal is set to true in a flip-flop manner to ensure the correct sequence in the state machine
        //Whenever a collision is detected, the flag is kept until it is cleared in the state machine
        if(msg->data)
                this->collisionDetected = true;
}

void MvnPln::callbackCollisionPoint(const geometry_msgs::PointStamped::ConstPtr& msg)
{
        this->collisionPointX = msg->point.x;
        this->collisionPointY = msg->point.y;
}
