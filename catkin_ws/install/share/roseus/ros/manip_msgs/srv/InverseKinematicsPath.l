;; Auto-generated. Do not edit!


(when (boundp 'manip_msgs::InverseKinematicsPath)
  (if (not (find-package "MANIP_MSGS"))
    (make-package "MANIP_MSGS"))
  (shadow 'InverseKinematicsPath (find-package "MANIP_MSGS")))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSPATH")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSPATH"))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSPATHREQUEST")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSPATHREQUEST"))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSPATHRESPONSE")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSPATHRESPONSE"))

(in-package "ROS")

(if (not (find-package "NAV_MSGS"))
  (ros::roseus-add-msgs "nav_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass manip_msgs::InverseKinematicsPathRequest
  :super ros::object
  :slots (_cartesian_path ))

(defmethod manip_msgs::InverseKinematicsPathRequest
  (:init
   (&key
    ((:cartesian_path __cartesian_path) (instance nav_msgs::Path :init))
    )
   (send-super :init)
   (setq _cartesian_path __cartesian_path)
   self)
  (:cartesian_path
   (&rest __cartesian_path)
   (if (keywordp (car __cartesian_path))
       (send* _cartesian_path __cartesian_path)
     (progn
       (if __cartesian_path (setq _cartesian_path (car __cartesian_path)))
       _cartesian_path)))
  (:serialization-length
   ()
   (+
    ;; nav_msgs/Path _cartesian_path
    (send _cartesian_path :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; nav_msgs/Path _cartesian_path
       (send _cartesian_path :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; nav_msgs/Path _cartesian_path
     (send _cartesian_path :deserialize buf ptr-) (incf ptr- (send _cartesian_path :serialization-length))
   ;;
   self)
  )

(defclass manip_msgs::InverseKinematicsPathResponse
  :super ros::object
  :slots (_articular_path ))

(defmethod manip_msgs::InverseKinematicsPathResponse
  (:init
   (&key
    ((:articular_path __articular_path) (let (r) (dotimes (i 0) (push (instance std_msgs::Float32MultiArray :init) r)) r))
    )
   (send-super :init)
   (setq _articular_path __articular_path)
   self)
  (:articular_path
   (&rest __articular_path)
   (if (keywordp (car __articular_path))
       (send* _articular_path __articular_path)
     (progn
       (if __articular_path (setq _articular_path (car __articular_path)))
       _articular_path)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32MultiArray[] _articular_path
    (apply #'+ (send-all _articular_path :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32MultiArray[] _articular_path
     (write-long (length _articular_path) s)
     (dolist (elem _articular_path)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32MultiArray[] _articular_path
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _articular_path (let (r) (dotimes (i n) (push (instance std_msgs::Float32MultiArray :init) r)) r))
     (dolist (elem- _articular_path)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass manip_msgs::InverseKinematicsPath
  :super ros::object
  :slots ())

(setf (get manip_msgs::InverseKinematicsPath :md5sum-) "a5c97a40ea2d6c552050c61cfc35f302")
(setf (get manip_msgs::InverseKinematicsPath :datatype-) "manip_msgs/InverseKinematicsPath")
(setf (get manip_msgs::InverseKinematicsPath :request) manip_msgs::InverseKinematicsPathRequest)
(setf (get manip_msgs::InverseKinematicsPath :response) manip_msgs::InverseKinematicsPathResponse)

(defmethod manip_msgs::InverseKinematicsPathRequest
  (:response () (instance manip_msgs::InverseKinematicsPathResponse :init)))

(setf (get manip_msgs::InverseKinematicsPathRequest :md5sum-) "a5c97a40ea2d6c552050c61cfc35f302")
(setf (get manip_msgs::InverseKinematicsPathRequest :datatype-) "manip_msgs/InverseKinematicsPathRequest")
(setf (get manip_msgs::InverseKinematicsPathRequest :definition-)
      "nav_msgs/Path cartesian_path

================================================================================
MSG: nav_msgs/Path
#An array of poses that represents a Path for a robot to follow
Header header
geometry_msgs/PoseStamped[] poses

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
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
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
---
std_msgs/Float32MultiArray[] articular_path













================================================================================
MSG: std_msgs/Float32MultiArray
# Please look at the MultiArrayLayout message definition for
# documentation on all multiarrays.

MultiArrayLayout  layout        # specification of data layout
float32[]         data          # array of data


================================================================================
MSG: std_msgs/MultiArrayLayout
# The multiarray declares a generic multi-dimensional array of a
# particular data type.  Dimensions are ordered from outer most
# to inner most.

MultiArrayDimension[] dim # Array of dimension properties
uint32 data_offset        # padding elements at front of data

# Accessors should ALWAYS be written in terms of dimension stride
# and specified outer-most dimension first.
# 
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]
#
# A standard, 3-channel 640x480 image with interleaved color channels
# would be specified as:
#
# dim[0].label  = \"height\"
# dim[0].size   = 480
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
# dim[1].label  = \"width\"
# dim[1].size   = 640
# dim[1].stride = 3*640 = 1920
# dim[2].label  = \"channel\"
# dim[2].size   = 3
# dim[2].stride = 3
#
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.

================================================================================
MSG: std_msgs/MultiArrayDimension
string label   # label of given dimension
uint32 size    # size of given dimension (in type units)
")

(setf (get manip_msgs::InverseKinematicsPathResponse :md5sum-) "a5c97a40ea2d6c552050c61cfc35f302")
(setf (get manip_msgs::InverseKinematicsPathResponse :datatype-) "manip_msgs/InverseKinematicsPathResponse")
(setf (get manip_msgs::InverseKinematicsPathResponse :definition-)
      "nav_msgs/Path cartesian_path

================================================================================
MSG: nav_msgs/Path
#An array of poses that represents a Path for a robot to follow
Header header
geometry_msgs/PoseStamped[] poses

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
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
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
---
std_msgs/Float32MultiArray[] articular_path













================================================================================
MSG: std_msgs/Float32MultiArray
# Please look at the MultiArrayLayout message definition for
# documentation on all multiarrays.

MultiArrayLayout  layout        # specification of data layout
float32[]         data          # array of data


================================================================================
MSG: std_msgs/MultiArrayLayout
# The multiarray declares a generic multi-dimensional array of a
# particular data type.  Dimensions are ordered from outer most
# to inner most.

MultiArrayDimension[] dim # Array of dimension properties
uint32 data_offset        # padding elements at front of data

# Accessors should ALWAYS be written in terms of dimension stride
# and specified outer-most dimension first.
# 
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]
#
# A standard, 3-channel 640x480 image with interleaved color channels
# would be specified as:
#
# dim[0].label  = \"height\"
# dim[0].size   = 480
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
# dim[1].label  = \"width\"
# dim[1].size   = 640
# dim[1].stride = 3*640 = 1920
# dim[2].label  = \"channel\"
# dim[2].size   = 3
# dim[2].stride = 3
#
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.

================================================================================
MSG: std_msgs/MultiArrayDimension
string label   # label of given dimension
uint32 size    # size of given dimension (in type units)
")



(provide :manip_msgs/InverseKinematicsPath "a5c97a40ea2d6c552050c61cfc35f302")


