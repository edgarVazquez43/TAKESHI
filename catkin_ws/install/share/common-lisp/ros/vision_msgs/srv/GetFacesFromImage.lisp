; Auto-generated. Do not edit!


(cl:in-package vision_msgs-srv)


;//! \htmlinclude GetFacesFromImage-request.msg.html

(cl:defclass <GetFacesFromImage-request> (roslisp-msg-protocol:ros-message)
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

(cl:defclass GetFacesFromImage-request (<GetFacesFromImage-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetFacesFromImage-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetFacesFromImage-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<GetFacesFromImage-request> is deprecated: use vision_msgs-srv:GetFacesFromImage-request instead.")))

(cl:ensure-generic-function 'panoramic_image-val :lambda-list '(m))
(cl:defmethod panoramic_image-val ((m <GetFacesFromImage-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:panoramic_image-val is deprecated.  Use vision_msgs-srv:panoramic_image instead.")
  (panoramic_image m))

(cl:ensure-generic-function 'panoramic_cloud-val :lambda-list '(m))
(cl:defmethod panoramic_cloud-val ((m <GetFacesFromImage-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:panoramic_cloud-val is deprecated.  Use vision_msgs-srv:panoramic_cloud instead.")
  (panoramic_cloud m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetFacesFromImage-request>) ostream)
  "Serializes a message object of type '<GetFacesFromImage-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'panoramic_image) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'panoramic_cloud) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetFacesFromImage-request>) istream)
  "Deserializes a message object of type '<GetFacesFromImage-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'panoramic_image) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'panoramic_cloud) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetFacesFromImage-request>)))
  "Returns string type for a service object of type '<GetFacesFromImage-request>"
  "vision_msgs/GetFacesFromImageRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetFacesFromImage-request)))
  "Returns string type for a service object of type 'GetFacesFromImage-request"
  "vision_msgs/GetFacesFromImageRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetFacesFromImage-request>)))
  "Returns md5sum for a message object of type '<GetFacesFromImage-request>"
  "c4982e3d6aa296c735fbed16dcc632c8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetFacesFromImage-request)))
  "Returns md5sum for a message object of type 'GetFacesFromImage-request"
  "c4982e3d6aa296c735fbed16dcc632c8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetFacesFromImage-request>)))
  "Returns full string definition for message of type '<GetFacesFromImage-request>"
  (cl:format cl:nil "sensor_msgs/Image        panoramic_image~%sensor_msgs/PointCloud2  panoramic_cloud~%~%================================================================================~%MSG: sensor_msgs/Image~%# This message contains an uncompressed image~%# (0, 0) is at top-left corner of image~%#~%~%Header header        # Header timestamp should be acquisition time of image~%                     # Header frame_id should be optical frame of camera~%                     # origin of frame should be optical center of cameara~%                     # +x should point to the right in the image~%                     # +y should point down in the image~%                     # +z should point into to plane of the image~%                     # If the frame_id here and the frame_id of the CameraInfo~%                     # message associated with the image conflict~%                     # the behavior is undefined~%~%uint32 height         # image height, that is, number of rows~%uint32 width          # image width, that is, number of columns~%~%# The legal values for encoding are in file src/image_encodings.cpp~%# If you want to standardize a new string format, join~%# ros-users@lists.sourceforge.net and send an email proposing a new encoding.~%~%string encoding       # Encoding of pixels -- channel meaning, ordering, size~%                      # taken from the list of strings in include/sensor_msgs/image_encodings.h~%~%uint8 is_bigendian    # is this data bigendian?~%uint32 step           # Full row length in bytes~%uint8[] data          # actual matrix data, size is (step * rows)~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetFacesFromImage-request)))
  "Returns full string definition for message of type 'GetFacesFromImage-request"
  (cl:format cl:nil "sensor_msgs/Image        panoramic_image~%sensor_msgs/PointCloud2  panoramic_cloud~%~%================================================================================~%MSG: sensor_msgs/Image~%# This message contains an uncompressed image~%# (0, 0) is at top-left corner of image~%#~%~%Header header        # Header timestamp should be acquisition time of image~%                     # Header frame_id should be optical frame of camera~%                     # origin of frame should be optical center of cameara~%                     # +x should point to the right in the image~%                     # +y should point down in the image~%                     # +z should point into to plane of the image~%                     # If the frame_id here and the frame_id of the CameraInfo~%                     # message associated with the image conflict~%                     # the behavior is undefined~%~%uint32 height         # image height, that is, number of rows~%uint32 width          # image width, that is, number of columns~%~%# The legal values for encoding are in file src/image_encodings.cpp~%# If you want to standardize a new string format, join~%# ros-users@lists.sourceforge.net and send an email proposing a new encoding.~%~%string encoding       # Encoding of pixels -- channel meaning, ordering, size~%                      # taken from the list of strings in include/sensor_msgs/image_encodings.h~%~%uint8 is_bigendian    # is this data bigendian?~%uint32 step           # Full row length in bytes~%uint8[] data          # actual matrix data, size is (step * rows)~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sensor_msgs/PointCloud2~%# This message holds a collection of N-dimensional points, which may~%# contain additional information such as normals, intensity, etc. The~%# point data is stored as a binary blob, its layout described by the~%# contents of the \"fields\" array.~%~%# The point cloud data may be organized 2d (image-like) or 1d~%# (unordered). Point clouds organized as 2d images may be produced by~%# camera depth sensors such as stereo or time-of-flight.~%~%# Time of sensor data acquisition, and the coordinate frame ID (for 3d~%# points).~%Header header~%~%# 2D structure of the point cloud. If the cloud is unordered, height is~%# 1 and width is the length of the point cloud.~%uint32 height~%uint32 width~%~%# Describes the channels and their layout in the binary data blob.~%PointField[] fields~%~%bool    is_bigendian # Is this data bigendian?~%uint32  point_step   # Length of a point in bytes~%uint32  row_step     # Length of a row in bytes~%uint8[] data         # Actual point data, size is (row_step*height)~%~%bool is_dense        # True if there are no invalid points~%~%================================================================================~%MSG: sensor_msgs/PointField~%# This message holds the description of one point entry in the~%# PointCloud2 message format.~%uint8 INT8    = 1~%uint8 UINT8   = 2~%uint8 INT16   = 3~%uint8 UINT16  = 4~%uint8 INT32   = 5~%uint8 UINT32  = 6~%uint8 FLOAT32 = 7~%uint8 FLOAT64 = 8~%~%string name      # Name of field~%uint32 offset    # Offset from start of point struct~%uint8  datatype  # Datatype enumeration, see above~%uint32 count     # How many elements in the field~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetFacesFromImage-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'panoramic_image))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'panoramic_cloud))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetFacesFromImage-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetFacesFromImage-request
    (cl:cons ':panoramic_image (panoramic_image msg))
    (cl:cons ':panoramic_cloud (panoramic_cloud msg))
))
;//! \htmlinclude GetFacesFromImage-response.msg.html

(cl:defclass <GetFacesFromImage-response> (roslisp-msg-protocol:ros-message)
  ((faces
    :reader faces
    :initarg :faces
    :type vision_msgs-msg:VisionFaceObjects
    :initform (cl:make-instance 'vision_msgs-msg:VisionFaceObjects)))
)

(cl:defclass GetFacesFromImage-response (<GetFacesFromImage-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetFacesFromImage-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetFacesFromImage-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<GetFacesFromImage-response> is deprecated: use vision_msgs-srv:GetFacesFromImage-response instead.")))

(cl:ensure-generic-function 'faces-val :lambda-list '(m))
(cl:defmethod faces-val ((m <GetFacesFromImage-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:faces-val is deprecated.  Use vision_msgs-srv:faces instead.")
  (faces m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetFacesFromImage-response>) ostream)
  "Serializes a message object of type '<GetFacesFromImage-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'faces) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetFacesFromImage-response>) istream)
  "Deserializes a message object of type '<GetFacesFromImage-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'faces) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetFacesFromImage-response>)))
  "Returns string type for a service object of type '<GetFacesFromImage-response>"
  "vision_msgs/GetFacesFromImageResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetFacesFromImage-response)))
  "Returns string type for a service object of type 'GetFacesFromImage-response"
  "vision_msgs/GetFacesFromImageResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetFacesFromImage-response>)))
  "Returns md5sum for a message object of type '<GetFacesFromImage-response>"
  "c4982e3d6aa296c735fbed16dcc632c8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetFacesFromImage-response)))
  "Returns md5sum for a message object of type 'GetFacesFromImage-response"
  "c4982e3d6aa296c735fbed16dcc632c8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetFacesFromImage-response>)))
  "Returns full string definition for message of type '<GetFacesFromImage-response>"
  (cl:format cl:nil "vision_msgs/VisionFaceObjects        faces~%~%~%================================================================================~%MSG: vision_msgs/VisionFaceObjects~%std_msgs/Header header~%vision_msgs/VisionFaceObject[] recog_faces~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/VisionFaceObject~%string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetFacesFromImage-response)))
  "Returns full string definition for message of type 'GetFacesFromImage-response"
  (cl:format cl:nil "vision_msgs/VisionFaceObjects        faces~%~%~%================================================================================~%MSG: vision_msgs/VisionFaceObjects~%std_msgs/Header header~%vision_msgs/VisionFaceObject[] recog_faces~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/VisionFaceObject~%string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetFacesFromImage-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'faces))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetFacesFromImage-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetFacesFromImage-response
    (cl:cons ':faces (faces msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetFacesFromImage)))
  'GetFacesFromImage-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetFacesFromImage)))
  'GetFacesFromImage-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetFacesFromImage)))
  "Returns string type for a service object of type '<GetFacesFromImage>"
  "vision_msgs/GetFacesFromImage")