cmake_minimum_required(VERSION 3.21)

set(CXX_DISABLE_WERROR 1)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME mc_xarm)
set(PROJECT_VERSION 1.0.0)
project(
  ${PROJECT_NAME}
  LANGUAGES CXX
  VERSION ${PROJECT_VERSION}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CTest)

find_package(mc_rtc REQUIRED)

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
