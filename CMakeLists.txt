cmake_minimum_required(VERSION 2.8.11)
project(LibGIST)

if(MSVC)
  set(CMAKE_CXX_FLAGS "-DUSE_GIST -DSTANDALONE_GIST")
else()
  # -Wall -g -o $@ $^ $(WFFTLIB) -lfftw3f -lm
  set(CMAKE_CXX_FLAGS "-std=c++14 -fno-operator-names -Wall -lm -DUSE_GIST -DSTANDALONE_GIST")
endif()

set(DEFAULT_LIB_PATH $ENV{DEV_LIBS})

find_package(FFTW REQUIRED PATHS ${DEFAULT_LIB_PATH}/FFTW)
include_directories(${FFTW_INCLUDES})

find_package(OpenCV REQUIRED PATHS ${DEFAULT_LIB_PATH}/OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_subdirectory(src)