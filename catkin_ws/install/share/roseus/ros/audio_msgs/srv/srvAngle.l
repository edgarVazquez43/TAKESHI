;; Auto-generated. Do not edit!


(when (boundp 'audio_msgs::srvAngle)
  (if (not (find-package "AUDIO_MSGS"))
    (make-package "AUDIO_MSGS"))
  (shadow 'srvAngle (find-package "AUDIO_MSGS")))
(unless (find-package "AUDIO_MSGS::SRVANGLE")
  (make-package "AUDIO_MSGS::SRVANGLE"))
(unless (find-package "AUDIO_MSGS::SRVANGLEREQUEST")
  (make-package "AUDIO_MSGS::SRVANGLEREQUEST"))
(unless (find-package "AUDIO_MSGS::SRVANGLERESPONSE")
  (make-package "AUDIO_MSGS::SRVANGLERESPONSE"))

(in-package "ROS")





(defclass audio_msgs::srvAngleRequest
  :super ros::object
  :slots ())

(defmethod audio_msgs::srvAngleRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass audio_msgs::srvAngleResponse
  :super ros::object
  :slots (_Angle ))

(defmethod audio_msgs::srvAngleResponse
  (:init
   (&key
    ((:Angle __Angle) 0.0)
    )
   (send-super :init)
   (setq _Angle (float __Angle))
   self)
  (:Angle
   (&optional __Angle)
   (if __Angle (setq _Angle __Angle)) _Angle)
  (:serialization-length
   ()
   (+
    ;; float32 _Angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _Angle
       (sys::poke _Angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _Angle
     (setq _Angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass audio_msgs::srvAngle
  :super ros::object
  :slots ())

(setf (get audio_msgs::srvAngle :md5sum-) "3c12d5a3eed4d7589fde4b3bcd93aff0")
(setf (get audio_msgs::srvAngle :datatype-) "audio_msgs/srvAngle")
(setf (get audio_msgs::srvAngle :request) audio_msgs::srvAngleRequest)
(setf (get audio_msgs::srvAngle :response) audio_msgs::srvAngleResponse)

(defmethod audio_msgs::srvAngleRequest
  (:response () (instance audio_msgs::srvAngleResponse :init)))

(setf (get audio_msgs::srvAngleRequest :md5sum-) "3c12d5a3eed4d7589fde4b3bcd93aff0")
(setf (get audio_msgs::srvAngleRequest :datatype-) "audio_msgs/srvAngleRequest")
(setf (get audio_msgs::srvAngleRequest :definition-)
      "---
float32 Angle
")

(setf (get audio_msgs::srvAngleResponse :md5sum-) "3c12d5a3eed4d7589fde4b3bcd93aff0")
(setf (get audio_msgs::srvAngleResponse :datatype-) "audio_msgs/srvAngleResponse")
(setf (get audio_msgs::srvAngleResponse :definition-)
      "---
float32 Angle
")



(provide :audio_msgs/srvAngle "3c12d5a3eed4d7589fde4b3bcd93aff0")


