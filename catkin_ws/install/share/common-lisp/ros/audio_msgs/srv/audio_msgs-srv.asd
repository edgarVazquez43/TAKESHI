
(cl:in-package :asdf)

(defsystem "audio_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "srvAngle" :depends-on ("_package_srvAngle"))
    (:file "_package_srvAngle" :depends-on ("_package"))
  ))