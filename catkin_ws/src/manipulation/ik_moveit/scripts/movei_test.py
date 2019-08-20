#!/usr/bin/env python
import sys
import copy
import rospy
import math
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
import sensor_msgs.msg
from std_msgs.msg import String
from moveit_msgs.msg import RobotState
from sensor_msgs.msg import JointState

"""La pregunta de los 64,000 pesos es como hacer que plenee en el marco
de referencia de otra cosa, actualmente planea sobre el gripper en el marco
de /odom evidentemente este tiene deriva y además sería muy latoso planear sobre este
pero si se indica que la pose a planear esta en el marco de referencia de la base
no planea. Y todo el graspero de justina/takeshi esta en el marco de la base"""

if __name__ == '__main__':

    moveit_commander.roscpp_initialize(sys.argv)

    rospy.init_node('grasping_tf', anonymous=True)

    robot = moveit_commander.RobotCommander()
    scene = moveit_commander.PlanningSceneInterface()
    group = moveit_commander.MoveGroupCommander(
        "whole_body")  # take control of the hsrb arm
    group.allow_replanning(True)  # 5 attempts
    robot_state = robot.get_current_state()
    print "============ Robot State:"
    # print robot_state #check that the state of the robot can be fetched
    #group.set_pose_reference_frame("base_footprint")
    print "============ Plannig frame: %s" % group.get_planning_frame()
    print "============ Pose frame: %s" % group.get_pose_reference_frame()
    print "============ Effector frame: %s" % group.get_end_effector_link()
    print "============ Robot Groups:"
    print robot.get_group_names()
    group.set_planning_time(10)  # 10 seconds for the planner
    group.set_start_state_to_current_state()
    group.set_goal_tolerance(0.01)
    # 'hand_palm_link') specifying the end effector is redundant
    target = group.get_current_pose()
    print "============ Initial pose"
    print target
    target.header.stamp = rospy.Time.now()
    # Si habilitamos el marco de referencia  para la pose objetivo como la base
    # no llega a una solución
    #target.header.frame_id = "base_link"
    #target.pose.position.z+=0.2;
    target.pose.position.x = 0.0;
    target.pose.position.y = 0.0;
    #target.pose.position.z += 0.1
    # target.pose.orientation.x = 0
    # target.pose.orientation.y = 0
    # target.pose.orientation.z = 0
    # target.pose.orientation.w = 1
    print "=========== Target Pose"
    print target
    group.set_pose_target(target)
    # group.set_rpy_target([0,0.7,0])
    plan = group.plan()
    group.execute(plan, wait=True)  # move robot arm
    group.stop()
