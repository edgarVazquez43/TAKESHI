; Auto-generated. Do not edit!


(cl:in-package manip_msgs-srv)


;//! \htmlinclude InverseKinematicsPath-request.msg.html

(cl:defclass <InverseKinematicsPath-request> (roslisp-msg-protocol:ros-message)
  ((cartesian_path
    :reader cartesian_path
    :initarg :cartesian_path
    :type nav_msgs-msg:Path
    :initform (cl:make-instance 'nav_msgs-msg:Path)))
)

(cl:defclass InverseKinematicsPath-request (<InverseKinematicsPath-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InverseKinematicsPath-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InverseKinematicsPath-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manip_msgs-srv:<InverseKinematicsPath-request> is deprecated: use manip_msgs-srv:InverseKinematicsPath-request instead.")))

(cl:ensure-generic-function 'cartesian_path-val :lambda-list '(m))
(cl:defmethod cartesian_path-val ((m <InverseKinematicsPath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manip_msgs-srv:cartesian_path-val is deprecated.  Use manip_msgs-srv:cartesian_path instead.")
  (cartesian_path m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InverseKinematicsPath-request>) ostream)
  "Serializes a message object of type '<InverseKinematicsPath-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cartesian_path) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InverseKinematicsPath-request>) istream)
  "Deserializes a message object of type '<InverseKinematicsPath-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cartesian_path) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InverseKinematicsPath-request>)))
  "Returns string type for a service object of type '<InverseKinematicsPath-request>"
  "manip_msgs/InverseKinematicsPathRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InverseKinematicsPath-request)))
  "Returns string type for a service object of type 'InverseKinematicsPath-request"
  "manip_msgs/InverseKinematicsPathRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InverseKinematicsPath-request>)))
  "Returns md5sum for a message object of type '<InverseKinematicsPath-request>"
  "a5c97a40ea2d6c552050c61cfc35f302")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InverseKinematicsPath-request)))
  "Returns md5sum for a message object of type 'InverseKinematicsPath-request"
  "a5c97a40ea2d6c552050c61cfc35f302")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InverseKinematicsPath-request>)))
  "Returns full string definition for message of type '<InverseKinematicsPath-request>"
  (cl:format cl:nil "nav_msgs/Path cartesian_path~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InverseKinematicsPath-request)))
  "Returns full string definition for message of type 'InverseKinematicsPath-request"
  (cl:format cl:nil "nav_msgs/Path cartesian_path~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InverseKinematicsPath-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cartesian_path))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InverseKinematicsPath-request>))
  "Converts a ROS message object to a list"
  (cl:list 'InverseKinematicsPath-request
    (cl:cons ':cartesian_path (cartesian_path msg))
))
;//! \htmlinclude InverseKinematicsPath-response.msg.html

(cl:defclass <InverseKinematicsPath-response> (roslisp-msg-protocol:ros-message)
  ((articular_path
    :reader articular_path
    :initarg :articular_path
    :type (cl:vector std_msgs-msg:Float32MultiArray)
   :initform (cl:make-array 0 :element-type 'std_msgs-msg:Float32MultiArray :initial-element (cl:make-instance 'std_msgs-msg:Float32MultiArray))))
)

(cl:defclass InverseKinematicsPath-response (<InverseKinematicsPath-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InverseKinematicsPath-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InverseKinematicsPath-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manip_msgs-srv:<InverseKinematicsPath-response> is deprecated: use manip_msgs-srv:InverseKinematicsPath-response instead.")))

(cl:ensure-generic-function 'articular_path-val :lambda-list '(m))
(cl:defmethod articular_path-val ((m <InverseKinematicsPath-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manip_msgs-srv:articular_path-val is deprecated.  Use manip_msgs-srv:articular_path instead.")
  (articular_path m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InverseKinematicsPath-response>) ostream)
  "Serializes a message object of type '<InverseKinematicsPath-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'articular_path))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'articular_path))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InverseKinematicsPath-response>) istream)
  "Deserializes a message object of type '<InverseKinematicsPath-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'articular_path) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'articular_path)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:Float32MultiArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InverseKinematicsPath-response>)))
  "Returns string type for a service object of type '<InverseKinematicsPath-response>"
  "manip_msgs/InverseKinematicsPathResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InverseKinematicsPath-response)))
  "Returns string type for a service object of type 'InverseKinematicsPath-response"
  "manip_msgs/InverseKinematicsPathResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InverseKinematicsPath-response>)))
  "Returns md5sum for a message object of type '<InverseKinematicsPath-response>"
  "a5c97a40ea2d6c552050c61cfc35f302")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InverseKinematicsPath-response)))
  "Returns md5sum for a message object of type 'InverseKinematicsPath-response"
  "a5c97a40ea2d6c552050c61cfc35f302")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InverseKinematicsPath-response>)))
  "Returns full string definition for message of type '<InverseKinematicsPath-response>"
  (cl:format cl:nil "std_msgs/Float32MultiArray[] articular_path~%~%~%~%~%~%~%~%~%~%~%~%~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InverseKinematicsPath-response)))
  "Returns full string definition for message of type 'InverseKinematicsPath-response"
  (cl:format cl:nil "std_msgs/Float32MultiArray[] articular_path~%~%~%~%~%~%~%~%~%~%~%~%~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InverseKinematicsPath-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'articular_path) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InverseKinematicsPath-response>))
  "Converts a ROS message object to a list"
  (cl:list 'InverseKinematicsPath-response
    (cl:cons ':articular_path (articular_path msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'InverseKinematicsPath)))
  'InverseKinematicsPath-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'InverseKinematicsPath)))
  'InverseKinematicsPath-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InverseKinematicsPath)))
  "Returns string type for a service object of type '<InverseKinematicsPath>"
  "manip_msgs/InverseKinematicsPath")