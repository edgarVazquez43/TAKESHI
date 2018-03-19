// Auto-generated. Do not edit!

// (in-package manip_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let nav_msgs = _finder('nav_msgs');

//-----------------------------------------------------------

let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class InverseKinematicsPathRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.cartesian_path = null;
    }
    else {
      if (initObj.hasOwnProperty('cartesian_path')) {
        this.cartesian_path = initObj.cartesian_path
      }
      else {
        this.cartesian_path = new nav_msgs.msg.Path();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type InverseKinematicsPathRequest
    // Serialize message field [cartesian_path]
    bufferOffset = nav_msgs.msg.Path.serialize(obj.cartesian_path, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type InverseKinematicsPathRequest
    let len;
    let data = new InverseKinematicsPathRequest(null);
    // Deserialize message field [cartesian_path]
    data.cartesian_path = nav_msgs.msg.Path.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += nav_msgs.msg.Path.getMessageSize(object.cartesian_path);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'manip_msgs/InverseKinematicsPathRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2cb4994d51effbee68ec44871fa9897e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    nav_msgs/Path cartesian_path
    
    ================================================================================
    MSG: nav_msgs/Path
    #An array of poses that represents a Path for a robot to follow
    Header header
    geometry_msgs/PoseStamped[] poses
    
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
    MSG: geometry_msgs/PoseStamped
    # A Pose with reference coordinate frame and timestamp
    Header header
    Pose pose
    
    ================================================================================
    MSG: geometry_msgs/Pose
    # A representation of pose in free space, composed of position and orientation. 
    Point position
    Quaternion orientation
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    ================================================================================
    MSG: geometry_msgs/Quaternion
    # This represents an orientation in free space in quaternion form.
    
    float64 x
    float64 y
    float64 z
    float64 w
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new InverseKinematicsPathRequest(null);
    if (msg.cartesian_path !== undefined) {
      resolved.cartesian_path = nav_msgs.msg.Path.Resolve(msg.cartesian_path)
    }
    else {
      resolved.cartesian_path = new nav_msgs.msg.Path()
    }

    return resolved;
    }
};

class InverseKinematicsPathResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.articular_path = null;
    }
    else {
      if (initObj.hasOwnProperty('articular_path')) {
        this.articular_path = initObj.articular_path
      }
      else {
        this.articular_path = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type InverseKinematicsPathResponse
    // Serialize message field [articular_path]
    // Serialize the length for message field [articular_path]
    bufferOffset = _serializer.uint32(obj.articular_path.length, buffer, bufferOffset);
    obj.articular_path.forEach((val) => {
      bufferOffset = std_msgs.msg.Float32MultiArray.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type InverseKinematicsPathResponse
    let len;
    let data = new InverseKinematicsPathResponse(null);
    // Deserialize message field [articular_path]
    // Deserialize array length for message field [articular_path]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.articular_path = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.articular_path[i] = std_msgs.msg.Float32MultiArray.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.articular_path.forEach((val) => {
      length += std_msgs.msg.Float32MultiArray.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'manip_msgs/InverseKinematicsPathResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '78f5199c75f7487cfdc5b4d31cc87362';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Float32MultiArray[] articular_path
    
    
    
    
    
    
    
    
    
    
    
    
    
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
    const resolved = new InverseKinematicsPathResponse(null);
    if (msg.articular_path !== undefined) {
      resolved.articular_path = new Array(msg.articular_path.length);
      for (let i = 0; i < resolved.articular_path.length; ++i) {
        resolved.articular_path[i] = std_msgs.msg.Float32MultiArray.Resolve(msg.articular_path[i]);
      }
    }
    else {
      resolved.articular_path = []
    }

    return resolved;
    }
};

module.exports = {
  Request: InverseKinematicsPathRequest,
  Response: InverseKinematicsPathResponse,
  md5sum() { return 'a5c97a40ea2d6c552050c61cfc35f302'; },
  datatype() { return 'manip_msgs/InverseKinematicsPath'; }
};
