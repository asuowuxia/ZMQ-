
cmake_minimum_required(VERSION 3.5)

project(zmq_projects)

# 将源代码添加到此项目的可执行文件。
add_executable (zmq_projects "zmq_projects.cpp" "zmq_projects.h")

add_library(mylib SHARED IMPORTED)
set_target_properties(mylib PROPERTIES
IMPORTED_LOCATION "${CMAKE_INCLUDE_CURRENT_DIR}/dll/libzmq-v143-mt-gd-4_3_5.dll"
IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/libzmq-v143-mt-gd-4_3_5.lib"
INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

 file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dll/libzmq-v143-mt-gd-4_3_5.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../out/build/x86-debug/zmq_projects)

target_link_libraries(zmq_projects mylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET zmq_projects PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
