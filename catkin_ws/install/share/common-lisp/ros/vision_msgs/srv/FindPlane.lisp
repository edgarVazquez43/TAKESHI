; Auto-generated. Do not edit!


(cl:in-package vision_msgs-srv)


;//! \htmlinclude FindPlane-request.msg.html

(cl:defclass <FindPlane-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (point_cloud
    :reader point_cloud
    :initarg :point_cloud
    :type sensor_msgs-msg:PointCloud2
    :initform (cl:make-instance 'sensor_msgs-msg:PointCloud2)))
)

(cl:defclass FindPlane-request (<FindPlane-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FindPlane-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FindPlane-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<FindPlane-request> is deprecated: use vision_msgs-srv:FindPlane-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <FindPlane-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:name-val is deprecated.  Use vision_msgs-srv:name instead.")
  (name m))

(cl:ensure-generic-function 'point_cloud-val :lambda-list '(m))
(cl:defmethod point_cloud-val ((m <FindPlane-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:point_cloud-val is deprecated.  Use vision_msgs-srv:point_cloud instead.")
  (point_cloud m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FindPlane-request>) ostream)
  "Serializes a message object of type '<FindPlane-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'point_cloud) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FindPlane-request>) istream)
  "Deserializes a message object of type '<FindPlane-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'point_cloud) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FindPlane-request>)))
  "Returns string type for a service object of type '<FindPlane-request>"
  "vision_msgs/FindPlaneRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FindPlane-request)))
  "Returns string type for a service object of type 'FindPlane-request"
  "vision_msgs/FindPlaneRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FindPlane-request>)))
  "Returns md5sum for a message object of type '<FindPlane-request>"
  "c9f71d0b8ee8e7ee471db6c2ca795c1a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FindPlane-request)))
  "Returns md5sum for a message object of type 'FindPlane-request"
  "c9f71d0b8ee8e7ee471db6c2ca795c1a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FindPlane-request>)))
  "Returns full string definition for message of type '<FindPlane-request>"
  (cl:format cl:nil "string name~%sensor_msgs/PointCloud2 point_cloud~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FindPlane-request)))
  "Returns full string definition for message of type 'FindPlane-request"
  (cl:format cl:nil "string name~%sensor_msgs/PointCloud2 point_cloud~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FindPlane-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'point_cloud))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FindPlane-request>))
  "Converts a ROS message object to a list"
  (cl:list 'FindPlane-request
    (cl:cons ':name (name msg))
    (cl:cons ':point_cloud (point_cloud msg))
))
;//! \htmlinclude FindPlane-response.msg.html

(cl:defclass <FindPlane-response> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (inliers
    :reader inliers
    :initarg :inliers
    :type (cl:vector std_msgs-msg:Int32)
   :initform (cl:make-array 0 :element-type 'std_msgs-msg:Int32 :initial-element (cl:make-instance 'std_msgs-msg:Int32)))
   (centroidFreeSpace
    :reader centroidFreeSpace
    :initarg :centroidFreeSpace
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (nearestPoint
    :reader nearestPoint
    :initarg :nearestPoint
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass FindPlane-response (<FindPlane-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FindPlane-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FindPlane-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<FindPlane-response> is deprecated: use vision_msgs-srv:FindPlane-response instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <FindPlane-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:header-val is deprecated.  Use vision_msgs-srv:header instead.")
  (header m))

(cl:ensure-generic-function 'inliers-val :lambda-list '(m))
(cl:defmethod inliers-val ((m <FindPlane-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:inliers-val is deprecated.  Use vision_msgs-srv:inliers instead.")
  (inliers m))

(cl:ensure-generic-function 'centroidFreeSpace-val :lambda-list '(m))
(cl:defmethod centroidFreeSpace-val ((m <FindPlane-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:centroidFreeSpace-val is deprecated.  Use vision_msgs-srv:centroidFreeSpace instead.")
  (centroidFreeSpace m))

(cl:ensure-generic-function 'nearestPoint-val :lambda-list '(m))
(cl:defmethod nearestPoint-val ((m <FindPlane-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:nearestPoint-val is deprecated.  Use vision_msgs-srv:nearestPoint instead.")
  (nearestPoint m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FindPlane-response>) ostream)
  "Serializes a message object of type '<FindPlane-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'inliers))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'inliers))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'centroidFreeSpace))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'centroidFreeSpace))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'nearestPoint) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FindPlane-response>) istream)
  "Deserializes a message object of type '<FindPlane-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'inliers) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'inliers)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:Int32))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'centroidFreeSpace) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'centroidFreeSpace)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'nearestPoint) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FindPlane-response>)))
  "Returns string type for a service object of type '<FindPlane-response>"
  "vision_msgs/FindPlaneResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FindPlane-response)))
  "Returns string type for a service object of type 'FindPlane-response"
  "vision_msgs/FindPlaneResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FindPlane-response>)))
  "Returns md5sum for a message object of type '<FindPlane-response>"
  "c9f71d0b8ee8e7ee471db6c2ca795c1a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FindPlane-response)))
  "Returns md5sum for a message object of type 'FindPlane-response"
  "c9f71d0b8ee8e7ee471db6c2ca795c1a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FindPlane-response>)))
  "Returns full string definition for message of type '<FindPlane-response>"
  (cl:format cl:nil "std_msgs/Header header~%std_msgs/Int32[] inliers~%geometry_msgs/Point[] 	centroidFreeSpace~%geometry_msgs/Point 	nearestPoint~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: std_msgs/Int32~%int32 data~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FindPlane-response)))
  "Returns full string definition for message of type 'FindPlane-response"
  (cl:format cl:nil "std_msgs/Header header~%std_msgs/Int32[] inliers~%geometry_msgs/Point[] 	centroidFreeSpace~%geometry_msgs/Point 	nearestPoint~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: std_msgs/Int32~%int32 data~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FindPlane-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'inliers) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'centroidFreeSpace) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'nearestPoint))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FindPlane-response>))
  "Converts a ROS message object to a list"
  (cl:list 'FindPlane-response
    (cl:cons ':header (header msg))
    (cl:cons ':inliers (inliers msg))
    (cl:cons ':centroidFreeSpace (centroidFreeSpace msg))
    (cl:cons ':nearestPoint (nearestPoint msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'FindPlane)))
  'FindPlane-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'FindPlane)))
  'FindPlane-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FindPlane)))
  "Returns string type for a service object of type '<FindPlane>"
  "vision_msgs/FindPlane")