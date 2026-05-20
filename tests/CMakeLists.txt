if(TARGET xarm7)
  # Change if needed to support other xArm models
  set(ROBOT_MODULE_PARAMS "\"xArm7\"")

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/loader.in.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/mc_xarm/loader.cpp"
  )
  add_executable(loader_xarm7 "${CMAKE_CURRENT_BINARY_DIR}/mc_xarm/loader.cpp")
  target_link_libraries(loader_xarm7 PUBLIC mc_rtc::mc_rbdyn)
  add_test(NAME loader_xarm7 COMMAND loader_xarm7 "$<TARGET_FILE_DIR:xarm7>")
endif()
