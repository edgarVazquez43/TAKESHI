// Auto-generated. Do not edit!

// (in-package knowledge_msgs.srv)


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

class search_remember_faceRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.robot_instructions = null;
      this.face_id = null;
      this.head_movs = null;
    }
    else {
      if (initObj.hasOwnProperty('robot_instructions')) {
        this.robot_instructions = initObj.robot_instructions
      }
      else {
        this.robot_instructions = '';
      }
      if (initObj.hasOwnProperty('face_id')) {
        this.face_id = initObj.face_id
      }
      else {
        this.face_id = '';
      }
      if (initObj.hasOwnProperty('head_movs')) {
        this.head_movs = initObj.head_movs
      }
      else {
        this.head_movs = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type search_remember_faceRequest
    // Serialize message field [robot_instructions]
    bufferOffset = _serializer.string(obj.robot_instructions, buffer, bufferOffset);
    // Serialize message field [face_id]
    bufferOffset = _serializer.string(obj.face_id, buffer, bufferOffset);
    // Serialize message field [head_movs]
    // Serialize the length for message field [head_movs]
    bufferOffset = _serializer.uint32(obj.head_movs.length, buffer, bufferOffset);
    obj.head_movs.forEach((val) => {
      bufferOffset = std_msgs.msg.Float32MultiArray.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type search_remember_faceRequest
    let len;
    let data = new search_remember_faceRequest(null);
    // Deserialize message field [robot_instructions]
    data.robot_instructions = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [face_id]
    data.face_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [head_movs]
    // Deserialize array length for message field [head_movs]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.head_movs = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.head_movs[i] = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.robot_instructions.length;
    length += object.face_id.length;
    object.head_movs.forEach((val) => {
      length += std_msgs.msg.Float32MultiArray.getMessageSize(val);
    });
    return length + 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/search_remember_faceRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3bf5ab55a237a4b92f17d0eeb84a55d5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string robot_instructions
    string face_id
    std_msgs/Float32MultiArray[] head_movs
    
    ================================================================================
    MSG: std_msgs/Float32MultiArray
    # Please look at the MultiArrayLayout message definition for
    # documentation on all multiarrays.
    
    MultiArrayLayout  layout        # specification of data layout
    float32[]         data          # array of data
    
    
    ================================================================================
    MSG: std_msgs/MultiArrayLayout
    # The multiarray declares a generic multi-dimensional array of a
    # particular data type.  Dimensions are ordered from outer most
    # to inner most.
    
    MultiArrayDimension[] dim # Array of dimension properties
    uint32 data_offset        # padding elements at front of data
    
    # Accessors should ALWAYS be written in terms of dimension stride
    # and specified outer-most dimension first.
    # 
    # multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]
    #
    # A standard, 3-channel 640x480 image with interleaved color channels
    # would be specified as:
    #
    # dim[0].label  = "height"
    # dim[0].size   = 480
    # dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)
    # dim[1].label  = "width"
    # dim[1].size   = 640
    # dim[1].stride = 3*640 = 1920
    # dim[2].label  = "channel"
    # dim[2].size   = 3
    # dim[2].stride = 3
    #
    # multiarray(i,j,k) refers to the ith row, jth column, and kth channel.
    
    ================================================================================
    MSG: std_msgs/MultiArrayDimension
    string label   # label of given dimension
    uint32 size    # size of given dimension (in type units)
    uint32 stride  # stride of given dimension
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new search_remember_faceRequest(null);
    if (msg.robot_instructions !== undefined) {
      resolved.robot_instructions = msg.robot_instructions;
    }
    else {
      resolved.robot_instructions = ''
    }

    if (msg.face_id !== undefined) {
      resolved.face_id = msg.face_id;
    }
    else {
      resolved.face_id = ''
    }

    if (msg.head_movs !== undefined) {
      resolved.head_movs = new Array(msg.head_movs.length);
      for (let i = 0; i < resolved.head_movs.length; ++i) {
        resolved.head_movs[i] = std_msgs.msg.Float32MultiArray.Resolve(msg.head_movs[i]);
      }
    }
    else {
      resolved.head_movs = []
    }

    return resolved;
    }
};

class search_remember_faceResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.training_success = null;
    }
    else {
      if (initObj.hasOwnProperty('training_success')) {
        this.training_success = initObj.training_success
      }
      else {
        this.training_success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type search_remember_faceResponse
    // Serialize message field [training_success]
    bufferOffset = _serializer.bool(obj.training_success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type search_remember_faceResponse
    let len;
    let data = new search_remember_faceResponse(null);
    // Deserialize message field [training_success]
    data.training_success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/search_remember_faceResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'aaffe7376155c795fd881e5816b01e10';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool training_success
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new search_remember_faceResponse(null);
    if (msg.training_success !== undefined) {
      resolved.training_success = msg.training_success;
    }
    else {
      resolved.training_success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: search_remember_faceRequest,
  Response: search_remember_faceResponse,
  md5sum() { return '1b76e414cf496b642eb3183c8057e767'; },
  datatype() { return 'knowledge_msgs/search_remember_face'; }
};
