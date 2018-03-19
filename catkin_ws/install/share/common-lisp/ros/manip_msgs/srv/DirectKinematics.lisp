; Auto-generated. Do not edit!


(cl:in-package manip_msgs-srv)


;//! \htmlinclude DirectKinematics-request.msg.html

(cl:defclass <DirectKinematics-request> (roslisp-msg-protocol:ros-message)
  ((articular_pose
    :reader articular_pose
    :initarg :articular_pose
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray)))
)

(cl:defclass DirectKinematics-request (<DirectKinematics-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DirectKinematics-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DirectKinematics-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manip_msgs-srv:<DirectKinematics-request> is deprecated: use manip_msgs-srv:DirectKinematics-request instead.")))

(cl:ensure-generic-function 'articular_pose-val :lambda-list '(m))
(cl:defmethod articular_pose-val ((m <DirectKinematics-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manip_msgs-srv:articular_pose-val is deprecated.  Use manip_msgs-srv:articular_pose instead.")
  (articular_pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DirectKinematics-request>) ostream)
  "Serializes a message object of type '<DirectKinematics-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'articular_pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DirectKinematics-request>) istream)
  "Deserializes a message object of type '<DirectKinematics-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'articular_pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DirectKinematics-request>)))
  "Returns string type for a service object of type '<DirectKinematics-request>"
  "manip_msgs/DirectKinematicsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DirectKinematics-request)))
  "Returns string type for a service object of type 'DirectKinematics-request"
  "manip_msgs/DirectKinematicsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DirectKinematics-request>)))
  "Returns md5sum for a message object of type '<DirectKinematics-request>"
  "6d3e3a04e953772f57d61cd8e812ab2e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DirectKinematics-request)))
  "Returns md5sum for a message object of type 'DirectKinematics-request"
  "6d3e3a04e953772f57d61cd8e812ab2e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DirectKinematics-request>)))
  "Returns full string definition for message of type '<DirectKinematics-request>"
  (cl:format cl:nil "std_msgs/Float32MultiArray articular_pose~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DirectKinematics-request)))
  "Returns full string definition for message of type 'DirectKinematics-request"
  (cl:format cl:nil "std_msgs/Float32MultiArray articular_pose~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DirectKinematics-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'articular_pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DirectKinematics-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DirectKinematics-request
    (cl:cons ':articular_pose (articular_pose msg))
))
;//! \htmlinclude DirectKinematics-response.msg.html

(cl:defclass <DirectKinematics-response> (roslisp-msg-protocol:ros-message)
  ((cartesian_pose
    :reader cartesian_pose
    :initarg :cartesian_pose
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray)))
)

(cl:defclass DirectKinematics-response (<DirectKinematics-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DirectKinematics-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DirectKinematics-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manip_msgs-srv:<DirectKinematics-response> is deprecated: use manip_msgs-srv:DirectKinematics-response instead.")))

(cl:ensure-generic-function 'cartesian_pose-val :lambda-list '(m))
(cl:defmethod cartesian_pose-val ((m <DirectKinematics-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manip_msgs-srv:cartesian_pose-val is deprecated.  Use manip_msgs-srv:cartesian_pose instead.")
  (cartesian_pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DirectKinematics-response>) ostream)
  "Serializes a message object of type '<DirectKinematics-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cartesian_pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DirectKinematics-response>) istream)
  "Deserializes a message object of type '<DirectKinematics-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cartesian_pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DirectKinematics-response>)))
  "Returns string type for a service object of type '<DirectKinematics-response>"
  "manip_msgs/DirectKinematicsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DirectKinematics-response)))
  "Returns string type for a service object of type 'DirectKinematics-response"
  "manip_msgs/DirectKinematicsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DirectKinematics-response>)))
  "Returns md5sum for a message object of type '<DirectKinematics-response>"
  "6d3e3a04e953772f57d61cd8e812ab2e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DirectKinematics-response)))
  "Returns md5sum for a message object of type 'DirectKinematics-response"
  "6d3e3a04e953772f57d61cd8e812ab2e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DirectKinematics-response>)))
  "Returns full string definition for message of type '<DirectKinematics-response>"
  (cl:format cl:nil "std_msgs/Float32MultiArray cartesian_pose~%~%~%~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DirectKinematics-response)))
  "Returns full string definition for message of type 'DirectKinematics-response"
  (cl:format cl:nil "std_msgs/Float32MultiArray cartesian_pose~%~%~%~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DirectKinematics-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cartesian_pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DirectKinematics-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DirectKinematics-response
    (cl:cons ':cartesian_pose (cartesian_pose msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DirectKinematics)))
  'DirectKinematics-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DirectKinematics)))
  'DirectKinematics-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DirectKinematics)))
  "Returns string type for a service object of type '<DirectKinematics>"
  "manip_msgs/DirectKinematics")