#include "InverseKinematics.h"

bool InverseKinematics::GetInverseKinematics(float x, float y, float z, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction)
{
  float torso_correction;
  float x_wc, y_wc, z_wc;     // Position of wrist center
  float x_wra, y_wra, z_wra;  // Goal pos respect arm
  float EE_Wc = 0.21;         // Const distance of End Efector to WristCenter
  float BL_BA = 0.12;         // Const distance of BaseLink to BaseArm  x-axis
  float roll, pitch, yaw;

  tf::Quaternion q;
  tf::Transform  Rwc_EE;   // Transform to Center Wrist to EndEffector
  tf::Vector3    wristPos(0.0, 0.0, 0.0);

  articular.resize(4);
  roll  = 0.0;
  pitch = 1.5707;
  yaw   = 0.0;
  base_correction.x = 0.0;


  ///////////////////////////////////////////
  //     Kinematic Decoupling              //
  //        roll, pitch, yaw
  q.setRPY(roll, pitch, yaw);    //Transfor in format roll, pitch, yaw.
  Rwc_EE.setIdentity();
  Rwc_EE.setRotation(q);

  wristPos[2] = EE_Wc;
  wristPos = Rwc_EE * wristPos;

  // This is the position of wrist center
  wristPos[0] = x - wristPos[0];
  wristPos[1] = y - wristPos[1];
  wristPos[2] = z - wristPos[2];

  x_wc = wristPos[0];
  y_wc = wristPos[1];
  z_wc = wristPos[2];

  std::cout << "Ik-Geometric->  EndEffector_pos: " << std::endl
	    << x << std::endl
	    << y << std::endl
	    << z << std::endl;

  std::cout << "Ik-Geometric->  wristCenter_pos: " << std::endl
	    << x_wc << std::endl
	    << y_wc << std::endl
	    << z_wc << std::endl
	    << std::endl;

  x_wra = x_wc - BL_BA;    // Goal pose respect arm on X-axis

  if(x_wra > 0.37)
  {
    if(x_wra - 0.37  > 0.20)
    {
      std::cout << "IK-Geometric-> This point is out of work space:" << std::endl;
      return false;
    }

    base_correction.x = x_wra - 0.37;
    x_wra = 0.365;
  }

  z_wra = sqrt( (0.37*0.37) - (x_wra*x_wra) );

  torso_correction = z_wc - z_wra - 0.31;
  std::cout << "Ik-Geometric-> TorsoCorrection:  " << torso_correction << std::endl;
  std::cout << "Ik-Geometric-> BaseCorrection[x]:  " << base_correction.x << std::endl;

  if(torso_correction < 0.0)
  {
    torso_correction = z_wc + z_wra - 0.33;

    articular[0] = atan2(-z_wra, x_wra) - 1.5707;
    articular[1] = 0.0;
    articular[2] = atan2(z_wra, x_wra);
    articular[3] = 0.0;
    torso = torso_correction;
  }
  else
  {
    articular[0] = atan2(z_wra, x_wra) - 1.5707;
    articular[1] = 0.0;
    articular[2] = -atan2(z_wra, x_wra);
    articular[3] = 0.0;
    torso = torso_correction;
  }

  std::cout << "Articular poses: " << std::endl;
  for (int i=0; i < articular.size() ; i++)
    std::cout << "   " << articular[i] << std::endl;

  torso = torso_correction;
  return true;
}


bool InverseKinematics::GetInverseKinematics(std::vector<float>& cartesian, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction)
{
  float torso_correction;
  float x_wc, y_wc, z_wc;
  float x_wra, y_wra, z_wra;
  float EE_Wc = 0.21;         // Const distance of End Efector to WristCenter
  float BL_BA = 0.12;         // Const distance of BaseLink to BaseArm  x-axis
  float x, y, z;
  float roll, pitch, yaw;

  tf::Quaternion q;
  tf::Transform  Rwc_EE;   // Transform to Center Wrist to EndEffector
  tf::Vector3    wristPos(0.0, 0.0, 0.0);


  articular.resize(4);
  x = cartesian[0];
  y = cartesian[1];
  z = cartesian[2];
  roll  = cartesian[3];
  pitch = cartesian[4];
  yaw   = cartesian[5];
  base_correction.x = 0.0;

  ///////////////////////////////////////////
  //     Kinematic Decoupling              //
  // Roll, pitch, yaw
  q.setRPY(roll, pitch, yaw);    //Transfor in format roll, pitch, yaw.
  Rwc_EE.setIdentity();
  Rwc_EE.setRotation(q);

  wristPos[2] = EE_Wc;
  wristPos = Rwc_EE * wristPos;

  // This is the position of wrist center
  wristPos[0] = x - wristPos[0];
  wristPos[1] = y - wristPos[1];
  wristPos[2] = z - wristPos[2];

  x_wc = wristPos[0];
  y_wc = wristPos[1];
  z_wc = wristPos[2];

  std::cout << "Ik-Geometric->  EndEffector_pos: " << std::endl
	    << x << std::endl
	    << y << std::endl
	    << z << std::endl;

  std::cout << "Ik-Geometric->  wristCenter_pos: " << std::endl
	    << x_wc << std::endl
	    << y_wc << std::endl
	    << z_wc << std::endl
	    << std::endl;

  x_wra = x_wc - BL_BA;

  // We are comparing
  if(x_wra > 0.37)
  {
    if(x_wra - 0.37  > 0.20)
    {
      std::cout << "IK-Geometric-> This point is out of work space:" << std::endl;
      return false;
    }

    base_correction.x = x_wra - 0.37;
    x_wra = 0.365;
  }

  z_wra = sqrt( (0.37*0.37) - (x_wra*x_wra) );

  torso_correction = z_wc - z_wra - 0.31;
  std::cout << "Ik-Geometric-> TorsoCorrection:  " << torso_correction << std::endl;
  std::cout << "Ik-Geometric-> BaseCorrection[x]:  " << base_correction.x << std::endl;


  if(torso_correction < 0.0)
  {
    torso_correction = z_wc + z_wra - 0.33;

    articular[0] = atan2(-z_wra, x_wra) - 1.5707;
    articular[1] = 0.0;
    articular[2] = atan2(z_wra, x_wra) + (1.5707 - pitch);
    articular[3] = 0.0 + yaw;
    torso = torso_correction;
  }
  else
  {
    articular[0] = atan2(z_wra, x_wra) - 1.5707;
    articular[1] = 0.0;
    articular[2] = -atan2(z_wra, x_wra)+ (1.5707 - pitch);
    articular[3] = 0.0 + yaw;
    torso = torso_correction;
  }

  std::cout << "Articular poses: " << std::endl;
  for (int i=0; i < articular.size() ; i++)
    std::cout << "   " << articular[i] << std::endl;

  torso = torso_correction;
  return true;
}

bool InverseKinematics::GetInverseKinematics(float x, float y, float z, float roll, float pitch, float yaw, std::vector<float>& articular, float& torso, geometry_msgs::Pose2D& base_correction)
{
  float torso_correction;
  float x_wc, y_wc, z_wc;
  float x_wra, y_wra, z_wra;
  float EE_Wc = 0.21;         // Const distance of End Efector to WristCenter
  float BL_BA = 0.12;         // Const distance of BaseLink to BaseArm  x-axis


  tf::Quaternion q;
  tf::Transform  Rwc_EE;   // Transform to Center Wrist to EndEffector
  tf::Vector3    wristPos(0.0, 0.0, 0.0);


  articular.resize(4);
  ///////////////////////////////////////////
  //     Kinematic Decoupling              //
  // Roll, pitch, yaw
  q.setRPY(roll, pitch, yaw);    //Transfor in format roll, pitch, yaw.
  Rwc_EE.setIdentity();
  Rwc_EE.setRotation(q);

  wristPos[2] = EE_Wc;
  wristPos = Rwc_EE * wristPos;

  // This is the position of wrist center
  wristPos[0] = x - wristPos[0];
  wristPos[1] = y - wristPos[1];
  wristPos[2] = z - wristPos[2];

  x_wc = wristPos[0];
  y_wc = wristPos[1];
  z_wc = wristPos[2];

  std::cout << "Ik-Geometric->  EndEffector_pos: " << std::endl
	    << x << std::endl
	    << y << std::endl
	    << z << std::endl;

  std::cout << "Ik-Geometric->  wristCenter_pos: " << std::endl
	    << x_wc << std::endl
	    << y_wc << std::endl
	    << z_wc << std::endl
	    << std::endl;

  x_wra = x_wc - BL_BA;

  //TODO remove non named constants
  if(x_wra > 0.37)
  {
    if(x_wra - 0.37  > 0.20)
    {
      std::cout << "IK-Geometric-> This point is out of work space:" << std::endl;
      return false;
    }

    base_correction.x = x_wra - 0.37;
    x_wra = 0.365;
  }

  z_wra = sqrt( (0.37*0.37) - (x_wra*x_wra) );

  torso_correction = z_wc - z_wra - 0.31;
  std::cout << "Ik-Geometric-> TorsoCorrection:  " << torso_correction << std::endl;
  std::cout << "Ik-Geometric-> BaseCorrection[x]:  " << base_correction.x << std::endl;

  if(torso_correction < 0.0)
  {
    torso_correction = z_wc + z_wra - 0.33;

    articular[0] = atan2(-z_wra, x_wra) - 1.5707;
    articular[1] = 0.0;
    articular[2] = atan2(z_wra, x_wra) + (1.5707 - pitch);
    articular[3] = 0.0 + yaw;
    torso = torso_correction;
  }
  else
  {
    articular[0] = atan2(z_wra, x_wra) - 1.5707;
    articular[1] = 0.0;
    articular[2] = -atan2(z_wra, x_wra)+ (1.5707 - pitch);
    articular[3] = 0.0 + yaw;
    torso = torso_correction;
  }

  std::cout << "Articular poses: " << std::endl;
  for (int i=0; i < articular.size() ; i++)
    std::cout << "   " << articular[i] << std::endl;

  torso = torso_correction;
  return true;
}


bool InverseKinematics::GetDirectKinematics(std::vector<float>& articular, std::vector<float>& cartesian)
{
    return true;
}
