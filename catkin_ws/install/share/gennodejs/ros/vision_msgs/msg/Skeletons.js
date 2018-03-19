// Auto-generated. Do not edit!

// (in-package vision_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Skeleton = require('./Skeleton.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Skeletons {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.skeletons = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('skeletons')) {
        this.skeletons = initObj.skeletons
      }
      else {
        this.skeletons = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Skeletons
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [skeletons]
    // Serialize the length for message field [skeletons]
    bufferOffset = _serializer.uint32(obj.skeletons.length, buffer, bufferOffset);
    obj.skeletons.forEach((val) => {
      bufferOffset = Skeleton.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Skeletons
    let len;
    let data = new Skeletons(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [skeletons]
    // Deserialize array length for message field [skeletons]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.skeletons = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.skeletons[i] = Skeleton.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.skeletons.forEach((val) => {
      length += Skeleton.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/Skeletons';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '234171c21eb8e829a5bd64c12d7b744b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    vision_msgs/Skeleton[] skeletons
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
    MSG: vision_msgs/Skeleton
    int32 user_id
    geometry_msgs/Point32 ref_point
    vision_msgs/SkeletonJoint[] joints
    
    ================================================================================
    MSG: geometry_msgs/Point32
    # This contains the position of a point in free space(with 32 bits of precision).
    # It is recommeded to use Point wherever possible instead of Point32.  
    # 
    # This recommendation is to promote interoperability.  
    #
    # This message is designed to take up less space when sending
    # lots of points at once, as in the case of a PointCloud.  
    
    float32 x
    float32 y
    float32 z
    ================================================================================
    MSG: vision_msgs/SkeletonJoint
    std_msgs/String name_joint
    geometry_msgs/Vector3 position
    geometry_msgs/Quaternion orientation
    
    ================================================================================
    MSG: std_msgs/String
    string data
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
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
    const resolved = new Skeletons(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.skeletons !== undefined) {
      resolved.skeletons = new Array(msg.skeletons.length);
      for (let i = 0; i < resolved.skeletons.length; ++i) {
        resolved.skeletons[i] = Skeleton.Resolve(msg.skeletons[i]);
      }
    }
    else {
      resolved.skeletons = []
    }

    return resolved;
    }
};

module.exports = Skeletons;
