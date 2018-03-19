; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude ask_store_name-request.msg.html

(cl:defclass <ask_store_name-request> (roslisp-msg-protocol:ros-message)
  ((attempt_timeout
    :reader attempt_timeout
    :initarg :attempt_timeout
    :type cl:integer
    :initform 0)
   (repeat_timeout
    :reader repeat_timeout
    :initarg :repeat_timeout
    :type cl:integer
    :initform 0)
   (max_attempts
    :reader max_attempts
    :initarg :max_attempts
    :type cl:integer
    :initform 0))
)

(cl:defclass ask_store_name-request (<ask_store_name-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ask_store_name-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ask_store_name-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<ask_store_name-request> is deprecated: use knowledge_msgs-srv:ask_store_name-request instead.")))

(cl:ensure-generic-function 'attempt_timeout-val :lambda-list '(m))
(cl:defmethod attempt_timeout-val ((m <ask_store_name-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:attempt_timeout-val is deprecated.  Use knowledge_msgs-srv:attempt_timeout instead.")
  (attempt_timeout m))

(cl:ensure-generic-function 'repeat_timeout-val :lambda-list '(m))
(cl:defmethod repeat_timeout-val ((m <ask_store_name-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:repeat_timeout-val is deprecated.  Use knowledge_msgs-srv:repeat_timeout instead.")
  (repeat_timeout m))

(cl:ensure-generic-function 'max_attempts-val :lambda-list '(m))
(cl:defmethod max_attempts-val ((m <ask_store_name-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:max_attempts-val is deprecated.  Use knowledge_msgs-srv:max_attempts instead.")
  (max_attempts m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ask_store_name-request>) ostream)
  "Serializes a message object of type '<ask_store_name-request>"
  (cl:let* ((signed (cl:slot-value msg 'attempt_timeout)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'repeat_timeout)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'max_attempts)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ask_store_name-request>) istream)
  "Deserializes a message object of type '<ask_store_name-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'attempt_timeout) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'repeat_timeout) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'max_attempts) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ask_store_name-request>)))
  "Returns string type for a service object of type '<ask_store_name-request>"
  "knowledge_msgs/ask_store_nameRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ask_store_name-request)))
  "Returns string type for a service object of type 'ask_store_name-request"
  "knowledge_msgs/ask_store_nameRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ask_store_name-request>)))
  "Returns md5sum for a message object of type '<ask_store_name-request>"
  "8a5870e234d40e3af46fc0ab4649d821")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ask_store_name-request)))
  "Returns md5sum for a message object of type 'ask_store_name-request"
  "8a5870e234d40e3af46fc0ab4649d821")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ask_store_name-request>)))
  "Returns full string definition for message of type '<ask_store_name-request>"
  (cl:format cl:nil "int32 attempt_timeout~%int32 repeat_timeout~%int32 max_attempts~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ask_store_name-request)))
  "Returns full string definition for message of type 'ask_store_name-request"
  (cl:format cl:nil "int32 attempt_timeout~%int32 repeat_timeout~%int32 max_attempts~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ask_store_name-request>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ask_store_name-request>))
  "Converts a ROS message object to a list"
  (cl:list 'ask_store_name-request
    (cl:cons ':attempt_timeout (attempt_timeout msg))
    (cl:cons ':repeat_timeout (repeat_timeout msg))
    (cl:cons ':max_attempts (max_attempts msg))
))
;//! \htmlinclude ask_store_name-response.msg.html

(cl:defclass <ask_store_name-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (stored_name
    :reader stored_name
    :initarg :stored_name
    :type cl:string
    :initform ""))
)

(cl:defclass ask_store_name-response (<ask_store_name-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ask_store_name-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ask_store_name-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<ask_store_name-response> is deprecated: use knowledge_msgs-srv:ask_store_name-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <ask_store_name-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:success-val is deprecated.  Use knowledge_msgs-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'stored_name-val :lambda-list '(m))
(cl:defmethod stored_name-val ((m <ask_store_name-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:stored_name-val is deprecated.  Use knowledge_msgs-srv:stored_name instead.")
  (stored_name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ask_store_name-response>) ostream)
  "Serializes a message object of type '<ask_store_name-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'stored_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'stored_name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ask_store_name-response>) istream)
  "Deserializes a message object of type '<ask_store_name-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stored_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'stored_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ask_store_name-response>)))
  "Returns string type for a service object of type '<ask_store_name-response>"
  "knowledge_msgs/ask_store_nameResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ask_store_name-response)))
  "Returns string type for a service object of type 'ask_store_name-response"
  "knowledge_msgs/ask_store_nameResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ask_store_name-response>)))
  "Returns md5sum for a message object of type '<ask_store_name-response>"
  "8a5870e234d40e3af46fc0ab4649d821")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ask_store_name-response)))
  "Returns md5sum for a message object of type 'ask_store_name-response"
  "8a5870e234d40e3af46fc0ab4649d821")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ask_store_name-response>)))
  "Returns full string definition for message of type '<ask_store_name-response>"
  (cl:format cl:nil "bool success~%string stored_name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ask_store_name-response)))
  "Returns full string definition for message of type 'ask_store_name-response"
  (cl:format cl:nil "bool success~%string stored_name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ask_store_name-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'stored_name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ask_store_name-response>))
  "Converts a ROS message object to a list"
  (cl:list 'ask_store_name-response
    (cl:cons ':success (success msg))
    (cl:cons ':stored_name (stored_name msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'ask_store_name)))
  'ask_store_name-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'ask_store_name)))
  'ask_store_name-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ask_store_name)))
  "Returns string type for a service object of type '<ask_store_name>"
  "knowledge_msgs/ask_store_name")