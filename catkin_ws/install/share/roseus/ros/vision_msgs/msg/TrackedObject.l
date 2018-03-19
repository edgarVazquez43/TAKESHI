;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::TrackedObject)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'TrackedObject (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::TRACKEDOBJECT")
  (make-package "VISION_MSGS::TRACKEDOBJECT"))

(in-package "ROS")
;;//! \htmlinclude TrackedObject.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::TrackedObject
  :super ros::object
  :slots (_header _id _position _isFound _confidence _point_cloud ))

(defmethod vision_msgs::TrackedObject
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:id __id) "")
    ((:position __position) (instance geometry_msgs::Point :init))
    ((:isFound __isFound) nil)
    ((:confidence __confidence) 0.0)
    ((:point_cloud __point_cloud) (instance sensor_msgs::PointCloud2 :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _id (string __id))
   (setq _position __position)
   (setq _isFound __isFound)
   (setq _confidence (float __confidence))
   (setq _point_cloud __point_cloud)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:isFound
   (&optional __isFound)
   (if __isFound (setq _isFound __isFound)) _isFound)
  (:confidence
   (&optional __confidence)
   (if __confidence (setq _confidence __confidence)) _confidence)
  (:point_cloud
   (&rest __point_cloud)
   (if (keywordp (car __point_cloud))
       (send* _point_cloud __point_cloud)
     (progn
       (if __point_cloud (setq _point_cloud (car __point_cloud)))
       _point_cloud)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _id
    4 (length _id)
    ;; geometry_msgs/Point _position
    (send _position :serialization-length)
    ;; bool _isFound
    1
    ;; float32 _confidence
    4
    ;; sensor_msgs/PointCloud2 _point_cloud
    (send _point_cloud :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; geometry_msgs/Point _position
       (send _position :serialize s)
     ;; bool _isFound
       (if _isFound (write-byte -1 s) (write-byte 0 s))
     ;; float32 _confidence
       (sys::poke _confidence (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; sensor_msgs/PointCloud2 _point_cloud
       (send _point_cloud :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Point _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; bool _isFound
     (setq _isFound (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _confidence
     (setq _confidence (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; sensor_msgs/PointCloud2 _point_cloud
     (send _point_cloud :deserialize buf ptr-) (incf ptr- (send _point_cloud :serialization-length))
   ;;
   self)
  )

(setf (get vision_msgs::TrackedObject :md5sum-) "bf450beb54877eb48ff4d12c71031b6e")
(setf (get vision_msgs::TrackedObject :datatype-) "vision_msgs/TrackedObject")
(setf (get vision_msgs::TrackedObject :definition-)
      "std_msgs/Header header
string id                            # name of identifying the object (milk, orange juice, etc)
geometry_msgs/Point position         # position in XYZ
bool isFound                         # is current position (is found) or last position (can be occluded, lost, etc.)
float32 confidence                   # value in [0,1] indicating the probability of a correct identification
sensor_msgs/PointCloud2 point_cloud  # Point cloud (probably, colored)
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
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

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



(provide :vision_msgs/TrackedObject "bf450beb54877eb48ff4d12c71031b6e")


