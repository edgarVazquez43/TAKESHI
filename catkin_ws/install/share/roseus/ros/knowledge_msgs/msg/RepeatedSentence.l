;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::RepeatedSentence)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'RepeatedSentence (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::REPEATEDSENTENCE")
  (make-package "KNOWLEDGE_MSGS::REPEATEDSENTENCE"))

(in-package "ROS")
;;//! \htmlinclude RepeatedSentence.msg.html


(defclass knowledge_msgs::RepeatedSentence
  :super ros::object
  :slots (_sentence _repeat_time ))

(defmethod knowledge_msgs::RepeatedSentence
  (:init
   (&key
    ((:sentence __sentence) "")
    ((:repeat_time __repeat_time) 0)
    )
   (send-super :init)
   (setq _sentence (string __sentence))
   (setq _repeat_time (round __repeat_time))
   self)
  (:sentence
   (&optional __sentence)
   (if __sentence (setq _sentence __sentence)) _sentence)
  (:repeat_time
   (&optional __repeat_time)
   (if __repeat_time (setq _repeat_time __repeat_time)) _repeat_time)
  (:serialization-length
   ()
   (+
    ;; string _sentence
    4 (length _sentence)
    ;; int32 _repeat_time
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _sentence
       (write-long (length _sentence) s) (princ _sentence s)
     ;; int32 _repeat_time
       (write-long _repeat_time s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _sentence
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _sentence (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _repeat_time
     (setq _repeat_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get knowledge_msgs::RepeatedSentence :md5sum-) "608dcaa9c362c4d6c83fcb8f1b807c83")
(setf (get knowledge_msgs::RepeatedSentence :datatype-) "knowledge_msgs/RepeatedSentence")
(setf (get knowledge_msgs::RepeatedSentence :definition-)
      "string sentence
int32 repeat_time

")



(provide :knowledge_msgs/RepeatedSentence "608dcaa9c362c4d6c83fcb8f1b807c83")


