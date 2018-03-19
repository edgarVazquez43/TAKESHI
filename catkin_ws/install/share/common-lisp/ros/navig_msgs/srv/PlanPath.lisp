; Auto-generated. Do not edit!


(cl:in-package navig_msgs-srv)


;//! \htmlinclude PlanPath-request.msg.html

(cl:defclass <PlanPath-request> (roslisp-msg-protocol:ros-message)
  ((start_pose
    :reader start_pose
    :initarg :start_pose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (goal_pose
    :reader goal_pose
    :initarg :goal_pose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (start_location_id
    :reader start_location_id
    :initarg :start_location_id
    :type cl:string
    :initform "")
   (goal_location_id
    :reader goal_location_id
    :initarg :goal_location_id
    :type cl:string
    :initform ""))
)

(cl:defclass PlanPath-request (<PlanPath-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PlanPath-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PlanPath-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navig_msgs-srv:<PlanPath-request> is deprecated: use navig_msgs-srv:PlanPath-request instead.")))

(cl:ensure-generic-function 'start_pose-val :lambda-list '(m))
(cl:defmethod start_pose-val ((m <PlanPath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:start_pose-val is deprecated.  Use navig_msgs-srv:start_pose instead.")
  (start_pose m))

(cl:ensure-generic-function 'goal_pose-val :lambda-list '(m))
(cl:defmethod goal_pose-val ((m <PlanPath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:goal_pose-val is deprecated.  Use navig_msgs-srv:goal_pose instead.")
  (goal_pose m))

(cl:ensure-generic-function 'start_location_id-val :lambda-list '(m))
(cl:defmethod start_location_id-val ((m <PlanPath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:start_location_id-val is deprecated.  Use navig_msgs-srv:start_location_id instead.")
  (start_location_id m))

(cl:ensure-generic-function 'goal_location_id-val :lambda-list '(m))
(cl:defmethod goal_location_id-val ((m <PlanPath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:goal_location_id-val is deprecated.  Use navig_msgs-srv:goal_location_id instead.")
  (goal_location_id m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PlanPath-request>) ostream)
  "Serializes a message object of type '<PlanPath-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'start_pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal_pose) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'start_location_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'start_location_id))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'goal_location_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'goal_location_id))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PlanPath-request>) istream)
  "Deserializes a message object of type '<PlanPath-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'start_pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal_pose) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'start_location_id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'start_location_id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'goal_location_id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'goal_location_id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PlanPath-request>)))
  "Returns string type for a service object of type '<PlanPath-request>"
  "navig_msgs/PlanPathRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PlanPath-request)))
  "Returns string type for a service object of type 'PlanPath-request"
  "navig_msgs/PlanPathRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PlanPath-request>)))
  "Returns md5sum for a message object of type '<PlanPath-request>"
  "d4c7fd7dba298b47cf73caf450fd8a9f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PlanPath-request)))
  "Returns md5sum for a message object of type 'PlanPath-request"
  "d4c7fd7dba298b47cf73caf450fd8a9f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PlanPath-request>)))
  "Returns full string definition for message of type '<PlanPath-request>"
  (cl:format cl:nil "geometry_msgs/Pose start_pose~%geometry_msgs/Pose goal_pose~%string start_location_id~%string goal_location_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PlanPath-request)))
  "Returns full string definition for message of type 'PlanPath-request"
  (cl:format cl:nil "geometry_msgs/Pose start_pose~%geometry_msgs/Pose goal_pose~%string start_location_id~%string goal_location_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PlanPath-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'start_pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal_pose))
     4 (cl:length (cl:slot-value msg 'start_location_id))
     4 (cl:length (cl:slot-value msg 'goal_location_id))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PlanPath-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PlanPath-request
    (cl:cons ':start_pose (start_pose msg))
    (cl:cons ':goal_pose (goal_pose msg))
    (cl:cons ':start_location_id (start_location_id msg))
    (cl:cons ':goal_location_id (goal_location_id msg))
))
;//! \htmlinclude PlanPath-response.msg.html

(cl:defclass <PlanPath-response> (roslisp-msg-protocol:ros-message)
  ((path
    :reader path
    :initarg :path
    :type nav_msgs-msg:Path
    :initform (cl:make-instance 'nav_msgs-msg:Path)))
)

(cl:defclass PlanPath-response (<PlanPath-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PlanPath-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PlanPath-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navig_msgs-srv:<PlanPath-response> is deprecated: use navig_msgs-srv:PlanPath-response instead.")))

(cl:ensure-generic-function 'path-val :lambda-list '(m))
(cl:defmethod path-val ((m <PlanPath-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:path-val is deprecated.  Use navig_msgs-srv:path instead.")
  (path m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PlanPath-response>) ostream)
  "Serializes a message object of type '<PlanPath-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'path) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PlanPath-response>) istream)
  "Deserializes a message object of type '<PlanPath-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'path) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PlanPath-response>)))
  "Returns string type for a service object of type '<PlanPath-response>"
  "navig_msgs/PlanPathResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PlanPath-response)))
  "Returns string type for a service object of type 'PlanPath-response"
  "navig_msgs/PlanPathResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PlanPath-response>)))
  "Returns md5sum for a message object of type '<PlanPath-response>"
  "d4c7fd7dba298b47cf73caf450fd8a9f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PlanPath-response)))
  "Returns md5sum for a message object of type 'PlanPath-response"
  "d4c7fd7dba298b47cf73caf450fd8a9f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PlanPath-response>)))
  "Returns full string definition for message of type '<PlanPath-response>"
  (cl:format cl:nil "nav_msgs/Path path~%~%~%~%~%~%~%~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PlanPath-response)))
  "Returns full string definition for message of type 'PlanPath-response"
  (cl:format cl:nil "nav_msgs/Path path~%~%~%~%~%~%~%~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PlanPath-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'path))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PlanPath-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PlanPath-response
    (cl:cons ':path (path msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PlanPath)))
  'PlanPath-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PlanPath)))
  'PlanPath-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PlanPath)))
  "Returns string type for a service object of type '<PlanPath>"
  "navig_msgs/PlanPath")