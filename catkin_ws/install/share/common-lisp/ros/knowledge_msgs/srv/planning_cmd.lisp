; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude planning_cmd-request.msg.html

(cl:defclass <planning_cmd-request> (roslisp-msg-protocol:ros-message)
  ((params
    :reader params
    :initarg :params
    :type cl:string
    :initform "")
   (name
    :reader name
    :initarg :name
    :type cl:string
    :initform ""))
)

(cl:defclass planning_cmd-request (<planning_cmd-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <planning_cmd-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'planning_cmd-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<planning_cmd-request> is deprecated: use knowledge_msgs-srv:planning_cmd-request instead.")))

(cl:ensure-generic-function 'params-val :lambda-list '(m))
(cl:defmethod params-val ((m <planning_cmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:params-val is deprecated.  Use knowledge_msgs-srv:params instead.")
  (params m))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <planning_cmd-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:name-val is deprecated.  Use knowledge_msgs-srv:name instead.")
  (name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <planning_cmd-request>) ostream)
  "Serializes a message object of type '<planning_cmd-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'params))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'params))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <planning_cmd-request>) istream)
  "Deserializes a message object of type '<planning_cmd-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'params) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'params) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<planning_cmd-request>)))
  "Returns string type for a service object of type '<planning_cmd-request>"
  "knowledge_msgs/planning_cmdRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'planning_cmd-request)))
  "Returns string type for a service object of type 'planning_cmd-request"
  "knowledge_msgs/planning_cmdRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<planning_cmd-request>)))
  "Returns md5sum for a message object of type '<planning_cmd-request>"
  "f9f6635257061aef8bea97260f4e6a8b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'planning_cmd-request)))
  "Returns md5sum for a message object of type 'planning_cmd-request"
  "f9f6635257061aef8bea97260f4e6a8b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<planning_cmd-request>)))
  "Returns full string definition for message of type '<planning_cmd-request>"
  (cl:format cl:nil "string params~%string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'planning_cmd-request)))
  "Returns full string definition for message of type 'planning_cmd-request"
  (cl:format cl:nil "string params~%string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <planning_cmd-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'params))
     4 (cl:length (cl:slot-value msg 'name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <planning_cmd-request>))
  "Converts a ROS message object to a list"
  (cl:list 'planning_cmd-request
    (cl:cons ':params (params msg))
    (cl:cons ':name (name msg))
))
;//! \htmlinclude planning_cmd-response.msg.html

(cl:defclass <planning_cmd-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (args
    :reader args
    :initarg :args
    :type cl:string
    :initform ""))
)

(cl:defclass planning_cmd-response (<planning_cmd-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <planning_cmd-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'planning_cmd-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<planning_cmd-response> is deprecated: use knowledge_msgs-srv:planning_cmd-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <planning_cmd-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:success-val is deprecated.  Use knowledge_msgs-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'args-val :lambda-list '(m))
(cl:defmethod args-val ((m <planning_cmd-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:args-val is deprecated.  Use knowledge_msgs-srv:args instead.")
  (args m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <planning_cmd-response>) ostream)
  "Serializes a message object of type '<planning_cmd-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'args))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'args))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <planning_cmd-response>) istream)
  "Deserializes a message object of type '<planning_cmd-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'args) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'args) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<planning_cmd-response>)))
  "Returns string type for a service object of type '<planning_cmd-response>"
  "knowledge_msgs/planning_cmdResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'planning_cmd-response)))
  "Returns string type for a service object of type 'planning_cmd-response"
  "knowledge_msgs/planning_cmdResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<planning_cmd-response>)))
  "Returns md5sum for a message object of type '<planning_cmd-response>"
  "f9f6635257061aef8bea97260f4e6a8b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'planning_cmd-response)))
  "Returns md5sum for a message object of type 'planning_cmd-response"
  "f9f6635257061aef8bea97260f4e6a8b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<planning_cmd-response>)))
  "Returns full string definition for message of type '<planning_cmd-response>"
  (cl:format cl:nil "bool success~%string args~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'planning_cmd-response)))
  "Returns full string definition for message of type 'planning_cmd-response"
  (cl:format cl:nil "bool success~%string args~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <planning_cmd-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'args))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <planning_cmd-response>))
  "Converts a ROS message object to a list"
  (cl:list 'planning_cmd-response
    (cl:cons ':success (success msg))
    (cl:cons ':args (args msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'planning_cmd)))
  'planning_cmd-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'planning_cmd)))
  'planning_cmd-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'planning_cmd)))
  "Returns string type for a service object of type '<planning_cmd>"
  "knowledge_msgs/planning_cmd")