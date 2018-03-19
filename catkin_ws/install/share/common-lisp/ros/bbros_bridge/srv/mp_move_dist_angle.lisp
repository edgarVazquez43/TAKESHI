; Auto-generated. Do not edit!


(cl:in-package bbros_bridge-srv)


;//! \htmlinclude mp_move_dist_angle-request.msg.html

(cl:defclass <mp_move_dist_angle-request> (roslisp-msg-protocol:ros-message)
  ((bearing
    :reader bearing
    :initarg :bearing
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (distance
    :reader distance
    :initarg :distance
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32)))
)

(cl:defclass mp_move_dist_angle-request (<mp_move_dist_angle-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_move_dist_angle-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_move_dist_angle-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<mp_move_dist_angle-request> is deprecated: use bbros_bridge-srv:mp_move_dist_angle-request instead.")))

(cl:ensure-generic-function 'bearing-val :lambda-list '(m))
(cl:defmethod bearing-val ((m <mp_move_dist_angle-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:bearing-val is deprecated.  Use bbros_bridge-srv:bearing instead.")
  (bearing m))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <mp_move_dist_angle-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:distance-val is deprecated.  Use bbros_bridge-srv:distance instead.")
  (distance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_move_dist_angle-request>) ostream)
  "Serializes a message object of type '<mp_move_dist_angle-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bearing) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'distance) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_move_dist_angle-request>) istream)
  "Deserializes a message object of type '<mp_move_dist_angle-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bearing) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'distance) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_move_dist_angle-request>)))
  "Returns string type for a service object of type '<mp_move_dist_angle-request>"
  "bbros_bridge/mp_move_dist_angleRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_move_dist_angle-request)))
  "Returns string type for a service object of type 'mp_move_dist_angle-request"
  "bbros_bridge/mp_move_dist_angleRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_move_dist_angle-request>)))
  "Returns md5sum for a message object of type '<mp_move_dist_angle-request>"
  "930663ac8b505c579c42369296ce1052")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_move_dist_angle-request)))
  "Returns md5sum for a message object of type 'mp_move_dist_angle-request"
  "930663ac8b505c579c42369296ce1052")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_move_dist_angle-request>)))
  "Returns full string definition for message of type '<mp_move_dist_angle-request>"
  (cl:format cl:nil "std_msgs/Float32 bearing~%std_msgs/Float32 distance~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_move_dist_angle-request)))
  "Returns full string definition for message of type 'mp_move_dist_angle-request"
  (cl:format cl:nil "std_msgs/Float32 bearing~%std_msgs/Float32 distance~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_move_dist_angle-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bearing))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'distance))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_move_dist_angle-request>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_move_dist_angle-request
    (cl:cons ':bearing (bearing msg))
    (cl:cons ':distance (distance msg))
))
;//! \htmlinclude mp_move_dist_angle-response.msg.html

(cl:defclass <mp_move_dist_angle-response> (roslisp-msg-protocol:ros-message)
  ((traveledBearing
    :reader traveledBearing
    :initarg :traveledBearing
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (traveledDistance
    :reader traveledDistance
    :initarg :traveledDistance
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32)))
)

(cl:defclass mp_move_dist_angle-response (<mp_move_dist_angle-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_move_dist_angle-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_move_dist_angle-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<mp_move_dist_angle-response> is deprecated: use bbros_bridge-srv:mp_move_dist_angle-response instead.")))

(cl:ensure-generic-function 'traveledBearing-val :lambda-list '(m))
(cl:defmethod traveledBearing-val ((m <mp_move_dist_angle-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:traveledBearing-val is deprecated.  Use bbros_bridge-srv:traveledBearing instead.")
  (traveledBearing m))

(cl:ensure-generic-function 'traveledDistance-val :lambda-list '(m))
(cl:defmethod traveledDistance-val ((m <mp_move_dist_angle-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:traveledDistance-val is deprecated.  Use bbros_bridge-srv:traveledDistance instead.")
  (traveledDistance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_move_dist_angle-response>) ostream)
  "Serializes a message object of type '<mp_move_dist_angle-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'traveledBearing) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'traveledDistance) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_move_dist_angle-response>) istream)
  "Deserializes a message object of type '<mp_move_dist_angle-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'traveledBearing) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'traveledDistance) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_move_dist_angle-response>)))
  "Returns string type for a service object of type '<mp_move_dist_angle-response>"
  "bbros_bridge/mp_move_dist_angleResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_move_dist_angle-response)))
  "Returns string type for a service object of type 'mp_move_dist_angle-response"
  "bbros_bridge/mp_move_dist_angleResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_move_dist_angle-response>)))
  "Returns md5sum for a message object of type '<mp_move_dist_angle-response>"
  "930663ac8b505c579c42369296ce1052")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_move_dist_angle-response)))
  "Returns md5sum for a message object of type 'mp_move_dist_angle-response"
  "930663ac8b505c579c42369296ce1052")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_move_dist_angle-response>)))
  "Returns full string definition for message of type '<mp_move_dist_angle-response>"
  (cl:format cl:nil "std_msgs/Float32 traveledBearing~%std_msgs/Float32 traveledDistance~%~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_move_dist_angle-response)))
  "Returns full string definition for message of type 'mp_move_dist_angle-response"
  (cl:format cl:nil "std_msgs/Float32 traveledBearing~%std_msgs/Float32 traveledDistance~%~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_move_dist_angle-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'traveledBearing))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'traveledDistance))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_move_dist_angle-response>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_move_dist_angle-response
    (cl:cons ':traveledBearing (traveledBearing msg))
    (cl:cons ':traveledDistance (traveledDistance msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'mp_move_dist_angle)))
  'mp_move_dist_angle-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'mp_move_dist_angle)))
  'mp_move_dist_angle-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_move_dist_angle)))
  "Returns string type for a service object of type '<mp_move_dist_angle>"
  "bbros_bridge/mp_move_dist_angle")