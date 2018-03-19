;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::Skeletons)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'Skeletons (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::SKELETONS")
  (make-package "VISION_MSGS::SKELETONS"))

(in-package "ROS")
;;//! \htmlinclude Skeletons.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::Skeletons
  :super ros::object
  :slots (_header _skeletons ))

(defmethod vision_msgs::Skeletons
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:skeletons __skeletons) (let (r) (dotimes (i 0) (push (instance vision_msgs::Skeleton :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _skeletons __skeletons)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:skeletons
   (&rest __skeletons)
   (if (keywordp (car __skeletons))
       (send* _skeletons __skeletons)
     (progn
       (if __skeletons (setq _skeletons (car __skeletons)))
       _skeletons)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; vision_msgs/Skeleton[] _skeletons
    (apply #'+ (send-all _skeletons :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; vision_msgs/Skeleton[] _skeletons
     (write-long (length _skeletons) s)
     (dolist (elem _skeletons)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; vision_msgs/Skeleton[] _skeletons
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _skeletons (let (r) (dotimes (i n) (push (instance vision_msgs::Skeleton :init) r)) r))
     (dolist (elem- _skeletons)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get vision_msgs::Skeletons :md5sum-) "234171c21eb8e829a5bd64c12d7b744b")
(setf (get vision_msgs::Skeletons :datatype-) "vision_msgs/Skeletons")
(setf (get vision_msgs::Skeletons :definition-)
      "std_msgs/Header header
vision_msgs/Skeleton[] skeletons
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: vision_msgs/Skeleton
int32 user_id
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



(provide :vision_msgs/Skeletons "234171c21eb8e829a5bd64c12d7b744b")


