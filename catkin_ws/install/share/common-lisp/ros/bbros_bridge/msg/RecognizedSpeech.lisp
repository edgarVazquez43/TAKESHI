; Auto-generated. Do not edit!


(cl:in-package bbros_bridge-msg)


;//! \htmlinclude RecognizedSpeech.msg.html

(cl:defclass <RecognizedSpeech> (roslisp-msg-protocol:ros-message)
  ((hypothesis
    :reader hypothesis
    :initarg :hypothesis
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element ""))
   (confidences
    :reader confidences
    :initarg :confidences
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass RecognizedSpeech (<RecognizedSpeech>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RecognizedSpeech>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RecognizedSpeech)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bbros_bridge-msg:<RecognizedSpeech> is deprecated: use bbros_bridge-msg:RecognizedSpeech instead.")))

(cl:ensure-generic-function 'hypothesis-val :lambda-list '(m))
(cl:defmethod hypothesis-val ((m <RecognizedSpeech>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-msg:hypothesis-val is deprecated.  Use bbros_bridge-msg:hypothesis instead.")
  (hypothesis m))

(cl:ensure-generic-function 'confidences-val :lambda-list '(m))
(cl:defmethod confidences-val ((m <RecognizedSpeech>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bbros_bridge-msg:confidences-val is deprecated.  Use bbros_bridge-msg:confidences instead.")
  (confidences m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RecognizedSpeech>) ostream)
  "Serializes a message object of type '<RecognizedSpeech>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'hypothesis))))
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
   (cl:slot-value msg 'hypothesis))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'confidences))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'confidences))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RecognizedSpeech>) istream)
  "Deserializes a message object of type '<RecognizedSpeech>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'hypothesis) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'hypothesis)))
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
  (cl:setf (cl:slot-value msg 'confidences) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'confidences)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RecognizedSpeech>)))
  "Returns string type for a message object of type '<RecognizedSpeech>"
  "bbros_bridge/RecognizedSpeech")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RecognizedSpeech)))
  "Returns string type for a message object of type 'RecognizedSpeech"
  "bbros_bridge/RecognizedSpeech")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RecognizedSpeech>)))
  "Returns md5sum for a message object of type '<RecognizedSpeech>"
  "b2cc166e4fd867bfc13e04afeee883be")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RecognizedSpeech)))
  "Returns md5sum for a message object of type 'RecognizedSpeech"
  "b2cc166e4fd867bfc13e04afeee883be")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RecognizedSpeech>)))
  "Returns full string definition for message of type '<RecognizedSpeech>"
  (cl:format cl:nil "string[] hypothesis~%float32[] confidences~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RecognizedSpeech)))
  "Returns full string definition for message of type 'RecognizedSpeech"
  (cl:format cl:nil "string[] hypothesis~%float32[] confidences~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RecognizedSpeech>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'hypothesis) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'confidences) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RecognizedSpeech>))
  "Converts a ROS message object to a list"
  (cl:list 'RecognizedSpeech
    (cl:cons ':hypothesis (hypothesis msg))
    (cl:cons ':confidences (confidences msg))
))
