cmake_minimum_required(VERSION 3.10)

#SET(CMAKE_C_COMPILER /usr/bin/clang)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)
set(CMAKE_VERBOSE_MAKEFILE on)

option (_WIN32 "Use _WIN32" ON)

#include_directories(../Chapter\ 3/RoboCat/Inc)
aux_source_directory(../Chapter\ 3/RoboCat/Src CHAPTER3_SRC_LIST)

message(${CHAPTER3_SRC_LIST})
list (REMOVE_ITEM CHAPTER3_SRC_LIST ../Chapter\ 3/RoboCat/Src/Main.cpp)
message(${CHAPTER3_SRC_LIST})
add_executable(TCPClient TCPClient.cpp ${CHAPTER3_SRC_LIST})
add_executable(TCPServer TCPServer.cpp ${CHAPTER3_SRC_LIST})
add_executable(Client client.c)
add_executable(Server server.c)

target_include_directories(TCPClient PRIVATE ../Chapter\ 3/RoboCat/Inc)
target_include_directories(TCPServer PRIVATE ../Chapter\ 3/RoboCat/Inc)

if (WIN32)
    target_link_libraries(TCPClient ws2_32)
    target_link_libraries(TCPServer ws2_32)
    target_link_libraries(Client ws2_32)
    target_link_libraries(Server ws2_32)
elseif(UNIX)

endif()
