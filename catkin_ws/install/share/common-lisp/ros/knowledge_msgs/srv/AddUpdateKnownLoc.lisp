; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude AddUpdateKnownLoc-request.msg.html

(cl:defclass <AddUpdateKnownLoc-request> (roslisp-msg-protocol:ros-message)
  ((loc
    :reader loc
    :initarg :loc
    :type knowledge_msgs-msg:MapKnownLocation
    :initform (cl:make-instance 'knowledge_msgs-msg:MapKnownLocation)))
)

(cl:defclass AddUpdateKnownLoc-request (<AddUpdateKnownLoc-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AddUpdateKnownLoc-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AddUpdateKnownLoc-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<AddUpdateKnownLoc-request> is deprecated: use knowledge_msgs-srv:AddUpdateKnownLoc-request instead.")))

(cl:ensure-generic-function 'loc-val :lambda-list '(m))
(cl:defmethod loc-val ((m <AddUpdateKnownLoc-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:loc-val is deprecated.  Use knowledge_msgs-srv:loc instead.")
  (loc m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AddUpdateKnownLoc-request>) ostream)
  "Serializes a message object of type '<AddUpdateKnownLoc-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'loc) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AddUpdateKnownLoc-request>) istream)
  "Deserializes a message object of type '<AddUpdateKnownLoc-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'loc) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AddUpdateKnownLoc-request>)))
  "Returns string type for a service object of type '<AddUpdateKnownLoc-request>"
  "knowledge_msgs/AddUpdateKnownLocRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddUpdateKnownLoc-request)))
  "Returns string type for a service object of type 'AddUpdateKnownLoc-request"
  "knowledge_msgs/AddUpdateKnownLocRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AddUpdateKnownLoc-request>)))
  "Returns md5sum for a message object of type '<AddUpdateKnownLoc-request>"
  "c8eea2400325e7fa5b296976b0201acc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AddUpdateKnownLoc-request)))
  "Returns md5sum for a message object of type 'AddUpdateKnownLoc-request"
  "c8eea2400325e7fa5b296976b0201acc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AddUpdateKnownLoc-request>)))
  "Returns full string definition for message of type '<AddUpdateKnownLoc-request>"
  (cl:format cl:nil "MapKnownLocation loc~%~%================================================================================~%MSG: knowledge_msgs/MapKnownLocation~%string name~%float32[] value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AddUpdateKnownLoc-request)))
  "Returns full string definition for message of type 'AddUpdateKnownLoc-request"
  (cl:format cl:nil "MapKnownLocation loc~%~%================================================================================~%MSG: knowledge_msgs/MapKnownLocation~%string name~%float32[] value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AddUpdateKnownLoc-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'loc))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AddUpdateKnownLoc-request>))
  "Converts a ROS message object to a list"
  (cl:list 'AddUpdateKnownLoc-request
    (cl:cons ':loc (loc msg))
))
;//! \htmlinclude AddUpdateKnownLoc-response.msg.html

(cl:defclass <AddUpdateKnownLoc-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass AddUpdateKnownLoc-response (<AddUpdateKnownLoc-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AddUpdateKnownLoc-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AddUpdateKnownLoc-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<AddUpdateKnownLoc-response> is deprecated: use knowledge_msgs-srv:AddUpdateKnownLoc-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AddUpdateKnownLoc-response>) ostream)
  "Serializes a message object of type '<AddUpdateKnownLoc-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AddUpdateKnownLoc-response>) istream)
  "Deserializes a message object of type '<AddUpdateKnownLoc-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AddUpdateKnownLoc-response>)))
  "Returns string type for a service object of type '<AddUpdateKnownLoc-response>"
  "knowledge_msgs/AddUpdateKnownLocResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddUpdateKnownLoc-response)))
  "Returns string type for a service object of type 'AddUpdateKnownLoc-response"
  "knowledge_msgs/AddUpdateKnownLocResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AddUpdateKnownLoc-response>)))
  "Returns md5sum for a message object of type '<AddUpdateKnownLoc-response>"
  "c8eea2400325e7fa5b296976b0201acc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AddUpdateKnownLoc-response)))
  "Returns md5sum for a message object of type 'AddUpdateKnownLoc-response"
  "c8eea2400325e7fa5b296976b0201acc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AddUpdateKnownLoc-response>)))
  "Returns full string definition for message of type '<AddUpdateKnownLoc-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AddUpdateKnownLoc-response)))
  "Returns full string definition for message of type 'AddUpdateKnownLoc-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AddUpdateKnownLoc-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AddUpdateKnownLoc-response>))
  "Converts a ROS message object to a list"
  (cl:list 'AddUpdateKnownLoc-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'AddUpdateKnownLoc)))
  'AddUpdateKnownLoc-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'AddUpdateKnownLoc)))
  'AddUpdateKnownLoc-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AddUpdateKnownLoc)))
  "Returns string type for a service object of type '<AddUpdateKnownLoc>"
  "knowledge_msgs/AddUpdateKnownLoc")