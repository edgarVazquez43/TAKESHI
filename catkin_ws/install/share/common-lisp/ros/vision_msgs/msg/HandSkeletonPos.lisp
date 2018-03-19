; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude HandSkeletonPos.msg.html

(cl:defclass <HandSkeletonPos> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (hands_position
    :reader hands_position
    :initarg :hands_position
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass HandSkeletonPos (<HandSkeletonPos>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <HandSkeletonPos>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'HandSkeletonPos)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<HandSkeletonPos> is deprecated: use vision_msgs-msg:HandSkeletonPos instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <HandSkeletonPos>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:header-val is deprecated.  Use vision_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'hands_position-val :lambda-list '(m))
(cl:defmethod hands_position-val ((m <HandSkeletonPos>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:hands_position-val is deprecated.  Use vision_msgs-msg:hands_position instead.")
  (hands_position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <HandSkeletonPos>) ostream)
  "Serializes a message object of type '<HandSkeletonPos>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'hands_position))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'hands_position))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <HandSkeletonPos>) istream)
  "Deserializes a message object of type '<HandSkeletonPos>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'hands_position) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'hands_position)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<HandSkeletonPos>)))
  "Returns string type for a message object of type '<HandSkeletonPos>"
  "vision_msgs/HandSkeletonPos")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'HandSkeletonPos)))
  "Returns string type for a message object of type 'HandSkeletonPos"
  "vision_msgs/HandSkeletonPos")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<HandSkeletonPos>)))
  "Returns md5sum for a message object of type '<HandSkeletonPos>"
  "2538d67d00ece1fbd2e374d69c22d6f0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'HandSkeletonPos)))
  "Returns md5sum for a message object of type 'HandSkeletonPos"
  "2538d67d00ece1fbd2e374d69c22d6f0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<HandSkeletonPos>)))
  "Returns full string definition for message of type '<HandSkeletonPos>"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point[] hands_position~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'HandSkeletonPos)))
  "Returns full string definition for message of type 'HandSkeletonPos"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Point[] hands_position~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <HandSkeletonPos>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'hands_position) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <HandSkeletonPos>))
  "Converts a ROS message object to a list"
  (cl:list 'HandSkeletonPos
    (cl:cons ':header (header msg))
    (cl:cons ':hands_position (hands_position msg))
))
