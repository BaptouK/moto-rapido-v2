cmake_minimum_required(VERSION 3.15)
project(server)

set(INCLUDE_PATHS asio-1.30.0/include crow/include)

add_executable(server
        src/main.cpp
        src/utils.cpp
        src/player.cpp
        src/lobby.cpp
        include/player.h
        include/utils.h
        include/lobby.h
)

target_include_directories(server PUBLIC ${INCLUDE_PATHS})

target_link_libraries(server PRIVATE ws2_32 mswsock )