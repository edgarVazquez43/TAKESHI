// Auto-generated. Do not edit!

// (in-package bbros_bridge.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class Default_BB_ROS_BridgeRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.params = null;
    }
    else {
      if (initObj.hasOwnProperty('params')) {
        this.params = initObj.params
      }
      else {
        this.params = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Default_BB_ROS_BridgeRequest
    // Serialize message field [params]
    bufferOffset = _serializer.string(obj.params, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Default_BB_ROS_BridgeRequest
    let len;
    let data = new Default_BB_ROS_BridgeRequest(null);
    // Deserialize message field [params]
    data.params = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.params.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/Default_BB_ROS_BridgeRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1d24bfbf0259585a9214528cc5c5211d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string params
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Default_BB_ROS_BridgeRequest(null);
    if (msg.params !== undefined) {
      resolved.params = msg.params;
    }
    else {
      resolved.params = ''
    }

    return resolved;
    }
};

class Default_BB_ROS_BridgeResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.response = null;
    }
    else {
      if (initObj.hasOwnProperty('response')) {
        this.response = initObj.response
      }
      else {
        this.response = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Default_BB_ROS_BridgeResponse
    // Serialize message field [response]
    bufferOffset = _serializer.string(obj.response, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Default_BB_ROS_BridgeResponse
    let len;
    let data = new Default_BB_ROS_BridgeResponse(null);
    // Deserialize message field [response]
    data.response = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.response.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'bbros_bridge/Default_BB_ROS_BridgeResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6de314e2dc76fbff2b6244a6ad70b68d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string response
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Default_BB_ROS_BridgeResponse(null);
    if (msg.response !== undefined) {
      resolved.response = msg.response;
    }
    else {
      resolved.response = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: Default_BB_ROS_BridgeRequest,
  Response: Default_BB_ROS_BridgeResponse,
  md5sum() { return '6162a5d58ec2c814778e9c41c1bf44eb'; },
  datatype() { return 'bbros_bridge/Default_BB_ROS_Bridge'; }
};
