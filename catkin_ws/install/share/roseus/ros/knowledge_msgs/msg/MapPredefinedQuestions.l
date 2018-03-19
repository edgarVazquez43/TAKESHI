;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::MapPredefinedQuestions)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'MapPredefinedQuestions (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::MAPPREDEFINEDQUESTIONS")
  (make-package "KNOWLEDGE_MSGS::MAPPREDEFINEDQUESTIONS"))

(in-package "ROS")
;;//! \htmlinclude MapPredefinedQuestions.msg.html


(defclass knowledge_msgs::MapPredefinedQuestions
  :super ros::object
  :slots (_question _answer ))

(defmethod knowledge_msgs::MapPredefinedQuestions
  (:init
   (&key
    ((:question __question) "")
    ((:answer __answer) "")
    )
   (send-super :init)
   (setq _question (string __question))
   (setq _answer (string __answer))
   self)
  (:question
   (&optional __question)
   (if __question (setq _question __question)) _question)
  (:answer
   (&optional __answer)
   (if __answer (setq _answer __answer)) _answer)
  (:serialization-length
   ()
   (+
    ;; string _question
    4 (length _question)
    ;; string _answer
    4 (length _answer)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _question
       (write-long (length _question) s) (princ _question s)
     ;; string _answer
       (write-long (length _answer) s) (princ _answer s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _question
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _question (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _answer
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _answer (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get knowledge_msgs::MapPredefinedQuestions :md5sum-) "a27d8629aeefd2b315942fe4a74ab143")
(setf (get knowledge_msgs::MapPredefinedQuestions :datatype-) "knowledge_msgs/MapPredefinedQuestions")
(setf (get knowledge_msgs::MapPredefinedQuestions :definition-)
      "string question
string answer

")



(provide :knowledge_msgs/MapPredefinedQuestions "a27d8629aeefd2b315942fe4a74ab143")


