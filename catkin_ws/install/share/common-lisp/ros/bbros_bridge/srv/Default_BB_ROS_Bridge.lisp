; Auto-generated. Do not edit!


(cl:in-package bbros_bridge-srv)


;//! \htmlinclude Default_BB_ROS_Bridge-request.msg.html

(cl:defclass <Default_BB_ROS_Bridge-request> (roslisp-msg-protocol:ros-message)
  ((params
    :reader params
    :initarg :params
    :type cl:string
    :initform ""))
)

(cl:defclass Default_BB_ROS_Bridge-request (<Default_BB_ROS_Bridge-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Default_BB_ROS_Bridge-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Default_BB_ROS_Bridge-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<Default_BB_ROS_Bridge-request> is deprecated: use bbros_bridge-srv:Default_BB_ROS_Bridge-request instead.")))

(cl:ensure-generic-function 'params-val :lambda-list '(m))
(cl:defmethod params-val ((m <Default_BB_ROS_Bridge-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:params-val is deprecated.  Use bbros_bridge-srv:params instead.")
  (params m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Default_BB_ROS_Bridge-request>) ostream)
  "Serializes a message object of type '<Default_BB_ROS_Bridge-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'params))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'params))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Default_BB_ROS_Bridge-request>) istream)
  "Deserializes a message object of type '<Default_BB_ROS_Bridge-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'params) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'params) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Default_BB_ROS_Bridge-request>)))
  "Returns string type for a service object of type '<Default_BB_ROS_Bridge-request>"
  "bbros_bridge/Default_BB_ROS_BridgeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Default_BB_ROS_Bridge-request)))
  "Returns string type for a service object of type 'Default_BB_ROS_Bridge-request"
  "bbros_bridge/Default_BB_ROS_BridgeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Default_BB_ROS_Bridge-request>)))
  "Returns md5sum for a message object of type '<Default_BB_ROS_Bridge-request>"
  "6162a5d58ec2c814778e9c41c1bf44eb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Default_BB_ROS_Bridge-request)))
  "Returns md5sum for a message object of type 'Default_BB_ROS_Bridge-request"
  "6162a5d58ec2c814778e9c41c1bf44eb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Default_BB_ROS_Bridge-request>)))
  "Returns full string definition for message of type '<Default_BB_ROS_Bridge-request>"
  (cl:format cl:nil "string params~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Default_BB_ROS_Bridge-request)))
  "Returns full string definition for message of type 'Default_BB_ROS_Bridge-request"
  (cl:format cl:nil "string params~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Default_BB_ROS_Bridge-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'params))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Default_BB_ROS_Bridge-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Default_BB_ROS_Bridge-request
    (cl:cons ':params (params msg))
))
;//! \htmlinclude Default_BB_ROS_Bridge-response.msg.html

(cl:defclass <Default_BB_ROS_Bridge-response> (roslisp-msg-protocol:ros-message)
  ((response
    :reader response
    :initarg :response
    :type cl:string
    :initform ""))
)

(cl:defclass Default_BB_ROS_Bridge-response (<Default_BB_ROS_Bridge-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Default_BB_ROS_Bridge-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Default_BB_ROS_Bridge-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<Default_BB_ROS_Bridge-response> is deprecated: use bbros_bridge-srv:Default_BB_ROS_Bridge-response instead.")))

(cl:ensure-generic-function 'response-val :lambda-list '(m))
(cl:defmethod response-val ((m <Default_BB_ROS_Bridge-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:response-val is deprecated.  Use bbros_bridge-srv:response instead.")
  (response m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Default_BB_ROS_Bridge-response>) ostream)
  "Serializes a message object of type '<Default_BB_ROS_Bridge-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'response))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'response))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Default_BB_ROS_Bridge-response>) istream)
  "Deserializes a message object of type '<Default_BB_ROS_Bridge-response>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Default_BB_ROS_Bridge-response>)))
  "Returns string type for a service object of type '<Default_BB_ROS_Bridge-response>"
  "bbros_bridge/Default_BB_ROS_BridgeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Default_BB_ROS_Bridge-response)))
  "Returns string type for a service object of type 'Default_BB_ROS_Bridge-response"
  "bbros_bridge/Default_BB_ROS_BridgeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Default_BB_ROS_Bridge-response>)))
  "Returns md5sum for a message object of type '<Default_BB_ROS_Bridge-response>"
  "6162a5d58ec2c814778e9c41c1bf44eb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Default_BB_ROS_Bridge-response)))
  "Returns md5sum for a message object of type 'Default_BB_ROS_Bridge-response"
  "6162a5d58ec2c814778e9c41c1bf44eb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Default_BB_ROS_Bridge-response>)))
  "Returns full string definition for message of type '<Default_BB_ROS_Bridge-response>"
  (cl:format cl:nil "string response~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Default_BB_ROS_Bridge-response)))
  "Returns full string definition for message of type 'Default_BB_ROS_Bridge-response"
  (cl:format cl:nil "string response~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Default_BB_ROS_Bridge-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'response))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Default_BB_ROS_Bridge-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Default_BB_ROS_Bridge-response
    (cl:cons ':response (response msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Default_BB_ROS_Bridge)))
  'Default_BB_ROS_Bridge-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Default_BB_ROS_Bridge)))
  'Default_BB_ROS_Bridge-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Default_BB_ROS_Bridge)))
  "Returns string type for a service object of type '<Default_BB_ROS_Bridge>"
  "bbros_bridge/Default_BB_ROS_Bridge")