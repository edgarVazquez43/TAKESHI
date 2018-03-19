;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::mp_getclose_xy)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'mp_getclose_xy (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::MP_GETCLOSE_XY")
  (make-package "BBROS_BRIDGE::MP_GETCLOSE_XY"))
(unless (find-package "BBROS_BRIDGE::MP_GETCLOSE_XYREQUEST")
  (make-package "BBROS_BRIDGE::MP_GETCLOSE_XYREQUEST"))
(unless (find-package "BBROS_BRIDGE::MP_GETCLOSE_XYRESPONSE")
  (make-package "BBROS_BRIDGE::MP_GETCLOSE_XYRESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass bbros_bridge::mp_getclose_xyRequest
  :super ros::object
  :slots (_goalX _goalY ))

(defmethod bbros_bridge::mp_getclose_xyRequest
  (:init
   (&key
    ((:goalX __goalX) (instance std_msgs::Float32 :init))
    ((:goalY __goalY) (instance std_msgs::Float32 :init))
    )
   (send-super :init)
   (setq _goalX __goalX)
   (setq _goalY __goalY)
   self)
  (:goalX
   (&rest __goalX)
   (if (keywordp (car __goalX))
       (send* _goalX __goalX)
     (progn
       (if __goalX (setq _goalX (car __goalX)))
       _goalX)))
  (:goalY
   (&rest __goalY)
   (if (keywordp (car __goalY))
       (send* _goalY __goalY)
     (progn
       (if __goalY (setq _goalY (car __goalY)))
       _goalY)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32 _goalX
    (send _goalX :serialization-length)
    ;; std_msgs/Float32 _goalY
    (send _goalY :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32 _goalX
       (send _goalX :serialize s)
     ;; std_msgs/Float32 _goalY
       (send _goalY :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32 _goalX
     (send _goalX :deserialize buf ptr-) (incf ptr- (send _goalX :serialization-length))
   ;; std_msgs/Float32 _goalY
     (send _goalY :deserialize buf ptr-) (incf ptr- (send _goalY :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::mp_getclose_xyResponse
  :super ros::object
  :slots (_error ))

(defmethod bbros_bridge::mp_getclose_xyResponse
  (:init
   (&key
    ((:error __error) (instance std_msgs::String :init))
    )
   (send-super :init)
   (setq _error __error)
   self)
  (:error
   (&rest __error)
   (if (keywordp (car __error))
       (send* _error __error)
     (progn
       (if __error (setq _error (car __error)))
       _error)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/String _error
    (send _error :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/String _error
       (send _error :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/String _error
     (send _error :deserialize buf ptr-) (incf ptr- (send _error :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::mp_getclose_xy
  :super ros::object
  :slots ())

(setf (get bbros_bridge::mp_getclose_xy :md5sum-) "a6bfdb792bb6f7c25c686505f84f9b9c")
(setf (get bbros_bridge::mp_getclose_xy :datatype-) "bbros_bridge/mp_getclose_xy")
(setf (get bbros_bridge::mp_getclose_xy :request) bbros_bridge::mp_getclose_xyRequest)
(setf (get bbros_bridge::mp_getclose_xy :response) bbros_bridge::mp_getclose_xyResponse)

(defmethod bbros_bridge::mp_getclose_xyRequest
  (:response () (instance bbros_bridge::mp_getclose_xyResponse :init)))

(setf (get bbros_bridge::mp_getclose_xyRequest :md5sum-) "a6bfdb792bb6f7c25c686505f84f9b9c")
(setf (get bbros_bridge::mp_getclose_xyRequest :datatype-) "bbros_bridge/mp_getclose_xyRequest")
(setf (get bbros_bridge::mp_getclose_xyRequest :definition-)
      "std_msgs/Float32 goalX
std_msgs/Float32 goalY

================================================================================
MSG: std_msgs/Float32
---
std_msgs/String error


================================================================================
MSG: std_msgs/String
string data
")

(setf (get bbros_bridge::mp_getclose_xyResponse :md5sum-) "a6bfdb792bb6f7c25c686505f84f9b9c")
(setf (get bbros_bridge::mp_getclose_xyResponse :datatype-) "bbros_bridge/mp_getclose_xyResponse")
(setf (get bbros_bridge::mp_getclose_xyResponse :definition-)
      "std_msgs/Float32 goalX
std_msgs/Float32 goalY

================================================================================
MSG: std_msgs/Float32
---
std_msgs/String error


================================================================================
MSG: std_msgs/String
string data
")



(provide :bbros_bridge/mp_getclose_xy "a6bfdb792bb6f7c25c686505f84f9b9c")


