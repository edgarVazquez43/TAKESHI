; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude wait_for_switch-request.msg.html

(cl:defclass <wait_for_switch-request> (roslisp-msg-protocol:ros-message)
  ((repeat_sentence
    :reader repeat_sentence
    :initarg :repeat_sentence
    :type knowledge_msgs-msg:RepeatedSentence
    :initform (cl:make-instance 'knowledge_msgs-msg:RepeatedSentence))
   (timeout
    :reader timeout
    :initarg :timeout
    :type cl:integer
    :initform 0))
)

(cl:defclass wait_for_switch-request (<wait_for_switch-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <wait_for_switch-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'wait_for_switch-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<wait_for_switch-request> is deprecated: use knowledge_msgs-srv:wait_for_switch-request instead.")))

(cl:ensure-generic-function 'repeat_sentence-val :lambda-list '(m))
(cl:defmethod repeat_sentence-val ((m <wait_for_switch-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:repeat_sentence-val is deprecated.  Use knowledge_msgs-srv:repeat_sentence instead.")
  (repeat_sentence m))

(cl:ensure-generic-function 'timeout-val :lambda-list '(m))
(cl:defmethod timeout-val ((m <wait_for_switch-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:timeout-val is deprecated.  Use knowledge_msgs-srv:timeout instead.")
  (timeout m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <wait_for_switch-request>) ostream)
  "Serializes a message object of type '<wait_for_switch-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'repeat_sentence) ostream)
  (cl:let* ((signed (cl:slot-value msg 'timeout)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <wait_for_switch-request>) istream)
  "Deserializes a message object of type '<wait_for_switch-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'repeat_sentence) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'timeout) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<wait_for_switch-request>)))
  "Returns string type for a service object of type '<wait_for_switch-request>"
  "knowledge_msgs/wait_for_switchRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_switch-request)))
  "Returns string type for a service object of type 'wait_for_switch-request"
  "knowledge_msgs/wait_for_switchRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<wait_for_switch-request>)))
  "Returns md5sum for a message object of type '<wait_for_switch-request>"
  "de6659e2a24efa10fd97e00db2c838ff")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'wait_for_switch-request)))
  "Returns md5sum for a message object of type 'wait_for_switch-request"
  "de6659e2a24efa10fd97e00db2c838ff")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<wait_for_switch-request>)))
  "Returns full string definition for message of type '<wait_for_switch-request>"
  (cl:format cl:nil "RepeatedSentence repeat_sentence~%int32 timeout~%~%================================================================================~%MSG: knowledge_msgs/RepeatedSentence~%string sentence~%int32 repeat_time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'wait_for_switch-request)))
  "Returns full string definition for message of type 'wait_for_switch-request"
  (cl:format cl:nil "RepeatedSentence repeat_sentence~%int32 timeout~%~%================================================================================~%MSG: knowledge_msgs/RepeatedSentence~%string sentence~%int32 repeat_time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <wait_for_switch-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'repeat_sentence))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <wait_for_switch-request>))
  "Converts a ROS message object to a list"
  (cl:list 'wait_for_switch-request
    (cl:cons ':repeat_sentence (repeat_sentence msg))
    (cl:cons ':timeout (timeout msg))
))
;//! \htmlinclude wait_for_switch-response.msg.html

(cl:defclass <wait_for_switch-response> (roslisp-msg-protocol:ros-message)
  ((goal
    :reader goal
    :initarg :goal
    :type cl:string
    :initform "")
   (command_received
    :reader command_received
    :initarg :command_received
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass wait_for_switch-response (<wait_for_switch-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <wait_for_switch-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'wait_for_switch-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<wait_for_switch-response> is deprecated: use knowledge_msgs-srv:wait_for_switch-response instead.")))

(cl:ensure-generic-function 'goal-val :lambda-list '(m))
(cl:defmethod goal-val ((m <wait_for_switch-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:goal-val is deprecated.  Use knowledge_msgs-srv:goal instead.")
  (goal m))

(cl:ensure-generic-function 'command_received-val :lambda-list '(m))
(cl:defmethod command_received-val ((m <wait_for_switch-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:command_received-val is deprecated.  Use knowledge_msgs-srv:command_received instead.")
  (command_received m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <wait_for_switch-response>) ostream)
  "Serializes a message object of type '<wait_for_switch-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'goal))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'goal))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'command_received) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <wait_for_switch-response>) istream)
  "Deserializes a message object of type '<wait_for_switch-response>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'goal) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'goal) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:slot-value msg 'command_received) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<wait_for_switch-response>)))
  "Returns string type for a service object of type '<wait_for_switch-response>"
  "knowledge_msgs/wait_for_switchResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_switch-response)))
  "Returns string type for a service object of type 'wait_for_switch-response"
  "knowledge_msgs/wait_for_switchResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<wait_for_switch-response>)))
  "Returns md5sum for a message object of type '<wait_for_switch-response>"
  "de6659e2a24efa10fd97e00db2c838ff")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'wait_for_switch-response)))
  "Returns md5sum for a message object of type 'wait_for_switch-response"
  "de6659e2a24efa10fd97e00db2c838ff")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<wait_for_switch-response>)))
  "Returns full string definition for message of type '<wait_for_switch-response>"
  (cl:format cl:nil "string goal~%bool command_received~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'wait_for_switch-response)))
  "Returns full string definition for message of type 'wait_for_switch-response"
  (cl:format cl:nil "string goal~%bool command_received~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <wait_for_switch-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'goal))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <wait_for_switch-response>))
  "Converts a ROS message object to a list"
  (cl:list 'wait_for_switch-response
    (cl:cons ':goal (goal msg))
    (cl:cons ':command_received (command_received msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'wait_for_switch)))
  'wait_for_switch-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'wait_for_switch)))
  'wait_for_switch-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_switch)))
  "Returns string type for a service object of type '<wait_for_switch>"
  "knowledge_msgs/wait_for_switch")