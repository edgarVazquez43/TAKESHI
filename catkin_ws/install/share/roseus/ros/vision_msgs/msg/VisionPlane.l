;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::VisionPlane)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'VisionPlane (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::VISIONPLANE")
  (make-package "VISION_MSGS::VISIONPLANE"))

(in-package "ROS")
;;//! \htmlinclude VisionPlane.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass vision_msgs::VisionPlane
  :super ros::object
  :slots (_id _point_cloud _centroid _normal _bounding_polygon ))

(defmethod vision_msgs::VisionPlane
  (:init
   (&key
    ((:id __id) "")
    ((:point_cloud __point_cloud) (instance sensor_msgs::PointCloud2 :init))
    ((:centroid __centroid) (instance geometry_msgs::Vector3 :init))
    ((:normal __normal) (instance geometry_msgs::Vector3 :init))
    ((:bounding_polygon __bounding_polygon) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Vector3 :init) r)) r))
    )
   (send-super :init)
   (setq _id (string __id))
   (setq _point_cloud __point_cloud)
   (setq _centroid __centroid)
   (setq _normal __normal)
   (setq _bounding_polygon __bounding_polygon)
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:point_cloud
   (&rest __point_cloud)
   (if (keywordp (car __point_cloud))
       (send* _point_cloud __point_cloud)
     (progn
       (if __point_cloud (setq _point_cloud (car __point_cloud)))
       _point_cloud)))
  (:centroid
   (&rest __centroid)
   (if (keywordp (car __centroid))
       (send* _centroid __centroid)
     (progn
       (if __centroid (setq _centroid (car __centroid)))
       _centroid)))
  (:normal
   (&rest __normal)
   (if (keywordp (car __normal))
       (send* _normal __normal)
     (progn
       (if __normal (setq _normal (car __normal)))
       _normal)))
  (:bounding_polygon
   (&rest __bounding_polygon)
   (if (keywordp (car __bounding_polygon))
       (send* _bounding_polygon __bounding_polygon)
     (progn
       (if __bounding_polygon (setq _bounding_polygon (car __bounding_polygon)))
       _bounding_polygon)))
  (:serialization-length
   ()
   (+
    ;; string _id
    4 (length _id)
    ;; sensor_msgs/PointCloud2 _point_cloud
    (send _point_cloud :serialization-length)
    ;; geometry_msgs/Vector3 _centroid
    (send _centroid :serialization-length)
    ;; geometry_msgs/Vector3 _normal
    (send _normal :serialization-length)
    ;; geometry_msgs/Vector3[] _bounding_polygon
    (apply #'+ (send-all _bounding_polygon :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; sensor_msgs/PointCloud2 _point_cloud
       (send _point_cloud :serialize s)
     ;; geometry_msgs/Vector3 _centroid
       (send _centroid :serialize s)
     ;; geometry_msgs/Vector3 _normal
       (send _normal :serialize s)
     ;; geometry_msgs/Vector3[] _bounding_polygon
     (write-long (length _bounding_polygon) s)
     (dolist (elem _bounding_polygon)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; sensor_msgs/PointCloud2 _point_cloud
     (send _point_cloud :deserialize buf ptr-) (incf ptr- (send _point_cloud :serialization-length))
   ;; geometry_msgs/Vector3 _centroid
     (send _centroid :deserialize buf ptr-) (incf ptr- (send _centroid :serialization-length))
   ;; geometry_msgs/Vector3 _normal
     (send _normal :deserialize buf ptr-) (incf ptr- (send _normal :serialization-length))
   ;; geometry_msgs/Vector3[] _bounding_polygon
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _bounding_polygon (let (r) (dotimes (i n) (push (instance geometry_msgs::Vector3 :init) r)) r))
     (dolist (elem- _bounding_polygon)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get vision_msgs::VisionPlane :md5sum-) "9dde39900df0527c4edab2ecf1c2188c")
(setf (get vision_msgs::VisionPlane :datatype-) "vision_msgs/VisionPlane")
(setf (get vision_msgs::VisionPlane :definition-)
      "string id                                    #plane id (desk, floor, etc)
sensor_msgs/PointCloud2 point_cloud          #Point cloud (probably, colored)
geometry_msgs/Vector3 centroid               
geometry_msgs/Vector3 normal                 #normal vector to the plane (should be normalized)
geometry_msgs/Vector3[] bounding_polygon     #N vectors 

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
")



(provide :vision_msgs/VisionPlane "9dde39900df0527c4edab2ecf1c2188c")


