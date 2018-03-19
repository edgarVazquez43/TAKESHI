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
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

class VisionPlane {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.point_cloud = null;
      this.centroid = null;
      this.normal = null;
      this.bounding_polygon = null;
    }
    else {
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = '';
      }
      if (initObj.hasOwnProperty('point_cloud')) {
        this.point_cloud = initObj.point_cloud
      }
      else {
        this.point_cloud = new sensor_msgs.msg.PointCloud2();
      }
      if (initObj.hasOwnProperty('centroid')) {
        this.centroid = initObj.centroid
      }
      else {
        this.centroid = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('normal')) {
        this.normal = initObj.normal
      }
      else {
        this.normal = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('bounding_polygon')) {
        this.bounding_polygon = initObj.bounding_polygon
      }
      else {
        this.bounding_polygon = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VisionPlane
    // Serialize message field [id]
    bufferOffset = _serializer.string(obj.id, buffer, bufferOffset);
    // Serialize message field [point_cloud]
    bufferOffset = sensor_msgs.msg.PointCloud2.serialize(obj.point_cloud, buffer, bufferOffset);
    // Serialize message field [centroid]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.centroid, buffer, bufferOffset);
    // Serialize message field [normal]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.normal, buffer, bufferOffset);
    // Serialize message field [bounding_polygon]
    // Serialize the length for message field [bounding_polygon]
    bufferOffset = _serializer.uint32(obj.bounding_polygon.length, buffer, bufferOffset);
    obj.bounding_polygon.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Vector3.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VisionPlane
    let len;
    let data = new VisionPlane(null);
    // Deserialize message field [id]
    data.id = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [point_cloud]
    data.point_cloud = sensor_msgs.msg.PointCloud2.deserialize(buffer, bufferOffset);
    // Deserialize message field [centroid]
    data.centroid = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [normal]
    data.normal = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [bounding_polygon]
    // Deserialize array length for message field [bounding_polygon]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.bounding_polygon = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.bounding_polygon[i] = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.id.length;
    length += sensor_msgs.msg.PointCloud2.getMessageSize(object.point_cloud);
    length += 24 * object.bounding_polygon.length;
    return length + 56;
  }

  static datatype() {
    // Returns string type for a message object
    return 'vision_msgs/VisionPlane';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9dde39900df0527c4edab2ecf1c2188c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string id                                    #plane id (desk, floor, etc)
    sensor_msgs/PointCloud2 point_cloud          #Point cloud (probably, colored)
    geometry_msgs/Vector3 centroid               
    geometry_msgs/Vector3 normal                 #normal vector to the plane (should be normalized)
    geometry_msgs/Vector3[] bounding_polygon     #N vectors 
    
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VisionPlane(null);
    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = ''
    }

    if (msg.point_cloud !== undefined) {
      resolved.point_cloud = sensor_msgs.msg.PointCloud2.Resolve(msg.point_cloud)
    }
    else {
      resolved.point_cloud = new sensor_msgs.msg.PointCloud2()
    }

    if (msg.centroid !== undefined) {
      resolved.centroid = geometry_msgs.msg.Vector3.Resolve(msg.centroid)
    }
    else {
      resolved.centroid = new geometry_msgs.msg.Vector3()
    }

    if (msg.normal !== undefined) {
      resolved.normal = geometry_msgs.msg.Vector3.Resolve(msg.normal)
    }
    else {
      resolved.normal = new geometry_msgs.msg.Vector3()
    }

    if (msg.bounding_polygon !== undefined) {
      resolved.bounding_polygon = new Array(msg.bounding_polygon.length);
      for (let i = 0; i < resolved.bounding_polygon.length; ++i) {
        resolved.bounding_polygon[i] = geometry_msgs.msg.Vector3.Resolve(msg.bounding_polygon[i]);
      }
    }
    else {
      resolved.bounding_polygon = []
    }

    return resolved;
    }
};

module.exports = VisionPlane;
