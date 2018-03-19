; Auto-generated. Do not edit!


(cl:in-package sp_rec-srv)


;//! \htmlinclude ActivateDictionaries-request.msg.html

(cl:defclass <ActivateDictionaries-request> (roslisp-msg-protocol:ros-message)
  ((names
    :reader names
    :initarg :names
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element ""))
   (active
    :reader active
    :initarg :active
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass ActivateDictionaries-request (<ActivateDictionaries-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ActivateDictionaries-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ActivateDictionaries-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sp_rec-srv:<ActivateDictionaries-request> is deprecated: use sp_rec-srv:ActivateDictionaries-request instead.")))

(cl:ensure-generic-function 'names-val :lambda-list '(m))
(cl:defmethod names-val ((m <ActivateDictionaries-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sp_rec-srv:names-val is deprecated.  Use sp_rec-srv:names instead.")
  (names m))

(cl:ensure-generic-function 'active-val :lambda-list '(m))
(cl:defmethod active-val ((m <ActivateDictionaries-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sp_rec-srv:active-val is deprecated.  Use sp_rec-srv:active instead.")
  (active m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ActivateDictionaries-request>) ostream)
  "Serializes a message object of type '<ActivateDictionaries-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'names))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'names))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'active) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ActivateDictionaries-request>) istream)
  "Deserializes a message object of type '<ActivateDictionaries-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'names) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'names)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
    (cl:setf (cl:slot-value msg 'active) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ActivateDictionaries-request>)))
  "Returns string type for a service object of type '<ActivateDictionaries-request>"
  "sp_rec/ActivateDictionariesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ActivateDictionaries-request)))
  "Returns string type for a service object of type 'ActivateDictionaries-request"
  "sp_rec/ActivateDictionariesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ActivateDictionaries-request>)))
  "Returns md5sum for a message object of type '<ActivateDictionaries-request>"
  "76e09ccff84329f0f31723b25e6297e8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ActivateDictionaries-request)))
  "Returns md5sum for a message object of type 'ActivateDictionaries-request"
  "76e09ccff84329f0f31723b25e6297e8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ActivateDictionaries-request>)))
  "Returns full string definition for message of type '<ActivateDictionaries-request>"
  (cl:format cl:nil "~%string[] names~%~%~%bool active~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ActivateDictionaries-request)))
  "Returns full string definition for message of type 'ActivateDictionaries-request"
  (cl:format cl:nil "~%string[] names~%~%~%bool active~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ActivateDictionaries-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'names) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ActivateDictionaries-request>))
  "Converts a ROS message object to a list"
  (cl:list 'ActivateDictionaries-request
    (cl:cons ':names (names msg))
    (cl:cons ':active (active msg))
))
;//! \htmlinclude ActivateDictionaries-response.msg.html

(cl:defclass <ActivateDictionaries-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:boolean
    :initform cl:nil)
   (message
    :reader message
    :initarg :message
    :type cl:string
    :initform ""))
)

(cl:defclass ActivateDictionaries-response (<ActivateDictionaries-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ActivateDictionaries-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ActivateDictionaries-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sp_rec-srv:<ActivateDictionaries-response> is deprecated: use sp_rec-srv:ActivateDictionaries-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <ActivateDictionaries-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sp_rec-srv:result-val is deprecated.  Use sp_rec-srv:result instead.")
  (result m))

(cl:ensure-generic-function 'message-val :lambda-list '(m))
(cl:defmethod message-val ((m <ActivateDictionaries-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sp_rec-srv:message-val is deprecated.  Use sp_rec-srv:message instead.")
  (message m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ActivateDictionaries-response>) ostream)
  "Serializes a message object of type '<ActivateDictionaries-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'result) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ActivateDictionaries-response>) istream)
  "Deserializes a message object of type '<ActivateDictionaries-response>"
    (cl:setf (cl:slot-value msg 'result) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ActivateDictionaries-response>)))
  "Returns string type for a service object of type '<ActivateDictionaries-response>"
  "sp_rec/ActivateDictionariesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ActivateDictionaries-response)))
  "Returns string type for a service object of type 'ActivateDictionaries-response"
  "sp_rec/ActivateDictionariesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ActivateDictionaries-response>)))
  "Returns md5sum for a message object of type '<ActivateDictionaries-response>"
  "76e09ccff84329f0f31723b25e6297e8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ActivateDictionaries-response)))
  "Returns md5sum for a message object of type 'ActivateDictionaries-response"
  "76e09ccff84329f0f31723b25e6297e8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ActivateDictionaries-response>)))
  "Returns full string definition for message of type '<ActivateDictionaries-response>"
  (cl:format cl:nil "~%~%bool result~%~%~%string message~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ActivateDictionaries-response)))
  "Returns full string definition for message of type 'ActivateDictionaries-response"
  (cl:format cl:nil "~%~%bool result~%~%~%string message~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ActivateDictionaries-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'message))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ActivateDictionaries-response>))
  "Converts a ROS message object to a list"
  (cl:list 'ActivateDictionaries-response
    (cl:cons ':result (result msg))
    (cl:cons ':message (message msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'ActivateDictionaries)))
  'ActivateDictionaries-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'ActivateDictionaries)))
  'ActivateDictionaries-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ActivateDictionaries)))
  "Returns string type for a service object of type '<ActivateDictionaries>"
  "sp_rec/ActivateDictionaries")