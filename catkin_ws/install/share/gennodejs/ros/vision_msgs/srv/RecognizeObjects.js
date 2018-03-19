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

let VisionObject = require('../msg/VisionObject.js');

//-----------------------------------------------------------

class RecognizeObjectsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.point_cloud = null;
    }
    else {
      if (initObj.hasOwnProperty('point_cloud')) {
        this.point_cloud = initObj.point_cloud
      }
      else {
        this.point_cloud = new sensor_msgs.msg.PointCloud2();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RecognizeObjectsRequest
    // Serialize message field [point_cloud]
    bufferOffset = sensor_msgs.msg.PointCloud2.serialize(obj.point_cloud, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RecognizeObjectsRequest
    let len;
    let data = new RecognizeObjectsRequest(null);
    // Deserialize message field [point_cloud]
    data.point_cloud = sensor_msgs.msg.PointCloud2.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += sensor_msgs.msg.PointCloud2.getMessageSize(object.point_cloud);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/RecognizeObjectsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd8288ab03c94033ddae07988baace1f7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new RecognizeObjectsRequest(null);
    if (msg.point_cloud !== undefined) {
      resolved.point_cloud = sensor_msgs.msg.PointCloud2.Resolve(msg.point_cloud)
    }
    else {
      resolved.point_cloud = new sensor_msgs.msg.PointCloud2()
    }

    return resolved;
    }
};

class RecognizeObjectsResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.recog_objects = null;
    }
    else {
      if (initObj.hasOwnProperty('recog_objects')) {
        this.recog_objects = initObj.recog_objects
      }
      else {
        this.recog_objects = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RecognizeObjectsResponse
    // Serialize message field [recog_objects]
    // Serialize the length for message field [recog_objects]
    bufferOffset = _serializer.uint32(obj.recog_objects.length, buffer, bufferOffset);
    obj.recog_objects.forEach((val) => {
      bufferOffset = VisionObject.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RecognizeObjectsResponse
    let len;
    let data = new RecognizeObjectsResponse(null);
    // Deserialize message field [recog_objects]
    // Deserialize array length for message field [recog_objects]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.recog_objects = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.recog_objects[i] = VisionObject.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.recog_objects.forEach((val) => {
      length += VisionObject.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/RecognizeObjectsResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c88df401c6f571c8ab4290b36732453b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    vision_msgs/VisionObject[] recog_objects
    
    ================================================================================
    MSG: vision_msgs/VisionObject
    std_msgs/Header header
    string id                                    #name of identifying the object (milk, orange juice, etc)
    string category                              #object type (drink, snack, etc)
    float32 confidence                           #value in [0,1] indicating the probability of a correct identification
    sensor_msgs/Image image			     #image in rgb of object;
    sensor_msgs/PointCloud2 point_cloud          #Point cloud (probably, colored)
    geometry_msgs/Vector3 size                   #Size in meters: size in x, y and z
    geometry_msgs/Pose pose                      #Centroid and orientation
    geometry_msgs/Vector3[] bounding_box         #Two vectors indicating the bounding box
    geometry_msgs/Vector3[] bounding_polygon     #N vectors 
    int32 x					     #top left x
    int32 y					     #top left y
    int32 width				     #top widht
    int32 height				     #top height
    bool graspable                               #graspable by the arm
    
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
    MSG: sensor_msgs/Image
    # This message contains an uncompressed image
    # (0, 0) is at top-left corner of image
    #
    
    Header header        # Header timestamp should be acquisition time of image
                         # Header frame_id should be optical frame of camera
                         # origin of frame should be optical center of cameara
                         # +x should point to the right in the image
                         # +y should point down in the image
                         # +z should point into to plane of the image
                         # If the frame_id here and the frame_id of the CameraInfo
                         # message associated with the image conflict
                         # the behavior is undefined
    
    uint32 height         # image height, that is, number of rows
    uint32 width          # image width, that is, number of columns
    
    # The legal values for encoding are in file src/image_encodings.cpp
    # If you want to standardize a new string format, join
    # ros-users@lists.sourceforge.net and send an email proposing a new encoding.
    
    string encoding       # Encoding of pixels -- channel meaning, ordering, size
                          # taken from the list of strings in include/sensor_msgs/image_encodings.h
    
    uint8 is_bigendian    # is this data bigendian?
    uint32 step           # Full row length in bytes
    uint8[] data          # actual matrix data, size is (step * rows)
    
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
    const resolved = new RecognizeObjectsResponse(null);
    if (msg.recog_objects !== undefined) {
      resolved.recog_objects = new Array(msg.recog_objects.length);
      for (let i = 0; i < resolved.recog_objects.length; ++i) {
        resolved.recog_objects[i] = VisionObject.Resolve(msg.recog_objects[i]);
      }
    }
    else {
      resolved.recog_objects = []
    }

    return resolved;
    }
};

module.exports = {
  Request: RecognizeObjectsRequest,
  Response: RecognizeObjectsResponse,
  md5sum() { return '8ec83fb54a82b05f779c1008aa4b3e0c'; },
  datatype() { return 'vision_msgs/RecognizeObjects'; }
};
