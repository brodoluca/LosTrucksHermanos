// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from message:msg/Message.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE__MSG__DETAIL__MESSAGE__BUILDER_HPP_
#define MESSAGE__MSG__DETAIL__MESSAGE__BUILDER_HPP_

#include "message/msg/detail/message__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace message
{

namespace msg
{

namespace builder
{

class Init_Message_event
{
public:
  explicit Init_Message_event(::message::msg::Message & msg)
  : msg_(msg)
  {}
  ::message::msg::Message event(::message::msg::Message::_event_type arg)
  {
    msg_.event = std::move(arg);
    return std::move(msg_);
  }

private:
  ::message::msg::Message msg_;
};

class Init_Message_body
{
public:
  explicit Init_Message_body(::message::msg::Message & msg)
  : msg_(msg)
  {}
  Init_Message_event body(::message::msg::Message::_body_type arg)
  {
    msg_.body = std::move(arg);
    return Init_Message_event(msg_);
  }

private:
  ::message::msg::Message msg_;
};

class Init_Message_receiver_id
{
public:
  explicit Init_Message_receiver_id(::message::msg::Message & msg)
  : msg_(msg)
  {}
  Init_Message_body receiver_id(::message::msg::Message::_receiver_id_type arg)
  {
    msg_.receiver_id = std::move(arg);
    return Init_Message_body(msg_);
  }

private:
  ::message::msg::Message msg_;
};

class Init_Message_sender_id
{
public:
  explicit Init_Message_sender_id(::message::msg::Message & msg)
  : msg_(msg)
  {}
  Init_Message_receiver_id sender_id(::message::msg::Message::_sender_id_type arg)
  {
    msg_.sender_id = std::move(arg);
    return Init_Message_receiver_id(msg_);
  }

private:
  ::message::msg::Message msg_;
};

class Init_Message_receiver_position
{
public:
  explicit Init_Message_receiver_position(::message::msg::Message & msg)
  : msg_(msg)
  {}
  Init_Message_sender_id receiver_position(::message::msg::Message::_receiver_position_type arg)
  {
    msg_.receiver_position = std::move(arg);
    return Init_Message_sender_id(msg_);
  }

private:
  ::message::msg::Message msg_;
};

class Init_Message_sender_position
{
public:
  Init_Message_sender_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Message_receiver_position sender_position(::message::msg::Message::_sender_position_type arg)
  {
    msg_.sender_position = std::move(arg);
    return Init_Message_receiver_position(msg_);
  }

private:
  ::message::msg::Message msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::message::msg::Message>()
{
  return message::msg::builder::Init_Message_sender_position();
}

}  // namespace message

#endif  // MESSAGE__MSG__DETAIL__MESSAGE__BUILDER_HPP_
