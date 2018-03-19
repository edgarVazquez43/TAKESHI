; Auto-generated. Do not edit!


(cl:in-package mvn_pln-srv)


;//! \htmlinclude mp_obstacle-request.msg.html

(cl:defclass <mp_obstacle-request> (roslisp-msg-protocol:ros-message)
  ((obstacle
    :reader obstacle
    :initarg :obstacle
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass mp_obstacle-request (<mp_obstacle-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_obstacle-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_obstacle-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mvn_pln-srv:<mp_obstacle-request> is deprecated: use mvn_pln-srv:mp_obstacle-request instead.")))

(cl:ensure-generic-function 'obstacle-val :lambda-list '(m))
(cl:defmethod obstacle-val ((m <mp_obstacle-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mvn_pln-srv:obstacle-val is deprecated.  Use mvn_pln-srv:obstacle instead.")
  (obstacle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_obstacle-request>) ostream)
  "Serializes a message object of type '<mp_obstacle-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'obstacle) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_obstacle-request>) istream)
  "Deserializes a message object of type '<mp_obstacle-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'obstacle) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_obstacle-request>)))
  "Returns string type for a service object of type '<mp_obstacle-request>"
  "mvn_pln/mp_obstacleRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_obstacle-request)))
  "Returns string type for a service object of type 'mp_obstacle-request"
  "mvn_pln/mp_obstacleRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_obstacle-request>)))
  "Returns md5sum for a message object of type '<mp_obstacle-request>"
  "938f9cc76650ee8bc7d6dc8275ba504b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_obstacle-request)))
  "Returns md5sum for a message object of type 'mp_obstacle-request"
  "938f9cc76650ee8bc7d6dc8275ba504b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_obstacle-request>)))
  "Returns full string definition for message of type '<mp_obstacle-request>"
  (cl:format cl:nil "std_msgs/String obstacle~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_obstacle-request)))
  "Returns full string definition for message of type 'mp_obstacle-request"
  (cl:format cl:nil "std_msgs/String obstacle~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_obstacle-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'obstacle))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_obstacle-request>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_obstacle-request
    (cl:cons ':obstacle (obstacle msg))
))
;//! \htmlinclude mp_obstacle-response.msg.html

(cl:defclass <mp_obstacle-response> (roslisp-msg-protocol:ros-message)
  ((found
    :reader found
    :initarg :found
    :type std_msgs-msg:Bool
    :initform (cl:make-instance 'std_msgs-msg:Bool)))
)

(cl:defclass mp_obstacle-response (<mp_obstacle-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_obstacle-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_obstacle-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mvn_pln-srv:<mp_obstacle-response> is deprecated: use mvn_pln-srv:mp_obstacle-response instead.")))

(cl:ensure-generic-function 'found-val :lambda-list '(m))
(cl:defmethod found-val ((m <mp_obstacle-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mvn_pln-srv:found-val is deprecated.  Use mvn_pln-srv:found instead.")
  (found m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_obstacle-response>) ostream)
  "Serializes a message object of type '<mp_obstacle-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'found) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_obstacle-response>) istream)
  "Deserializes a message object of type '<mp_obstacle-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'found) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_obstacle-response>)))
  "Returns string type for a service object of type '<mp_obstacle-response>"
  "mvn_pln/mp_obstacleResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_obstacle-response)))
  "Returns string type for a service object of type 'mp_obstacle-response"
  "mvn_pln/mp_obstacleResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_obstacle-response>)))
  "Returns md5sum for a message object of type '<mp_obstacle-response>"
  "938f9cc76650ee8bc7d6dc8275ba504b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_obstacle-response)))
  "Returns md5sum for a message object of type 'mp_obstacle-response"
  "938f9cc76650ee8bc7d6dc8275ba504b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_obstacle-response>)))
  "Returns full string definition for message of type '<mp_obstacle-response>"
  (cl:format cl:nil "std_msgs/Bool found~%~%================================================================================~%MSG: std_msgs/Bool~%bool data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_obstacle-response)))
  "Returns full string definition for message of type 'mp_obstacle-response"
  (cl:format cl:nil "std_msgs/Bool found~%~%================================================================================~%MSG: std_msgs/Bool~%bool data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_obstacle-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'found))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_obstacle-response>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_obstacle-response
    (cl:cons ':found (found msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'mp_obstacle)))
  'mp_obstacle-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'mp_obstacle)))
  'mp_obstacle-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_obstacle)))
  "Returns string type for a service object of type '<mp_obstacle>"
  "mvn_pln/mp_obstacle")