; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude search_remember_face-request.msg.html

(cl:defclass <search_remember_face-request> (roslisp-msg-protocol:ros-message)
  ((robot_instructions
    :reader robot_instructions
    :initarg :robot_instructions
    :type cl:string
    :initform "")
   (face_id
    :reader face_id
    :initarg :face_id
    :type cl:string
    :initform "")
   (head_movs
    :reader head_movs
    :initarg :head_movs
    :type (cl:vector std_msgs-msg:Float32MultiArray)
   :initform (cl:make-array 0 :element-type 'std_msgs-msg:Float32MultiArray :initial-element (cl:make-instance 'std_msgs-msg:Float32MultiArray))))
)

(cl:defclass search_remember_face-request (<search_remember_face-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <search_remember_face-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'search_remember_face-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<search_remember_face-request> is deprecated: use knowledge_msgs-srv:search_remember_face-request instead.")))

(cl:ensure-generic-function 'robot_instructions-val :lambda-list '(m))
(cl:defmethod robot_instructions-val ((m <search_remember_face-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:robot_instructions-val is deprecated.  Use knowledge_msgs-srv:robot_instructions instead.")
  (robot_instructions m))

(cl:ensure-generic-function 'face_id-val :lambda-list '(m))
(cl:defmethod face_id-val ((m <search_remember_face-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:face_id-val is deprecated.  Use knowledge_msgs-srv:face_id instead.")
  (face_id m))

(cl:ensure-generic-function 'head_movs-val :lambda-list '(m))
(cl:defmethod head_movs-val ((m <search_remember_face-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:head_movs-val is deprecated.  Use knowledge_msgs-srv:head_movs instead.")
  (head_movs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <search_remember_face-request>) ostream)
  "Serializes a message object of type '<search_remember_face-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'robot_instructions))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'robot_instructions))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'face_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'face_id))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'head_movs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'head_movs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <search_remember_face-request>) istream)
  "Deserializes a message object of type '<search_remember_face-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_instructions) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'robot_instructions) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'face_id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'face_id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'head_movs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'head_movs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:Float32MultiArray))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<search_remember_face-request>)))
  "Returns string type for a service object of type '<search_remember_face-request>"
  "knowledge_msgs/search_remember_faceRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'search_remember_face-request)))
  "Returns string type for a service object of type 'search_remember_face-request"
  "knowledge_msgs/search_remember_faceRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<search_remember_face-request>)))
  "Returns md5sum for a message object of type '<search_remember_face-request>"
  "1b76e414cf496b642eb3183c8057e767")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'search_remember_face-request)))
  "Returns md5sum for a message object of type 'search_remember_face-request"
  "1b76e414cf496b642eb3183c8057e767")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<search_remember_face-request>)))
  "Returns full string definition for message of type '<search_remember_face-request>"
  (cl:format cl:nil "string robot_instructions~%string face_id~%std_msgs/Float32MultiArray[] head_movs~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'search_remember_face-request)))
  "Returns full string definition for message of type 'search_remember_face-request"
  (cl:format cl:nil "string robot_instructions~%string face_id~%std_msgs/Float32MultiArray[] head_movs~%~%================================================================================~%MSG: std_msgs/Float32MultiArray~%# Please look at the MultiArrayLayout message definition for~%# documentation on all multiarrays.~%~%MultiArrayLayout  layout        # specification of data layout~%float32[]         data          # array of data~%~%~%================================================================================~%MSG: std_msgs/MultiArrayLayout~%# The multiarray declares a generic multi-dimensional array of a~%# particular data type.  Dimensions are ordered from outer most~%# to inner most.~%~%MultiArrayDimension[] dim # Array of dimension properties~%uint32 data_offset        # padding elements at front of data~%~%# Accessors should ALWAYS be written in terms of dimension stride~%# and specified outer-most dimension first.~%# ~%# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]~%#~%# A standard, 3-channel 640x480 image with interleaved color channels~%# would be specified as:~%#~%# dim[0].label  = \"height\"~%# dim[0].size   = 480~%# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)~%# dim[1].label  = \"width\"~%# dim[1].size   = 640~%# dim[1].stride = 3*640 = 1920~%# dim[2].label  = \"channel\"~%# dim[2].size   = 3~%# dim[2].stride = 3~%#~%# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.~%~%================================================================================~%MSG: std_msgs/MultiArrayDimension~%string label   # label of given dimension~%uint32 size    # size of given dimension (in type units)~%uint32 stride  # stride of given dimension~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <search_remember_face-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'robot_instructions))
     4 (cl:length (cl:slot-value msg 'face_id))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'head_movs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <search_remember_face-request>))
  "Converts a ROS message object to a list"
  (cl:list 'search_remember_face-request
    (cl:cons ':robot_instructions (robot_instructions msg))
    (cl:cons ':face_id (face_id msg))
    (cl:cons ':head_movs (head_movs msg))
))
;//! \htmlinclude search_remember_face-response.msg.html

(cl:defclass <search_remember_face-response> (roslisp-msg-protocol:ros-message)
  ((training_success
    :reader training_success
    :initarg :training_success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass search_remember_face-response (<search_remember_face-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <search_remember_face-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'search_remember_face-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<search_remember_face-response> is deprecated: use knowledge_msgs-srv:search_remember_face-response instead.")))

(cl:ensure-generic-function 'training_success-val :lambda-list '(m))
(cl:defmethod training_success-val ((m <search_remember_face-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:training_success-val is deprecated.  Use knowledge_msgs-srv:training_success instead.")
  (training_success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <search_remember_face-response>) ostream)
  "Serializes a message object of type '<search_remember_face-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'training_success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <search_remember_face-response>) istream)
  "Deserializes a message object of type '<search_remember_face-response>"
    (cl:setf (cl:slot-value msg 'training_success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<search_remember_face-response>)))
  "Returns string type for a service object of type '<search_remember_face-response>"
  "knowledge_msgs/search_remember_faceResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'search_remember_face-response)))
  "Returns string type for a service object of type 'search_remember_face-response"
  "knowledge_msgs/search_remember_faceResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<search_remember_face-response>)))
  "Returns md5sum for a message object of type '<search_remember_face-response>"
  "1b76e414cf496b642eb3183c8057e767")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'search_remember_face-response)))
  "Returns md5sum for a message object of type 'search_remember_face-response"
  "1b76e414cf496b642eb3183c8057e767")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<search_remember_face-response>)))
  "Returns full string definition for message of type '<search_remember_face-response>"
  (cl:format cl:nil "bool training_success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'search_remember_face-response)))
  "Returns full string definition for message of type 'search_remember_face-response"
  (cl:format cl:nil "bool training_success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <search_remember_face-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <search_remember_face-response>))
  "Converts a ROS message object to a list"
  (cl:list 'search_remember_face-response
    (cl:cons ':training_success (training_success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'search_remember_face)))
  'search_remember_face-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'search_remember_face)))
  'search_remember_face-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'search_remember_face)))
  "Returns string type for a service object of type '<search_remember_face>"
  "knowledge_msgs/search_remember_face")