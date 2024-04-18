cmake_minimum_required(VERSION 3.25)
project(office)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.hpp")

add_executable(office ${SRC_FILES} ${HEADER_FILES})

target_link_libraries(office ${CURSES_LIBRARIES})
