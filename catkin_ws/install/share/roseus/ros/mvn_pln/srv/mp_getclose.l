;; Auto-generated. Do not edit!


(when (boundp 'mvn_pln::mp_getclose)
  (if (not (find-package "MVN_PLN"))
    (make-package "MVN_PLN"))
  (shadow 'mp_getclose (find-package "MVN_PLN")))
(unless (find-package "MVN_PLN::MP_GETCLOSE")
  (make-package "MVN_PLN::MP_GETCLOSE"))
(unless (find-package "MVN_PLN::MP_GETCLOSEREQUEST")
  (make-package "MVN_PLN::MP_GETCLOSEREQUEST"))
(unless (find-package "MVN_PLN::MP_GETCLOSERESPONSE")
  (make-package "MVN_PLN::MP_GETCLOSERESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mvn_pln::mp_getcloseRequest
  :super ros::object
  :slots (_location ))

(defmethod mvn_pln::mp_getcloseRequest
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

(defclass mvn_pln::mp_getcloseResponse
  :super ros::object
  :slots (_error ))

(defmethod mvn_pln::mp_getcloseResponse
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

(defclass mvn_pln::mp_getclose
  :super ros::object
  :slots ())

(setf (get mvn_pln::mp_getclose :md5sum-) "1919ccd065ce7aa924cb46471f2dd632")
(setf (get mvn_pln::mp_getclose :datatype-) "mvn_pln/mp_getclose")
(setf (get mvn_pln::mp_getclose :request) mvn_pln::mp_getcloseRequest)
(setf (get mvn_pln::mp_getclose :response) mvn_pln::mp_getcloseResponse)

(defmethod mvn_pln::mp_getcloseRequest
  (:response () (instance mvn_pln::mp_getcloseResponse :init)))

(setf (get mvn_pln::mp_getcloseRequest :md5sum-) "1919ccd065ce7aa924cb46471f2dd632")
(setf (get mvn_pln::mp_getcloseRequest :datatype-) "mvn_pln/mp_getcloseRequest")
(setf (get mvn_pln::mp_getcloseRequest :definition-)
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

(setf (get mvn_pln::mp_getcloseResponse :md5sum-) "1919ccd065ce7aa924cb46471f2dd632")
(setf (get mvn_pln::mp_getcloseResponse :datatype-) "mvn_pln/mp_getcloseResponse")
(setf (get mvn_pln::mp_getcloseResponse :definition-)
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



(provide :mvn_pln/mp_getclose "1919ccd065ce7aa924cb46471f2dd632")


