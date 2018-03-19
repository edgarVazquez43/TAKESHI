;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::VisionObject)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'VisionObject (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::VISIONOBJECT")
  (make-package "VISION_MSGS::VISIONOBJECT"))

(in-package "ROS")
;;//! \htmlinclude VisionObject.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::VisionObject
  :super ros::object
  :slots (_header _id _category _confidence _image _point_cloud _size _pose _bounding_box _bounding_polygon _x _y _width _height _graspable ))

(defmethod vision_msgs::VisionObject
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:id __id) "")
    ((:category __category) "")
    ((:confidence __confidence) 0.0)
    ((:image __image) (instance sensor_msgs::Image :init))
    ((:point_cloud __point_cloud) (instance sensor_msgs::PointCloud2 :init))
    ((:size __size) (instance geometry_msgs::Vector3 :init))
    ((:pose __pose) (instance geometry_msgs::Pose :init))
    ((:bounding_box __bounding_box) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Vector3 :init) r)) r))
    ((:bounding_polygon __bounding_polygon) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Vector3 :init) r)) r))
    ((:x __x) 0)
    ((:y __y) 0)
    ((:width __width) 0)
    ((:height __height) 0)
    ((:graspable __graspable) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _id (string __id))
   (setq _category (string __category))
   (setq _confidence (float __confidence))
   (setq _image __image)
   (setq _point_cloud __point_cloud)
   (setq _size __size)
   (setq _pose __pose)
   (setq _bounding_box __bounding_box)
   (setq _bounding_polygon __bounding_polygon)
   (setq _x (round __x))
   (setq _y (round __y))
   (setq _width (round __width))
   (setq _height (round __height))
   (setq _graspable __graspable)
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
  (:category
   (&optional __category)
   (if __category (setq _category __category)) _category)
  (:confidence
   (&optional __confidence)
   (if __confidence (setq _confidence __confidence)) _confidence)
  (:image
   (&rest __image)
   (if (keywordp (car __image))
       (send* _image __image)
     (progn
       (if __image (setq _image (car __image)))
       _image)))
  (:point_cloud
   (&rest __point_cloud)
   (if (keywordp (car __point_cloud))
       (send* _point_cloud __point_cloud)
     (progn
       (if __point_cloud (setq _point_cloud (car __point_cloud)))
       _point_cloud)))
  (:size
   (&rest __size)
   (if (keywordp (car __size))
       (send* _size __size)
     (progn
       (if __size (setq _size (car __size)))
       _size)))
  (:pose
   (&rest __pose)
   (if (keywordp (car __pose))
       (send* _pose __pose)
     (progn
       (if __pose (setq _pose (car __pose)))
       _pose)))
  (:bounding_box
   (&rest __bounding_box)
   (if (keywordp (car __bounding_box))
       (send* _bounding_box __bounding_box)
     (progn
       (if __bounding_box (setq _bounding_box (car __bounding_box)))
       _bounding_box)))
  (:bounding_polygon
   (&rest __bounding_polygon)
   (if (keywordp (car __bounding_polygon))
       (send* _bounding_polygon __bounding_polygon)
     (progn
       (if __bounding_polygon (setq _bounding_polygon (car __bounding_polygon)))
       _bounding_polygon)))
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:graspable
   (&optional __graspable)
   (if __graspable (setq _graspable __graspable)) _graspable)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _id
    4 (length _id)
    ;; string _category
    4 (length _category)
    ;; float32 _confidence
    4
    ;; sensor_msgs/Image _image
    (send _image :serialization-length)
    ;; sensor_msgs/PointCloud2 _point_cloud
    (send _point_cloud :serialization-length)
    ;; geometry_msgs/Vector3 _size
    (send _size :serialization-length)
    ;; geometry_msgs/Pose _pose
    (send _pose :serialization-length)
    ;; geometry_msgs/Vector3[] _bounding_box
    (apply #'+ (send-all _bounding_box :serialization-length)) 4
    ;; geometry_msgs/Vector3[] _bounding_polygon
    (apply #'+ (send-all _bounding_polygon :serialization-length)) 4
    ;; int32 _x
    4
    ;; int32 _y
    4
    ;; int32 _width
    4
    ;; int32 _height
    4
    ;; bool _graspable
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; string _category
       (write-long (length _category) s) (princ _category s)
     ;; float32 _confidence
       (sys::poke _confidence (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; sensor_msgs/Image _image
       (send _image :serialize s)
     ;; sensor_msgs/PointCloud2 _point_cloud
       (send _point_cloud :serialize s)
     ;; geometry_msgs/Vector3 _size
       (send _size :serialize s)
     ;; geometry_msgs/Pose _pose
       (send _pose :serialize s)
     ;; geometry_msgs/Vector3[] _bounding_box
     (write-long (length _bounding_box) s)
     (dolist (elem _bounding_box)
       (send elem :serialize s)
       )
     ;; geometry_msgs/Vector3[] _bounding_polygon
     (write-long (length _bounding_polygon) s)
     (dolist (elem _bounding_polygon)
       (send elem :serialize s)
       )
     ;; int32 _x
       (write-long _x s)
     ;; int32 _y
       (write-long _y s)
     ;; int32 _width
       (write-long _width s)
     ;; int32 _height
       (write-long _height s)
     ;; bool _graspable
       (if _graspable (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _category
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _category (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32 _confidence
     (setq _confidence (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; sensor_msgs/Image _image
     (send _image :deserialize buf ptr-) (incf ptr- (send _image :serialization-length))
   ;; sensor_msgs/PointCloud2 _point_cloud
     (send _point_cloud :deserialize buf ptr-) (incf ptr- (send _point_cloud :serialization-length))
   ;; geometry_msgs/Vector3 _size
     (send _size :deserialize buf ptr-) (incf ptr- (send _size :serialization-length))
   ;; geometry_msgs/Pose _pose
     (send _pose :deserialize buf ptr-) (incf ptr- (send _pose :serialization-length))
   ;; geometry_msgs/Vector3[] _bounding_box
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _bounding_box (let (r) (dotimes (i n) (push (instance geometry_msgs::Vector3 :init) r)) r))
     (dolist (elem- _bounding_box)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/Vector3[] _bounding_polygon
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _bounding_polygon (let (r) (dotimes (i n) (push (instance geometry_msgs::Vector3 :init) r)) r))
     (dolist (elem- _bounding_polygon)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int32 _x
     (setq _x (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _y
     (setq _y (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _width
     (setq _width (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _height
     (setq _height (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _graspable
     (setq _graspable (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get vision_msgs::VisionObject :md5sum-) "d512ef0753fce8522e8e85f98930c2b2")
(setf (get vision_msgs::VisionObject :datatype-) "vision_msgs/VisionObject")
(setf (get vision_msgs::VisionObject :definition-)
      "std_msgs/Header header
string id                                    #name of identifying the object (milk, orange juice, etc)
string category                              #object type (drink, snack, etc)
float32 confidence                           #value in [0,1] indicating the probability of a correct identification
sensor_msgs/Image image			     #image in rgb of object;
sensor_msgs/PointCloud2 point_cloud          #Point cloud (probably, colored)
geometry_msgs/Vector3 size                   #Size in meters: size in x, y and z
geometry_msgs/Pose pose                      #Centroid and orientation
geometry_msgs/Vector3[] bounding_box         #Two vectors indicating the bounding box
geometry_msgs/Vector3[] bounding_polygon     #N vectors 
int32 x					     #top left x
int32 y					     #top left y
int32 width				     #top widht
int32 height				     #top height
bool graspable                               #graspable by the arm

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

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

")



(provide :vision_msgs/VisionObject "d512ef0753fce8522e8e85f98930c2b2")


