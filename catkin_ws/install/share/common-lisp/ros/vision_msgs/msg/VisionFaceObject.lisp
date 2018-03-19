; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude VisionFaceObject.msg.html

(cl:defclass <VisionFaceObject> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:string
    :initform "")
   (confidence
    :reader confidence
    :initarg :confidence
    :type cl:float
    :initform 0.0)
   (face_centroid
    :reader face_centroid
    :initarg :face_centroid
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (bounding_box
    :reader bounding_box
    :initarg :bounding_box
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (smile
    :reader smile
    :initarg :smile
    :type cl:boolean
    :initform cl:nil)
   (gender
    :reader gender
    :initarg :gender
    :type cl:fixnum
    :initform 0))
)

(cl:defclass VisionFaceObject (<VisionFaceObject>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VisionFaceObject>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VisionFaceObject)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<VisionFaceObject> is deprecated: use vision_msgs-msg:VisionFaceObject instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <VisionFaceObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:id-val is deprecated.  Use vision_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'confidence-val :lambda-list '(m))
(cl:defmethod confidence-val ((m <VisionFaceObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:confidence-val is deprecated.  Use vision_msgs-msg:confidence instead.")
  (confidence m))

(cl:ensure-generic-function 'face_centroid-val :lambda-list '(m))
(cl:defmethod face_centroid-val ((m <VisionFaceObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:face_centroid-val is deprecated.  Use vision_msgs-msg:face_centroid instead.")
  (face_centroid m))

(cl:ensure-generic-function 'bounding_box-val :lambda-list '(m))
(cl:defmethod bounding_box-val ((m <VisionFaceObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:bounding_box-val is deprecated.  Use vision_msgs-msg:bounding_box instead.")
  (bounding_box m))

(cl:ensure-generic-function 'smile-val :lambda-list '(m))
(cl:defmethod smile-val ((m <VisionFaceObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:smile-val is deprecated.  Use vision_msgs-msg:smile instead.")
  (smile m))

(cl:ensure-generic-function 'gender-val :lambda-list '(m))
(cl:defmethod gender-val ((m <VisionFaceObject>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:gender-val is deprecated.  Use vision_msgs-msg:gender instead.")
  (gender m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VisionFaceObject>) ostream)
  "Serializes a message object of type '<VisionFaceObject>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'id))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'confidence))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'face_centroid) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'bounding_box))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'bounding_box))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'smile) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'gender)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VisionFaceObject>) istream)
  "Deserializes a message object of type '<VisionFaceObject>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'confidence) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'face_centroid) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'bounding_box) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'bounding_box)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:setf (cl:slot-value msg 'smile) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gender) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VisionFaceObject>)))
  "Returns string type for a message object of type '<VisionFaceObject>"
  "vision_msgs/VisionFaceObject")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VisionFaceObject)))
  "Returns string type for a message object of type 'VisionFaceObject"
  "vision_msgs/VisionFaceObject")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VisionFaceObject>)))
  "Returns md5sum for a message object of type '<VisionFaceObject>"
  "93b90fa2697ed03b7e1dd7001e2d8cff")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VisionFaceObject)))
  "Returns md5sum for a message object of type 'VisionFaceObject"
  "93b90fa2697ed03b7e1dd7001e2d8cff")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VisionFaceObject>)))
  "Returns full string definition for message of type '<VisionFaceObject>"
  (cl:format cl:nil "string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VisionFaceObject)))
  "Returns full string definition for message of type 'VisionFaceObject"
  (cl:format cl:nil "string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VisionFaceObject>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'id))
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'face_centroid))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'bounding_box) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VisionFaceObject>))
  "Converts a ROS message object to a list"
  (cl:list 'VisionFaceObject
    (cl:cons ':id (id msg))
    (cl:cons ':confidence (confidence msg))
    (cl:cons ':face_centroid (face_centroid msg))
    (cl:cons ':bounding_box (bounding_box msg))
    (cl:cons ':smile (smile msg))
    (cl:cons ':gender (gender msg))
))
