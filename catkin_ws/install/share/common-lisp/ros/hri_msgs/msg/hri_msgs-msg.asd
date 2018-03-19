
(cl:in-package :asdf)

(defsystem "hri_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "RecognitionResult" :depends-on ("_package_RecognitionResult"))
    (:file "_package_RecognitionResult" :depends-on ("_package"))
    (:file "RecognizedSpeech" :depends-on ("_package_RecognizedSpeech"))
    (:file "_package_RecognizedSpeech" :depends-on ("_package"))
  ))