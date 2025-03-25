cmake_minimum_required(VERSION 3.15)
project(server)

set(INCLUDE_PATHS asio-1.30.0/include crow/include)

add_executable(server main.cpp)

target_include_directories(server PUBLIC ${INCLUDE_PATHS})

# Link against the required Winsock library
target_link_libraries(server PRIVATE ws2_32 mswsock)
