// Auto-generated. Do not edit!

// (in-package vision_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let VisionFaceObjects = require('../msg/VisionFaceObjects.js');

//-----------------------------------------------------------

class FaceRecognitionRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
    }
    else {
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FaceRecognitionRequest
    // Serialize message field [id]
    bufferOffset = _serializer.string(obj.id, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FaceRecognitionRequest
    let len;
    let data = new FaceRecognitionRequest(null);
    // Deserialize message field [id]
    data.id = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.id.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/FaceRecognitionRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bbfcda76036ebbe3d36caf7af80b260c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FaceRecognitionRequest(null);
    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = ''
    }

    return resolved;
    }
};

class FaceRecognitionResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.faces = null;
    }
    else {
      if (initObj.hasOwnProperty('faces')) {
        this.faces = initObj.faces
      }
      else {
        this.faces = new VisionFaceObjects();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FaceRecognitionResponse
    // Serialize message field [faces]
    bufferOffset = VisionFaceObjects.serialize(obj.faces, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FaceRecognitionResponse
    let len;
    let data = new FaceRecognitionResponse(null);
    // Deserialize message field [faces]
    data.faces = VisionFaceObjects.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += VisionFaceObjects.getMessageSize(object.faces);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/FaceRecognitionResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8e2d75e830abfad5240005304b036609';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    vision_msgs/VisionFaceObjects faces
    
    
    ================================================================================
    MSG: vision_msgs/VisionFaceObjects
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
    const resolved = new FaceRecognitionResponse(null);
    if (msg.faces !== undefined) {
      resolved.faces = VisionFaceObjects.Resolve(msg.faces)
    }
    else {
      resolved.faces = new VisionFaceObjects()
    }

    return resolved;
    }
};

module.exports = {
  Request: FaceRecognitionRequest,
  Response: FaceRecognitionResponse,
  md5sum() { return '7d89880e89dec4d521ffd613fc0a764b'; },
  datatype() { return 'vision_msgs/FaceRecognition'; }
};
