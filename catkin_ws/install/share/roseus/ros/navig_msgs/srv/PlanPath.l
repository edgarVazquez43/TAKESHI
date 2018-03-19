;; Auto-generated. Do not edit!


(when (boundp 'navig_msgs::PlanPath)
  (if (not (find-package "NAVIG_MSGS"))
    (make-package "NAVIG_MSGS"))
  (shadow 'PlanPath (find-package "NAVIG_MSGS")))
(unless (find-package "NAVIG_MSGS::PLANPATH")
  (make-package "NAVIG_MSGS::PLANPATH"))
(unless (find-package "NAVIG_MSGS::PLANPATHREQUEST")
  (make-package "NAVIG_MSGS::PLANPATHREQUEST"))
(unless (find-package "NAVIG_MSGS::PLANPATHRESPONSE")
  (make-package "NAVIG_MSGS::PLANPATHRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(if (not (find-package "NAV_MSGS"))
  (ros::roseus-add-msgs "nav_msgs"))


(defclass navig_msgs::PlanPathRequest
  :super ros::object
  :slots (_start_pose _goal_pose _start_location_id _goal_location_id ))

(defmethod navig_msgs::PlanPathRequest
  (:init
   (&key
    ((:start_pose __start_pose) (instance geometry_msgs::Pose :init))
    ((:goal_pose __goal_pose) (instance geometry_msgs::Pose :init))
    ((:start_location_id __start_location_id) "")
    ((:goal_location_id __goal_location_id) "")
    )
   (send-super :init)
   (setq _start_pose __start_pose)
   (setq _goal_pose __goal_pose)
   (setq _start_location_id (string __start_location_id))
   (setq _goal_location_id (string __goal_location_id))
   self)
  (:start_pose
   (&rest __start_pose)
   (if (keywordp (car __start_pose))
       (send* _start_pose __start_pose)
     (progn
       (if __start_pose (setq _start_pose (car __start_pose)))
       _start_pose)))
  (:goal_pose
   (&rest __goal_pose)
   (if (keywordp (car __goal_pose))
       (send* _goal_pose __goal_pose)
     (progn
       (if __goal_pose (setq _goal_pose (car __goal_pose)))
       _goal_pose)))
  (:start_location_id
   (&optional __start_location_id)
   (if __start_location_id (setq _start_location_id __start_location_id)) _start_location_id)
  (:goal_location_id
   (&optional __goal_location_id)
   (if __goal_location_id (setq _goal_location_id __goal_location_id)) _goal_location_id)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose _start_pose
    (send _start_pose :serialization-length)
    ;; geometry_msgs/Pose _goal_pose
    (send _goal_pose :serialization-length)
    ;; string _start_location_id
    4 (length _start_location_id)
    ;; string _goal_location_id
    4 (length _goal_location_id)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose _start_pose
       (send _start_pose :serialize s)
     ;; geometry_msgs/Pose _goal_pose
       (send _goal_pose :serialize s)
     ;; string _start_location_id
       (write-long (length _start_location_id) s) (princ _start_location_id s)
     ;; string _goal_location_id
       (write-long (length _goal_location_id) s) (princ _goal_location_id s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose _start_pose
     (send _start_pose :deserialize buf ptr-) (incf ptr- (send _start_pose :serialization-length))
   ;; geometry_msgs/Pose _goal_pose
     (send _goal_pose :deserialize buf ptr-) (incf ptr- (send _goal_pose :serialization-length))
   ;; string _start_location_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _start_location_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _goal_location_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _goal_location_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass navig_msgs::PlanPathResponse
  :super ros::object
  :slots (_path ))

(defmethod navig_msgs::PlanPathResponse
  (:init
   (&key
    ((:path __path) (instance nav_msgs::Path :init))
    )
   (send-super :init)
   (setq _path __path)
   self)
  (:path
   (&rest __path)
   (if (keywordp (car __path))
       (send* _path __path)
     (progn
       (if __path (setq _path (car __path)))
       _path)))
  (:serialization-length
   ()
   (+
    ;; nav_msgs/Path _path
    (send _path :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; nav_msgs/Path _path
       (send _path :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; nav_msgs/Path _path
     (send _path :deserialize buf ptr-) (incf ptr- (send _path :serialization-length))
   ;;
   self)
  )

(defclass navig_msgs::PlanPath
  :super ros::object
  :slots ())

(setf (get navig_msgs::PlanPath :md5sum-) "d4c7fd7dba298b47cf73caf450fd8a9f")
(setf (get navig_msgs::PlanPath :datatype-) "navig_msgs/PlanPath")
(setf (get navig_msgs::PlanPath :request) navig_msgs::PlanPathRequest)
(setf (get navig_msgs::PlanPath :response) navig_msgs::PlanPathResponse)

(defmethod navig_msgs::PlanPathRequest
  (:response () (instance navig_msgs::PlanPathResponse :init)))

(setf (get navig_msgs::PlanPathRequest :md5sum-) "d4c7fd7dba298b47cf73caf450fd8a9f")
(setf (get navig_msgs::PlanPathRequest :datatype-) "navig_msgs/PlanPathRequest")
(setf (get navig_msgs::PlanPathRequest :definition-)
      "geometry_msgs/Pose start_pose
geometry_msgs/Pose goal_pose
string start_location_id
string goal_location_id

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
---
nav_msgs/Path path








================================================================================
MSG: nav_msgs/Path
#An array of poses that represents a Path for a robot to follow
Header header
geometry_msgs/PoseStamped[] poses

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
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

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

(setf (get navig_msgs::PlanPathResponse :md5sum-) "d4c7fd7dba298b47cf73caf450fd8a9f")
(setf (get navig_msgs::PlanPathResponse :datatype-) "navig_msgs/PlanPathResponse")
(setf (get navig_msgs::PlanPathResponse :definition-)
      "geometry_msgs/Pose start_pose
geometry_msgs/Pose goal_pose
string start_location_id
string goal_location_id

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
---
nav_msgs/Path path








================================================================================
MSG: nav_msgs/Path
#An array of poses that represents a Path for a robot to follow
Header header
geometry_msgs/PoseStamped[] poses

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
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

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



(provide :navig_msgs/PlanPath "d4c7fd7dba298b47cf73caf450fd8a9f")


