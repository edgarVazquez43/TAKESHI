
(cl:in-package :asdf)

(defsystem "point_cloud_manager-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :sensor_msgs-msg
)
  :components ((:file "_package")
    (:file "GetRgbd" :depends-on ("_package_GetRgbd"))
    (:file "_package_GetRgbd" :depends-on ("_package"))
  ))