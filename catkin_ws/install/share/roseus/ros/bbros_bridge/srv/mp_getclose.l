;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::mp_getclose)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'mp_getclose (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::MP_GETCLOSE")
  (make-package "BBROS_BRIDGE::MP_GETCLOSE"))
(unless (find-package "BBROS_BRIDGE::MP_GETCLOSEREQUEST")
  (make-package "BBROS_BRIDGE::MP_GETCLOSEREQUEST"))
(unless (find-package "BBROS_BRIDGE::MP_GETCLOSERESPONSE")
  (make-package "BBROS_BRIDGE::MP_GETCLOSERESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass bbros_bridge::mp_getcloseRequest
  :super ros::object
  :slots (_location ))

(defmethod bbros_bridge::mp_getcloseRequest
  (:init
   (&key
    ((:location __location) (instance std_msgs::String :init))
    )
   (send-super :init)
   (setq _location __location)
   self)
  (:location
   (&rest __location)
   (if (keywordp (car __location))
       (send* _location __location)
     (progn
       (if __location (setq _location (car __location)))
       _location)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/String _location
    (send _location :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/String _location
       (send _location :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/String _location
     (send _location :deserialize buf ptr-) (incf ptr- (send _location :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::mp_getcloseResponse
  :super ros::object
  :slots (_error ))

(defmethod bbros_bridge::mp_getcloseResponse
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

(defclass bbros_bridge::mp_getclose
  :super ros::object
  :slots ())

(setf (get bbros_bridge::mp_getclose :md5sum-) "1919ccd065ce7aa924cb46471f2dd632")
(setf (get bbros_bridge::mp_getclose :datatype-) "bbros_bridge/mp_getclose")
(setf (get bbros_bridge::mp_getclose :request) bbros_bridge::mp_getcloseRequest)
(setf (get bbros_bridge::mp_getclose :response) bbros_bridge::mp_getcloseResponse)

(defmethod bbros_bridge::mp_getcloseRequest
  (:response () (instance bbros_bridge::mp_getcloseResponse :init)))

(setf (get bbros_bridge::mp_getcloseRequest :md5sum-) "1919ccd065ce7aa924cb46471f2dd632")
(setf (get bbros_bridge::mp_getcloseRequest :datatype-) "bbros_bridge/mp_getcloseRequest")
(setf (get bbros_bridge::mp_getcloseRequest :definition-)
      "std_msgs/String location

================================================================================
MSG: std_msgs/String
string data
---
std_msgs/String error


================================================================================
MSG: std_msgs/String
string data
")

(setf (get bbros_bridge::mp_getcloseResponse :md5sum-) "1919ccd065ce7aa924cb46471f2dd632")
(setf (get bbros_bridge::mp_getcloseResponse :datatype-) "bbros_bridge/mp_getcloseResponse")
(setf (get bbros_bridge::mp_getcloseResponse :definition-)
      "std_msgs/String location

================================================================================
MSG: std_msgs/String
string data
---
std_msgs/String error


================================================================================
MSG: std_msgs/String
string data
")



(provide :bbros_bridge/mp_getclose "1919ccd065ce7aa924cb46471f2dd632")


