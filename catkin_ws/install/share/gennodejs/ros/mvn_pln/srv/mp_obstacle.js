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

class mp_obstacleRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.obstacle = null;
    }
    else {
      if (initObj.hasOwnProperty('obstacle')) {
        this.obstacle = initObj.obstacle
      }
      else {
        this.obstacle = new std_msgs.msg.String();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_obstacleRequest
    // Serialize message field [obstacle]
    bufferOffset = std_msgs.msg.String.serialize(obj.obstacle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_obstacleRequest
    let len;
    let data = new mp_obstacleRequest(null);
    // Deserialize message field [obstacle]
    data.obstacle = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.String.getMessageSize(object.obstacle);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'mvn_pln/mp_obstacleRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b80e3084bc76ee4a4528a242d5b7a294';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/String obstacle
    
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
    const resolved = new mp_obstacleRequest(null);
    if (msg.obstacle !== undefined) {
      resolved.obstacle = std_msgs.msg.String.Resolve(msg.obstacle)
    }
    else {
      resolved.obstacle = new std_msgs.msg.String()
    }

    return resolved;
    }
};

class mp_obstacleResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.found = null;
    }
    else {
      if (initObj.hasOwnProperty('found')) {
        this.found = initObj.found
      }
      else {
        this.found = new std_msgs.msg.Bool();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mp_obstacleResponse
    // Serialize message field [found]
    bufferOffset = std_msgs.msg.Bool.serialize(obj.found, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mp_obstacleResponse
    let len;
    let data = new mp_obstacleResponse(null);
    // Deserialize message field [found]
    data.found = std_msgs.msg.Bool.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'mvn_pln/mp_obstacleResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '46ee5af4894e4648b96118490fdcd36d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Bool found
    
    ================================================================================
    MSG: std_msgs/Bool
    bool data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new mp_obstacleResponse(null);
    if (msg.found !== undefined) {
      resolved.found = std_msgs.msg.Bool.Resolve(msg.found)
    }
    else {
      resolved.found = new std_msgs.msg.Bool()
    }

    return resolved;
    }
};

module.exports = {
  Request: mp_obstacleRequest,
  Response: mp_obstacleResponse,
  md5sum() { return '938f9cc76650ee8bc7d6dc8275ba504b'; },
  datatype() { return 'mvn_pln/mp_obstacle'; }
};
