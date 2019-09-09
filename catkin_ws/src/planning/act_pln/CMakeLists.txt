cmake_minimum_required(VERSION 2.8.3)
project(act_pln)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  manip_msgs
  nav_msgs
  hri_msgs
  navig_msgs
  point_cloud_manager
  roscpp
  rospy
  std_msgs
  tf
  vision_msgs
  bbros_bridge
  justina_tools
  takeshi_tools
  std_srvs
  roslib
  message_generation
)

# Generate messages in the 'msg' folder
add_message_files(
  FILES
  virtualMsg.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES act_pln
#  CATKIN_DEPENDS geometry_msgs manip_msgs nav_msgs navig_msgs point_cloud_manager roscpp rospy std_msgs tf vision_msgs
   CATKIN_DEPENDS justina_tools roscpp rospy  hri_msgs takeshi_tools
#  DEPENDS system_lib
  CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
#include_directories(
#  ${catkin_INCLUDE_DIRS}
#)

find_package(OpenCV REQUIRED)
#find_package(PCL REQUIRED)
set(CMAKE_PREFIX_PATH "/usr/local/")
set(OpenCV_INCLUDE_DIRS "/usr/local/include")


include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
#  ${PCL_INCLUDE_DIRS}
)


#######################################
###    ACHY BREAKY HEART  [TEST]    ###
# add_executable(achy_breaky_heart
#  src/achy_breaky_heart.cpp
# )

# add_dependencies(achy_breaky_heart ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# target_link_libraries(achy_breaky_heart
#  ${catkin_LIBRARIES}
# )

#######################################
###    COYO TEST  [TEST]    ###
 add_executable(test_faces_osc
  src/test_faces_osc.cpp
 )

 add_dependencies(test_faces_osc ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

 target_link_libraries(test_faces_osc
  ${catkin_LIBRARIES}
 )

#####################################
####    HELP-ME CARRY   [TEST]    ###
# add_executable(helpMeCarry_test
#   src/helpMeCarry_test.cpp
#   )

# add_dependencies(helpMeCarry_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# target_link_libraries(helpMeCarry_test
#   ${catkin_LIBRARIES}
# )

#####################################
####    GPRS   [TEST]    ###
# add_executable(gpsr_test
#   src/gpsr_test.cpp
#   )

# add_dependencies(gpsr_test ${${PROJECT_NAME}_EXPORTED_TARGETS_TARGETS} ${catkin_EXPORTED_TARGETS})

# target_link_libraries (gpsr_test
#  ${catkin_LIBRARIES}
# )


#######################################
###    SPEECH AND PERSON  [TEST]    ###
# add_executable(speech_person_test
#   src/speech_person_test.cpp
# )

# add_dependencies(speech_person_test
# ${${PROJECT_NAME}_EXPORTED_TARGETS}
# ${catkin_EXPORTED_TARGETS})

# target_link_libraries(speech_person_test
#   ${catkin_LIBRARIES}
#   )

#######################################
###    OPEN-CHALLENGE  [TEST]    ###
#add_executable(open_challenge_montreal
#  src/open_Challenge_montreal.cpp
#)
#
#add_dependencies(open_challenge_montreal
#  ${${PROJECT_NAME}_EXPORTED_TARGETS}
#  ${catkin_EXPORTED_TARGETS}
#  )
#
#target_link_libraries(open_challenge_montreal
#  ${catkin_LIBRARIES}
#)

#######################################
####    EEGPSR  [TEST]    ###
#add_executable(eegpsr
#  src/eegpsr_test.cpp
#)
#
#add_dependencies(eegpsr
#  ${${PROJECT_NAME}_EXPORTED_TARGETS}
#  ${catkin_EXPORTED_TARGETS}
#  )
#
#target_link_libraries(eegpsr
#  ${catkin_LIBRARIES}
#)
#

#######################################
###    Bring Me  [TEST]    ###
#add_executable(bring_me_test
#  src/bring_me_test.cpp
#)
#
#add_dependencies(bring_me_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#
#target_link_libraries(bring_me_test
#  ${catkin_LIBRARIES}
#  )

#######################################
###    Tidy Up Here  [TEST]    ###
#add_executable(tidy_up_here_test
#  src/tidy_up_here_test.cpp
#)
#
#add_dependencies(tidy_up_here_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#
#target_link_libraries(tidy_up_here_test
#  ${catkin_LIBRARIES}
#  )

######################################
###    Automatic Search  [TEST]    ###
# add_executable(search_online
#   src/search_objects_online.cpp
# )
#
# add_dependencies(search_online ${${PROJECT_NAME}_EXPORTED_TARGETS} # ${catkin_EXPORTED_TARGETS})
#
# target_link_libraries(search_online
#   ${catkin_LIBRARIES}
#   )

#######################################
###    Time Monitor    ###
# add_executable(time_monitor
#   src/monitor.cpp
# )

# add_dependencies(time_monitor ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# target_link_libraries(time_monitor
#   ${catkin_LIBRARIES}
#   )

#######################################
###    Time Monitor    ###
 add_executable(test_task
   src/test.cpp
 )
add_dependencies(test_task ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

 target_link_libraries(test_task
   ${catkin_LIBRARIES}
   ${OpenCV_LIBS}
   )

###Another TEST because we cant have enough of them
# add_executable(coyo_test_task
#   src/test_coyo.cpp
# )

# add_dependencies(coyo_test_task ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# target_link_libraries(coyo_test_task
#   ${catkin_LIBRARIES}
#   )

#######################################
###    Final Tokio    ###
#add_executable(final_tokio
#  src/final_tokio.cpp
#)
#
#add_dependencies(final_tokio ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#
#target_link_libraries(final_tokio
#  ${catkin_LIBRARIES}
#  )

########################################
########  demo pickup ########
add_executable(demoPickUp src/demo_pick.cpp )
add_dependencies(demoPickUp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(demoPickUp
${catkin_LIBRARIES}
)

########################################
########  demo follow_me ########
add_executable(demoFollowMe src/demo_follow.cpp )
add_dependencies(demoFollowMe ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(demoFollowMe
${catkin_LIBRARIES}
)


########################################
########        demo full       ########
##Follow navigation handover and all that good stuff!!!

add_executable(finalTMR src/demo_noviembre_18.cpp )
add_dependencies(finalTMR ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(finalTMR ${catkin_LIBRARIES}
  )

##############################################
########     HSR-CHALLENGE Test       ########
add_executable(hsr_challenge src/hsr_challenge.cpp )
add_dependencies(hsr_challenge ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


target_link_libraries(hsr_challenge
${catkin_LIBRARIES}
)

########################################
########  Receptionist Test ########
add_executable(receptionist src/receptionist.cpp )
add_dependencies(receptionist ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(receptionist
${catkin_LIBRARIES}
)


########################################
########  carry_my_luggage Test ########

add_executable(carry_my_luggage src/carry_my_luggage.cpp )
add_dependencies(carry_my_luggage ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(carry_my_luggage
${catkin_LIBRARIES}
)


#######################################
###    ROBOT INSPECTION  2019    ###
add_executable(robot_inspection_TMR_2019
  src/robot_inspection_TMR_2019.cpp
)
add_dependencies(robot_inspection_TMR_2019 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_inspection_TMR_2019
  ${catkin_LIBRARIES}
  )


#######################################
###    Clean Up  [TEST]    ###
#add_executable(clean_up_test
#  src/clean_up_test.cpp
#)

#add_dependencies(clean_up_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#target_link_libraries(clean_up_test
#  ${catkin_LIBRARIES}
#  )

#######################################
###    Clean Up 2019    ###
 add_executable(clean_up_2019
   src/clean_up_2019.cpp
 )

 add_dependencies(clean_up_2019 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

 target_link_libraries(clean_up_2019
   ${catkin_LIBRARIES}
   )

#######################################
###    Clean Up 2019    ###
add_executable(clean_up_tester
  src/clean_up_tester.cpp
)

add_dependencies(clean_up_tester ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(clean_up_tester
  ${catkin_LIBRARIES}
  )

#######################################
###    STORING-GROSERIES  [TEST]    ###
add_executable(storing_groseries_test
 src/storing_groseries_test.cpp
)

add_dependencies(storing_groseries_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(storing_groseries_test
 ${catkin_LIBRARIES}
)


#######################################
###    SERVING DRINKS  [TEST]    ###
add_executable(serving_drinks
 src/serving_drinks_test.cpp
)

add_dependencies(serving_drinks ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(serving_drinks
 ${catkin_LIBRARIES}
 )

#######################################
###    RESTAURANT  [TEST]    ###
add_executable(restaurant_test
#  src/restaurant_canada.cpp
   src/restaurant.cpp
)

add_dependencies(restaurant_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
  )

target_link_libraries(restaurant_test
  ${catkin_LIBRARIES}
  )

#######################################
###    P&G  [TEST]    ###
add_executable(pg_test
 src/pg_test.cpp
)

add_dependencies(pg_test
 ${${PROJECT_NAME}_EXPORTED_TARGETS}
 ${catkin_EXPORTED_TARGETS}
 )

target_link_libraries(pg_test
 ${catkin_LIBRARIES}
 )

#######################################
###    TAKE OUT GARBAGE  [TEST]    ###
add_executable(take_out_garbage
 src/take_out_garbage.cpp
)

add_dependencies(take_out_garbage
 ${${PROJECT_NAME}_EXPORTED_TARGETS}
 ${catkin_EXPORTED_TARGETS}
 )

target_link_libraries(take_out_garbage
 ${catkin_LIBRARIES}
)

#######################################
###    Hand Me that    ###
add_executable(hand_me_that_task
  src/hand_me_that/hand_me_that.cpp
  src/hand_me_that/interactive_clean_test.h 
  src/hand_me_that/interactive_clean_test.cpp 
)

add_dependencies(hand_me_that_task ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(hand_me_that_task
  ${catkin_LIBRARIES}
  )

#######################################
###    TEST OSCAR  [TEST]    ###
add_executable( test_oscar
 src/test_oscar.cpp
)

add_dependencies(test_oscar
 ${${PROJECT_NAME}_EXPORTED_TARGETS}
 ${catkin_EXPORTED_TARGETS}
 )

target_link_libraries(test_oscar
 ${catkin_LIBRARIES}
)





#######################################
###    VR HSR    ###
add_executable(vr_hsr_test
  src/vr_hsr/vr_robocup2019.cpp
)

add_dependencies(hand_me_that_task ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(vr_hsr_test
  ${catkin_LIBRARIES}
  )


#######################################
###    VR HSR    ###
add_executable(final_robocup_sydney
  src/final_robocup.cpp
)

add_dependencies(final_robocup_sydney
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})

target_link_libraries(final_robocup_sydney
  ${catkin_LIBRARIES}
  )

