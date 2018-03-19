// Auto-generated. Do not edit!

// (in-package knowledge_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let RepeatedSentence = require('../msg/RepeatedSentence.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class wait_for_switchRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.repeat_sentence = null;
      this.timeout = null;
    }
    else {
      if (initObj.hasOwnProperty('repeat_sentence')) {
        this.repeat_sentence = initObj.repeat_sentence
      }
      else {
        this.repeat_sentence = new RepeatedSentence();
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
    // Serializes a message object of type wait_for_switchRequest
    // Serialize message field [repeat_sentence]
    bufferOffset = RepeatedSentence.serialize(obj.repeat_sentence, buffer, bufferOffset);
    // Serialize message field [timeout]
    bufferOffset = _serializer.int32(obj.timeout, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type wait_for_switchRequest
    let len;
    let data = new wait_for_switchRequest(null);
    // Deserialize message field [repeat_sentence]
    data.repeat_sentence = RepeatedSentence.deserialize(buffer, bufferOffset);
    // Deserialize message field [timeout]
    data.timeout = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += RepeatedSentence.getMessageSize(object.repeat_sentence);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/wait_for_switchRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '60d2194f0127ca2638d85f847c92c9e3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    RepeatedSentence repeat_sentence
    int32 timeout
    
    ================================================================================
    MSG: knowledge_msgs/RepeatedSentence
    string sentence
    int32 repeat_time
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new wait_for_switchRequest(null);
    if (msg.repeat_sentence !== undefined) {
      resolved.repeat_sentence = RepeatedSentence.Resolve(msg.repeat_sentence)
    }
    else {
      resolved.repeat_sentence = new RepeatedSentence()
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

class wait_for_switchResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.goal = null;
      this.command_received = null;
    }
    else {
      if (initObj.hasOwnProperty('goal')) {
        this.goal = initObj.goal
      }
      else {
        this.goal = '';
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
    // Serializes a message object of type wait_for_switchResponse
    // Serialize message field [goal]
    bufferOffset = _serializer.string(obj.goal, buffer, bufferOffset);
    // Serialize message field [command_received]
    bufferOffset = _serializer.bool(obj.command_received, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type wait_for_switchResponse
    let len;
    let data = new wait_for_switchResponse(null);
    // Deserialize message field [goal]
    data.goal = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [command_received]
    data.command_received = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.goal.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/wait_for_switchResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '631067880cb0a6bfd7be10539b2be1f3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string goal
    bool command_received
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new wait_for_switchResponse(null);
    if (msg.goal !== undefined) {
      resolved.goal = msg.goal;
    }
    else {
      resolved.goal = ''
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
  Request: wait_for_switchRequest,
  Response: wait_for_switchResponse,
  md5sum() { return 'de6659e2a24efa10fd97e00db2c838ff'; },
  datatype() { return 'knowledge_msgs/wait_for_switch'; }
};
