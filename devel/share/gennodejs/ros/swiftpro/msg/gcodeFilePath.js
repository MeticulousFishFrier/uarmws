// Auto-generated. Do not edit!

// (in-package swiftpro.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class gcodeFilePath {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gcodeFilePath = null;
    }
    else {
      if (initObj.hasOwnProperty('gcodeFilePath')) {
        this.gcodeFilePath = initObj.gcodeFilePath
      }
      else {
        this.gcodeFilePath = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type gcodeFilePath
    // Serialize message field [gcodeFilePath]
    bufferOffset = _serializer.string(obj.gcodeFilePath, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type gcodeFilePath
    let len;
    let data = new gcodeFilePath(null);
    // Deserialize message field [gcodeFilePath]
    data.gcodeFilePath = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.gcodeFilePath.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'swiftpro/gcodeFilePath';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7801f1611b4f357b77c3efe736e66a05';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string gcodeFilePath
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new gcodeFilePath(null);
    if (msg.gcodeFilePath !== undefined) {
      resolved.gcodeFilePath = msg.gcodeFilePath;
    }
    else {
      resolved.gcodeFilePath = ''
    }

    return resolved;
    }
};

module.exports = gcodeFilePath;
