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

class mp_getclose_xyaRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.goalX = null;
      this.goalY = null;
      this.goalAngle = null;
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
      if (initObj.hasOwnProperty('goalAngle')) {
        this.goalAngle = initObj.goalAngle
      }
      else {
        this.goalAngle = new std_msgs.msg.Float32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_getclose_xyaRequest
    // Serialize message field [goalX]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.goalX, buffer, bufferOffset);
    // Serialize message field [goalY]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.goalY, buffer, bufferOffset);
    // Serialize message field [goalAngle]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.goalAngle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_getclose_xyaRequest
    let len;
    let data = new mp_getclose_xyaRequest(null);
    // Deserialize message field [goalX]
    data.goalX = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [goalY]
    data.goalY = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [goalAngle]
    data.goalAngle = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/mp_getclose_xyaRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '178acf5a67ca3d651e2b78e01e55f45b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32 goalX
    std_msgs/Float32 goalY
    std_msgs/Float32 goalAngle
    
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
    const resolved = new mp_getclose_xyaRequest(null);
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

    if (msg.goalAngle !== undefined) {
      resolved.goalAngle = std_msgs.msg.Float32.Resolve(msg.goalAngle)
    }
    else {
      resolved.goalAngle = new std_msgs.msg.Float32()
    }

    return resolved;
    }
};

class mp_getclose_xyaResponse {
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
    // Serializes a message object of type mp_getclose_xyaResponse
    // Serialize message field [error]
    bufferOffset = std_msgs.msg.String.serialize(obj.error, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_getclose_xyaResponse
    let len;
    let data = new mp_getclose_xyaResponse(null);
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
    return 'bbros_bridge/mp_getclose_xyaResponse';
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
    const resolved = new mp_getclose_xyaResponse(null);
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
  Request: mp_getclose_xyaRequest,
  Response: mp_getclose_xyaResponse,
  md5sum() { return 'f236a8bf2a517b8af728eb19291f51cb'; },
  datatype() { return 'bbros_bridge/mp_getclose_xya'; }
};
