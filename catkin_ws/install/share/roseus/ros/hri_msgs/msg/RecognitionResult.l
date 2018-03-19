;; Auto-generated. Do not edit!


(when (boundp 'hri_msgs::RecognitionResult)
  (if (not (find-package "HRI_MSGS"))
    (make-package "HRI_MSGS"))
  (shadow 'RecognitionResult (find-package "HRI_MSGS")))
(unless (find-package "HRI_MSGS::RECOGNITIONRESULT")
  (make-package "HRI_MSGS::RECOGNITIONRESULT"))

(in-package "ROS")
;;//! \htmlinclude RecognitionResult.msg.html


(defclass hri_msgs::RecognitionResult
  :super ros::object
  :slots (_sentences _scores ))

(defmethod hri_msgs::RecognitionResult
  (:init
   (&key
    ((:sentences __sentences) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:scores __scores) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _sentences __sentences)
   (setq _scores __scores)
   self)
  (:sentences
   (&optional __sentences)
   (if __sentences (setq _sentences __sentences)) _sentences)
  (:scores
   (&optional __scores)
   (if __scores (setq _scores __scores)) _scores)
  (:serialization-length
   ()
   (+
    ;; string[] _sentences
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _sentences)) 4
    ;; float64[] _scores
    (* 8    (length _scores)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string[] _sentences
     (write-long (length _sentences) s)
     (dolist (elem _sentences)
       (write-long (length elem) s) (princ elem s)
       )
     ;; float64[] _scores
     (write-long (length _scores) s)
     (dotimes (i (length _scores))
       (sys::poke (elt _scores i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string[] _sentences
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _sentences (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _sentences i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; float64[] _scores
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _scores (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _scores i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get hri_msgs::RecognitionResult :md5sum-) "f96b075bcd484621907ceed990cf074d")
(setf (get hri_msgs::RecognitionResult :datatype-) "hri_msgs/RecognitionResult")
(setf (get hri_msgs::RecognitionResult :definition-)
      "string[] sentences
float64[] scores


")



(provide :hri_msgs/RecognitionResult "f96b075bcd484621907ceed990cf074d")


