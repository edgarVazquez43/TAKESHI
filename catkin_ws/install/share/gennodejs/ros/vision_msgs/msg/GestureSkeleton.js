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

class GestureSkeleton {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.gesture = null;
      this.gesture_centroid = null;
    }
    else {
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('gesture')) {
        this.gesture = initObj.gesture
      }
      else {
        this.gesture = '';
      }
      if (initObj.hasOwnProperty('gesture_centroid')) {
        this.gesture_centroid = initObj.gesture_centroid
      }
      else {
        this.gesture_centroid = new geometry_msgs.msg.Point();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GestureSkeleton
    // Serialize message field [id]
    bufferOffset = _serializer.int8(obj.id, buffer, bufferOffset);
    // Serialize message field [gesture]
    bufferOffset = _serializer.string(obj.gesture, buffer, bufferOffset);
    // Serialize message field [gesture_centroid]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.gesture_centroid, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GestureSkeleton
    let len;
    let data = new GestureSkeleton(null);
    // Deserialize message field [id]
    data.id = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [gesture]
    data.gesture = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [gesture_centroid]
    data.gesture_centroid = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.gesture.length;
    return length + 29;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/GestureSkeleton';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1e87d31b651e197f45459ceb0c0353fb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new GestureSkeleton(null);
    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.gesture !== undefined) {
      resolved.gesture = msg.gesture;
    }
    else {
      resolved.gesture = ''
    }

    if (msg.gesture_centroid !== undefined) {
      resolved.gesture_centroid = geometry_msgs.msg.Point.Resolve(msg.gesture_centroid)
    }
    else {
      resolved.gesture_centroid = new geometry_msgs.msg.Point()
    }

    return resolved;
    }
};

module.exports = GestureSkeleton;
