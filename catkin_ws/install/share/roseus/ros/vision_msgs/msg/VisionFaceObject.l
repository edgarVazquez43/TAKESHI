;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::VisionFaceObject)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'VisionFaceObject (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::VISIONFACEOBJECT")
  (make-package "VISION_MSGS::VISIONFACEOBJECT"))

(in-package "ROS")
;;//! \htmlinclude VisionFaceObject.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass vision_msgs::VisionFaceObject
  :super ros::object
  :slots (_id _confidence _face_centroid _bounding_box _smile _gender ))

(defmethod vision_msgs::VisionFaceObject
  (:init
   (&key
    ((:id __id) "")
    ((:confidence __confidence) 0.0)
    ((:face_centroid __face_centroid) (instance geometry_msgs::Point :init))
    ((:bounding_box __bounding_box) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    ((:smile __smile) nil)
    ((:gender __gender) 0)
    )
   (send-super :init)
   (setq _id (string __id))
   (setq _confidence (float __confidence))
   (setq _face_centroid __face_centroid)
   (setq _bounding_box __bounding_box)
   (setq _smile __smile)
   (setq _gender (round __gender))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:confidence
   (&optional __confidence)
   (if __confidence (setq _confidence __confidence)) _confidence)
  (:face_centroid
   (&rest __face_centroid)
   (if (keywordp (car __face_centroid))
       (send* _face_centroid __face_centroid)
     (progn
       (if __face_centroid (setq _face_centroid (car __face_centroid)))
       _face_centroid)))
  (:bounding_box
   (&rest __bounding_box)
   (if (keywordp (car __bounding_box))
       (send* _bounding_box __bounding_box)
     (progn
       (if __bounding_box (setq _bounding_box (car __bounding_box)))
       _bounding_box)))
  (:smile
   (&optional __smile)
   (if __smile (setq _smile __smile)) _smile)
  (:gender
   (&optional __gender)
   (if __gender (setq _gender __gender)) _gender)
  (:serialization-length
   ()
   (+
    ;; string _id
    4 (length _id)
    ;; float32 _confidence
    4
    ;; geometry_msgs/Point _face_centroid
    (send _face_centroid :serialization-length)
    ;; geometry_msgs/Point[] _bounding_box
    (apply #'+ (send-all _bounding_box :serialization-length)) 4
    ;; bool _smile
    1
    ;; int8 _gender
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; float32 _confidence
       (sys::poke _confidence (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; geometry_msgs/Point _face_centroid
       (send _face_centroid :serialize s)
     ;; geometry_msgs/Point[] _bounding_box
     (write-long (length _bounding_box) s)
     (dolist (elem _bounding_box)
       (send elem :serialize s)
       )
     ;; bool _smile
       (if _smile (write-byte -1 s) (write-byte 0 s))
     ;; int8 _gender
       (write-byte _gender s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32 _confidence
     (setq _confidence (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; geometry_msgs/Point _face_centroid
     (send _face_centroid :deserialize buf ptr-) (incf ptr- (send _face_centroid :serialization-length))
   ;; geometry_msgs/Point[] _bounding_box
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _bounding_box (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _bounding_box)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; bool _smile
     (setq _smile (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int8 _gender
     (setq _gender (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _gender 127) (setq _gender (- _gender 256)))
   ;;
   self)
  )

(setf (get vision_msgs::VisionFaceObject :md5sum-) "93b90fa2697ed03b7e1dd7001e2d8cff")
(setf (get vision_msgs::VisionFaceObject :datatype-) "vision_msgs/VisionFaceObject")
(setf (get vision_msgs::VisionFaceObject :definition-)
      "string id                                    #face id
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



(provide :vision_msgs/VisionFaceObject "93b90fa2697ed03b7e1dd7001e2d8cff")


