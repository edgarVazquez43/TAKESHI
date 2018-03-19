;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::parse_sentence_cfr)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'parse_sentence_cfr (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::PARSE_SENTENCE_CFR")
  (make-package "KNOWLEDGE_MSGS::PARSE_SENTENCE_CFR"))
(unless (find-package "KNOWLEDGE_MSGS::PARSE_SENTENCE_CFRREQUEST")
  (make-package "KNOWLEDGE_MSGS::PARSE_SENTENCE_CFRREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::PARSE_SENTENCE_CFRRESPONSE")
  (make-package "KNOWLEDGE_MSGS::PARSE_SENTENCE_CFRRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::parse_sentence_cfrRequest
  :super ros::object
  :slots (_sentence ))

(defmethod knowledge_msgs::parse_sentence_cfrRequest
  (:init
   (&key
    ((:sentence __sentence) "")
    )
   (send-super :init)
   (setq _sentence (string __sentence))
   self)
  (:sentence
   (&optional __sentence)
   (if __sentence (setq _sentence __sentence)) _sentence)
  (:serialization-length
   ()
   (+
    ;; string _sentence
    4 (length _sentence)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _sentence
       (write-long (length _sentence) s) (princ _sentence s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _sentence
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _sentence (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass knowledge_msgs::parse_sentence_cfrResponse
  :super ros::object
  :slots (_cfr ))

(defmethod knowledge_msgs::parse_sentence_cfrResponse
  (:init
   (&key
    ((:cfr __cfr) (instance knowledge_msgs::PlanningCFR :init))
    )
   (send-super :init)
   (setq _cfr __cfr)
   self)
  (:cfr
   (&rest __cfr)
   (if (keywordp (car __cfr))
       (send* _cfr __cfr)
     (progn
       (if __cfr (setq _cfr (car __cfr)))
       _cfr)))
  (:serialization-length
   ()
   (+
    ;; knowledge_msgs/PlanningCFR _cfr
    (send _cfr :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; knowledge_msgs/PlanningCFR _cfr
       (send _cfr :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; knowledge_msgs/PlanningCFR _cfr
     (send _cfr :deserialize buf ptr-) (incf ptr- (send _cfr :serialization-length))
   ;;
   self)
  )

(defclass knowledge_msgs::parse_sentence_cfr
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::parse_sentence_cfr :md5sum-) "953467976fe5830442f3fbb0187ffa3b")
(setf (get knowledge_msgs::parse_sentence_cfr :datatype-) "knowledge_msgs/parse_sentence_cfr")
(setf (get knowledge_msgs::parse_sentence_cfr :request) knowledge_msgs::parse_sentence_cfrRequest)
(setf (get knowledge_msgs::parse_sentence_cfr :response) knowledge_msgs::parse_sentence_cfrResponse)

(defmethod knowledge_msgs::parse_sentence_cfrRequest
  (:response () (instance knowledge_msgs::parse_sentence_cfrResponse :init)))

(setf (get knowledge_msgs::parse_sentence_cfrRequest :md5sum-) "953467976fe5830442f3fbb0187ffa3b")
(setf (get knowledge_msgs::parse_sentence_cfrRequest :datatype-) "knowledge_msgs/parse_sentence_cfrRequest")
(setf (get knowledge_msgs::parse_sentence_cfrRequest :definition-)
      "string sentence
---
PlanningCFR cfr


================================================================================
MSG: knowledge_msgs/PlanningCFR
string command
CFRParams[] params

================================================================================
MSG: knowledge_msgs/CFRParams
string frame_id
string frame_value
")

(setf (get knowledge_msgs::parse_sentence_cfrResponse :md5sum-) "953467976fe5830442f3fbb0187ffa3b")
(setf (get knowledge_msgs::parse_sentence_cfrResponse :datatype-) "knowledge_msgs/parse_sentence_cfrResponse")
(setf (get knowledge_msgs::parse_sentence_cfrResponse :definition-)
      "string sentence
---
PlanningCFR cfr


================================================================================
MSG: knowledge_msgs/PlanningCFR
string command
CFRParams[] params

================================================================================
MSG: knowledge_msgs/CFRParams
string frame_id
string frame_value
")



(provide :knowledge_msgs/parse_sentence_cfr "953467976fe5830442f3fbb0187ffa3b")


