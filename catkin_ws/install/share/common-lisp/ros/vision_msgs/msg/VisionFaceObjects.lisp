; Auto-generated. Do not edit!


(cl:in-package vision_msgs-msg)


;//! \htmlinclude VisionFaceObjects.msg.html

(cl:defclass <VisionFaceObjects> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (recog_faces
    :reader recog_faces
    :initarg :recog_faces
    :type (cl:vector vision_msgs-msg:VisionFaceObject)
   :initform (cl:make-array 0 :element-type 'vision_msgs-msg:VisionFaceObject :initial-element (cl:make-instance 'vision_msgs-msg:VisionFaceObject))))
)

(cl:defclass VisionFaceObjects (<VisionFaceObjects>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VisionFaceObjects>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VisionFaceObjects)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-msg:<VisionFaceObjects> is deprecated: use vision_msgs-msg:VisionFaceObjects instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VisionFaceObjects>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:header-val is deprecated.  Use vision_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'recog_faces-val :lambda-list '(m))
(cl:defmethod recog_faces-val ((m <VisionFaceObjects>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-msg:recog_faces-val is deprecated.  Use vision_msgs-msg:recog_faces instead.")
  (recog_faces m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VisionFaceObjects>) ostream)
  "Serializes a message object of type '<VisionFaceObjects>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'recog_faces))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'recog_faces))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VisionFaceObjects>) istream)
  "Deserializes a message object of type '<VisionFaceObjects>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'recog_faces) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'recog_faces)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'vision_msgs-msg:VisionFaceObject))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VisionFaceObjects>)))
  "Returns string type for a message object of type '<VisionFaceObjects>"
  "vision_msgs/VisionFaceObjects")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VisionFaceObjects)))
  "Returns string type for a message object of type 'VisionFaceObjects"
  "vision_msgs/VisionFaceObjects")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VisionFaceObjects>)))
  "Returns md5sum for a message object of type '<VisionFaceObjects>"
  "4fd1cb6b6d63c7ee8d419e777e468fd2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VisionFaceObjects)))
  "Returns md5sum for a message object of type 'VisionFaceObjects"
  "4fd1cb6b6d63c7ee8d419e777e468fd2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VisionFaceObjects>)))
  "Returns full string definition for message of type '<VisionFaceObjects>"
  (cl:format cl:nil "std_msgs/Header header~%vision_msgs/VisionFaceObject[] recog_faces~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/VisionFaceObject~%string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VisionFaceObjects)))
  "Returns full string definition for message of type 'VisionFaceObjects"
  (cl:format cl:nil "std_msgs/Header header~%vision_msgs/VisionFaceObject[] recog_faces~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/VisionFaceObject~%string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VisionFaceObjects>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'recog_faces) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VisionFaceObjects>))
  "Converts a ROS message object to a list"
  (cl:list 'VisionFaceObjects
    (cl:cons ':header (header msg))
    (cl:cons ':recog_faces (recog_faces msg))
))
