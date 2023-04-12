cmake_minimum_required(VERSION 2.8.12)
project(PocoExample)

SET(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(LoggingExample src/logging.cpp)
add_executable(HttpsServerExample src/https-server.cpp)

target_link_libraries(LoggingExample ${CONAN_LIBS})
target_link_libraries(HttpsServerExample ${CONAN_LIBS})
