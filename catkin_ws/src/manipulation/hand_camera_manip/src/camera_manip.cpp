#include "camera_manip.h"

#define RAD2DEG 180/M_PI
#define DEG2RAD M_PI/180

void camera_manipulation::get_current_position_controller(const control_msgs::JointTrajectoryControllerState &state)
{
        //printf("Got somethings\n" );

        for(int i = 0; i< state.joint_names.size(); i++)
        {
                printf("Joint %s: %f\n", state.joint_names[i].c_str(),state.actual.positions[i] );

        }
        return;
}

void camera_manipulation::get_current_position(const sensor_msgs::JointState &jo)
{
        //printf("Got something\n" );

        for(int i = 0; i< jo.name.size(); i++)
        {
                for (int k = 0; k < joints.name.size(); k++)
                {
                        if(joints.name[k]==jo.name[i])
                        {

                                joints.position[k]=jo.position[i];
                                //printf("Joint %s: %f\n", joints.name[k].c_str(),joints.position[k]*RAD2DEG );
                                //save values on inernal message
                        }
                }

        }
        return;
}

void camera_manipulation::move_arm(float pos[5])
{
        ctrl.points.resize(1);
        ctrl.points[0].positions.resize(5);
        ctrl.points[0].positions[0] = pos[0];
        ctrl.points[0].positions[1] = pos[1];
        ctrl.points[0].positions[2] = pos[2];
        ctrl.points[0].positions[3] = pos[3];
        ctrl.points[0].positions[4] = pos[4];
        ctrl.points[0].velocities.resize(5);
        for (size_t i = 0; i < 5; ++i) {
                ctrl.points[0].velocities[i] = 0.0;
        }
        ctrl.points[0].time_from_start = ros::Duration(2.0);
        control_pub.publish(ctrl);

        return;
}

void camera_manipulation::enable_callback(const std_msgs::Bool en)
{
        enable=en.data;
        std::cout << "Setting enable as " << enable<<'\n';
        return;
}

void camera_manipulation::ctrl_callback_shelf(const std_msgs::Float32MultiArray &p)
{
        if (enable) {
                ctrl_law_slide(p);
        }

        return;
}

void camera_manipulation::ctrl_callback_table(const std_msgs::Float32MultiArray &p)
{
        if (enable) {
                ctrl_law_pose2D(p);
        }

        return;
}

camera_manipulation::camera_manipulation(float kps[6],float kp_base[2], int x_c, int y_c,float area,int routine)
{
        std::cout << "Constructor Starting" << std::endl;

        position_sub = nh_.subscribe("/hsrb/joint_states", 1,
                                     &camera_manipulation::get_current_position, this);
        enable_sub =nh_.subscribe("/enable_hand",1,
                                  &camera_manipulation::enable_callback,this);
        fnsh_pub = nh_.advertise<std_msgs::Bool>("/hand_finish",1);
        control_pub = nh_.advertise<trajectory_msgs::JointTrajectory>("/hsrb/arm_trajectory_controller/command", 5);
        gripper_pub = nh_.advertise<trajectory_msgs::JointTrajectory>("/hsrb/gripper_controller/command", 5);
        base_pub = nh_.advertise<geometry_msgs::Twist>("/hsrb/command_velocity",1);
        error_pub = nh_.advertise<std_msgs::Float32MultiArray>("/hand_camera_error",5);

        switch (routine) {
        case 0:
                point_sub = nh_.subscribe("/hand/object",1,
                                          &camera_manipulation::ctrl_callback_shelf,this);
                break;
        case 1:
                point_sub = nh_.subscribe("/hand/object",1,
                                          &camera_manipulation::ctrl_callback_table,this);
                break;
        default:
                point_sub = nh_.subscribe("/hand/object",1,
                                          &camera_manipulation::ctrl_callback_shelf,this);
                break;
        }

        // while (pub.getNumSubscribers() == 0) {
        //         ros::Duration(0.1).sleep();
        // }

        ctrl.joint_names.push_back("arm_lift_joint");
        ctrl.joint_names.push_back("arm_flex_joint");
        ctrl.joint_names.push_back("arm_roll_joint");
        ctrl.joint_names.push_back("wrist_flex_joint");
        ctrl.joint_names.push_back("wrist_roll_joint");

        //use a dictionary
        joints.name.push_back("arm_lift_joint"); //kps[0]
        joints.name.push_back("arm_flex_joint"); //kps[1]
        joints.name.push_back("arm_roll_joint"); //kps[2]
        joints.name.push_back("wrist_flex_joint");
        joints.name.push_back("wrist_roll_joint"); //kps[4]
        joints.position.resize(5);

        kp_arm_lift= kps[0];
        kp_arm_flex =kps[1];
        kp_arm_roll = kps[2];
        kp_wrist_flex = kps[3];
        kp_wrist_roll = kps[4];

        kp_base_x=kp_base[0];
        kp_base_y=kp_base[1];
        x_center=x_c; y_center=y_c; obj_area=area;
        //std::cout << kp_arm_roll << '\n';
        enable=false;
        return;

}

void camera_manipulation::finish_manip(const std_msgs::Float32MultiArray error_msg)
{
        //Check error message,if less than a threslhold, grasps and stops
        //not actually a callback.
        std_msgs::Bool fnsh;
        fnsh.data=(fabs(error_msg.data[0])<0.05) && (fabs(error_msg.data[1])<0.05) && (fabs(error_msg.data[2])<0.05);

        if (fnsh.data)
        {
                std::cout << "Finished sequence" << '\n';
                enable=false; //Cease to grip
                // initialize action client
                act_cli cli("/hsrb/gripper_controller/grasp", true);
                // wait for the action server to establish connection
                cli.waitForServer();
                // fill ROS message
                tmc_control_msgs::GripperApplyEffortGoal goal;
                goal.effort = -0.05;
                // send message to the action server
                cli.sendGoal(goal);
                // wait for the action server to complete the order
                cli.waitForResult(ros::Duration(2.0));
                fnsh_pub.publish(fnsh); //this lets everyone knows it finihsed
        }
        return;

}


void camera_manipulation::ctrl_law_pose2D(const std_msgs::Float32MultiArray &p)
{
        float error_y=(y_center-p.data[1])/y_center;
        //float error_theta=(theta-p.data[2]);
        float error_x=(x_center-p.data[0])/x_center;
        float theta=p.data[2]; //in this case third element is an angle.
        //This is merely notation for clarity

        std_msgs::Float32MultiArray error_msg;
        error_msg.data.push_back(error_x);
        error_msg.data.push_back(error_y);
        //error_msg.data.push_back(error_theta); //this is normalized

        error_pub.publish(error_msg);
        set_ctrl_to_current();

        //ctrl.points[0].positions[4]=joints.position[4]-kp_wrist_roll*error_theta;
        //ctrl.points[0].positions[4]=DEG2RAD*theta;
        ctrl.points[0].time_from_start = ros::Duration(1.0);

        geometry_msgs::Twist base_msg;
        base_msg.linear.x=kp_base_x*error_x;
        base_msg.linear.y=kp_base_y*error_y;

        std::cout << "Theta " << theta <<'\n';
        std::cout << "X " << p.data[0]<<'\n';
        std::cout << "Y " << p.data[1]<<'\n';
        //std::cout << "Error_th " <<error_theta <<'\n';
        std::cout << "Error_x " <<error_x <<'\n';
        std::cout << "Error_y " <<error_y <<'\n';
        std::cout << "Control wrist roll" << ctrl.points[0].positions[4] <<'\n';
        std::cout << "Control base x " << base_msg.linear.x <<'\n';
        std::cout << "Control base y " << base_msg.linear.y <<'\n';

        float sat_values_min[4]={0.05,-90*DEG2RAD,-90*DEG2RAD,-90*DEG2RAD};
        float sat_values_max[4]={0.5,0,90*DEG2RAD,90*DEG2RAD};
        for (size_t i = 1; i < 4; i++) {
                if(ctrl.points[0].positions[i]<sat_values_min[i]  )
                {
                        ctrl.points[0].positions[i]=sat_values_min[i];
                }
                else if (ctrl.points[0].positions[i]>sat_values_max[i])
                {
                        ctrl.points[0].positions[i]=sat_values_max[i];
                }
        }

        base_pub.publish(base_msg);
        control_pub.publish(ctrl);
        //finish_manip(error_msg);
}

void camera_manipulation::ctrl_law_slide(const std_msgs::Float32MultiArray &p)
{
        float error_x=(x_center-p.data[0])/x_center;
        float error_y=(y_center-p.data[1])/y_center;
        float error_a=(obj_area-p.data[2])/obj_area;

        std_msgs::Float32MultiArray error_msg;
        error_msg.data.push_back(error_x);
        error_msg.data.push_back(error_y);
        error_msg.data.push_back(error_a); //this is normalized

        error_pub.publish(error_msg);
        set_ctrl_to_current();

        ctrl.points[0].positions[1]=joints.position[1]-kp_arm_flex*error_a;
        ctrl.points[0].positions[3]=joints.position[3]-kp_wrist_flex*error_x;
        ctrl.points[0].time_from_start = ros::Duration(1.0);

        geometry_msgs::Twist base_msg;
        base_msg.linear.y=kp_base_y*error_y;

        std::cout << "Error_a " <<error_a <<'\n';
        std::cout << "Error_x " <<error_x <<'\n';
        std::cout << "Error_y " <<error_y <<'\n';
        std::cout << "Control law arm flex" <<ctrl.points[0].positions[1] <<'\n';
        std::cout << "Control law wrist flex" <<ctrl.points[0].positions[3] <<'\n';
        std::cout << "Control base y" <<base_msg.linear.y<<'\n';

        float sat_values_min[4]={0.05,-90*DEG2RAD,-90*DEG2RAD,-90*DEG2RAD};
        float sat_values_max[4]={0.5,0,90*DEG2RAD,90*DEG2RAD};
        for (size_t i = 1; i < 4; i++) {
                if(ctrl.points[0].positions[i]<sat_values_min[i]  )
                {
                        ctrl.points[0].positions[i]=sat_values_min[i];
                }
                else if (ctrl.points[0].positions[i]>sat_values_max[i])
                {
                        ctrl.points[0].positions[i]=sat_values_max[i];
                }
        }

        base_pub.publish(base_msg);
        control_pub.publish(ctrl);
        finish_manip(error_msg);
}

void camera_manipulation::set_ctrl_to_current()
{
        //small helper function, set all control law inputs to the current Joint state

        ctrl.points.resize(1);
        ctrl.points[0].positions.resize(5);
        for (int i = 0; i < 5; i++) {
                ctrl.points[0].positions[i] = joints.position[i];
        }
        ctrl.points[0].velocities.resize(5);
        for (int i = 0; i < 5; i++) {
                ctrl.points[0].velocities[i] = 0.0;
        }
        return;
}

void camera_manipulation::ctrl_law_cartesian(const std_msgs::Float32MultiArray &p)
{

        float error_x=(x_center-p.data[0]);
        float error_y=(y_center-p.data[1]);
        float error_a=(obj_area-p.data[2])/obj_area;

        std_msgs::Float32MultiArray error_msg;
        error_msg.data.push_back(error_x);
        error_msg.data.push_back(error_y);
        error_msg.data.push_back(error_a); //this is normalized

        error_pub.publish(error_msg);

        set_ctrl_to_current();

        std::cout << "Control law" << '\n';

        ctrl.points[0].positions[0]=joints.position[0]-kp_arm_lift*error_x;
        ctrl.points[0].time_from_start = ros::Duration(1.0);

        geometry_msgs::Twist base_msg;
        base_msg.linear.y=kp_base_y*error_y;
        base_msg.linear.x=kp_base_x*error_a;

        std::cout << "Error_a " <<error_a <<'\n';
        std::cout << "Error_x " <<error_x <<'\n';
        std::cout << "Error_y " <<error_y <<'\n';
        std::cout << "Control law arm lift " <<ctrl.points[0].positions[0] <<'\n';
        std::cout << "Control law base x " <<base_msg.linear.x <<'\n';
        std::cout << "Control law base y " <<base_msg.linear.y <<'\n';

        float sat_values_min[4]={0.05,-90*DEG2RAD,-90*DEG2RAD,-90*DEG2RAD};
        float sat_values_max[4]={0.5,0,90*DEG2RAD,90*DEG2RAD};
        for (size_t i = 1; i < 4; i++) {
                if(ctrl.points[0].positions[i]<sat_values_min[i]  )
                {
                        ctrl.points[0].positions[i]=sat_values_min[i];
                }
                else if (ctrl.points[0].positions[i]>sat_values_max[i])
                {
                        ctrl.points[0].positions[i]=sat_values_max[i];
                }
        }

        base_pub.publish(base_msg);
        control_pub.publish(ctrl);
        return;
}


void camera_manipulation::ctrl_law_flex(const std_msgs::Float32MultiArray &p)
{

        float error_x=(x_center-p.data[0]);
        float error_y=(y_center-p.data[1]);
        float error_a=(p.data[2]-obj_area)/obj_area;

        std_msgs::Float32MultiArray error_msg;
        error_msg.data.push_back(error_x);
        error_msg.data.push_back(error_y);
        error_msg.data.push_back(error_a); //this is normalized

        error_pub.publish(error_msg);

        ctrl.points.resize(1);
        ctrl.points[0].positions.resize(5);
        for (int i = 0; i < 5; i++) {
                ctrl.points[0].positions[i] = joints.position[i];
        }
        ctrl.points[0].velocities.resize(5);
        for (int i = 0; i < 5; i++) {
                ctrl.points[0].velocities[i] = 0.0;
        }
        std::cout << "Control law" << '\n';

        ctrl.points[0].positions[1]=joints.position[1]+kp_arm_flex*error_a;
        ctrl.points[0].positions[2]=joints.position[2]+kp_arm_roll*error_y;
        ctrl.points[0].positions[3]=joints.position[3]-kp_wrist_flex*error_x;
        //ctrl.points[0].positions[3]=joints.position[3];
        //if ctrl.points[0].positions[4]
        ctrl.points[0].time_from_start = ros::Duration(1.0);

        std::cout << "Error_a " <<error_a <<'\n';
        std::cout << "Error_x " <<error_x <<'\n';
        std::cout << "Error_y " <<error_y <<'\n';
        std::cout << "Control law arm flex" <<ctrl.points[0].positions[1] <<'\n';
        std::cout << "Control law arm roll" <<ctrl.points[0].positions[2] <<'\n';
        std::cout << "Control law wrist flex" <<ctrl.points[0].positions[3] <<'\n';

        float sat_values_min[4]={0.05,-90*DEG2RAD,-90*DEG2RAD,-90*DEG2RAD};
        float sat_values_max[4]={0.5,0,90*DEG2RAD,90*DEG2RAD};
        for (size_t i = 1; i < 4; i++) {
                if(ctrl.points[0].positions[i]<sat_values_min[i]  )
                {
                        ctrl.points[0].positions[i]=sat_values_min[i];
                }
                else if (ctrl.points[0].positions[i]>sat_values_max[i])
                {
                        ctrl.points[0].positions[i]=sat_values_max[i];
                }
        }
        control_pub.publish(ctrl);
        return;
}

bool camera_manipulation::check_controllers()
{
        //check if controllers are  runinng
        ros::ServiceClient client = nh_.serviceClient<controller_manager_msgs::ListControllers>(
                "/hsrb/controller_manager/list_controllers");
        controller_manager_msgs::ListControllers list_controllers;
        bool running = false;

        ros::Duration(0.1).sleep();
        if (client.call(list_controllers))
        {
                for (unsigned int i = 0; i < list_controllers.response.controller.size(); i++)
                {
                        controller_manager_msgs::ControllerState c = list_controllers.response.controller[i];
                        if (c.name == "arm_trajectory_controller" && c.state == "running")
                        {
                                running = true;
                        }
                }
        }
        return running;
}

void camera_manipulation::set_kp(float KP[6])
{
        this->kp_arm_lift=KP[0];
        this->kp_arm_flex=KP[1];
        this->kp_arm_roll=KP[2];
        this->kp_wrist_roll=KP[3];
        this->kp_wrist_flex=KP[4];
}
