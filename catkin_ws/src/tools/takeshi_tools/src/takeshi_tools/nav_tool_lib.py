#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import hsrb_interface
from std_msgs.msg import Float32MultiArray, Bool, Empty
from geometry_msgs.msg import Pose, Vector3, Quaternion, PoseStamped

#global _navigation_setter
#global omnibase

#_navigation_setter="hsr"
global globalGoalReached
global goalReached
global omnibase
global pubGlobalGoalXYZ
global whole_body
global robot_stop
globalGoalReached=True
goalReached=True
robot_stop=False
def callback_global_goal_reached(msg):
	global globalGoalReached
	globalGoalReached = msg.data

def callback_goal_reached(msg):
	global goalReached
	goalReached = msg.data

def callback_stop(msg):
	global robot_stop
	robot_stop=True


class nav_module():
	"""docstring for nav_module"""
	
	def __init__(self,select="hsr"):

		global omnibase
		global robot
		global whole_body
		self.navigation_setter=select
		self.goal=Float32MultiArray()
		omnibase=0
		robot=hsrb_interface.Robot()
		omnibase=robot.get("omni_base")
		whole_body = robot.get("whole_body")
		self.pubGlobalGoalXYZ = rospy.Publisher('/navigation/mvn_pln/get_close_xya', Float32MultiArray, queue_size=1)
		self.pubDistAngle = rospy.Publisher('/navigation/path_planning/simple_move/goal_dist_angle', Float32MultiArray, queue_size=1)
		self.pubRobotStop = rospy.Publisher('/hardware/robot_state/stop', Empty, queue_size=1)
		rospy.Subscriber("/navigation/global_goal_reached", Bool, callback_global_goal_reached)
		rospy.Subscriber("/navigation/goal_reached", Bool, callback_goal_reached)
		rospy.Subscriber("/hardware/robot_state/stop", Empty, callback_stop)
		self.set_navigation_type(select)			



	def set_navigation_type(self, type_nav):
		if type_nav=="hsr" or type_nav=="pumas":
			self.navigation_setter=type_nav
		else:
			print"Invalid navigation mode"
		print "USING "+ str(self.navigation_setter).upper() + " NAVIGATION BY DEFAULT"


	def get_navigation_type(self):
		return self.navigation_setter


	def getClose(self,x,y,theta, timeout):
		global whole_body
		global globalGoalReached
		global robot_stop
		rate=rospy.Rate(10)
		#whole_body.move_to_go()
		goal=Float32MultiArray()
		globalGoalReached=False
		robot_stop=False
		goal.data=[x,y,theta]
		if timeout!=0:
			attemps=int(timeout*10)
		else:
			attemps=10000000000000
		#print  goal.data
		self.pubGlobalGoalXYZ.publish(goal)
		rate.sleep()
		rospy.sleep(5.)
		while not globalGoalReached and not rospy.is_shutdown() and not robot_stop and attemps>=0:
			attemps-=1
			rate.sleep()
		robot_stop=False
		if not globalGoalReached:
			msg_stop=Empty()
			self.pubRobotStop.publish(msg_stop)
			rate.sleep()
			rospy.sleep(5.)
		x=rospy.Duration.from_sec(2.5)
		rospy.sleep(x)	


	def go_abs(self,x,y,theta,timeout=0.0,type_nav=None):
		if type_nav=="pumas":
			self.getClose(x,y,theta,timeout)
		elif type_nav=="hsr":
			omnibase.go_abs(x,y,theta, timeout)
		else:
			if self.navigation_setter=="pumas":
				self.getClose(x,y,theta, timeout)
			else:
				omnibase.go_abs(x,y,theta,timeout)


	def moveDistAngle(self,x, yaw, timeout):
		global goalReached
		global robot_stop
		rate=rospy.Rate(10)
		goal=Float32MultiArray()
		goalReached =False
		robot_stop=False
		goal.data=[x,yaw]
		#print  goal.data
		if timeout!=0:
			attemps=int(timeout*10)
		else:
			attemps=10000000000000
		self.pubDistAngle.publish(goal)
		rate.sleep()
		rospy.sleep(5.)
		while not goalReached and not rospy.is_shutdown() and not robot_stop and attemps>=0:
			attemps-=1
			rate.sleep()
		robot_stop=False
		if not goalReached:
			msg_stop=Empty()
			self.pubRobotStop.publish(msg_stop)
			rate.sleep()
			rospy.sleep(5.)
		rate.sleep()
		x=rospy.Duration.from_sec(2.5)
		rospy.sleep(x)


	def go_rel(self, x=0.0, y=0.0, yaw=0.0,timeout=0.0, type_nav=None):
		if type_nav=="pumas":
			self.moveDistAngle(x,yaw,timeout)
		elif type_nav=="hsr":
			omnibase.go_rel(x,y,yaw,timeout)
		else:
			if self.navigation_setter=="pumas":
				self.moveDistAngle(x,yaw, timeout)
			else:
				omnibase.go_rel(x,y,yaw,timeout)	




	
	##############################
	##   HSR Functions bypass   ##
	##############################
	
	def cancel_goal(self):
		omnibase.cancel_goal()

	def create_follow_trajectory_goal(self, poses, time_from_starts=[], ref_frame_id=None):
		return omnibase.create_follow_trajectory_goal(poses, time_from_starts, ref_frame_id)
	
	def create_go_pose_goal(self, pose, ref_frame_id=None):
		return omnibase.create_go_pose_goal(pose, ref_frame_id)

	def execute(self, goal):
		omnibase.execute(goal)

	def follow_trajectory(self, poses, time_from_starts=[], ref_frame_id=None):
		omnibase.follow_trajectory(poses, time_from_starts, ref_frame_id)

	def get_pose(self, ref_frame_id=None):
		return omnibase.get_pose(ref_frame_id)

	def go(self,  x, y, yaw, timeout=0.0, relative=False):
		omnibase.go(x, y, yaw, timeout, relative)

	def go_pose(self, pose=Pose(Vector3(x=0.0, y=0.0, z=0.0), Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)), timeout=0.0, ref_frame_id=None):
		omnibase.go_pose(pose, timeout, ref_frame_id)
	
	def is_moving(self):
		return omnibase.is_moving()

	def is_succeeded(self):
		return omnibase.is_succeeded()

	def move(self, pose, timeout=0.0, ref_frame_id=None):
		omnibase.move(pose, timeout, ref_frame_id)

	def pose(self):
		return omnibase.pose
