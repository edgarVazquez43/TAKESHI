#include <iostream>
#include <vector>
#include <cmath>
#include "nav_msgs/Path.h"
#include "tf/transform_broadcaster.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Float32MultiArray.h"


class InverseKinematics
{
public:
  static bool GetInverseKinematics(float x, float y, float z, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction);
  static bool GetInverseKinematics(float x, float y, float z, float roll, float pitch, float yaw, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction);
  static bool GetInverseKinematics(std::vector<float>& cartesian, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction);
  static bool GetDirectKinematics(std::vector<float>& articular, std::vector<float>& cartesian);
};
