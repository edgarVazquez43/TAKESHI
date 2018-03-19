// Auto-generated. Do not edit!

// (in-package vision_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let VisionFaceObject = require('./VisionFaceObject.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VisionFaceObjects {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.recog_faces = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('recog_faces')) {
        this.recog_faces = initObj.recog_faces
      }
      else {
        this.recog_faces = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VisionFaceObjects
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [recog_faces]
    // Serialize the length for message field [recog_faces]
    bufferOffset = _serializer.uint32(obj.recog_faces.length, buffer, bufferOffset);
    obj.recog_faces.forEach((val) => {
      bufferOffset = VisionFaceObject.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VisionFaceObjects
    let len;
    let data = new VisionFaceObjects(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [recog_faces]
    // Deserialize array length for message field [recog_faces]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.recog_faces = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.recog_faces[i] = VisionFaceObject.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.recog_faces.forEach((val) => {
      length += VisionFaceObject.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/VisionFaceObjects';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4fd1cb6b6d63c7ee8d419e777e468fd2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    vision_msgs/VisionFaceObject[] recog_faces
    
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
    MSG: vision_msgs/VisionFaceObject
    string id                                    #face id
    float32 confidence                           #value in [0,1] indicating the probability of a correct identification
    geometry_msgs/Point face_centroid            #Face Centroid (x,y,z)
    geometry_msgs/Point[] bounding_box           #Face bounding box 2D 
    bool smile                                   #smiling face
    int8 gender                                  #Gender ID. 0: female, 1: male, 2: unknown
    
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
    const resolved = new VisionFaceObjects(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.recog_faces !== undefined) {
      resolved.recog_faces = new Array(msg.recog_faces.length);
      for (let i = 0; i < resolved.recog_faces.length; ++i) {
        resolved.recog_faces[i] = VisionFaceObject.Resolve(msg.recog_faces[i]);
      }
    }
    else {
      resolved.recog_faces = []
    }

    return resolved;
    }
};

module.exports = VisionFaceObjects;
