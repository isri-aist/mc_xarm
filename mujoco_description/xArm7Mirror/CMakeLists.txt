cmake_minimum_required(VERSION 3.22)

project(xarm7_mirror_mj_description VERSION 1.0.0)

option(HONOR_INSTALL_PREFIX
       "Whether to install in CMAKE_INSTALL_PREFIX (for nix)" OFF)
option(SRC_MODE "Use files in the repository instead of installed files" OFF)

if(HONOR_INSTALL_PREFIX)
  set(MC_MUJOCO_SHARE_DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()

# Generate XML with resolved mesh paths
configure_file(xml/xarm7_mirror.in.xml
               "${CMAKE_CURRENT_BINARY_DIR}/xml/xarm7_mirror.xml")

set(xarm7_mirror_XML_MODEL_PATH "xml/xarm7_mirror.xml")
set(xarm7_mirror_PDGAINS_PATH "pdgains/PDgains_sim.dat")

if(SRC_MODE)
  set(xarm7_mirror_XML_MODEL_PATH
      "${CMAKE_CURRENT_BINARY_DIR}/${xarm7_mirror_XML_MODEL_PATH}")
  set(xarm7_mirror_PDGAINS_PATH
      "${CMAKE_CURRENT_SOURCE_DIR}/${xarm7_mirror_PDGAINS_PATH}")
else()
  set(xarm7_mirror_XML_MODEL_PATH
      "${MC_MUJOCO_SHARE_DESTINATION}/xarm7_mirror/${xarm7_mirror_XML_MODEL_PATH}"
  )
  set(xarm7_mirror_PDGAINS_PATH
      "${MC_MUJOCO_SHARE_DESTINATION}/xarm7_mirror/${xarm7_mirror_PDGAINS_PATH}"
  )
endif()

configure_file(mc_mujoco/xarm7_mirror.in.yaml
               "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/xarm7_mirror.yaml")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/xarm7_mirror.yaml"
        DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}")

install(
  DIRECTORY pdgains
  DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/xarm7_mirror"
  FILES_MATCHING
  PATTERN "*.dat")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/xml/xarm7_mirror.xml"
        DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/xarm7_mirror/xml")
