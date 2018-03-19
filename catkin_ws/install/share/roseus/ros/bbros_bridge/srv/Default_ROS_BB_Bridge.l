;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::Default_ROS_BB_Bridge)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'Default_ROS_BB_Bridge (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::DEFAULT_ROS_BB_BRIDGE")
  (make-package "BBROS_BRIDGE::DEFAULT_ROS_BB_BRIDGE"))
(unless (find-package "BBROS_BRIDGE::DEFAULT_ROS_BB_BRIDGEREQUEST")
  (make-package "BBROS_BRIDGE::DEFAULT_ROS_BB_BRIDGEREQUEST"))
(unless (find-package "BBROS_BRIDGE::DEFAULT_ROS_BB_BRIDGERESPONSE")
  (make-package "BBROS_BRIDGE::DEFAULT_ROS_BB_BRIDGERESPONSE"))

(in-package "ROS")





(defclass bbros_bridge::Default_ROS_BB_BridgeRequest
  :super ros::object
  :slots (_parameters _timeout ))

(defmethod bbros_bridge::Default_ROS_BB_BridgeRequest
  (:init
   (&key
    ((:parameters __parameters) "")
    ((:timeout __timeout) 0)
    )
   (send-super :init)
   (setq _parameters (string __parameters))
   (setq _timeout (round __timeout))
   self)
  (:parameters
   (&optional __parameters)
   (if __parameters (setq _parameters __parameters)) _parameters)
  (:timeout
   (&optional __timeout)
   (if __timeout (setq _timeout __timeout)) _timeout)
  (:serialization-length
   ()
   (+
    ;; string _parameters
    4 (length _parameters)
    ;; int16 _timeout
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _parameters
       (write-long (length _parameters) s) (princ _parameters s)
     ;; int16 _timeout
       (write-word _timeout s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _parameters
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _parameters (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int16 _timeout
     (setq _timeout (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(defclass bbros_bridge::Default_ROS_BB_BridgeResponse
  :super ros::object
  :slots (_success _response ))

(defmethod bbros_bridge::Default_ROS_BB_BridgeResponse
  (:init
   (&key
    ((:success __success) nil)
    ((:response __response) "")
    )
   (send-super :init)
   (setq _success __success)
   (setq _response (string __response))
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:response
   (&optional __response)
   (if __response (setq _response __response)) _response)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ;; string _response
    4 (length _response)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;; string _response
       (write-long (length _response) s) (princ _response s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _response
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _response (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass bbros_bridge::Default_ROS_BB_Bridge
  :super ros::object
  :slots ())

(setf (get bbros_bridge::Default_ROS_BB_Bridge :md5sum-) "dc72b6691678f98c1cd8b4c963031bd5")
(setf (get bbros_bridge::Default_ROS_BB_Bridge :datatype-) "bbros_bridge/Default_ROS_BB_Bridge")
(setf (get bbros_bridge::Default_ROS_BB_Bridge :request) bbros_bridge::Default_ROS_BB_BridgeRequest)
(setf (get bbros_bridge::Default_ROS_BB_Bridge :response) bbros_bridge::Default_ROS_BB_BridgeResponse)

(defmethod bbros_bridge::Default_ROS_BB_BridgeRequest
  (:response () (instance bbros_bridge::Default_ROS_BB_BridgeResponse :init)))

(setf (get bbros_bridge::Default_ROS_BB_BridgeRequest :md5sum-) "dc72b6691678f98c1cd8b4c963031bd5")
(setf (get bbros_bridge::Default_ROS_BB_BridgeRequest :datatype-) "bbros_bridge/Default_ROS_BB_BridgeRequest")
(setf (get bbros_bridge::Default_ROS_BB_BridgeRequest :definition-)
      "string parameters
int16 timeout
---
bool success
string response

")

(setf (get bbros_bridge::Default_ROS_BB_BridgeResponse :md5sum-) "dc72b6691678f98c1cd8b4c963031bd5")
(setf (get bbros_bridge::Default_ROS_BB_BridgeResponse :datatype-) "bbros_bridge/Default_ROS_BB_BridgeResponse")
(setf (get bbros_bridge::Default_ROS_BB_BridgeResponse :definition-)
      "string parameters
int16 timeout
---
bool success
string response

")



(provide :bbros_bridge/Default_ROS_BB_Bridge "dc72b6691678f98c1cd8b4c963031bd5")


