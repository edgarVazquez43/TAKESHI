// Auto-generated. Do not edit!

// (in-package knowledge_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class MapPredefinedQuestions {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.question = null;
      this.answer = null;
    }
    else {
      if (initObj.hasOwnProperty('question')) {
        this.question = initObj.question
      }
      else {
        this.question = '';
      }
      if (initObj.hasOwnProperty('answer')) {
        this.answer = initObj.answer
      }
      else {
        this.answer = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MapPredefinedQuestions
    // Serialize message field [question]
    bufferOffset = _serializer.string(obj.question, buffer, bufferOffset);
    // Serialize message field [answer]
    bufferOffset = _serializer.string(obj.answer, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MapPredefinedQuestions
    let len;
    let data = new MapPredefinedQuestions(null);
    // Deserialize message field [question]
    data.question = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [answer]
    data.answer = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.question.length;
    length += object.answer.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'knowledge_msgs/MapPredefinedQuestions';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a27d8629aeefd2b315942fe4a74ab143';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string question
    string answer
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MapPredefinedQuestions(null);
    if (msg.question !== undefined) {
      resolved.question = msg.question;
    }
    else {
      resolved.question = ''
    }

    if (msg.answer !== undefined) {
      resolved.answer = msg.answer;
    }
    else {
      resolved.answer = ''
    }

    return resolved;
    }
};

module.exports = MapPredefinedQuestions;
