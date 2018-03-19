;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::CubesSegmented)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'CubesSegmented (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::CUBESSEGMENTED")
  (make-package "VISION_MSGS::CUBESSEGMENTED"))

(in-package "ROS")
;;//! \htmlinclude CubesSegmented.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::CubesSegmented
  :super ros::object
  :slots (_header _recog_cubes ))

(defmethod vision_msgs::CubesSegmented
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:recog_cubes __recog_cubes) (let (r) (dotimes (i 0) (push (instance vision_msgs::Cube :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _recog_cubes __recog_cubes)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:recog_cubes
   (&rest __recog_cubes)
   (if (keywordp (car __recog_cubes))
       (send* _recog_cubes __recog_cubes)
     (progn
       (if __recog_cubes (setq _recog_cubes (car __recog_cubes)))
       _recog_cubes)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; vision_msgs/Cube[] _recog_cubes
    (apply #'+ (send-all _recog_cubes :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; vision_msgs/Cube[] _recog_cubes
     (write-long (length _recog_cubes) s)
     (dolist (elem _recog_cubes)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; vision_msgs/Cube[] _recog_cubes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _recog_cubes (let (r) (dotimes (i n) (push (instance vision_msgs::Cube :init) r)) r))
     (dolist (elem- _recog_cubes)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get vision_msgs::CubesSegmented :md5sum-) "2b935aade8f9275f5577fcbf7010f212")
(setf (get vision_msgs::CubesSegmented :datatype-) "vision_msgs/CubesSegmented")
(setf (get vision_msgs::CubesSegmented :definition-)
      "std_msgs/Header header
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



(provide :vision_msgs/CubesSegmented "2b935aade8f9275f5577fcbf7010f212")


