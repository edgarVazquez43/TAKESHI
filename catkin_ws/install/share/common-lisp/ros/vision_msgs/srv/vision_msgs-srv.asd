
(cl:in-package :asdf)

(defsystem "vision_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :sensor_msgs-msg
               :std_msgs-msg
               :vision_msgs-msg
)
  :components ((:file "_package")
    (:file "DetectGripper" :depends-on ("_package_DetectGripper"))
    (:file "_package_DetectGripper" :depends-on ("_package"))
    (:file "DetectObjects" :depends-on ("_package_DetectObjects"))
    (:file "_package_DetectObjects" :depends-on ("_package"))
    (:file "FaceRecognition" :depends-on ("_package_FaceRecognition"))
    (:file "_package_FaceRecognition" :depends-on ("_package"))
    (:file "FindLines" :depends-on ("_package_FindLines"))
    (:file "_package_FindLines" :depends-on ("_package"))
    (:file "FindPlane" :depends-on ("_package_FindPlane"))
    (:file "_package_FindPlane" :depends-on ("_package"))
    (:file "FindWaving" :depends-on ("_package_FindWaving"))
    (:file "_package_FindWaving" :depends-on ("_package"))
    (:file "GetCubes" :depends-on ("_package_GetCubes"))
    (:file "_package_GetCubes" :depends-on ("_package"))
    (:file "GetFacesFromImage" :depends-on ("_package_GetFacesFromImage"))
    (:file "_package_GetFacesFromImage" :depends-on ("_package"))
    (:file "GetPanoramic" :depends-on ("_package_GetPanoramic"))
    (:file "_package_GetPanoramic" :depends-on ("_package"))
    (:file "GetThermalAngle" :depends-on ("_package_GetThermalAngle"))
    (:file "_package_GetThermalAngle" :depends-on ("_package"))
    (:file "RecognizeObject" :depends-on ("_package_RecognizeObject"))
    (:file "_package_RecognizeObject" :depends-on ("_package"))
    (:file "RecognizeObjects" :depends-on ("_package_RecognizeObjects"))
    (:file "_package_RecognizeObjects" :depends-on ("_package"))
    (:file "TrainObject" :depends-on ("_package_TrainObject"))
    (:file "_package_TrainObject" :depends-on ("_package"))
  ))