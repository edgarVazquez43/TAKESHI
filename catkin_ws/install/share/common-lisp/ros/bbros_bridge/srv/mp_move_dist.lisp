; Auto-generated. Do not edit!


(cl:in-package bbros_bridge-srv)


;//! \htmlinclude mp_move_dist-request.msg.html

(cl:defclass <mp_move_dist-request> (roslisp-msg-protocol:ros-message)
  ((distance
    :reader distance
    :initarg :distance
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32)))
)

(cl:defclass mp_move_dist-request (<mp_move_dist-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_move_dist-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_move_dist-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<mp_move_dist-request> is deprecated: use bbros_bridge-srv:mp_move_dist-request instead.")))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <mp_move_dist-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:distance-val is deprecated.  Use bbros_bridge-srv:distance instead.")
  (distance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_move_dist-request>) ostream)
  "Serializes a message object of type '<mp_move_dist-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'distance) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_move_dist-request>) istream)
  "Deserializes a message object of type '<mp_move_dist-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'distance) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_move_dist-request>)))
  "Returns string type for a service object of type '<mp_move_dist-request>"
  "bbros_bridge/mp_move_distRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_move_dist-request)))
  "Returns string type for a service object of type 'mp_move_dist-request"
  "bbros_bridge/mp_move_distRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_move_dist-request>)))
  "Returns md5sum for a message object of type '<mp_move_dist-request>"
  "6869a1d070e885a82e01cea5e86d2372")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_move_dist-request)))
  "Returns md5sum for a message object of type 'mp_move_dist-request"
  "6869a1d070e885a82e01cea5e86d2372")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_move_dist-request>)))
  "Returns full string definition for message of type '<mp_move_dist-request>"
  (cl:format cl:nil "std_msgs/Float32 distance~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_move_dist-request)))
  "Returns full string definition for message of type 'mp_move_dist-request"
  (cl:format cl:nil "std_msgs/Float32 distance~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_move_dist-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'distance))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_move_dist-request>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_move_dist-request
    (cl:cons ':distance (distance msg))
))
;//! \htmlinclude mp_move_dist-response.msg.html

(cl:defclass <mp_move_dist-response> (roslisp-msg-protocol:ros-message)
  ((traveledDistance
    :reader traveledDistance
    :initarg :traveledDistance
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32)))
)

(cl:defclass mp_move_dist-response (<mp_move_dist-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_move_dist-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_move_dist-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<mp_move_dist-response> is deprecated: use bbros_bridge-srv:mp_move_dist-response instead.")))

(cl:ensure-generic-function 'traveledDistance-val :lambda-list '(m))
(cl:defmethod traveledDistance-val ((m <mp_move_dist-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:traveledDistance-val is deprecated.  Use bbros_bridge-srv:traveledDistance instead.")
  (traveledDistance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_move_dist-response>) ostream)
  "Serializes a message object of type '<mp_move_dist-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'traveledDistance) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_move_dist-response>) istream)
  "Deserializes a message object of type '<mp_move_dist-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'traveledDistance) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_move_dist-response>)))
  "Returns string type for a service object of type '<mp_move_dist-response>"
  "bbros_bridge/mp_move_distResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_move_dist-response)))
  "Returns string type for a service object of type 'mp_move_dist-response"
  "bbros_bridge/mp_move_distResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_move_dist-response>)))
  "Returns md5sum for a message object of type '<mp_move_dist-response>"
  "6869a1d070e885a82e01cea5e86d2372")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_move_dist-response)))
  "Returns md5sum for a message object of type 'mp_move_dist-response"
  "6869a1d070e885a82e01cea5e86d2372")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_move_dist-response>)))
  "Returns full string definition for message of type '<mp_move_dist-response>"
  (cl:format cl:nil "std_msgs/Float32 traveledDistance~%~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_move_dist-response)))
  "Returns full string definition for message of type 'mp_move_dist-response"
  (cl:format cl:nil "std_msgs/Float32 traveledDistance~%~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_move_dist-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'traveledDistance))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_move_dist-response>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_move_dist-response
    (cl:cons ':traveledDistance (traveledDistance msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'mp_move_dist)))
  'mp_move_dist-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'mp_move_dist)))
  'mp_move_dist-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_move_dist)))
  "Returns string type for a service object of type '<mp_move_dist>"
  "bbros_bridge/mp_move_dist")