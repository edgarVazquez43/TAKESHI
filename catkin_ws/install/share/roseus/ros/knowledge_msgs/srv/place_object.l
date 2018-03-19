;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::place_object)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'place_object (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::PLACE_OBJECT")
  (make-package "KNOWLEDGE_MSGS::PLACE_OBJECT"))
(unless (find-package "KNOWLEDGE_MSGS::PLACE_OBJECTREQUEST")
  (make-package "KNOWLEDGE_MSGS::PLACE_OBJECTREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::PLACE_OBJECTRESPONSE")
  (make-package "KNOWLEDGE_MSGS::PLACE_OBJECTRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::place_objectRequest
  :super ros::object
  :slots (_dest_location _arm_to_use ))

(defmethod knowledge_msgs::place_objectRequest
  (:init
   (&key
    ((:dest_location __dest_location) "")
    ((:arm_to_use __arm_to_use) 0)
    )
   (send-super :init)
   (setq _dest_location (string __dest_location))
   (setq _arm_to_use (round __arm_to_use))
   self)
  (:dest_location
   (&optional __dest_location)
   (if __dest_location (setq _dest_location __dest_location)) _dest_location)
  (:arm_to_use
   (&optional __arm_to_use)
   (if __arm_to_use (setq _arm_to_use __arm_to_use)) _arm_to_use)
  (:serialization-length
   ()
   (+
    ;; string _dest_location
    4 (length _dest_location)
    ;; int32 _arm_to_use
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _dest_location
       (write-long (length _dest_location) s) (princ _dest_location s)
     ;; int32 _arm_to_use
       (write-long _arm_to_use s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _dest_location
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _dest_location (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _arm_to_use
     (setq _arm_to_use (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass knowledge_msgs::place_objectResponse
  :super ros::object
  :slots (_task_success ))

(defmethod knowledge_msgs::place_objectResponse
  (:init
   (&key
    ((:task_success __task_success) nil)
    )
   (send-super :init)
   (setq _task_success __task_success)
   self)
  (:task_success
   (&optional __task_success)
   (if __task_success (setq _task_success __task_success)) _task_success)
  (:serialization-length
   ()
   (+
    ;; bool _task_success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _task_success
       (if _task_success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _task_success
     (setq _task_success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass knowledge_msgs::place_object
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::place_object :md5sum-) "72e5fc1d3c709f9c79fea87497774dd9")
(setf (get knowledge_msgs::place_object :datatype-) "knowledge_msgs/place_object")
(setf (get knowledge_msgs::place_object :request) knowledge_msgs::place_objectRequest)
(setf (get knowledge_msgs::place_object :response) knowledge_msgs::place_objectResponse)

(defmethod knowledge_msgs::place_objectRequest
  (:response () (instance knowledge_msgs::place_objectResponse :init)))

(setf (get knowledge_msgs::place_objectRequest :md5sum-) "72e5fc1d3c709f9c79fea87497774dd9")
(setf (get knowledge_msgs::place_objectRequest :datatype-) "knowledge_msgs/place_objectRequest")
(setf (get knowledge_msgs::place_objectRequest :definition-)
      "string dest_location
int32 arm_to_use
---
bool task_success

")

(setf (get knowledge_msgs::place_objectResponse :md5sum-) "72e5fc1d3c709f9c79fea87497774dd9")
(setf (get knowledge_msgs::place_objectResponse :datatype-) "knowledge_msgs/place_objectResponse")
(setf (get knowledge_msgs::place_objectResponse :definition-)
      "string dest_location
int32 arm_to_use
---
bool task_success

")



(provide :knowledge_msgs/place_object "72e5fc1d3c709f9c79fea87497774dd9")


