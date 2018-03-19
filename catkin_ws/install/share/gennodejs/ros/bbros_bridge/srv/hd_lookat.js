// Auto-generated. Do not edit!

// (in-package bbros_bridge.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class hd_lookatRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.goalPan = null;
      this.goalTilt = null;
    }
    else {
      if (initObj.hasOwnProperty('goalPan')) {
        this.goalPan = initObj.goalPan
      }
      else {
        this.goalPan = new std_msgs.msg.Float32();
      }
      if (initObj.hasOwnProperty('goalTilt')) {
        this.goalTilt = initObj.goalTilt
      }
      else {
        this.goalTilt = new std_msgs.msg.Float32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type hd_lookatRequest
    // Serialize message field [goalPan]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.goalPan, buffer, bufferOffset);
    // Serialize message field [goalTilt]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.goalTilt, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type hd_lookatRequest
    let len;
    let data = new hd_lookatRequest(null);
    // Deserialize message field [goalPan]
    data.goalPan = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [goalTilt]
    data.goalTilt = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/hd_lookatRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e6fcb4f324f93c6ea919f38fa9ab0556';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32 goalPan
    std_msgs/Float32 goalTilt
    
    ================================================================================
    MSG: std_msgs/Float32
    float32 data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new hd_lookatRequest(null);
    if (msg.goalPan !== undefined) {
      resolved.goalPan = std_msgs.msg.Float32.Resolve(msg.goalPan)
    }
    else {
      resolved.goalPan = new std_msgs.msg.Float32()
    }

    if (msg.goalTilt !== undefined) {
      resolved.goalTilt = std_msgs.msg.Float32.Resolve(msg.goalTilt)
    }
    else {
      resolved.goalTilt = new std_msgs.msg.Float32()
    }

    return resolved;
    }
};

class hd_lookatResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.currentPan = null;
      this.currentTilt = null;
      this.errors = null;
    }
    else {
      if (initObj.hasOwnProperty('currentPan')) {
        this.currentPan = initObj.currentPan
      }
      else {
        this.currentPan = new std_msgs.msg.Float32();
      }
      if (initObj.hasOwnProperty('currentTilt')) {
        this.currentTilt = initObj.currentTilt
      }
      else {
        this.currentTilt = new std_msgs.msg.Float32();
      }
      if (initObj.hasOwnProperty('errors')) {
        this.errors = initObj.errors
      }
      else {
        this.errors = new std_msgs.msg.String();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type hd_lookatResponse
    // Serialize message field [currentPan]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.currentPan, buffer, bufferOffset);
    // Serialize message field [currentTilt]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.currentTilt, buffer, bufferOffset);
    // Serialize message field [errors]
    bufferOffset = std_msgs.msg.String.serialize(obj.errors, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type hd_lookatResponse
    let len;
    let data = new hd_lookatResponse(null);
    // Deserialize message field [currentPan]
    data.currentPan = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [currentTilt]
    data.currentTilt = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [errors]
    data.errors = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.String.getMessageSize(object.errors);
    return length + 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/hd_lookatResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8a4d1a02761c4dadc5f5b2b059a7e3dc';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32 currentPan
    std_msgs/Float32 currentTilt
    std_msgs/String errors
    
    
    ================================================================================
    MSG: std_msgs/Float32
    float32 data
    ================================================================================
    MSG: std_msgs/String
    string data
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new hd_lookatResponse(null);
    if (msg.currentPan !== undefined) {
      resolved.currentPan = std_msgs.msg.Float32.Resolve(msg.currentPan)
    }
    else {
      resolved.currentPan = new std_msgs.msg.Float32()
    }

    if (msg.currentTilt !== undefined) {
      resolved.currentTilt = std_msgs.msg.Float32.Resolve(msg.currentTilt)
    }
    else {
      resolved.currentTilt = new std_msgs.msg.Float32()
    }

    if (msg.errors !== undefined) {
      resolved.errors = std_msgs.msg.String.Resolve(msg.errors)
    }
    else {
      resolved.errors = new std_msgs.msg.String()
    }

    return resolved;
    }
};

module.exports = {
  Request: hd_lookatRequest,
  Response: hd_lookatResponse,
  md5sum() { return '0d2267ae1acd4d7549c1a4e21fcad0ae'; },
  datatype() { return 'bbros_bridge/hd_lookat'; }
};
