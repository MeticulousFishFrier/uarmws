; Auto-generated. Do not edit!


(cl:in-package swiftpro-msg)


;//! \htmlinclude gcodeFilePath.msg.html

(cl:defclass <gcodeFilePath> (roslisp-msg-protocol:ros-message)
  ((gcodeFilePath
    :reader gcodeFilePath
    :initarg :gcodeFilePath
    :type cl:string
    :initform ""))
)

(cl:defclass gcodeFilePath (<gcodeFilePath>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <gcodeFilePath>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'gcodeFilePath)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name swiftpro-msg:<gcodeFilePath> is deprecated: use swiftpro-msg:gcodeFilePath instead.")))

(cl:ensure-generic-function 'gcodeFilePath-val :lambda-list '(m))
(cl:defmethod gcodeFilePath-val ((m <gcodeFilePath>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swiftpro-msg:gcodeFilePath-val is deprecated.  Use swiftpro-msg:gcodeFilePath instead.")
  (gcodeFilePath m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <gcodeFilePath>) ostream)
  "Serializes a message object of type '<gcodeFilePath>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'gcodeFilePath))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'gcodeFilePath))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <gcodeFilePath>) istream)
  "Deserializes a message object of type '<gcodeFilePath>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gcodeFilePath) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'gcodeFilePath) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<gcodeFilePath>)))
  "Returns string type for a message object of type '<gcodeFilePath>"
  "swiftpro/gcodeFilePath")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'gcodeFilePath)))
  "Returns string type for a message object of type 'gcodeFilePath"
  "swiftpro/gcodeFilePath")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<gcodeFilePath>)))
  "Returns md5sum for a message object of type '<gcodeFilePath>"
  "7801f1611b4f357b77c3efe736e66a05")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'gcodeFilePath)))
  "Returns md5sum for a message object of type 'gcodeFilePath"
  "7801f1611b4f357b77c3efe736e66a05")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<gcodeFilePath>)))
  "Returns full string definition for message of type '<gcodeFilePath>"
  (cl:format cl:nil "string gcodeFilePath~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'gcodeFilePath)))
  "Returns full string definition for message of type 'gcodeFilePath"
  (cl:format cl:nil "string gcodeFilePath~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <gcodeFilePath>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'gcodeFilePath))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <gcodeFilePath>))
  "Converts a ROS message object to a list"
  (cl:list 'gcodeFilePath
    (cl:cons ':gcodeFilePath (gcodeFilePath msg))
))
