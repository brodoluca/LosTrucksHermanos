// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from message:msg/Message.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE__MSG__DETAIL__MESSAGE__STRUCT_H_
#define MESSAGE__MSG__DETAIL__MESSAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'body'
// Member 'event'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/Message in the package message.
typedef struct message__msg__Message
{
  int16_t sender_position;
  int16_t receiver_position;
  int16_t sender_id;
  int16_t receiver_id;
  rosidl_runtime_c__String body;
  rosidl_runtime_c__String event;
} message__msg__Message;

// Struct for a sequence of message__msg__Message.
typedef struct message__msg__Message__Sequence
{
  message__msg__Message * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} message__msg__Message__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGE__MSG__DETAIL__MESSAGE__STRUCT_H_
