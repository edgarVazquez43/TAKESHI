;; Auto-generated. Do not edit!


(when (boundp 'vision_msgs::FindWaving)
  (if (not (find-package "VISION_MSGS"))
    (make-package "VISION_MSGS"))
  (shadow 'FindWaving (find-package "VISION_MSGS")))
(unless (find-package "VISION_MSGS::FINDWAVING")
  (make-package "VISION_MSGS::FINDWAVING"))
(unless (find-package "VISION_MSGS::FINDWAVINGREQUEST")
  (make-package "VISION_MSGS::FINDWAVINGREQUEST"))
(unless (find-package "VISION_MSGS::FINDWAVINGRESPONSE")
  (make-package "VISION_MSGS::FINDWAVINGRESPONSE"))

(in-package "ROS")



(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass vision_msgs::FindWavingRequest
  :super ros::object
  :slots ())

(defmethod vision_msgs::FindWavingRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass vision_msgs::FindWavingResponse
  :super ros::object
  :slots (_bounding_box _frame_width _frame_height ))

(defmethod vision_msgs::FindWavingResponse
  (:init
   (&key
    ((:bounding_box __bounding_box) (let (r) (dotimes (i 0) (push (instance vision_msgs::VisionRect :init) r)) r))
    ((:frame_width __frame_width) (instance std_msgs::Int32 :init))
    ((:frame_height __frame_height) (instance std_msgs::Int32 :init))
    )
   (send-super :init)
   (setq _bounding_box __bounding_box)
   (setq _frame_width __frame_width)
   (setq _frame_height __frame_height)
   self)
  (:bounding_box
   (&rest __bounding_box)
   (if (keywordp (car __bounding_box))
       (send* _bounding_box __bounding_box)
     (progn
       (if __bounding_box (setq _bounding_box (car __bounding_box)))
       _bounding_box)))
  (:frame_width
   (&rest __frame_width)
   (if (keywordp (car __frame_width))
       (send* _frame_width __frame_width)
     (progn
       (if __frame_width (setq _frame_width (car __frame_width)))
       _frame_width)))
  (:frame_height
   (&rest __frame_height)
   (if (keywordp (car __frame_height))
       (send* _frame_height __frame_height)
     (progn
       (if __frame_height (setq _frame_height (car __frame_height)))
       _frame_height)))
  (:serialization-length
   ()
   (+
    ;; vision_msgs/VisionRect[] _bounding_box
    (apply #'+ (send-all _bounding_box :serialization-length)) 4
    ;; std_msgs/Int32 _frame_width
    (send _frame_width :serialization-length)
    ;; std_msgs/Int32 _frame_height
    (send _frame_height :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; vision_msgs/VisionRect[] _bounding_box
     (write-long (length _bounding_box) s)
     (dolist (elem _bounding_box)
       (send elem :serialize s)
       )
     ;; std_msgs/Int32 _frame_width
       (send _frame_width :serialize s)
     ;; std_msgs/Int32 _frame_height
       (send _frame_height :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; vision_msgs/VisionRect[] _bounding_box
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _bounding_box (let (r) (dotimes (i n) (push (instance vision_msgs::VisionRect :init) r)) r))
     (dolist (elem- _bounding_box)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; std_msgs/Int32 _frame_width
     (send _frame_width :deserialize buf ptr-) (incf ptr- (send _frame_width :serialization-length))
   ;; std_msgs/Int32 _frame_height
     (send _frame_height :deserialize buf ptr-) (incf ptr- (send _frame_height :serialization-length))
   ;;
   self)
  )

(defclass vision_msgs::FindWaving
  :super ros::object
  :slots ())

(setf (get vision_msgs::FindWaving :md5sum-) "a5efa18c4fad16dbe94cb16a4d7151ec")
(setf (get vision_msgs::FindWaving :datatype-) "vision_msgs/FindWaving")
(setf (get vision_msgs::FindWaving :request) vision_msgs::FindWavingRequest)
(setf (get vision_msgs::FindWaving :response) vision_msgs::FindWavingResponse)

(defmethod vision_msgs::FindWavingRequest
  (:response () (instance vision_msgs::FindWavingResponse :init)))

(setf (get vision_msgs::FindWavingRequest :md5sum-) "a5efa18c4fad16dbe94cb16a4d7151ec")
(setf (get vision_msgs::FindWavingRequest :datatype-) "vision_msgs/FindWavingRequest")
(setf (get vision_msgs::FindWavingRequest :definition-)
      "---
vision_msgs/VisionRect[] bounding_box
std_msgs/Int32 frame_width
std_msgs/Int32 frame_height



================================================================================
MSG: vision_msgs/VisionRect
int32 x
int32 y
int32 width
int32 height

================================================================================
MSG: std_msgs/Int32
")

(setf (get vision_msgs::FindWavingResponse :md5sum-) "a5efa18c4fad16dbe94cb16a4d7151ec")
(setf (get vision_msgs::FindWavingResponse :datatype-) "vision_msgs/FindWavingResponse")
(setf (get vision_msgs::FindWavingResponse :definition-)
      "---
vision_msgs/VisionRect[] bounding_box
std_msgs/Int32 frame_width
std_msgs/Int32 frame_height



================================================================================
MSG: vision_msgs/VisionRect
int32 x
int32 y
int32 width
int32 height

================================================================================
MSG: std_msgs/Int32
")



(provide :vision_msgs/FindWaving "a5efa18c4fad16dbe94cb16a4d7151ec")


