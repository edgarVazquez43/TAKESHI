cmake_minimum_required(VERSION 2.8.3)
project(hand_camera_manip)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  control_msgs
  controller_manager_msgs
  roscpp
  rospy
  tmc_control_msgs
  trajectory_msgs
  message_generation
  roslib
  vision_msgs
)
find_package(Boost REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
  actionlib
  control_msgs
  controller_manager_msgs
  roscpp
  rospy
  tmc_control_msgs
  trajectory_msgs
  roslib
  vision_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(hand_grasp_srv  src/grasp_srv.cpp src/hand_grasp_srv.cpp )
add_dependencies(hand_grasp_srv ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(hand_grasp_srv
  ${catkin_LIBRARIES}
  )

add_executable(camera_manip_node src/camera_manip.h src/camera_manip.cpp src/camera_manip_node.cpp  )
target_link_libraries(camera_manip_node
  ${catkin_LIBRARIES}
)
