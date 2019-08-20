#include "ros/ros.h"
#include "takeshi_tools/TakeshiKnowledge.h"
//src/planning/knowledge/navigation/known_object_locations.txt

//train obj
//detect
//store in ltm
int main(int argc, char *argv[]) {
        std::cout << "\033[1;34m Initializing ltm test for known objects \033[0m" << '\n';
        if (argc<3) {
                std::cout << "Ooops! failed to provide filename" << '\n';
        }
        std::string name(argv[2]);
        std::string pth(argv[1]);

        ros::init(argc, argv, "ltm_obj_test");
        ros::NodeHandle nh;
        TakeshiKnowledge::setNodeHandle(&nh);

        if (!TakeshiKnowledge::saveObjToLTM(name,pth,10,10,0.5)) {
          std::cout << "Failed to write" << '\n';
        }
        std::map<std::string, std::vector<float> > v;
        if (  TakeshiKnowledge::getKnownObjectsLocation(v)) {
          std::cout << "Objs by server" << '\n';
                for (std::map<std::string,std::vector<float> >::iterator it=v.begin(); it!=v.end(); ++it)
                {
                        std::cout << it->first << " => "
                                  << it->second[0] <<" "
                                  << it->second[1]<< " "
                                  << it->second[2]<< '\n';
                }
        }
        if (  TakeshiKnowledge::getKnownObjectsLocationFromFile(pth,v))
        {
          std::cout << "Objs by file" << '\n';
          for (std::map<std::string,std::vector<float> >::iterator it=v.begin(); it!=v.end(); ++it)
          {
                  std::cout << it->first << " => "
                            << it->second[0] <<" "
                            << it->second[1]<< " "
                            << it->second[2]<< '\n';
          }
        }
        else
        {
          std::cout << "Read Failed" << '\n';
        }
        return 0;
}
