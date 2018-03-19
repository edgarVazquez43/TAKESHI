// Auto-generated. Do not edit!

// (in-package knowledge_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class ask_store_nameRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.attempt_timeout = null;
      this.repeat_timeout = null;
      this.max_attempts = null;
    }
    else {
      if (initObj.hasOwnProperty('attempt_timeout')) {
        this.attempt_timeout = initObj.attempt_timeout
      }
      else {
        this.attempt_timeout = 0;
      }
      if (initObj.hasOwnProperty('repeat_timeout')) {
        this.repeat_timeout = initObj.repeat_timeout
      }
      else {
        this.repeat_timeout = 0;
      }
      if (initObj.hasOwnProperty('max_attempts')) {
        this.max_attempts = initObj.max_attempts
      }
      else {
        this.max_attempts = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ask_store_nameRequest
    // Serialize message field [attempt_timeout]
    bufferOffset = _serializer.int32(obj.attempt_timeout, buffer, bufferOffset);
    // Serialize message field [repeat_timeout]
    bufferOffset = _serializer.int32(obj.repeat_timeout, buffer, bufferOffset);
    // Serialize message field [max_attempts]
    bufferOffset = _serializer.int32(obj.max_attempts, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ask_store_nameRequest
    let len;
    let data = new ask_store_nameRequest(null);
    // Deserialize message field [attempt_timeout]
    data.attempt_timeout = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [repeat_timeout]
    data.repeat_timeout = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [max_attempts]
    data.max_attempts = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/ask_store_nameRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2572b3fb9d176b75a92c814bb14b18b8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 attempt_timeout
    int32 repeat_timeout
    int32 max_attempts
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ask_store_nameRequest(null);
    if (msg.attempt_timeout !== undefined) {
      resolved.attempt_timeout = msg.attempt_timeout;
    }
    else {
      resolved.attempt_timeout = 0
    }

    if (msg.repeat_timeout !== undefined) {
      resolved.repeat_timeout = msg.repeat_timeout;
    }
    else {
      resolved.repeat_timeout = 0
    }

    if (msg.max_attempts !== undefined) {
      resolved.max_attempts = msg.max_attempts;
    }
    else {
      resolved.max_attempts = 0
    }

    return resolved;
    }
};

class ask_store_nameResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
      this.stored_name = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
      if (initObj.hasOwnProperty('stored_name')) {
        this.stored_name = initObj.stored_name
      }
      else {
        this.stored_name = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ask_store_nameResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    // Serialize message field [stored_name]
    bufferOffset = _serializer.string(obj.stored_name, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ask_store_nameResponse
    let len;
    let data = new ask_store_nameResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [stored_name]
    data.stored_name = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.stored_name.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/ask_store_nameResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c03d4bbc2e5563b50d6af9b12d120fe9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool success
    string stored_name
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ask_store_nameResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    if (msg.stored_name !== undefined) {
      resolved.stored_name = msg.stored_name;
    }
    else {
      resolved.stored_name = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: ask_store_nameRequest,
  Response: ask_store_nameResponse,
  md5sum() { return '8a5870e234d40e3af46fc0ab4649d821'; },
  datatype() { return 'knowledge_msgs/ask_store_name'; }
};
