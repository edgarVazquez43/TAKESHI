; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude place_object-request.msg.html

(cl:defclass <place_object-request> (roslisp-msg-protocol:ros-message)
  ((dest_location
    :reader dest_location
    :initarg :dest_location
    :type cl:string
    :initform "")
   (arm_to_use
    :reader arm_to_use
    :initarg :arm_to_use
    :type cl:integer
    :initform 0))
)

(cl:defclass place_object-request (<place_object-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <place_object-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'place_object-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<place_object-request> is deprecated: use knowledge_msgs-srv:place_object-request instead.")))

(cl:ensure-generic-function 'dest_location-val :lambda-list '(m))
(cl:defmethod dest_location-val ((m <place_object-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:dest_location-val is deprecated.  Use knowledge_msgs-srv:dest_location instead.")
  (dest_location m))

(cl:ensure-generic-function 'arm_to_use-val :lambda-list '(m))
(cl:defmethod arm_to_use-val ((m <place_object-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:arm_to_use-val is deprecated.  Use knowledge_msgs-srv:arm_to_use instead.")
  (arm_to_use m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <place_object-request>) ostream)
  "Serializes a message object of type '<place_object-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'dest_location))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'dest_location))
  (cl:let* ((signed (cl:slot-value msg 'arm_to_use)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <place_object-request>) istream)
  "Deserializes a message object of type '<place_object-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'dest_location) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'dest_location) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'arm_to_use) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<place_object-request>)))
  "Returns string type for a service object of type '<place_object-request>"
  "knowledge_msgs/place_objectRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'place_object-request)))
  "Returns string type for a service object of type 'place_object-request"
  "knowledge_msgs/place_objectRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<place_object-request>)))
  "Returns md5sum for a message object of type '<place_object-request>"
  "72e5fc1d3c709f9c79fea87497774dd9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'place_object-request)))
  "Returns md5sum for a message object of type 'place_object-request"
  "72e5fc1d3c709f9c79fea87497774dd9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<place_object-request>)))
  "Returns full string definition for message of type '<place_object-request>"
  (cl:format cl:nil "string dest_location~%int32 arm_to_use~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'place_object-request)))
  "Returns full string definition for message of type 'place_object-request"
  (cl:format cl:nil "string dest_location~%int32 arm_to_use~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <place_object-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'dest_location))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <place_object-request>))
  "Converts a ROS message object to a list"
  (cl:list 'place_object-request
    (cl:cons ':dest_location (dest_location msg))
    (cl:cons ':arm_to_use (arm_to_use msg))
))
;//! \htmlinclude place_object-response.msg.html

(cl:defclass <place_object-response> (roslisp-msg-protocol:ros-message)
  ((task_success
    :reader task_success
    :initarg :task_success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass place_object-response (<place_object-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <place_object-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'place_object-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<place_object-response> is deprecated: use knowledge_msgs-srv:place_object-response instead.")))

(cl:ensure-generic-function 'task_success-val :lambda-list '(m))
(cl:defmethod task_success-val ((m <place_object-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:task_success-val is deprecated.  Use knowledge_msgs-srv:task_success instead.")
  (task_success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <place_object-response>) ostream)
  "Serializes a message object of type '<place_object-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'task_success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <place_object-response>) istream)
  "Deserializes a message object of type '<place_object-response>"
    (cl:setf (cl:slot-value msg 'task_success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<place_object-response>)))
  "Returns string type for a service object of type '<place_object-response>"
  "knowledge_msgs/place_objectResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'place_object-response)))
  "Returns string type for a service object of type 'place_object-response"
  "knowledge_msgs/place_objectResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<place_object-response>)))
  "Returns md5sum for a message object of type '<place_object-response>"
  "72e5fc1d3c709f9c79fea87497774dd9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'place_object-response)))
  "Returns md5sum for a message object of type 'place_object-response"
  "72e5fc1d3c709f9c79fea87497774dd9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<place_object-response>)))
  "Returns full string definition for message of type '<place_object-response>"
  (cl:format cl:nil "bool task_success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'place_object-response)))
  "Returns full string definition for message of type 'place_object-response"
  (cl:format cl:nil "bool task_success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <place_object-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <place_object-response>))
  "Converts a ROS message object to a list"
  (cl:list 'place_object-response
    (cl:cons ':task_success (task_success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'place_object)))
  'place_object-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'place_object)))
  'place_object-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'place_object)))
  "Returns string type for a service object of type '<place_object>"
  "knowledge_msgs/place_object")