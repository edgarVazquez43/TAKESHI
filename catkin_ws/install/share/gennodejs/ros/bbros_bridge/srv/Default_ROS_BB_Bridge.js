// Auto-generated. Do not edit!

// (in-package bbros_bridge.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class Default_ROS_BB_BridgeRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.parameters = null;
      this.timeout = null;
    }
    else {
      if (initObj.hasOwnProperty('parameters')) {
        this.parameters = initObj.parameters
      }
      else {
        this.parameters = '';
      }
      if (initObj.hasOwnProperty('timeout')) {
        this.timeout = initObj.timeout
      }
      else {
        this.timeout = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Default_ROS_BB_BridgeRequest
    // Serialize message field [parameters]
    bufferOffset = _serializer.string(obj.parameters, buffer, bufferOffset);
    // Serialize message field [timeout]
    bufferOffset = _serializer.int16(obj.timeout, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Default_ROS_BB_BridgeRequest
    let len;
    let data = new Default_ROS_BB_BridgeRequest(null);
    // Deserialize message field [parameters]
    data.parameters = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [timeout]
    data.timeout = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.parameters.length;
    return length + 6;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/Default_ROS_BB_BridgeRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd331c0a65a4491a774abbf2cc3fa6bd6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string parameters
    int16 timeout
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Default_ROS_BB_BridgeRequest(null);
    if (msg.parameters !== undefined) {
      resolved.parameters = msg.parameters;
    }
    else {
      resolved.parameters = ''
    }

    if (msg.timeout !== undefined) {
      resolved.timeout = msg.timeout;
    }
    else {
      resolved.timeout = 0
    }

    return resolved;
    }
};

class Default_ROS_BB_BridgeResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
      this.response = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
      if (initObj.hasOwnProperty('response')) {
        this.response = initObj.response
      }
      else {
        this.response = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Default_ROS_BB_BridgeResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    // Serialize message field [response]
    bufferOffset = _serializer.string(obj.response, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Default_ROS_BB_BridgeResponse
    let len;
    let data = new Default_ROS_BB_BridgeResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [response]
    data.response = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.response.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/Default_ROS_BB_BridgeResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '187f74b76a3c78db0f92719010b77755';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool success
    string response
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Default_ROS_BB_BridgeResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    if (msg.response !== undefined) {
      resolved.response = msg.response;
    }
    else {
      resolved.response = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: Default_ROS_BB_BridgeRequest,
  Response: Default_ROS_BB_BridgeResponse,
  md5sum() { return 'dc72b6691678f98c1cd8b4c963031bd5'; },
  datatype() { return 'bbros_bridge/Default_ROS_BB_Bridge'; }
};
