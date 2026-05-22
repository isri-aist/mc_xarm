if(NOT TARGET mc_mujoco::mc_mujoco)
  find_package(mc_mujoco REQUIRED)
endif()

option(MUJOCO_DESCRIPTION_LITE6 "Install mc_mujoco description Lite6" OFF)
if(${MUJOCO_DESCRIPTION_LITE6})
  add_subdirectory(Lite6)
endif()

option(MUJOCO_DESCRIPTION_XARM7 "Install mc_mujoco description xArm7" OFF)
if(${MUJOCO_DESCRIPTION_XARM7})
  add_subdirectory(xArm7)
endif()
