// Generated by gencpp from file manip_msgs/DirectKinematics.msg
// DO NOT EDIT!


#ifndef MANIP_MSGS_MESSAGE_DIRECTKINEMATICS_H
#define MANIP_MSGS_MESSAGE_DIRECTKINEMATICS_H

#include <ros/service_traits.h>


#include <manip_msgs/DirectKinematicsRequest.h>
#include <manip_msgs/DirectKinematicsResponse.h>


namespace manip_msgs
{

struct DirectKinematics
{

typedef DirectKinematicsRequest Request;
typedef DirectKinematicsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct DirectKinematics
} // namespace manip_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::manip_msgs::DirectKinematics > {
  static const char* value()
  {
    return "6d3e3a04e953772f57d61cd8e812ab2e";
  }

  static const char* value(const ::manip_msgs::DirectKinematics&) { return value(); }
};

template<>
struct DataType< ::manip_msgs::DirectKinematics > {
  static const char* value()
  {
    return "manip_msgs/DirectKinematics";
  }

  static const char* value(const ::manip_msgs::DirectKinematics&) { return value(); }
};


// service_traits::MD5Sum< ::manip_msgs::DirectKinematicsRequest> should match 
// service_traits::MD5Sum< ::manip_msgs::DirectKinematics > 
template<>
struct MD5Sum< ::manip_msgs::DirectKinematicsRequest>
{
  static const char* value()
  {
    return MD5Sum< ::manip_msgs::DirectKinematics >::value();
  }
  static const char* value(const ::manip_msgs::DirectKinematicsRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::manip_msgs::DirectKinematicsRequest> should match 
// service_traits::DataType< ::manip_msgs::DirectKinematics > 
template<>
struct DataType< ::manip_msgs::DirectKinematicsRequest>
{
  static const char* value()
  {
    return DataType< ::manip_msgs::DirectKinematics >::value();
  }
  static const char* value(const ::manip_msgs::DirectKinematicsRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::manip_msgs::DirectKinematicsResponse> should match 
// service_traits::MD5Sum< ::manip_msgs::DirectKinematics > 
template<>
struct MD5Sum< ::manip_msgs::DirectKinematicsResponse>
{
  static const char* value()
  {
    return MD5Sum< ::manip_msgs::DirectKinematics >::value();
  }
  static const char* value(const ::manip_msgs::DirectKinematicsResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::manip_msgs::DirectKinematicsResponse> should match 
// service_traits::DataType< ::manip_msgs::DirectKinematics > 
template<>
struct DataType< ::manip_msgs::DirectKinematicsResponse>
{
  static const char* value()
  {
    return DataType< ::manip_msgs::DirectKinematics >::value();
  }
  static const char* value(const ::manip_msgs::DirectKinematicsResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MANIP_MSGS_MESSAGE_DIRECTKINEMATICS_H