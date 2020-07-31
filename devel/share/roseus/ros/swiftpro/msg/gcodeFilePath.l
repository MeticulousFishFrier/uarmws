;; Auto-generated. Do not edit!


(when (boundp 'swiftpro::gcodeFilePath)
  (if (not (find-package "SWIFTPRO"))
    (make-package "SWIFTPRO"))
  (shadow 'gcodeFilePath (find-package "SWIFTPRO")))
(unless (find-package "SWIFTPRO::GCODEFILEPATH")
  (make-package "SWIFTPRO::GCODEFILEPATH"))

(in-package "ROS")
;;//! \htmlinclude gcodeFilePath.msg.html


(defclass swiftpro::gcodeFilePath
  :super ros::object
  :slots (_gcodeFilePath ))

(defmethod swiftpro::gcodeFilePath
  (:init
   (&key
    ((:gcodeFilePath __gcodeFilePath) "")
    )
   (send-super :init)
   (setq _gcodeFilePath (string __gcodeFilePath))
   self)
  (:gcodeFilePath
   (&optional __gcodeFilePath)
   (if __gcodeFilePath (setq _gcodeFilePath __gcodeFilePath)) _gcodeFilePath)
  (:serialization-length
   ()
   (+
    ;; string _gcodeFilePath
    4 (length _gcodeFilePath)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _gcodeFilePath
       (write-long (length _gcodeFilePath) s) (princ _gcodeFilePath s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _gcodeFilePath
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _gcodeFilePath (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get swiftpro::gcodeFilePath :md5sum-) "7801f1611b4f357b77c3efe736e66a05")
(setf (get swiftpro::gcodeFilePath :datatype-) "swiftpro/gcodeFilePath")
(setf (get swiftpro::gcodeFilePath :definition-)
      "string gcodeFilePath
")



(provide :swiftpro/gcodeFilePath "7801f1611b4f357b77c3efe736e66a05")


