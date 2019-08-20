
 #include "interactive_clean_test.h"


//-f $(find knowledge)/navigation/known_locations_montreal.txt
interactiveCleaner::interactiveCleaner(ros::NodeHandle &nh)
{
        ros::NodeHandle nh_priv("~");
        std::string filepath;
        nh_priv.param<std::string>("known_locations_file",filepath,"known_locations.txt" );
        //loadKnownLocations(filepath);

        nh_=nh;
        //skel_client = nh_.serviceClient<vision_msgs::GetSkeleton>("/get_skeleton");
        skeleton_enable = nh_.advertise<std_msgs::Bool>("/vision/skeleton_finder/enable_tracking",1);
        followerEnable = nh_.advertise<std_msgs::Bool>("/hri/skeleton_follower/enable",1);

        //params
        //How much the robot has to turn in order to face an object on the floor
        //In theory should be M_PI*0.5 but this wokrs too
        nh_priv.param<float>("angle_adjustment",angleAdjustment,M_PI*0.8);
        //Angle of a valid arm if it is more than this the arm is poitning at something
        //Angle measure with xy plane normal.
        nh_priv.param<float>("arm_angle_valid",armAngleValid,60);
        //Distance adjustment
        //How much the robot has to move away from pointed location,
        //To not hit the object and to actually see it and grasp it.
        nh_priv.param<float>("distance_adjustment",distanceAdjustment,0.50);


}

void interactiveCleaner::printArm(std::vector<geometry_msgs::PointStamped> &arm)
{
        std::cout << "Arm points int" << arm[0].header.frame_id <<'\n';
        printf("Elbow [%f,%f,%f]\n", arm[0].point.x,arm[0].point.y,arm[0].point.z);
        printf("Wrist [%f,%f,%f]\n", arm[1].point.x,arm[1].point.y,arm[1].point.z);

}

geometry_msgs::Point interactiveCleaner::findPointedObj(
        std::vector<vision_msgs::VisionObject> objects,
        std::vector<geometry_msgs::PointStamped> &armOnMap)
{
        //Get centroid of closest detected object to arm line
        geometry_msgs::Point p;
        double minDist =100;
        int objIdx=0;
        for (int i = 0; i < objects.size(); i++)
        {
                p=objects[i].pose.position;
                double dist=distanceToArm(armOnMap,p);
                if (dist<minDist)
                {
                        minDist=dist;
                        objIdx=i;
                }

        }
        p=objects[objIdx].pose.position;
        std::cout << "Object pointed is" << objects[objIdx].id <<'\n';
        return p;
}


double interactiveCleaner::euclideanDistance(vision_msgs::Skeleton person)
{
        //get distance to hopefully nose or neck of the person
        double x = person.joints[0].position.x;
        double y = person.joints[0].position.y;
        double z = person.joints[0].position.z;
        return sqrt(x*x+y*y+z*z);
}


bool interactiveCleaner::convertJoints(
        vision_msgs::SkeletonJoint joint,
        std::string outLink,
        geometry_msgs::PointStamped &outJointStamped)
{
        //Take arm articulations and convert to a geometry_msgs::PointStamped
        //Generally in the map frame
        //Stamped required for transform
        geometry_msgs::PointStamped jointStamped;
        jointStamped.header.stamp = skelHeader.stamp;
        jointStamped.header.frame_id = skelHeader.frame_id;
        jointStamped.point.x=joint.position.x;
        jointStamped.point.y=joint.position.y;
        jointStamped.point.z=joint.position.z;
        //tf::TransformListener tlistener(nh_);
        try
        {
                tlistener.transformPoint(outLink,jointStamped,outJointStamped);
        }
        catch (tf::TransformException ex) {

                ROS_ERROR("%s",ex.what());
                return false;
                //ros::Duration(1.0).sleep();
        }

        return true;
}

bool interactiveCleaner::convertArm(
        std::vector<vision_msgs::SkeletonJoint> &arm,
        std::vector<geometry_msgs::PointStamped> &armOnMap)
{
        //Take arm articulations and convert to a geometry_msgs::PointStamped
        //Generally in the map frame
        //Stamped required for transform
        bool converted=false;
        //std::cout << "Arms on maps " << armOnMap.size() << '\n';
        for (size_t i = 0; i < arm.size(); i++)
        {
                geometry_msgs::PointStamped tmpArmOnMap;
                converted=convertJoints(arm[i],"/map",tmpArmOnMap);
                armOnMap.push_back(tmpArmOnMap);
        }
        return converted;
}


geometry_msgs::Point interactiveCleaner::makePoint(float x, float y, float z)
{
        geometry_msgs::Point p;
        p.x=x;
        p.y=y;
        p.z=z;
        return p;
}

double interactiveCleaner::distanceToArm(
        std::vector<geometry_msgs::PointStamped>  &armOnMap,
        geometry_msgs::Point gp0)
{
        //Calculates distance to arm line via tf vector defined operations
        //geometry_msgs::Point gp0 = makePoint(x,y,z);
        tf::Stamped<tf::Vector3> wrist, elbow;
        tf::pointStampedMsgToTF(armOnMap[0],elbow);
        tf::pointStampedMsgToTF(armOnMap[1],wrist);
        tf::Vector3 p0;
        tf::pointMsgToTF(gp0,p0);
        tf::Vector3 p0elbow=p0-elbow;
        tf::Vector3 p0wrist=p0-wrist;
        tf::Vector3 elbowWrist=elbow-wrist;
        return p0elbow.cross(p0wrist).length2()/elbowWrist.length2();
}

double interactiveCleaner::distanceToArmLoc(
        std::vector<geometry_msgs::PointStamped>  &armOnMap,
        geometry_msgs::Point gp0)
{
        //Calculates distance to arm line via tf vector defined operations
        //geometry_msgs::Point gp0 = makePoint(x,y,z);
        tf::Stamped<tf::Vector3> wrist, elbow;
        tf::pointStampedMsgToTF(armOnMap[0],elbow);
        tf::pointStampedMsgToTF(armOnMap[1],wrist);
        tf::Vector3 p0;
        tf::pointMsgToTF(gp0,p0);
        p0.setZ(.75);
        tf::Vector3 p0elbow=p0-elbow;
        tf::Vector3 p0wrist=p0-wrist;
        tf::Vector3 elbowWrist=elbow-wrist;
        return p0elbow.cross(p0wrist).length2()/elbowWrist.length2();
}

bool interactiveCleaner::returnSkeletonsEnable(vision_msgs::Skeletons &skl)
{
        //enable pose estimation
        std_msgs::Bool msg; msg.data=true;
        skeleton_enable.publish(msg);
        std::string skeletonTopic = "/vision/skeleton_finder/skeleton_recog";
        //The library asked for boost::sharedPtr
        boost::shared_ptr<vision_msgs::Skeletons const> sharedPtr;
        sharedPtr = ros::topic::waitForMessage<vision_msgs::Skeletons> (skeletonTopic, nh_, ros::Duration(10.0) );
        if (sharedPtr==NULL)
        {
                msg.data=false;
                //skeleton_enable.publish(msg);
                ros::spinOnce();
                ROS_ERROR("Timed Out!, failed to call %s", skeletonTopic.c_str());
                return false;
        }

        skl = *sharedPtr;
        msg.data=false;
        skeleton_enable.publish(msg);
        return true;
}

bool interactiveCleaner::returnSkeletons(vision_msgs::Skeletons &skl)
{
        //enable: wether enable and disable openpose node stimation
        std::string skeletonTopic = "/vision/skeleton_finder/skeleton_recog";
        //The library asked for boost::sharedPtr
        boost::shared_ptr<vision_msgs::Skeletons const> sharedPtr;
        sharedPtr = ros::topic::waitForMessage<vision_msgs::Skeletons> (skeletonTopic, nh_, ros::Duration(10.0) );
        if (sharedPtr==NULL)
        {
                ROS_ERROR("Timed Out!, failed to call %s", skeletonTopic.c_str());
                return false;
        }

        skl = *sharedPtr;
        return true;
}

void interactiveCleaner::startRoutine(bool enable)
{
        //enables both follower and skeleton tracker
        //enableFollower(enable);//Follow skel
        std::cout << "Follower enabled " << '\n';
        enableSkel(enable);
        return;
}

void interactiveCleaner::enableFollower(bool enable){
        std_msgs::Bool msg; msg.data=enable;
        followerEnable.publish(msg);
}

void interactiveCleaner::enableSkel(bool enable)
{
        std_msgs::Bool msg; msg.data=enable;
        skeleton_enable.publish(msg);
}

bool interactiveCleaner::getArmsByTopicOnMap(
        std::vector<geometry_msgs::PointStamped> &armLeftOnMap,
        std::vector<geometry_msgs::PointStamped> &armRightOnMap,
                vision_msgs::Skeleton &closestSkeleton)
{
        //ask skeleton server to get the arms
        std::vector<vision_msgs::SkeletonJoint> armLeft, armRight;
        bool success= false;
        if(getArmsByTopic(armLeft, armRight, closestSkeleton))
        {
                std::cout << "Arms got: " <<
                armLeft.size()<<" "<<armRight.size() <<'\n';
                armLeftOnMap.clear();
                armRightOnMap.clear();
                success = convertArm(armLeft,armLeftOnMap) &&
                          convertArm(armRight,armRightOnMap);
        }

        return success;
}

bool interactiveCleaner::getArmsByTopic(
        std::vector<vision_msgs::SkeletonJoint> &armLeft,
        std::vector<vision_msgs::SkeletonJoint> &armRight,
        vision_msgs::Skeleton &closestSkeleton)
{
        //ask skeleton server to get the arms
        //find closest person
        vision_msgs::Skeletons skels;
        std::vector<vision_msgs::Skeleton> esqueletos; //si se me acabo la img
        if(returnSkeletons(skels))
        {
                esqueletos = skels.skeletons;
                std::cout << "Got:";
                std::cout << esqueletos.size() << " skeletons"<<'\n';
                skelHeader = skels.header; //Both skeletons came in base_link frame
                std::cout << "Reference frame " <<skels.header.frame_id<<'\n';
                if (esqueletos.size() > 0)
                {
                        int closestSkeletonIdx =0;
                        double minDist = euclideanDistance(esqueletos[closestSkeletonIdx]);
                        //find skeleton closer to camera
                        //TODO add option to default to first
                        for (int j = 0; j < esqueletos.size(); j++)
                        {
                                double personDistance = euclideanDistance(esqueletos[j]);

                                if (minDist>personDistance)
                                {
                                        minDist=personDistance;
                                        closestSkeletonIdx = j;
                                }
                        }
                        //find all joint and save them if they are shoulder or writst
                        /*vision_msgs::Skeleton */closestSkeleton = esqueletos[closestSkeletonIdx];
                        if (closestSkeleton.joints.size()<2) {
                                std::cout << "Skeleton does not have enough joints skipping" << '\n';
                                return false;
                        }
                        for (int i = 0; i < closestSkeleton.joints.size(); i++)
                        {
                                std::string jointName = closestSkeleton.joints[i].name_joint.data;
                                if (jointName.compare("right_elbow")==0)
                                {
                                        armRight.push_back(closestSkeleton.joints[i]);
                                }
                                if(!jointName.compare("right_wrist"))
                                {
                                        armRight.push_back(closestSkeleton.joints[i]);
                                }
                                if (!jointName.compare("left_elbow"))
                                {
                                        armLeft.push_back(closestSkeleton.joints[i]);
                                }
                                if(!jointName.compare("left_wrist"))
                                {
                                        armLeft.push_back(closestSkeleton.joints[i]);
                                }

                        }
                        // std::cout << "Closest person is " << closestSkeletonIdx <<'\n';
                        // std::cout << "ArmL size " << armLeft.size()<<'\n';
                        // std::cout << "ArmR size " << armRight.size()<<'\n';

                        if(armLeft.size()<2)
                        {
                                std::cout << "Not enough joints to make right arm" << '\n';
                                return false;
                        }
                        if(armRight.size()<2)
                        {
                                std::cout << "Not enough joints to make right arm" << '\n';
                                return false;
                        }

                }
        }
        else
        {
                ROS_ERROR("Failed to call topic");
                return false;

        }
        return true;
}

/*void interactiveCleaner::askForSkeleton()
{
        //ask skeleton server to get the arms
        vision_msgs::GetSkeleton skel;
        std::vector<vision_msgs::Skeleton> esqueletos; //si se me acabo la img
        if(skel_client.call(skel))
        {
                esqueletos = skel.response.skeletons.skeletons;
                std::cout << "Got:";
                std::cout << esqueletos.size() << '\n';
                if (esqueletos.size() > 0)
                {
                        for (int j = 0; j < esqueletos.size(); j++)
                        {
                                std::cout << "Skeleton: " << j << '\n';
                                for (size_t i = 0; i < esqueletos[j].joints.size(); i++)
                                {
                                        std::cout << "\tJoint: " << esqueletos[j].joints[i].name_joint  << '\n';
                                }
                        }
                }
        }
        else
        {
                ROS_ERROR("Failed to call service get_skeleton");

        }
        return;
}*/

double interactiveCleaner::distance(vision_msgs::Skeleton &closestSkeleton,
    geometry_msgs::Point gp0){

        //get distance to hopefully nose or neck of the person
        double x = closestSkeleton.joints[0].position.x;
        double y = closestSkeleton.joints[0].position.y;
        double z = closestSkeleton.joints[0].position.z;


        return sqrt((x-gp0.x)*(x-gp0.x) + (y-gp0.y)*(y-gp0.y) + (z-gp0.z)*(z-gp0.z));
}

double interactiveCleaner::distanceXY(vision_msgs::Skeleton &closestSkeleton,
    geometry_msgs::Point gp0){

        //get distance to hopefully nose or neck of the person
        double x = closestSkeleton.joints[0].position.x;
        double y = closestSkeleton.joints[0].position.y;
        //double z = closestSkeleton.joints[0].position.z;

    std::cout << "\tskeleton X" << closestSkeleton.joints[0].position.x << '\n';
            std::cout << "\tskeleton Y" << closestSkeleton.joints[0].position.y << '\n';

        return sqrt((x-gp0.x)*(x-gp0.x) + (y-gp0.y)*(y-gp0.y));
}

std::string interactiveCleaner::findPointedLocation(
        std::vector<geometry_msgs::PointStamped>  &armOnMap,
                vision_msgs::Skeleton &closestSkeleton,
                bool find_near_locations)
{
        //iterate over all known locations, find the one closest
        //to arm line, perpendicular disatance
        double minDist=100;
        std::string locationName("None");
        for (std::map<std::string,geometry_msgs::Point>::iterator it=locations.begin();
             it!=locations.end();
             ++it)
        {
            if(strcmp((it->first).c_str(),"carry_luggage") == 0){
                continue;
            }
                double dist=distanceToArmLoc(armOnMap,it->second);
                std::cout << "Distance to " << it->first << " is "<< dist <<'\n';
                if (dist<minDist)
                {
                        minDist=dist;
                        locationName=it->first;
                }
        }
        return locationName;
}


bool interactiveCleaner::loadKnownLocations(std::string path)
{
        std::cout << "Loading known locations from " << path << std::endl;
        std::ifstream file(path.c_str());
        if (!file.is_open()) {
                ROS_ERROR("File  %s cannot be opened", path.c_str());
        }
        std::string line;
        locations.clear();
        while (std::getline(file,line)) {
                std::istringstream iss(line);
                //float x, y, th;
                geometry_msgs::Point loc;
                std::string locName;
                if (!(iss >>locName>> loc.x >> loc.y)) // >>loc.th))
                {
                        std::cout << "Parsing Error" << '\n';
                        continue;
                }
                loc.z=0;
                std::pair<std::string, geometry_msgs::Point> tmp(locName,loc);
                locations.insert(tmp);
        }
        for (std::map<std::string,geometry_msgs::Point>::iterator it=locations.begin(); it!=locations.end(); ++it)
                std::cout << it->first << " => " << it->second.x <<" "<< it->second.y<< " "<<it->second.z<< '\n';
        return true;

}

bool interactiveCleaner::setKnownLocations(std::map<std::string, std::vector<float> > &locs)
{
        for (std::map<std::string,std::vector<float> >::iterator it=locs.begin(); it!=locs.end(); ++it)
        {
                geometry_msgs::Point l=              makePoint(it->second[0],it->second[1],0);
                std::string name(it->first);
                std::pair<std::string,geometry_msgs::Point> tmp(name,l);
                locations.insert(tmp);
        }
        std::cout << "Known Locations: " << '\n';
        std::map<std::string,geometry_msgs::Point>::iterator lt;
        for (lt=locations.begin(); lt!=locations.end(); ++lt)
        {
                std::cout << lt->first << " => " << lt->second.x <<" "<< lt->second.y<< " "<<lt->second.z<< '\n';
        }
}

double interactiveCleaner::angleOfArm(std::vector<geometry_msgs::PointStamped> &armOnMap)
{
        //Calculates angle of arm respect the xy plane
        //Expects arm  on map coordinates
        geometry_msgs::Point line_vector;
        line_vector.x= armOnMap[1].point.x -armOnMap[0].point.x;
        line_vector.y= armOnMap[1].point.y -armOnMap[0].point.y;
        line_vector.z= armOnMap[1].point.z -armOnMap[0].point.z;
        //get point product
        double sin_b = line_vector.z/(norm(line_vector));
        return asin(sin_b); //-M_PI/2;
}

double interactiveCleaner::norm(geometry_msgs::Point p){
        return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

geometry_msgs::Point interactiveCleaner::floorIntersect(std::vector<geometry_msgs::PointStamped> &armOnMap)
{
        //Given a map check where arm line intersect with floor
        geometry_msgs::Point line_vector, orig, inter;
        line_vector.x= armOnMap[1].point.x -armOnMap[0].point.x;
        line_vector.y= armOnMap[1].point.y -armOnMap[0].point.y;
        line_vector.z= armOnMap[1].point.z -armOnMap[0].point.z;
        orig=armOnMap[0].point;
        inter.x=-line_vector.x/line_vector.z*orig.z+orig.x;
        inter.y=-line_vector.y/line_vector.z*orig.z+orig.y;
        inter.z=0;
        return inter;

}

geometry_msgs::Pose2D interactiveCleaner::floorLocation(std::vector<geometry_msgs::PointStamped> &armOnMap)
{
        geometry_msgs::Point floorPoint = floorIntersect(armOnMap);
        geometry_msgs::Point vectorFloor;
        vectorFloor.x= armOnMap[1].point.x -armOnMap[0].point.x;
        vectorFloor.y= armOnMap[1].point.y -armOnMap[0].point.y;
        vectorFloor.z= 0;
        double vectorFloorNorm=norm(vectorFloor);
        vectorFloor.x= vectorFloor.x/vectorFloorNorm;
        vectorFloor.y= vectorFloor.y/vectorFloorNorm;
        geometry_msgs::Pose2D floorLoc;
        const float t = distanceAdjustment; //safety
        floorLoc.x = floorPoint.x+t*vectorFloor.x;
        floorLoc.y = floorPoint.y+t*vectorFloor.y;
        floorLoc.theta = atan2(vectorFloor.y,vectorFloor.x)-angleAdjustment;
        //compensación hardcodeada en teoria angleAdjustment deberia ser 0.5*M_PI
        return floorLoc;
}


bool interactiveCleaner::validateArms(std::vector<geometry_msgs::PointStamped>  &armLeft,
                                      std::vector<geometry_msgs::PointStamped>  &armRight,
                                      std::vector<geometry_msgs::PointStamped> &validArm)
{
        //Receives two arms, check wich is not poiinting to the floor
        double leftAngle=angleOfArm(armLeft);
        double rightAngle=angleOfArm(armRight);
        std::cout << "Right arm angle is: " << rightAngle * 180/M_PI <<'\n';
        std::cout << "Left arm angle is: " << leftAngle * 180/M_PI <<'\n';
        if(fabs(rightAngle)<= armAngleValid * M_PI/180)
        {
                std::cout << "\t Right selected" << '\n';
                validArm=armRight;
                return true;
        }
        else if(fabs(leftAngle)<= armAngleValid * M_PI/180)
        {
                std::cout << "\t Left selected" << '\n';
                validArm=armLeft;
                return true;
        }
        return false;
}
