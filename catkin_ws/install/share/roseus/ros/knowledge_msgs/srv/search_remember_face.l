;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::search_remember_face)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'search_remember_face (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::SEARCH_REMEMBER_FACE")
  (make-package "KNOWLEDGE_MSGS::SEARCH_REMEMBER_FACE"))
(unless (find-package "KNOWLEDGE_MSGS::SEARCH_REMEMBER_FACEREQUEST")
  (make-package "KNOWLEDGE_MSGS::SEARCH_REMEMBER_FACEREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::SEARCH_REMEMBER_FACERESPONSE")
  (make-package "KNOWLEDGE_MSGS::SEARCH_REMEMBER_FACERESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))




(defclass knowledge_msgs::search_remember_faceRequest
  :super ros::object
  :slots (_robot_instructions _face_id _head_movs ))

(defmethod knowledge_msgs::search_remember_faceRequest
  (:init
   (&key
    ((:robot_instructions __robot_instructions) "")
    ((:face_id __face_id) "")
    ((:head_movs __head_movs) (let (r) (dotimes (i 0) (push (instance std_msgs::Float32MultiArray :init) r)) r))
    )
   (send-super :init)
   (setq _robot_instructions (string __robot_instructions))
   (setq _face_id (string __face_id))
   (setq _head_movs __head_movs)
   self)
  (:robot_instructions
   (&optional __robot_instructions)
   (if __robot_instructions (setq _robot_instructions __robot_instructions)) _robot_instructions)
  (:face_id
   (&optional __face_id)
   (if __face_id (setq _face_id __face_id)) _face_id)
  (:head_movs
   (&rest __head_movs)
   (if (keywordp (car __head_movs))
       (send* _head_movs __head_movs)
     (progn
       (if __head_movs (setq _head_movs (car __head_movs)))
       _head_movs)))
  (:serialization-length
   ()
   (+
    ;; string _robot_instructions
    4 (length _robot_instructions)
    ;; string _face_id
    4 (length _face_id)
    ;; std_msgs/Float32MultiArray[] _head_movs
    (apply #'+ (send-all _head_movs :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _robot_instructions
       (write-long (length _robot_instructions) s) (princ _robot_instructions s)
     ;; string _face_id
       (write-long (length _face_id) s) (princ _face_id s)
     ;; std_msgs/Float32MultiArray[] _head_movs
     (write-long (length _head_movs) s)
     (dolist (elem _head_movs)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _robot_instructions
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _robot_instructions (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _face_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _face_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; std_msgs/Float32MultiArray[] _head_movs
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _head_movs (let (r) (dotimes (i n) (push (instance std_msgs::Float32MultiArray :init) r)) r))
     (dolist (elem- _head_movs)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass knowledge_msgs::search_remember_faceResponse
  :super ros::object
  :slots (_training_success ))

(defmethod knowledge_msgs::search_remember_faceResponse
  (:init
   (&key
    ((:training_success __training_success) nil)
    )
   (send-super :init)
   (setq _training_success __training_success)
   self)
  (:training_success
   (&optional __training_success)
   (if __training_success (setq _training_success __training_success)) _training_success)
  (:serialization-length
   ()
   (+
    ;; bool _training_success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _training_success
       (if _training_success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _training_success
     (setq _training_success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass knowledge_msgs::search_remember_face
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::search_remember_face :md5sum-) "1b76e414cf496b642eb3183c8057e767")
(setf (get knowledge_msgs::search_remember_face :datatype-) "knowledge_msgs/search_remember_face")
(setf (get knowledge_msgs::search_remember_face :request) knowledge_msgs::search_remember_faceRequest)
(setf (get knowledge_msgs::search_remember_face :response) knowledge_msgs::search_remember_faceResponse)

(defmethod knowledge_msgs::search_remember_faceRequest
  (:response () (instance knowledge_msgs::search_remember_faceResponse :init)))

(setf (get knowledge_msgs::search_remember_faceRequest :md5sum-) "1b76e414cf496b642eb3183c8057e767")
(setf (get knowledge_msgs::search_remember_faceRequest :datatype-) "knowledge_msgs/search_remember_faceRequest")
(setf (get knowledge_msgs::search_remember_faceRequest :definition-)
      "string robot_instructions
string face_id
std_msgs/Float32MultiArray[] head_movs

================================================================================
MSG: std_msgs/Float32MultiArray
# Please look at the MultiArrayLayout message definition for
# documentation on all multiarrays.

MultiArrayLayout  layout        # specification of data layout
float32[]         data          # array of data


================================================================================
MSG: std_msgs/MultiArrayLayout
# The multiarray declares a generic multi-dimensional array of a
# particular data type.  Dimensions are ordered from outer most
# to inner most.

MultiArrayDimension[] dim # Array of dimension properties
uint32 data_offset        # padding elements at front of data

# Accessors should ALWAYS be written in terms of dimension stride
# and specified outer-most dimension first.
# 
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]
#
# A standard, 3-channel 640x480 image with interleaved color channels
# would be specified as:
#
# dim[0].label  = \"height\"
# dim[0].size   = 480
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
# dim[1].label  = \"width\"
# dim[1].size   = 640
# dim[1].stride = 3*640 = 1920
# dim[2].label  = \"channel\"
# dim[2].size   = 3
# dim[2].stride = 3
#
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.

================================================================================
MSG: std_msgs/MultiArrayDimension
string label   # label of given dimension
uint32 size    # size of given dimension (in type units)
---
bool training_success

")

(setf (get knowledge_msgs::search_remember_faceResponse :md5sum-) "1b76e414cf496b642eb3183c8057e767")
(setf (get knowledge_msgs::search_remember_faceResponse :datatype-) "knowledge_msgs/search_remember_faceResponse")
(setf (get knowledge_msgs::search_remember_faceResponse :definition-)
      "string robot_instructions
string face_id
std_msgs/Float32MultiArray[] head_movs

================================================================================
MSG: std_msgs/Float32MultiArray
# Please look at the MultiArrayLayout message definition for
# documentation on all multiarrays.

MultiArrayLayout  layout        # specification of data layout
float32[]         data          # array of data


================================================================================
MSG: std_msgs/MultiArrayLayout
# The multiarray declares a generic multi-dimensional array of a
# particular data type.  Dimensions are ordered from outer most
# to inner most.

MultiArrayDimension[] dim # Array of dimension properties
uint32 data_offset        # padding elements at front of data

# Accessors should ALWAYS be written in terms of dimension stride
# and specified outer-most dimension first.
# 
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]
#
# A standard, 3-channel 640x480 image with interleaved color channels
# would be specified as:
#
# dim[0].label  = \"height\"
# dim[0].size   = 480
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
# dim[1].label  = \"width\"
# dim[1].size   = 640
# dim[1].stride = 3*640 = 1920
# dim[2].label  = \"channel\"
# dim[2].size   = 3
# dim[2].stride = 3
#
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.

================================================================================
MSG: std_msgs/MultiArrayDimension
string label   # label of given dimension
uint32 size    # size of given dimension (in type units)
---
bool training_success

")



(provide :knowledge_msgs/search_remember_face "1b76e414cf496b642eb3183c8057e767")


