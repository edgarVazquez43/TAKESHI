;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::wait_for_switch)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'wait_for_switch (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_SWITCH")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_SWITCH"))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_SWITCHREQUEST")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_SWITCHREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_SWITCHRESPONSE")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_SWITCHRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::wait_for_switchRequest
  :super ros::object
  :slots (_repeat_sentence _timeout ))

(defmethod knowledge_msgs::wait_for_switchRequest
  (:init
   (&key
    ((:repeat_sentence __repeat_sentence) (instance knowledge_msgs::RepeatedSentence :init))
    ((:timeout __timeout) 0)
    )
   (send-super :init)
   (setq _repeat_sentence __repeat_sentence)
   (setq _timeout (round __timeout))
   self)
  (:repeat_sentence
   (&rest __repeat_sentence)
   (if (keywordp (car __repeat_sentence))
       (send* _repeat_sentence __repeat_sentence)
     (progn
       (if __repeat_sentence (setq _repeat_sentence (car __repeat_sentence)))
       _repeat_sentence)))
  (:timeout
   (&optional __timeout)
   (if __timeout (setq _timeout __timeout)) _timeout)
  (:serialization-length
   ()
   (+
    ;; knowledge_msgs/RepeatedSentence _repeat_sentence
    (send _repeat_sentence :serialization-length)
    ;; int32 _timeout
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; knowledge_msgs/RepeatedSentence _repeat_sentence
       (send _repeat_sentence :serialize s)
     ;; int32 _timeout
       (write-long _timeout s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; knowledge_msgs/RepeatedSentence _repeat_sentence
     (send _repeat_sentence :deserialize buf ptr-) (incf ptr- (send _repeat_sentence :serialization-length))
   ;; int32 _timeout
     (setq _timeout (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass knowledge_msgs::wait_for_switchResponse
  :super ros::object
  :slots (_goal _command_received ))

(defmethod knowledge_msgs::wait_for_switchResponse
  (:init
   (&key
    ((:goal __goal) "")
    ((:command_received __command_received) nil)
    )
   (send-super :init)
   (setq _goal (string __goal))
   (setq _command_received __command_received)
   self)
  (:goal
   (&optional __goal)
   (if __goal (setq _goal __goal)) _goal)
  (:command_received
   (&optional __command_received)
   (if __command_received (setq _command_received __command_received)) _command_received)
  (:serialization-length
   ()
   (+
    ;; string _goal
    4 (length _goal)
    ;; bool _command_received
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _goal
       (write-long (length _goal) s) (princ _goal s)
     ;; bool _command_received
       (if _command_received (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _goal
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _goal (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; bool _command_received
     (setq _command_received (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass knowledge_msgs::wait_for_switch
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::wait_for_switch :md5sum-) "de6659e2a24efa10fd97e00db2c838ff")
(setf (get knowledge_msgs::wait_for_switch :datatype-) "knowledge_msgs/wait_for_switch")
(setf (get knowledge_msgs::wait_for_switch :request) knowledge_msgs::wait_for_switchRequest)
(setf (get knowledge_msgs::wait_for_switch :response) knowledge_msgs::wait_for_switchResponse)

(defmethod knowledge_msgs::wait_for_switchRequest
  (:response () (instance knowledge_msgs::wait_for_switchResponse :init)))

(setf (get knowledge_msgs::wait_for_switchRequest :md5sum-) "de6659e2a24efa10fd97e00db2c838ff")
(setf (get knowledge_msgs::wait_for_switchRequest :datatype-) "knowledge_msgs/wait_for_switchRequest")
(setf (get knowledge_msgs::wait_for_switchRequest :definition-)
      "RepeatedSentence repeat_sentence
int32 timeout

================================================================================
MSG: knowledge_msgs/RepeatedSentence
string sentence
int32 repeat_time
---
string goal
bool command_received

")

(setf (get knowledge_msgs::wait_for_switchResponse :md5sum-) "de6659e2a24efa10fd97e00db2c838ff")
(setf (get knowledge_msgs::wait_for_switchResponse :datatype-) "knowledge_msgs/wait_for_switchResponse")
(setf (get knowledge_msgs::wait_for_switchResponse :definition-)
      "RepeatedSentence repeat_sentence
int32 timeout

================================================================================
MSG: knowledge_msgs/RepeatedSentence
string sentence
int32 repeat_time
---
string goal
bool command_received

")



(provide :knowledge_msgs/wait_for_switch "de6659e2a24efa10fd97e00db2c838ff")


