# - Find the FFTW library
#
# Usage:
#   find_package(FFTW [REQUIRED] [QUIET] )
#     
# It sets the following variables:
#   FFTW_FOUND               ... true if fftw is found on the system
#   FFTW_LIBRARIES           ... full path to fftw library
#   FFTW_INCLUDES            ... fftw include directory
#
# The following variables will be checked by the function
#   FFTW_USE_STATIC_LIBS    ... if true, only static libraries are found
#   FFTW_DIR               ... if set, the libraries are exclusively searched
#                               under this path
#   FFTW_LIBRARY            ... fftw library to use
#   FFTW_INCLUDE_DIR        ... fftw include directory
#

#If environment variable FFTWDIR is specified, it has same effect as FFTW_DIR
if(NOT FFTW_DIR AND ENV{FFTWDIR})
  set(FFTW_DIR $ENV{FFTWDIR})
endif()

# Check if we can use PkgConfig
find_package(PkgConfig)

#Determine from PKG
if(PKG_CONFIG_FOUND AND NOT FFTW_DIR)
  pkg_check_modules(PKG_FFTW QUIET "fftw3")
endif()

#Check whether to search static or dynamic libs
set(CMAKE_FIND_LIBRARY_SUFFIXES_SAV ${CMAKE_FIND_LIBRARY_SUFFIXES})

#Check platform
if(MSVC)
  set(CMAKE_FIND_LIBRARY_SUFFIXES -3.lib)
  set(CMAKE_FIND_LIBRARY_PREFIXES lib)
elseif(MINGW)
  set(CMAKE_FIND_LIBRARY_SUFFIXES -3.dll)
else()
  if(${FFTW_USE_STATIC_LIBS})
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_STATIC_LIBRARY_SUFFIX})
  else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_SHARED_LIBRARY_SUFFIX})
  endif()
endif()

if(FFTW_DIR)

  #find libs
  find_library(
    FFTW_LIB
    NAMES fftw3
    PATHS ${FFTW_DIR}
    PATH_SUFFIXES lib lib64
    NO_DEFAULT_PATH
  )

  find_library(
    FFTWF_LIB
    NAMES fftw3f
    PATHS ${FFTW_DIR}
    PATH_SUFFIXES lib lib64
    NO_DEFAULT_PATH
  )

  find_library(
    FFTWL_LIB
    NAMES fftw3l
    PATHS ${FFTW_DIR}
    PATH_SUFFIXES lib lib64
    NO_DEFAULT_PATH
  )

  #find includes
  find_path(
    FFTW_INCLUDES
    NAMES fftw3.h
    PATHS ${FFTW_DIR}
    PATH_SUFFIXES include
    NO_DEFAULT_PATH
  )

else()

  find_library(
    FFTW_LIB
    NAMES "fftw3"
    PATHS ${PKG_FFTW_LIBRARY_DIRS} ${LIB_INSTALL_DIR}
  )

  find_library(
    FFTWF_LIB
    NAMES "fftw3f"
    PATHS ${PKG_FFTW_LIBRARY_DIRS} ${LIB_INSTALL_DIR}
  )


  find_library(
    FFTWL_LIB
    NAMES "fftw3l"
    PATHS ${PKG_FFTW_LIBRARY_DIRS} ${LIB_INSTALL_DIR}
  )

  find_path(
    FFTW_INCLUDES
    NAMES "fftw3.h"
    PATHS ${PKG_FFTW_INCLUDE_DIRS} ${INCLUDE_INSTALL_DIR}
  )

endif(FFTW_DIR)

set(FFTW_LIBRARIES ${FFTW_LIB} ${FFTWF_LIB})

if(FFTWL_LIB)
  set(FFTW_LIBRARIES ${FFTW_LIBRARIES} ${FFTWL_LIB})
endif()

set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES_SAV})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FFTW DEFAULT_MSG
                                  FFTW_INCLUDES FFTW_LIBRARIES)

mark_as_advanced(FFTW_INCLUDES FFTW_LIBRARIES FFTW_LIB FFTWF_LIB FFTWL_LIB)

