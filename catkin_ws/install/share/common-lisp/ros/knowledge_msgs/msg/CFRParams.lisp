; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-msg)


;//! \htmlinclude CFRParams.msg.html

(cl:defclass <CFRParams> (roslisp-msg-protocol:ros-message)
  ((frame_id
    :reader frame_id
    :initarg :frame_id
    :type cl:string
    :initform "")
   (frame_value
    :reader frame_value
    :initarg :frame_value
    :type cl:string
    :initform ""))
)

(cl:defclass CFRParams (<CFRParams>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CFRParams>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CFRParams)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-msg:<CFRParams> is deprecated: use knowledge_msgs-msg:CFRParams instead.")))

(cl:ensure-generic-function 'frame_id-val :lambda-list '(m))
(cl:defmethod frame_id-val ((m <CFRParams>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:frame_id-val is deprecated.  Use knowledge_msgs-msg:frame_id instead.")
  (frame_id m))

(cl:ensure-generic-function 'frame_value-val :lambda-list '(m))
(cl:defmethod frame_value-val ((m <CFRParams>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:frame_value-val is deprecated.  Use knowledge_msgs-msg:frame_value instead.")
  (frame_value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CFRParams>) ostream)
  "Serializes a message object of type '<CFRParams>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'frame_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'frame_id))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'frame_value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'frame_value))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CFRParams>) istream)
  "Deserializes a message object of type '<CFRParams>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frame_id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'frame_id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frame_value) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'frame_value) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CFRParams>)))
  "Returns string type for a message object of type '<CFRParams>"
  "knowledge_msgs/CFRParams")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CFRParams)))
  "Returns string type for a message object of type 'CFRParams"
  "knowledge_msgs/CFRParams")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CFRParams>)))
  "Returns md5sum for a message object of type '<CFRParams>"
  "4244adddfc44a0d0799b10600c99b834")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CFRParams)))
  "Returns md5sum for a message object of type 'CFRParams"
  "4244adddfc44a0d0799b10600c99b834")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CFRParams>)))
  "Returns full string definition for message of type '<CFRParams>"
  (cl:format cl:nil "string frame_id~%string frame_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CFRParams)))
  "Returns full string definition for message of type 'CFRParams"
  (cl:format cl:nil "string frame_id~%string frame_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CFRParams>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'frame_id))
     4 (cl:length (cl:slot-value msg 'frame_value))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CFRParams>))
  "Converts a ROS message object to a list"
  (cl:list 'CFRParams
    (cl:cons ':frame_id (frame_id msg))
    (cl:cons ':frame_value (frame_value msg))
))
