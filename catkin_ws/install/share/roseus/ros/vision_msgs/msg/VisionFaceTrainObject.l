;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::VisionFaceTrainObject)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'VisionFaceTrainObject (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::VISIONFACETRAINOBJECT")
  (make-package "VISION_MSGS::VISIONFACETRAINOBJECT"))

(in-package "ROS")
;;//! \htmlinclude VisionFaceTrainObject.msg.html


(defclass vision_msgs::VisionFaceTrainObject
  :super ros::object
  :slots (_id _frames ))

(defmethod vision_msgs::VisionFaceTrainObject
  (:init
   (&key
    ((:id __id) "")
    ((:frames __frames) 0)
    )
   (send-super :init)
   (setq _id (string __id))
   (setq _frames (round __frames))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:frames
   (&optional __frames)
   (if __frames (setq _frames __frames)) _frames)
  (:serialization-length
   ()
   (+
    ;; string _id
    4 (length _id)
    ;; int32 _frames
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _id
       (write-long (length _id) s) (princ _id s)
     ;; int32 _frames
       (write-long _frames s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _id
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _id (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _frames
     (setq _frames (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get vision_msgs::VisionFaceTrainObject :md5sum-) "b3e8e25fcbb0fb9e09f30fa7d99356d3")
(setf (get vision_msgs::VisionFaceTrainObject :datatype-) "vision_msgs/VisionFaceTrainObject")
(setf (get vision_msgs::VisionFaceTrainObject :definition-)
      "string id                                    #face id
int32 frames                                 #Number of frames to train

")



(provide :vision_msgs/VisionFaceTrainObject "b3e8e25fcbb0fb9e09f30fa7d99356d3")


