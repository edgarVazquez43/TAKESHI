;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::Skeleton)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'Skeleton (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::SKELETON")
  (make-package "VISION_MSGS::SKELETON"))

(in-package "ROS")
;;//! \htmlinclude Skeleton.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass vision_msgs::Skeleton
  :super ros::object
  :slots (_user_id _ref_point _joints ))

(defmethod vision_msgs::Skeleton
  (:init
   (&key
    ((:user_id __user_id) 0)
    ((:ref_point __ref_point) (instance geometry_msgs::Point32 :init))
    ((:joints __joints) (let (r) (dotimes (i 0) (push (instance vision_msgs::SkeletonJoint :init) r)) r))
    )
   (send-super :init)
   (setq _user_id (round __user_id))
   (setq _ref_point __ref_point)
   (setq _joints __joints)
   self)
  (:user_id
   (&optional __user_id)
   (if __user_id (setq _user_id __user_id)) _user_id)
  (:ref_point
   (&rest __ref_point)
   (if (keywordp (car __ref_point))
       (send* _ref_point __ref_point)
     (progn
       (if __ref_point (setq _ref_point (car __ref_point)))
       _ref_point)))
  (:joints
   (&rest __joints)
   (if (keywordp (car __joints))
       (send* _joints __joints)
     (progn
       (if __joints (setq _joints (car __joints)))
       _joints)))
  (:serialization-length
   ()
   (+
    ;; int32 _user_id
    4
    ;; geometry_msgs/Point32 _ref_point
    (send _ref_point :serialization-length)
    ;; vision_msgs/SkeletonJoint[] _joints
    (apply #'+ (send-all _joints :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _user_id
       (write-long _user_id s)
     ;; geometry_msgs/Point32 _ref_point
       (send _ref_point :serialize s)
     ;; vision_msgs/SkeletonJoint[] _joints
     (write-long (length _joints) s)
     (dolist (elem _joints)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _user_id
     (setq _user_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; geometry_msgs/Point32 _ref_point
     (send _ref_point :deserialize buf ptr-) (incf ptr- (send _ref_point :serialization-length))
   ;; vision_msgs/SkeletonJoint[] _joints
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _joints (let (r) (dotimes (i n) (push (instance vision_msgs::SkeletonJoint :init) r)) r))
     (dolist (elem- _joints)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get vision_msgs::Skeleton :md5sum-) "5f2d8c1c74d0773f8fb9581c67ba2f2a")
(setf (get vision_msgs::Skeleton :datatype-) "vision_msgs/Skeleton")
(setf (get vision_msgs::Skeleton :definition-)
      "int32 user_id
geometry_msgs/Point32 ref_point
vision_msgs/SkeletonJoint[] joints

================================================================================
MSG: geometry_msgs/Point32
# This contains the position of a point in free space(with 32 bits of precision).
# It is recommeded to use Point wherever possible instead of Point32.  
# 
# This recommendation is to promote interoperability.  
#
# This message is designed to take up less space when sending
# lots of points at once, as in the case of a PointCloud.  

float32 x
float32 y
float32 z
================================================================================
MSG: vision_msgs/SkeletonJoint
std_msgs/String name_joint
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



(provide :vision_msgs/Skeleton "5f2d8c1c74d0773f8fb9581c67ba2f2a")


