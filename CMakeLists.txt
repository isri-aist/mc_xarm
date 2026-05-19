cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME mc_xarm)
set(PROJECT_VERSION 0.0.1)
project(
  ${PROJECT_NAME}
  LANGUAGES CXX
  VERSION ${PROJECT_VERSION}
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(mc_rtc REQUIRED)
find_package(mc_fleet REQUIRED)

find_package(xarm_api REQUIRED)
find_package(xarm_description REQUIRED)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options thread)

find_program(SETCAP setcap)
find_program(SUDO sudo)

include_directories(include)
add_subdirectory(src)

option(BUILD_TESTING "Build test for ${PROJECT_NAME}" ON)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

message(STATUS "")
message(STATUS "Configuration Summary:")
message(STATUS "  Project: ${PROJECT_NAME} ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Build Tests: ${BUILD_TESTING}")
message(STATUS "")
