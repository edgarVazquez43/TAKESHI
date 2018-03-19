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

class Cube {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.color = null;
      this.cube_centroid = null;
      this.detected_cube = null;
      this.minPoint = null;
      this.maxPoint = null;
    }
    else {
      if (initObj.hasOwnProperty('color')) {
        this.color = initObj.color
      }
      else {
        this.color = '';
      }
      if (initObj.hasOwnProperty('cube_centroid')) {
        this.cube_centroid = initObj.cube_centroid
      }
      else {
        this.cube_centroid = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('detected_cube')) {
        this.detected_cube = initObj.detected_cube
      }
      else {
        this.detected_cube = false;
      }
      if (initObj.hasOwnProperty('minPoint')) {
        this.minPoint = initObj.minPoint
      }
      else {
        this.minPoint = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('maxPoint')) {
        this.maxPoint = initObj.maxPoint
      }
      else {
        this.maxPoint = new geometry_msgs.msg.Point();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Cube
    // Serialize message field [color]
    bufferOffset = _serializer.string(obj.color, buffer, bufferOffset);
    // Serialize message field [cube_centroid]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.cube_centroid, buffer, bufferOffset);
    // Serialize message field [detected_cube]
    bufferOffset = _serializer.bool(obj.detected_cube, buffer, bufferOffset);
    // Serialize message field [minPoint]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.minPoint, buffer, bufferOffset);
    // Serialize message field [maxPoint]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.maxPoint, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Cube
    let len;
    let data = new Cube(null);
    // Deserialize message field [color]
    data.color = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [cube_centroid]
    data.cube_centroid = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [detected_cube]
    data.detected_cube = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [minPoint]
    data.minPoint = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [maxPoint]
    data.maxPoint = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.color.length;
    return length + 77;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/Cube';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7208e2d20370e447988b77d98e81081d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string color #color of the cube
    geometry_msgs/Point cube_centroid		#Cube Centroid (x,y,z)
    bool detected_cube    #flag to indicate if the cube was detected
    geometry_msgs/Point minPoint	#Cube's min point
    geometry_msgs/Point maxPoint	#Cube's max point
    
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
    const resolved = new Cube(null);
    if (msg.color !== undefined) {
      resolved.color = msg.color;
    }
    else {
      resolved.color = ''
    }

    if (msg.cube_centroid !== undefined) {
      resolved.cube_centroid = geometry_msgs.msg.Point.Resolve(msg.cube_centroid)
    }
    else {
      resolved.cube_centroid = new geometry_msgs.msg.Point()
    }

    if (msg.detected_cube !== undefined) {
      resolved.detected_cube = msg.detected_cube;
    }
    else {
      resolved.detected_cube = false
    }

    if (msg.minPoint !== undefined) {
      resolved.minPoint = geometry_msgs.msg.Point.Resolve(msg.minPoint)
    }
    else {
      resolved.minPoint = new geometry_msgs.msg.Point()
    }

    if (msg.maxPoint !== undefined) {
      resolved.maxPoint = geometry_msgs.msg.Point.Resolve(msg.maxPoint)
    }
    else {
      resolved.maxPoint = new geometry_msgs.msg.Point()
    }

    return resolved;
    }
};

module.exports = Cube;
