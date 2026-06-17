cmake_minimum_required(VERSION 3.22)

project(xarm7_mj_description VERSION 1.0.0)

option(HONOR_INSTALL_PREFIX
       "Whether to install in CMAKE_INSTALL_PREFIX (for nix)" OFF)
option(SRC_MODE "Use files in the repository instead of installed files" OFF)

if(HONOR_INSTALL_PREFIX)
  set(MC_MUJOCO_SHARE_DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()

# Generate XML with resolved mesh paths
configure_file(xml/xarm7.in.xml "${CMAKE_CURRENT_BINARY_DIR}/xml/xarm7.xml")

set(XARM7_XML_MODEL_PATH "xml/xarm7.xml")
set(XARM7_PDGAINS_PATH "pdgains/PDgains_sim.dat")

if(SRC_MODE)
  set(XARM7_XML_MODEL_PATH
      "${CMAKE_CURRENT_BINARY_DIR}/${XARM7_XML_MODEL_PATH}")
  set(XARM7_PDGAINS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${XARM7_PDGAINS_PATH}")
else()
  set(XARM7_XML_MODEL_PATH
      "${MC_MUJOCO_SHARE_DESTINATION}/XARM7/${XARM7_XML_MODEL_PATH}")
  set(XARM7_PDGAINS_PATH
      "${MC_MUJOCO_SHARE_DESTINATION}/XARM7/${XARM7_PDGAINS_PATH}")
endif()

configure_file(mc_mujoco/xarm7.in.yaml
               "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/xarm7.yaml")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/xarm7.yaml"
        DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}")

install(
  DIRECTORY pdgains
  DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/XARM7"
  FILES_MATCHING
  PATTERN "*.dat")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/xml/xarm7.xml"
        DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/XARM7/xml")
