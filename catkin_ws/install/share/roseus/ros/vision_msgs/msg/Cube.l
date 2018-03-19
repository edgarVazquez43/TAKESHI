;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::Cube)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'Cube (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::CUBE")
  (make-package "VISION_MSGS::CUBE"))

(in-package "ROS")
;;//! \htmlinclude Cube.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass vision_msgs::Cube
  :super ros::object
  :slots (_color _cube_centroid _detected_cube _minPoint _maxPoint ))

(defmethod vision_msgs::Cube
  (:init
   (&key
    ((:color __color) "")
    ((:cube_centroid __cube_centroid) (instance geometry_msgs::Point :init))
    ((:detected_cube __detected_cube) nil)
    ((:minPoint __minPoint) (instance geometry_msgs::Point :init))
    ((:maxPoint __maxPoint) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _color (string __color))
   (setq _cube_centroid __cube_centroid)
   (setq _detected_cube __detected_cube)
   (setq _minPoint __minPoint)
   (setq _maxPoint __maxPoint)
   self)
  (:color
   (&optional __color)
   (if __color (setq _color __color)) _color)
  (:cube_centroid
   (&rest __cube_centroid)
   (if (keywordp (car __cube_centroid))
       (send* _cube_centroid __cube_centroid)
     (progn
       (if __cube_centroid (setq _cube_centroid (car __cube_centroid)))
       _cube_centroid)))
  (:detected_cube
   (&optional __detected_cube)
   (if __detected_cube (setq _detected_cube __detected_cube)) _detected_cube)
  (:minPoint
   (&rest __minPoint)
   (if (keywordp (car __minPoint))
       (send* _minPoint __minPoint)
     (progn
       (if __minPoint (setq _minPoint (car __minPoint)))
       _minPoint)))
  (:maxPoint
   (&rest __maxPoint)
   (if (keywordp (car __maxPoint))
       (send* _maxPoint __maxPoint)
     (progn
       (if __maxPoint (setq _maxPoint (car __maxPoint)))
       _maxPoint)))
  (:serialization-length
   ()
   (+
    ;; string _color
    4 (length _color)
    ;; geometry_msgs/Point _cube_centroid
    (send _cube_centroid :serialization-length)
    ;; bool _detected_cube
    1
    ;; geometry_msgs/Point _minPoint
    (send _minPoint :serialization-length)
    ;; geometry_msgs/Point _maxPoint
    (send _maxPoint :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _color
       (write-long (length _color) s) (princ _color s)
     ;; geometry_msgs/Point _cube_centroid
       (send _cube_centroid :serialize s)
     ;; bool _detected_cube
       (if _detected_cube (write-byte -1 s) (write-byte 0 s))
     ;; geometry_msgs/Point _minPoint
       (send _minPoint :serialize s)
     ;; geometry_msgs/Point _maxPoint
       (send _maxPoint :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _color
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _color (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Point _cube_centroid
     (send _cube_centroid :deserialize buf ptr-) (incf ptr- (send _cube_centroid :serialization-length))
   ;; bool _detected_cube
     (setq _detected_cube (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; geometry_msgs/Point _minPoint
     (send _minPoint :deserialize buf ptr-) (incf ptr- (send _minPoint :serialization-length))
   ;; geometry_msgs/Point _maxPoint
     (send _maxPoint :deserialize buf ptr-) (incf ptr- (send _maxPoint :serialization-length))
   ;;
   self)
  )

(setf (get vision_msgs::Cube :md5sum-) "7208e2d20370e447988b77d98e81081d")
(setf (get vision_msgs::Cube :datatype-) "vision_msgs/Cube")
(setf (get vision_msgs::Cube :definition-)
      "string color #color of the cube
geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)
bool detected_cube    #flag to indicate if the cube was detected
geometry_msgs/Point minPoint	#Cube's min point
geometry_msgs/Point maxPoint	#Cube's max point

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :vision_msgs/Cube "7208e2d20370e447988b77d98e81081d")


