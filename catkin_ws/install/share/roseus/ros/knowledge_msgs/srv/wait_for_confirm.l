;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::wait_for_confirm)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'wait_for_confirm (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_CONFIRM")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_CONFIRM"))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_CONFIRMREQUEST")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_CONFIRMREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_CONFIRMRESPONSE")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_CONFIRMRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::wait_for_confirmRequest
  :super ros::object
  :slots (_repeat_sentence _timeout ))

(defmethod knowledge_msgs::wait_for_confirmRequest
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

(defclass knowledge_msgs::wait_for_confirmResponse
  :super ros::object
  :slots (_confirmation_received ))

(defmethod knowledge_msgs::wait_for_confirmResponse
  (:init
   (&key
    ((:confirmation_received __confirmation_received) nil)
    )
   (send-super :init)
   (setq _confirmation_received __confirmation_received)
   self)
  (:confirmation_received
   (&optional __confirmation_received)
   (if __confirmation_received (setq _confirmation_received __confirmation_received)) _confirmation_received)
  (:serialization-length
   ()
   (+
    ;; bool _confirmation_received
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _confirmation_received
       (if _confirmation_received (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _confirmation_received
     (setq _confirmation_received (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass knowledge_msgs::wait_for_confirm
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::wait_for_confirm :md5sum-) "aae0ce22da8fbc00ac2c3455196d2577")
(setf (get knowledge_msgs::wait_for_confirm :datatype-) "knowledge_msgs/wait_for_confirm")
(setf (get knowledge_msgs::wait_for_confirm :request) knowledge_msgs::wait_for_confirmRequest)
(setf (get knowledge_msgs::wait_for_confirm :response) knowledge_msgs::wait_for_confirmResponse)

(defmethod knowledge_msgs::wait_for_confirmRequest
  (:response () (instance knowledge_msgs::wait_for_confirmResponse :init)))

(setf (get knowledge_msgs::wait_for_confirmRequest :md5sum-) "aae0ce22da8fbc00ac2c3455196d2577")
(setf (get knowledge_msgs::wait_for_confirmRequest :datatype-) "knowledge_msgs/wait_for_confirmRequest")
(setf (get knowledge_msgs::wait_for_confirmRequest :definition-)
      "RepeatedSentence repeat_sentence
int32 timeout

================================================================================
MSG: knowledge_msgs/RepeatedSentence
string sentence
int32 repeat_time
---
bool confirmation_received

")

(setf (get knowledge_msgs::wait_for_confirmResponse :md5sum-) "aae0ce22da8fbc00ac2c3455196d2577")
(setf (get knowledge_msgs::wait_for_confirmResponse :datatype-) "knowledge_msgs/wait_for_confirmResponse")
(setf (get knowledge_msgs::wait_for_confirmResponse :definition-)
      "RepeatedSentence repeat_sentence
int32 timeout

================================================================================
MSG: knowledge_msgs/RepeatedSentence
string sentence
int32 repeat_time
---
bool confirmation_received

")



(provide :knowledge_msgs/wait_for_confirm "aae0ce22da8fbc00ac2c3455196d2577")


