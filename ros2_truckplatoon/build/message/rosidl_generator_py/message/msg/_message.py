# generated from rosidl_generator_py/resource/_idl.py.em
# with input from message:msg/Message.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Message(type):
    """Metaclass of message 'Message'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('message')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'message.msg.Message')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__message
            cls._TYPE_SUPPORT = module.type_support_msg__msg__message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__message

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Message(metaclass=Metaclass_Message):
    """Message class 'Message'."""

    __slots__ = [
        '_sender_position',
        '_receiver_position',
        '_sender_id',
        '_receiver_id',
        '_body',
        '_event',
    ]

    _fields_and_field_types = {
        'sender_position': 'int16',
        'receiver_position': 'int16',
        'sender_id': 'int16',
        'receiver_id': 'int16',
        'body': 'string',
        'event': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.sender_position = kwargs.get('sender_position', int())
        self.receiver_position = kwargs.get('receiver_position', int())
        self.sender_id = kwargs.get('sender_id', int())
        self.receiver_id = kwargs.get('receiver_id', int())
        self.body = kwargs.get('body', str())
        self.event = kwargs.get('event', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.sender_position != other.sender_position:
            return False
        if self.receiver_position != other.receiver_position:
            return False
        if self.sender_id != other.sender_id:
            return False
        if self.receiver_id != other.receiver_id:
            return False
        if self.body != other.body:
            return False
        if self.event != other.event:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def sender_position(self):
        """Message field 'sender_position'."""
        return self._sender_position

    @sender_position.setter
    def sender_position(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sender_position' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'sender_position' field must be an integer in [-32768, 32767]"
        self._sender_position = value

    @property
    def receiver_position(self):
        """Message field 'receiver_position'."""
        return self._receiver_position

    @receiver_position.setter
    def receiver_position(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'receiver_position' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'receiver_position' field must be an integer in [-32768, 32767]"
        self._receiver_position = value

    @property
    def sender_id(self):
        """Message field 'sender_id'."""
        return self._sender_id

    @sender_id.setter
    def sender_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sender_id' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'sender_id' field must be an integer in [-32768, 32767]"
        self._sender_id = value

    @property
    def receiver_id(self):
        """Message field 'receiver_id'."""
        return self._receiver_id

    @receiver_id.setter
    def receiver_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'receiver_id' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'receiver_id' field must be an integer in [-32768, 32767]"
        self._receiver_id = value

    @property
    def body(self):
        """Message field 'body'."""
        return self._body

    @body.setter
    def body(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'body' field must be of type 'str'"
        self._body = value

    @property
    def event(self):
        """Message field 'event'."""
        return self._event

    @event.setter
    def event(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'event' field must be of type 'str'"
        self._event = value
