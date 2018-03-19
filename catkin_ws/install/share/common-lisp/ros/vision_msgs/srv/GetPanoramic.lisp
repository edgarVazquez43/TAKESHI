; Auto-generated. Do not edit!


(cl:in-package vision_msgs-srv)


;//! \htmlinclude GetPanoramic-request.msg.html

(cl:defclass <GetPanoramic-request> (roslisp-msg-protocol:ros-message)
  ((head_pan_min
    :reader head_pan_min
    :initarg :head_pan_min
    :type cl:float
    :initform 0.0)
   (head_pan_max
    :reader head_pan_max
    :initarg :head_pan_max
    :type cl:float
    :initform 0.0)
   (head_tilt_min
    :reader head_tilt_min
    :initarg :head_tilt_min
    :type cl:float
    :initform 0.0)
   (head_tilt_max
    :reader head_tilt_max
    :initarg :head_tilt_max
    :type cl:float
    :initform 0.0))
)

(cl:defclass GetPanoramic-request (<GetPanoramic-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetPanoramic-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetPanoramic-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<GetPanoramic-request> is deprecated: use vision_msgs-srv:GetPanoramic-request instead.")))

(cl:ensure-generic-function 'head_pan_min-val :lambda-list '(m))
(cl:defmethod head_pan_min-val ((m <GetPanoramic-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:head_pan_min-val is deprecated.  Use vision_msgs-srv:head_pan_min instead.")
  (head_pan_min m))

(cl:ensure-generic-function 'head_pan_max-val :lambda-list '(m))
(cl:defmethod head_pan_max-val ((m <GetPanoramic-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:head_pan_max-val is deprecated.  Use vision_msgs-srv:head_pan_max instead.")
  (head_pan_max m))

(cl:ensure-generic-function 'head_tilt_min-val :lambda-list '(m))
(cl:defmethod head_tilt_min-val ((m <GetPanoramic-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:head_tilt_min-val is deprecated.  Use vision_msgs-srv:head_tilt_min instead.")
  (head_tilt_min m))

(cl:ensure-generic-function 'head_tilt_max-val :lambda-list '(m))
(cl:defmethod head_tilt_max-val ((m <GetPanoramic-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:head_tilt_max-val is deprecated.  Use vision_msgs-srv:head_tilt_max instead.")
  (head_tilt_max m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetPanoramic-request>) ostream)
  "Serializes a message object of type '<GetPanoramic-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'head_pan_min))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'head_pan_max))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'head_tilt_min))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'head_tilt_max))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetPanoramic-request>) istream)
  "Deserializes a message object of type '<GetPanoramic-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'head_pan_min) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'head_pan_max) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'head_tilt_min) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'head_tilt_max) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetPanoramic-request>)))
  "Returns string type for a service object of type '<GetPanoramic-request>"
  "vision_msgs/GetPanoramicRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPanoramic-request)))
  "Returns string type for a service object of type 'GetPanoramic-request"
  "vision_msgs/GetPanoramicRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetPanoramic-request>)))
  "Returns md5sum for a message object of type '<GetPanoramic-request>"
  "7803f004018fa919db3f773819997d5d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetPanoramic-request)))
  "Returns md5sum for a message object of type 'GetPanoramic-request"
  "7803f004018fa919db3f773819997d5d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetPanoramic-request>)))
  "Returns full string definition for message of type '<GetPanoramic-request>"
  (cl:format cl:nil "float32 head_pan_min~%float32 head_pan_max~%float32 head_tilt_min~%float32 head_tilt_max~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetPanoramic-request)))
  "Returns full string definition for message of type 'GetPanoramic-request"
  (cl:format cl:nil "float32 head_pan_min~%float32 head_pan_max~%float32 head_tilt_min~%float32 head_tilt_max~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetPanoramic-request>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetPanoramic-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetPanoramic-request
    (cl:cons ':head_pan_min (head_pan_min msg))
    (cl:cons ':head_pan_max (head_pan_max msg))
    (cl:cons ':head_tilt_min (head_tilt_min msg))
    (cl:cons ':head_tilt_max (head_tilt_max msg))
))
;//! \htmlinclude GetPanoramic-response.msg.html

(cl:defclass <GetPanoramic-response> (roslisp-msg-protocol:ros-message)
  ((panoramic_image
    :reader panoramic_image
    :initarg :panoramic_image
    :type sensor_msgs-msg:Image
    :initform (cl:make-instance 'sensor_msgs-msg:Image))
   (panoramic_cloud
    :reader panoramic_cloud
    :initarg :panoramic_cloud
    :type sensor_msgs-msg:PointCloud2
    :initform (cl:make-instance 'sensor_msgs-msg:PointCloud2)))
)

(cl:defclass GetPanoramic-response (<GetPanoramic-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetPanoramic-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetPanoramic-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<GetPanoramic-response> is deprecated: use vision_msgs-srv:GetPanoramic-response instead.")))

(cl:ensure-generic-function 'panoramic_image-val :lambda-list '(m))
(cl:defmethod panoramic_image-val ((m <GetPanoramic-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:panoramic_image-val is deprecated.  Use vision_msgs-srv:panoramic_image instead.")
  (panoramic_image m))

(cl:ensure-generic-function 'panoramic_cloud-val :lambda-list '(m))
(cl:defmethod panoramic_cloud-val ((m <GetPanoramic-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:panoramic_cloud-val is deprecated.  Use vision_msgs-srv:panoramic_cloud instead.")
  (panoramic_cloud m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetPanoramic-response>) ostream)
  "Serializes a message object of type '<GetPanoramic-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'panoramic_image) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'panoramic_cloud) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetPanoramic-response>) istream)
  "Deserializes a message object of type '<GetPanoramic-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'panoramic_image) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'panoramic_cloud) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetPanoramic-response>)))
  "Returns string type for a service object of type '<GetPanoramic-response>"
  "vision_msgs/GetPanoramicResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPanoramic-response)))
  "Returns string type for a service object of type 'GetPanoramic-response"
  "vision_msgs/GetPanoramicResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetPanoramic-response>)))
  "Returns md5sum for a message object of type '<GetPanoramic-response>"
  "7803f004018fa919db3f773819997d5d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetPanoramic-response)))
  "Returns md5sum for a message object of type 'GetPanoramic-response"
  "7803f004018fa919db3f773819997d5d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetPanoramic-response>)))
  "Returns full string definition for message of type '<GetPanoramic-response>"
  (cl:format cl:nil "sensor_msgs/Image        panoramic_image~%sensor_msgs/PointCloud2  panoramic_cloud~%~%================================================================================~%MSG: sensor_msgs/Image~%# This message contains an uncompressed image~%# (0, 0) is at top-left corner of image~%#~%~%Header header        # Header timestamp should be acquisition time of image~%                     # Header frame_id should be optical frame of camera~%                     # origin of frame should be optical center of cameara~%                     # +x should point to the right in the image~%                     # +y should point down in the image~%                     # +z should point into to plane of the image~%                     # If the frame_id here and the frame_id of the CameraInfo~%                     # message associated with the image conflict~%                     # the behavior is undefined~%~%uint32 height         # image height, that is, number of rows~%uint32 width          # image width, that is, number of columns~%~%# The legal values for encoding are in file src/image_encodings.cpp~%# If you want to standardize a new string format, join~%# ros-users@lists.sourceforge.net and send an email proposing a new encoding.~%~%string encoding       # Encoding of pixels -- channel meaning, ordering, size~%                      # taken from the list of strings in include/sensor_msgs/image_encodings.h~%~%uint8 is_bigendian    # is this data bigendian?~%uint32 step           # Full row length in bytes~%uint8[] data          # actual matrix data, size is (step * rows)~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetPanoramic-response)))
  "Returns full string definition for message of type 'GetPanoramic-response"
  (cl:format cl:nil "sensor_msgs/Image        panoramic_image~%sensor_msgs/PointCloud2  panoramic_cloud~%~%================================================================================~%MSG: sensor_msgs/Image~%# This message contains an uncompressed image~%# (0, 0) is at top-left corner of image~%#~%~%Header header        # Header timestamp should be acquisition time of image~%                     # Header frame_id should be optical frame of camera~%                     # origin of frame should be optical center of cameara~%                     # +x should point to the right in the image~%                     # +y should point down in the image~%                     # +z should point into to plane of the image~%                     # If the frame_id here and the frame_id of the CameraInfo~%                     # message associated with the image conflict~%                     # the behavior is undefined~%~%uint32 height         # image height, that is, number of rows~%uint32 width          # image width, that is, number of columns~%~%# The legal values for encoding are in file src/image_encodings.cpp~%# If you want to standardize a new string format, join~%# ros-users@lists.sourceforge.net and send an email proposing a new encoding.~%~%string encoding       # Encoding of pixels -- channel meaning, ordering, size~%                      # taken from the list of strings in include/sensor_msgs/image_encodings.h~%~%uint8 is_bigendian    # is this data bigendian?~%uint32 step           # Full row length in bytes~%uint8[] data          # actual matrix data, size is (step * rows)~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetPanoramic-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'panoramic_image))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'panoramic_cloud))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetPanoramic-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetPanoramic-response
    (cl:cons ':panoramic_image (panoramic_image msg))
    (cl:cons ':panoramic_cloud (panoramic_cloud msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetPanoramic)))
  'GetPanoramic-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetPanoramic)))
  'GetPanoramic-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPanoramic)))
  "Returns string type for a service object of type '<GetPanoramic>"
  "vision_msgs/GetPanoramic")