// Auto-generated. Do not edit!

// (in-package manip_msgs.srv)


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

class DirectKinematicsFloatArrayRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.articular_pose = null;
    }
    else {
      if (initObj.hasOwnProperty('articular_pose')) {
        this.articular_pose = initObj.articular_pose
      }
      else {
        this.articular_pose = new std_msgs.msg.Float32MultiArray();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DirectKinematicsFloatArrayRequest
    // Serialize message field [articular_pose]
    bufferOffset = std_msgs.msg.Float32MultiArray.serialize(obj.articular_pose, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DirectKinematicsFloatArrayRequest
    let len;
    let data = new DirectKinematicsFloatArrayRequest(null);
    // Deserialize message field [articular_pose]
    data.articular_pose = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Float32MultiArray.getMessageSize(object.articular_pose);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'manip_msgs/DirectKinematicsFloatArrayRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '98280c273a083e97d905afcfe0befc9f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32MultiArray articular_pose
    
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
    const resolved = new DirectKinematicsFloatArrayRequest(null);
    if (msg.articular_pose !== undefined) {
      resolved.articular_pose = std_msgs.msg.Float32MultiArray.Resolve(msg.articular_pose)
    }
    else {
      resolved.articular_pose = new std_msgs.msg.Float32MultiArray()
    }

    return resolved;
    }
};

class DirectKinematicsFloatArrayResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.cartesian_pose = null;
    }
    else {
      if (initObj.hasOwnProperty('cartesian_pose')) {
        this.cartesian_pose = initObj.cartesian_pose
      }
      else {
        this.cartesian_pose = new std_msgs.msg.Float32MultiArray();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DirectKinematicsFloatArrayResponse
    // Serialize message field [cartesian_pose]
    bufferOffset = std_msgs.msg.Float32MultiArray.serialize(obj.cartesian_pose, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DirectKinematicsFloatArrayResponse
    let len;
    let data = new DirectKinematicsFloatArrayResponse(null);
    // Deserialize message field [cartesian_pose]
    data.cartesian_pose = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Float32MultiArray.getMessageSize(object.cartesian_pose);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'manip_msgs/DirectKinematicsFloatArrayResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3d9259e45801a4340eed157f58d7a2f7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32MultiArray cartesian_pose
    
    
    
    
    
    
    
    
    
    
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
    const resolved = new DirectKinematicsFloatArrayResponse(null);
    if (msg.cartesian_pose !== undefined) {
      resolved.cartesian_pose = std_msgs.msg.Float32MultiArray.Resolve(msg.cartesian_pose)
    }
    else {
      resolved.cartesian_pose = new std_msgs.msg.Float32MultiArray()
    }

    return resolved;
    }
};

module.exports = {
  Request: DirectKinematicsFloatArrayRequest,
  Response: DirectKinematicsFloatArrayResponse,
  md5sum() { return '6d3e3a04e953772f57d61cd8e812ab2e'; },
  datatype() { return 'manip_msgs/DirectKinematicsFloatArray'; }
};
