; Auto-generated. Do not edit!


(cl:in-package mvn_pln-srv)


;//! \htmlinclude mp_getclose-request.msg.html

(cl:defclass <mp_getclose-request> (roslisp-msg-protocol:ros-message)
  ((location
    :reader location
    :initarg :location
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass mp_getclose-request (<mp_getclose-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_getclose-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_getclose-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mvn_pln-srv:<mp_getclose-request> is deprecated: use mvn_pln-srv:mp_getclose-request instead.")))

(cl:ensure-generic-function 'location-val :lambda-list '(m))
(cl:defmethod location-val ((m <mp_getclose-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mvn_pln-srv:location-val is deprecated.  Use mvn_pln-srv:location instead.")
  (location m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_getclose-request>) ostream)
  "Serializes a message object of type '<mp_getclose-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'location) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_getclose-request>) istream)
  "Deserializes a message object of type '<mp_getclose-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'location) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_getclose-request>)))
  "Returns string type for a service object of type '<mp_getclose-request>"
  "mvn_pln/mp_getcloseRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose-request)))
  "Returns string type for a service object of type 'mp_getclose-request"
  "mvn_pln/mp_getcloseRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_getclose-request>)))
  "Returns md5sum for a message object of type '<mp_getclose-request>"
  "1919ccd065ce7aa924cb46471f2dd632")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_getclose-request)))
  "Returns md5sum for a message object of type 'mp_getclose-request"
  "1919ccd065ce7aa924cb46471f2dd632")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_getclose-request>)))
  "Returns full string definition for message of type '<mp_getclose-request>"
  (cl:format cl:nil "std_msgs/String location~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_getclose-request)))
  "Returns full string definition for message of type 'mp_getclose-request"
  (cl:format cl:nil "std_msgs/String location~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_getclose-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'location))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_getclose-request>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_getclose-request
    (cl:cons ':location (location msg))
))
;//! \htmlinclude mp_getclose-response.msg.html

(cl:defclass <mp_getclose-response> (roslisp-msg-protocol:ros-message)
  ((error
    :reader error
    :initarg :error
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass mp_getclose-response (<mp_getclose-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mp_getclose-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mp_getclose-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mvn_pln-srv:<mp_getclose-response> is deprecated: use mvn_pln-srv:mp_getclose-response instead.")))

(cl:ensure-generic-function 'error-val :lambda-list '(m))
(cl:defmethod error-val ((m <mp_getclose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mvn_pln-srv:error-val is deprecated.  Use mvn_pln-srv:error instead.")
  (error m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mp_getclose-response>) ostream)
  "Serializes a message object of type '<mp_getclose-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'error) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mp_getclose-response>) istream)
  "Deserializes a message object of type '<mp_getclose-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'error) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mp_getclose-response>)))
  "Returns string type for a service object of type '<mp_getclose-response>"
  "mvn_pln/mp_getcloseResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose-response)))
  "Returns string type for a service object of type 'mp_getclose-response"
  "mvn_pln/mp_getcloseResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mp_getclose-response>)))
  "Returns md5sum for a message object of type '<mp_getclose-response>"
  "1919ccd065ce7aa924cb46471f2dd632")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mp_getclose-response)))
  "Returns md5sum for a message object of type 'mp_getclose-response"
  "1919ccd065ce7aa924cb46471f2dd632")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mp_getclose-response>)))
  "Returns full string definition for message of type '<mp_getclose-response>"
  (cl:format cl:nil "std_msgs/String error~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mp_getclose-response)))
  "Returns full string definition for message of type 'mp_getclose-response"
  (cl:format cl:nil "std_msgs/String error~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mp_getclose-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'error))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mp_getclose-response>))
  "Converts a ROS message object to a list"
  (cl:list 'mp_getclose-response
    (cl:cons ':error (error msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'mp_getclose)))
  'mp_getclose-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'mp_getclose)))
  'mp_getclose-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mp_getclose)))
  "Returns string type for a service object of type '<mp_getclose>"
  "mvn_pln/mp_getclose")