; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude parse_sentence_cfr-request.msg.html

(cl:defclass <parse_sentence_cfr-request> (roslisp-msg-protocol:ros-message)
  ((sentence
    :reader sentence
    :initarg :sentence
    :type cl:string
    :initform ""))
)

(cl:defclass parse_sentence_cfr-request (<parse_sentence_cfr-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <parse_sentence_cfr-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'parse_sentence_cfr-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<parse_sentence_cfr-request> is deprecated: use knowledge_msgs-srv:parse_sentence_cfr-request instead.")))

(cl:ensure-generic-function 'sentence-val :lambda-list '(m))
(cl:defmethod sentence-val ((m <parse_sentence_cfr-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:sentence-val is deprecated.  Use knowledge_msgs-srv:sentence instead.")
  (sentence m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <parse_sentence_cfr-request>) ostream)
  "Serializes a message object of type '<parse_sentence_cfr-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'sentence))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'sentence))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <parse_sentence_cfr-request>) istream)
  "Deserializes a message object of type '<parse_sentence_cfr-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sentence) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'sentence) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<parse_sentence_cfr-request>)))
  "Returns string type for a service object of type '<parse_sentence_cfr-request>"
  "knowledge_msgs/parse_sentence_cfrRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'parse_sentence_cfr-request)))
  "Returns string type for a service object of type 'parse_sentence_cfr-request"
  "knowledge_msgs/parse_sentence_cfrRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<parse_sentence_cfr-request>)))
  "Returns md5sum for a message object of type '<parse_sentence_cfr-request>"
  "953467976fe5830442f3fbb0187ffa3b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'parse_sentence_cfr-request)))
  "Returns md5sum for a message object of type 'parse_sentence_cfr-request"
  "953467976fe5830442f3fbb0187ffa3b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<parse_sentence_cfr-request>)))
  "Returns full string definition for message of type '<parse_sentence_cfr-request>"
  (cl:format cl:nil "string sentence~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'parse_sentence_cfr-request)))
  "Returns full string definition for message of type 'parse_sentence_cfr-request"
  (cl:format cl:nil "string sentence~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <parse_sentence_cfr-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'sentence))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <parse_sentence_cfr-request>))
  "Converts a ROS message object to a list"
  (cl:list 'parse_sentence_cfr-request
    (cl:cons ':sentence (sentence msg))
))
;//! \htmlinclude parse_sentence_cfr-response.msg.html

(cl:defclass <parse_sentence_cfr-response> (roslisp-msg-protocol:ros-message)
  ((cfr
    :reader cfr
    :initarg :cfr
    :type knowledge_msgs-msg:PlanningCFR
    :initform (cl:make-instance 'knowledge_msgs-msg:PlanningCFR)))
)

(cl:defclass parse_sentence_cfr-response (<parse_sentence_cfr-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <parse_sentence_cfr-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'parse_sentence_cfr-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<parse_sentence_cfr-response> is deprecated: use knowledge_msgs-srv:parse_sentence_cfr-response instead.")))

(cl:ensure-generic-function 'cfr-val :lambda-list '(m))
(cl:defmethod cfr-val ((m <parse_sentence_cfr-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:cfr-val is deprecated.  Use knowledge_msgs-srv:cfr instead.")
  (cfr m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <parse_sentence_cfr-response>) ostream)
  "Serializes a message object of type '<parse_sentence_cfr-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cfr) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <parse_sentence_cfr-response>) istream)
  "Deserializes a message object of type '<parse_sentence_cfr-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cfr) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<parse_sentence_cfr-response>)))
  "Returns string type for a service object of type '<parse_sentence_cfr-response>"
  "knowledge_msgs/parse_sentence_cfrResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'parse_sentence_cfr-response)))
  "Returns string type for a service object of type 'parse_sentence_cfr-response"
  "knowledge_msgs/parse_sentence_cfrResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<parse_sentence_cfr-response>)))
  "Returns md5sum for a message object of type '<parse_sentence_cfr-response>"
  "953467976fe5830442f3fbb0187ffa3b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'parse_sentence_cfr-response)))
  "Returns md5sum for a message object of type 'parse_sentence_cfr-response"
  "953467976fe5830442f3fbb0187ffa3b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<parse_sentence_cfr-response>)))
  "Returns full string definition for message of type '<parse_sentence_cfr-response>"
  (cl:format cl:nil "PlanningCFR cfr~%~%~%================================================================================~%MSG: knowledge_msgs/PlanningCFR~%string command~%CFRParams[] params~%~%================================================================================~%MSG: knowledge_msgs/CFRParams~%string frame_id~%string frame_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'parse_sentence_cfr-response)))
  "Returns full string definition for message of type 'parse_sentence_cfr-response"
  (cl:format cl:nil "PlanningCFR cfr~%~%~%================================================================================~%MSG: knowledge_msgs/PlanningCFR~%string command~%CFRParams[] params~%~%================================================================================~%MSG: knowledge_msgs/CFRParams~%string frame_id~%string frame_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <parse_sentence_cfr-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cfr))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <parse_sentence_cfr-response>))
  "Converts a ROS message object to a list"
  (cl:list 'parse_sentence_cfr-response
    (cl:cons ':cfr (cfr msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'parse_sentence_cfr)))
  'parse_sentence_cfr-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'parse_sentence_cfr)))
  'parse_sentence_cfr-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'parse_sentence_cfr)))
  "Returns string type for a service object of type '<parse_sentence_cfr>"
  "knowledge_msgs/parse_sentence_cfr")