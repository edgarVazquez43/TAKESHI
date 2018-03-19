; Auto-generated. Do not edit!


(cl:in-package audio_msgs-srv)


;//! \htmlinclude srvAngle-request.msg.html

(cl:defclass <srvAngle-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass srvAngle-request (<srvAngle-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <srvAngle-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'srvAngle-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name audio_msgs-srv:<srvAngle-request> is deprecated: use audio_msgs-srv:srvAngle-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <srvAngle-request>) ostream)
  "Serializes a message object of type '<srvAngle-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <srvAngle-request>) istream)
  "Deserializes a message object of type '<srvAngle-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<srvAngle-request>)))
  "Returns string type for a service object of type '<srvAngle-request>"
  "audio_msgs/srvAngleRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvAngle-request)))
  "Returns string type for a service object of type 'srvAngle-request"
  "audio_msgs/srvAngleRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<srvAngle-request>)))
  "Returns md5sum for a message object of type '<srvAngle-request>"
  "3c12d5a3eed4d7589fde4b3bcd93aff0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'srvAngle-request)))
  "Returns md5sum for a message object of type 'srvAngle-request"
  "3c12d5a3eed4d7589fde4b3bcd93aff0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<srvAngle-request>)))
  "Returns full string definition for message of type '<srvAngle-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'srvAngle-request)))
  "Returns full string definition for message of type 'srvAngle-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <srvAngle-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <srvAngle-request>))
  "Converts a ROS message object to a list"
  (cl:list 'srvAngle-request
))
;//! \htmlinclude srvAngle-response.msg.html

(cl:defclass <srvAngle-response> (roslisp-msg-protocol:ros-message)
  ((Angle
    :reader Angle
    :initarg :Angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass srvAngle-response (<srvAngle-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <srvAngle-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'srvAngle-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name audio_msgs-srv:<srvAngle-response> is deprecated: use audio_msgs-srv:srvAngle-response instead.")))

(cl:ensure-generic-function 'Angle-val :lambda-list '(m))
(cl:defmethod Angle-val ((m <srvAngle-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader audio_msgs-srv:Angle-val is deprecated.  Use audio_msgs-srv:Angle instead.")
  (Angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <srvAngle-response>) ostream)
  "Serializes a message object of type '<srvAngle-response>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <srvAngle-response>) istream)
  "Deserializes a message object of type '<srvAngle-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<srvAngle-response>)))
  "Returns string type for a service object of type '<srvAngle-response>"
  "audio_msgs/srvAngleResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvAngle-response)))
  "Returns string type for a service object of type 'srvAngle-response"
  "audio_msgs/srvAngleResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<srvAngle-response>)))
  "Returns md5sum for a message object of type '<srvAngle-response>"
  "3c12d5a3eed4d7589fde4b3bcd93aff0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'srvAngle-response)))
  "Returns md5sum for a message object of type 'srvAngle-response"
  "3c12d5a3eed4d7589fde4b3bcd93aff0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<srvAngle-response>)))
  "Returns full string definition for message of type '<srvAngle-response>"
  (cl:format cl:nil "float32 Angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'srvAngle-response)))
  "Returns full string definition for message of type 'srvAngle-response"
  (cl:format cl:nil "float32 Angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <srvAngle-response>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <srvAngle-response>))
  "Converts a ROS message object to a list"
  (cl:list 'srvAngle-response
    (cl:cons ':Angle (Angle msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'srvAngle)))
  'srvAngle-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'srvAngle)))
  'srvAngle-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'srvAngle)))
  "Returns string type for a service object of type '<srvAngle>"
  "audio_msgs/srvAngle")