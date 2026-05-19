cmake_minimum_required(VERSION 3.14)
find_package(GTest CONFIG)

if(NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
  )
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE
  )
  FetchContent_MakeAvailable(googletest)
endif()
include(GoogleTest)

# --------------------------------------------------
# Collect all test files
# --------------------------------------------------
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

foreach(test_file ${TEST_SOURCES})
  # Extract filename without extension
  get_filename_component(test_name ${test_file} NAME_WE)

  # Create one executable per test file
  add_executable(${test_name} ${test_file})

  target_link_libraries(${test_name} PRIVATE mc_communication GTest::gtest_main)

  # Register tests
  gtest_discover_tests(${test_name})
endforeach()
