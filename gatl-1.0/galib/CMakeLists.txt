PROJECT(GALib)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


# Make some changes in CMake properties.
SET(CMAKE_NOT_USING_CONFIG_FLAGS ON CACHE BOOL "" FORCE)

IF(NOT ${PROJECT_NAME}_DONT_OVERRIDE_CMAKE_FLAGS)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)

  IF(MSVC)
  
    SET(ORIGINAL_ENTRY ${CMAKE_C_FLAGS_RELEASE})
    SET(CMAKE_C_FLAGS_RELEASE "${ORIGINAL_ENTRY} /bigobj /D_SECURE_SCL=0" CACHE STRING "" FORCE)

    SET(ORIGINAL_ENTRY ${CMAKE_CXX_FLAGS_RELEASE})
    SET(CMAKE_CXX_FLAGS_RELEASE "${ORIGINAL_ENTRY} /bigobj /D_SECURE_SCL=0" CACHE STRING "" FORCE)

    SET(ORIGINAL_ENTRY ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${ORIGINAL_ENTRY} /OPT:REF /OPT:ICF" CACHE STRING "" FORCE)

  ENDIF()

  SET(${PROJECT_NAME}_DONT_OVERRIDE_CMAKE_FLAGS "ON" CACHE BOOL "" FORCE)
ENDIF()


# Find required packages.
FIND_PACKAGE(BToolsLib REQUIRED PATHS "../btoolslib/build")
INCLUDE(${BToolsLib_USE_FILE})

FIND_PACKAGE(LALib REQUIRED PATHS "../lalib/build")
INCLUDE(${LALib_USE_FILE})

FIND_PACKAGE(OpenMP REQUIRED)


# Set (local) include directories.
INCLUDE_DIRECTORIES("include")


# Set source groups.
SET(INCLUDE_PATHS
  "/"
  "/ga"
  "/ga/_private"
  "/ga/_private/black_magic"
  "/ga/clifford"
  "/ga/clifford/_private"
  "/ga/conformal"
  "/ga/conformal/_private"
  "/ga/euclidean"
  "/ga/euclidean/_private"
  "/ga/homogeneous"
  "/ga/homogeneous/_private"
  "/ga/quadratic"
  "/ga/quadratic/_private")
  
FOREACH(INCLUDE_PATH ${INCLUDE_PATHS})
  FILE(GLOB CURRENT_HEADER_FILES include${INCLUDE_PATH}/*.h)
  STRING(REPLACE "/" "\\\\" CURRENT_HEADER_GROUP ${INCLUDE_PATH})
  SOURCE_GROUP("Header Files${CURRENT_HEADER_GROUP}" FILES ${CURRENT_HEADER_FILES})
ENDFOREACH()


# Setup main library.
LIST(REMOVE_AT INCLUDE_PATHS 0)
FOREACH(INCLUDE_PATH ${INCLUDE_PATHS})
  FILE(GLOB CURRENT_HEADER_FILES include${INCLUDE_PATH}/*.h)
  LIST(APPEND HEADER_FILES ${CURRENT_HEADER_FILES})
ENDFOREACH()

ADD_LIBRARY(${PROJECT_NAME} "source/validate.cpp" ${HEADER_FILES} "include/ga.h")
SET(${PROJECT_NAME}_IS_TEMPLATE_LIBRARY TRUE)
LIST(APPEND LIBRARY_NAMES ${PROJECT_NAME})


# Setup specialized libraries.
LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA2eLib)
SET(GA2eLib_LIBRARY_SOURCE_FILES "source/ga2e.cpp" "source/ga2e_validate.cpp")
SET(GA2eLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_euclidean_operations.h" "include/ga2e.h")

LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA3eLib)
SET(GA3eLib_LIBRARY_SOURCE_FILES "source/ga3e.cpp" "source/ga3e_validate.cpp")
SET(GA3eLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_euclidean_operations.h" "include/ga3e.h")

LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA4eLib)
SET(GA4eLib_LIBRARY_SOURCE_FILES "source/ga4e.cpp" "source/ga4e_validate.cpp")
SET(GA4eLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_euclidean_operations.h" "include/ga4e.h")

LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA2hLib)
SET(GA2hLib_LIBRARY_SOURCE_FILES "source/ga2h.cpp" "source/ga2h_validate.cpp")
SET(GA2hLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_homogeneous_operations.h" "include/ga2h.h")

LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA3hLib)
SET(GA3hLib_LIBRARY_SOURCE_FILES "source/ga3h.cpp" "source/ga3h_validate.cpp")
SET(GA3hLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_homogeneous_operations.h" "include/ga3h.h")

LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA2cLib)
SET(GA2cLib_LIBRARY_SOURCE_FILES "source/ga2c.cpp" "source/ga2c_validate.cpp")
SET(GA2cLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_conformal_operations.h" "include/ga2c.h")

LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA2cvLib)
SET(GA2cvLib_LIBRARY_SOURCE_FILES "source/ga2cv.cpp" "source/ga2cv_validate.cpp")
SET(GA2cvLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_conformal_operations.h" "include/ga2cv.h")

LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA3cLib)
SET(GA3cLib_LIBRARY_SOURCE_FILES "source/ga3c.cpp" "source/ga3c_validate.cpp")
SET(GA3cLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_conformal_operations.h" "include/ga3c.h")

LIST(APPEND SPECIALIZED_LIBRARY_NAMES GA2qLib)
SET(GA2qLib_LIBRARY_SOURCE_FILES "source/ga2q.cpp" "source/ga2q_validate.cpp")
SET(GA2qLib_LIBRARY_HEADER_FILES "include/ga.h" "include/ga_operations.h" "include/ga_quadratic_operations.h" "include/ga2q.h")

FOREACH(SPECIALIZED_LIBRARY_NAME ${SPECIALIZED_LIBRARY_NAMES})
  ADD_LIBRARY(${SPECIALIZED_LIBRARY_NAME} ${${SPECIALIZED_LIBRARY_NAME}_LIBRARY_SOURCE_FILES} ${HEADER_FILES} ${${SPECIALIZED_LIBRARY_NAME}_LIBRARY_HEADER_FILES})
  SET(${SPECIALIZED_LIBRARY_NAME}_IS_TEMPLATE_LIBRARY FALSE)
ENDFOREACH()
LIST(APPEND LIBRARY_NAMES ${SPECIALIZED_LIBRARY_NAMES})


# Help outside projects.
INCLUDE("${${PROJECT_NAME}_SOURCE_DIR}/../CMakeTemplateInstall.cmake")
INCLUDE("${${PROJECT_NAME}_SOURCE_DIR}/../CMakeTemplateExport.cmake")