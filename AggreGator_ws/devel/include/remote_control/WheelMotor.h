/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by genmsg_cpp from file /home/fnivek/Code/NASABotics/NASAboticsCode/AggreGator_ws/src/remote_control/msg/WheelMotor.msg
 *
 */


#ifndef REMOTE_CONTROL_MESSAGE_WHEELMOTOR_H
#define REMOTE_CONTROL_MESSAGE_WHEELMOTOR_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace remote_control
{
template <class ContainerAllocator>
struct WheelMotor_
{
  typedef WheelMotor_<ContainerAllocator> Type;

  WheelMotor_()
    : LF_motorVal(0)
    , RF_motorVal(0)
    , RR_motorVal(0)
    , LR_motorVal(0)  {
    }
  WheelMotor_(const ContainerAllocator& _alloc)
    : LF_motorVal(0)
    , RF_motorVal(0)
    , RR_motorVal(0)
    , LR_motorVal(0)  {
    }



   typedef int16_t _LF_motorVal_type;
  _LF_motorVal_type LF_motorVal;

   typedef int16_t _RF_motorVal_type;
  _RF_motorVal_type RF_motorVal;

   typedef int16_t _RR_motorVal_type;
  _RR_motorVal_type RR_motorVal;

   typedef int16_t _LR_motorVal_type;
  _LR_motorVal_type LR_motorVal;




  typedef boost::shared_ptr< ::remote_control::WheelMotor_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::remote_control::WheelMotor_<ContainerAllocator> const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;

}; // struct WheelMotor_

typedef ::remote_control::WheelMotor_<std::allocator<void> > WheelMotor;

typedef boost::shared_ptr< ::remote_control::WheelMotor > WheelMotorPtr;
typedef boost::shared_ptr< ::remote_control::WheelMotor const> WheelMotorConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::remote_control::WheelMotor_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::remote_control::WheelMotor_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace remote_control

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'remote_control': ['/home/fnivek/Code/NASABotics/NASAboticsCode/AggreGator_ws/src/remote_control/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::remote_control::WheelMotor_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::remote_control::WheelMotor_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::remote_control::WheelMotor_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::remote_control::WheelMotor_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::remote_control::WheelMotor_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::remote_control::WheelMotor_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::remote_control::WheelMotor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f0f17242b728bc2f9b92df609716f415";
  }

  static const char* value(const ::remote_control::WheelMotor_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf0f17242b728bc2fULL;
  static const uint64_t static_value2 = 0x9b92df609716f415ULL;
};

template<class ContainerAllocator>
struct DataType< ::remote_control::WheelMotor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "remote_control/WheelMotor";
  }

  static const char* value(const ::remote_control::WheelMotor_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::remote_control::WheelMotor_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int16 LF_motorVal\n\
int16 RF_motorVal\n\
int16 RR_motorVal\n\
int16 LR_motorVal\n\
";
  }

  static const char* value(const ::remote_control::WheelMotor_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::remote_control::WheelMotor_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.LF_motorVal);
      stream.next(m.RF_motorVal);
      stream.next(m.RR_motorVal);
      stream.next(m.LR_motorVal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct WheelMotor_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::remote_control::WheelMotor_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::remote_control::WheelMotor_<ContainerAllocator>& v)
  {
    s << indent << "LF_motorVal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.LF_motorVal);
    s << indent << "RF_motorVal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.RF_motorVal);
    s << indent << "RR_motorVal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.RR_motorVal);
    s << indent << "LR_motorVal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.LR_motorVal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // REMOTE_CONTROL_MESSAGE_WHEELMOTOR_H
