; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude GestureSkeleton.msg.html

(cl:defclass <GestureSkeleton> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (gesture
    :reader gesture
    :initarg :gesture
    :type cl:string
    :initform "")
   (gesture_centroid
    :reader gesture_centroid
    :initarg :gesture_centroid
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass GestureSkeleton (<GestureSkeleton>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GestureSkeleton>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GestureSkeleton)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<GestureSkeleton> is deprecated: use vision_msgs-msg:GestureSkeleton instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <GestureSkeleton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:id-val is deprecated.  Use vision_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'gesture-val :lambda-list '(m))
(cl:defmethod gesture-val ((m <GestureSkeleton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:gesture-val is deprecated.  Use vision_msgs-msg:gesture instead.")
  (gesture m))

(cl:ensure-generic-function 'gesture_centroid-val :lambda-list '(m))
(cl:defmethod gesture_centroid-val ((m <GestureSkeleton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:gesture_centroid-val is deprecated.  Use vision_msgs-msg:gesture_centroid instead.")
  (gesture_centroid m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GestureSkeleton>) ostream)
  "Serializes a message object of type '<GestureSkeleton>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'gesture))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'gesture))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gesture_centroid) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GestureSkeleton>) istream)
  "Deserializes a message object of type '<GestureSkeleton>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gesture) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'gesture) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gesture_centroid) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GestureSkeleton>)))
  "Returns string type for a message object of type '<GestureSkeleton>"
  "vision_msgs/GestureSkeleton")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GestureSkeleton)))
  "Returns string type for a message object of type 'GestureSkeleton"
  "vision_msgs/GestureSkeleton")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GestureSkeleton>)))
  "Returns md5sum for a message object of type '<GestureSkeleton>"
  "1e87d31b651e197f45459ceb0c0353fb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GestureSkeleton)))
  "Returns md5sum for a message object of type 'GestureSkeleton"
  "1e87d31b651e197f45459ceb0c0353fb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GestureSkeleton>)))
  "Returns full string definition for message of type '<GestureSkeleton>"
  (cl:format cl:nil "int8 id		#id of user~%string gesture		#gesture of user~%geometry_msgs/Point gesture_centroid		#Gesture Centroid (x,y,z)~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GestureSkeleton)))
  "Returns full string definition for message of type 'GestureSkeleton"
  (cl:format cl:nil "int8 id		#id of user~%string gesture		#gesture of user~%geometry_msgs/Point gesture_centroid		#Gesture Centroid (x,y,z)~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GestureSkeleton>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'gesture))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gesture_centroid))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GestureSkeleton>))
  "Converts a ROS message object to a list"
  (cl:list 'GestureSkeleton
    (cl:cons ':id (id msg))
    (cl:cons ':gesture (gesture msg))
    (cl:cons ':gesture_centroid (gesture_centroid msg))
))
