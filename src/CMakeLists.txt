# Here we find a typical ROS description package, this set the XARM_DESCRIPTION_PATH CMake variable
find_description_package(xarm_description)
if(EXISTS "${XARM_DESCRIPTION_PATH}/share/xarm_description")
  set(XARM_DESCRIPTION_PATH "${XARM_DESCRIPTION_PATH}/share/xarm_description")
endif()

# Generate the robot module C++ code using this value
configure_file(xarm.in.cpp "${CMAKE_CURRENT_BINARY_DIR}/xarm.cpp")

set(XARM_SRC "${CMAKE_CURRENT_BINARY_DIR}/xarm.cpp")
set(XARM_HDR xarm.h)

add_robot(xarm ${XARM_SRC} ${XARM_HDR})
target_include_directories(xarm PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
