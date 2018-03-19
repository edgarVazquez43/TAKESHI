; Auto-generated. Do not edit!


(cl:in-package bbros_bridge-srv)


;//! \htmlinclude mp_getclose_xya-request.msg.html

(cl:defclass <mp_getclose_xya-request> (roslisp-msg-protocol:ros-message)
  ((goalX
    :reader goalX
    :initarg :goalX
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (goalY
    :reader goalY
    :initarg :goalY
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (goalAngle
    :reader goalAngle
    :initarg :goalAngle
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32)))
)

(cl:defclass mp_getclose_xya-request (<mp_getclose_xya-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_getclose_xya-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_getclose_xya-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<mp_getclose_xya-request> is deprecated: use bbros_bridge-srv:mp_getclose_xya-request instead.")))

(cl:ensure-generic-function 'goalX-val :lambda-list '(m))
(cl:defmethod goalX-val ((m <mp_getclose_xya-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:goalX-val is deprecated.  Use bbros_bridge-srv:goalX instead.")
  (goalX m))

(cl:ensure-generic-function 'goalY-val :lambda-list '(m))
(cl:defmethod goalY-val ((m <mp_getclose_xya-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:goalY-val is deprecated.  Use bbros_bridge-srv:goalY instead.")
  (goalY m))

(cl:ensure-generic-function 'goalAngle-val :lambda-list '(m))
(cl:defmethod goalAngle-val ((m <mp_getclose_xya-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:goalAngle-val is deprecated.  Use bbros_bridge-srv:goalAngle instead.")
  (goalAngle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_getclose_xya-request>) ostream)
  "Serializes a message object of type '<mp_getclose_xya-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalX) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalY) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalAngle) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_getclose_xya-request>) istream)
  "Deserializes a message object of type '<mp_getclose_xya-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalX) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalY) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalAngle) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_getclose_xya-request>)))
  "Returns string type for a service object of type '<mp_getclose_xya-request>"
  "bbros_bridge/mp_getclose_xyaRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose_xya-request)))
  "Returns string type for a service object of type 'mp_getclose_xya-request"
  "bbros_bridge/mp_getclose_xyaRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_getclose_xya-request>)))
  "Returns md5sum for a message object of type '<mp_getclose_xya-request>"
  "f236a8bf2a517b8af728eb19291f51cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_getclose_xya-request)))
  "Returns md5sum for a message object of type 'mp_getclose_xya-request"
  "f236a8bf2a517b8af728eb19291f51cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_getclose_xya-request>)))
  "Returns full string definition for message of type '<mp_getclose_xya-request>"
  (cl:format cl:nil "std_msgs/Float32 goalX~%std_msgs/Float32 goalY~%std_msgs/Float32 goalAngle~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_getclose_xya-request)))
  "Returns full string definition for message of type 'mp_getclose_xya-request"
  (cl:format cl:nil "std_msgs/Float32 goalX~%std_msgs/Float32 goalY~%std_msgs/Float32 goalAngle~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_getclose_xya-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalX))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalY))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalAngle))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_getclose_xya-request>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_getclose_xya-request
    (cl:cons ':goalX (goalX msg))
    (cl:cons ':goalY (goalY msg))
    (cl:cons ':goalAngle (goalAngle msg))
))
;//! \htmlinclude mp_getclose_xya-response.msg.html

(cl:defclass <mp_getclose_xya-response> (roslisp-msg-protocol:ros-message)
  ((error
    :reader error
    :initarg :error
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass mp_getclose_xya-response (<mp_getclose_xya-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_getclose_xya-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_getclose_xya-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<mp_getclose_xya-response> is deprecated: use bbros_bridge-srv:mp_getclose_xya-response instead.")))

(cl:ensure-generic-function 'error-val :lambda-list '(m))
(cl:defmethod error-val ((m <mp_getclose_xya-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:error-val is deprecated.  Use bbros_bridge-srv:error instead.")
  (error m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_getclose_xya-response>) ostream)
  "Serializes a message object of type '<mp_getclose_xya-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'error) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_getclose_xya-response>) istream)
  "Deserializes a message object of type '<mp_getclose_xya-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'error) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_getclose_xya-response>)))
  "Returns string type for a service object of type '<mp_getclose_xya-response>"
  "bbros_bridge/mp_getclose_xyaResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose_xya-response)))
  "Returns string type for a service object of type 'mp_getclose_xya-response"
  "bbros_bridge/mp_getclose_xyaResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_getclose_xya-response>)))
  "Returns md5sum for a message object of type '<mp_getclose_xya-response>"
  "f236a8bf2a517b8af728eb19291f51cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_getclose_xya-response)))
  "Returns md5sum for a message object of type 'mp_getclose_xya-response"
  "f236a8bf2a517b8af728eb19291f51cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_getclose_xya-response>)))
  "Returns full string definition for message of type '<mp_getclose_xya-response>"
  (cl:format cl:nil "std_msgs/String error~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_getclose_xya-response)))
  "Returns full string definition for message of type 'mp_getclose_xya-response"
  (cl:format cl:nil "std_msgs/String error~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_getclose_xya-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'error))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_getclose_xya-response>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_getclose_xya-response
    (cl:cons ':error (error msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'mp_getclose_xya)))
  'mp_getclose_xya-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'mp_getclose_xya)))
  'mp_getclose_xya-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose_xya)))
  "Returns string type for a service object of type '<mp_getclose_xya>"
  "bbros_bridge/mp_getclose_xya")