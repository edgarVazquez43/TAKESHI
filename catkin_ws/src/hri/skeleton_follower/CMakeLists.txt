cmake_minimum_required(VERSION 2.8.3)
project(skeleton_follower)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  #actionlib
  roscpp
  rospy
  roslib
  vision_msgs
)
find_package(Boost REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
  #actionlib
  roscpp
  rospy
  roslib
  vision_msgs
  sensor_msgs
  trajectory_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(skeleton_follower_node  src/skeleton_follower_node.cpp src/skeleton_follower.cpp )
add_dependencies(skeleton_follower_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(skeleton_follower_node
  ${catkin_LIBRARIES}
  )
