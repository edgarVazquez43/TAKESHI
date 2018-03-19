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

let PlanningCFR = require('../msg/PlanningCFR.js');

//-----------------------------------------------------------

class wait_for_commandRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.timeout = null;
    }
    else {
      if (initObj.hasOwnProperty('timeout')) {
        this.timeout = initObj.timeout
      }
      else {
        this.timeout = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type wait_for_commandRequest
    // Serialize message field [timeout]
    bufferOffset = _serializer.int32(obj.timeout, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type wait_for_commandRequest
    let len;
    let data = new wait_for_commandRequest(null);
    // Deserialize message field [timeout]
    data.timeout = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/wait_for_commandRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '59c7c94880c7082d9353d4d0a3356213';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 timeout
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new wait_for_commandRequest(null);
    if (msg.timeout !== undefined) {
      resolved.timeout = msg.timeout;
    }
    else {
      resolved.timeout = 0
    }

    return resolved;
    }
};

class wait_for_commandResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.cfr = null;
      this.command_received = null;
    }
    else {
      if (initObj.hasOwnProperty('cfr')) {
        this.cfr = initObj.cfr
      }
      else {
        this.cfr = new PlanningCFR();
      }
      if (initObj.hasOwnProperty('command_received')) {
        this.command_received = initObj.command_received
      }
      else {
        this.command_received = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type wait_for_commandResponse
    // Serialize message field [cfr]
    bufferOffset = PlanningCFR.serialize(obj.cfr, buffer, bufferOffset);
    // Serialize message field [command_received]
    bufferOffset = _serializer.bool(obj.command_received, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type wait_for_commandResponse
    let len;
    let data = new wait_for_commandResponse(null);
    // Deserialize message field [cfr]
    data.cfr = PlanningCFR.deserialize(buffer, bufferOffset);
    // Deserialize message field [command_received]
    data.command_received = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += PlanningCFR.getMessageSize(object.cfr);
    return length + 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/wait_for_commandResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e163bed3671252577a854472ef22d315';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    PlanningCFR cfr
    bool command_received
    
    
    ================================================================================
    MSG: knowledge_msgs/PlanningCFR
    string command
    CFRParams[] params
    
    ================================================================================
    MSG: knowledge_msgs/CFRParams
    string frame_id
    string frame_value
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new wait_for_commandResponse(null);
    if (msg.cfr !== undefined) {
      resolved.cfr = PlanningCFR.Resolve(msg.cfr)
    }
    else {
      resolved.cfr = new PlanningCFR()
    }

    if (msg.command_received !== undefined) {
      resolved.command_received = msg.command_received;
    }
    else {
      resolved.command_received = false
    }

    return resolved;
    }
};

module.exports = {
  Request: wait_for_commandRequest,
  Response: wait_for_commandResponse,
  md5sum() { return 'f286b9f490839fee63da1e5ff1e054a7'; },
  datatype() { return 'knowledge_msgs/wait_for_command'; }
};
