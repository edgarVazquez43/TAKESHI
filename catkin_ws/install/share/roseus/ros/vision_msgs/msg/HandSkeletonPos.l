;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::HandSkeletonPos)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'HandSkeletonPos (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::HANDSKELETONPOS")
  (make-package "VISION_MSGS::HANDSKELETONPOS"))

(in-package "ROS")
;;//! \htmlinclude HandSkeletonPos.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::HandSkeletonPos
  :super ros::object
  :slots (_header _hands_position ))

(defmethod vision_msgs::HandSkeletonPos
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:hands_position __hands_position) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _hands_position __hands_position)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:hands_position
   (&rest __hands_position)
   (if (keywordp (car __hands_position))
       (send* _hands_position __hands_position)
     (progn
       (if __hands_position (setq _hands_position (car __hands_position)))
       _hands_position)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Point[] _hands_position
    (apply #'+ (send-all _hands_position :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Point[] _hands_position
     (write-long (length _hands_position) s)
     (dolist (elem _hands_position)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Point[] _hands_position
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _hands_position (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _hands_position)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get vision_msgs::HandSkeletonPos :md5sum-) "2538d67d00ece1fbd2e374d69c22d6f0")
(setf (get vision_msgs::HandSkeletonPos :datatype-) "vision_msgs/HandSkeletonPos")
(setf (get vision_msgs::HandSkeletonPos :definition-)
      "std_msgs/Header header
geometry_msgs/Point[] hands_position

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

")



(provide :vision_msgs/HandSkeletonPos "2538d67d00ece1fbd2e374d69c22d6f0")


