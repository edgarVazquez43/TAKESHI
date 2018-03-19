// Generated by gencpp from file knowledge_msgs/AddUpdateKnownLoc.msg
// DO NOT EDIT!


#ifndef KNOWLEDGE_MSGS_MESSAGE_ADDUPDATEKNOWNLOC_H
#define KNOWLEDGE_MSGS_MESSAGE_ADDUPDATEKNOWNLOC_H

#include <ros/service_traits.h>


#include <knowledge_msgs/AddUpdateKnownLocRequest.h>
#include <knowledge_msgs/AddUpdateKnownLocResponse.h>


namespace knowledge_msgs
{

struct AddUpdateKnownLoc
{

typedef AddUpdateKnownLocRequest Request;
typedef AddUpdateKnownLocResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct AddUpdateKnownLoc
} // namespace knowledge_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::knowledge_msgs::AddUpdateKnownLoc > {
  static const char* value()
  {
    return "c8eea2400325e7fa5b296976b0201acc";
  }

  static const char* value(const ::knowledge_msgs::AddUpdateKnownLoc&) { return value(); }
};

template<>
struct DataType< ::knowledge_msgs::AddUpdateKnownLoc > {
  static const char* value()
  {
    return "knowledge_msgs/AddUpdateKnownLoc";
  }

  static const char* value(const ::knowledge_msgs::AddUpdateKnownLoc&) { return value(); }
};


// service_traits::MD5Sum< ::knowledge_msgs::AddUpdateKnownLocRequest> should match 
// service_traits::MD5Sum< ::knowledge_msgs::AddUpdateKnownLoc > 
template<>
struct MD5Sum< ::knowledge_msgs::AddUpdateKnownLocRequest>
{
  static const char* value()
  {
    return MD5Sum< ::knowledge_msgs::AddUpdateKnownLoc >::value();
  }
  static const char* value(const ::knowledge_msgs::AddUpdateKnownLocRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::knowledge_msgs::AddUpdateKnownLocRequest> should match 
// service_traits::DataType< ::knowledge_msgs::AddUpdateKnownLoc > 
template<>
struct DataType< ::knowledge_msgs::AddUpdateKnownLocRequest>
{
  static const char* value()
  {
    return DataType< ::knowledge_msgs::AddUpdateKnownLoc >::value();
  }
  static const char* value(const ::knowledge_msgs::AddUpdateKnownLocRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::knowledge_msgs::AddUpdateKnownLocResponse> should match 
// service_traits::MD5Sum< ::knowledge_msgs::AddUpdateKnownLoc > 
template<>
struct MD5Sum< ::knowledge_msgs::AddUpdateKnownLocResponse>
{
  static const char* value()
  {
    return MD5Sum< ::knowledge_msgs::AddUpdateKnownLoc >::value();
  }
  static const char* value(const ::knowledge_msgs::AddUpdateKnownLocResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::knowledge_msgs::AddUpdateKnownLocResponse> should match 
// service_traits::DataType< ::knowledge_msgs::AddUpdateKnownLoc > 
template<>
struct DataType< ::knowledge_msgs::AddUpdateKnownLocResponse>
{
  static const char* value()
  {
    return DataType< ::knowledge_msgs::AddUpdateKnownLoc >::value();
  }
  static const char* value(const ::knowledge_msgs::AddUpdateKnownLocResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // KNOWLEDGE_MSGS_MESSAGE_ADDUPDATEKNOWNLOC_H