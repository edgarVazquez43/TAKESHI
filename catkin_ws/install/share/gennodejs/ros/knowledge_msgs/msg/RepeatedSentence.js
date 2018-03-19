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

class RepeatedSentence {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sentence = null;
      this.repeat_time = null;
    }
    else {
      if (initObj.hasOwnProperty('sentence')) {
        this.sentence = initObj.sentence
      }
      else {
        this.sentence = '';
      }
      if (initObj.hasOwnProperty('repeat_time')) {
        this.repeat_time = initObj.repeat_time
      }
      else {
        this.repeat_time = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RepeatedSentence
    // Serialize message field [sentence]
    bufferOffset = _serializer.string(obj.sentence, buffer, bufferOffset);
    // Serialize message field [repeat_time]
    bufferOffset = _serializer.int32(obj.repeat_time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RepeatedSentence
    let len;
    let data = new RepeatedSentence(null);
    // Deserialize message field [sentence]
    data.sentence = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [repeat_time]
    data.repeat_time = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.sentence.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'knowledge_msgs/RepeatedSentence';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '608dcaa9c362c4d6c83fcb8f1b807c83';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string sentence
    int32 repeat_time
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RepeatedSentence(null);
    if (msg.sentence !== undefined) {
      resolved.sentence = msg.sentence;
    }
    else {
      resolved.sentence = ''
    }

    if (msg.repeat_time !== undefined) {
      resolved.repeat_time = msg.repeat_time;
    }
    else {
      resolved.repeat_time = 0
    }

    return resolved;
    }
};

module.exports = RepeatedSentence;
