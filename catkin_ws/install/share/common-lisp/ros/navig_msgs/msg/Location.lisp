; Auto-generated. Do not edit!


(cl:in-package navig_msgs-msg)


;//! \htmlinclude Location.msg.html

(cl:defclass <Location> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:string
    :initform "")
   (position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (orientation
    :reader orientation
    :initarg :orientation
    :type cl:float
    :initform 0.0)
   (correct_angle
    :reader correct_angle
    :initarg :correct_angle
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Location (<Location>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Location>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Location)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name navig_msgs-msg:<Location> is deprecated: use navig_msgs-msg:Location instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <Location>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-msg:id-val is deprecated.  Use navig_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <Location>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-msg:position-val is deprecated.  Use navig_msgs-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <Location>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-msg:orientation-val is deprecated.  Use navig_msgs-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'correct_angle-val :lambda-list '(m))
(cl:defmethod correct_angle-val ((m <Location>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader navig_msgs-msg:correct_angle-val is deprecated.  Use navig_msgs-msg:correct_angle instead.")
  (correct_angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Location>) ostream)
  "Serializes a message object of type '<Location>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'id))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'orientation))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'correct_angle) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Location>) istream)
  "Deserializes a message object of type '<Location>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'orientation) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'correct_angle) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Location>)))
  "Returns string type for a message object of type '<Location>"
  "navig_msgs/Location")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Location)))
  "Returns string type for a message object of type 'Location"
  "navig_msgs/Location")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Location>)))
  "Returns md5sum for a message object of type '<Location>"
  "89fc57037e6b4762351eee5641dad2f8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Location)))
  "Returns md5sum for a message object of type 'Location"
  "89fc57037e6b4762351eee5641dad2f8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Location>)))
  "Returns full string definition for message of type '<Location>"
  (cl:format cl:nil "string id~%geometry_msgs/Point position~%float32 orientation~%bool correct_angle~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Location)))
  "Returns full string definition for message of type 'Location"
  (cl:format cl:nil "string id~%geometry_msgs/Point position~%float32 orientation~%bool correct_angle~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Location>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'id))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Location>))
  "Converts a ROS message object to a list"
  (cl:list 'Location
    (cl:cons ':id (id msg))
    (cl:cons ':position (position msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':correct_angle (correct_angle msg))
))
