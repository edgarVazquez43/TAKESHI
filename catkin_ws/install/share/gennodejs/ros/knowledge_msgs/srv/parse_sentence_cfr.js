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

class parse_sentence_cfrRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sentence = null;
    }
    else {
      if (initObj.hasOwnProperty('sentence')) {
        this.sentence = initObj.sentence
      }
      else {
        this.sentence = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type parse_sentence_cfrRequest
    // Serialize message field [sentence]
    bufferOffset = _serializer.string(obj.sentence, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type parse_sentence_cfrRequest
    let len;
    let data = new parse_sentence_cfrRequest(null);
    // Deserialize message field [sentence]
    data.sentence = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.sentence.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/parse_sentence_cfrRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3ee8e7a1b3ec1e5b34263db750df6246';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string sentence
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new parse_sentence_cfrRequest(null);
    if (msg.sentence !== undefined) {
      resolved.sentence = msg.sentence;
    }
    else {
      resolved.sentence = ''
    }

    return resolved;
    }
};

class parse_sentence_cfrResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.cfr = null;
    }
    else {
      if (initObj.hasOwnProperty('cfr')) {
        this.cfr = initObj.cfr
      }
      else {
        this.cfr = new PlanningCFR();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type parse_sentence_cfrResponse
    // Serialize message field [cfr]
    bufferOffset = PlanningCFR.serialize(obj.cfr, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type parse_sentence_cfrResponse
    let len;
    let data = new parse_sentence_cfrResponse(null);
    // Deserialize message field [cfr]
    data.cfr = PlanningCFR.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += PlanningCFR.getMessageSize(object.cfr);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/parse_sentence_cfrResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cd96389c3afb6e7a34d27c969a7ac94d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    PlanningCFR cfr
    
    
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
    const resolved = new parse_sentence_cfrResponse(null);
    if (msg.cfr !== undefined) {
      resolved.cfr = PlanningCFR.Resolve(msg.cfr)
    }
    else {
      resolved.cfr = new PlanningCFR()
    }

    return resolved;
    }
};

module.exports = {
  Request: parse_sentence_cfrRequest,
  Response: parse_sentence_cfrResponse,
  md5sum() { return '953467976fe5830442f3fbb0187ffa3b'; },
  datatype() { return 'knowledge_msgs/parse_sentence_cfr'; }
};
