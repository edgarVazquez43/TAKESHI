;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::StrQueryKDB)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'StrQueryKDB (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::STRQUERYKDB")
  (make-package "KNOWLEDGE_MSGS::STRQUERYKDB"))
(unless (find-package "KNOWLEDGE_MSGS::STRQUERYKDBREQUEST")
  (make-package "KNOWLEDGE_MSGS::STRQUERYKDBREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::STRQUERYKDBRESPONSE")
  (make-package "KNOWLEDGE_MSGS::STRQUERYKDBRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::StrQueryKDBRequest
  :super ros::object
  :slots (_query ))

(defmethod knowledge_msgs::StrQueryKDBRequest
  (:init
   (&key
    ((:query __query) "")
    )
   (send-super :init)
   (setq _query (string __query))
   self)
  (:query
   (&optional __query)
   (if __query (setq _query __query)) _query)
  (:serialization-length
   ()
   (+
    ;; string _query
    4 (length _query)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _query
       (write-long (length _query) s) (princ _query s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _query
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _query (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass knowledge_msgs::StrQueryKDBResponse
  :super ros::object
  :slots (_result ))

(defmethod knowledge_msgs::StrQueryKDBResponse
  (:init
   (&key
    ((:result __result) "")
    )
   (send-super :init)
   (setq _result (string __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; string _result
    4 (length _result)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _result
       (write-long (length _result) s) (princ _result s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _result
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _result (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass knowledge_msgs::StrQueryKDB
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::StrQueryKDB :md5sum-) "40ece397ad679f27203bff340007bd45")
(setf (get knowledge_msgs::StrQueryKDB :datatype-) "knowledge_msgs/StrQueryKDB")
(setf (get knowledge_msgs::StrQueryKDB :request) knowledge_msgs::StrQueryKDBRequest)
(setf (get knowledge_msgs::StrQueryKDB :response) knowledge_msgs::StrQueryKDBResponse)

(defmethod knowledge_msgs::StrQueryKDBRequest
  (:response () (instance knowledge_msgs::StrQueryKDBResponse :init)))

(setf (get knowledge_msgs::StrQueryKDBRequest :md5sum-) "40ece397ad679f27203bff340007bd45")
(setf (get knowledge_msgs::StrQueryKDBRequest :datatype-) "knowledge_msgs/StrQueryKDBRequest")
(setf (get knowledge_msgs::StrQueryKDBRequest :definition-)
      "string query
---
string result

")

(setf (get knowledge_msgs::StrQueryKDBResponse :md5sum-) "40ece397ad679f27203bff340007bd45")
(setf (get knowledge_msgs::StrQueryKDBResponse :datatype-) "knowledge_msgs/StrQueryKDBResponse")
(setf (get knowledge_msgs::StrQueryKDBResponse :definition-)
      "string query
---
string result

")



(provide :knowledge_msgs/StrQueryKDB "40ece397ad679f27203bff340007bd45")


