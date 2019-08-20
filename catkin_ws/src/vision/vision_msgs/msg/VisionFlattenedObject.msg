std_msgs/Header header
string id                                  # name of identifying the object (milk, orange juice, etc)
string category                            # object type (drink, snack, etc)
#sensor_msgs/Image image	           # image in rgb of object;
#sensor_msgs/PointCloud2 point_cloud       # Point cloud (probably, colored)
geometry_msgs/Vector3 size                 # Size in meters: size in x, y and z
geometry_msgs/Vector3[] eigen_vectors      # eigen vectors of the object from 3D informaction
geometry_msgs/Vector3 eigen_values	   # eigen values asociated with eigen_vector
int32 xi		          	   # top left x bounding box in image
int32 yi				   # top left y bounding box in image
int32 widthi                               # top widht bounding box in image
int32 heighti                              # top height bounding box in image
geometry_msgs/Point  nearest_point         # The nearespoint of the object
geometry_msgs/Point  center_point          # The nearespoint of the object
