// Auto-generated. Do not edit!

// (in-package hri_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class RecognitionResult {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sentences = null;
      this.scores = null;
    }
    else {
      if (initObj.hasOwnProperty('sentences')) {
        this.sentences = initObj.sentences
      }
      else {
        this.sentences = [];
      }
      if (initObj.hasOwnProperty('scores')) {
        this.scores = initObj.scores
      }
      else {
        this.scores = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RecognitionResult
    // Serialize message field [sentences]
    bufferOffset = _arraySerializer.string(obj.sentences, buffer, bufferOffset, null);
    // Serialize message field [scores]
    bufferOffset = _arraySerializer.float64(obj.scores, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RecognitionResult
    let len;
    let data = new RecognitionResult(null);
    // Deserialize message field [sentences]
    data.sentences = _arrayDeserializer.string(buffer, bufferOffset, null)
    // Deserialize message field [scores]
    data.scores = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.sentences.forEach((val) => {
      length += 4 + val.length;
    });
    length += 8 * object.scores.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hri_msgs/RecognitionResult';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f96b075bcd484621907ceed990cf074d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string[] sentences
    float64[] scores
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RecognitionResult(null);
    if (msg.sentences !== undefined) {
      resolved.sentences = msg.sentences;
    }
    else {
      resolved.sentences = []
    }

    if (msg.scores !== undefined) {
      resolved.scores = msg.scores;
    }
    else {
      resolved.scores = []
    }

    return resolved;
    }
};

module.exports = RecognitionResult;
