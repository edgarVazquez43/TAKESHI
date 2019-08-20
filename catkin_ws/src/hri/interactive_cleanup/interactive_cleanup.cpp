#include "interactive_clean_test.h"


//-f $(find knowledge)/navigation/known_locations_montreal.txt
interactiveCleaner::interactiveCleaner(ros::NodeHandle &nh)
{
        ros::NodeHandle nh_priv("~");
        std::string filepath;
        nh_priv.param<std::string>("known_locations_file",filepath,"known_locations.txt" );
        //loadKnownLocations(filepath);

        nh_=nh;
        skel_client = nh_.serviceClient<vision_msgs::GetSkeleton>("/get_skeleton");
        skeleton_enable = nh_.advertise<std_msgs::Bool>("/vision/skeleton_finder/enable_tracking",1);

        //to receive sigverses commands
        this->msgSubscriber =
                nh_.subscribe<interactive_cleanup::InteractiveCleanupMsg>("/interactive_cleanup/message/to_robot",
                                                                          100, &interactiveCleaner::messageCallback, this);
        this->msgPublisher =
                nh_.advertise<interactive_cleanup::InteractiveCleanupMsg>(
                        "/interactive_cleanup/message/to_moderator", 10);

        std::cout << "Interactive Cleanup object constructed" << '\n';

        interactive_cleanup::InteractiveCleanupMsg interactive_cleanup_msg;
        interactive_cleanup_msg.message = "This is a horrible test";
        msgPublisher.publish(interactive_cleanup_msg);
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


void interactiveCleaner::messageCallback(const interactive_cleanup::InteractiveCleanupMsg::ConstPtr &msg)
{
        ///This function receives the message and stores it on class.
        receivedMessage = msg->message;
        std::cout << "Callback called" << '\n';
        std::cout << receivedMessage << '\n';
}

void interactiveCleaner::sendMessage(std::string msg)
{
        interactive_cleanup::InteractiveCleanupMsg interactive_cleanup_msg;
        interactive_cleanup_msg.message = msg;
        msgPublisher.publish(interactive_cleanup_msg);
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

bool interactiveCleaner::setArm(std::vector<vision_msgs::SkeletonJoint> &arm)
{
        //Takes an arm find and trasnform to map coordinates, store in calls variable
        geometry_msgs::PointStamped p2, p1;
        bool convertSucces = convertJoints(arm[0],"map",p1);
        convertSucces = convertSucces && convertJoints(arm[1],"map",p2);
        if(convertSucces) {
                tf::pointStampedMsgToTF(p1,elbow);
                tf::pointStampedMsgToTF(p2,wrist);
        }
        return convertSucces;
}

geometry_msgs::Point interactiveCleaner::makePoint(float x, float y, float z)
{
        geometry_msgs::Point p;
        p.x=x;
        p.y=y;
        p.z=z;
        return p;
}

double interactiveCleaner::distanceToArm( geometry_msgs::Point gp0)
{
        //CAlculates distance to arm line via tf vector defined operations
        //geometry_msgs::Point gp0 = makePoint(x,y,z);
        tf::Vector3 p0;
        tf::pointMsgToTF(gp0,p0);
        tf::Vector3 p0elbow=p0-elbow;
        tf::Vector3 p0wrist=p0-wrist;
        tf::Vector3 elbowWrist=elbow-wrist;
        return p0elbow.cross(p0wrist).length2()/elbowWrist.length2();
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

bool interactiveCleaner::returnSkeletons(vision_msgs::Skeletons &skl)
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
                skeleton_enable.publish(msg);
                ros::spinOnce();
                ROS_ERROR("Timed Out!, failed to call %s", skeletonTopic.c_str());
                return false;
        }

        skl = *sharedPtr;
        msg.data=false;
        skeleton_enable.publish(msg);
        return true;
}

bool interactiveCleaner::getArmsByTopicOnMap(
        std::vector<geometry_msgs::PointStamped> &armLeftOnMap,
        std::vector<geometry_msgs::PointStamped> &armRightOnMap)
{
        //ask skeleton server to get the arms
        armLeftOnMap.clear();
        armRightOnMap.clear();
        std::vector<vision_msgs::SkeletonJoint> armLeft, armRight;
        bool success= false;
        if(getArmsByTopic(armLeft, armRight))
        {
                std::cout << "Arms got: " <<
                armLeft.size()<<" "<<armRight.size() <<'\n';
                success = convertArm(armLeft,armLeftOnMap) &&
                          convertArm(armRight,armRightOnMap);
        }
        return success;
}

bool interactiveCleaner::getArmsByTopic(
        std::vector<vision_msgs::SkeletonJoint> &armLeft,
        std::vector<vision_msgs::SkeletonJoint> &armRight)
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
                        vision_msgs::Skeleton closestSkeleton = esqueletos[closestSkeletonIdx];
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

                        if(armLeft.size()!=2)
                        {

                        }
                        if(armRight.size()!=2)
                        {

                                // std::cout << "Not enough joints to makean arm" << '\n';
                                //return false;
                        }

                }
        }
        else
        {
                ROS_ERROR("Failed to call topic");

        }
        return true;
}

void interactiveCleaner::askForSkeleton()
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
}

std::string interactiveCleaner::findPointedLocation(
        std::vector<geometry_msgs::PointStamped>  &armOnMap)
{
        //iterate over all known locations, find the one closest
        //to arm line, perpendicular disatance
        double minDist=100;
        std::string locationName("None");
        for (std::map<std::string,geometry_msgs::Point>::iterator it=locations.begin();
             it!=locations.end();
             ++it)
        {
                double dist=distanceToArm(armOnMap,it->second);
                //std::cout << "Distance to " << it->first << " is "<< dist <<'\n';
                if (dist<minDist)
                {
                        minDist=dist;
                        locationName=it->first;
                }
        }
        return locationName;
}

std::string interactiveCleaner::findPointedLocation()
{
        //iterate over all known locations, find the one closest
        //to arm line, perpendicular disatance
        double minDist=100;
        std::string locationName("None");
        for (std::map<std::string,geometry_msgs::Point>::iterator it=locations.begin();
             it!=locations.end();
             ++it)
        {
                double dist=distanceToArm(it->second);
                //std::cout << "Distance to " << it->first << " is "<< dist <<'\n';
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
