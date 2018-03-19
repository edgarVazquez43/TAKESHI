; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude wait_for_confirm-request.msg.html

(cl:defclass <wait_for_confirm-request> (roslisp-msg-protocol:ros-message)
  ((repeat_sentence
    :reader repeat_sentence
    :initarg :repeat_sentence
    :type knowledge_msgs-msg:RepeatedSentence
    :initform (cl:make-instance 'knowledge_msgs-msg:RepeatedSentence))
   (timeout
    :reader timeout
    :initarg :timeout
    :type cl:integer
    :initform 0))
)

(cl:defclass wait_for_confirm-request (<wait_for_confirm-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <wait_for_confirm-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'wait_for_confirm-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<wait_for_confirm-request> is deprecated: use knowledge_msgs-srv:wait_for_confirm-request instead.")))

(cl:ensure-generic-function 'repeat_sentence-val :lambda-list '(m))
(cl:defmethod repeat_sentence-val ((m <wait_for_confirm-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:repeat_sentence-val is deprecated.  Use knowledge_msgs-srv:repeat_sentence instead.")
  (repeat_sentence m))

(cl:ensure-generic-function 'timeout-val :lambda-list '(m))
(cl:defmethod timeout-val ((m <wait_for_confirm-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:timeout-val is deprecated.  Use knowledge_msgs-srv:timeout instead.")
  (timeout m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <wait_for_confirm-request>) ostream)
  "Serializes a message object of type '<wait_for_confirm-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'repeat_sentence) ostream)
  (cl:let* ((signed (cl:slot-value msg 'timeout)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <wait_for_confirm-request>) istream)
  "Deserializes a message object of type '<wait_for_confirm-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'repeat_sentence) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'timeout) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<wait_for_confirm-request>)))
  "Returns string type for a service object of type '<wait_for_confirm-request>"
  "knowledge_msgs/wait_for_confirmRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_confirm-request)))
  "Returns string type for a service object of type 'wait_for_confirm-request"
  "knowledge_msgs/wait_for_confirmRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<wait_for_confirm-request>)))
  "Returns md5sum for a message object of type '<wait_for_confirm-request>"
  "aae0ce22da8fbc00ac2c3455196d2577")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'wait_for_confirm-request)))
  "Returns md5sum for a message object of type 'wait_for_confirm-request"
  "aae0ce22da8fbc00ac2c3455196d2577")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<wait_for_confirm-request>)))
  "Returns full string definition for message of type '<wait_for_confirm-request>"
  (cl:format cl:nil "RepeatedSentence repeat_sentence~%int32 timeout~%~%================================================================================~%MSG: knowledge_msgs/RepeatedSentence~%string sentence~%int32 repeat_time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'wait_for_confirm-request)))
  "Returns full string definition for message of type 'wait_for_confirm-request"
  (cl:format cl:nil "RepeatedSentence repeat_sentence~%int32 timeout~%~%================================================================================~%MSG: knowledge_msgs/RepeatedSentence~%string sentence~%int32 repeat_time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <wait_for_confirm-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'repeat_sentence))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <wait_for_confirm-request>))
  "Converts a ROS message object to a list"
  (cl:list 'wait_for_confirm-request
    (cl:cons ':repeat_sentence (repeat_sentence msg))
    (cl:cons ':timeout (timeout msg))
))
;//! \htmlinclude wait_for_confirm-response.msg.html

(cl:defclass <wait_for_confirm-response> (roslisp-msg-protocol:ros-message)
  ((confirmation_received
    :reader confirmation_received
    :initarg :confirmation_received
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass wait_for_confirm-response (<wait_for_confirm-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <wait_for_confirm-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'wait_for_confirm-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<wait_for_confirm-response> is deprecated: use knowledge_msgs-srv:wait_for_confirm-response instead.")))

(cl:ensure-generic-function 'confirmation_received-val :lambda-list '(m))
(cl:defmethod confirmation_received-val ((m <wait_for_confirm-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:confirmation_received-val is deprecated.  Use knowledge_msgs-srv:confirmation_received instead.")
  (confirmation_received m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <wait_for_confirm-response>) ostream)
  "Serializes a message object of type '<wait_for_confirm-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'confirmation_received) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <wait_for_confirm-response>) istream)
  "Deserializes a message object of type '<wait_for_confirm-response>"
    (cl:setf (cl:slot-value msg 'confirmation_received) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<wait_for_confirm-response>)))
  "Returns string type for a service object of type '<wait_for_confirm-response>"
  "knowledge_msgs/wait_for_confirmResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_confirm-response)))
  "Returns string type for a service object of type 'wait_for_confirm-response"
  "knowledge_msgs/wait_for_confirmResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<wait_for_confirm-response>)))
  "Returns md5sum for a message object of type '<wait_for_confirm-response>"
  "aae0ce22da8fbc00ac2c3455196d2577")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'wait_for_confirm-response)))
  "Returns md5sum for a message object of type 'wait_for_confirm-response"
  "aae0ce22da8fbc00ac2c3455196d2577")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<wait_for_confirm-response>)))
  "Returns full string definition for message of type '<wait_for_confirm-response>"
  (cl:format cl:nil "bool confirmation_received~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'wait_for_confirm-response)))
  "Returns full string definition for message of type 'wait_for_confirm-response"
  (cl:format cl:nil "bool confirmation_received~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <wait_for_confirm-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <wait_for_confirm-response>))
  "Converts a ROS message object to a list"
  (cl:list 'wait_for_confirm-response
    (cl:cons ':confirmation_received (confirmation_received msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'wait_for_confirm)))
  'wait_for_confirm-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'wait_for_confirm)))
  'wait_for_confirm-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'wait_for_confirm)))
  "Returns string type for a service object of type '<wait_for_confirm>"
  "knowledge_msgs/wait_for_confirm")