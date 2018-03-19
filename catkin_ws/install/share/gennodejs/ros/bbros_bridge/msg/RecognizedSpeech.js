// Auto-generated. Do not edit!

// (in-package bbros_bridge.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class RecognizedSpeech {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.hypothesis = null;
      this.confidences = null;
    }
    else {
      if (initObj.hasOwnProperty('hypothesis')) {
        this.hypothesis = initObj.hypothesis
      }
      else {
        this.hypothesis = [];
      }
      if (initObj.hasOwnProperty('confidences')) {
        this.confidences = initObj.confidences
      }
      else {
        this.confidences = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RecognizedSpeech
    // Serialize message field [hypothesis]
    bufferOffset = _arraySerializer.string(obj.hypothesis, buffer, bufferOffset, null);
    // Serialize message field [confidences]
    bufferOffset = _arraySerializer.float32(obj.confidences, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RecognizedSpeech
    let len;
    let data = new RecognizedSpeech(null);
    // Deserialize message field [hypothesis]
    data.hypothesis = _arrayDeserializer.string(buffer, bufferOffset, null)
    // Deserialize message field [confidences]
    data.confidences = _arrayDeserializer.float32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.hypothesis.forEach((val) => {
      length += 4 + val.length;
    });
    length += 4 * object.confidences.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'bbros_bridge/RecognizedSpeech';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b2cc166e4fd867bfc13e04afeee883be';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string[] hypothesis
    float32[] confidences
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RecognizedSpeech(null);
    if (msg.hypothesis !== undefined) {
      resolved.hypothesis = msg.hypothesis;
    }
    else {
      resolved.hypothesis = []
    }

    if (msg.confidences !== undefined) {
      resolved.confidences = msg.confidences;
    }
    else {
      resolved.confidences = []
    }

    return resolved;
    }
};

module.exports = RecognizedSpeech;
