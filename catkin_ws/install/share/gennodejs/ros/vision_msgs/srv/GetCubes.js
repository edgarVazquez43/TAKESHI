// Auto-generated. Do not edit!

// (in-package vision_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let CubesSegmented = require('../msg/CubesSegmented.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class GetCubesRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.cubes_input = null;
    }
    else {
      if (initObj.hasOwnProperty('cubes_input')) {
        this.cubes_input = initObj.cubes_input
      }
      else {
        this.cubes_input = new CubesSegmented();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetCubesRequest
    // Serialize message field [cubes_input]
    bufferOffset = CubesSegmented.serialize(obj.cubes_input, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetCubesRequest
    let len;
    let data = new GetCubesRequest(null);
    // Deserialize message field [cubes_input]
    data.cubes_input = CubesSegmented.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += CubesSegmented.getMessageSize(object.cubes_input);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/GetCubesRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5d157fc83cf257e6044b1e57d3508700';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    vision_msgs/CubesSegmented cubes_input
    
    ================================================================================
    MSG: vision_msgs/CubesSegmented
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
    const resolved = new GetCubesRequest(null);
    if (msg.cubes_input !== undefined) {
      resolved.cubes_input = CubesSegmented.Resolve(msg.cubes_input)
    }
    else {
      resolved.cubes_input = new CubesSegmented()
    }

    return resolved;
    }
};

class GetCubesResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.cubes_output = null;
    }
    else {
      if (initObj.hasOwnProperty('cubes_output')) {
        this.cubes_output = initObj.cubes_output
      }
      else {
        this.cubes_output = new CubesSegmented();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetCubesResponse
    // Serialize message field [cubes_output]
    bufferOffset = CubesSegmented.serialize(obj.cubes_output, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetCubesResponse
    let len;
    let data = new GetCubesResponse(null);
    // Deserialize message field [cubes_output]
    data.cubes_output = CubesSegmented.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += CubesSegmented.getMessageSize(object.cubes_output);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/GetCubesResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'be6b91864d949081c0a4e00a949d7867';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    vision_msgs/CubesSegmented cubes_output
    
    
    ================================================================================
    MSG: vision_msgs/CubesSegmented
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
    const resolved = new GetCubesResponse(null);
    if (msg.cubes_output !== undefined) {
      resolved.cubes_output = CubesSegmented.Resolve(msg.cubes_output)
    }
    else {
      resolved.cubes_output = new CubesSegmented()
    }

    return resolved;
    }
};

module.exports = {
  Request: GetCubesRequest,
  Response: GetCubesResponse,
  md5sum() { return 'a2d88941f0bdf4936824e45f204e46ff'; },
  datatype() { return 'vision_msgs/GetCubes'; }
};
