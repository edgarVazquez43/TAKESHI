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

let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class DetectGripperRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DetectGripperRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DetectGripperRequest
    let len;
    let data = new DetectGripperRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/DetectGripperRequest';
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
    const resolved = new DetectGripperRequest(null);
    return resolved;
    }
};

class DetectGripperResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gripper_position = null;
    }
    else {
      if (initObj.hasOwnProperty('gripper_position')) {
        this.gripper_position = initObj.gripper_position
      }
      else {
        this.gripper_position = new geometry_msgs.msg.Point();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DetectGripperResponse
    // Serialize message field [gripper_position]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.gripper_position, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DetectGripperResponse
    let len;
    let data = new DetectGripperResponse(null);
    // Deserialize message field [gripper_position]
    data.gripper_position = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/DetectGripperResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd04c5ffec643228db4185f8b85f803c4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Point gripper_position
    
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DetectGripperResponse(null);
    if (msg.gripper_position !== undefined) {
      resolved.gripper_position = geometry_msgs.msg.Point.Resolve(msg.gripper_position)
    }
    else {
      resolved.gripper_position = new geometry_msgs.msg.Point()
    }

    return resolved;
    }
};

module.exports = {
  Request: DetectGripperRequest,
  Response: DetectGripperResponse,
  md5sum() { return 'd04c5ffec643228db4185f8b85f803c4'; },
  datatype() { return 'vision_msgs/DetectGripper'; }
};
