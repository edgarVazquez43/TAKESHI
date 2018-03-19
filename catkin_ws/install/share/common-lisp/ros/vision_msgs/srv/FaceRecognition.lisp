; Auto-generated. Do not edit!


(cl:in-package vision_msgs-srv)


;//! \htmlinclude FaceRecognition-request.msg.html

(cl:defclass <FaceRecognition-request> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:string
    :initform ""))
)

(cl:defclass FaceRecognition-request (<FaceRecognition-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FaceRecognition-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FaceRecognition-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<FaceRecognition-request> is deprecated: use vision_msgs-srv:FaceRecognition-request instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <FaceRecognition-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:id-val is deprecated.  Use vision_msgs-srv:id instead.")
  (id m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FaceRecognition-request>) ostream)
  "Serializes a message object of type '<FaceRecognition-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'id))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FaceRecognition-request>) istream)
  "Deserializes a message object of type '<FaceRecognition-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FaceRecognition-request>)))
  "Returns string type for a service object of type '<FaceRecognition-request>"
  "vision_msgs/FaceRecognitionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FaceRecognition-request)))
  "Returns string type for a service object of type 'FaceRecognition-request"
  "vision_msgs/FaceRecognitionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FaceRecognition-request>)))
  "Returns md5sum for a message object of type '<FaceRecognition-request>"
  "7d89880e89dec4d521ffd613fc0a764b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FaceRecognition-request)))
  "Returns md5sum for a message object of type 'FaceRecognition-request"
  "7d89880e89dec4d521ffd613fc0a764b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FaceRecognition-request>)))
  "Returns full string definition for message of type '<FaceRecognition-request>"
  (cl:format cl:nil "string id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FaceRecognition-request)))
  "Returns full string definition for message of type 'FaceRecognition-request"
  (cl:format cl:nil "string id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FaceRecognition-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'id))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FaceRecognition-request>))
  "Converts a ROS message object to a list"
  (cl:list 'FaceRecognition-request
    (cl:cons ':id (id msg))
))
;//! \htmlinclude FaceRecognition-response.msg.html

(cl:defclass <FaceRecognition-response> (roslisp-msg-protocol:ros-message)
  ((faces
    :reader faces
    :initarg :faces
    :type vision_msgs-msg:VisionFaceObjects
    :initform (cl:make-instance 'vision_msgs-msg:VisionFaceObjects)))
)

(cl:defclass FaceRecognition-response (<FaceRecognition-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FaceRecognition-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FaceRecognition-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<FaceRecognition-response> is deprecated: use vision_msgs-srv:FaceRecognition-response instead.")))

(cl:ensure-generic-function 'faces-val :lambda-list '(m))
(cl:defmethod faces-val ((m <FaceRecognition-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:faces-val is deprecated.  Use vision_msgs-srv:faces instead.")
  (faces m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FaceRecognition-response>) ostream)
  "Serializes a message object of type '<FaceRecognition-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'faces) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FaceRecognition-response>) istream)
  "Deserializes a message object of type '<FaceRecognition-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'faces) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FaceRecognition-response>)))
  "Returns string type for a service object of type '<FaceRecognition-response>"
  "vision_msgs/FaceRecognitionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FaceRecognition-response)))
  "Returns string type for a service object of type 'FaceRecognition-response"
  "vision_msgs/FaceRecognitionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FaceRecognition-response>)))
  "Returns md5sum for a message object of type '<FaceRecognition-response>"
  "7d89880e89dec4d521ffd613fc0a764b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FaceRecognition-response)))
  "Returns md5sum for a message object of type 'FaceRecognition-response"
  "7d89880e89dec4d521ffd613fc0a764b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FaceRecognition-response>)))
  "Returns full string definition for message of type '<FaceRecognition-response>"
  (cl:format cl:nil "vision_msgs/VisionFaceObjects faces~%~%~%================================================================================~%MSG: vision_msgs/VisionFaceObjects~%std_msgs/Header header~%vision_msgs/VisionFaceObject[] recog_faces~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/VisionFaceObject~%string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FaceRecognition-response)))
  "Returns full string definition for message of type 'FaceRecognition-response"
  (cl:format cl:nil "vision_msgs/VisionFaceObjects faces~%~%~%================================================================================~%MSG: vision_msgs/VisionFaceObjects~%std_msgs/Header header~%vision_msgs/VisionFaceObject[] recog_faces~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: vision_msgs/VisionFaceObject~%string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FaceRecognition-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'faces))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FaceRecognition-response>))
  "Converts a ROS message object to a list"
  (cl:list 'FaceRecognition-response
    (cl:cons ':faces (faces msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'FaceRecognition)))
  'FaceRecognition-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'FaceRecognition)))
  'FaceRecognition-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FaceRecognition)))
  "Returns string type for a service object of type '<FaceRecognition>"
  "vision_msgs/FaceRecognition")