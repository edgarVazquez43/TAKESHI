; Auto-generated. Do not edit!


(cl:in-package hri_msgs-msg)


;//! \htmlinclude RecognitionResult.msg.html

(cl:defclass <RecognitionResult> (roslisp-msg-protocol:ros-message)
  ((sentences
    :reader sentences
    :initarg :sentences
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element ""))
   (scores
    :reader scores
    :initarg :scores
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass RecognitionResult (<RecognitionResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RecognitionResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RecognitionResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hri_msgs-msg:<RecognitionResult> is deprecated: use hri_msgs-msg:RecognitionResult instead.")))

(cl:ensure-generic-function 'sentences-val :lambda-list '(m))
(cl:defmethod sentences-val ((m <RecognitionResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hri_msgs-msg:sentences-val is deprecated.  Use hri_msgs-msg:sentences instead.")
  (sentences m))

(cl:ensure-generic-function 'scores-val :lambda-list '(m))
(cl:defmethod scores-val ((m <RecognitionResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hri_msgs-msg:scores-val is deprecated.  Use hri_msgs-msg:scores instead.")
  (scores m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RecognitionResult>) ostream)
  "Serializes a message object of type '<RecognitionResult>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'sentences))))
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
   (cl:slot-value msg 'sentences))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'scores))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'scores))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RecognitionResult>) istream)
  "Deserializes a message object of type '<RecognitionResult>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'sentences) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'sentences)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'scores) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'scores)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RecognitionResult>)))
  "Returns string type for a message object of type '<RecognitionResult>"
  "hri_msgs/RecognitionResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RecognitionResult)))
  "Returns string type for a message object of type 'RecognitionResult"
  "hri_msgs/RecognitionResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RecognitionResult>)))
  "Returns md5sum for a message object of type '<RecognitionResult>"
  "f96b075bcd484621907ceed990cf074d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RecognitionResult)))
  "Returns md5sum for a message object of type 'RecognitionResult"
  "f96b075bcd484621907ceed990cf074d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RecognitionResult>)))
  "Returns full string definition for message of type '<RecognitionResult>"
  (cl:format cl:nil "string[] sentences~%float64[] scores~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RecognitionResult)))
  "Returns full string definition for message of type 'RecognitionResult"
  (cl:format cl:nil "string[] sentences~%float64[] scores~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RecognitionResult>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'sentences) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'scores) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RecognitionResult>))
  "Converts a ROS message object to a list"
  (cl:list 'RecognitionResult
    (cl:cons ':sentences (sentences msg))
    (cl:cons ':scores (scores msg))
))
