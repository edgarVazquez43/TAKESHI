// Auto-generated. Do not edit!

// (in-package vision_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Cube = require('./Cube.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class CubesSegmented {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.recog_cubes = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('recog_cubes')) {
        this.recog_cubes = initObj.recog_cubes
      }
      else {
        this.recog_cubes = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CubesSegmented
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [recog_cubes]
    // Serialize the length for message field [recog_cubes]
    bufferOffset = _serializer.uint32(obj.recog_cubes.length, buffer, bufferOffset);
    obj.recog_cubes.forEach((val) => {
      bufferOffset = Cube.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CubesSegmented
    let len;
    let data = new CubesSegmented(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [recog_cubes]
    // Deserialize array length for message field [recog_cubes]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.recog_cubes = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.recog_cubes[i] = Cube.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.recog_cubes.forEach((val) => {
      length += Cube.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/CubesSegmented';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2b935aade8f9275f5577fcbf7010f212';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    vision_msgs/Cube[] recog_cubes
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    ================================================================================
    MSG: vision_msgs/Cube
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
    const resolved = new CubesSegmented(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.recog_cubes !== undefined) {
      resolved.recog_cubes = new Array(msg.recog_cubes.length);
      for (let i = 0; i < resolved.recog_cubes.length; ++i) {
        resolved.recog_cubes[i] = Cube.Resolve(msg.recog_cubes[i]);
      }
    }
    else {
      resolved.recog_cubes = []
    }

    return resolved;
    }
};

module.exports = CubesSegmented;
