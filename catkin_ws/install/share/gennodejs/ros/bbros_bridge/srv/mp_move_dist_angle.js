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

class mp_move_dist_angleRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.bearing = null;
      this.distance = null;
    }
    else {
      if (initObj.hasOwnProperty('bearing')) {
        this.bearing = initObj.bearing
      }
      else {
        this.bearing = new std_msgs.msg.Float32();
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = new std_msgs.msg.Float32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_move_dist_angleRequest
    // Serialize message field [bearing]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.bearing, buffer, bufferOffset);
    // Serialize message field [distance]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.distance, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_move_dist_angleRequest
    let len;
    let data = new mp_move_dist_angleRequest(null);
    // Deserialize message field [bearing]
    data.bearing = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [distance]
    data.distance = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/mp_move_dist_angleRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ebb675b5ffe2861f054edd7cce6d60cd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32 bearing
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
    const resolved = new mp_move_dist_angleRequest(null);
    if (msg.bearing !== undefined) {
      resolved.bearing = std_msgs.msg.Float32.Resolve(msg.bearing)
    }
    else {
      resolved.bearing = new std_msgs.msg.Float32()
    }

    if (msg.distance !== undefined) {
      resolved.distance = std_msgs.msg.Float32.Resolve(msg.distance)
    }
    else {
      resolved.distance = new std_msgs.msg.Float32()
    }

    return resolved;
    }
};

class mp_move_dist_angleResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.traveledBearing = null;
      this.traveledDistance = null;
    }
    else {
      if (initObj.hasOwnProperty('traveledBearing')) {
        this.traveledBearing = initObj.traveledBearing
      }
      else {
        this.traveledBearing = new std_msgs.msg.Float32();
      }
      if (initObj.hasOwnProperty('traveledDistance')) {
        this.traveledDistance = initObj.traveledDistance
      }
      else {
        this.traveledDistance = new std_msgs.msg.Float32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_move_dist_angleResponse
    // Serialize message field [traveledBearing]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.traveledBearing, buffer, bufferOffset);
    // Serialize message field [traveledDistance]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.traveledDistance, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_move_dist_angleResponse
    let len;
    let data = new mp_move_dist_angleResponse(null);
    // Deserialize message field [traveledBearing]
    data.traveledBearing = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [traveledDistance]
    data.traveledDistance = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/mp_move_dist_angleResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '48d862723389a90b005451cb408b5a44';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32 traveledBearing
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
    const resolved = new mp_move_dist_angleResponse(null);
    if (msg.traveledBearing !== undefined) {
      resolved.traveledBearing = std_msgs.msg.Float32.Resolve(msg.traveledBearing)
    }
    else {
      resolved.traveledBearing = new std_msgs.msg.Float32()
    }

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
  Request: mp_move_dist_angleRequest,
  Response: mp_move_dist_angleResponse,
  md5sum() { return '930663ac8b505c579c42369296ce1052'; },
  datatype() { return 'bbros_bridge/mp_move_dist_angle'; }
};
