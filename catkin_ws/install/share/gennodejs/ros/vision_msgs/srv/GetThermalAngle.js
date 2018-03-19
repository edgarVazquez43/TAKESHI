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


//-----------------------------------------------------------

class GetThermalAngleRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetThermalAngleRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetThermalAngleRequest
    let len;
    let data = new GetThermalAngleRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/GetThermalAngleRequest';
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
    const resolved = new GetThermalAngleRequest(null);
    return resolved;
    }
};

class GetThermalAngleResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.th_angle = null;
    }
    else {
      if (initObj.hasOwnProperty('th_angle')) {
        this.th_angle = initObj.th_angle
      }
      else {
        this.th_angle = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetThermalAngleResponse
    // Serialize message field [th_angle]
    bufferOffset = _serializer.float32(obj.th_angle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetThermalAngleResponse
    let len;
    let data = new GetThermalAngleResponse(null);
    // Deserialize message field [th_angle]
    data.th_angle = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/GetThermalAngleResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6e530ad148ac6d527edc145df842dd24';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 th_angle
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetThermalAngleResponse(null);
    if (msg.th_angle !== undefined) {
      resolved.th_angle = msg.th_angle;
    }
    else {
      resolved.th_angle = 0.0
    }

    return resolved;
    }
};

module.exports = {
  Request: GetThermalAngleRequest,
  Response: GetThermalAngleResponse,
  md5sum() { return '6e530ad148ac6d527edc145df842dd24'; },
  datatype() { return 'vision_msgs/GetThermalAngle'; }
};
