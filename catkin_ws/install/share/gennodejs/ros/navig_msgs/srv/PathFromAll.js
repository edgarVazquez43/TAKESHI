// Auto-generated. Do not edit!

// (in-package navig_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let nav_msgs = _finder('nav_msgs');
let sensor_msgs = _finder('sensor_msgs');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class PathFromAllRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.start_pose = null;
      this.goal_pose = null;
      this.point_cloud = null;
      this.laser_scan = null;
      this.map = null;
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
      if (initObj.hasOwnProperty('point_cloud')) {
        this.point_cloud = initObj.point_cloud
      }
      else {
        this.point_cloud = new sensor_msgs.msg.PointCloud2();
      }
      if (initObj.hasOwnProperty('laser_scan')) {
        this.laser_scan = initObj.laser_scan
      }
      else {
        this.laser_scan = new sensor_msgs.msg.LaserScan();
      }
      if (initObj.hasOwnProperty('map')) {
        this.map = initObj.map
      }
      else {
        this.map = new nav_msgs.msg.OccupancyGrid();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PathFromAllRequest
    // Serialize message field [start_pose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.start_pose, buffer, bufferOffset);
    // Serialize message field [goal_pose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.goal_pose, buffer, bufferOffset);
    // Serialize message field [point_cloud]
    bufferOffset = sensor_msgs.msg.PointCloud2.serialize(obj.point_cloud, buffer, bufferOffset);
    // Serialize message field [laser_scan]
    bufferOffset = sensor_msgs.msg.LaserScan.serialize(obj.laser_scan, buffer, bufferOffset);
    // Serialize message field [map]
    bufferOffset = nav_msgs.msg.OccupancyGrid.serialize(obj.map, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PathFromAllRequest
    let len;
    let data = new PathFromAllRequest(null);
    // Deserialize message field [start_pose]
    data.start_pose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [goal_pose]
    data.goal_pose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [point_cloud]
    data.point_cloud = sensor_msgs.msg.PointCloud2.deserialize(buffer, bufferOffset);
    // Deserialize message field [laser_scan]
    data.laser_scan = sensor_msgs.msg.LaserScan.deserialize(buffer, bufferOffset);
    // Deserialize message field [map]
    data.map = nav_msgs.msg.OccupancyGrid.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += sensor_msgs.msg.PointCloud2.getMessageSize(object.point_cloud);
    length += sensor_msgs.msg.LaserScan.getMessageSize(object.laser_scan);
    length += nav_msgs.msg.OccupancyGrid.getMessageSize(object.map);
    return length + 112;
  }

  static datatype() {
    // Returns string type for a service object
    return 'navig_msgs/PathFromAllRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0e95d331efd1f47da80105cdf1596581';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Pose start_pose
    geometry_msgs/Pose goal_pose
    sensor_msgs/PointCloud2 point_cloud
    sensor_msgs/LaserScan laser_scan
    nav_msgs/OccupancyGrid map
    
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
    MSG: sensor_msgs/LaserScan
    # Single scan from a planar laser range-finder
    #
    # If you have another ranging device with different behavior (e.g. a sonar
    # array), please find or create a different message, since applications
    # will make fairly laser-specific assumptions about this data
    
    Header header            # timestamp in the header is the acquisition time of 
                             # the first ray in the scan.
                             #
                             # in frame frame_id, angles are measured around 
                             # the positive Z axis (counterclockwise, if Z is up)
                             # with zero angle being forward along the x axis
                             
    float32 angle_min        # start angle of the scan [rad]
    float32 angle_max        # end angle of the scan [rad]
    float32 angle_increment  # angular distance between measurements [rad]
    
    float32 time_increment   # time between measurements [seconds] - if your scanner
                             # is moving, this will be used in interpolating position
                             # of 3d points
    float32 scan_time        # time between scans [seconds]
    
    float32 range_min        # minimum range value [m]
    float32 range_max        # maximum range value [m]
    
    float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)
    float32[] intensities    # intensity data [device-specific units].  If your
                             # device does not provide intensities, please leave
                             # the array empty.
    
    ================================================================================
    MSG: nav_msgs/OccupancyGrid
    # This represents a 2-D grid map, in which each cell represents the probability of
    # occupancy.
    
    Header header 
    
    #MetaData for the map
    MapMetaData info
    
    # The map data, in row-major order, starting with (0,0).  Occupancy
    # probabilities are in the range [0,100].  Unknown is -1.
    int8[] data
    
    ================================================================================
    MSG: nav_msgs/MapMetaData
    # This hold basic information about the characterists of the OccupancyGrid
    
    # The time at which the map was loaded
    time map_load_time
    # The map resolution [m/cell]
    float32 resolution
    # Map width [cells]
    uint32 width
    # Map height [cells]
    uint32 height
    # The origin of the map [m, m, rad].  This is the real-world pose of the
    # cell (0,0) in the map.
    geometry_msgs/Pose origin
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PathFromAllRequest(null);
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

    if (msg.point_cloud !== undefined) {
      resolved.point_cloud = sensor_msgs.msg.PointCloud2.Resolve(msg.point_cloud)
    }
    else {
      resolved.point_cloud = new sensor_msgs.msg.PointCloud2()
    }

    if (msg.laser_scan !== undefined) {
      resolved.laser_scan = sensor_msgs.msg.LaserScan.Resolve(msg.laser_scan)
    }
    else {
      resolved.laser_scan = new sensor_msgs.msg.LaserScan()
    }

    if (msg.map !== undefined) {
      resolved.map = nav_msgs.msg.OccupancyGrid.Resolve(msg.map)
    }
    else {
      resolved.map = new nav_msgs.msg.OccupancyGrid()
    }

    return resolved;
    }
};

class PathFromAllResponse {
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
    // Serializes a message object of type PathFromAllResponse
    // Serialize message field [path]
    bufferOffset = nav_msgs.msg.Path.serialize(obj.path, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PathFromAllResponse
    let len;
    let data = new PathFromAllResponse(null);
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
    return 'navig_msgs/PathFromAllResponse';
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
    const resolved = new PathFromAllResponse(null);
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
  Request: PathFromAllRequest,
  Response: PathFromAllResponse,
  md5sum() { return '16f9de799db2245d5eab2e0bc95c1818'; },
  datatype() { return 'navig_msgs/PathFromAll'; }
};
