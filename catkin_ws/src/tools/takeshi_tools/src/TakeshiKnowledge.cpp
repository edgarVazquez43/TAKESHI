//Edd-2 was here
#include "takeshi_tools/TakeshiKnowledge.h"

tf::TransformListener * TakeshiKnowledge::tf_listener;

ros::Subscriber * TakeshiKnowledge::subUpdateKnowmLoc;
ros::Subscriber * TakeshiKnowledge::subInitKnowmLoc;
ros::Subscriber TakeshiKnowledge::subStopButton;

ros::Publisher * TakeshiKnowledge::pubEnableEdit;
ros::Publisher * TakeshiKnowledge::pubLoadFromFile;
ros::Publisher * TakeshiKnowledge::pubDeleteKnownLoc;
ros::Publisher * TakeshiKnowledge::pubSaveInFile;

ros::ServiceClient * TakeshiKnowledge::cliKnownLoc;
ros::ServiceClient * TakeshiKnowledge::cliAddUpKnownLoc;
ros::ServiceClient * TakeshiKnowledge::cliGetPredQues;
ros::ServiceClient * TakeshiKnowledge::cliAddUpdateObjectViz;
ros::ServiceClient * TakeshiKnowledge::cliIsInArea;

using namespace std;
bool TakeshiKnowledge::is_node_set = false;
bool TakeshiKnowledge::is_stopped = false;
bool TakeshiKnowledge::updateKnownLoc = false;
bool TakeshiKnowledge::initKnownLoc = false;

TakeshiKnowledge::~TakeshiKnowledge(){
  delete cliKnownLoc;
  delete cliAddUpKnownLoc;
  delete subUpdateKnowmLoc;
  delete subInitKnowmLoc;
  delete pubEnableEdit;
  delete pubLoadFromFile;
  delete pubDeleteKnownLoc;
  delete pubSaveInFile;
  delete cliAddUpdateObjectViz;
  delete cliIsInArea;
  delete tf_listener;
}    


bool TakeshiKnowledge::setNodeHandle(ros::NodeHandle* nh) {
        if(TakeshiKnowledge::is_node_set)
                return true;
        if(nh == 0)
                return false;
        cout << "\033[1;35m     TakeshiKnowledge.->Setting ros node...\033[0m" << endl;
        tf_listener = new tf::TransformListener();

	//Subscriber declarations
	subUpdateKnowmLoc = new ros::Subscriber(
		nh->subscribe("/knowledge/update_location_markers", 1, &TakeshiKnowledge::callBackUpdateKnownLoc));
	subInitKnowmLoc = new ros::Subscriber(
		nh->subscribe("/knowledge/init_location_markers", 1, &TakeshiKnowledge::callBackInitKnownLoc));
	TakeshiKnowledge::subStopButton = nh->subscribe(
		"/hsrb/runstop_button", 1,&TakeshiKnowledge::callbackStop_AndSaveLocation);
	
	cout << "\033[1;35m     TakeshiKnowledge.-> Subscribers has been declared... \033[0m" << endl;
	//Publishers declarations
	pubEnableEdit = new ros::Publisher(
		nh->advertise<std_msgs::Bool>("/knowledge/edit_known_loc", 1));
	pubLoadFromFile = new ros::Publisher(
		nh->advertise<std_msgs::String>("/knowledge/load_from_file", 1));
	pubDeleteKnownLoc = new ros::Publisher(
		nh->advertise<std_msgs::String>("/knowledge/delete_known_locations", 1));
	pubSaveInFile = new ros::Publisher(
		nh->advertise<std_msgs::String>("/knowledge/save_in_file", 1));
	
	cout << "\033[1;35m     TakeshiKnowledge.-> Publishers has been declared... \033[0m" << endl;
	//Client Services declarations
	cliKnownLoc = new ros::ServiceClient(
		nh->serviceClient<knowledge_msgs::KnownLocations>(
		    "/knowledge/known_locations"));
	cliAddUpKnownLoc =  new ros::ServiceClient(
	        nh->serviceClient<knowledge_msgs::AddUpdateKnownLoc>(
		    "/knowledge/add_update_known_locations"));
	cliGetPredQues = new ros::ServiceClient(
		nh->serviceClient<knowledge_msgs::GetPredefinedQuestions>(
		    "/knowledge/get_predefined_questions"));
	cliAddUpdateObjectViz = new ros::ServiceClient(
		nh->serviceClient<env_msgs::AddUpdateObjectViz>(
		    "/knowledge/object_description")); 
	cliIsInArea = new ros::ServiceClient(
		nh->serviceClient<knowledge_msgs::IsPointInKnownArea>(
		    "/knowledge/is_point_in_area"));

	cout << "\033[1;35m     TakeshiKnowledge.-> Client Services has been declared... \033[0m" << endl;
	tf_listener->waitForTransform("map", "base_link", ros::Time(0), ros::Duration(5.0));
        return true;
}

void TakeshiKnowledge::callBackUpdateKnownLoc(const std_msgs::Bool::ConstPtr updateKnownLoc)
{
  TakeshiKnowledge::updateKnownLoc = updateKnownLoc->data;
}

void TakeshiKnowledge::callBackInitKnownLoc(const std_msgs::Bool::ConstPtr initKnownLoc)
{
  TakeshiKnowledge::initKnownLoc = initKnownLoc->data;
} 

void TakeshiKnowledge::callbackStop_AndSaveLocation(const std_msgs::Bool::ConstPtr& msg)
{

    if (msg->data==true && TakeshiKnowledge::is_stopped ==false)
    {
        TakeshiKnowledge::addUpdateKnownLoc("last_know_location");
	//This is not fine  :(
        TakeshiKnowledge::saveInFile("/home/adrian/Software/HSR_PUMAS/catkin_ws/src/planning/knowledge/navigation/biorobotica2019-demoFebrero.txt");
        TakeshiKnowledge::is_stopped = true;

    }

}

void TakeshiKnowledge::getRobotPose(float &currentX, float &currentY, float &currentTheta){
        //would it kill you to using poses instead of every compoenent?
        tf::StampedTransform transform;
        tf::Quaternion q;
        tf_listener->lookupTransform("map", "base_link", ros::Time(0), transform);
        q = transform.getRotation();
        currentX = transform.getOrigin().x();
        currentY = transform.getOrigin().y();
        currentTheta = atan2((float)q.z(), (float)q.w()) * 2;
}

void TakeshiKnowledge::getKnownLocations(
        std::map<std::string, std::vector<float> >& known_locations) {
        known_locations.clear();
        knowledge_msgs::KnownLocations srv;
        if (cliKnownLoc->call(srv)) {
                for (std::vector<knowledge_msgs::MapKnownLocation>::iterator it =
                             srv.response.locations.begin();
                     it != srv.response.locations.end(); ++it) {
                        known_locations.insert(
                                std::pair<std::string, std::vector<float> >(it->name,
                                                                            it->value));
                }
        } else {
                ROS_ERROR("Failed to call service known_locations");
        }
}

void TakeshiKnowledge::getKnownLocation(std::string location, float &x, float& y, float &a){
    std::map<std::string, std::vector<float> > locations;
    TakeshiKnowledge::getKnownLocations(locations);
    std::map<std::string, std::vector<float> >::iterator it;
    it = locations.find(location);
    if(it != locations.end()){
        std::vector<float> components = it->second;
        x = components[0];
        y = components[1];
        if(components.size() == 3)
            a = components[2];
    }
}

bool TakeshiKnowledge::existKnownLocation(std::string location){
        std::map<std::string, std::vector<float> > locations;
        TakeshiKnowledge::getKnownLocations(locations);
        std::map<std::string, std::vector<float> >::iterator it;
        it = locations.find(location);
        if(it == locations.end())
                return false;
        return true;
}


//Test is needed
void TakeshiKnowledge::getUpdateKnownLoc(bool& updateKnownLoc){
  updateKnownLoc = TakeshiKnowledge::updateKnownLoc;
  TakeshiKnowledge::updateKnownLoc = false;
}

//Test is needed
void TakeshiKnowledge::getInitKnownLoc(bool& initKnownLoc){
  initKnownLoc = TakeshiKnowledge::initKnownLoc;
  TakeshiKnowledge::initKnownLoc = false;
}

//Test is needed
void TakeshiKnowledge::enableInteractiveUpdate(bool enable){
  std_msgs::Bool msg;
  msg.data = enable;
  pubEnableEdit->publish(msg);
}

void TakeshiKnowledge::loadFromFile(const std::string filePath){
  std_msgs::String msg;
  msg.data = filePath;
  pubLoadFromFile->publish(msg);
}




void TakeshiKnowledge::saveInFile(const std::string filePath){
    std_msgs::String msg;
    msg.data = filePath;
    pubSaveInFile->publish(msg);
}

void TakeshiKnowledge::addUpdateKnownLoc(std::string name, std::vector<float> values){
  knowledge_msgs::AddUpdateKnownLoc srv;
  srv.request.loc.name = name;
  srv.request.loc.value = values;
  if (cliAddUpKnownLoc->call(srv)) {
  } else {
    ROS_ERROR("Failed to call service known_locations");
  }
}

void TakeshiKnowledge::addUpdateKnownLoc(std::string name){
        knowledge_msgs::AddUpdateKnownLoc srv;
        std::vector<float> values;
        float x, y, theta;
        TakeshiKnowledge::getRobotPose(x, y, theta);
        cout << "\033[1;35m     TakeshiKnowledge.->Get robot pose x:" << x << " y: " << y << " theta: " << theta << " \033[0m" << endl;
        srv.request.loc.name = name;
        values.push_back(x);
        values.push_back(y);
        values.push_back(theta);
        srv.request.loc.value = values;
        if (cliAddUpKnownLoc->call(srv)) {
        } else {
                ROS_ERROR("Failed to call service known_locations");
        }
}

void TakeshiKnowledge::addUpdateKnownLoc(std::string name, float ori){
    knowledge_msgs::AddUpdateKnownLoc srv;
    std::vector<float> values;
    float x, y, theta;
    getRobotPose(x, y, theta);
    values.push_back(x);
    values.push_back(y);
    values.push_back(ori);
    srv.request.loc.name = name;
    srv.request.loc.value = values;
    if (cliAddUpKnownLoc->call(srv)) {
    } else {
        ROS_ERROR("Failed to call service known_locations");
    }
}
void TakeshiKnowledge::addUpdateKnownLoc(std::string name, float x, float y){
        knowledge_msgs::AddUpdateKnownLoc srv;
        std::vector<float> values;
        values.push_back(x);
        values.push_back(y);
        srv.request.loc.name = name;
        srv.request.loc.value = values;
        if (cliAddUpKnownLoc->call(srv)) {
        } else {
                ROS_ERROR("Failed to call service known_locations");
        }
}

void TakeshiKnowledge::addUpdateKnownLoc(std::string name, float x, float y,float th){
        knowledge_msgs::AddUpdateKnownLoc srv;
        std::vector<float> values;
        values.push_back(x);
        values.push_back(y);
        values.push_back(th);
        srv.request.loc.name = name;
        srv.request.loc.value = values;
        if (cliAddUpKnownLoc->call(srv)) {
        } else {
                ROS_ERROR("Failed to call service known_locations");
        }
}


void TakeshiKnowledge::deleteKnownLoc(const std::string name){
        std_msgs::String msg;
        msg.data = name;
        pubDeleteKnownLoc->publish(msg);
}


void TakeshiKnowledge::getPredQuestions(std::vector<std::string> &questions){
        knowledge_msgs::GetPredefinedQuestions srv;
        if (cliGetPredQues->call(srv)) {
                for(int i = 0; i < srv.response.predefinedQuestions.size(); i++) {
                        questions.push_back(srv.response.predefinedQuestions[i].question);
                        cout << srv.response.predefinedQuestions[i].question << endl;
                }
        } else {
                ROS_ERROR("Failed to call service known_locations");
        }
}

void TakeshiKnowledge::getPredQuestions(std::map<std::string, std::string> &predQues){
        knowledge_msgs::GetPredefinedQuestions srv;
        if (cliGetPredQues->call(srv)) {
                for(int i = 0; i < srv.response.predefinedQuestions.size(); i++) {
                        predQues[srv.response.predefinedQuestions[i].question] = srv.response.predefinedQuestions[i].answer;
                }
        } else {
                ROS_ERROR("Failed to call service known_locations");
        }
}

bool TakeshiKnowledge::comparePredQuestion(std::string question, std::string &answer){
        std::map<std::string, std::string> predQues;
        getPredQuestions(predQues);
        boost::replace_all(question, ",", " ");
        boost::replace_all(question, ".", " ");
        cout << "\033[1;35m     TakeshiKnowledge.->Ask answer:" << question <<" \033[0m" << endl;
        /*std::replace(question.begin(), question.end(), "," , " ");
           std::replace(question.begin(), question.end(), "," , ".");*/
        std::map<std::string, std::string>::iterator quesFound = predQues.find(question);
        if(quesFound == predQues.end())
                return false;
        answer = quesFound->second;
        cout << "\033[1;35m     TakeshiKnowledge.->Answer:" << answer <<" \033[0m" << endl;
        return true;
}

void TakeshiKnowledge::addUpdateObjectViz(std::string id,
					  float minX, float minY, float minZ,
					  float maxX, float maxY, float maxZ,
					  float centroidX, float centroidY, float centroidZ,
					  float colorR, float colorG, float colorB,
					  std::string frame_original, std::string frame_goal)
{
  env_msgs::ObjectViz objectViz;
  objectViz.id.data = id;
  objectViz.frame_original.data = frame_original;
  objectViz.frame_goal.data = frame_goal;
  objectViz.centroid.x = centroidX;
  objectViz.centroid.y = centroidY;
  objectViz.centroid.z = centroidZ;
  objectViz.minPoint.x = minX;
  objectViz.minPoint.y = minY;
  objectViz.minPoint.z = minZ;
  objectViz.maxPoint.x = maxX;
  objectViz.maxPoint.y = maxY;
  objectViz.maxPoint.z = maxZ;
  objectViz.color.x = colorR;
  objectViz.color.y = colorG;
  objectViz.color.z = colorB;
  env_msgs::AddUpdateObjectViz srv;
  srv.request.object = objectViz;
  if (cliAddUpdateObjectViz->call(srv)) {
  } else
    ROS_ERROR("Failed to call add object viz");
}

bool TakeshiKnowledge::isPointInKnownArea(float x, float y, std::string location){
    knowledge_msgs::IsPointInKnownArea srv;
    geometry_msgs::Point32 data;
    data.x = x;
    data.y = y;
    data.z = 0.0f;
    srv.request.location = location;
    srv.request.point = data;
    if (cliIsInArea->call(srv)) {
        return srv.response.isInLocation;
    } else 
        ROS_ERROR("Failed to call service known_locations");
    return false;
}



bool TakeshiKnowledge::saveObjToLTM(std::string name,std::string path,  float x, float y, float th)
{
        //Store object pose: x y theta to file.
        //Stores in disk directly without using ltm
        std::ofstream objFile(path,ios::app);
        if (objFile.is_open())
        {
                objFile << name << " " << x << " " << y << " " << th<< "\n";
        }
        else
        {
                objFile.close();
                return false;
        }
        objFile.close();
        return true;
}

bool TakeshiKnowledge::saveObjToLTM(std::string name,  float x, float y, float theta)
{
        //Store object pose: x y theta to file.
        //Uses LTM node
        knowledge_msgs::AddUpdateKnownLoc srv;
	cout << "\033[1;35m     TakeshiKnowledge.->Get objects location is not implemented Yet... \033[0m" << endl;
	/*
        std::vector<float> values;
        cout << "\033[1;35m     TakeshiKnowledge.->Get robot pose x:" << x << " y: " << y << " theta: " << theta << " \033[0m" << endl;
        srv.request.loc.name = name;
        values.push_back(x);
        values.push_back(y);
        values.push_back(theta);

        srv.request.loc.value = values;
        if (cliAddUpKnownObjLoc->call(srv)) {
        } else {
                ROS_ERROR("Failed to call service known_locations");
        }
	*/
	ROS_ERROR("Failed to call service known_objects_locations");
	return false;
}

bool TakeshiKnowledge::getKnownObjectsLocation(
        std::map<std::string, std::vector<float> >& locations)
{
        //Call known object locations server for locations of known objects
        locations.clear();
	cout << "\033[1;35m     TakeshiKnowledge.->Get objects location is not implemented Yet... \033[0m" << endl;
	/*
	knowledge_msgs::KnownLocations srv;
        if (cliKnownObjLoc->call(srv)) {
                std::vector<knowledge_msgs::MapKnownLocation>::iterator it;
                for ( it=srv.response.locations.begin();
                      it != srv.response.locations.end();
                      ++it)
                {
                        std::pair<std::string, std::vector<float> > tmp(it->name,
                                                                        it->value);
                        locations.insert(tmp);
                }
        } else {
                ROS_ERROR("Failed to call service known_objects_locations");
                return false;
        }
        return true;
	*/
	ROS_ERROR("Failed to call service known_objects_locations");
	return false;
}

bool TakeshiKnowledge::getKnownObjectsLocationFromFile(
        std::string pth,
        std::map<std::string, std::vector<float> >& locations)
{
        //This should also be able to work without the ltm node
        //Will simply read file on from pth.
        //Wonder why we have a server...
        std::cout << "Loading known object locations from 4" << pth   << std::endl;
        std::ifstream file(pth.c_str());
        if (!file.is_open()) {
                std::cout << "Cloud not open file" << '\n';
                file.close();
                return false;
        }
        std::string line;
        locations.clear();
        while (std::getline(file,line)) {
                std::istringstream iss(line);
                //float x, y, th;
                std::vector<float> loc(5);
                std::string locName;
                if (!(iss >>locName>> loc[0] >> loc[1] >>loc[2] >> loc[3] >> loc[4]))
                {
                        std::cout << "Parsing Error" << '\n';
                        continue;
                }
                std::pair<std::string, std::vector<float> > tmp(locName,loc);
                locations.insert(tmp);
        }
        file.close();
        return true;

}

bool TakeshiKnowledge::getKnownObjectsLocationFromFile(
        std::string pth,
        std::map<std::string, std::string >& locations)
{
        //This should also be able to work without the ltm node
        //Will simply read file on from pth.
        //Wonder why we have a server...
        std::cout << "Loading known object locations from 3" << pth   << std::endl;
        std::ifstream file(pth.c_str());
        if (!file.is_open()) {
                std::cout << "Cloud not open file" << '\n';
                file.close();
                return false;
        }
        std::string line;
        locations.clear();
        while (std::getline(file,line)) {
                std::istringstream iss(line);
                //float x, y, th;
                std::string objName, locName;
                if (!(iss >> objName >> locName))
                {
                        std::cout << "Parsing Error" << '\n';
                        continue;
                }
                std::pair<std::string, std::string > tmp(objName,locName);
                locations.insert(tmp);
        }
        file.close();
        return true;

}

bool TakeshiKnowledge::getKnownObjectsLocationFromFile(
        std::string pth,
        std::map<std::string, loc3D >& locations)
{
        //This should also be able to work without the ltm node
        //Will simply read file on from pth.
        //Wonder why we have a server...
        std::cout << "Loading known object locations from 1" << pth   << std::endl;
        std::ifstream file(pth.c_str());
        if (!file.is_open()) {
                std::cout << "Cloud not open file" << '\n';
                file.close();
                return false;
        }
        std::string line;
        locations.clear();
        while (std::getline(file,line)) {
                std::istringstream iss(line);
                //float x, y, th;
                std::string objName, locName;
                loc3D loc;
                float z;
                if (!(iss >> objName >> loc.name>> loc.height))
                {
                        std::cout << "Parsing Error" << '\n';
                        continue;
                }
       
                std::pair<std::string, loc3D > tmp(objName,loc);
                locations.insert(tmp);
        }
        file.close();
        return true;

}

bool TakeshiKnowledge::getKnownPosesFromFile(
        std::string pth,
        std::map<std::string, joints >& poses)
{
        //This should also be able to work without the ltm node
        //Will simply read file on from pth.
        //Wonder why we have a server...
        std::cout << "Loading known object poses from 2" << pth   << std::endl;
        std::ifstream file(pth.c_str());
        if (!file.is_open()) {
                std::cout << "Cloud not open file" << '\n';
                file.close();
                return false;
        }
        std::string line;
        poses.clear();
        while (std::getline(file,line)) {
                std::istringstream iss(line);
                //float x, y, th;
                std::string objName;
                joints posee(5);

                if (!(iss >> objName >> posee[0]>>
                      posee[1]>>posee[2]
                      >>posee[3] >>posee[4]))
                {
                        std::cout << "Parsing Error" << '\n';
                        continue;
                }
                for(int i=0; i< posee.size();i++)
                    cout << posee[i] << endl;
                std::pair<std::string, joints > tmp(objName,posee);
                poses.insert(tmp);
        }
        file.close();
        return true;

}

void TakeshiKnowledge::saveNameUnknownObject(std::string objectName, std::string objectPath){
        ofstream fileObject;
        fileObject.open(objectPath);
        fileObject << objectName << endl;
        fileObject.close();
}

bool TakeshiKnowledge::loadNameUnknownObject(std::string& objectName, std::string objectPath){
        std::ifstream file(objectPath.c_str());

        if (!file.is_open()) {
                std::cout << "Could not open file" << '\n';
                file.close();
                return false;
        }

        std::getline(file,objectName);
        return true;
}




