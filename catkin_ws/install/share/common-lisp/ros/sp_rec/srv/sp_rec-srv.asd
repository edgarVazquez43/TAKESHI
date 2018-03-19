
(cl:in-package :asdf)

(defsystem "sp_rec-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :sp_rec-msg
)
  :components ((:file "_package")
    (:file "ActivateDictionaries" :depends-on ("_package_ActivateDictionaries"))
    (:file "_package_ActivateDictionaries" :depends-on ("_package"))
    (:file "AddDictionary" :depends-on ("_package_AddDictionary"))
    (:file "_package_AddDictionary" :depends-on ("_package"))
    (:file "DeleteDictionaries" :depends-on ("_package_DeleteDictionaries"))
    (:file "_package_DeleteDictionaries" :depends-on ("_package"))
    (:file "GetDictionary" :depends-on ("_package_GetDictionary"))
    (:file "_package_GetDictionary" :depends-on ("_package"))
    (:file "ListDictionaries" :depends-on ("_package_ListDictionaries"))
    (:file "_package_ListDictionaries" :depends-on ("_package"))
  ))