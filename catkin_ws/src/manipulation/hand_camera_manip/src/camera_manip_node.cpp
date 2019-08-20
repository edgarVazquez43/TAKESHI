#include "camera_manip.h"

enum routines {
        SLIDE, // fro grasping base on y, arm on flex and writ on flex
        CARTESIAN, //base in x,y and lift for z
        TWIST, //base on theta and arm flex and and wrist flex
};

int main(int argc, char **argv) {
        ros::init(argc, argv, "camera_manipulator");

        ros::NodeHandle nh_priv("~");
        // wait to establish connection between the controller

        float kps[6];
        nh_priv.param<float>("kp_arm_lift",kps[0],0.01);
        nh_priv.param<float>("kp_arm_flex",kps[1],0.05);
        nh_priv.param<float>("kp_arm_roll",kps[2],0.002);
        nh_priv.param<float>("kp_wrist_flex",kps[3],0.002);
        nh_priv.param<float>("kp_wrist_roll",kps[4],0.002);
        int x_c,y_c; //immage_center
        nh_priv.param<int>("y_center",y_c,240); 
        nh_priv.param<int>("x_center",x_c,240);
        float area; //area to regulate
        nh_priv.param<float>("area_setpoint",area,50000);
        float kp_b[2];
        nh_priv.param<float>("kp_base_x",kp_b[0],0.001); //360 lower half of the image
        nh_priv.param<float>("kp_base_y",kp_b[1],0.001);
        int routine; //type of movement to do:
        nh_priv.param<int>("routine",routine,0);

        // publish ROS message
        ros::Rate loop_rate(5);
        camera_manipulation cm(kps,kp_b,x_c,y_c,area,routine);
        if(!cm.check_controllers())
        {
                printf("Controllers not online\n" );
                return -1;
        }
        std::cout << "Starting" << '\n';



        // float pos[5]={0.2,-0.5,0.0,0.0,0.0};
        // printf("Sending command\n");
        // cm.move_arm(pos);
        // ros::spinOnce();

        while(ros::ok())
        {
                loop_rate.sleep();
                ros::spinOnce();
        }
        std::cout << "Bye" << '\n';

        return 0;
}
