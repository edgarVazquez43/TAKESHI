; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-msg)


;//! \htmlinclude MapPredefinedQuestions.msg.html

(cl:defclass <MapPredefinedQuestions> (roslisp-msg-protocol:ros-message)
  ((question
    :reader question
    :initarg :question
    :type cl:string
    :initform "")
   (answer
    :reader answer
    :initarg :answer
    :type cl:string
    :initform ""))
)

(cl:defclass MapPredefinedQuestions (<MapPredefinedQuestions>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MapPredefinedQuestions>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MapPredefinedQuestions)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-msg:<MapPredefinedQuestions> is deprecated: use knowledge_msgs-msg:MapPredefinedQuestions instead.")))

(cl:ensure-generic-function 'question-val :lambda-list '(m))
(cl:defmethod question-val ((m <MapPredefinedQuestions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:question-val is deprecated.  Use knowledge_msgs-msg:question instead.")
  (question m))

(cl:ensure-generic-function 'answer-val :lambda-list '(m))
(cl:defmethod answer-val ((m <MapPredefinedQuestions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:answer-val is deprecated.  Use knowledge_msgs-msg:answer instead.")
  (answer m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MapPredefinedQuestions>) ostream)
  "Serializes a message object of type '<MapPredefinedQuestions>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'question))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'question))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'answer))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'answer))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MapPredefinedQuestions>) istream)
  "Deserializes a message object of type '<MapPredefinedQuestions>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'question) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'question) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'answer) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'answer) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MapPredefinedQuestions>)))
  "Returns string type for a message object of type '<MapPredefinedQuestions>"
  "knowledge_msgs/MapPredefinedQuestions")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MapPredefinedQuestions)))
  "Returns string type for a message object of type 'MapPredefinedQuestions"
  "knowledge_msgs/MapPredefinedQuestions")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MapPredefinedQuestions>)))
  "Returns md5sum for a message object of type '<MapPredefinedQuestions>"
  "a27d8629aeefd2b315942fe4a74ab143")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MapPredefinedQuestions)))
  "Returns md5sum for a message object of type 'MapPredefinedQuestions"
  "a27d8629aeefd2b315942fe4a74ab143")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MapPredefinedQuestions>)))
  "Returns full string definition for message of type '<MapPredefinedQuestions>"
  (cl:format cl:nil "string question~%string answer~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MapPredefinedQuestions)))
  "Returns full string definition for message of type 'MapPredefinedQuestions"
  (cl:format cl:nil "string question~%string answer~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MapPredefinedQuestions>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'question))
     4 (cl:length (cl:slot-value msg 'answer))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MapPredefinedQuestions>))
  "Converts a ROS message object to a list"
  (cl:list 'MapPredefinedQuestions
    (cl:cons ':question (question msg))
    (cl:cons ':answer (answer msg))
))
