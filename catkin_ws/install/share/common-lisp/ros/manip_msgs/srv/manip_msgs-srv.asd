
(cl:in-package :asdf)

(defsystem "manip_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :nav_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "DirectKinematics" :depends-on ("_package_DirectKinematics"))
    (:file "_package_DirectKinematics" :depends-on ("_package"))
    (:file "DirectKinematicsFloatArray" :depends-on ("_package_DirectKinematicsFloatArray"))
    (:file "_package_DirectKinematicsFloatArray" :depends-on ("_package"))
    (:file "InverseKinematicsFloatArray" :depends-on ("_package_InverseKinematicsFloatArray"))
    (:file "_package_InverseKinematicsFloatArray" :depends-on ("_package"))
    (:file "InverseKinematicsPath" :depends-on ("_package_InverseKinematicsPath"))
    (:file "_package_InverseKinematicsPath" :depends-on ("_package"))
    (:file "InverseKinematicsPose" :depends-on ("_package_InverseKinematicsPose"))
    (:file "_package_InverseKinematicsPose" :depends-on ("_package"))
  ))