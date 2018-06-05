# - Try to find the libcppunit libraries
# Once done this will define
#
# CPPUNIT_FOUND - system has libcppunit
# CPPUNIT_INCLUDE_DIRS - the libcppunit include directory
# CPPUNIT_LIBRARIES - libcppunit library
# CPPUNIT_ROOT - root directory to start from

include (MacroEnsureVersion)

if(CPPUNIT_INCLUDE_DIR)
    # in cache already
    set(CPPUNIT_FIND_QUIETLY TRUE)
endif()

find_package(PkgConfig QUIET)
pkg_check_modules(PC_CPPUNIT QUIET cppunit)

find_path(CPPUNIT_INCLUDE_DIR cppunit/TestRunner.h HINTS ${CPPUNIT_ROOT} ${PC_CPPUNIT_INCLUDEDIR} ${PC_CPPUNIT_INCLUDE_DIRS})
find_library(CPPUNIT_LIBRARY_RELEASE NAMES cppunit cppunit_dll HINTS ${CPPUNIT_ROOT} ${PC_CPPUNIT_LIBDIR} ${PC_CPPUNIT_LIBRARY_DIRS})
find_library(CPPUNIT_LIBRARY_DEBUG NAMES cppunitd cppunitd_dll HINTS ${CPPUNIT_ROOT} ${PC_CPPUNIT_LIBDIR} ${PC_CPPUNIT_LIBRARY_DIRS})

include(SelectLibraryConfigurations)
select_library_configurations(CPPUNIT)

if(CPPUNIT_INCLUDE_DIR AND EXISTS "${CPPUNIT_INCLUDE_DIR}/cppunit/Portability.h")
  file(STRINGS "${CPPUNIT_INCLUDE_DIR}/cppunit/Portability.h" PORTABILITY_H REGEX "^#define CPPUNIT_VERSION  \"[^\"]*\"$")
  string(REGEX REPLACE "^.*CPPUNIT_VERSION  \"([0-9]+).*$" "\\1" CPPUNIT_VERSION_MAJOR "${PORTABILITY_H}")
  string(REGEX REPLACE "^.*CPPUNIT_VERSION  \"[0-9]+\\.([0-9]+).*$" "\\1" CPPUNIT_VERSION_MINOR  "${PORTABILITY_H}")
  string(REGEX REPLACE "^.*CPPUNIT_VERSION  \"[0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" CPPUNIT_VERSION_PATCH "${PORTABILITY_H}")
  set(CPPUNIT_VERSION_STRING "${CPPUNIT_VERSION_MAJOR}.${CPPUNIT_VERSION_MINOR}.${CPPUNIT_VERSION_PATCH}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CppUnit
  REQUIRED_VARS CPPUNIT_INCLUDE_DIR CPPUNIT_LIBRARY
  VERSION_VAR CPPUNIT_VERSION_STRING
)

if(CPPUNIT_FOUND)
  set(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY})
  set(CPPUNIT_INCLUDE_DIRS ${CPPUNIT_INCLUDE_DIR})
  if(NOT TARGET CppUnit::CppUnit)
    add_library(CppUnit::CppUnit UNKNOWN IMPORTED)
    set_target_properties(CppUnit::CppUnit PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CPPUNIT_INCLUDE_DIRS}"
    )

    if(CPPUNIT_LIBRARY_RELEASE)
      set_property(TARGET CppUnit::CppUnit APPEND PROPERTY
        IMPORTED_CONFIGURATIONS RELEASE
      )
      set_target_properties(CppUnit::CppUnit PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CPPUNIT_LIBRARY_RELEASE}"
      )
    endif()

    if(CPPUNIT_LIBRARY_DEBUG)
      set_property(TARGET CppUnit::CppUnit APPEND PROPERTY
        IMPORTED_CONFIGURATIONS DEBUG
      )
      set_target_properties(CppUnit::CppUnit PROPERTIES
        IMPORTED_LOCATION_DEBUG "${CPPUNIT_LIBRARY_DEBUG}"
      )
    endif()

    if(NOT CPPUNIT_LIBRARY_RELEASE AND NOT CPPUNIT_LIBRARY_DEBUG)
      set_property(TARGET CppUnit::CppUnit APPEND PROPERTY
        IMPORTED_LOCATION "${CPPUNIT_LIBRARY}"
      )
    endif()

  endif()
endif()

mark_as_advanced(CPPUNIT_INCLUDE_DIR CPPUNIT_LIBRARY)
