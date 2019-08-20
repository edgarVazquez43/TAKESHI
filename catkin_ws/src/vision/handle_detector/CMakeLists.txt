cmake_minimum_required(VERSION 2.8.3)
project(handle_detector)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(PCL 1.7.2 REQUIRED)
find_package(catkin REQUIRED cmake_modules)
find_package(Eigen REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  pcl_conversions
  pcl_ros
  roscpp
  sensor_msgs
  std_msgs
  tf
  vision_msgs
  point_cloud_manager
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES handle_detector
  CATKIN_DEPENDS geometry_msgs pcl pcl_conversions pcl_ros roscpp sensor_msgs std_msgs tf vision_msgs point_cloud_manager
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

message(WARNING DEV ${PCL_LIBRARY_DIRS} )
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(${PROJECT_NAME}_node src/handle_detector_node.cpp src/handle_detector.cpp)
add_dependencies(${PROJECT_NAME}_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES} ${PCL_LIBRARIES}
 )

 add_executable(${PROJECT_NAME}_server src/handle_detector_server.cpp src/handle_detector.cpp)
 add_dependencies(${PROJECT_NAME}_server ${catkin_EXPORTED_TARGETS})
 target_link_libraries(${PROJECT_NAME}_server
    ${catkin_LIBRARIES} ${PCL_LIBRARIES}
  )
