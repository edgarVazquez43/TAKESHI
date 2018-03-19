// Auto-generated. Do not edit!

// (in-package mvn_pln.srv)


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

class mp_getcloseRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.location = null;
    }
    else {
      if (initObj.hasOwnProperty('location')) {
        this.location = initObj.location
      }
      else {
        this.location = new std_msgs.msg.String();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_getcloseRequest
    // Serialize message field [location]
    bufferOffset = std_msgs.msg.String.serialize(obj.location, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_getcloseRequest
    let len;
    let data = new mp_getcloseRequest(null);
    // Deserialize message field [location]
    data.location = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.String.getMessageSize(object.location);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'mvn_pln/mp_getcloseRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '47803332a54872fa6c672c9dd144c561';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/String location
    
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
    const resolved = new mp_getcloseRequest(null);
    if (msg.location !== undefined) {
      resolved.location = std_msgs.msg.String.Resolve(msg.location)
    }
    else {
      resolved.location = new std_msgs.msg.String()
    }

    return resolved;
    }
};

class mp_getcloseResponse {
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
    // Serializes a message object of type mp_getcloseResponse
    // Serialize message field [error]
    bufferOffset = std_msgs.msg.String.serialize(obj.error, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_getcloseResponse
    let len;
    let data = new mp_getcloseResponse(null);
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
    return 'mvn_pln/mp_getcloseResponse';
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
    const resolved = new mp_getcloseResponse(null);
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
  Request: mp_getcloseRequest,
  Response: mp_getcloseResponse,
  md5sum() { return '1919ccd065ce7aa924cb46471f2dd632'; },
  datatype() { return 'mvn_pln/mp_getclose'; }
};
