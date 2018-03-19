; Auto-generated. Do not edit!


(cl:in-package knowledge_msgs-srv)


;//! \htmlinclude find_person-request.msg.html

(cl:defclass <find_person-request> (roslisp-msg-protocol:ros-message)
  ((person_face_id
    :reader person_face_id
    :initarg :person_face_id
    :type cl:string
    :initform "")
   (location
    :reader location
    :initarg :location
    :type cl:string
    :initform ""))
)

(cl:defclass find_person-request (<find_person-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <find_person-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'find_person-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<find_person-request> is deprecated: use knowledge_msgs-srv:find_person-request instead.")))

(cl:ensure-generic-function 'person_face_id-val :lambda-list '(m))
(cl:defmethod person_face_id-val ((m <find_person-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:person_face_id-val is deprecated.  Use knowledge_msgs-srv:person_face_id instead.")
  (person_face_id m))

(cl:ensure-generic-function 'location-val :lambda-list '(m))
(cl:defmethod location-val ((m <find_person-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:location-val is deprecated.  Use knowledge_msgs-srv:location instead.")
  (location m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <find_person-request>) ostream)
  "Serializes a message object of type '<find_person-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'person_face_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'person_face_id))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'location))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'location))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <find_person-request>) istream)
  "Deserializes a message object of type '<find_person-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'person_face_id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'person_face_id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'location) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'location) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<find_person-request>)))
  "Returns string type for a service object of type '<find_person-request>"
  "knowledge_msgs/find_personRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_person-request)))
  "Returns string type for a service object of type 'find_person-request"
  "knowledge_msgs/find_personRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<find_person-request>)))
  "Returns md5sum for a message object of type '<find_person-request>"
  "0819b34699306bff12623f558a5cd6ca")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'find_person-request)))
  "Returns md5sum for a message object of type 'find_person-request"
  "0819b34699306bff12623f558a5cd6ca")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<find_person-request>)))
  "Returns full string definition for message of type '<find_person-request>"
  (cl:format cl:nil "string person_face_id~%string location~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'find_person-request)))
  "Returns full string definition for message of type 'find_person-request"
  (cl:format cl:nil "string person_face_id~%string location~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <find_person-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'person_face_id))
     4 (cl:length (cl:slot-value msg 'location))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <find_person-request>))
  "Converts a ROS message object to a list"
  (cl:list 'find_person-request
    (cl:cons ':person_face_id (person_face_id msg))
    (cl:cons ':location (location msg))
))
;//! \htmlinclude find_person-response.msg.html

(cl:defclass <find_person-response> (roslisp-msg-protocol:ros-message)
  ((person_face
    :reader person_face
    :initarg :person_face
    :type vision_msgs-msg:VisionFaceObject
    :initform (cl:make-instance 'vision_msgs-msg:VisionFaceObject))
   (task_success
    :reader task_success
    :initarg :task_success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass find_person-response (<find_person-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <find_person-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'find_person-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name knowledge_msgs-srv:<find_person-response> is deprecated: use knowledge_msgs-srv:find_person-response instead.")))

(cl:ensure-generic-function 'person_face-val :lambda-list '(m))
(cl:defmethod person_face-val ((m <find_person-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:person_face-val is deprecated.  Use knowledge_msgs-srv:person_face instead.")
  (person_face m))

(cl:ensure-generic-function 'task_success-val :lambda-list '(m))
(cl:defmethod task_success-val ((m <find_person-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader knowledge_msgs-srv:task_success-val is deprecated.  Use knowledge_msgs-srv:task_success instead.")
  (task_success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <find_person-response>) ostream)
  "Serializes a message object of type '<find_person-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'person_face) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'task_success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <find_person-response>) istream)
  "Deserializes a message object of type '<find_person-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'person_face) istream)
    (cl:setf (cl:slot-value msg 'task_success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<find_person-response>)))
  "Returns string type for a service object of type '<find_person-response>"
  "knowledge_msgs/find_personResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_person-response)))
  "Returns string type for a service object of type 'find_person-response"
  "knowledge_msgs/find_personResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<find_person-response>)))
  "Returns md5sum for a message object of type '<find_person-response>"
  "0819b34699306bff12623f558a5cd6ca")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'find_person-response)))
  "Returns md5sum for a message object of type 'find_person-response"
  "0819b34699306bff12623f558a5cd6ca")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<find_person-response>)))
  "Returns full string definition for message of type '<find_person-response>"
  (cl:format cl:nil "vision_msgs/VisionFaceObject person_face~%bool task_success~%~%~%================================================================================~%MSG: vision_msgs/VisionFaceObject~%string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'find_person-response)))
  "Returns full string definition for message of type 'find_person-response"
  (cl:format cl:nil "vision_msgs/VisionFaceObject person_face~%bool task_success~%~%~%================================================================================~%MSG: vision_msgs/VisionFaceObject~%string id                                    #face id~%float32 confidence                           #value in [0,1] indicating the probability of a correct identification~%geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)~%geometry_msgs/Point[] bounding_box           #Face bounding box 2D ~%bool smile                                   #smiling face~%int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <find_person-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'person_face))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <find_person-response>))
  "Converts a ROS message object to a list"
  (cl:list 'find_person-response
    (cl:cons ':person_face (person_face msg))
    (cl:cons ':task_success (task_success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'find_person)))
  'find_person-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'find_person)))
  'find_person-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_person)))
  "Returns string type for a service object of type '<find_person>"
  "knowledge_msgs/find_person")