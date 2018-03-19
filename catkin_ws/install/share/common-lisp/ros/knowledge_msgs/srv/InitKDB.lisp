; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude InitKDB-request.msg.html

(cl:defclass <InitKDB-request> (roslisp-msg-protocol:ros-message)
  ((filePath
    :reader filePath
    :initarg :filePath
    :type cl:string
    :initform "")
   (run
    :reader run
    :initarg :run
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass InitKDB-request (<InitKDB-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InitKDB-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InitKDB-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<InitKDB-request> is deprecated: use knowledge_msgs-srv:InitKDB-request instead.")))

(cl:ensure-generic-function 'filePath-val :lambda-list '(m))
(cl:defmethod filePath-val ((m <InitKDB-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:filePath-val is deprecated.  Use knowledge_msgs-srv:filePath instead.")
  (filePath m))

(cl:ensure-generic-function 'run-val :lambda-list '(m))
(cl:defmethod run-val ((m <InitKDB-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:run-val is deprecated.  Use knowledge_msgs-srv:run instead.")
  (run m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InitKDB-request>) ostream)
  "Serializes a message object of type '<InitKDB-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'filePath))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'filePath))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'run) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InitKDB-request>) istream)
  "Deserializes a message object of type '<InitKDB-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'filePath) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'filePath) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:slot-value msg 'run) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InitKDB-request>)))
  "Returns string type for a service object of type '<InitKDB-request>"
  "knowledge_msgs/InitKDBRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitKDB-request)))
  "Returns string type for a service object of type 'InitKDB-request"
  "knowledge_msgs/InitKDBRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InitKDB-request>)))
  "Returns md5sum for a message object of type '<InitKDB-request>"
  "7d40ee22877bfab4f2e1de8cb2e7b970")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InitKDB-request)))
  "Returns md5sum for a message object of type 'InitKDB-request"
  "7d40ee22877bfab4f2e1de8cb2e7b970")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InitKDB-request>)))
  "Returns full string definition for message of type '<InitKDB-request>"
  (cl:format cl:nil "string filePath~%bool run~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InitKDB-request)))
  "Returns full string definition for message of type 'InitKDB-request"
  (cl:format cl:nil "string filePath~%bool run~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InitKDB-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'filePath))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InitKDB-request>))
  "Converts a ROS message object to a list"
  (cl:list 'InitKDB-request
    (cl:cons ':filePath (filePath msg))
    (cl:cons ':run (run msg))
))
;//! \htmlinclude InitKDB-response.msg.html

(cl:defclass <InitKDB-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass InitKDB-response (<InitKDB-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InitKDB-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InitKDB-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<InitKDB-response> is deprecated: use knowledge_msgs-srv:InitKDB-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InitKDB-response>) ostream)
  "Serializes a message object of type '<InitKDB-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InitKDB-response>) istream)
  "Deserializes a message object of type '<InitKDB-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InitKDB-response>)))
  "Returns string type for a service object of type '<InitKDB-response>"
  "knowledge_msgs/InitKDBResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitKDB-response)))
  "Returns string type for a service object of type 'InitKDB-response"
  "knowledge_msgs/InitKDBResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InitKDB-response>)))
  "Returns md5sum for a message object of type '<InitKDB-response>"
  "7d40ee22877bfab4f2e1de8cb2e7b970")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InitKDB-response)))
  "Returns md5sum for a message object of type 'InitKDB-response"
  "7d40ee22877bfab4f2e1de8cb2e7b970")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InitKDB-response>)))
  "Returns full string definition for message of type '<InitKDB-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InitKDB-response)))
  "Returns full string definition for message of type 'InitKDB-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InitKDB-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InitKDB-response>))
  "Converts a ROS message object to a list"
  (cl:list 'InitKDB-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'InitKDB)))
  'InitKDB-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'InitKDB)))
  'InitKDB-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitKDB)))
  "Returns string type for a service object of type '<InitKDB>"
  "knowledge_msgs/InitKDB")