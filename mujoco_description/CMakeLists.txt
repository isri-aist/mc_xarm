if(NOT TARGET mc_mujoco::mc_mujoco)
  find_package(mc_mujoco REQUIRED)
endif()

if(${MUJOCO_DESCRIPTION_LITE6})
  add_subdirectory(Lite6)
endif()

if(${MUJOCO_DESCRIPTION_XARM7})
  add_subdirectory(xArm7)
endif()
