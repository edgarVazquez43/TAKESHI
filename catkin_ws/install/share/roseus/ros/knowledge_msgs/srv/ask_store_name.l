;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::ask_store_name)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'ask_store_name (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::ASK_STORE_NAME")
  (make-package "KNOWLEDGE_MSGS::ASK_STORE_NAME"))
(unless (find-package "KNOWLEDGE_MSGS::ASK_STORE_NAMEREQUEST")
  (make-package "KNOWLEDGE_MSGS::ASK_STORE_NAMEREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::ASK_STORE_NAMERESPONSE")
  (make-package "KNOWLEDGE_MSGS::ASK_STORE_NAMERESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::ask_store_nameRequest
  :super ros::object
  :slots (_attempt_timeout _repeat_timeout _max_attempts ))

(defmethod knowledge_msgs::ask_store_nameRequest
  (:init
   (&key
    ((:attempt_timeout __attempt_timeout) 0)
    ((:repeat_timeout __repeat_timeout) 0)
    ((:max_attempts __max_attempts) 0)
    )
   (send-super :init)
   (setq _attempt_timeout (round __attempt_timeout))
   (setq _repeat_timeout (round __repeat_timeout))
   (setq _max_attempts (round __max_attempts))
   self)
  (:attempt_timeout
   (&optional __attempt_timeout)
   (if __attempt_timeout (setq _attempt_timeout __attempt_timeout)) _attempt_timeout)
  (:repeat_timeout
   (&optional __repeat_timeout)
   (if __repeat_timeout (setq _repeat_timeout __repeat_timeout)) _repeat_timeout)
  (:max_attempts
   (&optional __max_attempts)
   (if __max_attempts (setq _max_attempts __max_attempts)) _max_attempts)
  (:serialization-length
   ()
   (+
    ;; int32 _attempt_timeout
    4
    ;; int32 _repeat_timeout
    4
    ;; int32 _max_attempts
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _attempt_timeout
       (write-long _attempt_timeout s)
     ;; int32 _repeat_timeout
       (write-long _repeat_timeout s)
     ;; int32 _max_attempts
       (write-long _max_attempts s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _attempt_timeout
     (setq _attempt_timeout (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _repeat_timeout
     (setq _repeat_timeout (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _max_attempts
     (setq _max_attempts (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass knowledge_msgs::ask_store_nameResponse
  :super ros::object
  :slots (_success _stored_name ))

(defmethod knowledge_msgs::ask_store_nameResponse
  (:init
   (&key
    ((:success __success) nil)
    ((:stored_name __stored_name) "")
    )
   (send-super :init)
   (setq _success __success)
   (setq _stored_name (string __stored_name))
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:stored_name
   (&optional __stored_name)
   (if __stored_name (setq _stored_name __stored_name)) _stored_name)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ;; string _stored_name
    4 (length _stored_name)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;; string _stored_name
       (write-long (length _stored_name) s) (princ _stored_name s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _stored_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _stored_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass knowledge_msgs::ask_store_name
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::ask_store_name :md5sum-) "8a5870e234d40e3af46fc0ab4649d821")
(setf (get knowledge_msgs::ask_store_name :datatype-) "knowledge_msgs/ask_store_name")
(setf (get knowledge_msgs::ask_store_name :request) knowledge_msgs::ask_store_nameRequest)
(setf (get knowledge_msgs::ask_store_name :response) knowledge_msgs::ask_store_nameResponse)

(defmethod knowledge_msgs::ask_store_nameRequest
  (:response () (instance knowledge_msgs::ask_store_nameResponse :init)))

(setf (get knowledge_msgs::ask_store_nameRequest :md5sum-) "8a5870e234d40e3af46fc0ab4649d821")
(setf (get knowledge_msgs::ask_store_nameRequest :datatype-) "knowledge_msgs/ask_store_nameRequest")
(setf (get knowledge_msgs::ask_store_nameRequest :definition-)
      "int32 attempt_timeout
int32 repeat_timeout
int32 max_attempts
---
bool success
string stored_name

")

(setf (get knowledge_msgs::ask_store_nameResponse :md5sum-) "8a5870e234d40e3af46fc0ab4649d821")
(setf (get knowledge_msgs::ask_store_nameResponse :datatype-) "knowledge_msgs/ask_store_nameResponse")
(setf (get knowledge_msgs::ask_store_nameResponse :definition-)
      "int32 attempt_timeout
int32 repeat_timeout
int32 max_attempts
---
bool success
string stored_name

")



(provide :knowledge_msgs/ask_store_name "8a5870e234d40e3af46fc0ab4649d821")


