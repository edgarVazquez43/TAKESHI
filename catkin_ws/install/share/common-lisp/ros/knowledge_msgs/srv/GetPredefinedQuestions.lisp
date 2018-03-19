; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude GetPredefinedQuestions-request.msg.html

(cl:defclass <GetPredefinedQuestions-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass GetPredefinedQuestions-request (<GetPredefinedQuestions-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetPredefinedQuestions-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetPredefinedQuestions-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<GetPredefinedQuestions-request> is deprecated: use knowledge_msgs-srv:GetPredefinedQuestions-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetPredefinedQuestions-request>) ostream)
  "Serializes a message object of type '<GetPredefinedQuestions-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetPredefinedQuestions-request>) istream)
  "Deserializes a message object of type '<GetPredefinedQuestions-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetPredefinedQuestions-request>)))
  "Returns string type for a service object of type '<GetPredefinedQuestions-request>"
  "knowledge_msgs/GetPredefinedQuestionsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPredefinedQuestions-request)))
  "Returns string type for a service object of type 'GetPredefinedQuestions-request"
  "knowledge_msgs/GetPredefinedQuestionsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetPredefinedQuestions-request>)))
  "Returns md5sum for a message object of type '<GetPredefinedQuestions-request>"
  "68d94395b4ec7b52f8954f4e6ebf72fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetPredefinedQuestions-request)))
  "Returns md5sum for a message object of type 'GetPredefinedQuestions-request"
  "68d94395b4ec7b52f8954f4e6ebf72fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetPredefinedQuestions-request>)))
  "Returns full string definition for message of type '<GetPredefinedQuestions-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetPredefinedQuestions-request)))
  "Returns full string definition for message of type 'GetPredefinedQuestions-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetPredefinedQuestions-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetPredefinedQuestions-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetPredefinedQuestions-request
))
;//! \htmlinclude GetPredefinedQuestions-response.msg.html

(cl:defclass <GetPredefinedQuestions-response> (roslisp-msg-protocol:ros-message)
  ((predefinedQuestions
    :reader predefinedQuestions
    :initarg :predefinedQuestions
    :type (cl:vector knowledge_msgs-msg:MapPredefinedQuestions)
   :initform (cl:make-array 0 :element-type 'knowledge_msgs-msg:MapPredefinedQuestions :initial-element (cl:make-instance 'knowledge_msgs-msg:MapPredefinedQuestions))))
)

(cl:defclass GetPredefinedQuestions-response (<GetPredefinedQuestions-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetPredefinedQuestions-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetPredefinedQuestions-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<GetPredefinedQuestions-response> is deprecated: use knowledge_msgs-srv:GetPredefinedQuestions-response instead.")))

(cl:ensure-generic-function 'predefinedQuestions-val :lambda-list '(m))
(cl:defmethod predefinedQuestions-val ((m <GetPredefinedQuestions-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:predefinedQuestions-val is deprecated.  Use knowledge_msgs-srv:predefinedQuestions instead.")
  (predefinedQuestions m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetPredefinedQuestions-response>) ostream)
  "Serializes a message object of type '<GetPredefinedQuestions-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'predefinedQuestions))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'predefinedQuestions))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetPredefinedQuestions-response>) istream)
  "Deserializes a message object of type '<GetPredefinedQuestions-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'predefinedQuestions) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'predefinedQuestions)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'knowledge_msgs-msg:MapPredefinedQuestions))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetPredefinedQuestions-response>)))
  "Returns string type for a service object of type '<GetPredefinedQuestions-response>"
  "knowledge_msgs/GetPredefinedQuestionsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPredefinedQuestions-response)))
  "Returns string type for a service object of type 'GetPredefinedQuestions-response"
  "knowledge_msgs/GetPredefinedQuestionsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetPredefinedQuestions-response>)))
  "Returns md5sum for a message object of type '<GetPredefinedQuestions-response>"
  "68d94395b4ec7b52f8954f4e6ebf72fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetPredefinedQuestions-response)))
  "Returns md5sum for a message object of type 'GetPredefinedQuestions-response"
  "68d94395b4ec7b52f8954f4e6ebf72fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetPredefinedQuestions-response>)))
  "Returns full string definition for message of type '<GetPredefinedQuestions-response>"
  (cl:format cl:nil "MapPredefinedQuestions[] predefinedQuestions~%~%~%================================================================================~%MSG: knowledge_msgs/MapPredefinedQuestions~%string question~%string answer~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetPredefinedQuestions-response)))
  "Returns full string definition for message of type 'GetPredefinedQuestions-response"
  (cl:format cl:nil "MapPredefinedQuestions[] predefinedQuestions~%~%~%================================================================================~%MSG: knowledge_msgs/MapPredefinedQuestions~%string question~%string answer~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetPredefinedQuestions-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'predefinedQuestions) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetPredefinedQuestions-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetPredefinedQuestions-response
    (cl:cons ':predefinedQuestions (predefinedQuestions msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetPredefinedQuestions)))
  'GetPredefinedQuestions-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetPredefinedQuestions)))
  'GetPredefinedQuestions-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPredefinedQuestions)))
  "Returns string type for a service object of type '<GetPredefinedQuestions>"
  "knowledge_msgs/GetPredefinedQuestions")