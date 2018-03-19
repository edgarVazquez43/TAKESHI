;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::SkeletonJoint)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'SkeletonJoint (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::SKELETONJOINT")
  (make-package "VISION_MSGS::SKELETONJOINT"))

(in-package "ROS")
;;//! \htmlinclude SkeletonJoint.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::SkeletonJoint
  :super ros::object
  :slots (_name_joint _position _orientation ))

(defmethod vision_msgs::SkeletonJoint
  (:init
   (&key
    ((:name_joint __name_joint) (instance std_msgs::String :init))
    ((:position __position) (instance geometry_msgs::Vector3 :init))
    ((:orientation __orientation) (instance geometry_msgs::Quaternion :init))
    )
   (send-super :init)
   (setq _name_joint __name_joint)
   (setq _position __position)
   (setq _orientation __orientation)
   self)
  (:name_joint
   (&rest __name_joint)
   (if (keywordp (car __name_joint))
       (send* _name_joint __name_joint)
     (progn
       (if __name_joint (setq _name_joint (car __name_joint)))
       _name_joint)))
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:orientation
   (&rest __orientation)
   (if (keywordp (car __orientation))
       (send* _orientation __orientation)
     (progn
       (if __orientation (setq _orientation (car __orientation)))
       _orientation)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/String _name_joint
    (send _name_joint :serialization-length)
    ;; geometry_msgs/Vector3 _position
    (send _position :serialization-length)
    ;; geometry_msgs/Quaternion _orientation
    (send _orientation :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/String _name_joint
       (send _name_joint :serialize s)
     ;; geometry_msgs/Vector3 _position
       (send _position :serialize s)
     ;; geometry_msgs/Quaternion _orientation
       (send _orientation :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/String _name_joint
     (send _name_joint :deserialize buf ptr-) (incf ptr- (send _name_joint :serialization-length))
   ;; geometry_msgs/Vector3 _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; geometry_msgs/Quaternion _orientation
     (send _orientation :deserialize buf ptr-) (incf ptr- (send _orientation :serialization-length))
   ;;
   self)
  )

(setf (get vision_msgs::SkeletonJoint :md5sum-) "cc5468d1135a7ad558e21de9fa6840a5")
(setf (get vision_msgs::SkeletonJoint :datatype-) "vision_msgs/SkeletonJoint")
(setf (get vision_msgs::SkeletonJoint :definition-)
      "std_msgs/String name_joint
geometry_msgs/Vector3 position
geometry_msgs/Quaternion orientation

================================================================================
MSG: std_msgs/String
string data

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

")



(provide :vision_msgs/SkeletonJoint "cc5468d1135a7ad558e21de9fa6840a5")


