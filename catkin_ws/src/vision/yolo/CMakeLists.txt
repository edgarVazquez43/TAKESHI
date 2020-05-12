cmake_minimum_required(VERSION 2.8.3)
project(yolo_v3)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  roslib
  geometry_msgs
  takeshi_tools
  sensor_msgs
  std_msgs
  tf
  vision_msgs
  )

add_definitions(-std=c++11)

find_package(OpenCV REQUIRED)

set(CMAKE_PREFIX_PATH "/usr/local/")
set(OpenCV_INCLUDE_DIRS "/usr/local/include")

catkin_package(
  )

include_directories(
  include ${catkin_INCLUDE_DIRS})

link_directories(${catkin_LIBRARY_DIRS})


add_executable(yolo_node src/yolo_node.cpp)
add_dependencies(yolo_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(yolo_node ${OpenNI_LIBRARIES} ${orocos_kdl_LIBRARIES} ${catkin_LIBRARIES})
