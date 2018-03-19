; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude Cube.msg.html

(cl:defclass <Cube> (roslisp-msg-protocol:ros-message)
  ((color
    :reader color
    :initarg :color
    :type cl:string
    :initform "")
   (cube_centroid
    :reader cube_centroid
    :initarg :cube_centroid
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (detected_cube
    :reader detected_cube
    :initarg :detected_cube
    :type cl:boolean
    :initform cl:nil)
   (minPoint
    :reader minPoint
    :initarg :minPoint
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (maxPoint
    :reader maxPoint
    :initarg :maxPoint
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass Cube (<Cube>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Cube>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Cube)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<Cube> is deprecated: use vision_msgs-msg:Cube instead.")))

(cl:ensure-generic-function 'color-val :lambda-list '(m))
(cl:defmethod color-val ((m <Cube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:color-val is deprecated.  Use vision_msgs-msg:color instead.")
  (color m))

(cl:ensure-generic-function 'cube_centroid-val :lambda-list '(m))
(cl:defmethod cube_centroid-val ((m <Cube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:cube_centroid-val is deprecated.  Use vision_msgs-msg:cube_centroid instead.")
  (cube_centroid m))

(cl:ensure-generic-function 'detected_cube-val :lambda-list '(m))
(cl:defmethod detected_cube-val ((m <Cube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:detected_cube-val is deprecated.  Use vision_msgs-msg:detected_cube instead.")
  (detected_cube m))

(cl:ensure-generic-function 'minPoint-val :lambda-list '(m))
(cl:defmethod minPoint-val ((m <Cube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:minPoint-val is deprecated.  Use vision_msgs-msg:minPoint instead.")
  (minPoint m))

(cl:ensure-generic-function 'maxPoint-val :lambda-list '(m))
(cl:defmethod maxPoint-val ((m <Cube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:maxPoint-val is deprecated.  Use vision_msgs-msg:maxPoint instead.")
  (maxPoint m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Cube>) ostream)
  "Serializes a message object of type '<Cube>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'color))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'color))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cube_centroid) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'detected_cube) 1 0)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'minPoint) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'maxPoint) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Cube>) istream)
  "Deserializes a message object of type '<Cube>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'color) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'color) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cube_centroid) istream)
    (cl:setf (cl:slot-value msg 'detected_cube) (cl:not (cl:zerop (cl:read-byte istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'minPoint) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'maxPoint) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Cube>)))
  "Returns string type for a message object of type '<Cube>"
  "vision_msgs/Cube")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Cube)))
  "Returns string type for a message object of type 'Cube"
  "vision_msgs/Cube")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Cube>)))
  "Returns md5sum for a message object of type '<Cube>"
  "7208e2d20370e447988b77d98e81081d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Cube)))
  "Returns md5sum for a message object of type 'Cube"
  "7208e2d20370e447988b77d98e81081d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Cube>)))
  "Returns full string definition for message of type '<Cube>"
  (cl:format cl:nil "string color #color of the cube~%geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)~%bool detected_cube    #flag to indicate if the cube was detected~%geometry_msgs/Point minPoint	#Cube's min point~%geometry_msgs/Point maxPoint	#Cube's max point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Cube)))
  "Returns full string definition for message of type 'Cube"
  (cl:format cl:nil "string color #color of the cube~%geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)~%bool detected_cube    #flag to indicate if the cube was detected~%geometry_msgs/Point minPoint	#Cube's min point~%geometry_msgs/Point maxPoint	#Cube's max point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Cube>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'color))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cube_centroid))
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'minPoint))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'maxPoint))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Cube>))
  "Converts a ROS message object to a list"
  (cl:list 'Cube
    (cl:cons ':color (color msg))
    (cl:cons ':cube_centroid (cube_centroid msg))
    (cl:cons ':detected_cube (detected_cube msg))
    (cl:cons ':minPoint (minPoint msg))
    (cl:cons ':maxPoint (maxPoint msg))
))
