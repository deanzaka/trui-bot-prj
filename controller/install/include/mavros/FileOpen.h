// Generated by gencpp from file mavros/FileOpen.msg
// DO NOT EDIT!


#ifndef MAVROS_MESSAGE_FILEOPEN_H
#define MAVROS_MESSAGE_FILEOPEN_H

#include <ros/service_traits.h>


#include <mavros/FileOpenRequest.h>
#include <mavros/FileOpenResponse.h>


namespace mavros
{

struct FileOpen
{

typedef FileOpenRequest Request;
typedef FileOpenResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct FileOpen
} // namespace mavros


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::mavros::FileOpen > {
  static const char* value()
  {
    return "99a3f49cc67b91477cf49ff15c42af0e";
  }

  static const char* value(const ::mavros::FileOpen&) { return value(); }
};

template<>
struct DataType< ::mavros::FileOpen > {
  static const char* value()
  {
    return "mavros/FileOpen";
  }

  static const char* value(const ::mavros::FileOpen&) { return value(); }
};


// service_traits::MD5Sum< ::mavros::FileOpenRequest> should match 
// service_traits::MD5Sum< ::mavros::FileOpen > 
template<>
struct MD5Sum< ::mavros::FileOpenRequest>
{
  static const char* value()
  {
    return MD5Sum< ::mavros::FileOpen >::value();
  }
  static const char* value(const ::mavros::FileOpenRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::mavros::FileOpenRequest> should match 
// service_traits::DataType< ::mavros::FileOpen > 
template<>
struct DataType< ::mavros::FileOpenRequest>
{
  static const char* value()
  {
    return DataType< ::mavros::FileOpen >::value();
  }
  static const char* value(const ::mavros::FileOpenRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::mavros::FileOpenResponse> should match 
// service_traits::MD5Sum< ::mavros::FileOpen > 
template<>
struct MD5Sum< ::mavros::FileOpenResponse>
{
  static const char* value()
  {
    return MD5Sum< ::mavros::FileOpen >::value();
  }
  static const char* value(const ::mavros::FileOpenResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::mavros::FileOpenResponse> should match 
// service_traits::DataType< ::mavros::FileOpen > 
template<>
struct DataType< ::mavros::FileOpenResponse>
{
  static const char* value()
  {
    return DataType< ::mavros::FileOpen >::value();
  }
  static const char* value(const ::mavros::FileOpenResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MAVROS_MESSAGE_FILEOPEN_H
