// Auto-generated. Do not edit!

// (in-package vision_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let GestureSkeleton = require('./GestureSkeleton.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class GestureSkeletons {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.recog_gestures = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('recog_gestures')) {
        this.recog_gestures = initObj.recog_gestures
      }
      else {
        this.recog_gestures = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GestureSkeletons
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [recog_gestures]
    // Serialize the length for message field [recog_gestures]
    bufferOffset = _serializer.uint32(obj.recog_gestures.length, buffer, bufferOffset);
    obj.recog_gestures.forEach((val) => {
      bufferOffset = GestureSkeleton.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GestureSkeletons
    let len;
    let data = new GestureSkeletons(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [recog_gestures]
    // Deserialize array length for message field [recog_gestures]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.recog_gestures = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.recog_gestures[i] = GestureSkeleton.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.recog_gestures.forEach((val) => {
      length += GestureSkeleton.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/GestureSkeletons';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f4df52aabef2b028180e9bc45fa637db';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    vision_msgs/GestureSkeleton[] recog_gestures
    
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
    MSG: vision_msgs/GestureSkeleton
    int8 id		#id of user
    string gesture		#gesture of user
    geometry_msgs/Point gesture_centroid		#Gesture Centroid (x,y,z)
    
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
    const resolved = new GestureSkeletons(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.recog_gestures !== undefined) {
      resolved.recog_gestures = new Array(msg.recog_gestures.length);
      for (let i = 0; i < resolved.recog_gestures.length; ++i) {
        resolved.recog_gestures[i] = GestureSkeleton.Resolve(msg.recog_gestures[i]);
      }
    }
    else {
      resolved.recog_gestures = []
    }

    return resolved;
    }
};

module.exports = GestureSkeletons;
