// Auto-generated. Do not edit!

// (in-package vision_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class FindPlaneRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.name = null;
      this.point_cloud = null;
    }
    else {
      if (initObj.hasOwnProperty('name')) {
        this.name = initObj.name
      }
      else {
        this.name = '';
      }
      if (initObj.hasOwnProperty('point_cloud')) {
        this.point_cloud = initObj.point_cloud
      }
      else {
        this.point_cloud = new sensor_msgs.msg.PointCloud2();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FindPlaneRequest
    // Serialize message field [name]
    bufferOffset = _serializer.string(obj.name, buffer, bufferOffset);
    // Serialize message field [point_cloud]
    bufferOffset = sensor_msgs.msg.PointCloud2.serialize(obj.point_cloud, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FindPlaneRequest
    let len;
    let data = new FindPlaneRequest(null);
    // Deserialize message field [name]
    data.name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [point_cloud]
    data.point_cloud = sensor_msgs.msg.PointCloud2.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.name.length;
    length += sensor_msgs.msg.PointCloud2.getMessageSize(object.point_cloud);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/FindPlaneRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '24a1c00aaaa04ab0f6e71328b58eb6c4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string name
    sensor_msgs/PointCloud2 point_cloud
    
    ================================================================================
    MSG: sensor_msgs/PointCloud2
    # This message holds a collection of N-dimensional points, which may
    # contain additional information such as normals, intensity, etc. The
    # point data is stored as a binary blob, its layout described by the
    # contents of the "fields" array.
    
    # The point cloud data may be organized 2d (image-like) or 1d
    # (unordered). Point clouds organized as 2d images may be produced by
    # camera depth sensors such as stereo or time-of-flight.
    
    # Time of sensor data acquisition, and the coordinate frame ID (for 3d
    # points).
    Header header
    
    # 2D structure of the point cloud. If the cloud is unordered, height is
    # 1 and width is the length of the point cloud.
    uint32 height
    uint32 width
    
    # Describes the channels and their layout in the binary data blob.
    PointField[] fields
    
    bool    is_bigendian # Is this data bigendian?
    uint32  point_step   # Length of a point in bytes
    uint32  row_step     # Length of a row in bytes
    uint8[] data         # Actual point data, size is (row_step*height)
    
    bool is_dense        # True if there are no invalid points
    
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
    MSG: sensor_msgs/PointField
    # This message holds the description of one point entry in the
    # PointCloud2 message format.
    uint8 INT8    = 1
    uint8 UINT8   = 2
    uint8 INT16   = 3
    uint8 UINT16  = 4
    uint8 INT32   = 5
    uint8 UINT32  = 6
    uint8 FLOAT32 = 7
    uint8 FLOAT64 = 8
    
    string name      # Name of field
    uint32 offset    # Offset from start of point struct
    uint8  datatype  # Datatype enumeration, see above
    uint32 count     # How many elements in the field
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FindPlaneRequest(null);
    if (msg.name !== undefined) {
      resolved.name = msg.name;
    }
    else {
      resolved.name = ''
    }

    if (msg.point_cloud !== undefined) {
      resolved.point_cloud = sensor_msgs.msg.PointCloud2.Resolve(msg.point_cloud)
    }
    else {
      resolved.point_cloud = new sensor_msgs.msg.PointCloud2()
    }

    return resolved;
    }
};

class FindPlaneResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.inliers = null;
      this.centroidFreeSpace = null;
      this.nearestPoint = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('inliers')) {
        this.inliers = initObj.inliers
      }
      else {
        this.inliers = [];
      }
      if (initObj.hasOwnProperty('centroidFreeSpace')) {
        this.centroidFreeSpace = initObj.centroidFreeSpace
      }
      else {
        this.centroidFreeSpace = [];
      }
      if (initObj.hasOwnProperty('nearestPoint')) {
        this.nearestPoint = initObj.nearestPoint
      }
      else {
        this.nearestPoint = new geometry_msgs.msg.Point();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FindPlaneResponse
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [inliers]
    // Serialize the length for message field [inliers]
    bufferOffset = _serializer.uint32(obj.inliers.length, buffer, bufferOffset);
    obj.inliers.forEach((val) => {
      bufferOffset = std_msgs.msg.Int32.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [centroidFreeSpace]
    // Serialize the length for message field [centroidFreeSpace]
    bufferOffset = _serializer.uint32(obj.centroidFreeSpace.length, buffer, bufferOffset);
    obj.centroidFreeSpace.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [nearestPoint]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.nearestPoint, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FindPlaneResponse
    let len;
    let data = new FindPlaneResponse(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [inliers]
    // Deserialize array length for message field [inliers]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.inliers = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.inliers[i] = std_msgs.msg.Int32.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [centroidFreeSpace]
    // Deserialize array length for message field [centroidFreeSpace]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.centroidFreeSpace = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.centroidFreeSpace[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [nearestPoint]
    data.nearestPoint = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 4 * object.inliers.length;
    length += 24 * object.centroidFreeSpace.length;
    return length + 32;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/FindPlaneResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2bf5756a4399688586f4b7e4f5ae1e09';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    std_msgs/Int32[] inliers
    geometry_msgs/Point[] 	centroidFreeSpace
    geometry_msgs/Point 	nearestPoint
    
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
    MSG: std_msgs/Int32
    int32 data
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
    const resolved = new FindPlaneResponse(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.inliers !== undefined) {
      resolved.inliers = new Array(msg.inliers.length);
      for (let i = 0; i < resolved.inliers.length; ++i) {
        resolved.inliers[i] = std_msgs.msg.Int32.Resolve(msg.inliers[i]);
      }
    }
    else {
      resolved.inliers = []
    }

    if (msg.centroidFreeSpace !== undefined) {
      resolved.centroidFreeSpace = new Array(msg.centroidFreeSpace.length);
      for (let i = 0; i < resolved.centroidFreeSpace.length; ++i) {
        resolved.centroidFreeSpace[i] = geometry_msgs.msg.Point.Resolve(msg.centroidFreeSpace[i]);
      }
    }
    else {
      resolved.centroidFreeSpace = []
    }

    if (msg.nearestPoint !== undefined) {
      resolved.nearestPoint = geometry_msgs.msg.Point.Resolve(msg.nearestPoint)
    }
    else {
      resolved.nearestPoint = new geometry_msgs.msg.Point()
    }

    return resolved;
    }
};

module.exports = {
  Request: FindPlaneRequest,
  Response: FindPlaneResponse,
  md5sum() { return 'c9f71d0b8ee8e7ee471db6c2ca795c1a'; },
  datatype() { return 'vision_msgs/FindPlane'; }
};
