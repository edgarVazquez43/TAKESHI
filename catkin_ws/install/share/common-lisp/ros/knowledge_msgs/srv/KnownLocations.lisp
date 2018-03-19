; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude KnownLocations-request.msg.html

(cl:defclass <KnownLocations-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass KnownLocations-request (<KnownLocations-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <KnownLocations-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'KnownLocations-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<KnownLocations-request> is deprecated: use knowledge_msgs-srv:KnownLocations-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <KnownLocations-request>) ostream)
  "Serializes a message object of type '<KnownLocations-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <KnownLocations-request>) istream)
  "Deserializes a message object of type '<KnownLocations-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<KnownLocations-request>)))
  "Returns string type for a service object of type '<KnownLocations-request>"
  "knowledge_msgs/KnownLocationsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'KnownLocations-request)))
  "Returns string type for a service object of type 'KnownLocations-request"
  "knowledge_msgs/KnownLocationsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<KnownLocations-request>)))
  "Returns md5sum for a message object of type '<KnownLocations-request>"
  "6bd6e203855e6403b9f65224e511af1a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'KnownLocations-request)))
  "Returns md5sum for a message object of type 'KnownLocations-request"
  "6bd6e203855e6403b9f65224e511af1a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<KnownLocations-request>)))
  "Returns full string definition for message of type '<KnownLocations-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'KnownLocations-request)))
  "Returns full string definition for message of type 'KnownLocations-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <KnownLocations-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <KnownLocations-request>))
  "Converts a ROS message object to a list"
  (cl:list 'KnownLocations-request
))
;//! \htmlinclude KnownLocations-response.msg.html

(cl:defclass <KnownLocations-response> (roslisp-msg-protocol:ros-message)
  ((locations
    :reader locations
    :initarg :locations
    :type (cl:vector knowledge_msgs-msg:MapKnownLocation)
   :initform (cl:make-array 0 :element-type 'knowledge_msgs-msg:MapKnownLocation :initial-element (cl:make-instance 'knowledge_msgs-msg:MapKnownLocation))))
)

(cl:defclass KnownLocations-response (<KnownLocations-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <KnownLocations-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'KnownLocations-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<KnownLocations-response> is deprecated: use knowledge_msgs-srv:KnownLocations-response instead.")))

(cl:ensure-generic-function 'locations-val :lambda-list '(m))
(cl:defmethod locations-val ((m <KnownLocations-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:locations-val is deprecated.  Use knowledge_msgs-srv:locations instead.")
  (locations m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <KnownLocations-response>) ostream)
  "Serializes a message object of type '<KnownLocations-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'locations))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'locations))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <KnownLocations-response>) istream)
  "Deserializes a message object of type '<KnownLocations-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'locations) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'locations)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'knowledge_msgs-msg:MapKnownLocation))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<KnownLocations-response>)))
  "Returns string type for a service object of type '<KnownLocations-response>"
  "knowledge_msgs/KnownLocationsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'KnownLocations-response)))
  "Returns string type for a service object of type 'KnownLocations-response"
  "knowledge_msgs/KnownLocationsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<KnownLocations-response>)))
  "Returns md5sum for a message object of type '<KnownLocations-response>"
  "6bd6e203855e6403b9f65224e511af1a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'KnownLocations-response)))
  "Returns md5sum for a message object of type 'KnownLocations-response"
  "6bd6e203855e6403b9f65224e511af1a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<KnownLocations-response>)))
  "Returns full string definition for message of type '<KnownLocations-response>"
  (cl:format cl:nil "MapKnownLocation[] locations~%~%~%================================================================================~%MSG: knowledge_msgs/MapKnownLocation~%string name~%float32[] value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'KnownLocations-response)))
  "Returns full string definition for message of type 'KnownLocations-response"
  (cl:format cl:nil "MapKnownLocation[] locations~%~%~%================================================================================~%MSG: knowledge_msgs/MapKnownLocation~%string name~%float32[] value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <KnownLocations-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'locations) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <KnownLocations-response>))
  "Converts a ROS message object to a list"
  (cl:list 'KnownLocations-response
    (cl:cons ':locations (locations msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'KnownLocations)))
  'KnownLocations-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'KnownLocations)))
  'KnownLocations-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'KnownLocations)))
  "Returns string type for a service object of type '<KnownLocations>"
  "knowledge_msgs/KnownLocations")