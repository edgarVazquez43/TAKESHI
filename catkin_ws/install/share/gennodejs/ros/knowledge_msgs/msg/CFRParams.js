// Auto-generated. Do not edit!

// (in-package knowledge_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class CFRParams {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.frame_id = null;
      this.frame_value = null;
    }
    else {
      if (initObj.hasOwnProperty('frame_id')) {
        this.frame_id = initObj.frame_id
      }
      else {
        this.frame_id = '';
      }
      if (initObj.hasOwnProperty('frame_value')) {
        this.frame_value = initObj.frame_value
      }
      else {
        this.frame_value = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CFRParams
    // Serialize message field [frame_id]
    bufferOffset = _serializer.string(obj.frame_id, buffer, bufferOffset);
    // Serialize message field [frame_value]
    bufferOffset = _serializer.string(obj.frame_value, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CFRParams
    let len;
    let data = new CFRParams(null);
    // Deserialize message field [frame_id]
    data.frame_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [frame_value]
    data.frame_value = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.frame_id.length;
    length += object.frame_value.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'knowledge_msgs/CFRParams';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4244adddfc44a0d0799b10600c99b834';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string frame_id
    string frame_value
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CFRParams(null);
    if (msg.frame_id !== undefined) {
      resolved.frame_id = msg.frame_id;
    }
    else {
      resolved.frame_id = ''
    }

    if (msg.frame_value !== undefined) {
      resolved.frame_value = msg.frame_value;
    }
    else {
      resolved.frame_value = ''
    }

    return resolved;
    }
};

module.exports = CFRParams;
