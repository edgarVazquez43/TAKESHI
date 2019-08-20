cmake_minimum_required(VERSION 2.8.3)
project(surf_recog)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)
find_package(OpenCV REQUIRED)
# Find OpenNI
#find_package(PkgConfig)
#pkg_check_modules(OpenNI REQUIRED libopenni)

catkin_package(

)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide

add_executable(surf_trainer_node src/surf_trainer.cpp src/surf_trainer.h src/surf_trainer_node.cpp)
add_executable(surf_detector_node src/surf_detector.cpp src/surf_detector.h src/surf_detector_node.cpp)
##add_dependencies(skeleton_finder_node geometry_msgs_gencpp vision_msgs_gencpp)

target_link_libraries(surf_trainer_node

	${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

target_link_libraries(surf_detector_node

	${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)


#############
## Install ##
#############


#############
## Testing ##
#############
