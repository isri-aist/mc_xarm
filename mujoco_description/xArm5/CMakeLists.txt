cmake_minimum_required(VERSION 3.22)

project(xarm5_mj_description VERSION 1.0.0)

option(HONOR_INSTALL_PREFIX
       "Whether to install in CMAKE_INSTALL_PREFIX (for nix)" OFF)
option(SRC_MODE "Use files in the repository instead of installed files" OFF)

if(HONOR_INSTALL_PREFIX)
  set(MC_MUJOCO_SHARE_DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()

# Generate XML with resolved mesh paths
configure_file(xml/xarm5.in.xml "${CMAKE_CURRENT_BINARY_DIR}/xml/xarm5.xml")

set(XARM5_XML_MODEL_PATH "xml/xarm5.xml")
set(XARM5_PDGAINS_PATH "pdgains/PDgains_sim.dat")

if(SRC_MODE)
  set(XARM5_XML_MODEL_PATH
      "${CMAKE_CURRENT_BINARY_DIR}/${XARM5_XML_MODEL_PATH}")
  set(XARM5_PDGAINS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${XARM5_PDGAINS_PATH}")
else()
  set(XARM5_XML_MODEL_PATH
      "${MC_MUJOCO_SHARE_DESTINATION}/XARM5/${XARM5_XML_MODEL_PATH}")
  set(XARM5_PDGAINS_PATH
      "${MC_MUJOCO_SHARE_DESTINATION}/XARM5/${XARM5_PDGAINS_PATH}")
endif()

configure_file(mc_mujoco/xarm5.in.yaml
               "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/xarm5.yaml")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/xarm5.yaml"
        DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}")

install(
  DIRECTORY pdgains
  DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/XARM5"
  FILES_MATCHING
  PATTERN "*.dat")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/xml/xarm5.xml"
        DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/XARM5/xml")
