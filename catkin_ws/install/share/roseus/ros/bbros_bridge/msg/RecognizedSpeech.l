;; Auto-generated. Do not edit!


(when (boundp 'bbros_bridge::RecognizedSpeech)
  (if (not (find-package "BBROS_BRIDGE"))
    (make-package "BBROS_BRIDGE"))
  (shadow 'RecognizedSpeech (find-package "BBROS_BRIDGE")))
(unless (find-package "BBROS_BRIDGE::RECOGNIZEDSPEECH")
  (make-package "BBROS_BRIDGE::RECOGNIZEDSPEECH"))

(in-package "ROS")
;;//! \htmlinclude RecognizedSpeech.msg.html


(defclass bbros_bridge::RecognizedSpeech
  :super ros::object
  :slots (_hypothesis _confidences ))

(defmethod bbros_bridge::RecognizedSpeech
  (:init
   (&key
    ((:hypothesis __hypothesis) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:confidences __confidences) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _hypothesis __hypothesis)
   (setq _confidences __confidences)
   self)
  (:hypothesis
   (&optional __hypothesis)
   (if __hypothesis (setq _hypothesis __hypothesis)) _hypothesis)
  (:confidences
   (&optional __confidences)
   (if __confidences (setq _confidences __confidences)) _confidences)
  (:serialization-length
   ()
   (+
    ;; string[] _hypothesis
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _hypothesis)) 4
    ;; float32[] _confidences
    (* 4    (length _confidences)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string[] _hypothesis
     (write-long (length _hypothesis) s)
     (dolist (elem _hypothesis)
       (write-long (length elem) s) (princ elem s)
       )
     ;; float32[] _confidences
     (write-long (length _confidences) s)
     (dotimes (i (length _confidences))
       (sys::poke (elt _confidences i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string[] _hypothesis
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _hypothesis (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _hypothesis i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; float32[] _confidences
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _confidences (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _confidences i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get bbros_bridge::RecognizedSpeech :md5sum-) "b2cc166e4fd867bfc13e04afeee883be")
(setf (get bbros_bridge::RecognizedSpeech :datatype-) "bbros_bridge/RecognizedSpeech")
(setf (get bbros_bridge::RecognizedSpeech :definition-)
      "string[] hypothesis
float32[] confidences

")



(provide :bbros_bridge/RecognizedSpeech "b2cc166e4fd867bfc13e04afeee883be")


