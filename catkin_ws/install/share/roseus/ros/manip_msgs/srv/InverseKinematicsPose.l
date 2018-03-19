;; Auto-generated. Do not edit!


(when (boundp 'manip_msgs::InverseKinematicsPose)
  (if (not (find-package "MANIP_MSGS"))
    (make-package "MANIP_MSGS"))
  (shadow 'InverseKinematicsPose (find-package "MANIP_MSGS")))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSPOSE")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSPOSE"))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSPOSEREQUEST")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSPOSEREQUEST"))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSPOSERESPONSE")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSPOSERESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass manip_msgs::InverseKinematicsPoseRequest
  :super ros::object
  :slots (_cartesian_pose ))

(defmethod manip_msgs::InverseKinematicsPoseRequest
  (:init
   (&key
    ((:cartesian_pose __cartesian_pose) (instance geometry_msgs::Pose :init))
    )
   (send-super :init)
   (setq _cartesian_pose __cartesian_pose)
   self)
  (:cartesian_pose
   (&rest __cartesian_pose)
   (if (keywordp (car __cartesian_pose))
       (send* _cartesian_pose __cartesian_pose)
     (progn
       (if __cartesian_pose (setq _cartesian_pose (car __cartesian_pose)))
       _cartesian_pose)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose _cartesian_pose
    (send _cartesian_pose :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose _cartesian_pose
       (send _cartesian_pose :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose _cartesian_pose
     (send _cartesian_pose :deserialize buf ptr-) (incf ptr- (send _cartesian_pose :serialization-length))
   ;;
   self)
  )

(defclass manip_msgs::InverseKinematicsPoseResponse
  :super ros::object
  :slots (_articular_pose ))

(defmethod manip_msgs::InverseKinematicsPoseResponse
  (:init
   (&key
    ((:articular_pose __articular_pose) (instance std_msgs::Float32MultiArray :init))
    )
   (send-super :init)
   (setq _articular_pose __articular_pose)
   self)
  (:articular_pose
   (&rest __articular_pose)
   (if (keywordp (car __articular_pose))
       (send* _articular_pose __articular_pose)
     (progn
       (if __articular_pose (setq _articular_pose (car __articular_pose)))
       _articular_pose)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32MultiArray _articular_pose
    (send _articular_pose :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32MultiArray _articular_pose
       (send _articular_pose :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32MultiArray _articular_pose
     (send _articular_pose :deserialize buf ptr-) (incf ptr- (send _articular_pose :serialization-length))
   ;;
   self)
  )

(defclass manip_msgs::InverseKinematicsPose
  :super ros::object
  :slots ())

(setf (get manip_msgs::InverseKinematicsPose :md5sum-) "1760e4c67453e0f01e66004e3b3191b6")
(setf (get manip_msgs::InverseKinematicsPose :datatype-) "manip_msgs/InverseKinematicsPose")
(setf (get manip_msgs::InverseKinematicsPose :request) manip_msgs::InverseKinematicsPoseRequest)
(setf (get manip_msgs::InverseKinematicsPose :response) manip_msgs::InverseKinematicsPoseResponse)

(defmethod manip_msgs::InverseKinematicsPoseRequest
  (:response () (instance manip_msgs::InverseKinematicsPoseResponse :init)))

(setf (get manip_msgs::InverseKinematicsPoseRequest :md5sum-) "1760e4c67453e0f01e66004e3b3191b6")
(setf (get manip_msgs::InverseKinematicsPoseRequest :datatype-) "manip_msgs/InverseKinematicsPoseRequest")
(setf (get manip_msgs::InverseKinematicsPoseRequest :definition-)
      "geometry_msgs/Pose cartesian_pose

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
std_msgs/Float32MultiArray articular_pose










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

(setf (get manip_msgs::InverseKinematicsPoseResponse :md5sum-) "1760e4c67453e0f01e66004e3b3191b6")
(setf (get manip_msgs::InverseKinematicsPoseResponse :datatype-) "manip_msgs/InverseKinematicsPoseResponse")
(setf (get manip_msgs::InverseKinematicsPoseResponse :definition-)
      "geometry_msgs/Pose cartesian_pose

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
std_msgs/Float32MultiArray articular_pose










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



(provide :manip_msgs/InverseKinematicsPose "1760e4c67453e0f01e66004e3b3191b6")


