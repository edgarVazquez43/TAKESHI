// Auto-generated. Do not edit!

// (in-package knowledge_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let CFRParams = require('./CFRParams.js');

//-----------------------------------------------------------

class PlanningCFR {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.command = null;
      this.params = null;
    }
    else {
      if (initObj.hasOwnProperty('command')) {
        this.command = initObj.command
      }
      else {
        this.command = '';
      }
      if (initObj.hasOwnProperty('params')) {
        this.params = initObj.params
      }
      else {
        this.params = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PlanningCFR
    // Serialize message field [command]
    bufferOffset = _serializer.string(obj.command, buffer, bufferOffset);
    // Serialize message field [params]
    // Serialize the length for message field [params]
    bufferOffset = _serializer.uint32(obj.params.length, buffer, bufferOffset);
    obj.params.forEach((val) => {
      bufferOffset = CFRParams.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PlanningCFR
    let len;
    let data = new PlanningCFR(null);
    // Deserialize message field [command]
    data.command = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [params]
    // Deserialize array length for message field [params]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.params = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.params[i] = CFRParams.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.command.length;
    object.params.forEach((val) => {
      length += CFRParams.getMessageSize(val);
    });
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'knowledge_msgs/PlanningCFR';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1bda369640b5ce77a1917aec327930a1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new PlanningCFR(null);
    if (msg.command !== undefined) {
      resolved.command = msg.command;
    }
    else {
      resolved.command = ''
    }

    if (msg.params !== undefined) {
      resolved.params = new Array(msg.params.length);
      for (let i = 0; i < resolved.params.length; ++i) {
        resolved.params[i] = CFRParams.Resolve(msg.params[i]);
      }
    }
    else {
      resolved.params = []
    }

    return resolved;
    }
};

module.exports = PlanningCFR;
