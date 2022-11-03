// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from message:msg/Message.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "message/msg/detail/message__struct.h"
#include "message/msg/detail/message__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool message__msg__message__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[29];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("message.msg._message.Message", full_classname_dest, 28) == 0);
  }
  message__msg__Message * ros_message = _ros_message;
  {  // sender_position
    PyObject * field = PyObject_GetAttrString(_pymsg, "sender_position");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->sender_position = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // receiver_position
    PyObject * field = PyObject_GetAttrString(_pymsg, "receiver_position");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->receiver_position = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // sender_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "sender_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->sender_id = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // receiver_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "receiver_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->receiver_id = (int16_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // body
    PyObject * field = PyObject_GetAttrString(_pymsg, "body");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->body, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // event
    PyObject * field = PyObject_GetAttrString(_pymsg, "event");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->event, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * message__msg__message__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Message */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("message.msg._message");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Message");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  message__msg__Message * ros_message = (message__msg__Message *)raw_ros_message;
  {  // sender_position
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->sender_position);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sender_position", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // receiver_position
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->receiver_position);
    {
      int rc = PyObject_SetAttrString(_pymessage, "receiver_position", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sender_id
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->sender_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sender_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // receiver_id
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->receiver_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "receiver_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // body
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->body.data,
      strlen(ros_message->body.data),
      "strict");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "body", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // event
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->event.data,
      strlen(ros_message->event.data),
      "strict");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "event", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
