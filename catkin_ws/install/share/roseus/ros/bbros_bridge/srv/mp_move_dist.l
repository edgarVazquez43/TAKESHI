;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::mp_move_dist)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'mp_move_dist (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::MP_MOVE_DIST")
  (make-package "BBROS_BRIDGE::MP_MOVE_DIST"))
(unless (find-package "BBROS_BRIDGE::MP_MOVE_DISTREQUEST")
  (make-package "BBROS_BRIDGE::MP_MOVE_DISTREQUEST"))
(unless (find-package "BBROS_BRIDGE::MP_MOVE_DISTRESPONSE")
  (make-package "BBROS_BRIDGE::MP_MOVE_DISTRESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass bbros_bridge::mp_move_distRequest
  :super ros::object
  :slots (_distance ))

(defmethod bbros_bridge::mp_move_distRequest
  (:init
   (&key
    ((:distance __distance) (instance std_msgs::Float32 :init))
    )
   (send-super :init)
   (setq _distance __distance)
   self)
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
    ;; std_msgs/Float32 _distance
    (send _distance :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32 _distance
       (send _distance :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32 _distance
     (send _distance :deserialize buf ptr-) (incf ptr- (send _distance :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::mp_move_distResponse
  :super ros::object
  :slots (_traveledDistance ))

(defmethod bbros_bridge::mp_move_distResponse
  (:init
   (&key
    ((:traveledDistance __traveledDistance) (instance std_msgs::Float32 :init))
    )
   (send-super :init)
   (setq _traveledDistance __traveledDistance)
   self)
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
    ;; std_msgs/Float32 _traveledDistance
    (send _traveledDistance :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32 _traveledDistance
       (send _traveledDistance :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32 _traveledDistance
     (send _traveledDistance :deserialize buf ptr-) (incf ptr- (send _traveledDistance :serialization-length))
   ;;
   self)
  )

(defclass bbros_bridge::mp_move_dist
  :super ros::object
  :slots ())

(setf (get bbros_bridge::mp_move_dist :md5sum-) "6869a1d070e885a82e01cea5e86d2372")
(setf (get bbros_bridge::mp_move_dist :datatype-) "bbros_bridge/mp_move_dist")
(setf (get bbros_bridge::mp_move_dist :request) bbros_bridge::mp_move_distRequest)
(setf (get bbros_bridge::mp_move_dist :response) bbros_bridge::mp_move_distResponse)

(defmethod bbros_bridge::mp_move_distRequest
  (:response () (instance bbros_bridge::mp_move_distResponse :init)))

(setf (get bbros_bridge::mp_move_distRequest :md5sum-) "6869a1d070e885a82e01cea5e86d2372")
(setf (get bbros_bridge::mp_move_distRequest :datatype-) "bbros_bridge/mp_move_distRequest")
(setf (get bbros_bridge::mp_move_distRequest :definition-)
      "std_msgs/Float32 distance

================================================================================
MSG: std_msgs/Float32
---
std_msgs/Float32 traveledDistance


================================================================================
MSG: std_msgs/Float32
")

(setf (get bbros_bridge::mp_move_distResponse :md5sum-) "6869a1d070e885a82e01cea5e86d2372")
(setf (get bbros_bridge::mp_move_distResponse :datatype-) "bbros_bridge/mp_move_distResponse")
(setf (get bbros_bridge::mp_move_distResponse :definition-)
      "std_msgs/Float32 distance

================================================================================
MSG: std_msgs/Float32
---
std_msgs/Float32 traveledDistance


================================================================================
MSG: std_msgs/Float32
")



(provide :bbros_bridge/mp_move_dist "6869a1d070e885a82e01cea5e86d2372")


