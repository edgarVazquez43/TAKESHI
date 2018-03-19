;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::MapKnownLocation)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'MapKnownLocation (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::MAPKNOWNLOCATION")
  (make-package "KNOWLEDGE_MSGS::MAPKNOWNLOCATION"))

(in-package "ROS")
;;//! \htmlinclude MapKnownLocation.msg.html


(defclass knowledge_msgs::MapKnownLocation
  :super ros::object
  :slots (_name _value ))

(defmethod knowledge_msgs::MapKnownLocation
  (:init
   (&key
    ((:name __name) "")
    ((:value __value) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _value __value)
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; float32[] _value
    (* 4    (length _value)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; float32[] _value
     (write-long (length _value) s)
     (dotimes (i (length _value))
       (sys::poke (elt _value i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32[] _value
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _value (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _value i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get knowledge_msgs::MapKnownLocation :md5sum-) "8b31cd087b52c8acca2d7bf6ae29aeab")
(setf (get knowledge_msgs::MapKnownLocation :datatype-) "knowledge_msgs/MapKnownLocation")
(setf (get knowledge_msgs::MapKnownLocation :definition-)
      "string name
float32[] value

")



(provide :knowledge_msgs/MapKnownLocation "8b31cd087b52c8acca2d7bf6ae29aeab")


