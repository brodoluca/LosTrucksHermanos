# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_truck_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED truck_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(truck_FOUND FALSE)
  elseif(NOT truck_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(truck_FOUND FALSE)
  endif()
  return()
endif()
set(_truck_CONFIG_INCLUDED TRUE)

# output package information
if(NOT truck_FIND_QUIETLY)
  message(STATUS "Found truck: 0.0.0 (${truck_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'truck' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${truck_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(truck_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${truck_DIR}/${_extra}")
endforeach()
