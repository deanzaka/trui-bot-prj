// Generated by gencpp from file mavros/ParamGetRequest.msg
// DO NOT EDIT!


#ifndef MAVROS_MESSAGE_PARAMGETREQUEST_H
#define MAVROS_MESSAGE_PARAMGETREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mavros
{
template <class ContainerAllocator>
struct ParamGetRequest_
{
  typedef ParamGetRequest_<ContainerAllocator> Type;

  ParamGetRequest_()
    : param_id()  {
    }
  ParamGetRequest_(const ContainerAllocator& _alloc)
    : param_id(_alloc)  {
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _param_id_type;
  _param_id_type param_id;




  typedef boost::shared_ptr< ::mavros::ParamGetRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros::ParamGetRequest_<ContainerAllocator> const> ConstPtr;

}; // struct ParamGetRequest_

typedef ::mavros::ParamGetRequest_<std::allocator<void> > ParamGetRequest;

typedef boost::shared_ptr< ::mavros::ParamGetRequest > ParamGetRequestPtr;
typedef boost::shared_ptr< ::mavros::ParamGetRequest const> ParamGetRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros::ParamGetRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros::ParamGetRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mavros

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'mavros': ['/home/deanzaka/Github/trui-bot-prj/controller/src/mavros/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/indigo/share/sensor_msgs/cmake/../msg'], 'diagnostic_msgs': ['/opt/ros/indigo/share/diagnostic_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mavros::ParamGetRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros::ParamGetRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros::ParamGetRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros::ParamGetRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros::ParamGetRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros::ParamGetRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros::ParamGetRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a0c8304d59f465712790120c3fc4b7d0";
  }

  static const char* value(const ::mavros::ParamGetRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa0c8304d59f46571ULL;
  static const uint64_t static_value2 = 0x2790120c3fc4b7d0ULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros::ParamGetRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros/ParamGetRequest";
  }

  static const char* value(const ::mavros::ParamGetRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros::ParamGetRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
\n\
\n\
\n\
\n\
\n\
\n\
\n\
string param_id\n\
";
  }

  static const char* value(const ::mavros::ParamGetRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros::ParamGetRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.param_id);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct ParamGetRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros::ParamGetRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros::ParamGetRequest_<ContainerAllocator>& v)
  {
    s << indent << "param_id: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.param_id);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MESSAGE_PARAMGETREQUEST_H
