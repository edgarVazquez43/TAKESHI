; Auto-generated. Do not edit!


(cl:in-package vision_msgs-srv)


;//! \htmlinclude FindWaving-request.msg.html

(cl:defclass <FindWaving-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass FindWaving-request (<FindWaving-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FindWaving-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FindWaving-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<FindWaving-request> is deprecated: use vision_msgs-srv:FindWaving-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FindWaving-request>) ostream)
  "Serializes a message object of type '<FindWaving-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FindWaving-request>) istream)
  "Deserializes a message object of type '<FindWaving-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FindWaving-request>)))
  "Returns string type for a service object of type '<FindWaving-request>"
  "vision_msgs/FindWavingRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FindWaving-request)))
  "Returns string type for a service object of type 'FindWaving-request"
  "vision_msgs/FindWavingRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FindWaving-request>)))
  "Returns md5sum for a message object of type '<FindWaving-request>"
  "a5efa18c4fad16dbe94cb16a4d7151ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FindWaving-request)))
  "Returns md5sum for a message object of type 'FindWaving-request"
  "a5efa18c4fad16dbe94cb16a4d7151ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FindWaving-request>)))
  "Returns full string definition for message of type '<FindWaving-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FindWaving-request)))
  "Returns full string definition for message of type 'FindWaving-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FindWaving-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FindWaving-request>))
  "Converts a ROS message object to a list"
  (cl:list 'FindWaving-request
))
;//! \htmlinclude FindWaving-response.msg.html

(cl:defclass <FindWaving-response> (roslisp-msg-protocol:ros-message)
  ((bounding_box
    :reader bounding_box
    :initarg :bounding_box
    :type (cl:vector vision_msgs-msg:VisionRect)
   :initform (cl:make-array 0 :element-type 'vision_msgs-msg:VisionRect :initial-element (cl:make-instance 'vision_msgs-msg:VisionRect)))
   (frame_width
    :reader frame_width
    :initarg :frame_width
    :type std_msgs-msg:Int32
    :initform (cl:make-instance 'std_msgs-msg:Int32))
   (frame_height
    :reader frame_height
    :initarg :frame_height
    :type std_msgs-msg:Int32
    :initform (cl:make-instance 'std_msgs-msg:Int32)))
)

(cl:defclass FindWaving-response (<FindWaving-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FindWaving-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FindWaving-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<FindWaving-response> is deprecated: use vision_msgs-srv:FindWaving-response instead.")))

(cl:ensure-generic-function 'bounding_box-val :lambda-list '(m))
(cl:defmethod bounding_box-val ((m <FindWaving-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:bounding_box-val is deprecated.  Use vision_msgs-srv:bounding_box instead.")
  (bounding_box m))

(cl:ensure-generic-function 'frame_width-val :lambda-list '(m))
(cl:defmethod frame_width-val ((m <FindWaving-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:frame_width-val is deprecated.  Use vision_msgs-srv:frame_width instead.")
  (frame_width m))

(cl:ensure-generic-function 'frame_height-val :lambda-list '(m))
(cl:defmethod frame_height-val ((m <FindWaving-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:frame_height-val is deprecated.  Use vision_msgs-srv:frame_height instead.")
  (frame_height m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FindWaving-response>) ostream)
  "Serializes a message object of type '<FindWaving-response>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'bounding_box))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'bounding_box))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'frame_width) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'frame_height) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FindWaving-response>) istream)
  "Deserializes a message object of type '<FindWaving-response>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'bounding_box) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'bounding_box)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'vision_msgs-msg:VisionRect))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'frame_width) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'frame_height) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FindWaving-response>)))
  "Returns string type for a service object of type '<FindWaving-response>"
  "vision_msgs/FindWavingResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FindWaving-response)))
  "Returns string type for a service object of type 'FindWaving-response"
  "vision_msgs/FindWavingResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FindWaving-response>)))
  "Returns md5sum for a message object of type '<FindWaving-response>"
  "a5efa18c4fad16dbe94cb16a4d7151ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FindWaving-response)))
  "Returns md5sum for a message object of type 'FindWaving-response"
  "a5efa18c4fad16dbe94cb16a4d7151ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FindWaving-response>)))
  "Returns full string definition for message of type '<FindWaving-response>"
  (cl:format cl:nil "vision_msgs/VisionRect[] bounding_box~%std_msgs/Int32 frame_width~%std_msgs/Int32 frame_height~%~%~%~%================================================================================~%MSG: vision_msgs/VisionRect~%int32 x~%int32 y~%int32 width~%int32 height~%~%================================================================================~%MSG: std_msgs/Int32~%int32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FindWaving-response)))
  "Returns full string definition for message of type 'FindWaving-response"
  (cl:format cl:nil "vision_msgs/VisionRect[] bounding_box~%std_msgs/Int32 frame_width~%std_msgs/Int32 frame_height~%~%~%~%================================================================================~%MSG: vision_msgs/VisionRect~%int32 x~%int32 y~%int32 width~%int32 height~%~%================================================================================~%MSG: std_msgs/Int32~%int32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FindWaving-response>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'bounding_box) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'frame_width))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'frame_height))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FindWaving-response>))
  "Converts a ROS message object to a list"
  (cl:list 'FindWaving-response
    (cl:cons ':bounding_box (bounding_box msg))
    (cl:cons ':frame_width (frame_width msg))
    (cl:cons ':frame_height (frame_height msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'FindWaving)))
  'FindWaving-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'FindWaving)))
  'FindWaving-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FindWaving)))
  "Returns string type for a service object of type '<FindWaving>"
  "vision_msgs/FindWaving")