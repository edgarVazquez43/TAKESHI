; Auto-generated. Do not edit!


(cl:in-package navig_msgs-srv)


;//! \htmlinclude PathFromMap-request.msg.html

(cl:defclass <PathFromMap-request> (roslisp-msg-protocol:ros-message)
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
   (map
    :reader map
    :initarg :map
    :type nav_msgs-msg:OccupancyGrid
    :initform (cl:make-instance 'nav_msgs-msg:OccupancyGrid)))
)

(cl:defclass PathFromMap-request (<PathFromMap-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathFromMap-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathFromMap-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navig_msgs-srv:<PathFromMap-request> is deprecated: use navig_msgs-srv:PathFromMap-request instead.")))

(cl:ensure-generic-function 'start_pose-val :lambda-list '(m))
(cl:defmethod start_pose-val ((m <PathFromMap-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:start_pose-val is deprecated.  Use navig_msgs-srv:start_pose instead.")
  (start_pose m))

(cl:ensure-generic-function 'goal_pose-val :lambda-list '(m))
(cl:defmethod goal_pose-val ((m <PathFromMap-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:goal_pose-val is deprecated.  Use navig_msgs-srv:goal_pose instead.")
  (goal_pose m))

(cl:ensure-generic-function 'map-val :lambda-list '(m))
(cl:defmethod map-val ((m <PathFromMap-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:map-val is deprecated.  Use navig_msgs-srv:map instead.")
  (map m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathFromMap-request>) ostream)
  "Serializes a message object of type '<PathFromMap-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'start_pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal_pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'map) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathFromMap-request>) istream)
  "Deserializes a message object of type '<PathFromMap-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'start_pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal_pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'map) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathFromMap-request>)))
  "Returns string type for a service object of type '<PathFromMap-request>"
  "navig_msgs/PathFromMapRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathFromMap-request)))
  "Returns string type for a service object of type 'PathFromMap-request"
  "navig_msgs/PathFromMapRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathFromMap-request>)))
  "Returns md5sum for a message object of type '<PathFromMap-request>"
  "d2d67a7b3113d6cff0dbdc8eda5ddb01")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathFromMap-request)))
  "Returns md5sum for a message object of type 'PathFromMap-request"
  "d2d67a7b3113d6cff0dbdc8eda5ddb01")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathFromMap-request>)))
  "Returns full string definition for message of type '<PathFromMap-request>"
  (cl:format cl:nil "geometry_msgs/Pose start_pose~%geometry_msgs/Pose goal_pose~%nav_msgs/OccupancyGrid map~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: nav_msgs/OccupancyGrid~%# This represents a 2-D grid map, in which each cell represents the probability of~%# occupancy.~%~%Header header ~%~%#MetaData for the map~%MapMetaData info~%~%# The map data, in row-major order, starting with (0,0).  Occupancy~%# probabilities are in the range [0,100].  Unknown is -1.~%int8[] data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nav_msgs/MapMetaData~%# This hold basic information about the characterists of the OccupancyGrid~%~%# The time at which the map was loaded~%time map_load_time~%# The map resolution [m/cell]~%float32 resolution~%# Map width [cells]~%uint32 width~%# Map height [cells]~%uint32 height~%# The origin of the map [m, m, rad].  This is the real-world pose of the~%# cell (0,0) in the map.~%geometry_msgs/Pose origin~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathFromMap-request)))
  "Returns full string definition for message of type 'PathFromMap-request"
  (cl:format cl:nil "geometry_msgs/Pose start_pose~%geometry_msgs/Pose goal_pose~%nav_msgs/OccupancyGrid map~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: nav_msgs/OccupancyGrid~%# This represents a 2-D grid map, in which each cell represents the probability of~%# occupancy.~%~%Header header ~%~%#MetaData for the map~%MapMetaData info~%~%# The map data, in row-major order, starting with (0,0).  Occupancy~%# probabilities are in the range [0,100].  Unknown is -1.~%int8[] data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nav_msgs/MapMetaData~%# This hold basic information about the characterists of the OccupancyGrid~%~%# The time at which the map was loaded~%time map_load_time~%# The map resolution [m/cell]~%float32 resolution~%# Map width [cells]~%uint32 width~%# Map height [cells]~%uint32 height~%# The origin of the map [m, m, rad].  This is the real-world pose of the~%# cell (0,0) in the map.~%geometry_msgs/Pose origin~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathFromMap-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'start_pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal_pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'map))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathFromMap-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PathFromMap-request
    (cl:cons ':start_pose (start_pose msg))
    (cl:cons ':goal_pose (goal_pose msg))
    (cl:cons ':map (map msg))
))
;//! \htmlinclude PathFromMap-response.msg.html

(cl:defclass <PathFromMap-response> (roslisp-msg-protocol:ros-message)
  ((path
    :reader path
    :initarg :path
    :type nav_msgs-msg:Path
    :initform (cl:make-instance 'nav_msgs-msg:Path)))
)

(cl:defclass PathFromMap-response (<PathFromMap-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathFromMap-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathFromMap-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navig_msgs-srv:<PathFromMap-response> is deprecated: use navig_msgs-srv:PathFromMap-response instead.")))

(cl:ensure-generic-function 'path-val :lambda-list '(m))
(cl:defmethod path-val ((m <PathFromMap-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:path-val is deprecated.  Use navig_msgs-srv:path instead.")
  (path m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathFromMap-response>) ostream)
  "Serializes a message object of type '<PathFromMap-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'path) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathFromMap-response>) istream)
  "Deserializes a message object of type '<PathFromMap-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'path) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathFromMap-response>)))
  "Returns string type for a service object of type '<PathFromMap-response>"
  "navig_msgs/PathFromMapResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathFromMap-response)))
  "Returns string type for a service object of type 'PathFromMap-response"
  "navig_msgs/PathFromMapResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathFromMap-response>)))
  "Returns md5sum for a message object of type '<PathFromMap-response>"
  "d2d67a7b3113d6cff0dbdc8eda5ddb01")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathFromMap-response)))
  "Returns md5sum for a message object of type 'PathFromMap-response"
  "d2d67a7b3113d6cff0dbdc8eda5ddb01")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathFromMap-response>)))
  "Returns full string definition for message of type '<PathFromMap-response>"
  (cl:format cl:nil "nav_msgs/Path path~%~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathFromMap-response)))
  "Returns full string definition for message of type 'PathFromMap-response"
  (cl:format cl:nil "nav_msgs/Path path~%~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathFromMap-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'path))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathFromMap-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PathFromMap-response
    (cl:cons ':path (path msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PathFromMap)))
  'PathFromMap-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PathFromMap)))
  'PathFromMap-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathFromMap)))
  "Returns string type for a service object of type '<PathFromMap>"
  "navig_msgs/PathFromMap")