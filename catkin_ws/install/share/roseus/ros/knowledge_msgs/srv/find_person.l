;; Auto-generated. Do not edit!


(when (boundp 'knowledge_msgs::find_person)
  (if (not (find-package "KNOWLEDGE_MSGS"))
    (make-package "KNOWLEDGE_MSGS"))
  (shadow 'find_person (find-package "KNOWLEDGE_MSGS")))
(unless (find-package "KNOWLEDGE_MSGS::FIND_PERSON")
  (make-package "KNOWLEDGE_MSGS::FIND_PERSON"))
(unless (find-package "KNOWLEDGE_MSGS::FIND_PERSONREQUEST")
  (make-package "KNOWLEDGE_MSGS::FIND_PERSONREQUEST"))
(unless (find-package "KNOWLEDGE_MSGS::FIND_PERSONRESPONSE")
  (make-package "KNOWLEDGE_MSGS::FIND_PERSONRESPONSE"))

(in-package "ROS")



(if (not (find-package "VISION_MSGS"))
  (ros::roseus-add-msgs "vision_msgs"))


(defclass knowledge_msgs::find_personRequest
  :super ros::object
  :slots (_person_face_id _location ))

(defmethod knowledge_msgs::find_personRequest
  (:init
   (&key
    ((:person_face_id __person_face_id) "")
    ((:location __location) "")
    )
   (send-super :init)
   (setq _person_face_id (string __person_face_id))
   (setq _location (string __location))
   self)
  (:person_face_id
   (&optional __person_face_id)
   (if __person_face_id (setq _person_face_id __person_face_id)) _person_face_id)
  (:location
   (&optional __location)
   (if __location (setq _location __location)) _location)
  (:serialization-length
   ()
   (+
    ;; string _person_face_id
    4 (length _person_face_id)
    ;; string _location
    4 (length _location)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _person_face_id
       (write-long (length _person_face_id) s) (princ _person_face_id s)
     ;; string _location
       (write-long (length _location) s) (princ _location s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _person_face_id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _person_face_id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _location
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _location (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass knowledge_msgs::find_personResponse
  :super ros::object
  :slots (_person_face _task_success ))

(defmethod knowledge_msgs::find_personResponse
  (:init
   (&key
    ((:person_face __person_face) (instance vision_msgs::VisionFaceObject :init))
    ((:task_success __task_success) nil)
    )
   (send-super :init)
   (setq _person_face __person_face)
   (setq _task_success __task_success)
   self)
  (:person_face
   (&rest __person_face)
   (if (keywordp (car __person_face))
       (send* _person_face __person_face)
     (progn
       (if __person_face (setq _person_face (car __person_face)))
       _person_face)))
  (:task_success
   (&optional __task_success)
   (if __task_success (setq _task_success __task_success)) _task_success)
  (:serialization-length
   ()
   (+
    ;; vision_msgs/VisionFaceObject _person_face
    (send _person_face :serialization-length)
    ;; bool _task_success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; vision_msgs/VisionFaceObject _person_face
       (send _person_face :serialize s)
     ;; bool _task_success
       (if _task_success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; vision_msgs/VisionFaceObject _person_face
     (send _person_face :deserialize buf ptr-) (incf ptr- (send _person_face :serialization-length))
   ;; bool _task_success
     (setq _task_success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass knowledge_msgs::find_person
  :super ros::object
  :slots ())

(setf (get knowledge_msgs::find_person :md5sum-) "0819b34699306bff12623f558a5cd6ca")
(setf (get knowledge_msgs::find_person :datatype-) "knowledge_msgs/find_person")
(setf (get knowledge_msgs::find_person :request) knowledge_msgs::find_personRequest)
(setf (get knowledge_msgs::find_person :response) knowledge_msgs::find_personResponse)

(defmethod knowledge_msgs::find_personRequest
  (:response () (instance knowledge_msgs::find_personResponse :init)))

(setf (get knowledge_msgs::find_personRequest :md5sum-) "0819b34699306bff12623f558a5cd6ca")
(setf (get knowledge_msgs::find_personRequest :datatype-) "knowledge_msgs/find_personRequest")
(setf (get knowledge_msgs::find_personRequest :definition-)
      "string person_face_id
string location
---
vision_msgs/VisionFaceObject person_face
bool task_success


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

(setf (get knowledge_msgs::find_personResponse :md5sum-) "0819b34699306bff12623f558a5cd6ca")
(setf (get knowledge_msgs::find_personResponse :datatype-) "knowledge_msgs/find_personResponse")
(setf (get knowledge_msgs::find_personResponse :definition-)
      "string person_face_id
string location
---
vision_msgs/VisionFaceObject person_face
bool task_success


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



(provide :knowledge_msgs/find_person "0819b34699306bff12623f558a5cd6ca")


