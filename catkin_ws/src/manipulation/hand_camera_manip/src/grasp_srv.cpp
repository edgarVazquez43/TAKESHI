#include "hand_camera_manip/grasp_srv.h"

grasp_srv::grasp_srv()
{
        loader_pub = nh.advertise<std_msgs::String>("/load_surf_recog",1);
        enable_surf = nh.advertise<std_msgs::Bool>("/enable_surf", 1);
        enable_sat = nh.advertise<std_msgs::Bool>("en_sat_seg",1);
        enable_hand = nh.advertise<std_msgs::Bool>("/enable_hand", 1);
        fnsh_sub = nh.subscribe("/hand_finish",1, &grasp_srv::finish_cb, this);


        hand_grasp_server = nh.advertiseService("hand_camera_grasp", &grasp_srv::service_callback,this);

        ROS_INFO("Starting Service Client by Coyo-Soft\n");
}

void grasp_srv::grasp_by_hand(std::string fileToLoad )
{
        std_msgs::Bool enable;
        std_msgs::String file_msg;
        enable.data=true;
        enable_surf.publish(enable);
        file_msg.data=fileToLoad;
        loader_pub.publish(file_msg);
        enable_hand.publish(enable);
        //wait some time

        ros::Duration(15).sleep();
        enable.data=false;
        enable_surf.publish(enable);
        enable_hand.publish(enable); //hand node autodisable on grap but just to be sure
        ros::spinOnce();
        return;

}

void grasp_srv::grasp_kalas()
{
        std_msgs::Bool enable;
        std_msgs::String file_msg;
        enable.data=true;
        enable_sat.publish(enable);
        enable_hand.publish(enable);
        //wait some time
        ros::Duration(8).sleep();
        enable.data=false;
        enable_sat.publish(enable);
        enable_hand.publish(enable); //hand node autodisable on grap but just to be sure
        ros::spinOnce();
        return;

}

bool grasp_srv::service_callback(vision_msgs::HandCameraGrasp::Request& request,
                                 vision_msgs::HandCameraGrasp::Response& response)
{
        std::string query= ros::package::getPath("surf_recog") + "/config/";
        std::string obj;
        boost::filesystem::path p(query);
        boost::filesystem::directory_iterator end_itr;
        success=false;
        bool found_file=false;
        // cycle through the directory
        for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
        {
                // If it's not a directory, list it. If you want to list directories too, just remove this check.
                if (is_regular_file(itr->path())) {
                        // assign current file name to current_file and echo it out to the console.
                        std::string current_file = itr->path().stem().string();
                        //std::cout<< current_file<< std::endl;
                        if (request.name==current_file)
                        {
                                found_file=true;
                                obj=current_file+".xml";
                                std::cout << "File: " <<obj << " found"<< '\n';
                        }

                }
        }

        if (found_file)
        {
                grasp_by_hand(obj);
        }
        else if (request.name=="kalas")
        {
                grasp_kalas();
        }

        response.finish=this->success;
        ROS_INFO("Request: %s", request.name.c_str());
        ROS_INFO("Response %d", response.finish);
        return true;
}

void grasp_srv::finish_cb(const std_msgs::Bool &f)
{
        this->success=f.data;
        ROS_INFO("Grasping succesfull\n");
        return;
}
