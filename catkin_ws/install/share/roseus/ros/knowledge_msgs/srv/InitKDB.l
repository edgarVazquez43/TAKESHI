;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::InitKDB)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'InitKDB (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::INITKDB")
  (make-package "KNOWLEDGE_MSGS::INITKDB"))
(unless (find-package "KNOWLEDGE_MSGS::INITKDBREQUEST")
  (make-package "KNOWLEDGE_MSGS::INITKDBREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::INITKDBRESPONSE")
  (make-package "KNOWLEDGE_MSGS::INITKDBRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::InitKDBRequest
  :super ros::object
  :slots (_filePath _run ))

(defmethod knowledge_msgs::InitKDBRequest
  (:init
   (&key
    ((:filePath __filePath) "")
    ((:run __run) nil)
    )
   (send-super :init)
   (setq _filePath (string __filePath))
   (setq _run __run)
   self)
  (:filePath
   (&optional __filePath)
   (if __filePath (setq _filePath __filePath)) _filePath)
  (:run
   (&optional __run)
   (if __run (setq _run __run)) _run)
  (:serialization-length
   ()
   (+
    ;; string _filePath
    4 (length _filePath)
    ;; bool _run
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _filePath
       (write-long (length _filePath) s) (princ _filePath s)
     ;; bool _run
       (if _run (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _filePath
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _filePath (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; bool _run
     (setq _run (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass knowledge_msgs::InitKDBResponse
  :super ros::object
  :slots ())

(defmethod knowledge_msgs::InitKDBResponse
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

(defclass knowledge_msgs::InitKDB
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::InitKDB :md5sum-) "7d40ee22877bfab4f2e1de8cb2e7b970")
(setf (get knowledge_msgs::InitKDB :datatype-) "knowledge_msgs/InitKDB")
(setf (get knowledge_msgs::InitKDB :request) knowledge_msgs::InitKDBRequest)
(setf (get knowledge_msgs::InitKDB :response) knowledge_msgs::InitKDBResponse)

(defmethod knowledge_msgs::InitKDBRequest
  (:response () (instance knowledge_msgs::InitKDBResponse :init)))

(setf (get knowledge_msgs::InitKDBRequest :md5sum-) "7d40ee22877bfab4f2e1de8cb2e7b970")
(setf (get knowledge_msgs::InitKDBRequest :datatype-) "knowledge_msgs/InitKDBRequest")
(setf (get knowledge_msgs::InitKDBRequest :definition-)
      "string filePath
bool run
---

")

(setf (get knowledge_msgs::InitKDBResponse :md5sum-) "7d40ee22877bfab4f2e1de8cb2e7b970")
(setf (get knowledge_msgs::InitKDBResponse :datatype-) "knowledge_msgs/InitKDBResponse")
(setf (get knowledge_msgs::InitKDBResponse :definition-)
      "string filePath
bool run
---

")



(provide :knowledge_msgs/InitKDB "7d40ee22877bfab4f2e1de8cb2e7b970")


