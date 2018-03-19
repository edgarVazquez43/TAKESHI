;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::DetectGripper)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'DetectGripper (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::DETECTGRIPPER")
  (make-package "VISION_MSGS::DETECTGRIPPER"))
(unless (find-package "VISION_MSGS::DETECTGRIPPERREQUEST")
  (make-package "VISION_MSGS::DETECTGRIPPERREQUEST"))
(unless (find-package "VISION_MSGS::DETECTGRIPPERRESPONSE")
  (make-package "VISION_MSGS::DETECTGRIPPERRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass vision_msgs::DetectGripperRequest
  :super ros::object
  :slots ())

(defmethod vision_msgs::DetectGripperRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass vision_msgs::DetectGripperResponse
  :super ros::object
  :slots (_gripper_position ))

(defmethod vision_msgs::DetectGripperResponse
  (:init
   (&key
    ((:gripper_position __gripper_position) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _gripper_position __gripper_position)
   self)
  (:gripper_position
   (&rest __gripper_position)
   (if (keywordp (car __gripper_position))
       (send* _gripper_position __gripper_position)
     (progn
       (if __gripper_position (setq _gripper_position (car __gripper_position)))
       _gripper_position)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _gripper_position
    (send _gripper_position :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _gripper_position
       (send _gripper_position :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _gripper_position
     (send _gripper_position :deserialize buf ptr-) (incf ptr- (send _gripper_position :serialization-length))
   ;;
   self)
  )

(defclass vision_msgs::DetectGripper
  :super ros::object
  :slots ())

(setf (get vision_msgs::DetectGripper :md5sum-) "d04c5ffec643228db4185f8b85f803c4")
(setf (get vision_msgs::DetectGripper :datatype-) "vision_msgs/DetectGripper")
(setf (get vision_msgs::DetectGripper :request) vision_msgs::DetectGripperRequest)
(setf (get vision_msgs::DetectGripper :response) vision_msgs::DetectGripperResponse)

(defmethod vision_msgs::DetectGripperRequest
  (:response () (instance vision_msgs::DetectGripperResponse :init)))

(setf (get vision_msgs::DetectGripperRequest :md5sum-) "d04c5ffec643228db4185f8b85f803c4")
(setf (get vision_msgs::DetectGripperRequest :datatype-) "vision_msgs/DetectGripperRequest")
(setf (get vision_msgs::DetectGripperRequest :definition-)
      "
---
geometry_msgs/Point gripper_position


================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")

(setf (get vision_msgs::DetectGripperResponse :md5sum-) "d04c5ffec643228db4185f8b85f803c4")
(setf (get vision_msgs::DetectGripperResponse :datatype-) "vision_msgs/DetectGripperResponse")
(setf (get vision_msgs::DetectGripperResponse :definition-)
      "
---
geometry_msgs/Point gripper_position


================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")



(provide :vision_msgs/DetectGripper "d04c5ffec643228db4185f8b85f803c4")


