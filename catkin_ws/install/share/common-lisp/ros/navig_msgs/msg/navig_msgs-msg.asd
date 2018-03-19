
(cl:in-package :asdf)

(defsystem "navig_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "Location" :depends-on ("_package_Location"))
    (:file "_package_Location" :depends-on ("_package"))
  ))