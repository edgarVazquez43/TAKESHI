// Auto-generated. Do not edit!

// (in-package navig_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

let nav_msgs = _finder('nav_msgs');

//-----------------------------------------------------------

class PlanPathRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.start_pose = null;
      this.goal_pose = null;
      this.start_location_id = null;
      this.goal_location_id = null;
    }
    else {
      if (initObj.hasOwnProperty('start_pose')) {
        this.start_pose = initObj.start_pose
      }
      else {
        this.start_pose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('goal_pose')) {
        this.goal_pose = initObj.goal_pose
      }
      else {
        this.goal_pose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('start_location_id')) {
        this.start_location_id = initObj.start_location_id
      }
      else {
        this.start_location_id = '';
      }
      if (initObj.hasOwnProperty('goal_location_id')) {
        this.goal_location_id = initObj.goal_location_id
      }
      else {
        this.goal_location_id = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PlanPathRequest
    // Serialize message field [start_pose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.start_pose, buffer, bufferOffset);
    // Serialize message field [goal_pose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.goal_pose, buffer, bufferOffset);
    // Serialize message field [start_location_id]
    bufferOffset = _serializer.string(obj.start_location_id, buffer, bufferOffset);
    // Serialize message field [goal_location_id]
    bufferOffset = _serializer.string(obj.goal_location_id, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PlanPathRequest
    let len;
    let data = new PlanPathRequest(null);
    // Deserialize message field [start_pose]
    data.start_pose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [goal_pose]
    data.goal_pose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [start_location_id]
    data.start_location_id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [goal_location_id]
    data.goal_location_id = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.start_location_id.length;
    length += object.goal_location_id.length;
    return length + 120;
  }

  static datatype() {
    // Returns string type for a service object
    return 'navig_msgs/PlanPathRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e328a33f1ac3d707db24f1f00f6a5f08';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Pose start_pose
    geometry_msgs/Pose goal_pose
    string start_location_id
    string goal_location_id
    
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
    const resolved = new PlanPathRequest(null);
    if (msg.start_pose !== undefined) {
      resolved.start_pose = geometry_msgs.msg.Pose.Resolve(msg.start_pose)
    }
    else {
      resolved.start_pose = new geometry_msgs.msg.Pose()
    }

    if (msg.goal_pose !== undefined) {
      resolved.goal_pose = geometry_msgs.msg.Pose.Resolve(msg.goal_pose)
    }
    else {
      resolved.goal_pose = new geometry_msgs.msg.Pose()
    }

    if (msg.start_location_id !== undefined) {
      resolved.start_location_id = msg.start_location_id;
    }
    else {
      resolved.start_location_id = ''
    }

    if (msg.goal_location_id !== undefined) {
      resolved.goal_location_id = msg.goal_location_id;
    }
    else {
      resolved.goal_location_id = ''
    }

    return resolved;
    }
};

class PlanPathResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.path = null;
    }
    else {
      if (initObj.hasOwnProperty('path')) {
        this.path = initObj.path
      }
      else {
        this.path = new nav_msgs.msg.Path();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PlanPathResponse
    // Serialize message field [path]
    bufferOffset = nav_msgs.msg.Path.serialize(obj.path, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PlanPathResponse
    let len;
    let data = new PlanPathResponse(null);
    // Deserialize message field [path]
    data.path = nav_msgs.msg.Path.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += nav_msgs.msg.Path.getMessageSize(object.path);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'navig_msgs/PlanPathResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '58d6f138c7de7ef47c75d4b7e5df5472';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    nav_msgs/Path path
    
    
    
    
    
    
    
    
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
    const resolved = new PlanPathResponse(null);
    if (msg.path !== undefined) {
      resolved.path = nav_msgs.msg.Path.Resolve(msg.path)
    }
    else {
      resolved.path = new nav_msgs.msg.Path()
    }

    return resolved;
    }
};

module.exports = {
  Request: PlanPathRequest,
  Response: PlanPathResponse,
  md5sum() { return 'd4c7fd7dba298b47cf73caf450fd8a9f'; },
  datatype() { return 'navig_msgs/PlanPath'; }
};
