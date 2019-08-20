cmake_minimum_required(VERSION 2.8.3)
project(test)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  justina_tools
  takeshi_tools
  roscpp
  rospy
  hri_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES test
   CATKIN_DEPENDS justina_tools roscpp rospy hri_msgs
#  DEPENDS system_lib
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


##### INVERSE_KINEMATIC (MoveIt)  TEST  #####
add_executable(ik_moveit
  src/ik_moveit.cpp
)
target_link_libraries(ik_moveit
  ${catkin_LIBRARIES}
  )

add_dependencies(ik_moveit
  ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


##### INVERSE_KINEMATIC (Geometric)  TEST  #####
add_executable(ik_geometric
  src/ik_geometric.cpp
)
target_link_libraries(ik_geometric
  ${catkin_LIBRARIES}
  )

add_dependencies(ik_geometric
  ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


# ###### SPEECH_TEST #######
# add_executable(speech_test
#   src/speech_test.cpp)

## Specify libraries to link a library or executable target against
##### DIRECT_KINEMATIC (MoveIt) TEST  #####
add_executable(dk_moveit_test
  src/dk_moveit.cpp
  )

target_link_libraries(dk_moveit_test
  ${catkin_LIBRARIES}
  )

add_dependencies(dk_moveit_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})



##### JustinaHardware (MoveIt) TEST  #####
add_executable(JustinaHardware_test
  src/JustinaHardware_test.cpp
  )

target_link_libraries(JustinaHardware_test
  ${catkin_LIBRARIES}
  )

add_dependencies(JustinaHardware_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})



##### JustinaObjectReco TEST  #####
add_executable(find_objects_test
  src/find_objects_test.cpp
  )

target_link_libraries(find_objects_test
  ${catkin_LIBRARIES}
  )

add_dependencies(find_objects_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})


##### JustinaObjectReco TEST  #####
add_executable(state_machine_1
  src/machine_state.cpp
  )

target_link_libraries(state_machine_1
  ${catkin_LIBRARIES}
  )

add_dependencies(state_machine_1
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})


##### MANIP TEST  #####
add_executable(manip_test
  src/manip_test.cpp
  )

target_link_libraries(manip_test
  ${catkin_LIBRARIES}
  )

add_dependencies(manip_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})


##### Panoramic Photo TEST  #####
add_executable(panoMaker_test
  src/panoramic_test.cpp
  )

target_link_libraries(panoMaker_test
  ${catkin_LIBRARIES}
  )

add_dependencies(panoMaker_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})

##### Hand Camera TEST  #####
add_executable(hand_camera_test
  src/hand_camera_manip.cpp
  )

target_link_libraries(hand_camera_test
  ${catkin_LIBRARIES}
  )

add_dependencies(hand_camera_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})


##Known object ltm test
add_executable(handover_test
  src/handover_test.cpp
  )

target_link_libraries(handover_test
  ${catkin_LIBRARIES}
  )

add_dependencies(handover_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})

##Known object ltm test
add_executable(grasp_obj_test
  src/grasp_obj_test.cpp
  )

target_link_libraries(grasp_obj_test
  ${catkin_LIBRARIES}
  )

add_dependencies(grasp_obj_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
