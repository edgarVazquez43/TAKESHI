;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::GestureSkeleton)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'GestureSkeleton (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::GESTURESKELETON")
  (make-package "VISION_MSGS::GESTURESKELETON"))

(in-package "ROS")
;;//! \htmlinclude GestureSkeleton.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass vision_msgs::GestureSkeleton
  :super ros::object
  :slots (_id _gesture _gesture_centroid ))

(defmethod vision_msgs::GestureSkeleton
  (:init
   (&key
    ((:id __id) 0)
    ((:gesture __gesture) "")
    ((:gesture_centroid __gesture_centroid) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _gesture (string __gesture))
   (setq _gesture_centroid __gesture_centroid)
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:gesture
   (&optional __gesture)
   (if __gesture (setq _gesture __gesture)) _gesture)
  (:gesture_centroid
   (&rest __gesture_centroid)
   (if (keywordp (car __gesture_centroid))
       (send* _gesture_centroid __gesture_centroid)
     (progn
       (if __gesture_centroid (setq _gesture_centroid (car __gesture_centroid)))
       _gesture_centroid)))
  (:serialization-length
   ()
   (+
    ;; int8 _id
    1
    ;; string _gesture
    4 (length _gesture)
    ;; geometry_msgs/Point _gesture_centroid
    (send _gesture_centroid :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _id
       (write-byte _id s)
     ;; string _gesture
       (write-long (length _gesture) s) (princ _gesture s)
     ;; geometry_msgs/Point _gesture_centroid
       (send _gesture_centroid :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _id 127) (setq _id (- _id 256)))
   ;; string _gesture
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _gesture (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Point _gesture_centroid
     (send _gesture_centroid :deserialize buf ptr-) (incf ptr- (send _gesture_centroid :serialization-length))
   ;;
   self)
  )

(setf (get vision_msgs::GestureSkeleton :md5sum-) "1e87d31b651e197f45459ceb0c0353fb")
(setf (get vision_msgs::GestureSkeleton :datatype-) "vision_msgs/GestureSkeleton")
(setf (get vision_msgs::GestureSkeleton :definition-)
      "int8 id		#id of user
string gesture		#gesture of user
geometry_msgs/Point gesture_centroid		#Gesture Centroid (x,y,z)

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :vision_msgs/GestureSkeleton "1e87d31b651e197f45459ceb0c0353fb")


