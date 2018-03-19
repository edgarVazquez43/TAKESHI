// Auto-generated. Do not edit!

// (in-package knowledge_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let vision_msgs = _finder('vision_msgs');

//-----------------------------------------------------------

class find_personRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.person_face_id = null;
      this.location = null;
    }
    else {
      if (initObj.hasOwnProperty('person_face_id')) {
        this.person_face_id = initObj.person_face_id
      }
      else {
        this.person_face_id = '';
      }
      if (initObj.hasOwnProperty('location')) {
        this.location = initObj.location
      }
      else {
        this.location = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type find_personRequest
    // Serialize message field [person_face_id]
    bufferOffset = _serializer.string(obj.person_face_id, buffer, bufferOffset);
    // Serialize message field [location]
    bufferOffset = _serializer.string(obj.location, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type find_personRequest
    let len;
    let data = new find_personRequest(null);
    // Deserialize message field [person_face_id]
    data.person_face_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [location]
    data.location = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.person_face_id.length;
    length += object.location.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/find_personRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '129b97809ad0a5de0db4efc9d284c7f7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string person_face_id
    string location
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new find_personRequest(null);
    if (msg.person_face_id !== undefined) {
      resolved.person_face_id = msg.person_face_id;
    }
    else {
      resolved.person_face_id = ''
    }

    if (msg.location !== undefined) {
      resolved.location = msg.location;
    }
    else {
      resolved.location = ''
    }

    return resolved;
    }
};

class find_personResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.person_face = null;
      this.task_success = null;
    }
    else {
      if (initObj.hasOwnProperty('person_face')) {
        this.person_face = initObj.person_face
      }
      else {
        this.person_face = new vision_msgs.msg.VisionFaceObject();
      }
      if (initObj.hasOwnProperty('task_success')) {
        this.task_success = initObj.task_success
      }
      else {
        this.task_success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type find_personResponse
    // Serialize message field [person_face]
    bufferOffset = vision_msgs.msg.VisionFaceObject.serialize(obj.person_face, buffer, bufferOffset);
    // Serialize message field [task_success]
    bufferOffset = _serializer.bool(obj.task_success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type find_personResponse
    let len;
    let data = new find_personResponse(null);
    // Deserialize message field [person_face]
    data.person_face = vision_msgs.msg.VisionFaceObject.deserialize(buffer, bufferOffset);
    // Deserialize message field [task_success]
    data.task_success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += vision_msgs.msg.VisionFaceObject.getMessageSize(object.person_face);
    return length + 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'knowledge_msgs/find_personResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '447e2e729a9086b0d48c8a37ddf7990f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    vision_msgs/VisionFaceObject person_face
    bool task_success
    
    
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
    const resolved = new find_personResponse(null);
    if (msg.person_face !== undefined) {
      resolved.person_face = vision_msgs.msg.VisionFaceObject.Resolve(msg.person_face)
    }
    else {
      resolved.person_face = new vision_msgs.msg.VisionFaceObject()
    }

    if (msg.task_success !== undefined) {
      resolved.task_success = msg.task_success;
    }
    else {
      resolved.task_success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: find_personRequest,
  Response: find_personResponse,
  md5sum() { return '0819b34699306bff12623f558a5cd6ca'; },
  datatype() { return 'knowledge_msgs/find_person'; }
};
