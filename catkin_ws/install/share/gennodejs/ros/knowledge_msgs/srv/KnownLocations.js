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

let MapKnownLocation = require('../msg/MapKnownLocation.js');

//-----------------------------------------------------------

class KnownLocationsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type KnownLocationsRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type KnownLocationsRequest
    let len;
    let data = new KnownLocationsRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/KnownLocationsRequest';
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
    const resolved = new KnownLocationsRequest(null);
    return resolved;
    }
};

class KnownLocationsResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.locations = null;
    }
    else {
      if (initObj.hasOwnProperty('locations')) {
        this.locations = initObj.locations
      }
      else {
        this.locations = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type KnownLocationsResponse
    // Serialize message field [locations]
    // Serialize the length for message field [locations]
    bufferOffset = _serializer.uint32(obj.locations.length, buffer, bufferOffset);
    obj.locations.forEach((val) => {
      bufferOffset = MapKnownLocation.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type KnownLocationsResponse
    let len;
    let data = new KnownLocationsResponse(null);
    // Deserialize message field [locations]
    // Deserialize array length for message field [locations]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.locations = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.locations[i] = MapKnownLocation.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.locations.forEach((val) => {
      length += MapKnownLocation.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/KnownLocationsResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6bd6e203855e6403b9f65224e511af1a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    MapKnownLocation[] locations
    
    
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
    const resolved = new KnownLocationsResponse(null);
    if (msg.locations !== undefined) {
      resolved.locations = new Array(msg.locations.length);
      for (let i = 0; i < resolved.locations.length; ++i) {
        resolved.locations[i] = MapKnownLocation.Resolve(msg.locations[i]);
      }
    }
    else {
      resolved.locations = []
    }

    return resolved;
    }
};

module.exports = {
  Request: KnownLocationsRequest,
  Response: KnownLocationsResponse,
  md5sum() { return '6bd6e203855e6403b9f65224e511af1a'; },
  datatype() { return 'knowledge_msgs/KnownLocations'; }
};
