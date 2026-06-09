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

find_program(XACRO xacro REQUIRED)
find_package(mc_rtc REQUIRED)
find_package(mc_mujoco OPTIONAL)

find_description_package(xarm_description REQUIRED)

# Resolve the actual share path (ROS install layout has an extra share/xarm_description subdir)
if(EXISTS "${XARM_DESCRIPTION_PATH}/share/xarm_description")
  set(XARM_DESCRIPTION_SHARE "${XARM_DESCRIPTION_PATH}/share/xarm_description")
else()
  set(XARM_DESCRIPTION_SHARE "${XARM_DESCRIPTION_PATH}")
endif()

# Glob all xacro files for dependency tracking
file(GLOB_RECURSE XARM_XACRO_FILES "${XARM_DESCRIPTION_SHARE}/*.xacro")

# Installation directories
# IMPORTANT: XARM_DESCRIPTION_PATH (baked into the binary) must equal
# CMAKE_INSTALL_PREFIX/share/mc_xarm so that RobotModule finds
# urdf/xarm7.urdf relative to it.
set(MC_XARM_SHARE_DIR "${CMAKE_INSTALL_PREFIX}/share/mc_xarm")
set(MC_XARM_URDF_DIR "${MC_XARM_SHARE_DIR}/urdf")

# This is the path that gets compiled into the robot module via config.in.h.
# It must match where the URDFs are installed at runtime.
set(XARM_DESCRIPTION_PATH "${MC_XARM_SHARE_DIR}")

# Models to generate
set(XARM_MODELS "xarm5" "xarm6" "xarm7" "xarm7_mirror" "lite6")

set(GENERATED_URDF_FILES "")

# Configure wrapper xacros (substitute @XARM_DESCRIPTION_SHARE@)
foreach(MODEL ${XARM_MODELS})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/xacro/${MODEL}.urdf.in.xacro"
    "${CMAKE_CURRENT_BINARY_DIR}/xacro/${MODEL}.urdf.xacro" @ONLY
  )
endforeach()

set(GENERATED_URDF_FILES "")

foreach(MODEL ${XARM_MODELS})

  # Point to the CONFIGURED wrapper (in build dir, with absolute paths)
  set(XACRO_IN "${CMAKE_CURRENT_BINARY_DIR}/xacro/${MODEL}.urdf.xacro")
  set(GENERATED_URDF "${CMAKE_CURRENT_BINARY_DIR}/urdf/${MODEL}.urdf")

  message(STATUS "URDF generation: ${XACRO_IN} -> ${GENERATED_URDF}")

  add_custom_command(
    OUTPUT ${GENERATED_URDF}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/urdf
    COMMAND
      ${CMAKE_COMMAND} -E env
      "AMENT_PREFIX_PATH=/usr/local:$ENV{AMENT_PREFIX_PATH}" ${XACRO}
      ${XACRO_IN} -o ${GENERATED_URDF}
    DEPENDS ${XACRO_IN} ${XARM_XACRO_FILES}
    COMMENT "Generating URDF for ${MODEL}"
    VERBATIM
  )

  list(APPEND GENERATED_URDF_FILES ${GENERATED_URDF})

endforeach()

# Single target for all URDFs
add_custom_target(generate-xarm-urdf ALL DEPENDS ${GENERATED_URDF_FILES})

# Build (XARM_DESCRIPTION_PATH is now set to the install-time value,
# so configure_file in src/ will bake in the correct path)
add_subdirectory(src)

if(mc_mujoco_FOUND)
  add_subdirectory(mujoco_description)
endif()

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Install generated URDFs into share/mc_xarm/urdf/ —
# matches the XARM_DESCRIPTION_PATH/urdf/{name}.urdf layout that RobotModule expects
install(FILES ${GENERATED_URDF_FILES} DESTINATION ${MC_XARM_URDF_DIR})
