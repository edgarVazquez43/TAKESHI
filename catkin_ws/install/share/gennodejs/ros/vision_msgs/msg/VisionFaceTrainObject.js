// Auto-generated. Do not edit!

// (in-package vision_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class VisionFaceTrainObject {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.frames = null;
    }
    else {
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = '';
      }
      if (initObj.hasOwnProperty('frames')) {
        this.frames = initObj.frames
      }
      else {
        this.frames = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VisionFaceTrainObject
    // Serialize message field [id]
    bufferOffset = _serializer.string(obj.id, buffer, bufferOffset);
    // Serialize message field [frames]
    bufferOffset = _serializer.int32(obj.frames, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VisionFaceTrainObject
    let len;
    let data = new VisionFaceTrainObject(null);
    // Deserialize message field [id]
    data.id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [frames]
    data.frames = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.id.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/VisionFaceTrainObject';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b3e8e25fcbb0fb9e09f30fa7d99356d3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string id                                    #face id
    int32 frames                                 #Number of frames to train
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VisionFaceTrainObject(null);
    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = ''
    }

    if (msg.frames !== undefined) {
      resolved.frames = msg.frames;
    }
    else {
      resolved.frames = 0
    }

    return resolved;
    }
};

module.exports = VisionFaceTrainObject;
