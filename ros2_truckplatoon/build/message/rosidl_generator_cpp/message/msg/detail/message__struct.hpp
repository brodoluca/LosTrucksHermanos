// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from message:msg/Message.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE__MSG__DETAIL__MESSAGE__STRUCT_HPP_
#define MESSAGE__MSG__DETAIL__MESSAGE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__message__msg__Message __attribute__((deprecated))
#else
# define DEPRECATED__message__msg__Message __declspec(deprecated)
#endif

namespace message
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Message_
{
  using Type = Message_<ContainerAllocator>;

  explicit Message_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sender_position = 0;
      this->receiver_position = 0;
      this->sender_id = 0;
      this->receiver_id = 0;
      this->body = "";
      this->event = "";
    }
  }

  explicit Message_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : body(_alloc),
    event(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sender_position = 0;
      this->receiver_position = 0;
      this->sender_id = 0;
      this->receiver_id = 0;
      this->body = "";
      this->event = "";
    }
  }

  // field types and members
  using _sender_position_type =
    int16_t;
  _sender_position_type sender_position;
  using _receiver_position_type =
    int16_t;
  _receiver_position_type receiver_position;
  using _sender_id_type =
    int16_t;
  _sender_id_type sender_id;
  using _receiver_id_type =
    int16_t;
  _receiver_id_type receiver_id;
  using _body_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _body_type body;
  using _event_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _event_type event;

  // setters for named parameter idiom
  Type & set__sender_position(
    const int16_t & _arg)
  {
    this->sender_position = _arg;
    return *this;
  }
  Type & set__receiver_position(
    const int16_t & _arg)
  {
    this->receiver_position = _arg;
    return *this;
  }
  Type & set__sender_id(
    const int16_t & _arg)
  {
    this->sender_id = _arg;
    return *this;
  }
  Type & set__receiver_id(
    const int16_t & _arg)
  {
    this->receiver_id = _arg;
    return *this;
  }
  Type & set__body(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->body = _arg;
    return *this;
  }
  Type & set__event(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->event = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    message::msg::Message_<ContainerAllocator> *;
  using ConstRawPtr =
    const message::msg::Message_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<message::msg::Message_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<message::msg::Message_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      message::msg::Message_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<message::msg::Message_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      message::msg::Message_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<message::msg::Message_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<message::msg::Message_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<message::msg::Message_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__message__msg__Message
    std::shared_ptr<message::msg::Message_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__message__msg__Message
    std::shared_ptr<message::msg::Message_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Message_ & other) const
  {
    if (this->sender_position != other.sender_position) {
      return false;
    }
    if (this->receiver_position != other.receiver_position) {
      return false;
    }
    if (this->sender_id != other.sender_id) {
      return false;
    }
    if (this->receiver_id != other.receiver_id) {
      return false;
    }
    if (this->body != other.body) {
      return false;
    }
    if (this->event != other.event) {
      return false;
    }
    return true;
  }
  bool operator!=(const Message_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Message_

// alias to use template instance with default allocator
using Message =
  message::msg::Message_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace message

#endif  // MESSAGE__MSG__DETAIL__MESSAGE__STRUCT_HPP_
