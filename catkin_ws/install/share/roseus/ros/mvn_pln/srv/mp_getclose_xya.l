;; Auto-generated. Do not edit!


(when (boundp 'mvn_pln::mp_getclose_xya)
  (if (not (find-package "MVN_PLN"))
    (make-package "MVN_PLN"))
  (shadow 'mp_getclose_xya (find-package "MVN_PLN")))
(unless (find-package "MVN_PLN::MP_GETCLOSE_XYA")
  (make-package "MVN_PLN::MP_GETCLOSE_XYA"))
(unless (find-package "MVN_PLN::MP_GETCLOSE_XYAREQUEST")
  (make-package "MVN_PLN::MP_GETCLOSE_XYAREQUEST"))
(unless (find-package "MVN_PLN::MP_GETCLOSE_XYARESPONSE")
  (make-package "MVN_PLN::MP_GETCLOSE_XYARESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mvn_pln::mp_getclose_xyaRequest
  :super ros::object
  :slots (_goalX _goalY _goalAngle ))

(defmethod mvn_pln::mp_getclose_xyaRequest
  (:init
   (&key
    ((:goalX __goalX) (instance std_msgs::Float32 :init))
    ((:goalY __goalY) (instance std_msgs::Float32 :init))
    ((:goalAngle __goalAngle) (instance std_msgs::Float32 :init))
    )
   (send-super :init)
   (setq _goalX __goalX)
   (setq _goalY __goalY)
   (setq _goalAngle __goalAngle)
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
  (:goalAngle
   (&rest __goalAngle)
   (if (keywordp (car __goalAngle))
       (send* _goalAngle __goalAngle)
     (progn
       (if __goalAngle (setq _goalAngle (car __goalAngle)))
       _goalAngle)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32 _goalX
    (send _goalX :serialization-length)
    ;; std_msgs/Float32 _goalY
    (send _goalY :serialization-length)
    ;; std_msgs/Float32 _goalAngle
    (send _goalAngle :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32 _goalX
       (send _goalX :serialize s)
     ;; std_msgs/Float32 _goalY
       (send _goalY :serialize s)
     ;; std_msgs/Float32 _goalAngle
       (send _goalAngle :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32 _goalX
     (send _goalX :deserialize buf ptr-) (incf ptr- (send _goalX :serialization-length))
   ;; std_msgs/Float32 _goalY
     (send _goalY :deserialize buf ptr-) (incf ptr- (send _goalY :serialization-length))
   ;; std_msgs/Float32 _goalAngle
     (send _goalAngle :deserialize buf ptr-) (incf ptr- (send _goalAngle :serialization-length))
   ;;
   self)
  )

(defclass mvn_pln::mp_getclose_xyaResponse
  :super ros::object
  :slots (_error ))

(defmethod mvn_pln::mp_getclose_xyaResponse
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

(defclass mvn_pln::mp_getclose_xya
  :super ros::object
  :slots ())

(setf (get mvn_pln::mp_getclose_xya :md5sum-) "f236a8bf2a517b8af728eb19291f51cb")
(setf (get mvn_pln::mp_getclose_xya :datatype-) "mvn_pln/mp_getclose_xya")
(setf (get mvn_pln::mp_getclose_xya :request) mvn_pln::mp_getclose_xyaRequest)
(setf (get mvn_pln::mp_getclose_xya :response) mvn_pln::mp_getclose_xyaResponse)

(defmethod mvn_pln::mp_getclose_xyaRequest
  (:response () (instance mvn_pln::mp_getclose_xyaResponse :init)))

(setf (get mvn_pln::mp_getclose_xyaRequest :md5sum-) "f236a8bf2a517b8af728eb19291f51cb")
(setf (get mvn_pln::mp_getclose_xyaRequest :datatype-) "mvn_pln/mp_getclose_xyaRequest")
(setf (get mvn_pln::mp_getclose_xyaRequest :definition-)
      "std_msgs/Float32 goalX
std_msgs/Float32 goalY
std_msgs/Float32 goalAngle

================================================================================
MSG: std_msgs/Float32
---
std_msgs/String error


================================================================================
MSG: std_msgs/String
string data
")

(setf (get mvn_pln::mp_getclose_xyaResponse :md5sum-) "f236a8bf2a517b8af728eb19291f51cb")
(setf (get mvn_pln::mp_getclose_xyaResponse :datatype-) "mvn_pln/mp_getclose_xyaResponse")
(setf (get mvn_pln::mp_getclose_xyaResponse :definition-)
      "std_msgs/Float32 goalX
std_msgs/Float32 goalY
std_msgs/Float32 goalAngle

================================================================================
MSG: std_msgs/Float32
---
std_msgs/String error


================================================================================
MSG: std_msgs/String
string data
")



(provide :mvn_pln/mp_getclose_xya "f236a8bf2a517b8af728eb19291f51cb")


