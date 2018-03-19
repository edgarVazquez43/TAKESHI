; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude GestureSkeletons.msg.html

(cl:defclass <GestureSkeletons> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (recog_gestures
    :reader recog_gestures
    :initarg :recog_gestures
    :type (cl:vector vision_msgs-msg:GestureSkeleton)
   :initform (cl:make-array 0 :element-type 'vision_msgs-msg:GestureSkeleton :initial-element (cl:make-instance 'vision_msgs-msg:GestureSkeleton))))
)

(cl:defclass GestureSkeletons (<GestureSkeletons>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GestureSkeletons>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GestureSkeletons)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<GestureSkeletons> is deprecated: use vision_msgs-msg:GestureSkeletons instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <GestureSkeletons>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:header-val is deprecated.  Use vision_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'recog_gestures-val :lambda-list '(m))
(cl:defmethod recog_gestures-val ((m <GestureSkeletons>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:recog_gestures-val is deprecated.  Use vision_msgs-msg:recog_gestures instead.")
  (recog_gestures m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GestureSkeletons>) ostream)
  "Serializes a message object of type '<GestureSkeletons>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'recog_gestures))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'recog_gestures))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GestureSkeletons>) istream)
  "Deserializes a message object of type '<GestureSkeletons>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'recog_gestures) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'recog_gestures)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'vision_msgs-msg:GestureSkeleton))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GestureSkeletons>)))
  "Returns string type for a message object of type '<GestureSkeletons>"
  "vision_msgs/GestureSkeletons")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GestureSkeletons)))
  "Returns string type for a message object of type 'GestureSkeletons"
  "vision_msgs/GestureSkeletons")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GestureSkeletons>)))
  "Returns md5sum for a message object of type '<GestureSkeletons>"
  "f4df52aabef2b028180e9bc45fa637db")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GestureSkeletons)))
  "Returns md5sum for a message object of type 'GestureSkeletons"
  "f4df52aabef2b028180e9bc45fa637db")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GestureSkeletons>)))
  "Returns full string definition for message of type '<GestureSkeletons>"
  (cl:format cl:nil "std_msgs/Header header~%vision_msgs/GestureSkeleton[] recog_gestures~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/GestureSkeleton~%int8 id		#id of user~%string gesture		#gesture of user~%geometry_msgs/Point gesture_centroid		#Gesture Centroid (x,y,z)~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GestureSkeletons)))
  "Returns full string definition for message of type 'GestureSkeletons"
  (cl:format cl:nil "std_msgs/Header header~%vision_msgs/GestureSkeleton[] recog_gestures~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/GestureSkeleton~%int8 id		#id of user~%string gesture		#gesture of user~%geometry_msgs/Point gesture_centroid		#Gesture Centroid (x,y,z)~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GestureSkeletons>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'recog_gestures) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GestureSkeletons>))
  "Converts a ROS message object to a list"
  (cl:list 'GestureSkeletons
    (cl:cons ':header (header msg))
    (cl:cons ':recog_gestures (recog_gestures msg))
))
