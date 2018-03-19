;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::GetPanoramic)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'GetPanoramic (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::GETPANORAMIC")
  (make-package "VISION_MSGS::GETPANORAMIC"))
(unless (find-package "VISION_MSGS::GETPANORAMICREQUEST")
  (make-package "VISION_MSGS::GETPANORAMICREQUEST"))
(unless (find-package "VISION_MSGS::GETPANORAMICRESPONSE")
  (make-package "VISION_MSGS::GETPANORAMICRESPONSE"))

(in-package "ROS")



(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass vision_msgs::GetPanoramicRequest
  :super ros::object
  :slots (_head_pan_min _head_pan_max _head_tilt_min _head_tilt_max ))

(defmethod vision_msgs::GetPanoramicRequest
  (:init
   (&key
    ((:head_pan_min __head_pan_min) 0.0)
    ((:head_pan_max __head_pan_max) 0.0)
    ((:head_tilt_min __head_tilt_min) 0.0)
    ((:head_tilt_max __head_tilt_max) 0.0)
    )
   (send-super :init)
   (setq _head_pan_min (float __head_pan_min))
   (setq _head_pan_max (float __head_pan_max))
   (setq _head_tilt_min (float __head_tilt_min))
   (setq _head_tilt_max (float __head_tilt_max))
   self)
  (:head_pan_min
   (&optional __head_pan_min)
   (if __head_pan_min (setq _head_pan_min __head_pan_min)) _head_pan_min)
  (:head_pan_max
   (&optional __head_pan_max)
   (if __head_pan_max (setq _head_pan_max __head_pan_max)) _head_pan_max)
  (:head_tilt_min
   (&optional __head_tilt_min)
   (if __head_tilt_min (setq _head_tilt_min __head_tilt_min)) _head_tilt_min)
  (:head_tilt_max
   (&optional __head_tilt_max)
   (if __head_tilt_max (setq _head_tilt_max __head_tilt_max)) _head_tilt_max)
  (:serialization-length
   ()
   (+
    ;; float32 _head_pan_min
    4
    ;; float32 _head_pan_max
    4
    ;; float32 _head_tilt_min
    4
    ;; float32 _head_tilt_max
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _head_pan_min
       (sys::poke _head_pan_min (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _head_pan_max
       (sys::poke _head_pan_max (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _head_tilt_min
       (sys::poke _head_tilt_min (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _head_tilt_max
       (sys::poke _head_tilt_max (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _head_pan_min
     (setq _head_pan_min (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _head_pan_max
     (setq _head_pan_max (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _head_tilt_min
     (setq _head_tilt_min (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _head_tilt_max
     (setq _head_tilt_max (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass vision_msgs::GetPanoramicResponse
  :super ros::object
  :slots (_panoramic_image _panoramic_cloud ))

(defmethod vision_msgs::GetPanoramicResponse
  (:init
   (&key
    ((:panoramic_image __panoramic_image) (instance sensor_msgs::Image :init))
    ((:panoramic_cloud __panoramic_cloud) (instance sensor_msgs::PointCloud2 :init))
    )
   (send-super :init)
   (setq _panoramic_image __panoramic_image)
   (setq _panoramic_cloud __panoramic_cloud)
   self)
  (:panoramic_image
   (&rest __panoramic_image)
   (if (keywordp (car __panoramic_image))
       (send* _panoramic_image __panoramic_image)
     (progn
       (if __panoramic_image (setq _panoramic_image (car __panoramic_image)))
       _panoramic_image)))
  (:panoramic_cloud
   (&rest __panoramic_cloud)
   (if (keywordp (car __panoramic_cloud))
       (send* _panoramic_cloud __panoramic_cloud)
     (progn
       (if __panoramic_cloud (setq _panoramic_cloud (car __panoramic_cloud)))
       _panoramic_cloud)))
  (:serialization-length
   ()
   (+
    ;; sensor_msgs/Image _panoramic_image
    (send _panoramic_image :serialization-length)
    ;; sensor_msgs/PointCloud2 _panoramic_cloud
    (send _panoramic_cloud :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; sensor_msgs/Image _panoramic_image
       (send _panoramic_image :serialize s)
     ;; sensor_msgs/PointCloud2 _panoramic_cloud
       (send _panoramic_cloud :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; sensor_msgs/Image _panoramic_image
     (send _panoramic_image :deserialize buf ptr-) (incf ptr- (send _panoramic_image :serialization-length))
   ;; sensor_msgs/PointCloud2 _panoramic_cloud
     (send _panoramic_cloud :deserialize buf ptr-) (incf ptr- (send _panoramic_cloud :serialization-length))
   ;;
   self)
  )

(defclass vision_msgs::GetPanoramic
  :super ros::object
  :slots ())

(setf (get vision_msgs::GetPanoramic :md5sum-) "7803f004018fa919db3f773819997d5d")
(setf (get vision_msgs::GetPanoramic :datatype-) "vision_msgs/GetPanoramic")
(setf (get vision_msgs::GetPanoramic :request) vision_msgs::GetPanoramicRequest)
(setf (get vision_msgs::GetPanoramic :response) vision_msgs::GetPanoramicResponse)

(defmethod vision_msgs::GetPanoramicRequest
  (:response () (instance vision_msgs::GetPanoramicResponse :init)))

(setf (get vision_msgs::GetPanoramicRequest :md5sum-) "7803f004018fa919db3f773819997d5d")
(setf (get vision_msgs::GetPanoramicRequest :datatype-) "vision_msgs/GetPanoramicRequest")
(setf (get vision_msgs::GetPanoramicRequest :definition-)
      "float32 head_pan_min
float32 head_pan_max
float32 head_tilt_min
float32 head_tilt_max
---
sensor_msgs/Image        panoramic_image
sensor_msgs/PointCloud2  panoramic_cloud

================================================================================
MSG: sensor_msgs/Image
# This message contains an uncompressed image
# (0, 0) is at top-left corner of image
#

Header header        # Header timestamp should be acquisition time of image
                     # Header frame_id should be optical frame of camera
                     # origin of frame should be optical center of cameara
                     # +x should point to the right in the image
                     # +y should point down in the image
                     # +z should point into to plane of the image
                     # If the frame_id here and the frame_id of the CameraInfo
                     # message associated with the image conflict
                     # the behavior is undefined

uint32 height         # image height, that is, number of rows
uint32 width          # image width, that is, number of columns

# The legal values for encoding are in file src/image_encodings.cpp
# If you want to standardize a new string format, join
# ros-users@lists.sourceforge.net and send an email proposing a new encoding.

string encoding       # Encoding of pixels -- channel meaning, ordering, size
                      # taken from the list of strings in include/sensor_msgs/image_encodings.h

uint8 is_bigendian    # is this data bigendian?
uint32 step           # Full row length in bytes
uint8[] data          # actual matrix data, size is (step * rows)

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: sensor_msgs/PointCloud2
# This message holds a collection of N-dimensional points, which may
# contain additional information such as normals, intensity, etc. The
# point data is stored as a binary blob, its layout described by the
# contents of the \"fields\" array.

# The point cloud data may be organized 2d (image-like) or 1d
# (unordered). Point clouds organized as 2d images may be produced by
# camera depth sensors such as stereo or time-of-flight.

# Time of sensor data acquisition, and the coordinate frame ID (for 3d
# points).
Header header

# 2D structure of the point cloud. If the cloud is unordered, height is
# 1 and width is the length of the point cloud.
uint32 height
uint32 width

# Describes the channels and their layout in the binary data blob.
PointField[] fields

bool    is_bigendian # Is this data bigendian?
uint32  point_step   # Length of a point in bytes
uint32  row_step     # Length of a row in bytes
uint8[] data         # Actual point data, size is (row_step*height)

bool is_dense        # True if there are no invalid points

================================================================================
MSG: sensor_msgs/PointField
# This message holds the description of one point entry in the
# PointCloud2 message format.
uint8 INT8    = 1
uint8 UINT8   = 2
uint8 INT16   = 3
uint8 UINT16  = 4
uint8 INT32   = 5
uint8 UINT32  = 6
uint8 FLOAT32 = 7
uint8 FLOAT64 = 8

string name      # Name of field
uint32 offset    # Offset from start of point struct
uint8  datatype  # Datatype enumeration, see above
uint32 count     # How many elements in the field
")

(setf (get vision_msgs::GetPanoramicResponse :md5sum-) "7803f004018fa919db3f773819997d5d")
(setf (get vision_msgs::GetPanoramicResponse :datatype-) "vision_msgs/GetPanoramicResponse")
(setf (get vision_msgs::GetPanoramicResponse :definition-)
      "float32 head_pan_min
float32 head_pan_max
float32 head_tilt_min
float32 head_tilt_max
---
sensor_msgs/Image        panoramic_image
sensor_msgs/PointCloud2  panoramic_cloud

================================================================================
MSG: sensor_msgs/Image
# This message contains an uncompressed image
# (0, 0) is at top-left corner of image
#

Header header        # Header timestamp should be acquisition time of image
                     # Header frame_id should be optical frame of camera
                     # origin of frame should be optical center of cameara
                     # +x should point to the right in the image
                     # +y should point down in the image
                     # +z should point into to plane of the image
                     # If the frame_id here and the frame_id of the CameraInfo
                     # message associated with the image conflict
                     # the behavior is undefined

uint32 height         # image height, that is, number of rows
uint32 width          # image width, that is, number of columns

# The legal values for encoding are in file src/image_encodings.cpp
# If you want to standardize a new string format, join
# ros-users@lists.sourceforge.net and send an email proposing a new encoding.

string encoding       # Encoding of pixels -- channel meaning, ordering, size
                      # taken from the list of strings in include/sensor_msgs/image_encodings.h

uint8 is_bigendian    # is this data bigendian?
uint32 step           # Full row length in bytes
uint8[] data          # actual matrix data, size is (step * rows)

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: sensor_msgs/PointCloud2
# This message holds a collection of N-dimensional points, which may
# contain additional information such as normals, intensity, etc. The
# point data is stored as a binary blob, its layout described by the
# contents of the \"fields\" array.

# The point cloud data may be organized 2d (image-like) or 1d
# (unordered). Point clouds organized as 2d images may be produced by
# camera depth sensors such as stereo or time-of-flight.

# Time of sensor data acquisition, and the coordinate frame ID (for 3d
# points).
Header header

# 2D structure of the point cloud. If the cloud is unordered, height is
# 1 and width is the length of the point cloud.
uint32 height
uint32 width

# Describes the channels and their layout in the binary data blob.
PointField[] fields

bool    is_bigendian # Is this data bigendian?
uint32  point_step   # Length of a point in bytes
uint32  row_step     # Length of a row in bytes
uint8[] data         # Actual point data, size is (row_step*height)

bool is_dense        # True if there are no invalid points

================================================================================
MSG: sensor_msgs/PointField
# This message holds the description of one point entry in the
# PointCloud2 message format.
uint8 INT8    = 1
uint8 UINT8   = 2
uint8 INT16   = 3
uint8 UINT16  = 4
uint8 INT32   = 5
uint8 UINT32  = 6
uint8 FLOAT32 = 7
uint8 FLOAT64 = 8

string name      # Name of field
uint32 offset    # Offset from start of point struct
uint8  datatype  # Datatype enumeration, see above
uint32 count     # How many elements in the field
")



(provide :vision_msgs/GetPanoramic "7803f004018fa919db3f773819997d5d")


