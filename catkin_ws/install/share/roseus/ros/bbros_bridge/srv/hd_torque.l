;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::hd_torque)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'hd_torque (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::HD_TORQUE")
  (make-package "BBROS_BRIDGE::HD_TORQUE"))
(unless (find-package "BBROS_BRIDGE::HD_TORQUEREQUEST")
  (make-package "BBROS_BRIDGE::HD_TORQUEREQUEST"))
(unless (find-package "BBROS_BRIDGE::HD_TORQUERESPONSE")
  (make-package "BBROS_BRIDGE::HD_TORQUERESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass bbros_bridge::hd_torqueRequest
  :super ros::object
  :slots (_enable ))

(defmethod bbros_bridge::hd_torqueRequest
  (:init
   (&key
    ((:enable __enable) (instance std_msgs::Bool :init))
    )
   (send-super :init)
   (setq _enable __enable)
   self)
  (:enable
   (&rest __enable)
   (if (keywordp (car __enable))
       (send* _enable __enable)
     (progn
       (if __enable (setq _enable (car __enable)))
       _enable)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Bool _enable
    (send _enable :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Bool _enable
       (send _enable :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Bool _enable
     (send _enable :deserialize buf ptr-) (incf ptr- (send _enable :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::hd_torqueResponse
  :super ros::object
  :slots (_errors ))

(defmethod bbros_bridge::hd_torqueResponse
  (:init
   (&key
    ((:errors __errors) (instance std_msgs::String :init))
    )
   (send-super :init)
   (setq _errors __errors)
   self)
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
    ;; std_msgs/String _errors
    (send _errors :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/String _errors
       (send _errors :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/String _errors
     (send _errors :deserialize buf ptr-) (incf ptr- (send _errors :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::hd_torque
  :super ros::object
  :slots ())

(setf (get bbros_bridge::hd_torque :md5sum-) "5ec6cba259224de8444ec81114c3fa2f")
(setf (get bbros_bridge::hd_torque :datatype-) "bbros_bridge/hd_torque")
(setf (get bbros_bridge::hd_torque :request) bbros_bridge::hd_torqueRequest)
(setf (get bbros_bridge::hd_torque :response) bbros_bridge::hd_torqueResponse)

(defmethod bbros_bridge::hd_torqueRequest
  (:response () (instance bbros_bridge::hd_torqueResponse :init)))

(setf (get bbros_bridge::hd_torqueRequest :md5sum-) "5ec6cba259224de8444ec81114c3fa2f")
(setf (get bbros_bridge::hd_torqueRequest :datatype-) "bbros_bridge/hd_torqueRequest")
(setf (get bbros_bridge::hd_torqueRequest :definition-)
      "std_msgs/Bool enable

================================================================================
MSG: std_msgs/Bool
---
std_msgs/String errors


================================================================================
MSG: std_msgs/String
string data
")

(setf (get bbros_bridge::hd_torqueResponse :md5sum-) "5ec6cba259224de8444ec81114c3fa2f")
(setf (get bbros_bridge::hd_torqueResponse :datatype-) "bbros_bridge/hd_torqueResponse")
(setf (get bbros_bridge::hd_torqueResponse :definition-)
      "std_msgs/Bool enable

================================================================================
MSG: std_msgs/Bool
---
std_msgs/String errors


================================================================================
MSG: std_msgs/String
string data
")



(provide :bbros_bridge/hd_torque "5ec6cba259224de8444ec81114c3fa2f")


