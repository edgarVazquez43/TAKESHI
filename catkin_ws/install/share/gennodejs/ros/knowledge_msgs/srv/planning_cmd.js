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

class planning_cmdRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.params = null;
      this.name = null;
    }
    else {
      if (initObj.hasOwnProperty('params')) {
        this.params = initObj.params
      }
      else {
        this.params = '';
      }
      if (initObj.hasOwnProperty('name')) {
        this.name = initObj.name
      }
      else {
        this.name = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type planning_cmdRequest
    // Serialize message field [params]
    bufferOffset = _serializer.string(obj.params, buffer, bufferOffset);
    // Serialize message field [name]
    bufferOffset = _serializer.string(obj.name, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type planning_cmdRequest
    let len;
    let data = new planning_cmdRequest(null);
    // Deserialize message field [params]
    data.params = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [name]
    data.name = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.params.length;
    length += object.name.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/planning_cmdRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6f06fa99b3a7a624255764732217776c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string params
    string name
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new planning_cmdRequest(null);
    if (msg.params !== undefined) {
      resolved.params = msg.params;
    }
    else {
      resolved.params = ''
    }

    if (msg.name !== undefined) {
      resolved.name = msg.name;
    }
    else {
      resolved.name = ''
    }

    return resolved;
    }
};

class planning_cmdResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
      this.args = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
      if (initObj.hasOwnProperty('args')) {
        this.args = initObj.args
      }
      else {
        this.args = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type planning_cmdResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    // Serialize message field [args]
    bufferOffset = _serializer.string(obj.args, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type planning_cmdResponse
    let len;
    let data = new planning_cmdResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [args]
    data.args = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.args.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/planning_cmdResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '866983ef097d9f8b07290732e0d3ba58';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool success
    string args
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new planning_cmdResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    if (msg.args !== undefined) {
      resolved.args = msg.args;
    }
    else {
      resolved.args = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: planning_cmdRequest,
  Response: planning_cmdResponse,
  md5sum() { return 'f9f6635257061aef8bea97260f4e6a8b'; },
  datatype() { return 'knowledge_msgs/planning_cmd'; }
};
