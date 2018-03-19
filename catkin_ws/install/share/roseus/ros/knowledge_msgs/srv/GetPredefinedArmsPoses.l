;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::GetPredefinedArmsPoses)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'GetPredefinedArmsPoses (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::GETPREDEFINEDARMSPOSES")
  (make-package "KNOWLEDGE_MSGS::GETPREDEFINEDARMSPOSES"))
(unless (find-package "KNOWLEDGE_MSGS::GETPREDEFINEDARMSPOSESREQUEST")
  (make-package "KNOWLEDGE_MSGS::GETPREDEFINEDARMSPOSESREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::GETPREDEFINEDARMSPOSESRESPONSE")
  (make-package "KNOWLEDGE_MSGS::GETPREDEFINEDARMSPOSESRESPONSE"))

(in-package "ROS")



(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass knowledge_msgs::GetPredefinedArmsPosesRequest
  :super ros::object
  :slots (_name ))

(defmethod knowledge_msgs::GetPredefinedArmsPosesRequest
  (:init
   (&key
    ((:name __name) "")
    )
   (send-super :init)
   (setq _name (string __name))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass knowledge_msgs::GetPredefinedArmsPosesResponse
  :super ros::object
  :slots (_angles ))

(defmethod knowledge_msgs::GetPredefinedArmsPosesResponse
  (:init
   (&key
    ((:angles __angles) (let (r) (dotimes (i 0) (push (instance std_msgs::Float32 :init) r)) r))
    )
   (send-super :init)
   (setq _angles __angles)
   self)
  (:angles
   (&rest __angles)
   (if (keywordp (car __angles))
       (send* _angles __angles)
     (progn
       (if __angles (setq _angles (car __angles)))
       _angles)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Float32[] _angles
    (apply #'+ (send-all _angles :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Float32[] _angles
     (write-long (length _angles) s)
     (dolist (elem _angles)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Float32[] _angles
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _angles (let (r) (dotimes (i n) (push (instance std_msgs::Float32 :init) r)) r))
     (dolist (elem- _angles)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass knowledge_msgs::GetPredefinedArmsPoses
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::GetPredefinedArmsPoses :md5sum-) "5f93696d26db52709ee264c439d53838")
(setf (get knowledge_msgs::GetPredefinedArmsPoses :datatype-) "knowledge_msgs/GetPredefinedArmsPoses")
(setf (get knowledge_msgs::GetPredefinedArmsPoses :request) knowledge_msgs::GetPredefinedArmsPosesRequest)
(setf (get knowledge_msgs::GetPredefinedArmsPoses :response) knowledge_msgs::GetPredefinedArmsPosesResponse)

(defmethod knowledge_msgs::GetPredefinedArmsPosesRequest
  (:response () (instance knowledge_msgs::GetPredefinedArmsPosesResponse :init)))

(setf (get knowledge_msgs::GetPredefinedArmsPosesRequest :md5sum-) "5f93696d26db52709ee264c439d53838")
(setf (get knowledge_msgs::GetPredefinedArmsPosesRequest :datatype-) "knowledge_msgs/GetPredefinedArmsPosesRequest")
(setf (get knowledge_msgs::GetPredefinedArmsPosesRequest :definition-)
      "string name
---
std_msgs/Float32[] angles


================================================================================
MSG: std_msgs/Float32
")

(setf (get knowledge_msgs::GetPredefinedArmsPosesResponse :md5sum-) "5f93696d26db52709ee264c439d53838")
(setf (get knowledge_msgs::GetPredefinedArmsPosesResponse :datatype-) "knowledge_msgs/GetPredefinedArmsPosesResponse")
(setf (get knowledge_msgs::GetPredefinedArmsPosesResponse :definition-)
      "string name
---
std_msgs/Float32[] angles


================================================================================
MSG: std_msgs/Float32
")



(provide :knowledge_msgs/GetPredefinedArmsPoses "5f93696d26db52709ee264c439d53838")


