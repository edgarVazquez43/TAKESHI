; Auto-generated. Do not edit!


(cl:in-package manip_msgs-srv)


;//! \htmlinclude InverseKinematicsPose-request.msg.html

(cl:defclass <InverseKinematicsPose-request> (roslisp-msg-protocol:ros-message)
  ((cartesian_pose
    :reader cartesian_pose
    :initarg :cartesian_pose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose)))
)

(cl:defclass InverseKinematicsPose-request (<InverseKinematicsPose-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InverseKinematicsPose-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InverseKinematicsPose-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manip_msgs-srv:<InverseKinematicsPose-request> is deprecated: use manip_msgs-srv:InverseKinematicsPose-request instead.")))

(cl:ensure-generic-function 'cartesian_pose-val :lambda-list '(m))
(cl:defmethod cartesian_pose-val ((m <InverseKinematicsPose-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manip_msgs-srv:cartesian_pose-val is deprecated.  Use manip_msgs-srv:cartesian_pose instead.")
  (cartesian_pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InverseKinematicsPose-request>) ostream)
  "Serializes a message object of type '<InverseKinematicsPose-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cartesian_pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InverseKinematicsPose-request>) istream)
  "Deserializes a message object of type '<InverseKinematicsPose-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cartesian_pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InverseKinematicsPose-request>)))
  "Returns string type for a service object of type '<InverseKinematicsPose-request>"
  "manip_msgs/InverseKinematicsPoseRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InverseKinematicsPose-request)))
  "Returns string type for a service object of type 'InverseKinematicsPose-request"
  "manip_msgs/InverseKinematicsPoseRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InverseKinematicsPose-request>)))
  "Returns md5sum for a message object of type '<InverseKinematicsPose-request>"
  "1760e4c67453e0f01e66004e3b3191b6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InverseKinematicsPose-request)))
  "Returns md5sum for a message object of type 'InverseKinematicsPose-request"
  "1760e4c67453e0f01e66004e3b3191b6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InverseKinematicsPose-request>)))
  "Returns full string definition for message of type '<InverseKinematicsPose-request>"
  (cl:format cl:nil "geometry_msgs/Pose cartesian_pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InverseKinematicsPose-request)))
  "Returns full string definition for message of type 'InverseKinematicsPose-request"
  (cl:format cl:nil "geometry_msgs/Pose cartesian_pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InverseKinematicsPose-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cartesian_pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InverseKinematicsPose-request>))
  "Converts a ROS message object to a list"
  (cl:list 'InverseKinematicsPose-request
    (cl:cons ':cartesian_pose (cartesian_pose msg))
))
;//! \htmlinclude InverseKinematicsPose-response.msg.html

(cl:defclass <InverseKinematicsPose-response> (roslisp-msg-protocol:ros-message)
  ((articular_pose
    :reader articular_pose
    :initarg :articular_pose
    :type std_msgs-msg:Float32MultiArray
    :initform (cl:make-instance 'std_msgs-msg:Float32MultiArray)))
)

(cl:defclass InverseKinematicsPose-response (<InverseKinematicsPose-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InverseKinematicsPose-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InverseKinematicsPose-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name manip_msgs-srv:<InverseKinematicsPose-response> is deprecated: use manip_msgs-srv:InverseKinematicsPose-response instead.")))

(cl:ensure-generic-function 'articular_pose-val :lambda-list '(m))
(cl:defmethod articular_pose-val ((m <InverseKinematicsPose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader manip_msgs-srv:articular_pose-val is deprecated.  Use manip_msgs-srv:articular_pose instead.")
  (articular_pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InverseKinematicsPose-response>) ostream)
  "Serializes a message object of type '<InverseKinematicsPose-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'articular_pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InverseKinematicsPose-response>) istream)
  "Deserializes a message object of type '<InverseKinematicsPose-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'articular_pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InverseKinematicsPose-response>)))
  "Returns string type for a service object of type '<InverseKinematicsPose-response>"
  "manip_msgs/InverseKinematicsPoseResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InverseKinematicsPose-response)))
  "Returns string type for a service object of type 'InverseKinematicsPose-response"
  "manip_msgs/InverseKinematicsPoseResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InverseKinematicsPose-response>)))
  "Returns md5sum for a message object of type '<InverseKinematicsPose-response>"
  "1760e4c67453e0f01e66004e3b3191b6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InverseKinematicsPose-response)))
  "Returns md5sum for a message object of type 'InverseKinematicsPose-response"
  "1760e4c67453e0f01e66004e3b3191b6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InverseKinematicsPose-response>)))
  "Returns full string definition for message of type '<InverseKinematicsPose-response>"
  (cl:format cl:nil "std_msgs/Float32MultiArray articular_pose~%~%~%~%~%~%~%~%~%~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InverseKinematicsPose-response)))
  "Returns full string definition for message of type 'InverseKinematicsPose-response"
  (cl:format cl:nil "std_msgs/Float32MultiArray articular_pose~%~%~%~%~%~%~%~%~%~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InverseKinematicsPose-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'articular_pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InverseKinematicsPose-response>))
  "Converts a ROS message object to a list"
  (cl:list 'InverseKinematicsPose-response
    (cl:cons ':articular_pose (articular_pose msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'InverseKinematicsPose)))
  'InverseKinematicsPose-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'InverseKinematicsPose)))
  'InverseKinematicsPose-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InverseKinematicsPose)))
  "Returns string type for a service object of type '<InverseKinematicsPose>"
  "manip_msgs/InverseKinematicsPose")