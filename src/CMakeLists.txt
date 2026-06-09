# XARM_DESCRIPTION_PATH is set by the parent CMakeLists.txt to the install-time
# path (CMAKE_INSTALL_PREFIX/share/mc_xarm) *before* add_subdirectory(src) is
# called, so configure_file bakes in the correct runtime path in both generated
# files.

# Generate xarm.cpp from the template (substitutes @XARM_DESCRIPTION_PATH@)
# configure_file(xarm.in.cpp "${CMAKE_CURRENT_BINARY_DIR}/xarm.cpp")

# Generate config.h from the template (substitutes @XARM_DESCRIPTION_PATH@)
configure_file(config.in.h "${CMAKE_CURRENT_BINARY_DIR}/config.h")

set(XARM_SRC "${CMAKE_CURRENT_SOURCE_DIR}/xarm.cpp")
set(XARM_HDR "${CMAKE_CURRENT_SOURCE_DIR}/xarm.h")

add_robot(xarm ${XARM_SRC} ${XARM_HDR})

target_include_directories(
  xarm
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
          "${CMAKE_CURRENT_BINARY_DIR}" # so that #include "config.h" resolves
)
