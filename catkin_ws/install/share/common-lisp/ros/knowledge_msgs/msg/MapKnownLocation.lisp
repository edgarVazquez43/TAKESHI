; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-msg)


;//! \htmlinclude MapKnownLocation.msg.html

(cl:defclass <MapKnownLocation> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (value
    :reader value
    :initarg :value
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass MapKnownLocation (<MapKnownLocation>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MapKnownLocation>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MapKnownLocation)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-msg:<MapKnownLocation> is deprecated: use knowledge_msgs-msg:MapKnownLocation instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <MapKnownLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:name-val is deprecated.  Use knowledge_msgs-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <MapKnownLocation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-msg:value-val is deprecated.  Use knowledge_msgs-msg:value instead.")
  (value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MapKnownLocation>) ostream)
  "Serializes a message object of type '<MapKnownLocation>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'value))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MapKnownLocation>) istream)
  "Deserializes a message object of type '<MapKnownLocation>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'value) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'value)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MapKnownLocation>)))
  "Returns string type for a message object of type '<MapKnownLocation>"
  "knowledge_msgs/MapKnownLocation")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MapKnownLocation)))
  "Returns string type for a message object of type 'MapKnownLocation"
  "knowledge_msgs/MapKnownLocation")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MapKnownLocation>)))
  "Returns md5sum for a message object of type '<MapKnownLocation>"
  "8b31cd087b52c8acca2d7bf6ae29aeab")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MapKnownLocation)))
  "Returns md5sum for a message object of type 'MapKnownLocation"
  "8b31cd087b52c8acca2d7bf6ae29aeab")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MapKnownLocation>)))
  "Returns full string definition for message of type '<MapKnownLocation>"
  (cl:format cl:nil "string name~%float32[] value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MapKnownLocation)))
  "Returns full string definition for message of type 'MapKnownLocation"
  (cl:format cl:nil "string name~%float32[] value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MapKnownLocation>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'value) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MapKnownLocation>))
  "Converts a ROS message object to a list"
  (cl:list 'MapKnownLocation
    (cl:cons ':name (name msg))
    (cl:cons ':value (value msg))
))
