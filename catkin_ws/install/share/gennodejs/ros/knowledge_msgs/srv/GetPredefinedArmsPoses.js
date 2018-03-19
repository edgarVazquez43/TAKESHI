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

let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class GetPredefinedArmsPosesRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.name = null;
    }
    else {
      if (initObj.hasOwnProperty('name')) {
        this.name = initObj.name
      }
      else {
        this.name = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetPredefinedArmsPosesRequest
    // Serialize message field [name]
    bufferOffset = _serializer.string(obj.name, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetPredefinedArmsPosesRequest
    let len;
    let data = new GetPredefinedArmsPosesRequest(null);
    // Deserialize message field [name]
    data.name = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.name.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/GetPredefinedArmsPosesRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c1f3d28f1b044c871e6eff2e9fc3c667';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string name
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetPredefinedArmsPosesRequest(null);
    if (msg.name !== undefined) {
      resolved.name = msg.name;
    }
    else {
      resolved.name = ''
    }

    return resolved;
    }
};

class GetPredefinedArmsPosesResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.angles = null;
    }
    else {
      if (initObj.hasOwnProperty('angles')) {
        this.angles = initObj.angles
      }
      else {
        this.angles = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetPredefinedArmsPosesResponse
    // Serialize message field [angles]
    // Serialize the length for message field [angles]
    bufferOffset = _serializer.uint32(obj.angles.length, buffer, bufferOffset);
    obj.angles.forEach((val) => {
      bufferOffset = std_msgs.msg.Float32.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetPredefinedArmsPosesResponse
    let len;
    let data = new GetPredefinedArmsPosesResponse(null);
    // Deserialize message field [angles]
    // Deserialize array length for message field [angles]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.angles = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.angles[i] = std_msgs.msg.Float32.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.angles.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/GetPredefinedArmsPosesResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1d84a87ae4c7d22f3ffd0d082eecaedf';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32[] angles
    
    
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
    const resolved = new GetPredefinedArmsPosesResponse(null);
    if (msg.angles !== undefined) {
      resolved.angles = new Array(msg.angles.length);
      for (let i = 0; i < resolved.angles.length; ++i) {
        resolved.angles[i] = std_msgs.msg.Float32.Resolve(msg.angles[i]);
      }
    }
    else {
      resolved.angles = []
    }

    return resolved;
    }
};

module.exports = {
  Request: GetPredefinedArmsPosesRequest,
  Response: GetPredefinedArmsPosesResponse,
  md5sum() { return '5f93696d26db52709ee264c439d53838'; },
  datatype() { return 'knowledge_msgs/GetPredefinedArmsPoses'; }
};
