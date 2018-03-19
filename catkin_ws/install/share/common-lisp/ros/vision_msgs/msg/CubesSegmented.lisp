; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude CubesSegmented.msg.html

(cl:defclass <CubesSegmented> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (recog_cubes
    :reader recog_cubes
    :initarg :recog_cubes
    :type (cl:vector vision_msgs-msg:Cube)
   :initform (cl:make-array 0 :element-type 'vision_msgs-msg:Cube :initial-element (cl:make-instance 'vision_msgs-msg:Cube))))
)

(cl:defclass CubesSegmented (<CubesSegmented>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CubesSegmented>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CubesSegmented)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<CubesSegmented> is deprecated: use vision_msgs-msg:CubesSegmented instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CubesSegmented>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:header-val is deprecated.  Use vision_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'recog_cubes-val :lambda-list '(m))
(cl:defmethod recog_cubes-val ((m <CubesSegmented>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:recog_cubes-val is deprecated.  Use vision_msgs-msg:recog_cubes instead.")
  (recog_cubes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CubesSegmented>) ostream)
  "Serializes a message object of type '<CubesSegmented>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'recog_cubes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'recog_cubes))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CubesSegmented>) istream)
  "Deserializes a message object of type '<CubesSegmented>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'recog_cubes) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'recog_cubes)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'vision_msgs-msg:Cube))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CubesSegmented>)))
  "Returns string type for a message object of type '<CubesSegmented>"
  "vision_msgs/CubesSegmented")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CubesSegmented)))
  "Returns string type for a message object of type 'CubesSegmented"
  "vision_msgs/CubesSegmented")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CubesSegmented>)))
  "Returns md5sum for a message object of type '<CubesSegmented>"
  "2b935aade8f9275f5577fcbf7010f212")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CubesSegmented)))
  "Returns md5sum for a message object of type 'CubesSegmented"
  "2b935aade8f9275f5577fcbf7010f212")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CubesSegmented>)))
  "Returns full string definition for message of type '<CubesSegmented>"
  (cl:format cl:nil "std_msgs/Header header~%vision_msgs/Cube[] recog_cubes~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/Cube~%string color #color of the cube~%geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)~%bool detected_cube    #flag to indicate if the cube was detected~%geometry_msgs/Point minPoint	#Cube's min point~%geometry_msgs/Point maxPoint	#Cube's max point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CubesSegmented)))
  "Returns full string definition for message of type 'CubesSegmented"
  (cl:format cl:nil "std_msgs/Header header~%vision_msgs/Cube[] recog_cubes~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/Cube~%string color #color of the cube~%geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)~%bool detected_cube    #flag to indicate if the cube was detected~%geometry_msgs/Point minPoint	#Cube's min point~%geometry_msgs/Point maxPoint	#Cube's max point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CubesSegmented>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'recog_cubes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CubesSegmented>))
  "Converts a ROS message object to a list"
  (cl:list 'CubesSegmented
    (cl:cons ':header (header msg))
    (cl:cons ':recog_cubes (recog_cubes msg))
))
