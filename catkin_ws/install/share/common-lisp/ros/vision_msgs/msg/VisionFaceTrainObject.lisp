; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude VisionFaceTrainObject.msg.html

(cl:defclass <VisionFaceTrainObject> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:string
    :initform "")
   (frames
    :reader frames
    :initarg :frames
    :type cl:integer
    :initform 0))
)

(cl:defclass VisionFaceTrainObject (<VisionFaceTrainObject>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VisionFaceTrainObject>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VisionFaceTrainObject)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<VisionFaceTrainObject> is deprecated: use vision_msgs-msg:VisionFaceTrainObject instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <VisionFaceTrainObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:id-val is deprecated.  Use vision_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'frames-val :lambda-list '(m))
(cl:defmethod frames-val ((m <VisionFaceTrainObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:frames-val is deprecated.  Use vision_msgs-msg:frames instead.")
  (frames m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VisionFaceTrainObject>) ostream)
  "Serializes a message object of type '<VisionFaceTrainObject>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'id))
  (cl:let* ((signed (cl:slot-value msg 'frames)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VisionFaceTrainObject>) istream)
  "Deserializes a message object of type '<VisionFaceTrainObject>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frames) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VisionFaceTrainObject>)))
  "Returns string type for a message object of type '<VisionFaceTrainObject>"
  "vision_msgs/VisionFaceTrainObject")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VisionFaceTrainObject)))
  "Returns string type for a message object of type 'VisionFaceTrainObject"
  "vision_msgs/VisionFaceTrainObject")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VisionFaceTrainObject>)))
  "Returns md5sum for a message object of type '<VisionFaceTrainObject>"
  "b3e8e25fcbb0fb9e09f30fa7d99356d3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VisionFaceTrainObject)))
  "Returns md5sum for a message object of type 'VisionFaceTrainObject"
  "b3e8e25fcbb0fb9e09f30fa7d99356d3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VisionFaceTrainObject>)))
  "Returns full string definition for message of type '<VisionFaceTrainObject>"
  (cl:format cl:nil "string id                                    #face id~%int32 frames                                 #Number of frames to train~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VisionFaceTrainObject)))
  "Returns full string definition for message of type 'VisionFaceTrainObject"
  (cl:format cl:nil "string id                                    #face id~%int32 frames                                 #Number of frames to train~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VisionFaceTrainObject>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'id))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VisionFaceTrainObject>))
  "Converts a ROS message object to a list"
  (cl:list 'VisionFaceTrainObject
    (cl:cons ':id (id msg))
    (cl:cons ':frames (frames msg))
))
