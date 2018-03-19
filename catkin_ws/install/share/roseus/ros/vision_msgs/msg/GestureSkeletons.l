;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::GestureSkeletons)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'GestureSkeletons (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::GESTURESKELETONS")
  (make-package "VISION_MSGS::GESTURESKELETONS"))

(in-package "ROS")
;;//! \htmlinclude GestureSkeletons.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::GestureSkeletons
  :super ros::object
  :slots (_header _recog_gestures ))

(defmethod vision_msgs::GestureSkeletons
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:recog_gestures __recog_gestures) (let (r) (dotimes (i 0) (push (instance vision_msgs::GestureSkeleton :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _recog_gestures __recog_gestures)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:recog_gestures
   (&rest __recog_gestures)
   (if (keywordp (car __recog_gestures))
       (send* _recog_gestures __recog_gestures)
     (progn
       (if __recog_gestures (setq _recog_gestures (car __recog_gestures)))
       _recog_gestures)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; vision_msgs/GestureSkeleton[] _recog_gestures
    (apply #'+ (send-all _recog_gestures :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; vision_msgs/GestureSkeleton[] _recog_gestures
     (write-long (length _recog_gestures) s)
     (dolist (elem _recog_gestures)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; vision_msgs/GestureSkeleton[] _recog_gestures
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _recog_gestures (let (r) (dotimes (i n) (push (instance vision_msgs::GestureSkeleton :init) r)) r))
     (dolist (elem- _recog_gestures)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get vision_msgs::GestureSkeletons :md5sum-) "f4df52aabef2b028180e9bc45fa637db")
(setf (get vision_msgs::GestureSkeletons :datatype-) "vision_msgs/GestureSkeletons")
(setf (get vision_msgs::GestureSkeletons :definition-)
      "std_msgs/Header header
vision_msgs/GestureSkeleton[] recog_gestures

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
MSG: vision_msgs/GestureSkeleton
int8 id		#id of user
string gesture		#gesture of user
geometry_msgs/Point gesture_centroid		#Gesture Centroid (x,y,z)

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :vision_msgs/GestureSkeletons "f4df52aabef2b028180e9bc45fa637db")


