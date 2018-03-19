; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-msg)


;//! \htmlinclude RepeatedSentence.msg.html

(cl:defclass <RepeatedSentence> (roslisp-msg-protocol:ros-message)
  ((sentence
    :reader sentence
    :initarg :sentence
    :type cl:string
    :initform "")
   (repeat_time
    :reader repeat_time
    :initarg :repeat_time
    :type cl:integer
    :initform 0))
)

(cl:defclass RepeatedSentence (<RepeatedSentence>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RepeatedSentence>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RepeatedSentence)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-msg:<RepeatedSentence> is deprecated: use knowledge_msgs-msg:RepeatedSentence instead.")))

(cl:ensure-generic-function 'sentence-val :lambda-list '(m))
(cl:defmethod sentence-val ((m <RepeatedSentence>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:sentence-val is deprecated.  Use knowledge_msgs-msg:sentence instead.")
  (sentence m))

(cl:ensure-generic-function 'repeat_time-val :lambda-list '(m))
(cl:defmethod repeat_time-val ((m <RepeatedSentence>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:repeat_time-val is deprecated.  Use knowledge_msgs-msg:repeat_time instead.")
  (repeat_time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RepeatedSentence>) ostream)
  "Serializes a message object of type '<RepeatedSentence>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'sentence))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'sentence))
  (cl:let* ((signed (cl:slot-value msg 'repeat_time)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RepeatedSentence>) istream)
  "Deserializes a message object of type '<RepeatedSentence>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sentence) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'sentence) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'repeat_time) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RepeatedSentence>)))
  "Returns string type for a message object of type '<RepeatedSentence>"
  "knowledge_msgs/RepeatedSentence")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RepeatedSentence)))
  "Returns string type for a message object of type 'RepeatedSentence"
  "knowledge_msgs/RepeatedSentence")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RepeatedSentence>)))
  "Returns md5sum for a message object of type '<RepeatedSentence>"
  "608dcaa9c362c4d6c83fcb8f1b807c83")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RepeatedSentence)))
  "Returns md5sum for a message object of type 'RepeatedSentence"
  "608dcaa9c362c4d6c83fcb8f1b807c83")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RepeatedSentence>)))
  "Returns full string definition for message of type '<RepeatedSentence>"
  (cl:format cl:nil "string sentence~%int32 repeat_time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RepeatedSentence)))
  "Returns full string definition for message of type 'RepeatedSentence"
  (cl:format cl:nil "string sentence~%int32 repeat_time~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RepeatedSentence>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'sentence))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RepeatedSentence>))
  "Converts a ROS message object to a list"
  (cl:list 'RepeatedSentence
    (cl:cons ':sentence (sentence msg))
    (cl:cons ':repeat_time (repeat_time msg))
))
