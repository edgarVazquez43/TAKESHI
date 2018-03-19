;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::AddUpdateKnownLoc)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'AddUpdateKnownLoc (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::ADDUPDATEKNOWNLOC")
  (make-package "KNOWLEDGE_MSGS::ADDUPDATEKNOWNLOC"))
(unless (find-package "KNOWLEDGE_MSGS::ADDUPDATEKNOWNLOCREQUEST")
  (make-package "KNOWLEDGE_MSGS::ADDUPDATEKNOWNLOCREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::ADDUPDATEKNOWNLOCRESPONSE")
  (make-package "KNOWLEDGE_MSGS::ADDUPDATEKNOWNLOCRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::AddUpdateKnownLocRequest
  :super ros::object
  :slots (_loc ))

(defmethod knowledge_msgs::AddUpdateKnownLocRequest
  (:init
   (&key
    ((:loc __loc) (instance knowledge_msgs::MapKnownLocation :init))
    )
   (send-super :init)
   (setq _loc __loc)
   self)
  (:loc
   (&rest __loc)
   (if (keywordp (car __loc))
       (send* _loc __loc)
     (progn
       (if __loc (setq _loc (car __loc)))
       _loc)))
  (:serialization-length
   ()
   (+
    ;; knowledge_msgs/MapKnownLocation _loc
    (send _loc :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; knowledge_msgs/MapKnownLocation _loc
       (send _loc :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; knowledge_msgs/MapKnownLocation _loc
     (send _loc :deserialize buf ptr-) (incf ptr- (send _loc :serialization-length))
   ;;
   self)
  )

(defclass knowledge_msgs::AddUpdateKnownLocResponse
  :super ros::object
  :slots ())

(defmethod knowledge_msgs::AddUpdateKnownLocResponse
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

(defclass knowledge_msgs::AddUpdateKnownLoc
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::AddUpdateKnownLoc :md5sum-) "c8eea2400325e7fa5b296976b0201acc")
(setf (get knowledge_msgs::AddUpdateKnownLoc :datatype-) "knowledge_msgs/AddUpdateKnownLoc")
(setf (get knowledge_msgs::AddUpdateKnownLoc :request) knowledge_msgs::AddUpdateKnownLocRequest)
(setf (get knowledge_msgs::AddUpdateKnownLoc :response) knowledge_msgs::AddUpdateKnownLocResponse)

(defmethod knowledge_msgs::AddUpdateKnownLocRequest
  (:response () (instance knowledge_msgs::AddUpdateKnownLocResponse :init)))

(setf (get knowledge_msgs::AddUpdateKnownLocRequest :md5sum-) "c8eea2400325e7fa5b296976b0201acc")
(setf (get knowledge_msgs::AddUpdateKnownLocRequest :datatype-) "knowledge_msgs/AddUpdateKnownLocRequest")
(setf (get knowledge_msgs::AddUpdateKnownLocRequest :definition-)
      "MapKnownLocation loc

================================================================================
MSG: knowledge_msgs/MapKnownLocation
string name
float32[] value
---

")

(setf (get knowledge_msgs::AddUpdateKnownLocResponse :md5sum-) "c8eea2400325e7fa5b296976b0201acc")
(setf (get knowledge_msgs::AddUpdateKnownLocResponse :datatype-) "knowledge_msgs/AddUpdateKnownLocResponse")
(setf (get knowledge_msgs::AddUpdateKnownLocResponse :definition-)
      "MapKnownLocation loc

================================================================================
MSG: knowledge_msgs/MapKnownLocation
string name
float32[] value
---

")



(provide :knowledge_msgs/AddUpdateKnownLoc "c8eea2400325e7fa5b296976b0201acc")


