; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude GetPredefinedArmsPoses-request.msg.html

(cl:defclass <GetPredefinedArmsPoses-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform ""))
)

(cl:defclass GetPredefinedArmsPoses-request (<GetPredefinedArmsPoses-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetPredefinedArmsPoses-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetPredefinedArmsPoses-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<GetPredefinedArmsPoses-request> is deprecated: use knowledge_msgs-srv:GetPredefinedArmsPoses-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <GetPredefinedArmsPoses-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:name-val is deprecated.  Use knowledge_msgs-srv:name instead.")
  (name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetPredefinedArmsPoses-request>) ostream)
  "Serializes a message object of type '<GetPredefinedArmsPoses-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetPredefinedArmsPoses-request>) istream)
  "Deserializes a message object of type '<GetPredefinedArmsPoses-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetPredefinedArmsPoses-request>)))
  "Returns string type for a service object of type '<GetPredefinedArmsPoses-request>"
  "knowledge_msgs/GetPredefinedArmsPosesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPredefinedArmsPoses-request)))
  "Returns string type for a service object of type 'GetPredefinedArmsPoses-request"
  "knowledge_msgs/GetPredefinedArmsPosesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetPredefinedArmsPoses-request>)))
  "Returns md5sum for a message object of type '<GetPredefinedArmsPoses-request>"
  "5f93696d26db52709ee264c439d53838")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetPredefinedArmsPoses-request)))
  "Returns md5sum for a message object of type 'GetPredefinedArmsPoses-request"
  "5f93696d26db52709ee264c439d53838")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetPredefinedArmsPoses-request>)))
  "Returns full string definition for message of type '<GetPredefinedArmsPoses-request>"
  (cl:format cl:nil "string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetPredefinedArmsPoses-request)))
  "Returns full string definition for message of type 'GetPredefinedArmsPoses-request"
  (cl:format cl:nil "string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetPredefinedArmsPoses-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetPredefinedArmsPoses-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetPredefinedArmsPoses-request
    (cl:cons ':name (name msg))
))
;//! \htmlinclude GetPredefinedArmsPoses-response.msg.html

(cl:defclass <GetPredefinedArmsPoses-response> (roslisp-msg-protocol:ros-message)
  ((angles
    :reader angles
    :initarg :angles
    :type (cl:vector std_msgs-msg:Float32)
   :initform (cl:make-array 0 :element-type 'std_msgs-msg:Float32 :initial-element (cl:make-instance 'std_msgs-msg:Float32))))
)

(cl:defclass GetPredefinedArmsPoses-response (<GetPredefinedArmsPoses-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetPredefinedArmsPoses-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetPredefinedArmsPoses-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<GetPredefinedArmsPoses-response> is deprecated: use knowledge_msgs-srv:GetPredefinedArmsPoses-response instead.")))

(cl:ensure-generic-function 'angles-val :lambda-list '(m))
(cl:defmethod angles-val ((m <GetPredefinedArmsPoses-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:angles-val is deprecated.  Use knowledge_msgs-srv:angles instead.")
  (angles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetPredefinedArmsPoses-response>) ostream)
  "Serializes a message object of type '<GetPredefinedArmsPoses-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'angles))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'angles))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetPredefinedArmsPoses-response>) istream)
  "Deserializes a message object of type '<GetPredefinedArmsPoses-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'angles) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'angles)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:Float32))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetPredefinedArmsPoses-response>)))
  "Returns string type for a service object of type '<GetPredefinedArmsPoses-response>"
  "knowledge_msgs/GetPredefinedArmsPosesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPredefinedArmsPoses-response)))
  "Returns string type for a service object of type 'GetPredefinedArmsPoses-response"
  "knowledge_msgs/GetPredefinedArmsPosesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetPredefinedArmsPoses-response>)))
  "Returns md5sum for a message object of type '<GetPredefinedArmsPoses-response>"
  "5f93696d26db52709ee264c439d53838")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetPredefinedArmsPoses-response)))
  "Returns md5sum for a message object of type 'GetPredefinedArmsPoses-response"
  "5f93696d26db52709ee264c439d53838")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetPredefinedArmsPoses-response>)))
  "Returns full string definition for message of type '<GetPredefinedArmsPoses-response>"
  (cl:format cl:nil "std_msgs/Float32[] angles~%~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetPredefinedArmsPoses-response)))
  "Returns full string definition for message of type 'GetPredefinedArmsPoses-response"
  (cl:format cl:nil "std_msgs/Float32[] angles~%~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetPredefinedArmsPoses-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'angles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetPredefinedArmsPoses-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetPredefinedArmsPoses-response
    (cl:cons ':angles (angles msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetPredefinedArmsPoses)))
  'GetPredefinedArmsPoses-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetPredefinedArmsPoses)))
  'GetPredefinedArmsPoses-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPredefinedArmsPoses)))
  "Returns string type for a service object of type '<GetPredefinedArmsPoses>"
  "knowledge_msgs/GetPredefinedArmsPoses")