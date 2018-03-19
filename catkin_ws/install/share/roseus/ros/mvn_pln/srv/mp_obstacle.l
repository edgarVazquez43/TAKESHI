;; Auto-generated. Do not edit!


(when (boundp 'mvn_pln::mp_obstacle)
  (if (not (find-package "MVN_PLN"))
    (make-package "MVN_PLN"))
  (shadow 'mp_obstacle (find-package "MVN_PLN")))
(unless (find-package "MVN_PLN::MP_OBSTACLE")
  (make-package "MVN_PLN::MP_OBSTACLE"))
(unless (find-package "MVN_PLN::MP_OBSTACLEREQUEST")
  (make-package "MVN_PLN::MP_OBSTACLEREQUEST"))
(unless (find-package "MVN_PLN::MP_OBSTACLERESPONSE")
  (make-package "MVN_PLN::MP_OBSTACLERESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mvn_pln::mp_obstacleRequest
  :super ros::object
  :slots (_obstacle ))

(defmethod mvn_pln::mp_obstacleRequest
  (:init
   (&key
    ((:obstacle __obstacle) (instance std_msgs::String :init))
    )
   (send-super :init)
   (setq _obstacle __obstacle)
   self)
  (:obstacle
   (&rest __obstacle)
   (if (keywordp (car __obstacle))
       (send* _obstacle __obstacle)
     (progn
       (if __obstacle (setq _obstacle (car __obstacle)))
       _obstacle)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/String _obstacle
    (send _obstacle :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/String _obstacle
       (send _obstacle :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/String _obstacle
     (send _obstacle :deserialize buf ptr-) (incf ptr- (send _obstacle :serialization-length))
   ;;
   self)
  )

(defclass mvn_pln::mp_obstacleResponse
  :super ros::object
  :slots (_found ))

(defmethod mvn_pln::mp_obstacleResponse
  (:init
   (&key
    ((:found __found) (instance std_msgs::Bool :init))
    )
   (send-super :init)
   (setq _found __found)
   self)
  (:found
   (&rest __found)
   (if (keywordp (car __found))
       (send* _found __found)
     (progn
       (if __found (setq _found (car __found)))
       _found)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Bool _found
    (send _found :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Bool _found
       (send _found :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Bool _found
     (send _found :deserialize buf ptr-) (incf ptr- (send _found :serialization-length))
   ;;
   self)
  )

(defclass mvn_pln::mp_obstacle
  :super ros::object
  :slots ())

(setf (get mvn_pln::mp_obstacle :md5sum-) "938f9cc76650ee8bc7d6dc8275ba504b")
(setf (get mvn_pln::mp_obstacle :datatype-) "mvn_pln/mp_obstacle")
(setf (get mvn_pln::mp_obstacle :request) mvn_pln::mp_obstacleRequest)
(setf (get mvn_pln::mp_obstacle :response) mvn_pln::mp_obstacleResponse)

(defmethod mvn_pln::mp_obstacleRequest
  (:response () (instance mvn_pln::mp_obstacleResponse :init)))

(setf (get mvn_pln::mp_obstacleRequest :md5sum-) "938f9cc76650ee8bc7d6dc8275ba504b")
(setf (get mvn_pln::mp_obstacleRequest :datatype-) "mvn_pln/mp_obstacleRequest")
(setf (get mvn_pln::mp_obstacleRequest :definition-)
      "std_msgs/String obstacle

================================================================================
MSG: std_msgs/String
string data
---
std_msgs/Bool found

================================================================================
MSG: std_msgs/Bool
")

(setf (get mvn_pln::mp_obstacleResponse :md5sum-) "938f9cc76650ee8bc7d6dc8275ba504b")
(setf (get mvn_pln::mp_obstacleResponse :datatype-) "mvn_pln/mp_obstacleResponse")
(setf (get mvn_pln::mp_obstacleResponse :definition-)
      "std_msgs/String obstacle

================================================================================
MSG: std_msgs/String
string data
---
std_msgs/Bool found

================================================================================
MSG: std_msgs/Bool
")



(provide :mvn_pln/mp_obstacle "938f9cc76650ee8bc7d6dc8275ba504b")


