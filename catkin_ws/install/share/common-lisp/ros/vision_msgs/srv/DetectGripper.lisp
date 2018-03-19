; Auto-generated. Do not edit!


(cl:in-package vision_msgs-srv)


;//! \htmlinclude DetectGripper-request.msg.html

(cl:defclass <DetectGripper-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass DetectGripper-request (<DetectGripper-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DetectGripper-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DetectGripper-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<DetectGripper-request> is deprecated: use vision_msgs-srv:DetectGripper-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DetectGripper-request>) ostream)
  "Serializes a message object of type '<DetectGripper-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DetectGripper-request>) istream)
  "Deserializes a message object of type '<DetectGripper-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DetectGripper-request>)))
  "Returns string type for a service object of type '<DetectGripper-request>"
  "vision_msgs/DetectGripperRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectGripper-request)))
  "Returns string type for a service object of type 'DetectGripper-request"
  "vision_msgs/DetectGripperRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DetectGripper-request>)))
  "Returns md5sum for a message object of type '<DetectGripper-request>"
  "d04c5ffec643228db4185f8b85f803c4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DetectGripper-request)))
  "Returns md5sum for a message object of type 'DetectGripper-request"
  "d04c5ffec643228db4185f8b85f803c4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DetectGripper-request>)))
  "Returns full string definition for message of type '<DetectGripper-request>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DetectGripper-request)))
  "Returns full string definition for message of type 'DetectGripper-request"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DetectGripper-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DetectGripper-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DetectGripper-request
))
;//! \htmlinclude DetectGripper-response.msg.html

(cl:defclass <DetectGripper-response> (roslisp-msg-protocol:ros-message)
  ((gripper_position
    :reader gripper_position
    :initarg :gripper_position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass DetectGripper-response (<DetectGripper-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DetectGripper-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DetectGripper-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name vision_msgs-srv:<DetectGripper-response> is deprecated: use vision_msgs-srv:DetectGripper-response instead.")))

(cl:ensure-generic-function 'gripper_position-val :lambda-list '(m))
(cl:defmethod gripper_position-val ((m <DetectGripper-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader vision_msgs-srv:gripper_position-val is deprecated.  Use vision_msgs-srv:gripper_position instead.")
  (gripper_position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DetectGripper-response>) ostream)
  "Serializes a message object of type '<DetectGripper-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gripper_position) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DetectGripper-response>) istream)
  "Deserializes a message object of type '<DetectGripper-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gripper_position) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DetectGripper-response>)))
  "Returns string type for a service object of type '<DetectGripper-response>"
  "vision_msgs/DetectGripperResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectGripper-response)))
  "Returns string type for a service object of type 'DetectGripper-response"
  "vision_msgs/DetectGripperResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DetectGripper-response>)))
  "Returns md5sum for a message object of type '<DetectGripper-response>"
  "d04c5ffec643228db4185f8b85f803c4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DetectGripper-response)))
  "Returns md5sum for a message object of type 'DetectGripper-response"
  "d04c5ffec643228db4185f8b85f803c4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DetectGripper-response>)))
  "Returns full string definition for message of type '<DetectGripper-response>"
  (cl:format cl:nil "geometry_msgs/Point gripper_position~%~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DetectGripper-response)))
  "Returns full string definition for message of type 'DetectGripper-response"
  (cl:format cl:nil "geometry_msgs/Point gripper_position~%~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DetectGripper-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gripper_position))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DetectGripper-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DetectGripper-response
    (cl:cons ':gripper_position (gripper_position msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DetectGripper)))
  'DetectGripper-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DetectGripper)))
  'DetectGripper-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectGripper)))
  "Returns string type for a service object of type '<DetectGripper>"
  "vision_msgs/DetectGripper")