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

class InitKDBRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.filePath = null;
      this.run = null;
    }
    else {
      if (initObj.hasOwnProperty('filePath')) {
        this.filePath = initObj.filePath
      }
      else {
        this.filePath = '';
      }
      if (initObj.hasOwnProperty('run')) {
        this.run = initObj.run
      }
      else {
        this.run = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type InitKDBRequest
    // Serialize message field [filePath]
    bufferOffset = _serializer.string(obj.filePath, buffer, bufferOffset);
    // Serialize message field [run]
    bufferOffset = _serializer.bool(obj.run, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type InitKDBRequest
    let len;
    let data = new InitKDBRequest(null);
    // Deserialize message field [filePath]
    data.filePath = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [run]
    data.run = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.filePath.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/InitKDBRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7d40ee22877bfab4f2e1de8cb2e7b970';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string filePath
    bool run
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new InitKDBRequest(null);
    if (msg.filePath !== undefined) {
      resolved.filePath = msg.filePath;
    }
    else {
      resolved.filePath = ''
    }

    if (msg.run !== undefined) {
      resolved.run = msg.run;
    }
    else {
      resolved.run = false
    }

    return resolved;
    }
};

class InitKDBResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type InitKDBResponse
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type InitKDBResponse
    let len;
    let data = new InitKDBResponse(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/InitKDBResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new InitKDBResponse(null);
    return resolved;
    }
};

module.exports = {
  Request: InitKDBRequest,
  Response: InitKDBResponse,
  md5sum() { return '7d40ee22877bfab4f2e1de8cb2e7b970'; },
  datatype() { return 'knowledge_msgs/InitKDB'; }
};
