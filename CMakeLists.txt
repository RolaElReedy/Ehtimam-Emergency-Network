cmake_minimum_required(VERSION 3.15)
project(Ehtimam)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.70 REQUIRED)
find_package(nlohmann_json REQUIRED)

find_library(SQLITE3_LIB sqlite3)
find_path(SQLITE3_INCLUDE sqlite3.h)

add_executable(server_app src/server/server.cpp)
target_include_directories(server_app PRIVATE ${Boost_INCLUDE_DIRS} ${SQLITE3_INCLUDE})
target_link_libraries(server_app nlohmann_json::nlohmann_json ${SQLITE3_LIB} pthread)

add_executable(client_app src/client/client.cpp)
target_include_directories(client_app PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(client_app pthread)
