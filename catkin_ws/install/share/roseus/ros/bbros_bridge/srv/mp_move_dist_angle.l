;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::mp_move_dist_angle)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'mp_move_dist_angle (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::MP_MOVE_DIST_ANGLE")
  (make-package "BBROS_BRIDGE::MP_MOVE_DIST_ANGLE"))
(unless (find-package "BBROS_BRIDGE::MP_MOVE_DIST_ANGLEREQUEST")
  (make-package "BBROS_BRIDGE::MP_MOVE_DIST_ANGLEREQUEST"))
(unless (find-package "BBROS_BRIDGE::MP_MOVE_DIST_ANGLERESPONSE")
  (make-package "BBROS_BRIDGE::MP_MOVE_DIST_ANGLERESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass bbros_bridge::mp_move_dist_angleRequest
  :super ros::object
  :slots (_bearing _distance ))

(defmethod bbros_bridge::mp_move_dist_angleRequest
  (:init
   (&key
    ((:bearing __bearing) (instance std_msgs::Float32 :init))
    ((:distance __distance) (instance std_msgs::Float32 :init))
    )
   (send-super :init)
   (setq _bearing __bearing)
   (setq _distance __distance)
   self)
  (:bearing
   (&rest __bearing)
   (if (keywordp (car __bearing))
       (send* _bearing __bearing)
     (progn
       (if __bearing (setq _bearing (car __bearing)))
       _bearing)))
  (:distance
   (&rest __distance)
   (if (keywordp (car __distance))
       (send* _distance __distance)
     (progn
       (if __distance (setq _distance (car __distance)))
       _distance)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32 _bearing
    (send _bearing :serialization-length)
    ;; std_msgs/Float32 _distance
    (send _distance :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32 _bearing
       (send _bearing :serialize s)
     ;; std_msgs/Float32 _distance
       (send _distance :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32 _bearing
     (send _bearing :deserialize buf ptr-) (incf ptr- (send _bearing :serialization-length))
   ;; std_msgs/Float32 _distance
     (send _distance :deserialize buf ptr-) (incf ptr- (send _distance :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::mp_move_dist_angleResponse
  :super ros::object
  :slots (_traveledBearing _traveledDistance ))

(defmethod bbros_bridge::mp_move_dist_angleResponse
  (:init
   (&key
    ((:traveledBearing __traveledBearing) (instance std_msgs::Float32 :init))
    ((:traveledDistance __traveledDistance) (instance std_msgs::Float32 :init))
    )
   (send-super :init)
   (setq _traveledBearing __traveledBearing)
   (setq _traveledDistance __traveledDistance)
   self)
  (:traveledBearing
   (&rest __traveledBearing)
   (if (keywordp (car __traveledBearing))
       (send* _traveledBearing __traveledBearing)
     (progn
       (if __traveledBearing (setq _traveledBearing (car __traveledBearing)))
       _traveledBearing)))
  (:traveledDistance
   (&rest __traveledDistance)
   (if (keywordp (car __traveledDistance))
       (send* _traveledDistance __traveledDistance)
     (progn
       (if __traveledDistance (setq _traveledDistance (car __traveledDistance)))
       _traveledDistance)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32 _traveledBearing
    (send _traveledBearing :serialization-length)
    ;; std_msgs/Float32 _traveledDistance
    (send _traveledDistance :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32 _traveledBearing
       (send _traveledBearing :serialize s)
     ;; std_msgs/Float32 _traveledDistance
       (send _traveledDistance :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32 _traveledBearing
     (send _traveledBearing :deserialize buf ptr-) (incf ptr- (send _traveledBearing :serialization-length))
   ;; std_msgs/Float32 _traveledDistance
     (send _traveledDistance :deserialize buf ptr-) (incf ptr- (send _traveledDistance :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::mp_move_dist_angle
  :super ros::object
  :slots ())

(setf (get bbros_bridge::mp_move_dist_angle :md5sum-) "930663ac8b505c579c42369296ce1052")
(setf (get bbros_bridge::mp_move_dist_angle :datatype-) "bbros_bridge/mp_move_dist_angle")
(setf (get bbros_bridge::mp_move_dist_angle :request) bbros_bridge::mp_move_dist_angleRequest)
(setf (get bbros_bridge::mp_move_dist_angle :response) bbros_bridge::mp_move_dist_angleResponse)

(defmethod bbros_bridge::mp_move_dist_angleRequest
  (:response () (instance bbros_bridge::mp_move_dist_angleResponse :init)))

(setf (get bbros_bridge::mp_move_dist_angleRequest :md5sum-) "930663ac8b505c579c42369296ce1052")
(setf (get bbros_bridge::mp_move_dist_angleRequest :datatype-) "bbros_bridge/mp_move_dist_angleRequest")
(setf (get bbros_bridge::mp_move_dist_angleRequest :definition-)
      "std_msgs/Float32 bearing
std_msgs/Float32 distance

================================================================================
MSG: std_msgs/Float32
---
std_msgs/Float32 traveledBearing
std_msgs/Float32 traveledDistance


================================================================================
MSG: std_msgs/Float32
")

(setf (get bbros_bridge::mp_move_dist_angleResponse :md5sum-) "930663ac8b505c579c42369296ce1052")
(setf (get bbros_bridge::mp_move_dist_angleResponse :datatype-) "bbros_bridge/mp_move_dist_angleResponse")
(setf (get bbros_bridge::mp_move_dist_angleResponse :definition-)
      "std_msgs/Float32 bearing
std_msgs/Float32 distance

================================================================================
MSG: std_msgs/Float32
---
std_msgs/Float32 traveledBearing
std_msgs/Float32 traveledDistance


================================================================================
MSG: std_msgs/Float32
")



(provide :bbros_bridge/mp_move_dist_angle "930663ac8b505c579c42369296ce1052")


