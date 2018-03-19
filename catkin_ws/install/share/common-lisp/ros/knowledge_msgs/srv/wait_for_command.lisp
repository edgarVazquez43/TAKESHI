; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude wait_for_command-request.msg.html

(cl:defclass <wait_for_command-request> (roslisp-msg-protocol:ros-message)
  ((timeout
    :reader timeout
    :initarg :timeout
    :type cl:integer
    :initform 0))
)

(cl:defclass wait_for_command-request (<wait_for_command-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <wait_for_command-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'wait_for_command-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<wait_for_command-request> is deprecated: use knowledge_msgs-srv:wait_for_command-request instead.")))

(cl:ensure-generic-function 'timeout-val :lambda-list '(m))
(cl:defmethod timeout-val ((m <wait_for_command-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:timeout-val is deprecated.  Use knowledge_msgs-srv:timeout instead.")
  (timeout m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <wait_for_command-request>) ostream)
  "Serializes a message object of type '<wait_for_command-request>"
  (cl:let* ((signed (cl:slot-value msg 'timeout)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <wait_for_command-request>) istream)
  "Deserializes a message object of type '<wait_for_command-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'timeout) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<wait_for_command-request>)))
  "Returns string type for a service object of type '<wait_for_command-request>"
  "knowledge_msgs/wait_for_commandRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_command-request)))
  "Returns string type for a service object of type 'wait_for_command-request"
  "knowledge_msgs/wait_for_commandRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<wait_for_command-request>)))
  "Returns md5sum for a message object of type '<wait_for_command-request>"
  "f286b9f490839fee63da1e5ff1e054a7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'wait_for_command-request)))
  "Returns md5sum for a message object of type 'wait_for_command-request"
  "f286b9f490839fee63da1e5ff1e054a7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<wait_for_command-request>)))
  "Returns full string definition for message of type '<wait_for_command-request>"
  (cl:format cl:nil "int32 timeout~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'wait_for_command-request)))
  "Returns full string definition for message of type 'wait_for_command-request"
  (cl:format cl:nil "int32 timeout~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <wait_for_command-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <wait_for_command-request>))
  "Converts a ROS message object to a list"
  (cl:list 'wait_for_command-request
    (cl:cons ':timeout (timeout msg))
))
;//! \htmlinclude wait_for_command-response.msg.html

(cl:defclass <wait_for_command-response> (roslisp-msg-protocol:ros-message)
  ((cfr
    :reader cfr
    :initarg :cfr
    :type knowledge_msgs-msg:PlanningCFR
    :initform (cl:make-instance 'knowledge_msgs-msg:PlanningCFR))
   (command_received
    :reader command_received
    :initarg :command_received
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass wait_for_command-response (<wait_for_command-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <wait_for_command-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'wait_for_command-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<wait_for_command-response> is deprecated: use knowledge_msgs-srv:wait_for_command-response instead.")))

(cl:ensure-generic-function 'cfr-val :lambda-list '(m))
(cl:defmethod cfr-val ((m <wait_for_command-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:cfr-val is deprecated.  Use knowledge_msgs-srv:cfr instead.")
  (cfr m))

(cl:ensure-generic-function 'command_received-val :lambda-list '(m))
(cl:defmethod command_received-val ((m <wait_for_command-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:command_received-val is deprecated.  Use knowledge_msgs-srv:command_received instead.")
  (command_received m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <wait_for_command-response>) ostream)
  "Serializes a message object of type '<wait_for_command-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cfr) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'command_received) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <wait_for_command-response>) istream)
  "Deserializes a message object of type '<wait_for_command-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cfr) istream)
    (cl:setf (cl:slot-value msg 'command_received) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<wait_for_command-response>)))
  "Returns string type for a service object of type '<wait_for_command-response>"
  "knowledge_msgs/wait_for_commandResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_command-response)))
  "Returns string type for a service object of type 'wait_for_command-response"
  "knowledge_msgs/wait_for_commandResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<wait_for_command-response>)))
  "Returns md5sum for a message object of type '<wait_for_command-response>"
  "f286b9f490839fee63da1e5ff1e054a7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'wait_for_command-response)))
  "Returns md5sum for a message object of type 'wait_for_command-response"
  "f286b9f490839fee63da1e5ff1e054a7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<wait_for_command-response>)))
  "Returns full string definition for message of type '<wait_for_command-response>"
  (cl:format cl:nil "PlanningCFR cfr~%bool command_received~%~%~%================================================================================~%MSG: knowledge_msgs/PlanningCFR~%string command~%CFRParams[] params~%~%================================================================================~%MSG: knowledge_msgs/CFRParams~%string frame_id~%string frame_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'wait_for_command-response)))
  "Returns full string definition for message of type 'wait_for_command-response"
  (cl:format cl:nil "PlanningCFR cfr~%bool command_received~%~%~%================================================================================~%MSG: knowledge_msgs/PlanningCFR~%string command~%CFRParams[] params~%~%================================================================================~%MSG: knowledge_msgs/CFRParams~%string frame_id~%string frame_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <wait_for_command-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cfr))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <wait_for_command-response>))
  "Converts a ROS message object to a list"
  (cl:list 'wait_for_command-response
    (cl:cons ':cfr (cfr msg))
    (cl:cons ':command_received (command_received msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'wait_for_command)))
  'wait_for_command-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'wait_for_command)))
  'wait_for_command-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_command)))
  "Returns string type for a service object of type '<wait_for_command>"
  "knowledge_msgs/wait_for_command")