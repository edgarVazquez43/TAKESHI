// Auto-generated. Do not edit!

// (in-package knowledge_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let MapKnownLocation = require('../msg/MapKnownLocation.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class AddUpdateKnownLocRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.loc = null;
    }
    else {
      if (initObj.hasOwnProperty('loc')) {
        this.loc = initObj.loc
      }
      else {
        this.loc = new MapKnownLocation();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type AddUpdateKnownLocRequest
    // Serialize message field [loc]
    bufferOffset = MapKnownLocation.serialize(obj.loc, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AddUpdateKnownLocRequest
    let len;
    let data = new AddUpdateKnownLocRequest(null);
    // Deserialize message field [loc]
    data.loc = MapKnownLocation.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += MapKnownLocation.getMessageSize(object.loc);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/AddUpdateKnownLocRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c8eea2400325e7fa5b296976b0201acc';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    MapKnownLocation loc
    
    ================================================================================
    MSG: knowledge_msgs/MapKnownLocation
    string name
    float32[] value
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new AddUpdateKnownLocRequest(null);
    if (msg.loc !== undefined) {
      resolved.loc = MapKnownLocation.Resolve(msg.loc)
    }
    else {
      resolved.loc = new MapKnownLocation()
    }

    return resolved;
    }
};

class AddUpdateKnownLocResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type AddUpdateKnownLocResponse
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type AddUpdateKnownLocResponse
    let len;
    let data = new AddUpdateKnownLocResponse(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/AddUpdateKnownLocResponse';
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
    const resolved = new AddUpdateKnownLocResponse(null);
    return resolved;
    }
};

module.exports = {
  Request: AddUpdateKnownLocRequest,
  Response: AddUpdateKnownLocResponse,
  md5sum() { return 'c8eea2400325e7fa5b296976b0201acc'; },
  datatype() { return 'knowledge_msgs/AddUpdateKnownLoc'; }
};
