; Auto-generated. Do not edit!


(cl:in-package navig_msgs-srv)


;//! \htmlinclude PathFromAll-request.msg.html

(cl:defclass <PathFromAll-request> (roslisp-msg-protocol:ros-message)
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
   (point_cloud
    :reader point_cloud
    :initarg :point_cloud
    :type sensor_msgs-msg:PointCloud2
    :initform (cl:make-instance 'sensor_msgs-msg:PointCloud2))
   (laser_scan
    :reader laser_scan
    :initarg :laser_scan
    :type sensor_msgs-msg:LaserScan
    :initform (cl:make-instance 'sensor_msgs-msg:LaserScan))
   (map
    :reader map
    :initarg :map
    :type nav_msgs-msg:OccupancyGrid
    :initform (cl:make-instance 'nav_msgs-msg:OccupancyGrid)))
)

(cl:defclass PathFromAll-request (<PathFromAll-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathFromAll-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathFromAll-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navig_msgs-srv:<PathFromAll-request> is deprecated: use navig_msgs-srv:PathFromAll-request instead.")))

(cl:ensure-generic-function 'start_pose-val :lambda-list '(m))
(cl:defmethod start_pose-val ((m <PathFromAll-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:start_pose-val is deprecated.  Use navig_msgs-srv:start_pose instead.")
  (start_pose m))

(cl:ensure-generic-function 'goal_pose-val :lambda-list '(m))
(cl:defmethod goal_pose-val ((m <PathFromAll-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:goal_pose-val is deprecated.  Use navig_msgs-srv:goal_pose instead.")
  (goal_pose m))

(cl:ensure-generic-function 'point_cloud-val :lambda-list '(m))
(cl:defmethod point_cloud-val ((m <PathFromAll-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:point_cloud-val is deprecated.  Use navig_msgs-srv:point_cloud instead.")
  (point_cloud m))

(cl:ensure-generic-function 'laser_scan-val :lambda-list '(m))
(cl:defmethod laser_scan-val ((m <PathFromAll-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:laser_scan-val is deprecated.  Use navig_msgs-srv:laser_scan instead.")
  (laser_scan m))

(cl:ensure-generic-function 'map-val :lambda-list '(m))
(cl:defmethod map-val ((m <PathFromAll-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:map-val is deprecated.  Use navig_msgs-srv:map instead.")
  (map m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathFromAll-request>) ostream)
  "Serializes a message object of type '<PathFromAll-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'start_pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal_pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'point_cloud) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'laser_scan) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'map) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathFromAll-request>) istream)
  "Deserializes a message object of type '<PathFromAll-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'start_pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal_pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'point_cloud) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'laser_scan) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'map) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathFromAll-request>)))
  "Returns string type for a service object of type '<PathFromAll-request>"
  "navig_msgs/PathFromAllRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathFromAll-request)))
  "Returns string type for a service object of type 'PathFromAll-request"
  "navig_msgs/PathFromAllRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathFromAll-request>)))
  "Returns md5sum for a message object of type '<PathFromAll-request>"
  "16f9de799db2245d5eab2e0bc95c1818")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathFromAll-request)))
  "Returns md5sum for a message object of type 'PathFromAll-request"
  "16f9de799db2245d5eab2e0bc95c1818")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathFromAll-request>)))
  "Returns full string definition for message of type '<PathFromAll-request>"
  (cl:format cl:nil "geometry_msgs/Pose start_pose~%geometry_msgs/Pose goal_pose~%sensor_msgs/PointCloud2 point_cloud~%sensor_msgs/LaserScan laser_scan~%nav_msgs/OccupancyGrid map~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%================================================================================~%MSG: sensor_msgs/LaserScan~%# Single scan from a planar laser range-finder~%#~%# If you have another ranging device with different behavior (e.g. a sonar~%# array), please find or create a different message, since applications~%# will make fairly laser-specific assumptions about this data~%~%Header header            # timestamp in the header is the acquisition time of ~%                         # the first ray in the scan.~%                         #~%                         # in frame frame_id, angles are measured around ~%                         # the positive Z axis (counterclockwise, if Z is up)~%                         # with zero angle being forward along the x axis~%                         ~%float32 angle_min        # start angle of the scan [rad]~%float32 angle_max        # end angle of the scan [rad]~%float32 angle_increment  # angular distance between measurements [rad]~%~%float32 time_increment   # time between measurements [seconds] - if your scanner~%                         # is moving, this will be used in interpolating position~%                         # of 3d points~%float32 scan_time        # time between scans [seconds]~%~%float32 range_min        # minimum range value [m]~%float32 range_max        # maximum range value [m]~%~%float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)~%float32[] intensities    # intensity data [device-specific units].  If your~%                         # device does not provide intensities, please leave~%                         # the array empty.~%~%================================================================================~%MSG: nav_msgs/OccupancyGrid~%# This represents a 2-D grid map, in which each cell represents the probability of~%# occupancy.~%~%Header header ~%~%#MetaData for the map~%MapMetaData info~%~%# The map data, in row-major order, starting with (0,0).  Occupancy~%# probabilities are in the range [0,100].  Unknown is -1.~%int8[] data~%~%================================================================================~%MSG: nav_msgs/MapMetaData~%# This hold basic information about the characterists of the OccupancyGrid~%~%# The time at which the map was loaded~%time map_load_time~%# The map resolution [m/cell]~%float32 resolution~%# Map width [cells]~%uint32 width~%# Map height [cells]~%uint32 height~%# The origin of the map [m, m, rad].  This is the real-world pose of the~%# cell (0,0) in the map.~%geometry_msgs/Pose origin~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathFromAll-request)))
  "Returns full string definition for message of type 'PathFromAll-request"
  (cl:format cl:nil "geometry_msgs/Pose start_pose~%geometry_msgs/Pose goal_pose~%sensor_msgs/PointCloud2 point_cloud~%sensor_msgs/LaserScan laser_scan~%nav_msgs/OccupancyGrid map~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%================================================================================~%MSG: sensor_msgs/LaserScan~%# Single scan from a planar laser range-finder~%#~%# If you have another ranging device with different behavior (e.g. a sonar~%# array), please find or create a different message, since applications~%# will make fairly laser-specific assumptions about this data~%~%Header header            # timestamp in the header is the acquisition time of ~%                         # the first ray in the scan.~%                         #~%                         # in frame frame_id, angles are measured around ~%                         # the positive Z axis (counterclockwise, if Z is up)~%                         # with zero angle being forward along the x axis~%                         ~%float32 angle_min        # start angle of the scan [rad]~%float32 angle_max        # end angle of the scan [rad]~%float32 angle_increment  # angular distance between measurements [rad]~%~%float32 time_increment   # time between measurements [seconds] - if your scanner~%                         # is moving, this will be used in interpolating position~%                         # of 3d points~%float32 scan_time        # time between scans [seconds]~%~%float32 range_min        # minimum range value [m]~%float32 range_max        # maximum range value [m]~%~%float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)~%float32[] intensities    # intensity data [device-specific units].  If your~%                         # device does not provide intensities, please leave~%                         # the array empty.~%~%================================================================================~%MSG: nav_msgs/OccupancyGrid~%# This represents a 2-D grid map, in which each cell represents the probability of~%# occupancy.~%~%Header header ~%~%#MetaData for the map~%MapMetaData info~%~%# The map data, in row-major order, starting with (0,0).  Occupancy~%# probabilities are in the range [0,100].  Unknown is -1.~%int8[] data~%~%================================================================================~%MSG: nav_msgs/MapMetaData~%# This hold basic information about the characterists of the OccupancyGrid~%~%# The time at which the map was loaded~%time map_load_time~%# The map resolution [m/cell]~%float32 resolution~%# Map width [cells]~%uint32 width~%# Map height [cells]~%uint32 height~%# The origin of the map [m, m, rad].  This is the real-world pose of the~%# cell (0,0) in the map.~%geometry_msgs/Pose origin~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathFromAll-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'start_pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal_pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'point_cloud))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'laser_scan))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'map))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathFromAll-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PathFromAll-request
    (cl:cons ':start_pose (start_pose msg))
    (cl:cons ':goal_pose (goal_pose msg))
    (cl:cons ':point_cloud (point_cloud msg))
    (cl:cons ':laser_scan (laser_scan msg))
    (cl:cons ':map (map msg))
))
;//! \htmlinclude PathFromAll-response.msg.html

(cl:defclass <PathFromAll-response> (roslisp-msg-protocol:ros-message)
  ((path
    :reader path
    :initarg :path
    :type nav_msgs-msg:Path
    :initform (cl:make-instance 'nav_msgs-msg:Path)))
)

(cl:defclass PathFromAll-response (<PathFromAll-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathFromAll-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathFromAll-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navig_msgs-srv:<PathFromAll-response> is deprecated: use navig_msgs-srv:PathFromAll-response instead.")))

(cl:ensure-generic-function 'path-val :lambda-list '(m))
(cl:defmethod path-val ((m <PathFromAll-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-srv:path-val is deprecated.  Use navig_msgs-srv:path instead.")
  (path m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathFromAll-response>) ostream)
  "Serializes a message object of type '<PathFromAll-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'path) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathFromAll-response>) istream)
  "Deserializes a message object of type '<PathFromAll-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'path) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathFromAll-response>)))
  "Returns string type for a service object of type '<PathFromAll-response>"
  "navig_msgs/PathFromAllResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathFromAll-response)))
  "Returns string type for a service object of type 'PathFromAll-response"
  "navig_msgs/PathFromAllResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathFromAll-response>)))
  "Returns md5sum for a message object of type '<PathFromAll-response>"
  "16f9de799db2245d5eab2e0bc95c1818")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathFromAll-response)))
  "Returns md5sum for a message object of type 'PathFromAll-response"
  "16f9de799db2245d5eab2e0bc95c1818")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathFromAll-response>)))
  "Returns full string definition for message of type '<PathFromAll-response>"
  (cl:format cl:nil "nav_msgs/Path path~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathFromAll-response)))
  "Returns full string definition for message of type 'PathFromAll-response"
  (cl:format cl:nil "nav_msgs/Path path~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathFromAll-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'path))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathFromAll-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PathFromAll-response
    (cl:cons ':path (path msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PathFromAll)))
  'PathFromAll-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PathFromAll)))
  'PathFromAll-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathFromAll)))
  "Returns string type for a service object of type '<PathFromAll>"
  "navig_msgs/PathFromAll")