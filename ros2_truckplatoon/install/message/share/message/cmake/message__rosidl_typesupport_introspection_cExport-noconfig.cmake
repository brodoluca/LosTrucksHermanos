#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "message::message__rosidl_typesupport_introspection_c" for configuration ""
set_property(TARGET message::message__rosidl_typesupport_introspection_c APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(message::message__rosidl_typesupport_introspection_c PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmessage__rosidl_typesupport_introspection_c.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/libmessage__rosidl_typesupport_introspection_c.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS message::message__rosidl_typesupport_introspection_c )
list(APPEND _IMPORT_CHECK_FILES_FOR_message::message__rosidl_typesupport_introspection_c "${_IMPORT_PREFIX}/lib/libmessage__rosidl_typesupport_introspection_c.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
