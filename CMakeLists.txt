cmake_minimum_required(VERSION 3.20)
project(eighth_sem)

set(CMAKE_CXX_STANDARD 20)

set(Boost_INCLUDE_DIR C:/Mingw/include/)
set(Boost_LIBRARY_DIR C:/Mingw/lib/)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)

target_link_libraries(sender ws2_32)
target_link_libraries(receiver ws2_32)
