;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::wait_for_command)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'wait_for_command (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_COMMAND")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_COMMAND"))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_COMMANDREQUEST")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_COMMANDREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::WAIT_FOR_COMMANDRESPONSE")
  (make-package "KNOWLEDGE_MSGS::WAIT_FOR_COMMANDRESPONSE"))

(in-package "ROS")





(defclass knowledge_msgs::wait_for_commandRequest
  :super ros::object
  :slots (_timeout ))

(defmethod knowledge_msgs::wait_for_commandRequest
  (:init
   (&key
    ((:timeout __timeout) 0)
    )
   (send-super :init)
   (setq _timeout (round __timeout))
   self)
  (:timeout
   (&optional __timeout)
   (if __timeout (setq _timeout __timeout)) _timeout)
  (:serialization-length
   ()
   (+
    ;; int32 _timeout
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _timeout
       (write-long _timeout s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _timeout
     (setq _timeout (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass knowledge_msgs::wait_for_commandResponse
  :super ros::object
  :slots (_cfr _command_received ))

(defmethod knowledge_msgs::wait_for_commandResponse
  (:init
   (&key
    ((:cfr __cfr) (instance knowledge_msgs::PlanningCFR :init))
    ((:command_received __command_received) nil)
    )
   (send-super :init)
   (setq _cfr __cfr)
   (setq _command_received __command_received)
   self)
  (:cfr
   (&rest __cfr)
   (if (keywordp (car __cfr))
       (send* _cfr __cfr)
     (progn
       (if __cfr (setq _cfr (car __cfr)))
       _cfr)))
  (:command_received
   (&optional __command_received)
   (if __command_received (setq _command_received __command_received)) _command_received)
  (:serialization-length
   ()
   (+
    ;; knowledge_msgs/PlanningCFR _cfr
    (send _cfr :serialization-length)
    ;; bool _command_received
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; knowledge_msgs/PlanningCFR _cfr
       (send _cfr :serialize s)
     ;; bool _command_received
       (if _command_received (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; knowledge_msgs/PlanningCFR _cfr
     (send _cfr :deserialize buf ptr-) (incf ptr- (send _cfr :serialization-length))
   ;; bool _command_received
     (setq _command_received (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass knowledge_msgs::wait_for_command
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::wait_for_command :md5sum-) "f286b9f490839fee63da1e5ff1e054a7")
(setf (get knowledge_msgs::wait_for_command :datatype-) "knowledge_msgs/wait_for_command")
(setf (get knowledge_msgs::wait_for_command :request) knowledge_msgs::wait_for_commandRequest)
(setf (get knowledge_msgs::wait_for_command :response) knowledge_msgs::wait_for_commandResponse)

(defmethod knowledge_msgs::wait_for_commandRequest
  (:response () (instance knowledge_msgs::wait_for_commandResponse :init)))

(setf (get knowledge_msgs::wait_for_commandRequest :md5sum-) "f286b9f490839fee63da1e5ff1e054a7")
(setf (get knowledge_msgs::wait_for_commandRequest :datatype-) "knowledge_msgs/wait_for_commandRequest")
(setf (get knowledge_msgs::wait_for_commandRequest :definition-)
      "int32 timeout
---
PlanningCFR cfr
bool command_received


================================================================================
MSG: knowledge_msgs/PlanningCFR
string command
CFRParams[] params

================================================================================
MSG: knowledge_msgs/CFRParams
string frame_id
string frame_value
")

(setf (get knowledge_msgs::wait_for_commandResponse :md5sum-) "f286b9f490839fee63da1e5ff1e054a7")
(setf (get knowledge_msgs::wait_for_commandResponse :datatype-) "knowledge_msgs/wait_for_commandResponse")
(setf (get knowledge_msgs::wait_for_commandResponse :definition-)
      "int32 timeout
---
PlanningCFR cfr
bool command_received


================================================================================
MSG: knowledge_msgs/PlanningCFR
string command
CFRParams[] params

================================================================================
MSG: knowledge_msgs/CFRParams
string frame_id
string frame_value
")



(provide :knowledge_msgs/wait_for_command "f286b9f490839fee63da1e5ff1e054a7")


