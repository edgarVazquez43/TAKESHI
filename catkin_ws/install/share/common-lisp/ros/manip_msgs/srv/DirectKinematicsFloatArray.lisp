; Auto-generated. Do not edit!


(cl:in-package manip_msgs-srv)


;//! \htmlinclude DirectKinematicsFloatArray-request.msg.html

(cl:defclass <DirectKinematicsFloatArray-request> (roslisp-msg-protocol:ros-message)
  ((articular_pose
    :reader articular_pose
    :initarg :articular_pose
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray)))
)

(cl:defclass DirectKinematicsFloatArray-request (<DirectKinematicsFloatArray-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DirectKinematicsFloatArray-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DirectKinematicsFloatArray-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manip_msgs-srv:<DirectKinematicsFloatArray-request> is deprecated: use manip_msgs-srv:DirectKinematicsFloatArray-request instead.")))

(cl:ensure-generic-function 'articular_pose-val :lambda-list '(m))
(cl:defmethod articular_pose-val ((m <DirectKinematicsFloatArray-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manip_msgs-srv:articular_pose-val is deprecated.  Use manip_msgs-srv:articular_pose instead.")
  (articular_pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DirectKinematicsFloatArray-request>) ostream)
  "Serializes a message object of type '<DirectKinematicsFloatArray-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'articular_pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DirectKinematicsFloatArray-request>) istream)
  "Deserializes a message object of type '<DirectKinematicsFloatArray-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'articular_pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DirectKinematicsFloatArray-request>)))
  "Returns string type for a service object of type '<DirectKinematicsFloatArray-request>"
  "manip_msgs/DirectKinematicsFloatArrayRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DirectKinematicsFloatArray-request)))
  "Returns string type for a service object of type 'DirectKinematicsFloatArray-request"
  "manip_msgs/DirectKinematicsFloatArrayRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DirectKinematicsFloatArray-request>)))
  "Returns md5sum for a message object of type '<DirectKinematicsFloatArray-request>"
  "6d3e3a04e953772f57d61cd8e812ab2e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DirectKinematicsFloatArray-request)))
  "Returns md5sum for a message object of type 'DirectKinematicsFloatArray-request"
  "6d3e3a04e953772f57d61cd8e812ab2e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DirectKinematicsFloatArray-request>)))
  "Returns full string definition for message of type '<DirectKinematicsFloatArray-request>"
  (cl:format cl:nil "std_msgs/Float32MultiArray articular_pose~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DirectKinematicsFloatArray-request)))
  "Returns full string definition for message of type 'DirectKinematicsFloatArray-request"
  (cl:format cl:nil "std_msgs/Float32MultiArray articular_pose~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DirectKinematicsFloatArray-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'articular_pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DirectKinematicsFloatArray-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DirectKinematicsFloatArray-request
    (cl:cons ':articular_pose (articular_pose msg))
))
;//! \htmlinclude DirectKinematicsFloatArray-response.msg.html

(cl:defclass <DirectKinematicsFloatArray-response> (roslisp-msg-protocol:ros-message)
  ((cartesian_pose
    :reader cartesian_pose
    :initarg :cartesian_pose
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray)))
)

(cl:defclass DirectKinematicsFloatArray-response (<DirectKinematicsFloatArray-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DirectKinematicsFloatArray-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DirectKinematicsFloatArray-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manip_msgs-srv:<DirectKinematicsFloatArray-response> is deprecated: use manip_msgs-srv:DirectKinematicsFloatArray-response instead.")))

(cl:ensure-generic-function 'cartesian_pose-val :lambda-list '(m))
(cl:defmethod cartesian_pose-val ((m <DirectKinematicsFloatArray-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manip_msgs-srv:cartesian_pose-val is deprecated.  Use manip_msgs-srv:cartesian_pose instead.")
  (cartesian_pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DirectKinematicsFloatArray-response>) ostream)
  "Serializes a message object of type '<DirectKinematicsFloatArray-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cartesian_pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DirectKinematicsFloatArray-response>) istream)
  "Deserializes a message object of type '<DirectKinematicsFloatArray-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cartesian_pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DirectKinematicsFloatArray-response>)))
  "Returns string type for a service object of type '<DirectKinematicsFloatArray-response>"
  "manip_msgs/DirectKinematicsFloatArrayResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DirectKinematicsFloatArray-response)))
  "Returns string type for a service object of type 'DirectKinematicsFloatArray-response"
  "manip_msgs/DirectKinematicsFloatArrayResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DirectKinematicsFloatArray-response>)))
  "Returns md5sum for a message object of type '<DirectKinematicsFloatArray-response>"
  "6d3e3a04e953772f57d61cd8e812ab2e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DirectKinematicsFloatArray-response)))
  "Returns md5sum for a message object of type 'DirectKinematicsFloatArray-response"
  "6d3e3a04e953772f57d61cd8e812ab2e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DirectKinematicsFloatArray-response>)))
  "Returns full string definition for message of type '<DirectKinematicsFloatArray-response>"
  (cl:format cl:nil "std_msgs/Float32MultiArray cartesian_pose~%~%~%~%~%~%~%~%~%~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DirectKinematicsFloatArray-response)))
  "Returns full string definition for message of type 'DirectKinematicsFloatArray-response"
  (cl:format cl:nil "std_msgs/Float32MultiArray cartesian_pose~%~%~%~%~%~%~%~%~%~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DirectKinematicsFloatArray-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cartesian_pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DirectKinematicsFloatArray-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DirectKinematicsFloatArray-response
    (cl:cons ':cartesian_pose (cartesian_pose msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DirectKinematicsFloatArray)))
  'DirectKinematicsFloatArray-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DirectKinematicsFloatArray)))
  'DirectKinematicsFloatArray-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DirectKinematicsFloatArray)))
  "Returns string type for a service object of type '<DirectKinematicsFloatArray>"
  "manip_msgs/DirectKinematicsFloatArray")