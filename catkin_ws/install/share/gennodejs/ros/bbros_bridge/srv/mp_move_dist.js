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

class mp_move_distRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.distance = null;
    }
    else {
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = new std_msgs.msg.Float32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_move_distRequest
    // Serialize message field [distance]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.distance, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_move_distRequest
    let len;
    let data = new mp_move_distRequest(null);
    // Deserialize message field [distance]
    data.distance = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/mp_move_distRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e1093a895d389825abe211cea01772a0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32 distance
    
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
    const resolved = new mp_move_distRequest(null);
    if (msg.distance !== undefined) {
      resolved.distance = std_msgs.msg.Float32.Resolve(msg.distance)
    }
    else {
      resolved.distance = new std_msgs.msg.Float32()
    }

    return resolved;
    }
};

class mp_move_distResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.traveledDistance = null;
    }
    else {
      if (initObj.hasOwnProperty('traveledDistance')) {
        this.traveledDistance = initObj.traveledDistance
      }
      else {
        this.traveledDistance = new std_msgs.msg.Float32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_move_distResponse
    // Serialize message field [traveledDistance]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.traveledDistance, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_move_distResponse
    let len;
    let data = new mp_move_distResponse(null);
    // Deserialize message field [traveledDistance]
    data.traveledDistance = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/mp_move_distResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9b4962461942d22bd56adac85e70348d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32 traveledDistance
    
    
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
    const resolved = new mp_move_distResponse(null);
    if (msg.traveledDistance !== undefined) {
      resolved.traveledDistance = std_msgs.msg.Float32.Resolve(msg.traveledDistance)
    }
    else {
      resolved.traveledDistance = new std_msgs.msg.Float32()
    }

    return resolved;
    }
};

module.exports = {
  Request: mp_move_distRequest,
  Response: mp_move_distResponse,
  md5sum() { return '6869a1d070e885a82e01cea5e86d2372'; },
  datatype() { return 'bbros_bridge/mp_move_dist'; }
};
