; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude SkeletonJoint.msg.html

(cl:defclass <SkeletonJoint> (roslisp-msg-protocol:ros-message)
  ((name_joint
    :reader name_joint
    :initarg :name_joint
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String))
   (position
    :reader position
    :initarg :position
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (orientation
    :reader orientation
    :initarg :orientation
    :type geometry_msgs-msg:Quaternion
    :initform (cl:make-instance 'geometry_msgs-msg:Quaternion)))
)

(cl:defclass SkeletonJoint (<SkeletonJoint>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SkeletonJoint>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SkeletonJoint)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<SkeletonJoint> is deprecated: use vision_msgs-msg:SkeletonJoint instead.")))

(cl:ensure-generic-function 'name_joint-val :lambda-list '(m))
(cl:defmethod name_joint-val ((m <SkeletonJoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:name_joint-val is deprecated.  Use vision_msgs-msg:name_joint instead.")
  (name_joint m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <SkeletonJoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:position-val is deprecated.  Use vision_msgs-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <SkeletonJoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:orientation-val is deprecated.  Use vision_msgs-msg:orientation instead.")
  (orientation m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SkeletonJoint>) ostream)
  "Serializes a message object of type '<SkeletonJoint>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'name_joint) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'orientation) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SkeletonJoint>) istream)
  "Deserializes a message object of type '<SkeletonJoint>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'name_joint) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'orientation) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SkeletonJoint>)))
  "Returns string type for a message object of type '<SkeletonJoint>"
  "vision_msgs/SkeletonJoint")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SkeletonJoint)))
  "Returns string type for a message object of type 'SkeletonJoint"
  "vision_msgs/SkeletonJoint")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SkeletonJoint>)))
  "Returns md5sum for a message object of type '<SkeletonJoint>"
  "cc5468d1135a7ad558e21de9fa6840a5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SkeletonJoint)))
  "Returns md5sum for a message object of type 'SkeletonJoint"
  "cc5468d1135a7ad558e21de9fa6840a5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SkeletonJoint>)))
  "Returns full string definition for message of type '<SkeletonJoint>"
  (cl:format cl:nil "std_msgs/String name_joint~%geometry_msgs/Vector3 position~%geometry_msgs/Quaternion orientation~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SkeletonJoint)))
  "Returns full string definition for message of type 'SkeletonJoint"
  (cl:format cl:nil "std_msgs/String name_joint~%geometry_msgs/Vector3 position~%geometry_msgs/Quaternion orientation~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SkeletonJoint>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'name_joint))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'orientation))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SkeletonJoint>))
  "Converts a ROS message object to a list"
  (cl:list 'SkeletonJoint
    (cl:cons ':name_joint (name_joint msg))
    (cl:cons ':position (position msg))
    (cl:cons ':orientation (orientation msg))
))
