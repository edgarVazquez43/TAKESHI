; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude Skeleton.msg.html

(cl:defclass <Skeleton> (roslisp-msg-protocol:ros-message)
  ((user_id
    :reader user_id
    :initarg :user_id
    :type cl:integer
    :initform 0)
   (ref_point
    :reader ref_point
    :initarg :ref_point
    :type geometry_msgs-msg:Point32
    :initform (cl:make-instance 'geometry_msgs-msg:Point32))
   (joints
    :reader joints
    :initarg :joints
    :type (cl:vector vision_msgs-msg:SkeletonJoint)
   :initform (cl:make-array 0 :element-type 'vision_msgs-msg:SkeletonJoint :initial-element (cl:make-instance 'vision_msgs-msg:SkeletonJoint))))
)

(cl:defclass Skeleton (<Skeleton>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Skeleton>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Skeleton)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<Skeleton> is deprecated: use vision_msgs-msg:Skeleton instead.")))

(cl:ensure-generic-function 'user_id-val :lambda-list '(m))
(cl:defmethod user_id-val ((m <Skeleton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:user_id-val is deprecated.  Use vision_msgs-msg:user_id instead.")
  (user_id m))

(cl:ensure-generic-function 'ref_point-val :lambda-list '(m))
(cl:defmethod ref_point-val ((m <Skeleton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:ref_point-val is deprecated.  Use vision_msgs-msg:ref_point instead.")
  (ref_point m))

(cl:ensure-generic-function 'joints-val :lambda-list '(m))
(cl:defmethod joints-val ((m <Skeleton>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:joints-val is deprecated.  Use vision_msgs-msg:joints instead.")
  (joints m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Skeleton>) ostream)
  "Serializes a message object of type '<Skeleton>"
  (cl:let* ((signed (cl:slot-value msg 'user_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ref_point) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'joints))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'joints))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Skeleton>) istream)
  "Deserializes a message object of type '<Skeleton>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'user_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ref_point) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'joints) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'joints)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'vision_msgs-msg:SkeletonJoint))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Skeleton>)))
  "Returns string type for a message object of type '<Skeleton>"
  "vision_msgs/Skeleton")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Skeleton)))
  "Returns string type for a message object of type 'Skeleton"
  "vision_msgs/Skeleton")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Skeleton>)))
  "Returns md5sum for a message object of type '<Skeleton>"
  "5f2d8c1c74d0773f8fb9581c67ba2f2a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Skeleton)))
  "Returns md5sum for a message object of type 'Skeleton"
  "5f2d8c1c74d0773f8fb9581c67ba2f2a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Skeleton>)))
  "Returns full string definition for message of type '<Skeleton>"
  (cl:format cl:nil "int32 user_id~%geometry_msgs/Point32 ref_point~%vision_msgs/SkeletonJoint[] joints~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: vision_msgs/SkeletonJoint~%std_msgs/String name_joint~%geometry_msgs/Vector3 position~%geometry_msgs/Quaternion orientation~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Skeleton)))
  "Returns full string definition for message of type 'Skeleton"
  (cl:format cl:nil "int32 user_id~%geometry_msgs/Point32 ref_point~%vision_msgs/SkeletonJoint[] joints~%~%================================================================================~%MSG: geometry_msgs/Point32~%# This contains the position of a point in free space(with 32 bits of precision).~%# It is recommeded to use Point wherever possible instead of Point32.  ~%# ~%# This recommendation is to promote interoperability.  ~%#~%# This message is designed to take up less space when sending~%# lots of points at once, as in the case of a PointCloud.  ~%~%float32 x~%float32 y~%float32 z~%================================================================================~%MSG: vision_msgs/SkeletonJoint~%std_msgs/String name_joint~%geometry_msgs/Vector3 position~%geometry_msgs/Quaternion orientation~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Skeleton>))
  (cl:+ 0
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ref_point))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'joints) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Skeleton>))
  "Converts a ROS message object to a list"
  (cl:list 'Skeleton
    (cl:cons ':user_id (user_id msg))
    (cl:cons ':ref_point (ref_point msg))
    (cl:cons ':joints (joints msg))
))
