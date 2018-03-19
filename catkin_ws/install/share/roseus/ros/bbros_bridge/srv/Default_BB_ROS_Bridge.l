;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::Default_BB_ROS_Bridge)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'Default_BB_ROS_Bridge (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::DEFAULT_BB_ROS_BRIDGE")
  (make-package "BBROS_BRIDGE::DEFAULT_BB_ROS_BRIDGE"))
(unless (find-package "BBROS_BRIDGE::DEFAULT_BB_ROS_BRIDGEREQUEST")
  (make-package "BBROS_BRIDGE::DEFAULT_BB_ROS_BRIDGEREQUEST"))
(unless (find-package "BBROS_BRIDGE::DEFAULT_BB_ROS_BRIDGERESPONSE")
  (make-package "BBROS_BRIDGE::DEFAULT_BB_ROS_BRIDGERESPONSE"))

(in-package "ROS")





(defclass bbros_bridge::Default_BB_ROS_BridgeRequest
  :super ros::object
  :slots (_params ))

(defmethod bbros_bridge::Default_BB_ROS_BridgeRequest
  (:init
   (&key
    ((:params __params) "")
    )
   (send-super :init)
   (setq _params (string __params))
   self)
  (:params
   (&optional __params)
   (if __params (setq _params __params)) _params)
  (:serialization-length
   ()
   (+
    ;; string _params
    4 (length _params)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _params
       (write-long (length _params) s) (princ _params s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _params
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _params (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass bbros_bridge::Default_BB_ROS_BridgeResponse
  :super ros::object
  :slots (_response ))

(defmethod bbros_bridge::Default_BB_ROS_BridgeResponse
  (:init
   (&key
    ((:response __response) "")
    )
   (send-super :init)
   (setq _response (string __response))
   self)
  (:response
   (&optional __response)
   (if __response (setq _response __response)) _response)
  (:serialization-length
   ()
   (+
    ;; string _response
    4 (length _response)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _response
       (write-long (length _response) s) (princ _response s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _response
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _response (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass bbros_bridge::Default_BB_ROS_Bridge
  :super ros::object
  :slots ())

(setf (get bbros_bridge::Default_BB_ROS_Bridge :md5sum-) "6162a5d58ec2c814778e9c41c1bf44eb")
(setf (get bbros_bridge::Default_BB_ROS_Bridge :datatype-) "bbros_bridge/Default_BB_ROS_Bridge")
(setf (get bbros_bridge::Default_BB_ROS_Bridge :request) bbros_bridge::Default_BB_ROS_BridgeRequest)
(setf (get bbros_bridge::Default_BB_ROS_Bridge :response) bbros_bridge::Default_BB_ROS_BridgeResponse)

(defmethod bbros_bridge::Default_BB_ROS_BridgeRequest
  (:response () (instance bbros_bridge::Default_BB_ROS_BridgeResponse :init)))

(setf (get bbros_bridge::Default_BB_ROS_BridgeRequest :md5sum-) "6162a5d58ec2c814778e9c41c1bf44eb")
(setf (get bbros_bridge::Default_BB_ROS_BridgeRequest :datatype-) "bbros_bridge/Default_BB_ROS_BridgeRequest")
(setf (get bbros_bridge::Default_BB_ROS_BridgeRequest :definition-)
      "string params
---
string response

")

(setf (get bbros_bridge::Default_BB_ROS_BridgeResponse :md5sum-) "6162a5d58ec2c814778e9c41c1bf44eb")
(setf (get bbros_bridge::Default_BB_ROS_BridgeResponse :datatype-) "bbros_bridge/Default_BB_ROS_BridgeResponse")
(setf (get bbros_bridge::Default_BB_ROS_BridgeResponse :definition-)
      "string params
---
string response

")



(provide :bbros_bridge/Default_BB_ROS_Bridge "6162a5d58ec2c814778e9c41c1bf44eb")


