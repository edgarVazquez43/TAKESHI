;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::VisionFaceObjects)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'VisionFaceObjects (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::VISIONFACEOBJECTS")
  (make-package "VISION_MSGS::VISIONFACEOBJECTS"))

(in-package "ROS")
;;//! \htmlinclude VisionFaceObjects.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::VisionFaceObjects
  :super ros::object
  :slots (_header _recog_faces ))

(defmethod vision_msgs::VisionFaceObjects
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:recog_faces __recog_faces) (let (r) (dotimes (i 0) (push (instance vision_msgs::VisionFaceObject :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _recog_faces __recog_faces)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:recog_faces
   (&rest __recog_faces)
   (if (keywordp (car __recog_faces))
       (send* _recog_faces __recog_faces)
     (progn
       (if __recog_faces (setq _recog_faces (car __recog_faces)))
       _recog_faces)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; vision_msgs/VisionFaceObject[] _recog_faces
    (apply #'+ (send-all _recog_faces :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; vision_msgs/VisionFaceObject[] _recog_faces
     (write-long (length _recog_faces) s)
     (dolist (elem _recog_faces)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; vision_msgs/VisionFaceObject[] _recog_faces
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _recog_faces (let (r) (dotimes (i n) (push (instance vision_msgs::VisionFaceObject :init) r)) r))
     (dolist (elem- _recog_faces)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get vision_msgs::VisionFaceObjects :md5sum-) "4fd1cb6b6d63c7ee8d419e777e468fd2")
(setf (get vision_msgs::VisionFaceObjects :datatype-) "vision_msgs/VisionFaceObjects")
(setf (get vision_msgs::VisionFaceObjects :definition-)
      "std_msgs/Header header
vision_msgs/VisionFaceObject[] recog_faces

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
MSG: vision_msgs/VisionFaceObject
string id                                    #face id
float32 confidence                           #value in [0,1] indicating the probability of a correct identification
geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)
geometry_msgs/Point[] bounding_box           #Face bounding box 2D 
bool smile                                   #smiling face
int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :vision_msgs/VisionFaceObjects "4fd1cb6b6d63c7ee8d419e777e468fd2")


