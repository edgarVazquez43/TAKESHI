; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-msg)


;//! \htmlinclude PlanningCmdClips.msg.html

(cl:defclass <PlanningCmdClips> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (params
    :reader params
    :initarg :params
    :type cl:string
    :initform "")
   (id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (successful
    :reader successful
    :initarg :successful
    :type cl:integer
    :initform 0))
)

(cl:defclass PlanningCmdClips (<PlanningCmdClips>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PlanningCmdClips>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PlanningCmdClips)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-msg:<PlanningCmdClips> is deprecated: use knowledge_msgs-msg:PlanningCmdClips instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <PlanningCmdClips>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:name-val is deprecated.  Use knowledge_msgs-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'params-val :lambda-list '(m))
(cl:defmethod params-val ((m <PlanningCmdClips>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:params-val is deprecated.  Use knowledge_msgs-msg:params instead.")
  (params m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <PlanningCmdClips>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:id-val is deprecated.  Use knowledge_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'successful-val :lambda-list '(m))
(cl:defmethod successful-val ((m <PlanningCmdClips>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:successful-val is deprecated.  Use knowledge_msgs-msg:successful instead.")
  (successful m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PlanningCmdClips>) ostream)
  "Serializes a message object of type '<PlanningCmdClips>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'params))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'params))
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'successful)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PlanningCmdClips>) istream)
  "Deserializes a message object of type '<PlanningCmdClips>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'params) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'params) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'successful) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PlanningCmdClips>)))
  "Returns string type for a message object of type '<PlanningCmdClips>"
  "knowledge_msgs/PlanningCmdClips")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PlanningCmdClips)))
  "Returns string type for a message object of type 'PlanningCmdClips"
  "knowledge_msgs/PlanningCmdClips")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PlanningCmdClips>)))
  "Returns md5sum for a message object of type '<PlanningCmdClips>"
  "74450e6e60135cf7d80c9acedebf851b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PlanningCmdClips)))
  "Returns md5sum for a message object of type 'PlanningCmdClips"
  "74450e6e60135cf7d80c9acedebf851b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PlanningCmdClips>)))
  "Returns full string definition for message of type '<PlanningCmdClips>"
  (cl:format cl:nil "string name~%string params~%int32 id~%int32 successful~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PlanningCmdClips)))
  "Returns full string definition for message of type 'PlanningCmdClips"
  (cl:format cl:nil "string name~%string params~%int32 id~%int32 successful~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PlanningCmdClips>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     4 (cl:length (cl:slot-value msg 'params))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PlanningCmdClips>))
  "Converts a ROS message object to a list"
  (cl:list 'PlanningCmdClips
    (cl:cons ':name (name msg))
    (cl:cons ':params (params msg))
    (cl:cons ':id (id msg))
    (cl:cons ':successful (successful msg))
))
