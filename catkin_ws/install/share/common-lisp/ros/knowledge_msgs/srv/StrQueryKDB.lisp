; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude StrQueryKDB-request.msg.html

(cl:defclass <StrQueryKDB-request> (roslisp-msg-protocol:ros-message)
  ((query
    :reader query
    :initarg :query
    :type cl:string
    :initform ""))
)

(cl:defclass StrQueryKDB-request (<StrQueryKDB-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StrQueryKDB-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StrQueryKDB-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<StrQueryKDB-request> is deprecated: use knowledge_msgs-srv:StrQueryKDB-request instead.")))

(cl:ensure-generic-function 'query-val :lambda-list '(m))
(cl:defmethod query-val ((m <StrQueryKDB-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:query-val is deprecated.  Use knowledge_msgs-srv:query instead.")
  (query m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StrQueryKDB-request>) ostream)
  "Serializes a message object of type '<StrQueryKDB-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'query))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'query))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StrQueryKDB-request>) istream)
  "Deserializes a message object of type '<StrQueryKDB-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'query) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'query) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StrQueryKDB-request>)))
  "Returns string type for a service object of type '<StrQueryKDB-request>"
  "knowledge_msgs/StrQueryKDBRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StrQueryKDB-request)))
  "Returns string type for a service object of type 'StrQueryKDB-request"
  "knowledge_msgs/StrQueryKDBRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StrQueryKDB-request>)))
  "Returns md5sum for a message object of type '<StrQueryKDB-request>"
  "40ece397ad679f27203bff340007bd45")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StrQueryKDB-request)))
  "Returns md5sum for a message object of type 'StrQueryKDB-request"
  "40ece397ad679f27203bff340007bd45")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StrQueryKDB-request>)))
  "Returns full string definition for message of type '<StrQueryKDB-request>"
  (cl:format cl:nil "string query~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StrQueryKDB-request)))
  "Returns full string definition for message of type 'StrQueryKDB-request"
  (cl:format cl:nil "string query~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StrQueryKDB-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'query))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StrQueryKDB-request>))
  "Converts a ROS message object to a list"
  (cl:list 'StrQueryKDB-request
    (cl:cons ':query (query msg))
))
;//! \htmlinclude StrQueryKDB-response.msg.html

(cl:defclass <StrQueryKDB-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:string
    :initform ""))
)

(cl:defclass StrQueryKDB-response (<StrQueryKDB-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StrQueryKDB-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StrQueryKDB-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<StrQueryKDB-response> is deprecated: use knowledge_msgs-srv:StrQueryKDB-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <StrQueryKDB-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:result-val is deprecated.  Use knowledge_msgs-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StrQueryKDB-response>) ostream)
  "Serializes a message object of type '<StrQueryKDB-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'result))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'result))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StrQueryKDB-response>) istream)
  "Deserializes a message object of type '<StrQueryKDB-response>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'result) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'result) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StrQueryKDB-response>)))
  "Returns string type for a service object of type '<StrQueryKDB-response>"
  "knowledge_msgs/StrQueryKDBResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StrQueryKDB-response)))
  "Returns string type for a service object of type 'StrQueryKDB-response"
  "knowledge_msgs/StrQueryKDBResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StrQueryKDB-response>)))
  "Returns md5sum for a message object of type '<StrQueryKDB-response>"
  "40ece397ad679f27203bff340007bd45")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StrQueryKDB-response)))
  "Returns md5sum for a message object of type 'StrQueryKDB-response"
  "40ece397ad679f27203bff340007bd45")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StrQueryKDB-response>)))
  "Returns full string definition for message of type '<StrQueryKDB-response>"
  (cl:format cl:nil "string result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StrQueryKDB-response)))
  "Returns full string definition for message of type 'StrQueryKDB-response"
  (cl:format cl:nil "string result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StrQueryKDB-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'result))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StrQueryKDB-response>))
  "Converts a ROS message object to a list"
  (cl:list 'StrQueryKDB-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'StrQueryKDB)))
  'StrQueryKDB-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'StrQueryKDB)))
  'StrQueryKDB-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StrQueryKDB)))
  "Returns string type for a service object of type '<StrQueryKDB>"
  "knowledge_msgs/StrQueryKDB")