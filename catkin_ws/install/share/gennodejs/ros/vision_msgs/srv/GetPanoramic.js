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

let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

class GetPanoramicRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.head_pan_min = null;
      this.head_pan_max = null;
      this.head_tilt_min = null;
      this.head_tilt_max = null;
    }
    else {
      if (initObj.hasOwnProperty('head_pan_min')) {
        this.head_pan_min = initObj.head_pan_min
      }
      else {
        this.head_pan_min = 0.0;
      }
      if (initObj.hasOwnProperty('head_pan_max')) {
        this.head_pan_max = initObj.head_pan_max
      }
      else {
        this.head_pan_max = 0.0;
      }
      if (initObj.hasOwnProperty('head_tilt_min')) {
        this.head_tilt_min = initObj.head_tilt_min
      }
      else {
        this.head_tilt_min = 0.0;
      }
      if (initObj.hasOwnProperty('head_tilt_max')) {
        this.head_tilt_max = initObj.head_tilt_max
      }
      else {
        this.head_tilt_max = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetPanoramicRequest
    // Serialize message field [head_pan_min]
    bufferOffset = _serializer.float32(obj.head_pan_min, buffer, bufferOffset);
    // Serialize message field [head_pan_max]
    bufferOffset = _serializer.float32(obj.head_pan_max, buffer, bufferOffset);
    // Serialize message field [head_tilt_min]
    bufferOffset = _serializer.float32(obj.head_tilt_min, buffer, bufferOffset);
    // Serialize message field [head_tilt_max]
    bufferOffset = _serializer.float32(obj.head_tilt_max, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetPanoramicRequest
    let len;
    let data = new GetPanoramicRequest(null);
    // Deserialize message field [head_pan_min]
    data.head_pan_min = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [head_pan_max]
    data.head_pan_max = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [head_tilt_min]
    data.head_tilt_min = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [head_tilt_max]
    data.head_tilt_max = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/GetPanoramicRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b149da6f54b371a0f2a877e89f17bd10';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 head_pan_min
    float32 head_pan_max
    float32 head_tilt_min
    float32 head_tilt_max
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetPanoramicRequest(null);
    if (msg.head_pan_min !== undefined) {
      resolved.head_pan_min = msg.head_pan_min;
    }
    else {
      resolved.head_pan_min = 0.0
    }

    if (msg.head_pan_max !== undefined) {
      resolved.head_pan_max = msg.head_pan_max;
    }
    else {
      resolved.head_pan_max = 0.0
    }

    if (msg.head_tilt_min !== undefined) {
      resolved.head_tilt_min = msg.head_tilt_min;
    }
    else {
      resolved.head_tilt_min = 0.0
    }

    if (msg.head_tilt_max !== undefined) {
      resolved.head_tilt_max = msg.head_tilt_max;
    }
    else {
      resolved.head_tilt_max = 0.0
    }

    return resolved;
    }
};

class GetPanoramicResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.panoramic_image = null;
      this.panoramic_cloud = null;
    }
    else {
      if (initObj.hasOwnProperty('panoramic_image')) {
        this.panoramic_image = initObj.panoramic_image
      }
      else {
        this.panoramic_image = new sensor_msgs.msg.Image();
      }
      if (initObj.hasOwnProperty('panoramic_cloud')) {
        this.panoramic_cloud = initObj.panoramic_cloud
      }
      else {
        this.panoramic_cloud = new sensor_msgs.msg.PointCloud2();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetPanoramicResponse
    // Serialize message field [panoramic_image]
    bufferOffset = sensor_msgs.msg.Image.serialize(obj.panoramic_image, buffer, bufferOffset);
    // Serialize message field [panoramic_cloud]
    bufferOffset = sensor_msgs.msg.PointCloud2.serialize(obj.panoramic_cloud, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetPanoramicResponse
    let len;
    let data = new GetPanoramicResponse(null);
    // Deserialize message field [panoramic_image]
    data.panoramic_image = sensor_msgs.msg.Image.deserialize(buffer, bufferOffset);
    // Deserialize message field [panoramic_cloud]
    data.panoramic_cloud = sensor_msgs.msg.PointCloud2.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += sensor_msgs.msg.Image.getMessageSize(object.panoramic_image);
    length += sensor_msgs.msg.PointCloud2.getMessageSize(object.panoramic_cloud);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vision_msgs/GetPanoramicResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bef8c4ceb9df687b141c7c27121aa80e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    sensor_msgs/Image        panoramic_image
    sensor_msgs/PointCloud2  panoramic_cloud
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetPanoramicResponse(null);
    if (msg.panoramic_image !== undefined) {
      resolved.panoramic_image = sensor_msgs.msg.Image.Resolve(msg.panoramic_image)
    }
    else {
      resolved.panoramic_image = new sensor_msgs.msg.Image()
    }

    if (msg.panoramic_cloud !== undefined) {
      resolved.panoramic_cloud = sensor_msgs.msg.PointCloud2.Resolve(msg.panoramic_cloud)
    }
    else {
      resolved.panoramic_cloud = new sensor_msgs.msg.PointCloud2()
    }

    return resolved;
    }
};

module.exports = {
  Request: GetPanoramicRequest,
  Response: GetPanoramicResponse,
  md5sum() { return '7803f004018fa919db3f773819997d5d'; },
  datatype() { return 'vision_msgs/GetPanoramic'; }
};
