;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::PlanningCmdClips)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'PlanningCmdClips (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::PLANNINGCMDCLIPS")
  (make-package "KNOWLEDGE_MSGS::PLANNINGCMDCLIPS"))

(in-package "ROS")
;;//! \htmlinclude PlanningCmdClips.msg.html


(defclass knowledge_msgs::PlanningCmdClips
  :super ros::object
  :slots (_name _params _id _successful ))

(defmethod knowledge_msgs::PlanningCmdClips
  (:init
   (&key
    ((:name __name) "")
    ((:params __params) "")
    ((:id __id) 0)
    ((:successful __successful) 0)
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _params (string __params))
   (setq _id (round __id))
   (setq _successful (round __successful))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:params
   (&optional __params)
   (if __params (setq _params __params)) _params)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:successful
   (&optional __successful)
   (if __successful (setq _successful __successful)) _successful)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; string _params
    4 (length _params)
    ;; int32 _id
    4
    ;; int32 _successful
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; string _params
       (write-long (length _params) s) (princ _params s)
     ;; int32 _id
       (write-long _id s)
     ;; int32 _successful
       (write-long _successful s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _params
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _params (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _successful
     (setq _successful (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get knowledge_msgs::PlanningCmdClips :md5sum-) "74450e6e60135cf7d80c9acedebf851b")
(setf (get knowledge_msgs::PlanningCmdClips :datatype-) "knowledge_msgs/PlanningCmdClips")
(setf (get knowledge_msgs::PlanningCmdClips :definition-)
      "string name
string params
int32 id
int32 successful
")



(provide :knowledge_msgs/PlanningCmdClips "74450e6e60135cf7d80c9acedebf851b")


