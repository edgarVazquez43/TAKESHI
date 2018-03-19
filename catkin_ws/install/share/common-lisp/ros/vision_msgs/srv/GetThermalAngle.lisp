; Auto-generated. Do not edit!


(cl:in-package vision_msgs-srv)


;//! \htmlinclude GetThermalAngle-request.msg.html

(cl:defclass <GetThermalAngle-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetThermalAngle-request (<GetThermalAngle-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetThermalAngle-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetThermalAngle-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<GetThermalAngle-request> is deprecated: use vision_msgs-srv:GetThermalAngle-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetThermalAngle-request>) ostream)
  "Serializes a message object of type '<GetThermalAngle-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetThermalAngle-request>) istream)
  "Deserializes a message object of type '<GetThermalAngle-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetThermalAngle-request>)))
  "Returns string type for a service object of type '<GetThermalAngle-request>"
  "vision_msgs/GetThermalAngleRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetThermalAngle-request)))
  "Returns string type for a service object of type 'GetThermalAngle-request"
  "vision_msgs/GetThermalAngleRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetThermalAngle-request>)))
  "Returns md5sum for a message object of type '<GetThermalAngle-request>"
  "6e530ad148ac6d527edc145df842dd24")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetThermalAngle-request)))
  "Returns md5sum for a message object of type 'GetThermalAngle-request"
  "6e530ad148ac6d527edc145df842dd24")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetThermalAngle-request>)))
  "Returns full string definition for message of type '<GetThermalAngle-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetThermalAngle-request)))
  "Returns full string definition for message of type 'GetThermalAngle-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetThermalAngle-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetThermalAngle-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetThermalAngle-request
))
;//! \htmlinclude GetThermalAngle-response.msg.html

(cl:defclass <GetThermalAngle-response> (roslisp-msg-protocol:ros-message)
  ((th_angle
    :reader th_angle
    :initarg :th_angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass GetThermalAngle-response (<GetThermalAngle-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetThermalAngle-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetThermalAngle-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<GetThermalAngle-response> is deprecated: use vision_msgs-srv:GetThermalAngle-response instead.")))

(cl:ensure-generic-function 'th_angle-val :lambda-list '(m))
(cl:defmethod th_angle-val ((m <GetThermalAngle-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:th_angle-val is deprecated.  Use vision_msgs-srv:th_angle instead.")
  (th_angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetThermalAngle-response>) ostream)
  "Serializes a message object of type '<GetThermalAngle-response>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'th_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetThermalAngle-response>) istream)
  "Deserializes a message object of type '<GetThermalAngle-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'th_angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetThermalAngle-response>)))
  "Returns string type for a service object of type '<GetThermalAngle-response>"
  "vision_msgs/GetThermalAngleResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetThermalAngle-response)))
  "Returns string type for a service object of type 'GetThermalAngle-response"
  "vision_msgs/GetThermalAngleResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetThermalAngle-response>)))
  "Returns md5sum for a message object of type '<GetThermalAngle-response>"
  "6e530ad148ac6d527edc145df842dd24")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetThermalAngle-response)))
  "Returns md5sum for a message object of type 'GetThermalAngle-response"
  "6e530ad148ac6d527edc145df842dd24")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetThermalAngle-response>)))
  "Returns full string definition for message of type '<GetThermalAngle-response>"
  (cl:format cl:nil "float32 th_angle~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetThermalAngle-response)))
  "Returns full string definition for message of type 'GetThermalAngle-response"
  (cl:format cl:nil "float32 th_angle~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetThermalAngle-response>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetThermalAngle-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetThermalAngle-response
    (cl:cons ':th_angle (th_angle msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetThermalAngle)))
  'GetThermalAngle-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetThermalAngle)))
  'GetThermalAngle-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetThermalAngle)))
  "Returns string type for a service object of type '<GetThermalAngle>"
  "vision_msgs/GetThermalAngle")