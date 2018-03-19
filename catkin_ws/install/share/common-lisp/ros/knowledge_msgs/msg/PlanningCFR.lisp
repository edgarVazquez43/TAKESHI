; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-msg)


;//! \htmlinclude PlanningCFR.msg.html

(cl:defclass <PlanningCFR> (roslisp-msg-protocol:ros-message)
  ((command
    :reader command
    :initarg :command
    :type cl:string
    :initform "")
   (params
    :reader params
    :initarg :params
    :type (cl:vector knowledge_msgs-msg:CFRParams)
   :initform (cl:make-array 0 :element-type 'knowledge_msgs-msg:CFRParams :initial-element (cl:make-instance 'knowledge_msgs-msg:CFRParams))))
)

(cl:defclass PlanningCFR (<PlanningCFR>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PlanningCFR>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PlanningCFR)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-msg:<PlanningCFR> is deprecated: use knowledge_msgs-msg:PlanningCFR instead.")))

(cl:ensure-generic-function 'command-val :lambda-list '(m))
(cl:defmethod command-val ((m <PlanningCFR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:command-val is deprecated.  Use knowledge_msgs-msg:command instead.")
  (command m))

(cl:ensure-generic-function 'params-val :lambda-list '(m))
(cl:defmethod params-val ((m <PlanningCFR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:params-val is deprecated.  Use knowledge_msgs-msg:params instead.")
  (params m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PlanningCFR>) ostream)
  "Serializes a message object of type '<PlanningCFR>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'command))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'command))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'params))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'params))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PlanningCFR>) istream)
  "Deserializes a message object of type '<PlanningCFR>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'command) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'command) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'params) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'params)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'knowledge_msgs-msg:CFRParams))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PlanningCFR>)))
  "Returns string type for a message object of type '<PlanningCFR>"
  "knowledge_msgs/PlanningCFR")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PlanningCFR)))
  "Returns string type for a message object of type 'PlanningCFR"
  "knowledge_msgs/PlanningCFR")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PlanningCFR>)))
  "Returns md5sum for a message object of type '<PlanningCFR>"
  "1bda369640b5ce77a1917aec327930a1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PlanningCFR)))
  "Returns md5sum for a message object of type 'PlanningCFR"
  "1bda369640b5ce77a1917aec327930a1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PlanningCFR>)))
  "Returns full string definition for message of type '<PlanningCFR>"
  (cl:format cl:nil "string command~%CFRParams[] params~%~%================================================================================~%MSG: knowledge_msgs/CFRParams~%string frame_id~%string frame_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PlanningCFR)))
  "Returns full string definition for message of type 'PlanningCFR"
  (cl:format cl:nil "string command~%CFRParams[] params~%~%================================================================================~%MSG: knowledge_msgs/CFRParams~%string frame_id~%string frame_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PlanningCFR>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'command))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'params) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PlanningCFR>))
  "Converts a ROS message object to a list"
  (cl:list 'PlanningCFR
    (cl:cons ':command (command msg))
    (cl:cons ':params (params msg))
))
