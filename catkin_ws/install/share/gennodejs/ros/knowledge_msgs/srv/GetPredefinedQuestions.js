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

let MapPredefinedQuestions = require('../msg/MapPredefinedQuestions.js');

//-----------------------------------------------------------

class GetPredefinedQuestionsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetPredefinedQuestionsRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetPredefinedQuestionsRequest
    let len;
    let data = new GetPredefinedQuestionsRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/GetPredefinedQuestionsRequest';
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
    const resolved = new GetPredefinedQuestionsRequest(null);
    return resolved;
    }
};

class GetPredefinedQuestionsResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.predefinedQuestions = null;
    }
    else {
      if (initObj.hasOwnProperty('predefinedQuestions')) {
        this.predefinedQuestions = initObj.predefinedQuestions
      }
      else {
        this.predefinedQuestions = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetPredefinedQuestionsResponse
    // Serialize message field [predefinedQuestions]
    // Serialize the length for message field [predefinedQuestions]
    bufferOffset = _serializer.uint32(obj.predefinedQuestions.length, buffer, bufferOffset);
    obj.predefinedQuestions.forEach((val) => {
      bufferOffset = MapPredefinedQuestions.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetPredefinedQuestionsResponse
    let len;
    let data = new GetPredefinedQuestionsResponse(null);
    // Deserialize message field [predefinedQuestions]
    // Deserialize array length for message field [predefinedQuestions]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.predefinedQuestions = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.predefinedQuestions[i] = MapPredefinedQuestions.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.predefinedQuestions.forEach((val) => {
      length += MapPredefinedQuestions.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/GetPredefinedQuestionsResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '68d94395b4ec7b52f8954f4e6ebf72fa';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    MapPredefinedQuestions[] predefinedQuestions
    
    
    ================================================================================
    MSG: knowledge_msgs/MapPredefinedQuestions
    string question
    string answer
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetPredefinedQuestionsResponse(null);
    if (msg.predefinedQuestions !== undefined) {
      resolved.predefinedQuestions = new Array(msg.predefinedQuestions.length);
      for (let i = 0; i < resolved.predefinedQuestions.length; ++i) {
        resolved.predefinedQuestions[i] = MapPredefinedQuestions.Resolve(msg.predefinedQuestions[i]);
      }
    }
    else {
      resolved.predefinedQuestions = []
    }

    return resolved;
    }
};

module.exports = {
  Request: GetPredefinedQuestionsRequest,
  Response: GetPredefinedQuestionsResponse,
  md5sum() { return '68d94395b4ec7b52f8954f4e6ebf72fa'; },
  datatype() { return 'knowledge_msgs/GetPredefinedQuestions'; }
};
