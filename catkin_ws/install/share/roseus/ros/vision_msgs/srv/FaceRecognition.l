;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::FaceRecognition)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'FaceRecognition (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::FACERECOGNITION")
  (make-package "VISION_MSGS::FACERECOGNITION"))
(unless (find-package "VISION_MSGS::FACERECOGNITIONREQUEST")
  (make-package "VISION_MSGS::FACERECOGNITIONREQUEST"))
(unless (find-package "VISION_MSGS::FACERECOGNITIONRESPONSE")
  (make-package "VISION_MSGS::FACERECOGNITIONRESPONSE"))

(in-package "ROS")





(defclass vision_msgs::FaceRecognitionRequest
  :super ros::object
  :slots (_id ))

(defmethod vision_msgs::FaceRecognitionRequest
  (:init
   (&key
    ((:id __id) "")
    )
   (send-super :init)
   (setq _id (string __id))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:serialization-length
   ()
   (+
    ;; string _id
    4 (length _id)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass vision_msgs::FaceRecognitionResponse
  :super ros::object
  :slots (_faces ))

(defmethod vision_msgs::FaceRecognitionResponse
  (:init
   (&key
    ((:faces __faces) (instance vision_msgs::VisionFaceObjects :init))
    )
   (send-super :init)
   (setq _faces __faces)
   self)
  (:faces
   (&rest __faces)
   (if (keywordp (car __faces))
       (send* _faces __faces)
     (progn
       (if __faces (setq _faces (car __faces)))
       _faces)))
  (:serialization-length
   ()
   (+
    ;; vision_msgs/VisionFaceObjects _faces
    (send _faces :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; vision_msgs/VisionFaceObjects _faces
       (send _faces :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; vision_msgs/VisionFaceObjects _faces
     (send _faces :deserialize buf ptr-) (incf ptr- (send _faces :serialization-length))
   ;;
   self)
  )

(defclass vision_msgs::FaceRecognition
  :super ros::object
  :slots ())

(setf (get vision_msgs::FaceRecognition :md5sum-) "7d89880e89dec4d521ffd613fc0a764b")
(setf (get vision_msgs::FaceRecognition :datatype-) "vision_msgs/FaceRecognition")
(setf (get vision_msgs::FaceRecognition :request) vision_msgs::FaceRecognitionRequest)
(setf (get vision_msgs::FaceRecognition :response) vision_msgs::FaceRecognitionResponse)

(defmethod vision_msgs::FaceRecognitionRequest
  (:response () (instance vision_msgs::FaceRecognitionResponse :init)))

(setf (get vision_msgs::FaceRecognitionRequest :md5sum-) "7d89880e89dec4d521ffd613fc0a764b")
(setf (get vision_msgs::FaceRecognitionRequest :datatype-) "vision_msgs/FaceRecognitionRequest")
(setf (get vision_msgs::FaceRecognitionRequest :definition-)
      "string id
---
vision_msgs/VisionFaceObjects faces


================================================================================
MSG: vision_msgs/VisionFaceObjects
std_msgs/Header header
vision_msgs/VisionFaceObject[] recog_faces

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: vision_msgs/VisionFaceObject
string id                                    #face id
float32 confidence                           #value in [0,1] indicating the probability of a correct identification
geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)
geometry_msgs/Point[] bounding_box           #Face bounding box 2D 
bool smile                                   #smiling face
int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")

(setf (get vision_msgs::FaceRecognitionResponse :md5sum-) "7d89880e89dec4d521ffd613fc0a764b")
(setf (get vision_msgs::FaceRecognitionResponse :datatype-) "vision_msgs/FaceRecognitionResponse")
(setf (get vision_msgs::FaceRecognitionResponse :definition-)
      "string id
---
vision_msgs/VisionFaceObjects faces


================================================================================
MSG: vision_msgs/VisionFaceObjects
std_msgs/Header header
vision_msgs/VisionFaceObject[] recog_faces

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: vision_msgs/VisionFaceObject
string id                                    #face id
float32 confidence                           #value in [0,1] indicating the probability of a correct identification
geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)
geometry_msgs/Point[] bounding_box           #Face bounding box 2D 
bool smile                                   #smiling face
int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")



(provide :vision_msgs/FaceRecognition "7d89880e89dec4d521ffd613fc0a764b")


