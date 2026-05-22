option(XARM7_MUJOCO_DESCRIPTION "Install mc_mujoco description xArm7" OFF)

if(${XARM7_MUJOCO_DESCRIPTION})
  add_subdirectory(xArm7)
endif()
