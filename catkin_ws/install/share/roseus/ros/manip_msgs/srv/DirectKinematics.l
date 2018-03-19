;; Auto-generated. Do not edit!


(when (boundp 'manip_msgs::DirectKinematics)
  (if (not (find-package "MANIP_MSGS"))
    (make-package "MANIP_MSGS"))
  (shadow 'DirectKinematics (find-package "MANIP_MSGS")))
(unless (find-package "MANIP_MSGS::DIRECTKINEMATICS")
  (make-package "MANIP_MSGS::DIRECTKINEMATICS"))
(unless (find-package "MANIP_MSGS::DIRECTKINEMATICSREQUEST")
  (make-package "MANIP_MSGS::DIRECTKINEMATICSREQUEST"))
(unless (find-package "MANIP_MSGS::DIRECTKINEMATICSRESPONSE")
  (make-package "MANIP_MSGS::DIRECTKINEMATICSRESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass manip_msgs::DirectKinematicsRequest
  :super ros::object
  :slots (_articular_pose ))

(defmethod manip_msgs::DirectKinematicsRequest
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

(defclass manip_msgs::DirectKinematicsResponse
  :super ros::object
  :slots (_cartesian_pose ))

(defmethod manip_msgs::DirectKinematicsResponse
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

(defclass manip_msgs::DirectKinematics
  :super ros::object
  :slots ())

(setf (get manip_msgs::DirectKinematics :md5sum-) "6d3e3a04e953772f57d61cd8e812ab2e")
(setf (get manip_msgs::DirectKinematics :datatype-) "manip_msgs/DirectKinematics")
(setf (get manip_msgs::DirectKinematics :request) manip_msgs::DirectKinematicsRequest)
(setf (get manip_msgs::DirectKinematics :response) manip_msgs::DirectKinematicsResponse)

(defmethod manip_msgs::DirectKinematicsRequest
  (:response () (instance manip_msgs::DirectKinematicsResponse :init)))

(setf (get manip_msgs::DirectKinematicsRequest :md5sum-) "6d3e3a04e953772f57d61cd8e812ab2e")
(setf (get manip_msgs::DirectKinematicsRequest :datatype-) "manip_msgs/DirectKinematicsRequest")
(setf (get manip_msgs::DirectKinematicsRequest :definition-)
      "std_msgs/Float32MultiArray articular_pose

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
std_msgs/Float32MultiArray cartesian_pose




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

(setf (get manip_msgs::DirectKinematicsResponse :md5sum-) "6d3e3a04e953772f57d61cd8e812ab2e")
(setf (get manip_msgs::DirectKinematicsResponse :datatype-) "manip_msgs/DirectKinematicsResponse")
(setf (get manip_msgs::DirectKinematicsResponse :definition-)
      "std_msgs/Float32MultiArray articular_pose

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
std_msgs/Float32MultiArray cartesian_pose




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



(provide :manip_msgs/DirectKinematics "6d3e3a04e953772f57d61cd8e812ab2e")


