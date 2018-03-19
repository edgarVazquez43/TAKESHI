;; Auto-generated. Do not edit!


(when (boundp 'manip_msgs::InverseKinematicsFloatArray)
  (if (not (find-package "MANIP_MSGS"))
    (make-package "MANIP_MSGS"))
  (shadow 'InverseKinematicsFloatArray (find-package "MANIP_MSGS")))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSFLOATARRAY")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSFLOATARRAY"))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSFLOATARRAYREQUEST")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSFLOATARRAYREQUEST"))
(unless (find-package "MANIP_MSGS::INVERSEKINEMATICSFLOATARRAYRESPONSE")
  (make-package "MANIP_MSGS::INVERSEKINEMATICSFLOATARRAYRESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass manip_msgs::InverseKinematicsFloatArrayRequest
  :super ros::object
  :slots (_cartesian_pose ))

(defmethod manip_msgs::InverseKinematicsFloatArrayRequest
  (:init
   (&key
    ((:cartesian_pose __cartesian_pose) (instance std_msgs::Float32MultiArray :init))
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
    ;; std_msgs/Float32MultiArray _cartesian_pose
    (send _cartesian_pose :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32MultiArray _cartesian_pose
       (send _cartesian_pose :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32MultiArray _cartesian_pose
     (send _cartesian_pose :deserialize buf ptr-) (incf ptr- (send _cartesian_pose :serialization-length))
   ;;
   self)
  )

(defclass manip_msgs::InverseKinematicsFloatArrayResponse
  :super ros::object
  :slots (_articular_pose _omni_base_correction ))

(defmethod manip_msgs::InverseKinematicsFloatArrayResponse
  (:init
   (&key
    ((:articular_pose __articular_pose) (instance std_msgs::Float32MultiArray :init))
    ((:omni_base_correction __omni_base_correction) (instance geometry_msgs::Pose2D :init))
    )
   (send-super :init)
   (setq _articular_pose __articular_pose)
   (setq _omni_base_correction __omni_base_correction)
   self)
  (:articular_pose
   (&rest __articular_pose)
   (if (keywordp (car __articular_pose))
       (send* _articular_pose __articular_pose)
     (progn
       (if __articular_pose (setq _articular_pose (car __articular_pose)))
       _articular_pose)))
  (:omni_base_correction
   (&rest __omni_base_correction)
   (if (keywordp (car __omni_base_correction))
       (send* _omni_base_correction __omni_base_correction)
     (progn
       (if __omni_base_correction (setq _omni_base_correction (car __omni_base_correction)))
       _omni_base_correction)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32MultiArray _articular_pose
    (send _articular_pose :serialization-length)
    ;; geometry_msgs/Pose2D _omni_base_correction
    (send _omni_base_correction :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32MultiArray _articular_pose
       (send _articular_pose :serialize s)
     ;; geometry_msgs/Pose2D _omni_base_correction
       (send _omni_base_correction :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32MultiArray _articular_pose
     (send _articular_pose :deserialize buf ptr-) (incf ptr- (send _articular_pose :serialization-length))
   ;; geometry_msgs/Pose2D _omni_base_correction
     (send _omni_base_correction :deserialize buf ptr-) (incf ptr- (send _omni_base_correction :serialization-length))
   ;;
   self)
  )

(defclass manip_msgs::InverseKinematicsFloatArray
  :super ros::object
  :slots ())

(setf (get manip_msgs::InverseKinematicsFloatArray :md5sum-) "5286aef9c86ebe7d94286a61bc7ebe60")
(setf (get manip_msgs::InverseKinematicsFloatArray :datatype-) "manip_msgs/InverseKinematicsFloatArray")
(setf (get manip_msgs::InverseKinematicsFloatArray :request) manip_msgs::InverseKinematicsFloatArrayRequest)
(setf (get manip_msgs::InverseKinematicsFloatArray :response) manip_msgs::InverseKinematicsFloatArrayResponse)

(defmethod manip_msgs::InverseKinematicsFloatArrayRequest
  (:response () (instance manip_msgs::InverseKinematicsFloatArrayResponse :init)))

(setf (get manip_msgs::InverseKinematicsFloatArrayRequest :md5sum-) "5286aef9c86ebe7d94286a61bc7ebe60")
(setf (get manip_msgs::InverseKinematicsFloatArrayRequest :datatype-) "manip_msgs/InverseKinematicsFloatArrayRequest")
(setf (get manip_msgs::InverseKinematicsFloatArrayRequest :definition-)
      "std_msgs/Float32MultiArray   cartesian_pose

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
---
std_msgs/Float32MultiArray   articular_pose
geometry_msgs/Pose2D 	     omni_base_correction
















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
uint32 stride  # stride of given dimension
================================================================================
MSG: geometry_msgs/Pose2D
# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
")

(setf (get manip_msgs::InverseKinematicsFloatArrayResponse :md5sum-) "5286aef9c86ebe7d94286a61bc7ebe60")
(setf (get manip_msgs::InverseKinematicsFloatArrayResponse :datatype-) "manip_msgs/InverseKinematicsFloatArrayResponse")
(setf (get manip_msgs::InverseKinematicsFloatArrayResponse :definition-)
      "std_msgs/Float32MultiArray   cartesian_pose

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
---
std_msgs/Float32MultiArray   articular_pose
geometry_msgs/Pose2D 	     omni_base_correction
















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
uint32 stride  # stride of given dimension
================================================================================
MSG: geometry_msgs/Pose2D
# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
")



(provide :manip_msgs/InverseKinematicsFloatArray "5286aef9c86ebe7d94286a61bc7ebe60")


