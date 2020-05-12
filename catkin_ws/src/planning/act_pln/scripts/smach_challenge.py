#!/usr/bin/env python

import rospy
import smach
from hsrb_interface import Robot
from hsrb_interface import collision_world
import hsrb_interface
import rospy
import sys
import math
import tf
import tf2_ros
import tf2_geometry_msgs
from hsrb_interface import geometry
from geometry_msgs.msg import PoseStamped, Point
import geometry_msgs
from vision_msgs.srv import Yolov3_detector
from std_msgs.msg import Int32, Bool
from vision_msgs.msg import VisionObject, ObjectCoordinatesForDetection
import numpy as np
import os
from takeshi_tools.nav_tool_lib import nav_module

##################INITIA
robot = Robot()
#base = robot.try_get('omni_base')
base = nav_module("hsr")
tts = robot.try_get('default_tts')
whole_body = robot.try_get('whole_body')
gripper=robot.try_get('gripper')
collision= collision_world.CollisionWorld('global_collision_world')
#tf_broadcaster=tf.TransformBroadcaster()
tf_listener = tf.TransformListener()
tf_broadcaster=tf2_ros.StaticTransformBroadcaster()
#tf_buffer = robot._get_tf2_buffer()

global turn_rigth
turn_rigth=True

def detect_yolo_foo(timeout):
    objectCoordinates=ObjectCoordinatesForDetection()
    objectCoordinates.x_min=-1.0;
    objectCoordinates.x_max=2.0;
    objectCoordinates.y_min=-1.0;
    objectCoordinates.y_max=1.0;
    objectCoordinates.z_min=0.0;
    objectCoordinates.z_max=2.0;

    timeout_msg=Int32()
    timeout_msg.data=timeout
    try:
        yolo_detection=rospy.ServiceProxy('/vision/yolov3_detector/detect_all_yolo_objects',Yolov3_detector)
        recognizedYoloObjects=yolo_detection(timeout_msg,objectCoordinates)
        #print recognizedYoloObjects.recognizedYoloObjects
        return recognizedYoloObjects.recognizedYoloObjects
    except rospy.ServiceException, e:
        print "service call failled: %s"%e
        return False

def detect_yolo_hand_foo(timeout):
    objectCoordinates=ObjectCoordinatesForDetection()
    objectCoordinates.x_min=-1.0;
    objectCoordinates.x_max=2.0;
    objectCoordinates.y_min=-1.0;
    objectCoordinates.y_max=1.0;
    objectCoordinates.z_min=0.0;
    objectCoordinates.z_max=2.0;

    timeout_msg=Int32()
    timeout_msg.data=timeout



    try:
        yolo_detection=rospy.ServiceProxy('vision/yolov3_detector/detect_all_yolo_objects_with_arm_camera',Yolov3_detector)
        recognizedYoloObjects=yolo_detection(timeout_msg,objectCoordinates)
        #print recognizedYoloObjects.recognizedYoloObjects
        return recognizedYoloObjects.recognizedYoloObjects
    except rospy.ServiceException, e:
        print "service call failled: %s"%e
        return False

def enable_circle_hand(var):
    loop=rospy.Rate(10)
    msg=Bool()
    pub=rospy.Publisher("vision/circle_detector/hand/enable", Bool, queue_size=10)
    msg.data=var
    for i in range(5):
        pub.publish(msg)
        loop.sleep()
        rospy.sleep(5.)
    x=rospy.Duration.from_sec(2.5)
    rospy.sleep(x)

def enable_circle_xtion(var):
    loop=rospy.Rate(10)
    msg=Bool()
    pub=rospy.Publisher("vision/circle_detector/xtion/enable", Bool, queue_size=10)
    msg.data=var
    for i in range(5):
        pub.publish(msg)
        loop.sleep()
        #rospy.sleep(5.)
    x=rospy.Duration.from_sec(1)
    rospy.sleep(x)

#class ETERNAL_YOLO
class eternal_yolo(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1'])
    
    def execute(self,userdata):
        rospy.loginfo('State : ETERNAL_YOLO')
        recognizedYoloObjects=detect_yolo_foo(4000)
        #recognizedYoloObjects=detect_yolo_hand_foo(4000)
        print "number of objects detected"
        print (len(recognizedYoloObjects))
        
        if (len(recognizedYoloObjects) >0):
            self.found=True
            print ('closest', recognizedYoloObjects[0].id)
            print (recognizedYoloObjects[0].bounding_box.ymin,recognizedYoloObjects[0].bounding_box.ymax,recognizedYoloObjects[0].bounding_box.xmax,recognizedYoloObjects[0].bounding_box.xmin)


            static_transformStamped = geometry_msgs.msg.TransformStamped()        
            static_transformStamped.header.stamp = rospy.Time.now()
            static_transformStamped.header.frame_id = "base_link"
            static_transformStamped.child_frame_id = recognizedYoloObjects[0].id

            static_transformStamped.transform.translation.x = recognizedYoloObjects[0].pose.position.x
            static_transformStamped.transform.translation.y = recognizedYoloObjects[0].pose.position.y
            static_transformStamped.transform.translation.z = recognizedYoloObjects[0].pose.position.z
            quat = tf.transformations.quaternion_from_euler(
                       float(3.1416),float(0),float(1.57))
            static_transformStamped.transform.rotation.x = 0
            static_transformStamped.transform.rotation.y = 0
            static_transformStamped.transform.rotation.z = 0
            static_transformStamped.transform.rotation.w = 1
            
            tf_broadcaster.sendTransform(static_transformStamped)
            

        return 'outcome1'







# define state Initial State
class initial_state(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['gotoobject','notdetected','graspobject'])
        
    def execute(self,userdata):
        global closest_object
        tries=0
        rospy.loginfo('STATE : initial state')
        
                      
        collision.remove_all()
        collision.add_box(x=1.5, y=.9, z=0.55, pose=geometry.pose(x=7.7,y=4.34, z=0.6), frame_id='map')
        #whole_body.collision_world=collision

        
            
        
        
        #print (recognizedYoloObjects) 
        #base.go_rel(-0.2,0,0)
        #whole_body.move_end_effector_pose(geometry.pose(x=-.3,y=.3, z=.2,ei=3.1416),'my_frame_hole')
        #base.go_rel(0,0,.7)

        #whole_body.move_to_joint_positions({'arm_flex_joint': -2.08,                                'arm_lift_joint': 0.35,                                'arm_roll_joint': -1.57})
        whole_body.move_to_go()
        base.go_abs(6.1,4,0,20,"pumas" ) 
        whole_body.move_to_joint_positions({'arm_flex_joint':-1.32,'arm_lift_joint':0.68,'arm_roll_joint':0 })
        base.go_rel(0.3,0,0.6, 20, "pumas") 
        whole_body.gaze_point((0,0.3,-.20), 'my_frame_hole')
        whole_body.linear_weight=90
        while tries<5:
            tries=tries+1
            recognizedYoloObjects=detect_yolo_foo(4000)
            #recognizedYoloObjects=detect_yolo_hand_foo(4000)
            print "number of objects detected"
            print (len(recognizedYoloObjects))
    
            
            if (len(recognizedYoloObjects) >0):
                self.found=True
                print (recognizedYoloObjects[0].bounding_box.ymin,recognizedYoloObjects[0].bounding_box.ymax,recognizedYoloObjects[0].bounding_box.xmax,recognizedYoloObjects[0].bounding_box.xmin)
    
    
                static_transformStamped = geometry_msgs.msg.TransformStamped()        
                static_transformStamped.header.stamp = rospy.Time.now()
                static_transformStamped.header.frame_id = "base_link"
                static_transformStamped.child_frame_id = recognizedYoloObjects[0].id
    
                static_transformStamped.transform.translation.x = recognizedYoloObjects[0].pose.position.x
                static_transformStamped.transform.translation.y = recognizedYoloObjects[0].pose.position.y
                static_transformStamped.transform.translation.z = recognizedYoloObjects[0].pose.position.z
                quat = tf.transformations.quaternion_from_euler(
                           float(3.1416),float(0),float(1.57))
                static_transformStamped.transform.rotation.x = 0
                static_transformStamped.transform.rotation.y = 0
                static_transformStamped.transform.rotation.z = 0
                static_transformStamped.transform.rotation.w = 1
                
                tf_broadcaster.sendTransform(static_transformStamped)
    
                #whole_body.move_to_go()
                
                print('goinG to ',recognizedYoloObjects[0].id)
                closest_object=recognizedYoloObjects[0].id
                whole_body.move_to_joint_positions({'head_tilt_joint':0,'head_pan_joint':0})
    
    
                #whole_body.move_to_neutral()
    
    
    
                whole_body.move_end_effector_pose(geometry.pose(z=.15,ei=3.1416,ek=-1.57), recognizedYoloObjects[0].id)
                if (recognizedYoloObjects[0].id== 'pinkSpoon' or recognizedYoloObjects[0].id== 'pinkFork'):
                    return 'gotoobject'
                else:
                    return'graspobject'

        
            







            """ tf_broadcaster.sendTransform(
               (recognizedYoloObjects[0].pose.position.x, recognizedYoloObjects[0].pose.position.y, recognizedYoloObjects[0].pose.position.z) 
               ,tf.transformations.quaternion_from_euler(0, 0, 0),
                rospy.Time.now(),recognizedYoloObjects[0].id,"base_link"   )"""
        #whole_body.move_to_go() 

# 
#
        
        
        return 'notdetected'
        


# define state go to hole
class go_to_table(smach.State):
    def __init__(self):

        smach.State.__init__(self,outcomes=['outcome1','outcome2'])
        self.found=False
    
    def execute(self,userdata):
        rospy.loginfo('State : go to table')

       


#class reestimate_hole 
class reestimate_hole(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1','outcome2'])
        self.visited=False
    
    def execute(self,userdata):
        rospy.loginfo('State : reestimate_hole')
       
        if self.visited:
            return 'outcome2'
        else:
            
            self.visited = True

            return 'outcome1'


#class ANCHOR_BODY
class anchor_body(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1'])
    
    def execute(self,userdata):
        rospy.loginfo('State : ANCHOR_BODY')
       
        return 'outcome1'


class grasp(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['graspable','notgraspable','notdetected'])

    
#    def execute(self,userdata):
#        rospy.loginfo('State : GRASP')
#        #whole_body.move_to_joint_positions({'wrist_roll_joint':0})
#        gripper.set_distance(.8,1)
#        curr=whole_body.joint_positions['wrist_roll_joint']  

#        recognizedYoloObjects=detect_yolo_hand_foo(4000)
#        if (len(recognizedYoloObjects) >0):
#            deltax,deltay=(float)(recognizedYoloObjects[0].bounding_box.xmax-recognizedYoloObjects[0].bounding_box.xmin),(float)(recognizedYoloObjects[0].bounding_box.ymax-recognizedYoloObjects[0].bounding_box.ymin)
#            print('x,y',((float)(deltay/deltax)))
#            est_ori= np.arctan(deltay/deltax)
#            print(est_ori)
#            if (np.abs(est_ori)<.3):
#                print("Graspable")
#                return 'graspable'
#            else:
#                print('not grapsable.. realigning')
#                if(curr+.5*est_ori >2.7):
#                    return 'notgraspable'
#
#                whole_body.move_to_joint_positions({'wrist_roll_joint':curr+.5*est_ori})
#                return 'notgraspable'
    def execute(self,userdata):
        #print (closest_object)
        global turn_rigth
        rospy.loginfo('State : GRASP')
        #whole_body.move_to_joint_positions({'wrist_roll_joint':0})
        gripper.set_distance(.6,1)
        curr=whole_body.joint_positions['wrist_roll_joint']  

        recognizedYoloObjects=detect_yolo_hand_foo(4000)
        if (len(recognizedYoloObjects) >0):
            deltax,deltay=(float)(recognizedYoloObjects[0].bounding_box.xmax-recognizedYoloObjects[0].bounding_box.xmin),(float)(recognizedYoloObjects[0].bounding_box.ymax-recognizedYoloObjects[0].bounding_box.ymin)
            print('x,y',((float)(deltay/deltax)))
            est_ori= np.arctan(deltay/deltax)
            print "ori"+str(est_ori)
            print "curr"+str(curr)
            if (np.abs(est_ori)<0.4):
                print("Graspable")
                return 'graspable'
            else:
                print('not grapsable.. realigning')
                if turn_rigth:
                    print "turn rigth"
                    if curr>=2:
                        turn_rigth=False
                        curr=0
                        print "new"+str(curr)
                        whole_body.move_to_joint_positions({'wrist_roll_joint':curr})
                        return 'notgraspable'
                    else:
                        curr=curr+(0.5*est_ori)
                        print "new"+str(curr)
                        whole_body.move_to_joint_positions({'wrist_roll_joint':curr})
                        return 'notgraspable'


                else:
                    print "turn left"   
                    if curr<=-2:
                        urn_rigth=True
                        curr=0
                        print "new"+str(curr)
                        whole_body.move_to_joint_positions({'wrist_roll_joint':curr})
                        return 'notgraspable'

                    else:
                        curr=curr-(0.5*est_ori)
                        print "new"+str(curr)
                        whole_body.move_to_joint_positions({'wrist_roll_joint':curr})
                        return 'notgraspable'
        else:
            whole_body.move_to_joint_positions({'wrist_roll_joint':0})
            if(turn_rigth):
                turn_rigth=False
            else:
                turn_rigth=True
            return 'notgraspable'

    
#    def execute(self,userdata):
#        rospy.loginfo('State : GRASP')
#        #whole_body.move_to_joint_positions({'wrist_roll_joint':0})
#        gripper.set_distance(.8,1)
#        curr=whole_body.joint_positions['wrist_roll_joint']  

#        recognizedYoloObjects=detect_yolo_hand_foo(4000)
#        if (len(recognizedYoloObjects) >0):
#            deltax,deltay=(float)(recognizedYoloObjects[0].bounding_box.xmax-recognizedYoloObjects[0].bounding_box.xmin),(float)(recognizedYoloObjects[0].bounding_box.ymax-recognizedYoloObjects[0].bounding_box.ymin)
#            print('x,y',((float)(deltay/deltax)))
#            est_ori= np.arctan(deltay/deltax)
#            print(est_ori)
#            if (np.abs(est_ori)<.3):
#                print("Graspable")
#                return 'graspable'
#            else:
#                print('not grapsable.. realigning')
#                if(curr+.5*est_ori >2.7):
#                    return 'notgraspable'
#
#                whole_body.move_to_joint_positions({'wrist_roll_joint':curr+.5*est_ori})
#                return 'notgraspable'
"""    def execute(self,userdata):
        global turn_rigth
        rospy.loginfo('State : GRASP')
        #whole_body.move_to_joint_positions({'wrist_roll_joint':0})
        gripper.set_distance(.6,1)
        curr=whole_body.joint_positions['wrist_roll_joint']  

        recognizedYoloObjects=detect_yolo_hand_foo(4000)
        if (len(recognizedYoloObjects) >0):
            deltax,deltay=(float)(recognizedYoloObjects[0].bounding_box.xmax-recognizedYoloObjects[0].bounding_box.xmin),(float)(recognizedYoloObjects[0].bounding_box.ymax-recognizedYoloObjects[0].bounding_box.ymin)
            print('x,y',((float)(deltay/deltax)))
            est_ori= np.arctan(deltay/deltax)
            print "ori"+str(est_ori)
            print "curr"+str(curr)
            if (np.abs(est_ori)<0.3):
                print("Graspable")
                return 'graspable'
            else:
                print('not grapsable.. realigning')
                if turn_rigth:
                    print "turn rigth"
                    if curr>=1.8:
                        turn_rigth=False
                        curr=0
                        print "new"+str(curr)
                        whole_body.move_to_joint_positions({'wrist_roll_joint':curr})
                        return 'notgraspable'
                    else:
                        curr=curr+(0.5*est_ori)
                        print "new"+str(curr)
                        whole_body.move_to_joint_positions({'wrist_roll_joint':curr})
                        return 'notgraspable'


                else:
                    print "turn left"   
                    if curr<=-1.8:
                        urn_rigth=True
                        curr=0
                        print "new"+str(curr)
                        whole_body.move_to_joint_positions({'wrist_roll_joint':curr})
                        return 'notgraspable'

                    else:
                        curr=curr-(0.5*est_ori)
                        print "new"+str(curr)
                        whole_body.move_to_joint_positions({'wrist_roll_joint':curr})
                        return 'notgraspable'
        else:
            return 'notdetected'                    
"""
                         
class exec_grasp(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1'])
    
    def execute(self,userdata):
        rospy.loginfo('State : EXEC_GRASP')
        whole_body.impedance_config = 'grasping'
        #whole_body.move_to_joint_positions({'wrist_roll_joint':0})
        gripper.set_distance(.8,1)
        whole_body.move_end_effector_by_line((0,0,1),.11)
        gripper.apply_force(.8)
        whole_body.move_end_effector_by_line((1,0,1),-.08)
        whole_body.impedance_config = None
        #whole_body.move_to_go()
        return 'outcome1'  

class find_circle(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1'])
    
    def execute(self,userdata):
        rospy.loginfo('State : FIND_CIRCLE')
        whole_body.linear_weight=90
        base.go_abs(6.55,3.44,-1.43,20,"pumas" )
        whole_body.move_to_joint_positions({'arm_flex_joint': -0.8094775280188853,'arm_lift_joint': 0.4044679367584029,'head_tilt_joint': -1.20003092728992})
        enable_circle_xtion(True)
        print('ant3es')
        rospy.sleep(4.)
        print ('later')
        enable_circle_xtion(False)
        whole_body.move_end_effector_pose(geometry.pose(z=.2,ei=3.1416, ej=-1.57,ek=-1.57), 'hole_reest')
        return 'outcome1'


class go_to_trash(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1'])
    
    def execute(self,userdata):
        rospy.loginfo('State : GO_TO_TRASH')
        
        whole_body.move_to_joint_positions({'arm_flex_joint': -0.8094775280188853,'arm_lift_joint': 0.4044679367584029,'head_pan_joint': -0.8998789015469959,'head_tilt_joint': -1.20003092728992})
        whole_body.move_end_effector_pose(geometry.pose(y=-.05,z=.19,ei=3.1416,ek=-1.57), 'trash')
        enable_circle_xtion(False)
        #gripper.apply_force(.4)
        return 'outcome1'


class place_trash_grasped_above(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['outcome1'])
    
    def execute(self,userdata):
        rospy.loginfo('State : PLACE_TRASH_GRASPED_ABOVE')
        base.go_rel(-0.35,0,0,10,"pumas")
        whole_body.move_to_go()
        whole_body.move_end_effector_pose(geometry.pose(ei=3.1416, ej=-1.57,ek=-1.57), 'trash')
        whole_body.move_end_effector_pose(geometry.pose(ei=3.1416, ej=-1.57,ek=-1.57), 'trash')
        whole_body.move_end_effector_by_line((-1,0,0),.1)
        gripper.set_distance(.8,.1)
        whole_body.move_end_effector_by_line((1,0,-1),.08)
        gripper.set_distance(.01,.1)
        whole_body.move_to_go()


       
        #whole_body.move_end_effector_pose(geometry.pose(y=-.08,z=.19,ei=3.1416,ej=-1.57,ek=1.57), 'hole_reest')

        
        return 'outcome1'        
def main():
    #rospy.init_node('hsrb_challenge')
    sm=smach.StateMachine(outcomes=['END'])
    
    with sm:
        smach.StateMachine.add('INITIAL', initial_state(),transitions={'notdetected': 'INITIAL', 'gotoobject':'GRASP','graspobject':'EXEC_GRASP'})
        smach.StateMachine.add('FIND_CIRCLE',find_circle(),transitions={'outcome1':'END'})
        smach.StateMachine.add('PLACE_TRASH_GRASPED_ABOVE',place_trash_grasped_above(),transitions={'outcome1':'INITIAL'})
        smach.StateMachine.add('ETERNAL_YOLO',eternal_yolo(),transitions={'outcome1':'ETERNAL_YOLO'})
        smach.StateMachine.add('GO_TO_TRASH',go_to_trash(),transitions={'outcome1':'GO_TO_TRASH'})
        smach.StateMachine.add('GRASP',grasp(),transitions={'graspable':'EXEC_GRASP', 'notgraspable':'GRASP','notdetected':'GRASP'})
        smach.StateMachine.add('EXEC_GRASP',exec_grasp(),transitions={'outcome1':'PLACE_TRASH_GRASPED_ABOVE'})
        smach.StateMachine.add('GO_TO_TABLE',go_to_table(), transitions={'outcome1':'GO_TO_TABLE','outcome2':'GO_TO_TABLE'})
        smach.StateMachine.add('REESTIMATE_HOLE_TF',reestimate_hole(),transitions={'outcome1':'ANCHOR_BODY','outcome2':'END'})
        smach.StateMachine.add('ANCHOR_BODY',anchor_body(),transitions={'outcome1':'ANCHOR_BODY'})

             
    
    outcome= sm.execute()
if __name__== '__main__':
    main()