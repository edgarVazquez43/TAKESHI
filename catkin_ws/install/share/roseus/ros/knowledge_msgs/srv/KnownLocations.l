;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::KnownLocations)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'KnownLocations (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::KNOWNLOCATIONS")
  (make-package "KNOWLEDGE_MSGS::KNOWNLOCATIONS"))
(unless (find-package "KNOWLEDGE_MSGS::KNOWNLOCATIONSREQUEST")
  (make-package "KNOWLEDGE_MSGS::KNOWNLOCATIONSREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::KNOWNLOCATIONSRESPONSE")
  (make-package "KNOWLEDGE_MSGS::KNOWNLOCATIONSRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::KnownLocationsRequest
  :super ros::object
  :slots ())

(defmethod knowledge_msgs::KnownLocationsRequest
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

(defclass knowledge_msgs::KnownLocationsResponse
  :super ros::object
  :slots (_locations ))

(defmethod knowledge_msgs::KnownLocationsResponse
  (:init
   (&key
    ((:locations __locations) (let (r) (dotimes (i 0) (push (instance knowledge_msgs::MapKnownLocation :init) r)) r))
    )
   (send-super :init)
   (setq _locations __locations)
   self)
  (:locations
   (&rest __locations)
   (if (keywordp (car __locations))
       (send* _locations __locations)
     (progn
       (if __locations (setq _locations (car __locations)))
       _locations)))
  (:serialization-length
   ()
   (+
    ;; knowledge_msgs/MapKnownLocation[] _locations
    (apply #'+ (send-all _locations :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; knowledge_msgs/MapKnownLocation[] _locations
     (write-long (length _locations) s)
     (dolist (elem _locations)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; knowledge_msgs/MapKnownLocation[] _locations
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _locations (let (r) (dotimes (i n) (push (instance knowledge_msgs::MapKnownLocation :init) r)) r))
     (dolist (elem- _locations)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass knowledge_msgs::KnownLocations
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::KnownLocations :md5sum-) "6bd6e203855e6403b9f65224e511af1a")
(setf (get knowledge_msgs::KnownLocations :datatype-) "knowledge_msgs/KnownLocations")
(setf (get knowledge_msgs::KnownLocations :request) knowledge_msgs::KnownLocationsRequest)
(setf (get knowledge_msgs::KnownLocations :response) knowledge_msgs::KnownLocationsResponse)

(defmethod knowledge_msgs::KnownLocationsRequest
  (:response () (instance knowledge_msgs::KnownLocationsResponse :init)))

(setf (get knowledge_msgs::KnownLocationsRequest :md5sum-) "6bd6e203855e6403b9f65224e511af1a")
(setf (get knowledge_msgs::KnownLocationsRequest :datatype-) "knowledge_msgs/KnownLocationsRequest")
(setf (get knowledge_msgs::KnownLocationsRequest :definition-)
      "---
MapKnownLocation[] locations


================================================================================
MSG: knowledge_msgs/MapKnownLocation
string name
float32[] value
")

(setf (get knowledge_msgs::KnownLocationsResponse :md5sum-) "6bd6e203855e6403b9f65224e511af1a")
(setf (get knowledge_msgs::KnownLocationsResponse :datatype-) "knowledge_msgs/KnownLocationsResponse")
(setf (get knowledge_msgs::KnownLocationsResponse :definition-)
      "---
MapKnownLocation[] locations


================================================================================
MSG: knowledge_msgs/MapKnownLocation
string name
float32[] value
")



(provide :knowledge_msgs/KnownLocations "6bd6e203855e6403b9f65224e511af1a")


