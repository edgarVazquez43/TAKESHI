; Auto-generated. Do not edit!


(cl:in-package mvn_pln-srv)


;//! \htmlinclude mp_getclose_xy-request.msg.html

(cl:defclass <mp_getclose_xy-request> (roslisp-msg-protocol:ros-message)
  ((goalX
    :reader goalX
    :initarg :goalX
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (goalY
    :reader goalY
    :initarg :goalY
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32)))
)

(cl:defclass mp_getclose_xy-request (<mp_getclose_xy-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_getclose_xy-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_getclose_xy-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mvn_pln-srv:<mp_getclose_xy-request> is deprecated: use mvn_pln-srv:mp_getclose_xy-request instead.")))

(cl:ensure-generic-function 'goalX-val :lambda-list '(m))
(cl:defmethod goalX-val ((m <mp_getclose_xy-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mvn_pln-srv:goalX-val is deprecated.  Use mvn_pln-srv:goalX instead.")
  (goalX m))

(cl:ensure-generic-function 'goalY-val :lambda-list '(m))
(cl:defmethod goalY-val ((m <mp_getclose_xy-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mvn_pln-srv:goalY-val is deprecated.  Use mvn_pln-srv:goalY instead.")
  (goalY m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_getclose_xy-request>) ostream)
  "Serializes a message object of type '<mp_getclose_xy-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalX) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalY) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_getclose_xy-request>) istream)
  "Deserializes a message object of type '<mp_getclose_xy-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalX) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalY) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_getclose_xy-request>)))
  "Returns string type for a service object of type '<mp_getclose_xy-request>"
  "mvn_pln/mp_getclose_xyRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose_xy-request)))
  "Returns string type for a service object of type 'mp_getclose_xy-request"
  "mvn_pln/mp_getclose_xyRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_getclose_xy-request>)))
  "Returns md5sum for a message object of type '<mp_getclose_xy-request>"
  "a6bfdb792bb6f7c25c686505f84f9b9c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_getclose_xy-request)))
  "Returns md5sum for a message object of type 'mp_getclose_xy-request"
  "a6bfdb792bb6f7c25c686505f84f9b9c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_getclose_xy-request>)))
  "Returns full string definition for message of type '<mp_getclose_xy-request>"
  (cl:format cl:nil "std_msgs/Float32 goalX~%std_msgs/Float32 goalY~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_getclose_xy-request)))
  "Returns full string definition for message of type 'mp_getclose_xy-request"
  (cl:format cl:nil "std_msgs/Float32 goalX~%std_msgs/Float32 goalY~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_getclose_xy-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalX))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalY))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_getclose_xy-request>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_getclose_xy-request
    (cl:cons ':goalX (goalX msg))
    (cl:cons ':goalY (goalY msg))
))
;//! \htmlinclude mp_getclose_xy-response.msg.html

(cl:defclass <mp_getclose_xy-response> (roslisp-msg-protocol:ros-message)
  ((error
    :reader error
    :initarg :error
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass mp_getclose_xy-response (<mp_getclose_xy-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_getclose_xy-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_getclose_xy-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mvn_pln-srv:<mp_getclose_xy-response> is deprecated: use mvn_pln-srv:mp_getclose_xy-response instead.")))

(cl:ensure-generic-function 'error-val :lambda-list '(m))
(cl:defmethod error-val ((m <mp_getclose_xy-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mvn_pln-srv:error-val is deprecated.  Use mvn_pln-srv:error instead.")
  (error m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_getclose_xy-response>) ostream)
  "Serializes a message object of type '<mp_getclose_xy-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'error) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_getclose_xy-response>) istream)
  "Deserializes a message object of type '<mp_getclose_xy-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'error) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_getclose_xy-response>)))
  "Returns string type for a service object of type '<mp_getclose_xy-response>"
  "mvn_pln/mp_getclose_xyResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose_xy-response)))
  "Returns string type for a service object of type 'mp_getclose_xy-response"
  "mvn_pln/mp_getclose_xyResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_getclose_xy-response>)))
  "Returns md5sum for a message object of type '<mp_getclose_xy-response>"
  "a6bfdb792bb6f7c25c686505f84f9b9c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_getclose_xy-response)))
  "Returns md5sum for a message object of type 'mp_getclose_xy-response"
  "a6bfdb792bb6f7c25c686505f84f9b9c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_getclose_xy-response>)))
  "Returns full string definition for message of type '<mp_getclose_xy-response>"
  (cl:format cl:nil "std_msgs/String error~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_getclose_xy-response)))
  "Returns full string definition for message of type 'mp_getclose_xy-response"
  (cl:format cl:nil "std_msgs/String error~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_getclose_xy-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'error))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_getclose_xy-response>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_getclose_xy-response
    (cl:cons ':error (error msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'mp_getclose_xy)))
  'mp_getclose_xy-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'mp_getclose_xy)))
  'mp_getclose_xy-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose_xy)))
  "Returns string type for a service object of type '<mp_getclose_xy>"
  "mvn_pln/mp_getclose_xy")