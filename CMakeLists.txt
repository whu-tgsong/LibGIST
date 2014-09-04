cmake_minimum_required(VERSION 2.8.11)
project(LibGIST)

if(MSVC)
  set(CMAKE_CXX_FLAGS "/EHsc")
else()
  set(CMAKE_CXX_FLAGS "-std=c++11 -fno-operator-names")
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

option(USE_DEV_LIBS_PATH OFF)
if(USE_DEV_LIBS_PATH)
  set(DEFAULT_LIB_PATH $ENV{DEV_LIBS})
  set(FFTW_DIR ${DEFAULT_LIB_PATH}/FFTW)
  set(OpenCV_DIR ${DEFAULT_LIB_PATH}/OpenCV)
endif()

find_package(FFTW REQUIRED)
include_directories(${FFTW_INCLUDES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(PROJ_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJ_INCLUDE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_subdirectory(src)