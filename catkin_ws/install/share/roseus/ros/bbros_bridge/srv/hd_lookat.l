;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::hd_lookat)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'hd_lookat (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::HD_LOOKAT")
  (make-package "BBROS_BRIDGE::HD_LOOKAT"))
(unless (find-package "BBROS_BRIDGE::HD_LOOKATREQUEST")
  (make-package "BBROS_BRIDGE::HD_LOOKATREQUEST"))
(unless (find-package "BBROS_BRIDGE::HD_LOOKATRESPONSE")
  (make-package "BBROS_BRIDGE::HD_LOOKATRESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass bbros_bridge::hd_lookatRequest
  :super ros::object
  :slots (_goalPan _goalTilt ))

(defmethod bbros_bridge::hd_lookatRequest
  (:init
   (&key
    ((:goalPan __goalPan) (instance std_msgs::Float32 :init))
    ((:goalTilt __goalTilt) (instance std_msgs::Float32 :init))
    )
   (send-super :init)
   (setq _goalPan __goalPan)
   (setq _goalTilt __goalTilt)
   self)
  (:goalPan
   (&rest __goalPan)
   (if (keywordp (car __goalPan))
       (send* _goalPan __goalPan)
     (progn
       (if __goalPan (setq _goalPan (car __goalPan)))
       _goalPan)))
  (:goalTilt
   (&rest __goalTilt)
   (if (keywordp (car __goalTilt))
       (send* _goalTilt __goalTilt)
     (progn
       (if __goalTilt (setq _goalTilt (car __goalTilt)))
       _goalTilt)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32 _goalPan
    (send _goalPan :serialization-length)
    ;; std_msgs/Float32 _goalTilt
    (send _goalTilt :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32 _goalPan
       (send _goalPan :serialize s)
     ;; std_msgs/Float32 _goalTilt
       (send _goalTilt :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32 _goalPan
     (send _goalPan :deserialize buf ptr-) (incf ptr- (send _goalPan :serialization-length))
   ;; std_msgs/Float32 _goalTilt
     (send _goalTilt :deserialize buf ptr-) (incf ptr- (send _goalTilt :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::hd_lookatResponse
  :super ros::object
  :slots (_currentPan _currentTilt _errors ))

(defmethod bbros_bridge::hd_lookatResponse
  (:init
   (&key
    ((:currentPan __currentPan) (instance std_msgs::Float32 :init))
    ((:currentTilt __currentTilt) (instance std_msgs::Float32 :init))
    ((:errors __errors) (instance std_msgs::String :init))
    )
   (send-super :init)
   (setq _currentPan __currentPan)
   (setq _currentTilt __currentTilt)
   (setq _errors __errors)
   self)
  (:currentPan
   (&rest __currentPan)
   (if (keywordp (car __currentPan))
       (send* _currentPan __currentPan)
     (progn
       (if __currentPan (setq _currentPan (car __currentPan)))
       _currentPan)))
  (:currentTilt
   (&rest __currentTilt)
   (if (keywordp (car __currentTilt))
       (send* _currentTilt __currentTilt)
     (progn
       (if __currentTilt (setq _currentTilt (car __currentTilt)))
       _currentTilt)))
  (:errors
   (&rest __errors)
   (if (keywordp (car __errors))
       (send* _errors __errors)
     (progn
       (if __errors (setq _errors (car __errors)))
       _errors)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32 _currentPan
    (send _currentPan :serialization-length)
    ;; std_msgs/Float32 _currentTilt
    (send _currentTilt :serialization-length)
    ;; std_msgs/String _errors
    (send _errors :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32 _currentPan
       (send _currentPan :serialize s)
     ;; std_msgs/Float32 _currentTilt
       (send _currentTilt :serialize s)
     ;; std_msgs/String _errors
       (send _errors :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32 _currentPan
     (send _currentPan :deserialize buf ptr-) (incf ptr- (send _currentPan :serialization-length))
   ;; std_msgs/Float32 _currentTilt
     (send _currentTilt :deserialize buf ptr-) (incf ptr- (send _currentTilt :serialization-length))
   ;; std_msgs/String _errors
     (send _errors :deserialize buf ptr-) (incf ptr- (send _errors :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::hd_lookat
  :super ros::object
  :slots ())

(setf (get bbros_bridge::hd_lookat :md5sum-) "0d2267ae1acd4d7549c1a4e21fcad0ae")
(setf (get bbros_bridge::hd_lookat :datatype-) "bbros_bridge/hd_lookat")
(setf (get bbros_bridge::hd_lookat :request) bbros_bridge::hd_lookatRequest)
(setf (get bbros_bridge::hd_lookat :response) bbros_bridge::hd_lookatResponse)

(defmethod bbros_bridge::hd_lookatRequest
  (:response () (instance bbros_bridge::hd_lookatResponse :init)))

(setf (get bbros_bridge::hd_lookatRequest :md5sum-) "0d2267ae1acd4d7549c1a4e21fcad0ae")
(setf (get bbros_bridge::hd_lookatRequest :datatype-) "bbros_bridge/hd_lookatRequest")
(setf (get bbros_bridge::hd_lookatRequest :definition-)
      "std_msgs/Float32 goalPan
std_msgs/Float32 goalTilt

================================================================================
MSG: std_msgs/Float32
---
std_msgs/Float32 currentPan
std_msgs/Float32 currentTilt
std_msgs/String errors


================================================================================
MSG: std_msgs/Float32
float32 data
================================================================================
MSG: std_msgs/String
string data
")

(setf (get bbros_bridge::hd_lookatResponse :md5sum-) "0d2267ae1acd4d7549c1a4e21fcad0ae")
(setf (get bbros_bridge::hd_lookatResponse :datatype-) "bbros_bridge/hd_lookatResponse")
(setf (get bbros_bridge::hd_lookatResponse :definition-)
      "std_msgs/Float32 goalPan
std_msgs/Float32 goalTilt

================================================================================
MSG: std_msgs/Float32
---
std_msgs/Float32 currentPan
std_msgs/Float32 currentTilt
std_msgs/String errors


================================================================================
MSG: std_msgs/Float32
float32 data
================================================================================
MSG: std_msgs/String
string data
")



(provide :bbros_bridge/hd_lookat "0d2267ae1acd4d7549c1a4e21fcad0ae")


