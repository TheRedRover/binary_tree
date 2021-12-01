cmake_minimum_required(VERSION 3.1)

project(Weather)

set(HEADERS src/headers)
set(SRC src/sources)

set(CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lboost_system -Wall -Wextra -Werror ")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(${HEADERS}/)

file(GLOB SOURCES ${SRC}/*.cpp)

add_executable(BinTree ${SOURCES})

target_link_libraries( BinTree ${OpenCV_LIBS} )
