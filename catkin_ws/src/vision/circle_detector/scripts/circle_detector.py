#!/usr/bin/env python

import cv2
from geometry_msgs.msg import Quaternion
import numpy as np
import rospy
import message_filters
from std_msgs.msg import String
from sensor_msgs.msg import LaserScan
from sensor_msgs.msg import Image
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist
from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import PoseStamped
import geometry_msgs
from tf.transformations import *
from tf.msg import tfMessage
from tf.transformations import euler_from_quaternion
import tf
import tf2_ros
from cv_bridge import CvBridge, CvBridgeError
bridge = CvBridge()
global tf_listener
global tf_broadcaster


from std_msgs.msg import String, Bool

global enable_xtion, enable_hand
enable_hand=False
enable_xtion=False

def shutdown(self):
 
		exit()

def callBackEnable_xtion(msg):
	global enable_xtion
	enable_xtion=msg.data
	if enable_xtion:
		print "circle detecttor xtion enable"
	else:
		print "circle detector xtion disable"

def callBackEnable_hand(msg):
	global enable_hand
	enable_hand=msg.data
	if enable_hand:
		print "circle detecttor hand camera enable"
	else:
		print "circle detector hand camera disable"

def callback_hand(img_msg):
	global enable_hand

	#tf_broadcaster=tf.TransformBroadcaster()
	tf_broadcaster=tf2_ros.StaticTransformBroadcaster()
	(trans,rot)=tf_listener.lookupTransform('hand_palm_link', 'map', rospy.Time(0))
	
	goal_hole=np.array((258,261))
   
	
	
   
	
################################################################ DO THINGS HERE
	cv2_img = bridge.imgmsg_to_cv2(img_msg, "bgr8")
	gray = cv2.cvtColor(cv2_img,cv2.COLOR_BGR2GRAY)
	blur = cv2.GaussianBlur(gray,(11,11),0)
	cv2.namedWindow("xtion_blur")
	cv2.imshow("xtion_blur", blur)   
	edges = cv2.Canny(blur,100,200)
	cv2.namedWindow("canny")
	cv2.imshow("canny", edges)
	contours, hierarchy = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	height, width = gray.shape
	contours_img=np.zeros((height, width, 1),np.uint8)
	for cnt in contours:
		if (cv2.contourArea(cnt) > 700):
			print cv2.contourArea(cnt)
			cv2.drawContours(contours_img, [cnt], 0,255,4) 
	cv2.namedWindow("edges")
	cv2.imshow("edges", contours_img)

	circles = cv2.HoughCircles(contours_img, cv2.HOUGH_GRADIENT, 1.2, 20,param1 = 50, 
               param2 = 30, minRadius = 10, maxRadius = 40)
if circles is not None and enable_hand:
		print (circles)
		circles = np.round(circles[0, :]).astype("int")
		for (x, y, r) in circles:
		# draw the circle in the output image, then draw a rectangle
		# corresponding to the center of the circle
			cv2.circle(cv2_img, (x, y), r, (0, 255, 0), 4)
		
		if (r>100):
			px_m=0
		else:
			px_m=.06/r
		tf_broadcaster.sendTransform(
		(   (x-goal_hole[0])*.5*px_m,(y-goal_hole[1])*.5*px_m, 0.15),tf.transformations.quaternion_from_euler(3.1416, 0, 1.57),
		rospy.Time.now(),"chido","hand_palm_link")
		
		
		
		(trans,rot)=tf_listener.lookupTransform('my_frame_hole','chido',  rospy.Time(0))
		static_transformStamped = geometry_msgs.msg.TransformStamped()        
		static_transformStamped.header.stamp = rospy.Time.now()
		static_transformStamped.header.frame_id = "my_frame_hole"
		static_transformStamped.child_frame_id = "hole_reest"

		static_transformStamped.transform.translation.x = trans[0]
		static_transformStamped.transform.translation.y = trans[1]
		static_transformStamped.transform.translation.z = trans[2]

		quat = tf.transformations.quaternion_from_euler(
				   float(3.1416),float(0),float(1.57))
		static_transformStamped.transform.rotation.x = rot[0]
		static_transformStamped.transform.rotation.y = rot[1]
		static_transformStamped.transform.rotation.z = rot[2]
		static_transformStamped.transform.rotation.w = rot[3]
		
		tf2_broadcaster.sendTransform(static_transformStamped)
		
	
	
		
		#tf_broadcaster.sendTransform((x-goal_hole[0])*px_m, (y-goal_hole[1])*px_m, 0),
	   
		 
		  
		  
#################  
		  
#	cv2.namedWindow("hand_cam")
#	
#	cv2.imshow("hand_cam", cv2_img)    
#	k = cv2.waitKey(100)
#	k=False
#	if k & 0xFF == ord('q'):
#		# q key pressed so quit
#		print("Quitting...")
#		kill_node=True
#		cv2.destroyAllWindows()
#		exit()
#
#	elif k & 0xFF == ord('c'):
#		# c key pressed so capture frame to image file
#		cap_cnt=0
#		cap_name = "capture_{}.png".format(cap_cnt)
#		cv2.imwrite(cap_name, cv2_img)
#		print("Saving {}!".format(cap_name))
		
def callback_xtion(img_msg):
   
	global enable_xtion
	tf_broadcaster=tf.TransformBroadcaster()
	tf2_broadcaster=tf2_ros.StaticTransformBroadcaster()
	(trans,rot)=tf_listener.lookupTransform('head_rgbd_sensor_rgb_frame', 'map', rospy.Time(0))
	
	goal_hole=np.array((258,261))
   
################################################################ DO THINGS HERE
	cv2_img = bridge.imgmsg_to_cv2(img_msg, "bgr8")
	gray = cv2.cvtColor(cv2_img,cv2.COLOR_BGR2GRAY)
	radius = 4
	num_corners=4
	"""   
	corners=cv2.goodFeaturesToTrack(gray,num_corners,.01,10)
	for i in range(corners.shape[0]):
		cv2.circle(cv2_img, (corners[i,0,0], corners[i,0,1]), radius, (200,0,200), cv2.FILLED)
	orb = cv2.ORB_create()
	kp = orb.detect(cv2_img,None)
	
	kp, des = orb.compute(cv2_img, kp)
	img2 = cv2.drawKeypoints(cv2_img, kp, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

   
	
	
   # np.save('imagen.npy',cv2_img)

	"""
	circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1.5, 45)
	if circles is not None and enable_xtion:
		print (enable_xtion)
		print (circles)
		circles = np.round(circles[0, :]).astype("int")
		for (x, y, r) in circles:
		# draw the circle in the output image, then draw a rectangle
		# corresponding to the center of the circle
			cv2.circle(cv2_img, (x, y), r, (0, 255, 0), 4)
		
		if (r>100):
			px_m=0
		else:
			px_m=.06/r
		tf_broadcaster.sendTransform(
		(   (x-goal_hole[0])*.5*px_m,(y-goal_hole[1])*.5*px_m, 0.52),tf.transformations.quaternion_from_euler(1.57-1.2,3.1416,0),
		rospy.Time.now(),"chido","head_rgbd_sensor_rgb_frame"     
		)
		
		
		
		(trans,rot)=tf_listener.lookupTransform('my_frame_hole','chido',  rospy.Time(0))
		static_transformStamped = geometry_msgs.msg.TransformStamped()        
		static_transformStamped.header.stamp = rospy.Time.now()
		static_transformStamped.header.frame_id = "my_frame_hole"
		static_transformStamped.child_frame_id = "hole_reest"

		static_transformStamped.transform.translation.x = trans[0]
		static_transformStamped.transform.translation.y = trans[1]
		static_transformStamped.transform.translation.z = trans[2]

		quat = tf.transformations.quaternion_from_euler(
				   float(3.1416),float(0),float(1.57))
		static_transformStamped.transform.rotation.x = rot[0]
		static_transformStamped.transform.rotation.y = rot[1]
		static_transformStamped.transform.rotation.z = rot[2]
		static_transformStamped.transform.rotation.w = rot[3]
		
		tf2_broadcaster.sendTransform(static_transformStamped)
        pub.publish(str(x)+','+str(y)+','+str(r))
		
	
	
		
		#tf_broadcaster.sendTransform((x-goal_hole[0])*px_m, (y-goal_hole[1])*px_m, 0),
	   
	   
		 
		  
		  
#################  
		  
	cv2.namedWindow("xtion")
	
	cv2.imshow("xtion", cv2_img)    
	k = cv2.waitKey(1)
	if k & 0xFF == ord('q'):
		# q key pressed so quit
		print("Quitting...")
		kill_node=True
		cv2.destroyAllWindows()
		exit()

	elif k & 0xFF == ord('c'):
		# c key pressed so capture frame to image file
		cap_cnt=0
		cap_name = "capture_{}.png".format(cap_cnt)
		cv2.imwrite(cap_name, cv2_img)
		print("Saving {}!".format(cap_name))

	
	
	
def listener():

	# In ROS, nodes are uniquely named. If two nodes with the same
	# name are launched, the previous one is kicked off. The
	# anonymous=True flag means that rospy will choose a unique
	# name for our 'listener' node so that multiple listeners can
	# run simultaneously.
	global tf_listener,pub
	rospy.init_node('hand_camera_listener', anonymous=True)
	
	rospy.on_shutdown(shutdown)
	tf_listener = tf.TransformListener()
	
	pub=rospy.Publisher ("circles",String,queue_size=10)
	rospy.Subscriber("/hsrb/hand_camera/image_raw", Image, callback_hand)
	rospy.Subscriber("/hsrb/head_rgbd_sensor/rgb/image_raw", Image, callback_xtion)
	rospy.Subscriber("vision/circle_detector/hand/enable", Bool, callBackEnable_hand)
	rospy.Subscriber("vision/circle_detector/xtion/enable", Bool, callBackEnable_xtion)
	rospy.spin()
	


if __name__ == '__main__':
	  
	listener()
	