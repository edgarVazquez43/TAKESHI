// Auto-generated. Do not edit!

// (in-package vision_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let SkeletonJoint = require('./SkeletonJoint.js');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class Skeleton {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.user_id = null;
      this.ref_point = null;
      this.joints = null;
    }
    else {
      if (initObj.hasOwnProperty('user_id')) {
        this.user_id = initObj.user_id
      }
      else {
        this.user_id = 0;
      }
      if (initObj.hasOwnProperty('ref_point')) {
        this.ref_point = initObj.ref_point
      }
      else {
        this.ref_point = new geometry_msgs.msg.Point32();
      }
      if (initObj.hasOwnProperty('joints')) {
        this.joints = initObj.joints
      }
      else {
        this.joints = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Skeleton
    // Serialize message field [user_id]
    bufferOffset = _serializer.int32(obj.user_id, buffer, bufferOffset);
    // Serialize message field [ref_point]
    bufferOffset = geometry_msgs.msg.Point32.serialize(obj.ref_point, buffer, bufferOffset);
    // Serialize message field [joints]
    // Serialize the length for message field [joints]
    bufferOffset = _serializer.uint32(obj.joints.length, buffer, bufferOffset);
    obj.joints.forEach((val) => {
      bufferOffset = SkeletonJoint.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Skeleton
    let len;
    let data = new Skeleton(null);
    // Deserialize message field [user_id]
    data.user_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [ref_point]
    data.ref_point = geometry_msgs.msg.Point32.deserialize(buffer, bufferOffset);
    // Deserialize message field [joints]
    // Deserialize array length for message field [joints]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.joints = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.joints[i] = SkeletonJoint.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.joints.forEach((val) => {
      length += SkeletonJoint.getMessageSize(val);
    });
    return length + 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/Skeleton';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5f2d8c1c74d0773f8fb9581c67ba2f2a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new Skeleton(null);
    if (msg.user_id !== undefined) {
      resolved.user_id = msg.user_id;
    }
    else {
      resolved.user_id = 0
    }

    if (msg.ref_point !== undefined) {
      resolved.ref_point = geometry_msgs.msg.Point32.Resolve(msg.ref_point)
    }
    else {
      resolved.ref_point = new geometry_msgs.msg.Point32()
    }

    if (msg.joints !== undefined) {
      resolved.joints = new Array(msg.joints.length);
      for (let i = 0; i < resolved.joints.length; ++i) {
        resolved.joints[i] = SkeletonJoint.Resolve(msg.joints[i]);
      }
    }
    else {
      resolved.joints = []
    }

    return resolved;
    }
};

module.exports = Skeleton;
