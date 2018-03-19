// Auto-generated. Do not edit!

// (in-package bbros_bridge.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class hd_torqueRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.enable = null;
    }
    else {
      if (initObj.hasOwnProperty('enable')) {
        this.enable = initObj.enable
      }
      else {
        this.enable = new std_msgs.msg.Bool();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type hd_torqueRequest
    // Serialize message field [enable]
    bufferOffset = std_msgs.msg.Bool.serialize(obj.enable, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type hd_torqueRequest
    let len;
    let data = new hd_torqueRequest(null);
    // Deserialize message field [enable]
    data.enable = std_msgs.msg.Bool.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/hd_torqueRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c94b48865c522830ab172ce493501afc';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Bool enable
    
    ================================================================================
    MSG: std_msgs/Bool
    bool data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new hd_torqueRequest(null);
    if (msg.enable !== undefined) {
      resolved.enable = std_msgs.msg.Bool.Resolve(msg.enable)
    }
    else {
      resolved.enable = new std_msgs.msg.Bool()
    }

    return resolved;
    }
};

class hd_torqueResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.errors = null;
    }
    else {
      if (initObj.hasOwnProperty('errors')) {
        this.errors = initObj.errors
      }
      else {
        this.errors = new std_msgs.msg.String();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type hd_torqueResponse
    // Serialize message field [errors]
    bufferOffset = std_msgs.msg.String.serialize(obj.errors, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type hd_torqueResponse
    let len;
    let data = new hd_torqueResponse(null);
    // Deserialize message field [errors]
    data.errors = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.String.getMessageSize(object.errors);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/hd_torqueResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5c3e9cddcecd48bec5347f4d784d98ff';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/String errors
    
    
    ================================================================================
    MSG: std_msgs/String
    string data
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new hd_torqueResponse(null);
    if (msg.errors !== undefined) {
      resolved.errors = std_msgs.msg.String.Resolve(msg.errors)
    }
    else {
      resolved.errors = new std_msgs.msg.String()
    }

    return resolved;
    }
};

module.exports = {
  Request: hd_torqueRequest,
  Response: hd_torqueResponse,
  md5sum() { return '5ec6cba259224de8444ec81114c3fa2f'; },
  datatype() { return 'bbros_bridge/hd_torque'; }
};
