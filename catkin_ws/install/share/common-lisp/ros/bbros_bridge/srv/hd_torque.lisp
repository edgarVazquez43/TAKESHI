; Auto-generated. Do not edit!


(cl:in-package bbros_bridge-srv)


;//! \htmlinclude hd_torque-request.msg.html

(cl:defclass <hd_torque-request> (roslisp-msg-protocol:ros-message)
  ((enable
    :reader enable
    :initarg :enable
    :type std_msgs-msg:Bool
    :initform (cl:make-instance 'std_msgs-msg:Bool)))
)

(cl:defclass hd_torque-request (<hd_torque-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hd_torque-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hd_torque-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<hd_torque-request> is deprecated: use bbros_bridge-srv:hd_torque-request instead.")))

(cl:ensure-generic-function 'enable-val :lambda-list '(m))
(cl:defmethod enable-val ((m <hd_torque-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:enable-val is deprecated.  Use bbros_bridge-srv:enable instead.")
  (enable m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hd_torque-request>) ostream)
  "Serializes a message object of type '<hd_torque-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'enable) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hd_torque-request>) istream)
  "Deserializes a message object of type '<hd_torque-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'enable) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hd_torque-request>)))
  "Returns string type for a service object of type '<hd_torque-request>"
  "bbros_bridge/hd_torqueRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hd_torque-request)))
  "Returns string type for a service object of type 'hd_torque-request"
  "bbros_bridge/hd_torqueRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hd_torque-request>)))
  "Returns md5sum for a message object of type '<hd_torque-request>"
  "5ec6cba259224de8444ec81114c3fa2f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hd_torque-request)))
  "Returns md5sum for a message object of type 'hd_torque-request"
  "5ec6cba259224de8444ec81114c3fa2f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hd_torque-request>)))
  "Returns full string definition for message of type '<hd_torque-request>"
  (cl:format cl:nil "std_msgs/Bool enable~%~%================================================================================~%MSG: std_msgs/Bool~%bool data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hd_torque-request)))
  "Returns full string definition for message of type 'hd_torque-request"
  (cl:format cl:nil "std_msgs/Bool enable~%~%================================================================================~%MSG: std_msgs/Bool~%bool data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hd_torque-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'enable))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hd_torque-request>))
  "Converts a ROS message object to a list"
  (cl:list 'hd_torque-request
    (cl:cons ':enable (enable msg))
))
;//! \htmlinclude hd_torque-response.msg.html

(cl:defclass <hd_torque-response> (roslisp-msg-protocol:ros-message)
  ((errors
    :reader errors
    :initarg :errors
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass hd_torque-response (<hd_torque-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hd_torque-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hd_torque-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<hd_torque-response> is deprecated: use bbros_bridge-srv:hd_torque-response instead.")))

(cl:ensure-generic-function 'errors-val :lambda-list '(m))
(cl:defmethod errors-val ((m <hd_torque-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:errors-val is deprecated.  Use bbros_bridge-srv:errors instead.")
  (errors m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hd_torque-response>) ostream)
  "Serializes a message object of type '<hd_torque-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'errors) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hd_torque-response>) istream)
  "Deserializes a message object of type '<hd_torque-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'errors) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hd_torque-response>)))
  "Returns string type for a service object of type '<hd_torque-response>"
  "bbros_bridge/hd_torqueResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hd_torque-response)))
  "Returns string type for a service object of type 'hd_torque-response"
  "bbros_bridge/hd_torqueResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hd_torque-response>)))
  "Returns md5sum for a message object of type '<hd_torque-response>"
  "5ec6cba259224de8444ec81114c3fa2f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hd_torque-response)))
  "Returns md5sum for a message object of type 'hd_torque-response"
  "5ec6cba259224de8444ec81114c3fa2f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hd_torque-response>)))
  "Returns full string definition for message of type '<hd_torque-response>"
  (cl:format cl:nil "std_msgs/String errors~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hd_torque-response)))
  "Returns full string definition for message of type 'hd_torque-response"
  (cl:format cl:nil "std_msgs/String errors~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hd_torque-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'errors))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hd_torque-response>))
  "Converts a ROS message object to a list"
  (cl:list 'hd_torque-response
    (cl:cons ':errors (errors msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'hd_torque)))
  'hd_torque-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'hd_torque)))
  'hd_torque-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hd_torque)))
  "Returns string type for a service object of type '<hd_torque>"
  "bbros_bridge/hd_torque")