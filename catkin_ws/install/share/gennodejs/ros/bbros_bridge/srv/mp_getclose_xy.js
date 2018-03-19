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

class mp_getclose_xyRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.goalX = null;
      this.goalY = null;
    }
    else {
      if (initObj.hasOwnProperty('goalX')) {
        this.goalX = initObj.goalX
      }
      else {
        this.goalX = new std_msgs.msg.Float32();
      }
      if (initObj.hasOwnProperty('goalY')) {
        this.goalY = initObj.goalY
      }
      else {
        this.goalY = new std_msgs.msg.Float32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_getclose_xyRequest
    // Serialize message field [goalX]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.goalX, buffer, bufferOffset);
    // Serialize message field [goalY]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.goalY, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_getclose_xyRequest
    let len;
    let data = new mp_getclose_xyRequest(null);
    // Deserialize message field [goalX]
    data.goalX = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [goalY]
    data.goalY = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/mp_getclose_xyRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9061aee48320f865b73af2589fed8f03';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32 goalX
    std_msgs/Float32 goalY
    
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
    const resolved = new mp_getclose_xyRequest(null);
    if (msg.goalX !== undefined) {
      resolved.goalX = std_msgs.msg.Float32.Resolve(msg.goalX)
    }
    else {
      resolved.goalX = new std_msgs.msg.Float32()
    }

    if (msg.goalY !== undefined) {
      resolved.goalY = std_msgs.msg.Float32.Resolve(msg.goalY)
    }
    else {
      resolved.goalY = new std_msgs.msg.Float32()
    }

    return resolved;
    }
};

class mp_getclose_xyResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.error = null;
    }
    else {
      if (initObj.hasOwnProperty('error')) {
        this.error = initObj.error
      }
      else {
        this.error = new std_msgs.msg.String();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_getclose_xyResponse
    // Serialize message field [error]
    bufferOffset = std_msgs.msg.String.serialize(obj.error, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_getclose_xyResponse
    let len;
    let data = new mp_getclose_xyResponse(null);
    // Deserialize message field [error]
    data.error = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.String.getMessageSize(object.error);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/mp_getclose_xyResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '52f61832eab3a7c7b495ac0b338dd373';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/String error
    
    
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
    const resolved = new mp_getclose_xyResponse(null);
    if (msg.error !== undefined) {
      resolved.error = std_msgs.msg.String.Resolve(msg.error)
    }
    else {
      resolved.error = new std_msgs.msg.String()
    }

    return resolved;
    }
};

module.exports = {
  Request: mp_getclose_xyRequest,
  Response: mp_getclose_xyResponse,
  md5sum() { return 'a6bfdb792bb6f7c25c686505f84f9b9c'; },
  datatype() { return 'bbros_bridge/mp_getclose_xy'; }
};
