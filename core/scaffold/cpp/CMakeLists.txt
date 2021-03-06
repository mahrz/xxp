# CMakeLists.txt generated by xxp create {{adaptor}} {{experiment}}
cmake_minimum_required (VERSION 2.6)
project({{experiment}})

exec_program(xxp ARGS path cmake
  OUTPUT_VARIABLE XXP_CMAKE_MODULES)

exec_program(xxp ARGS path adaptors/cpp/include
  OUTPUT_VARIABLE XXP_INCLUDES)

# Find boost headers and zmq library & headers
set(CMAKE_MODULE_PATH "${XXP_CMAKE_MODULES}")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

find_package(ZMQ)
include_directories(${ZMQ_INCLUDE_DIRS})

# Include adaptor header files
include_directories("${XXP_INCLUDES}")

# Cpp adaptor requires C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# In debug mode define XXP_DEBUG macro
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DXXP_DEBUG")

# Actual Configuration Starts Here
add_executable({{experiment}} main.cpp)
target_link_libraries({{experiment}} ${ZMQ_LIBRARIES})