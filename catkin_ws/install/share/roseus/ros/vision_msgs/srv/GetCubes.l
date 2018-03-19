;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::GetCubes)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'GetCubes (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::GETCUBES")
  (make-package "VISION_MSGS::GETCUBES"))
(unless (find-package "VISION_MSGS::GETCUBESREQUEST")
  (make-package "VISION_MSGS::GETCUBESREQUEST"))
(unless (find-package "VISION_MSGS::GETCUBESRESPONSE")
  (make-package "VISION_MSGS::GETCUBESRESPONSE"))

(in-package "ROS")





(defclass vision_msgs::GetCubesRequest
  :super ros::object
  :slots (_cubes_input ))

(defmethod vision_msgs::GetCubesRequest
  (:init
   (&key
    ((:cubes_input __cubes_input) (instance vision_msgs::CubesSegmented :init))
    )
   (send-super :init)
   (setq _cubes_input __cubes_input)
   self)
  (:cubes_input
   (&rest __cubes_input)
   (if (keywordp (car __cubes_input))
       (send* _cubes_input __cubes_input)
     (progn
       (if __cubes_input (setq _cubes_input (car __cubes_input)))
       _cubes_input)))
  (:serialization-length
   ()
   (+
    ;; vision_msgs/CubesSegmented _cubes_input
    (send _cubes_input :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; vision_msgs/CubesSegmented _cubes_input
       (send _cubes_input :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; vision_msgs/CubesSegmented _cubes_input
     (send _cubes_input :deserialize buf ptr-) (incf ptr- (send _cubes_input :serialization-length))
   ;;
   self)
  )

(defclass vision_msgs::GetCubesResponse
  :super ros::object
  :slots (_cubes_output ))

(defmethod vision_msgs::GetCubesResponse
  (:init
   (&key
    ((:cubes_output __cubes_output) (instance vision_msgs::CubesSegmented :init))
    )
   (send-super :init)
   (setq _cubes_output __cubes_output)
   self)
  (:cubes_output
   (&rest __cubes_output)
   (if (keywordp (car __cubes_output))
       (send* _cubes_output __cubes_output)
     (progn
       (if __cubes_output (setq _cubes_output (car __cubes_output)))
       _cubes_output)))
  (:serialization-length
   ()
   (+
    ;; vision_msgs/CubesSegmented _cubes_output
    (send _cubes_output :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; vision_msgs/CubesSegmented _cubes_output
       (send _cubes_output :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; vision_msgs/CubesSegmented _cubes_output
     (send _cubes_output :deserialize buf ptr-) (incf ptr- (send _cubes_output :serialization-length))
   ;;
   self)
  )

(defclass vision_msgs::GetCubes
  :super ros::object
  :slots ())

(setf (get vision_msgs::GetCubes :md5sum-) "a2d88941f0bdf4936824e45f204e46ff")
(setf (get vision_msgs::GetCubes :datatype-) "vision_msgs/GetCubes")
(setf (get vision_msgs::GetCubes :request) vision_msgs::GetCubesRequest)
(setf (get vision_msgs::GetCubes :response) vision_msgs::GetCubesResponse)

(defmethod vision_msgs::GetCubesRequest
  (:response () (instance vision_msgs::GetCubesResponse :init)))

(setf (get vision_msgs::GetCubesRequest :md5sum-) "a2d88941f0bdf4936824e45f204e46ff")
(setf (get vision_msgs::GetCubesRequest :datatype-) "vision_msgs/GetCubesRequest")
(setf (get vision_msgs::GetCubesRequest :definition-)
      "vision_msgs/CubesSegmented cubes_input

================================================================================
MSG: vision_msgs/CubesSegmented
std_msgs/Header header
vision_msgs/Cube[] recog_cubes

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
MSG: vision_msgs/Cube
string color #color of the cube
geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)
bool detected_cube    #flag to indicate if the cube was detected
geometry_msgs/Point minPoint	#Cube's min point
geometry_msgs/Point maxPoint	#Cube's max point

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
---
vision_msgs/CubesSegmented cubes_output


================================================================================
MSG: vision_msgs/CubesSegmented
std_msgs/Header header
vision_msgs/Cube[] recog_cubes

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
MSG: vision_msgs/Cube
string color #color of the cube
geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)
bool detected_cube    #flag to indicate if the cube was detected
geometry_msgs/Point minPoint	#Cube's min point
geometry_msgs/Point maxPoint	#Cube's max point

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")

(setf (get vision_msgs::GetCubesResponse :md5sum-) "a2d88941f0bdf4936824e45f204e46ff")
(setf (get vision_msgs::GetCubesResponse :datatype-) "vision_msgs/GetCubesResponse")
(setf (get vision_msgs::GetCubesResponse :definition-)
      "vision_msgs/CubesSegmented cubes_input

================================================================================
MSG: vision_msgs/CubesSegmented
std_msgs/Header header
vision_msgs/Cube[] recog_cubes

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
MSG: vision_msgs/Cube
string color #color of the cube
geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)
bool detected_cube    #flag to indicate if the cube was detected
geometry_msgs/Point minPoint	#Cube's min point
geometry_msgs/Point maxPoint	#Cube's max point

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
---
vision_msgs/CubesSegmented cubes_output


================================================================================
MSG: vision_msgs/CubesSegmented
std_msgs/Header header
vision_msgs/Cube[] recog_cubes

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
MSG: vision_msgs/Cube
string color #color of the cube
geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)
bool detected_cube    #flag to indicate if the cube was detected
geometry_msgs/Point minPoint	#Cube's min point
geometry_msgs/Point maxPoint	#Cube's max point

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")



(provide :vision_msgs/GetCubes "a2d88941f0bdf4936824e45f204e46ff")


