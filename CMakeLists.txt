cmake_minimum_required(VERSION 3.15)
project(Ehtimam)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Boost 1.70 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_library(SQLITE3_LIB sqlite3)
find_path(SQLITE3_INCLUDE sqlite3.h)

# Server
add_executable(server_app src/server/server.cpp)
target_include_directories(server_app PRIVATE ${Boost_INCLUDE_DIRS} ${SQLITE3_INCLUDE})
target_link_libraries(server_app nlohmann_json::nlohmann_json ${SQLITE3_LIB} pthread)

# GUI Client
add_executable(ehtimam_app
    src/main.cpp
    src/gui/AppController.cpp
    src/gui/LoginWindow.cpp
    src/gui/MainWindow.cpp
    src/gui/CircleWindow.cpp
    src/network/NetworkClient.cpp
)
target_include_directories(ehtimam_app PRIVATE ${Boost_INCLUDE_DIRS} src)
target_link_libraries(ehtimam_app Qt6::Core Qt6::Widgets nlohmann_json::nlohmann_json pthread)

# Tests
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    find_package(GTest QUIET PATHS /opt/homebrew/lib/cmake/GTest /opt/homebrew/Cellar)
endif()
if(GTest_FOUND OR TARGET GTest::gtest)
    enable_testing()
    add_executable(run_tests tests/test_main.cpp)
    target_include_directories(run_tests PRIVATE /opt/homebrew/include)
    target_link_libraries(run_tests /opt/homebrew/lib/libgtest.a /opt/homebrew/lib/libgmock.a /opt/homebrew/lib/libgtest_main.a nlohmann_json::nlohmann_json)
    set_target_properties(run_tests PROPERTIES BUILD_RPATH "/opt/homebrew/lib" INSTALL_RPATH "/opt/homebrew/lib")
    add_test(NAME EhtimamTests COMMAND run_tests)
endif()
