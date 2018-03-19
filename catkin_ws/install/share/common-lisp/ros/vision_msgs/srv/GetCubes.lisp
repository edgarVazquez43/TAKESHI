; Auto-generated. Do not edit!


(cl:in-package vision_msgs-srv)


;//! \htmlinclude GetCubes-request.msg.html

(cl:defclass <GetCubes-request> (roslisp-msg-protocol:ros-message)
  ((cubes_input
    :reader cubes_input
    :initarg :cubes_input
    :type vision_msgs-msg:CubesSegmented
    :initform (cl:make-instance 'vision_msgs-msg:CubesSegmented)))
)

(cl:defclass GetCubes-request (<GetCubes-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetCubes-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetCubes-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<GetCubes-request> is deprecated: use vision_msgs-srv:GetCubes-request instead.")))

(cl:ensure-generic-function 'cubes_input-val :lambda-list '(m))
(cl:defmethod cubes_input-val ((m <GetCubes-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:cubes_input-val is deprecated.  Use vision_msgs-srv:cubes_input instead.")
  (cubes_input m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetCubes-request>) ostream)
  "Serializes a message object of type '<GetCubes-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cubes_input) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetCubes-request>) istream)
  "Deserializes a message object of type '<GetCubes-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cubes_input) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetCubes-request>)))
  "Returns string type for a service object of type '<GetCubes-request>"
  "vision_msgs/GetCubesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetCubes-request)))
  "Returns string type for a service object of type 'GetCubes-request"
  "vision_msgs/GetCubesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetCubes-request>)))
  "Returns md5sum for a message object of type '<GetCubes-request>"
  "a2d88941f0bdf4936824e45f204e46ff")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetCubes-request)))
  "Returns md5sum for a message object of type 'GetCubes-request"
  "a2d88941f0bdf4936824e45f204e46ff")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetCubes-request>)))
  "Returns full string definition for message of type '<GetCubes-request>"
  (cl:format cl:nil "vision_msgs/CubesSegmented cubes_input~%~%================================================================================~%MSG: vision_msgs/CubesSegmented~%std_msgs/Header header~%vision_msgs/Cube[] recog_cubes~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/Cube~%string color #color of the cube~%geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)~%bool detected_cube    #flag to indicate if the cube was detected~%geometry_msgs/Point minPoint	#Cube's min point~%geometry_msgs/Point maxPoint	#Cube's max point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetCubes-request)))
  "Returns full string definition for message of type 'GetCubes-request"
  (cl:format cl:nil "vision_msgs/CubesSegmented cubes_input~%~%================================================================================~%MSG: vision_msgs/CubesSegmented~%std_msgs/Header header~%vision_msgs/Cube[] recog_cubes~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/Cube~%string color #color of the cube~%geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)~%bool detected_cube    #flag to indicate if the cube was detected~%geometry_msgs/Point minPoint	#Cube's min point~%geometry_msgs/Point maxPoint	#Cube's max point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetCubes-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cubes_input))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetCubes-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetCubes-request
    (cl:cons ':cubes_input (cubes_input msg))
))
;//! \htmlinclude GetCubes-response.msg.html

(cl:defclass <GetCubes-response> (roslisp-msg-protocol:ros-message)
  ((cubes_output
    :reader cubes_output
    :initarg :cubes_output
    :type vision_msgs-msg:CubesSegmented
    :initform (cl:make-instance 'vision_msgs-msg:CubesSegmented)))
)

(cl:defclass GetCubes-response (<GetCubes-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetCubes-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetCubes-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<GetCubes-response> is deprecated: use vision_msgs-srv:GetCubes-response instead.")))

(cl:ensure-generic-function 'cubes_output-val :lambda-list '(m))
(cl:defmethod cubes_output-val ((m <GetCubes-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:cubes_output-val is deprecated.  Use vision_msgs-srv:cubes_output instead.")
  (cubes_output m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetCubes-response>) ostream)
  "Serializes a message object of type '<GetCubes-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cubes_output) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetCubes-response>) istream)
  "Deserializes a message object of type '<GetCubes-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cubes_output) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetCubes-response>)))
  "Returns string type for a service object of type '<GetCubes-response>"
  "vision_msgs/GetCubesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetCubes-response)))
  "Returns string type for a service object of type 'GetCubes-response"
  "vision_msgs/GetCubesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetCubes-response>)))
  "Returns md5sum for a message object of type '<GetCubes-response>"
  "a2d88941f0bdf4936824e45f204e46ff")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetCubes-response)))
  "Returns md5sum for a message object of type 'GetCubes-response"
  "a2d88941f0bdf4936824e45f204e46ff")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetCubes-response>)))
  "Returns full string definition for message of type '<GetCubes-response>"
  (cl:format cl:nil "vision_msgs/CubesSegmented cubes_output~%~%~%================================================================================~%MSG: vision_msgs/CubesSegmented~%std_msgs/Header header~%vision_msgs/Cube[] recog_cubes~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/Cube~%string color #color of the cube~%geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)~%bool detected_cube    #flag to indicate if the cube was detected~%geometry_msgs/Point minPoint	#Cube's min point~%geometry_msgs/Point maxPoint	#Cube's max point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetCubes-response)))
  "Returns full string definition for message of type 'GetCubes-response"
  (cl:format cl:nil "vision_msgs/CubesSegmented cubes_output~%~%~%================================================================================~%MSG: vision_msgs/CubesSegmented~%std_msgs/Header header~%vision_msgs/Cube[] recog_cubes~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/Cube~%string color #color of the cube~%geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)~%bool detected_cube    #flag to indicate if the cube was detected~%geometry_msgs/Point minPoint	#Cube's min point~%geometry_msgs/Point maxPoint	#Cube's max point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetCubes-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cubes_output))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetCubes-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetCubes-response
    (cl:cons ':cubes_output (cubes_output msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetCubes)))
  'GetCubes-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetCubes)))
  'GetCubes-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetCubes)))
  "Returns string type for a service object of type '<GetCubes>"
  "vision_msgs/GetCubes")