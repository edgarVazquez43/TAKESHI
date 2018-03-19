; Auto-generated. Do not edit!


(cl:in-package bbros_bridge-srv)


;//! \htmlinclude hd_lookat-request.msg.html

(cl:defclass <hd_lookat-request> (roslisp-msg-protocol:ros-message)
  ((goalPan
    :reader goalPan
    :initarg :goalPan
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (goalTilt
    :reader goalTilt
    :initarg :goalTilt
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32)))
)

(cl:defclass hd_lookat-request (<hd_lookat-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hd_lookat-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hd_lookat-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<hd_lookat-request> is deprecated: use bbros_bridge-srv:hd_lookat-request instead.")))

(cl:ensure-generic-function 'goalPan-val :lambda-list '(m))
(cl:defmethod goalPan-val ((m <hd_lookat-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:goalPan-val is deprecated.  Use bbros_bridge-srv:goalPan instead.")
  (goalPan m))

(cl:ensure-generic-function 'goalTilt-val :lambda-list '(m))
(cl:defmethod goalTilt-val ((m <hd_lookat-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:goalTilt-val is deprecated.  Use bbros_bridge-srv:goalTilt instead.")
  (goalTilt m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hd_lookat-request>) ostream)
  "Serializes a message object of type '<hd_lookat-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalPan) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalTilt) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hd_lookat-request>) istream)
  "Deserializes a message object of type '<hd_lookat-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalPan) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalTilt) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hd_lookat-request>)))
  "Returns string type for a service object of type '<hd_lookat-request>"
  "bbros_bridge/hd_lookatRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hd_lookat-request)))
  "Returns string type for a service object of type 'hd_lookat-request"
  "bbros_bridge/hd_lookatRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hd_lookat-request>)))
  "Returns md5sum for a message object of type '<hd_lookat-request>"
  "0d2267ae1acd4d7549c1a4e21fcad0ae")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hd_lookat-request)))
  "Returns md5sum for a message object of type 'hd_lookat-request"
  "0d2267ae1acd4d7549c1a4e21fcad0ae")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hd_lookat-request>)))
  "Returns full string definition for message of type '<hd_lookat-request>"
  (cl:format cl:nil "std_msgs/Float32 goalPan~%std_msgs/Float32 goalTilt~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hd_lookat-request)))
  "Returns full string definition for message of type 'hd_lookat-request"
  (cl:format cl:nil "std_msgs/Float32 goalPan~%std_msgs/Float32 goalTilt~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hd_lookat-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalPan))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalTilt))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hd_lookat-request>))
  "Converts a ROS message object to a list"
  (cl:list 'hd_lookat-request
    (cl:cons ':goalPan (goalPan msg))
    (cl:cons ':goalTilt (goalTilt msg))
))
;//! \htmlinclude hd_lookat-response.msg.html

(cl:defclass <hd_lookat-response> (roslisp-msg-protocol:ros-message)
  ((currentPan
    :reader currentPan
    :initarg :currentPan
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (currentTilt
    :reader currentTilt
    :initarg :currentTilt
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32))
   (errors
    :reader errors
    :initarg :errors
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass hd_lookat-response (<hd_lookat-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <hd_lookat-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'hd_lookat-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-srv:<hd_lookat-response> is deprecated: use bbros_bridge-srv:hd_lookat-response instead.")))

(cl:ensure-generic-function 'currentPan-val :lambda-list '(m))
(cl:defmethod currentPan-val ((m <hd_lookat-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:currentPan-val is deprecated.  Use bbros_bridge-srv:currentPan instead.")
  (currentPan m))

(cl:ensure-generic-function 'currentTilt-val :lambda-list '(m))
(cl:defmethod currentTilt-val ((m <hd_lookat-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:currentTilt-val is deprecated.  Use bbros_bridge-srv:currentTilt instead.")
  (currentTilt m))

(cl:ensure-generic-function 'errors-val :lambda-list '(m))
(cl:defmethod errors-val ((m <hd_lookat-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-srv:errors-val is deprecated.  Use bbros_bridge-srv:errors instead.")
  (errors m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <hd_lookat-response>) ostream)
  "Serializes a message object of type '<hd_lookat-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'currentPan) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'currentTilt) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'errors) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <hd_lookat-response>) istream)
  "Deserializes a message object of type '<hd_lookat-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'currentPan) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'currentTilt) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'errors) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<hd_lookat-response>)))
  "Returns string type for a service object of type '<hd_lookat-response>"
  "bbros_bridge/hd_lookatResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hd_lookat-response)))
  "Returns string type for a service object of type 'hd_lookat-response"
  "bbros_bridge/hd_lookatResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<hd_lookat-response>)))
  "Returns md5sum for a message object of type '<hd_lookat-response>"
  "0d2267ae1acd4d7549c1a4e21fcad0ae")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'hd_lookat-response)))
  "Returns md5sum for a message object of type 'hd_lookat-response"
  "0d2267ae1acd4d7549c1a4e21fcad0ae")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<hd_lookat-response>)))
  "Returns full string definition for message of type '<hd_lookat-response>"
  (cl:format cl:nil "std_msgs/Float32 currentPan~%std_msgs/Float32 currentTilt~%std_msgs/String errors~%~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'hd_lookat-response)))
  "Returns full string definition for message of type 'hd_lookat-response"
  (cl:format cl:nil "std_msgs/Float32 currentPan~%std_msgs/Float32 currentTilt~%std_msgs/String errors~%~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <hd_lookat-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'currentPan))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'currentTilt))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'errors))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <hd_lookat-response>))
  "Converts a ROS message object to a list"
  (cl:list 'hd_lookat-response
    (cl:cons ':currentPan (currentPan msg))
    (cl:cons ':currentTilt (currentTilt msg))
    (cl:cons ':errors (errors msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'hd_lookat)))
  'hd_lookat-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'hd_lookat)))
  'hd_lookat-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'hd_lookat)))
  "Returns string type for a service object of type '<hd_lookat>"
  "bbros_bridge/hd_lookat")