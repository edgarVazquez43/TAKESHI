// Auto-generated. Do not edit!

// (in-package audio_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class srvAngleRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type srvAngleRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type srvAngleRequest
    let len;
    let data = new srvAngleRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'audio_msgs/srvAngleRequest';
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
    const resolved = new srvAngleRequest(null);
    return resolved;
    }
};

class srvAngleResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Angle = null;
    }
    else {
      if (initObj.hasOwnProperty('Angle')) {
        this.Angle = initObj.Angle
      }
      else {
        this.Angle = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type srvAngleResponse
    // Serialize message field [Angle]
    bufferOffset = _serializer.float32(obj.Angle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type srvAngleResponse
    let len;
    let data = new srvAngleResponse(null);
    // Deserialize message field [Angle]
    data.Angle = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'audio_msgs/srvAngleResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3c12d5a3eed4d7589fde4b3bcd93aff0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 Angle
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new srvAngleResponse(null);
    if (msg.Angle !== undefined) {
      resolved.Angle = msg.Angle;
    }
    else {
      resolved.Angle = 0.0
    }

    return resolved;
    }
};

module.exports = {
  Request: srvAngleRequest,
  Response: srvAngleResponse,
  md5sum() { return '3c12d5a3eed4d7589fde4b3bcd93aff0'; },
  datatype() { return 'audio_msgs/srvAngle'; }
};
