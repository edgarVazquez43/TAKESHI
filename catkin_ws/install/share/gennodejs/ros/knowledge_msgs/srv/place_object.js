// Auto-generated. Do not edit!

// (in-package knowledge_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class place_objectRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.dest_location = null;
      this.arm_to_use = null;
    }
    else {
      if (initObj.hasOwnProperty('dest_location')) {
        this.dest_location = initObj.dest_location
      }
      else {
        this.dest_location = '';
      }
      if (initObj.hasOwnProperty('arm_to_use')) {
        this.arm_to_use = initObj.arm_to_use
      }
      else {
        this.arm_to_use = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type place_objectRequest
    // Serialize message field [dest_location]
    bufferOffset = _serializer.string(obj.dest_location, buffer, bufferOffset);
    // Serialize message field [arm_to_use]
    bufferOffset = _serializer.int32(obj.arm_to_use, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type place_objectRequest
    let len;
    let data = new place_objectRequest(null);
    // Deserialize message field [dest_location]
    data.dest_location = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [arm_to_use]
    data.arm_to_use = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.dest_location.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/place_objectRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '713d2d353c5f29ec7d69a614ac5b8dad';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string dest_location
    int32 arm_to_use
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new place_objectRequest(null);
    if (msg.dest_location !== undefined) {
      resolved.dest_location = msg.dest_location;
    }
    else {
      resolved.dest_location = ''
    }

    if (msg.arm_to_use !== undefined) {
      resolved.arm_to_use = msg.arm_to_use;
    }
    else {
      resolved.arm_to_use = 0
    }

    return resolved;
    }
};

class place_objectResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.task_success = null;
    }
    else {
      if (initObj.hasOwnProperty('task_success')) {
        this.task_success = initObj.task_success
      }
      else {
        this.task_success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type place_objectResponse
    // Serialize message field [task_success]
    bufferOffset = _serializer.bool(obj.task_success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type place_objectResponse
    let len;
    let data = new place_objectResponse(null);
    // Deserialize message field [task_success]
    data.task_success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/place_objectResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '635f9b999d70fffc8286e662bf8bcadb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool task_success
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new place_objectResponse(null);
    if (msg.task_success !== undefined) {
      resolved.task_success = msg.task_success;
    }
    else {
      resolved.task_success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: place_objectRequest,
  Response: place_objectResponse,
  md5sum() { return '72e5fc1d3c709f9c79fea87497774dd9'; },
  datatype() { return 'knowledge_msgs/place_object'; }
};
