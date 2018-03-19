; Auto-generated. Do not edit!


(cl:in-package point_cloud_manager-srv)


;//! \htmlinclude GetRgbd-request.msg.html

(cl:defclass <GetRgbd-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetRgbd-request (<GetRgbd-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetRgbd-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetRgbd-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name point_cloud_manager-srv:<GetRgbd-request> is deprecated: use point_cloud_manager-srv:GetRgbd-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetRgbd-request>) ostream)
  "Serializes a message object of type '<GetRgbd-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetRgbd-request>) istream)
  "Deserializes a message object of type '<GetRgbd-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetRgbd-request>)))
  "Returns string type for a service object of type '<GetRgbd-request>"
  "point_cloud_manager/GetRgbdRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetRgbd-request)))
  "Returns string type for a service object of type 'GetRgbd-request"
  "point_cloud_manager/GetRgbdRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetRgbd-request>)))
  "Returns md5sum for a message object of type '<GetRgbd-request>"
  "d8288ab03c94033ddae07988baace1f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetRgbd-request)))
  "Returns md5sum for a message object of type 'GetRgbd-request"
  "d8288ab03c94033ddae07988baace1f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetRgbd-request>)))
  "Returns full string definition for message of type '<GetRgbd-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetRgbd-request)))
  "Returns full string definition for message of type 'GetRgbd-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetRgbd-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetRgbd-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetRgbd-request
))
;//! \htmlinclude GetRgbd-response.msg.html

(cl:defclass <GetRgbd-response> (roslisp-msg-protocol:ros-message)
  ((point_cloud
    :reader point_cloud
    :initarg :point_cloud
    :type sensor_msgs-msg:PointCloud2
    :initform (cl:make-instance 'sensor_msgs-msg:PointCloud2)))
)

(cl:defclass GetRgbd-response (<GetRgbd-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetRgbd-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetRgbd-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name point_cloud_manager-srv:<GetRgbd-response> is deprecated: use point_cloud_manager-srv:GetRgbd-response instead.")))

(cl:ensure-generic-function 'point_cloud-val :lambda-list '(m))
(cl:defmethod point_cloud-val ((m <GetRgbd-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader point_cloud_manager-srv:point_cloud-val is deprecated.  Use point_cloud_manager-srv:point_cloud instead.")
  (point_cloud m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetRgbd-response>) ostream)
  "Serializes a message object of type '<GetRgbd-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'point_cloud) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetRgbd-response>) istream)
  "Deserializes a message object of type '<GetRgbd-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'point_cloud) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetRgbd-response>)))
  "Returns string type for a service object of type '<GetRgbd-response>"
  "point_cloud_manager/GetRgbdResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetRgbd-response)))
  "Returns string type for a service object of type 'GetRgbd-response"
  "point_cloud_manager/GetRgbdResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetRgbd-response>)))
  "Returns md5sum for a message object of type '<GetRgbd-response>"
  "d8288ab03c94033ddae07988baace1f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetRgbd-response)))
  "Returns md5sum for a message object of type 'GetRgbd-response"
  "d8288ab03c94033ddae07988baace1f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetRgbd-response>)))
  "Returns full string definition for message of type '<GetRgbd-response>"
  (cl:format cl:nil "sensor_msgs/PointCloud2 point_cloud~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetRgbd-response)))
  "Returns full string definition for message of type 'GetRgbd-response"
  (cl:format cl:nil "sensor_msgs/PointCloud2 point_cloud~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetRgbd-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'point_cloud))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetRgbd-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetRgbd-response
    (cl:cons ':point_cloud (point_cloud msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetRgbd)))
  'GetRgbd-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetRgbd)))
  'GetRgbd-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetRgbd)))
  "Returns string type for a service object of type '<GetRgbd>"
  "point_cloud_manager/GetRgbd")