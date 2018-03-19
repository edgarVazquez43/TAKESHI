;; Auto-generated. Do not edit!


(when (boundp 'navig_msgs::Location)
  (if (not (find-package "NAVIG_MSGS"))
    (make-package "NAVIG_MSGS"))
  (shadow 'Location (find-package "NAVIG_MSGS")))
(unless (find-package "NAVIG_MSGS::LOCATION")
  (make-package "NAVIG_MSGS::LOCATION"))

(in-package "ROS")
;;//! \htmlinclude Location.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass navig_msgs::Location
  :super ros::object
  :slots (_id _position _orientation _correct_angle ))

(defmethod navig_msgs::Location
  (:init
   (&key
    ((:id __id) "")
    ((:position __position) (instance geometry_msgs::Point :init))
    ((:orientation __orientation) 0.0)
    ((:correct_angle __correct_angle) nil)
    )
   (send-super :init)
   (setq _id (string __id))
   (setq _position __position)
   (setq _orientation (float __orientation))
   (setq _correct_angle __correct_angle)
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:orientation
   (&optional __orientation)
   (if __orientation (setq _orientation __orientation)) _orientation)
  (:correct_angle
   (&optional __correct_angle)
   (if __correct_angle (setq _correct_angle __correct_angle)) _correct_angle)
  (:serialization-length
   ()
   (+
    ;; string _id
    4 (length _id)
    ;; geometry_msgs/Point _position
    (send _position :serialization-length)
    ;; float32 _orientation
    4
    ;; bool _correct_angle
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; geometry_msgs/Point _position
       (send _position :serialize s)
     ;; float32 _orientation
       (sys::poke _orientation (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; bool _correct_angle
       (if _correct_angle (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Point _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; float32 _orientation
     (setq _orientation (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; bool _correct_angle
     (setq _correct_angle (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get navig_msgs::Location :md5sum-) "89fc57037e6b4762351eee5641dad2f8")
(setf (get navig_msgs::Location :datatype-) "navig_msgs/Location")
(setf (get navig_msgs::Location :definition-)
      "string id
geometry_msgs/Point position
float32 orientation
bool correct_angle
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :navig_msgs/Location "89fc57037e6b4762351eee5641dad2f8")


