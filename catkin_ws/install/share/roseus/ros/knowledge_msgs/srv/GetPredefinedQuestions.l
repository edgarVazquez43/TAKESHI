;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::GetPredefinedQuestions)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'GetPredefinedQuestions (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::GETPREDEFINEDQUESTIONS")
  (make-package "KNOWLEDGE_MSGS::GETPREDEFINEDQUESTIONS"))
(unless (find-package "KNOWLEDGE_MSGS::GETPREDEFINEDQUESTIONSREQUEST")
  (make-package "KNOWLEDGE_MSGS::GETPREDEFINEDQUESTIONSREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::GETPREDEFINEDQUESTIONSRESPONSE")
  (make-package "KNOWLEDGE_MSGS::GETPREDEFINEDQUESTIONSRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::GetPredefinedQuestionsRequest
  :super ros::object
  :slots ())

(defmethod knowledge_msgs::GetPredefinedQuestionsRequest
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

(defclass knowledge_msgs::GetPredefinedQuestionsResponse
  :super ros::object
  :slots (_predefinedQuestions ))

(defmethod knowledge_msgs::GetPredefinedQuestionsResponse
  (:init
   (&key
    ((:predefinedQuestions __predefinedQuestions) (let (r) (dotimes (i 0) (push (instance knowledge_msgs::MapPredefinedQuestions :init) r)) r))
    )
   (send-super :init)
   (setq _predefinedQuestions __predefinedQuestions)
   self)
  (:predefinedQuestions
   (&rest __predefinedQuestions)
   (if (keywordp (car __predefinedQuestions))
       (send* _predefinedQuestions __predefinedQuestions)
     (progn
       (if __predefinedQuestions (setq _predefinedQuestions (car __predefinedQuestions)))
       _predefinedQuestions)))
  (:serialization-length
   ()
   (+
    ;; knowledge_msgs/MapPredefinedQuestions[] _predefinedQuestions
    (apply #'+ (send-all _predefinedQuestions :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; knowledge_msgs/MapPredefinedQuestions[] _predefinedQuestions
     (write-long (length _predefinedQuestions) s)
     (dolist (elem _predefinedQuestions)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; knowledge_msgs/MapPredefinedQuestions[] _predefinedQuestions
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _predefinedQuestions (let (r) (dotimes (i n) (push (instance knowledge_msgs::MapPredefinedQuestions :init) r)) r))
     (dolist (elem- _predefinedQuestions)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass knowledge_msgs::GetPredefinedQuestions
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::GetPredefinedQuestions :md5sum-) "68d94395b4ec7b52f8954f4e6ebf72fa")
(setf (get knowledge_msgs::GetPredefinedQuestions :datatype-) "knowledge_msgs/GetPredefinedQuestions")
(setf (get knowledge_msgs::GetPredefinedQuestions :request) knowledge_msgs::GetPredefinedQuestionsRequest)
(setf (get knowledge_msgs::GetPredefinedQuestions :response) knowledge_msgs::GetPredefinedQuestionsResponse)

(defmethod knowledge_msgs::GetPredefinedQuestionsRequest
  (:response () (instance knowledge_msgs::GetPredefinedQuestionsResponse :init)))

(setf (get knowledge_msgs::GetPredefinedQuestionsRequest :md5sum-) "68d94395b4ec7b52f8954f4e6ebf72fa")
(setf (get knowledge_msgs::GetPredefinedQuestionsRequest :datatype-) "knowledge_msgs/GetPredefinedQuestionsRequest")
(setf (get knowledge_msgs::GetPredefinedQuestionsRequest :definition-)
      "---
MapPredefinedQuestions[] predefinedQuestions


================================================================================
MSG: knowledge_msgs/MapPredefinedQuestions
string question
string answer
")

(setf (get knowledge_msgs::GetPredefinedQuestionsResponse :md5sum-) "68d94395b4ec7b52f8954f4e6ebf72fa")
(setf (get knowledge_msgs::GetPredefinedQuestionsResponse :datatype-) "knowledge_msgs/GetPredefinedQuestionsResponse")
(setf (get knowledge_msgs::GetPredefinedQuestionsResponse :definition-)
      "---
MapPredefinedQuestions[] predefinedQuestions


================================================================================
MSG: knowledge_msgs/MapPredefinedQuestions
string question
string answer
")



(provide :knowledge_msgs/GetPredefinedQuestions "68d94395b4ec7b52f8954f4e6ebf72fa")


