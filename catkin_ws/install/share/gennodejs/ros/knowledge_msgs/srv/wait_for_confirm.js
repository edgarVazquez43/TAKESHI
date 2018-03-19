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

class wait_for_confirmRequest {
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
    // Serializes a message object of type wait_for_confirmRequest
    // Serialize message field [repeat_sentence]
    bufferOffset = RepeatedSentence.serialize(obj.repeat_sentence, buffer, bufferOffset);
    // Serialize message field [timeout]
    bufferOffset = _serializer.int32(obj.timeout, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type wait_for_confirmRequest
    let len;
    let data = new wait_for_confirmRequest(null);
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
    return 'knowledge_msgs/wait_for_confirmRequest';
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
    const resolved = new wait_for_confirmRequest(null);
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

class wait_for_confirmResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.confirmation_received = null;
    }
    else {
      if (initObj.hasOwnProperty('confirmation_received')) {
        this.confirmation_received = initObj.confirmation_received
      }
      else {
        this.confirmation_received = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type wait_for_confirmResponse
    // Serialize message field [confirmation_received]
    bufferOffset = _serializer.bool(obj.confirmation_received, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type wait_for_confirmResponse
    let len;
    let data = new wait_for_confirmResponse(null);
    // Deserialize message field [confirmation_received]
    data.confirmation_received = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/wait_for_confirmResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3150393c037475b6e3f74cfde86e6112';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool confirmation_received
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new wait_for_confirmResponse(null);
    if (msg.confirmation_received !== undefined) {
      resolved.confirmation_received = msg.confirmation_received;
    }
    else {
      resolved.confirmation_received = false
    }

    return resolved;
    }
};

module.exports = {
  Request: wait_for_confirmRequest,
  Response: wait_for_confirmResponse,
  md5sum() { return 'aae0ce22da8fbc00ac2c3455196d2577'; },
  datatype() { return 'knowledge_msgs/wait_for_confirm'; }
};
