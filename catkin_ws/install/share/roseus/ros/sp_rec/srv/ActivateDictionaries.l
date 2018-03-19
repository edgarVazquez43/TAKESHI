;; Auto-generated. Do not edit!


(when (boundp 'sp_rec::ActivateDictionaries)
  (if (not (find-package "SP_REC"))
    (make-package "SP_REC"))
  (shadow 'ActivateDictionaries (find-package "SP_REC")))
(unless (find-package "SP_REC::ACTIVATEDICTIONARIES")
  (make-package "SP_REC::ACTIVATEDICTIONARIES"))
(unless (find-package "SP_REC::ACTIVATEDICTIONARIESREQUEST")
  (make-package "SP_REC::ACTIVATEDICTIONARIESREQUEST"))
(unless (find-package "SP_REC::ACTIVATEDICTIONARIESRESPONSE")
  (make-package "SP_REC::ACTIVATEDICTIONARIESRESPONSE"))

(in-package "ROS")





(defclass sp_rec::ActivateDictionariesRequest
  :super ros::object
  :slots (_names _active ))

(defmethod sp_rec::ActivateDictionariesRequest
  (:init
   (&key
    ((:names __names) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:active __active) nil)
    )
   (send-super :init)
   (setq _names __names)
   (setq _active __active)
   self)
  (:names
   (&optional __names)
   (if __names (setq _names __names)) _names)
  (:active
   (&optional __active)
   (if __active (setq _active __active)) _active)
  (:serialization-length
   ()
   (+
    ;; string[] _names
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _names)) 4
    ;; bool _active
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string[] _names
     (write-long (length _names) s)
     (dolist (elem _names)
       (write-long (length elem) s) (princ elem s)
       )
     ;; bool _active
       (if _active (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string[] _names
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _names (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _names i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; bool _active
     (setq _active (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass sp_rec::ActivateDictionariesResponse
  :super ros::object
  :slots (_result _message ))

(defmethod sp_rec::ActivateDictionariesResponse
  (:init
   (&key
    ((:result __result) nil)
    ((:message __message) "")
    )
   (send-super :init)
   (setq _result __result)
   (setq _message (string __message))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:message
   (&optional __message)
   (if __message (setq _message __message)) _message)
  (:serialization-length
   ()
   (+
    ;; bool _result
    1
    ;; string _message
    4 (length _message)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _result
       (if _result (write-byte -1 s) (write-byte 0 s))
     ;; string _message
       (write-long (length _message) s) (princ _message s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _result
     (setq _result (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _message
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass sp_rec::ActivateDictionaries
  :super ros::object
  :slots ())

(setf (get sp_rec::ActivateDictionaries :md5sum-) "76e09ccff84329f0f31723b25e6297e8")
(setf (get sp_rec::ActivateDictionaries :datatype-) "sp_rec/ActivateDictionaries")
(setf (get sp_rec::ActivateDictionaries :request) sp_rec::ActivateDictionariesRequest)
(setf (get sp_rec::ActivateDictionaries :response) sp_rec::ActivateDictionariesResponse)

(defmethod sp_rec::ActivateDictionariesRequest
  (:response () (instance sp_rec::ActivateDictionariesResponse :init)))

(setf (get sp_rec::ActivateDictionariesRequest :md5sum-) "76e09ccff84329f0f31723b25e6297e8")
(setf (get sp_rec::ActivateDictionariesRequest :datatype-) "sp_rec/ActivateDictionariesRequest")
(setf (get sp_rec::ActivateDictionariesRequest :definition-)
      "
string[] names


bool active

---


bool result


string message

")

(setf (get sp_rec::ActivateDictionariesResponse :md5sum-) "76e09ccff84329f0f31723b25e6297e8")
(setf (get sp_rec::ActivateDictionariesResponse :datatype-) "sp_rec/ActivateDictionariesResponse")
(setf (get sp_rec::ActivateDictionariesResponse :definition-)
      "
string[] names


bool active

---


bool result


string message

")



(provide :sp_rec/ActivateDictionaries "76e09ccff84329f0f31723b25e6297e8")


