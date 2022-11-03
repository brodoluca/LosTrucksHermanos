// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from message:msg/Message.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE__MSG__DETAIL__MESSAGE__TRAITS_HPP_
#define MESSAGE__MSG__DETAIL__MESSAGE__TRAITS_HPP_

#include "message/msg/detail/message__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<message::msg::Message>()
{
  return "message::msg::Message";
}

template<>
inline const char * name<message::msg::Message>()
{
  return "message/msg/Message";
}

template<>
struct has_fixed_size<message::msg::Message>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<message::msg::Message>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<message::msg::Message>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGE__MSG__DETAIL__MESSAGE__TRAITS_HPP_
