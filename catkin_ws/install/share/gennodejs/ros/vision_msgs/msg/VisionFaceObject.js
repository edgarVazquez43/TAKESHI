// Auto-generated. Do not edit!

// (in-package vision_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class VisionFaceObject {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.confidence = null;
      this.face_centroid = null;
      this.bounding_box = null;
      this.smile = null;
      this.gender = null;
    }
    else {
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = '';
      }
      if (initObj.hasOwnProperty('confidence')) {
        this.confidence = initObj.confidence
      }
      else {
        this.confidence = 0.0;
      }
      if (initObj.hasOwnProperty('face_centroid')) {
        this.face_centroid = initObj.face_centroid
      }
      else {
        this.face_centroid = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('bounding_box')) {
        this.bounding_box = initObj.bounding_box
      }
      else {
        this.bounding_box = [];
      }
      if (initObj.hasOwnProperty('smile')) {
        this.smile = initObj.smile
      }
      else {
        this.smile = false;
      }
      if (initObj.hasOwnProperty('gender')) {
        this.gender = initObj.gender
      }
      else {
        this.gender = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VisionFaceObject
    // Serialize message field [id]
    bufferOffset = _serializer.string(obj.id, buffer, bufferOffset);
    // Serialize message field [confidence]
    bufferOffset = _serializer.float32(obj.confidence, buffer, bufferOffset);
    // Serialize message field [face_centroid]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.face_centroid, buffer, bufferOffset);
    // Serialize message field [bounding_box]
    // Serialize the length for message field [bounding_box]
    bufferOffset = _serializer.uint32(obj.bounding_box.length, buffer, bufferOffset);
    obj.bounding_box.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [smile]
    bufferOffset = _serializer.bool(obj.smile, buffer, bufferOffset);
    // Serialize message field [gender]
    bufferOffset = _serializer.int8(obj.gender, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VisionFaceObject
    let len;
    let data = new VisionFaceObject(null);
    // Deserialize message field [id]
    data.id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [confidence]
    data.confidence = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [face_centroid]
    data.face_centroid = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [bounding_box]
    // Deserialize array length for message field [bounding_box]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.bounding_box = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.bounding_box[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [smile]
    data.smile = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [gender]
    data.gender = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.id.length;
    length += 24 * object.bounding_box.length;
    return length + 38;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/VisionFaceObject';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '93b90fa2697ed03b7e1dd7001e2d8cff';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string id                                    #face id
    float32 confidence                           #value in [0,1] indicating the probability of a correct identification
    geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)
    geometry_msgs/Point[] bounding_box           #Face bounding box 2D 
    bool smile                                   #smiling face
    int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown
    
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
    const resolved = new VisionFaceObject(null);
    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = ''
    }

    if (msg.confidence !== undefined) {
      resolved.confidence = msg.confidence;
    }
    else {
      resolved.confidence = 0.0
    }

    if (msg.face_centroid !== undefined) {
      resolved.face_centroid = geometry_msgs.msg.Point.Resolve(msg.face_centroid)
    }
    else {
      resolved.face_centroid = new geometry_msgs.msg.Point()
    }

    if (msg.bounding_box !== undefined) {
      resolved.bounding_box = new Array(msg.bounding_box.length);
      for (let i = 0; i < resolved.bounding_box.length; ++i) {
        resolved.bounding_box[i] = geometry_msgs.msg.Point.Resolve(msg.bounding_box[i]);
      }
    }
    else {
      resolved.bounding_box = []
    }

    if (msg.smile !== undefined) {
      resolved.smile = msg.smile;
    }
    else {
      resolved.smile = false
    }

    if (msg.gender !== undefined) {
      resolved.gender = msg.gender;
    }
    else {
      resolved.gender = 0
    }

    return resolved;
    }
};

module.exports = VisionFaceObject;
