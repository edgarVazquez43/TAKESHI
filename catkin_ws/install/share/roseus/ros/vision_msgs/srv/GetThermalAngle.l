;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::GetThermalAngle)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'GetThermalAngle (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::GETTHERMALANGLE")
  (make-package "VISION_MSGS::GETTHERMALANGLE"))
(unless (find-package "VISION_MSGS::GETTHERMALANGLEREQUEST")
  (make-package "VISION_MSGS::GETTHERMALANGLEREQUEST"))
(unless (find-package "VISION_MSGS::GETTHERMALANGLERESPONSE")
  (make-package "VISION_MSGS::GETTHERMALANGLERESPONSE"))

(in-package "ROS")





(defclass vision_msgs::GetThermalAngleRequest
  :super ros::object
  :slots ())

(defmethod vision_msgs::GetThermalAngleRequest
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

(defclass vision_msgs::GetThermalAngleResponse
  :super ros::object
  :slots (_th_angle ))

(defmethod vision_msgs::GetThermalAngleResponse
  (:init
   (&key
    ((:th_angle __th_angle) 0.0)
    )
   (send-super :init)
   (setq _th_angle (float __th_angle))
   self)
  (:th_angle
   (&optional __th_angle)
   (if __th_angle (setq _th_angle __th_angle)) _th_angle)
  (:serialization-length
   ()
   (+
    ;; float32 _th_angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _th_angle
       (sys::poke _th_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _th_angle
     (setq _th_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass vision_msgs::GetThermalAngle
  :super ros::object
  :slots ())

(setf (get vision_msgs::GetThermalAngle :md5sum-) "6e530ad148ac6d527edc145df842dd24")
(setf (get vision_msgs::GetThermalAngle :datatype-) "vision_msgs/GetThermalAngle")
(setf (get vision_msgs::GetThermalAngle :request) vision_msgs::GetThermalAngleRequest)
(setf (get vision_msgs::GetThermalAngle :response) vision_msgs::GetThermalAngleResponse)

(defmethod vision_msgs::GetThermalAngleRequest
  (:response () (instance vision_msgs::GetThermalAngleResponse :init)))

(setf (get vision_msgs::GetThermalAngleRequest :md5sum-) "6e530ad148ac6d527edc145df842dd24")
(setf (get vision_msgs::GetThermalAngleRequest :datatype-) "vision_msgs/GetThermalAngleRequest")
(setf (get vision_msgs::GetThermalAngleRequest :definition-)
      "---
float32 th_angle

")

(setf (get vision_msgs::GetThermalAngleResponse :md5sum-) "6e530ad148ac6d527edc145df842dd24")
(setf (get vision_msgs::GetThermalAngleResponse :datatype-) "vision_msgs/GetThermalAngleResponse")
(setf (get vision_msgs::GetThermalAngleResponse :definition-)
      "---
float32 th_angle

")



(provide :vision_msgs/GetThermalAngle "6e530ad148ac6d527edc145df842dd24")


