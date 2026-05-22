cmake_minimum_required(VERSION 3.22)

project(lite6_mj_description VERSION 1.0.0)

option(HONOR_INSTALL_PREFIX
       "Whether to install in CMAKE_INSTALL_PREFIX (for nix)" OFF
)
option(SRC_MODE "Use files in the repository instead of installed files" OFF)

if(HONOR_INSTALL_PREFIX)
  set(MC_MUJOCO_SHARE_DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()

set(LITE6_XML_MODEL_PATH "xml/lite6.xml")
set(LITE6_PDGAINS_PATH "pdgains/PDgains_sim.dat")

if(SRC_MODE)
  set(LITE6_XML_MODEL_PATH
      "${CMAKE_CURRENT_SOURCE_DIR}/${LITE6_XML_MODEL_PATH}"
  )
  set(LITE6_PDGAINS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${LITE6_PDGAINS_PATH}")
else()
  set(LITE6_XML_MODEL_PATH
      "${MC_MUJOCO_SHARE_DESTINATION}/LITE6/${LITE6_XML_MODEL_PATH}"
  )
  set(LITE6_PDGAINS_PATH
      "${MC_MUJOCO_SHARE_DESTINATION}/LITE6/${LITE6_PDGAINS_PATH}"
  )
endif()

configure_file(
  mc_mujoco/lite6.in.yaml "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/lite6.yaml"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mc_mujoco/lite6.yaml"
        DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}"
)
install(DIRECTORY pdgains DESTINATION "${MC_MUJOCO_SHARE_DESTINATION}/LITE6"
                                      FILES_MATCHING PATTERN "*.dat"
)
install(
  DIRECTORY xml
  DESTINATION
    "${MC_MUJOCO_SHARE_DESTINATION}/LITE6"
    FILES_MATCHING
    PATTERN
    "*.xml"
    PATTERN
    "*.obj"
    PATTERN
    "*.stl"
)
