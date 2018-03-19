// Auto-generated. Do not edit!

// (in-package vision_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let VisionRect = require('../msg/VisionRect.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class FindWavingRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FindWavingRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FindWavingRequest
    let len;
    let data = new FindWavingRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/FindWavingRequest';
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
    const resolved = new FindWavingRequest(null);
    return resolved;
    }
};

class FindWavingResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.bounding_box = null;
      this.frame_width = null;
      this.frame_height = null;
    }
    else {
      if (initObj.hasOwnProperty('bounding_box')) {
        this.bounding_box = initObj.bounding_box
      }
      else {
        this.bounding_box = [];
      }
      if (initObj.hasOwnProperty('frame_width')) {
        this.frame_width = initObj.frame_width
      }
      else {
        this.frame_width = new std_msgs.msg.Int32();
      }
      if (initObj.hasOwnProperty('frame_height')) {
        this.frame_height = initObj.frame_height
      }
      else {
        this.frame_height = new std_msgs.msg.Int32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FindWavingResponse
    // Serialize message field [bounding_box]
    // Serialize the length for message field [bounding_box]
    bufferOffset = _serializer.uint32(obj.bounding_box.length, buffer, bufferOffset);
    obj.bounding_box.forEach((val) => {
      bufferOffset = VisionRect.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [frame_width]
    bufferOffset = std_msgs.msg.Int32.serialize(obj.frame_width, buffer, bufferOffset);
    // Serialize message field [frame_height]
    bufferOffset = std_msgs.msg.Int32.serialize(obj.frame_height, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FindWavingResponse
    let len;
    let data = new FindWavingResponse(null);
    // Deserialize message field [bounding_box]
    // Deserialize array length for message field [bounding_box]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.bounding_box = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.bounding_box[i] = VisionRect.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [frame_width]
    data.frame_width = std_msgs.msg.Int32.deserialize(buffer, bufferOffset);
    // Deserialize message field [frame_height]
    data.frame_height = std_msgs.msg.Int32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 16 * object.bounding_box.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/FindWavingResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a5efa18c4fad16dbe94cb16a4d7151ec';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    vision_msgs/VisionRect[] bounding_box
    std_msgs/Int32 frame_width
    std_msgs/Int32 frame_height
    
    
    
    ================================================================================
    MSG: vision_msgs/VisionRect
    int32 x
    int32 y
    int32 width
    int32 height
    
    ================================================================================
    MSG: std_msgs/Int32
    int32 data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FindWavingResponse(null);
    if (msg.bounding_box !== undefined) {
      resolved.bounding_box = new Array(msg.bounding_box.length);
      for (let i = 0; i < resolved.bounding_box.length; ++i) {
        resolved.bounding_box[i] = VisionRect.Resolve(msg.bounding_box[i]);
      }
    }
    else {
      resolved.bounding_box = []
    }

    if (msg.frame_width !== undefined) {
      resolved.frame_width = std_msgs.msg.Int32.Resolve(msg.frame_width)
    }
    else {
      resolved.frame_width = new std_msgs.msg.Int32()
    }

    if (msg.frame_height !== undefined) {
      resolved.frame_height = std_msgs.msg.Int32.Resolve(msg.frame_height)
    }
    else {
      resolved.frame_height = new std_msgs.msg.Int32()
    }

    return resolved;
    }
};

module.exports = {
  Request: FindWavingRequest,
  Response: FindWavingResponse,
  md5sum() { return 'a5efa18c4fad16dbe94cb16a4d7151ec'; },
  datatype() { return 'vision_msgs/FindWaving'; }
};
