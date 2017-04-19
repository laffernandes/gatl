# @PROJECT_NAME@Config.cmake - @PROJECT_NAME@ CMake configuration file for external projects.
#
# This file is configured by @PROJECT_NAME@ and used by the @PROJECT_NAME@Use.cmake module
# to load @PROJECT_NAME@'s settings for an external project.

# The directory of @PROJECT_NAME@Config.cmake is, by definition, @PROJECT_NAME@_DIR.
GET_FILENAME_COMPONENT(this_dir "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(@PROJECT_NAME@_ROOT_DIR "${this_dir}/@CV_CONFIG_TO_ROOT@" ABSOLUTE)


# CMake files required to build client applications that use @PROJECT_NAME@.
SET(@PROJECT_NAME@_BUILD_SETTINGS_FILE "@CV_BUILD_SETTINGS_FILE@")

SET(@PROJECT_NAME@_LIBRARY_NAMES @CV_LIBRARY_NAMES@)
FOREACH(@PROJECT_NAME@_LIBRARY_NAME ${@PROJECT_NAME@_LIBRARY_NAMES})
  SET(${@PROJECT_NAME@_LIBRARY_NAME}_USE_FILE "@CV_USE_FILES_PATH@/${@PROJECT_NAME@_LIBRARY_NAME}Use.cmake")
ENDFOREACH()


# The @PROJECT_NAME@ directories.
SET(@PROJECT_NAME@_INCLUDE_DIRS "@CV_INCLUDE_DIRS@")
SET(@PROJECT_NAME@_LIBRARY_DIRS "@CV_LIBRARY_DIRS@")


# The extra @PROJECT_NAME@ directories.
SET(@PROJECT_NAME@_EXTRA_INCLUDE_DIRS "@CV_EXTRA_INCLUDE_DIRS@")
SET(@PROJECT_NAME@_EXTRA_LIBRARY_DIRS "@CV_EXTRA_LIBRARY_DIRS@")


# The @PROJECT_NAME@ libraries.
SET(@PROJECT_NAME@_LIBRARY_NAMES @CV_LIBRARY_NAMES@)
FOREACH(@PROJECT_NAME@_LIBRARY_NAME ${@PROJECT_NAME@_LIBRARY_NAMES})
  SET(${@PROJECT_NAME@_LIBRARY_NAME}_LIBRARIES "${@PROJECT_NAME@_LIBRARY_NAME}")
ENDFOREACH()


# The @PROJECT_NAME@ library dependencies.
IF(NOT @PROJECT_NAME@_NO_LIBRARY_DEPENDS)
  INCLUDE("@CV_LIBRARY_DEPENDS_FILE@")
ENDIF()