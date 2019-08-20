  #include "hand_camera_manip/grasp_srv.h"

int main(int argc, char *argv[]) {
        ros::init(argc, argv, "hand_camera_grasp_server");
        grasp_srv gs;

        ros::spin();

        return 0;
}
