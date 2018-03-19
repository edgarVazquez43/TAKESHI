
(cl:in-package :asdf)

(defsystem "bbros_bridge-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "RecognizedSpeech" :depends-on ("_package_RecognizedSpeech"))
    (:file "_package_RecognizedSpeech" :depends-on ("_package"))
  ))