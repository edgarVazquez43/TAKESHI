; Auto-generated. Do not edit!


(cl:in-package bbros_bridge-srv)


;//! \htmlinclude Default_ROS_BB_Bridge-request.msg.html

(cl:defclass <Default_ROS_BB_Bridge-request> (roslisp-msg-protocol:ros-message)
  ((parameters
    :reader parameters
    :initarg :parameters
    :type cl:string
    :initform "")
   (timeout
    :reader timeout
    :initarg :timeout
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Default_ROS_BB_Bridge-request (<Default_ROS_BB_Bridge-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Default_ROS_BB_Bridge-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Default_ROS_BB_Bridge-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<Default_ROS_BB_Bridge-request> is deprecated: use bbros_bridge-srv:Default_ROS_BB_Bridge-request instead.")))

(cl:ensure-generic-function 'parameters-val :lambda-list '(m))
(cl:defmethod parameters-val ((m <Default_ROS_BB_Bridge-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:parameters-val is deprecated.  Use bbros_bridge-srv:parameters instead.")
  (parameters m))

(cl:ensure-generic-function 'timeout-val :lambda-list '(m))
(cl:defmethod timeout-val ((m <Default_ROS_BB_Bridge-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:timeout-val is deprecated.  Use bbros_bridge-srv:timeout instead.")
  (timeout m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Default_ROS_BB_Bridge-request>) ostream)
  "Serializes a message object of type '<Default_ROS_BB_Bridge-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'parameters))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'parameters))
  (cl:let* ((signed (cl:slot-value msg 'timeout)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Default_ROS_BB_Bridge-request>) istream)
  "Deserializes a message object of type '<Default_ROS_BB_Bridge-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'parameters) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'parameters) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'timeout) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Default_ROS_BB_Bridge-request>)))
  "Returns string type for a service object of type '<Default_ROS_BB_Bridge-request>"
  "bbros_bridge/Default_ROS_BB_BridgeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Default_ROS_BB_Bridge-request)))
  "Returns string type for a service object of type 'Default_ROS_BB_Bridge-request"
  "bbros_bridge/Default_ROS_BB_BridgeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Default_ROS_BB_Bridge-request>)))
  "Returns md5sum for a message object of type '<Default_ROS_BB_Bridge-request>"
  "dc72b6691678f98c1cd8b4c963031bd5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Default_ROS_BB_Bridge-request)))
  "Returns md5sum for a message object of type 'Default_ROS_BB_Bridge-request"
  "dc72b6691678f98c1cd8b4c963031bd5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Default_ROS_BB_Bridge-request>)))
  "Returns full string definition for message of type '<Default_ROS_BB_Bridge-request>"
  (cl:format cl:nil "string parameters~%int16 timeout~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Default_ROS_BB_Bridge-request)))
  "Returns full string definition for message of type 'Default_ROS_BB_Bridge-request"
  (cl:format cl:nil "string parameters~%int16 timeout~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Default_ROS_BB_Bridge-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'parameters))
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Default_ROS_BB_Bridge-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Default_ROS_BB_Bridge-request
    (cl:cons ':parameters (parameters msg))
    (cl:cons ':timeout (timeout msg))
))
;//! \htmlinclude Default_ROS_BB_Bridge-response.msg.html

(cl:defclass <Default_ROS_BB_Bridge-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (response
    :reader response
    :initarg :response
    :type cl:string
    :initform ""))
)

(cl:defclass Default_ROS_BB_Bridge-response (<Default_ROS_BB_Bridge-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Default_ROS_BB_Bridge-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Default_ROS_BB_Bridge-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<Default_ROS_BB_Bridge-response> is deprecated: use bbros_bridge-srv:Default_ROS_BB_Bridge-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <Default_ROS_BB_Bridge-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:success-val is deprecated.  Use bbros_bridge-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'response-val :lambda-list '(m))
(cl:defmethod response-val ((m <Default_ROS_BB_Bridge-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:response-val is deprecated.  Use bbros_bridge-srv:response instead.")
  (response m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Default_ROS_BB_Bridge-response>) ostream)
  "Serializes a message object of type '<Default_ROS_BB_Bridge-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'response))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'response))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Default_ROS_BB_Bridge-response>) istream)
  "Deserializes a message object of type '<Default_ROS_BB_Bridge-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'response) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'response) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Default_ROS_BB_Bridge-response>)))
  "Returns string type for a service object of type '<Default_ROS_BB_Bridge-response>"
  "bbros_bridge/Default_ROS_BB_BridgeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Default_ROS_BB_Bridge-response)))
  "Returns string type for a service object of type 'Default_ROS_BB_Bridge-response"
  "bbros_bridge/Default_ROS_BB_BridgeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Default_ROS_BB_Bridge-response>)))
  "Returns md5sum for a message object of type '<Default_ROS_BB_Bridge-response>"
  "dc72b6691678f98c1cd8b4c963031bd5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Default_ROS_BB_Bridge-response)))
  "Returns md5sum for a message object of type 'Default_ROS_BB_Bridge-response"
  "dc72b6691678f98c1cd8b4c963031bd5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Default_ROS_BB_Bridge-response>)))
  "Returns full string definition for message of type '<Default_ROS_BB_Bridge-response>"
  (cl:format cl:nil "bool success~%string response~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Default_ROS_BB_Bridge-response)))
  "Returns full string definition for message of type 'Default_ROS_BB_Bridge-response"
  (cl:format cl:nil "bool success~%string response~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Default_ROS_BB_Bridge-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'response))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Default_ROS_BB_Bridge-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Default_ROS_BB_Bridge-response
    (cl:cons ':success (success msg))
    (cl:cons ':response (response msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Default_ROS_BB_Bridge)))
  'Default_ROS_BB_Bridge-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Default_ROS_BB_Bridge)))
  'Default_ROS_BB_Bridge-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Default_ROS_BB_Bridge)))
  "Returns string type for a service object of type '<Default_ROS_BB_Bridge>"
  "bbros_bridge/Default_ROS_BB_Bridge")