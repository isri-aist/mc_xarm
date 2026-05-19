add_executable(${PROJECT_NAME} interface.cpp main.cpp)

target_include_directories(
  ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_definitions(
  ${PROJECT_NAME} PRIVATE CMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}"
                          PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE Boost::program_options mc_fleet::mc_robot_interface
)

set(JOB_POOL_OPTION)
if(${CMAKE_VERSION} VERSION_GREATER "3.14")
  set(JOB_POOL_OPTION JOB_POOL console)
endif()
add_custom_target(
  setcap_${PROJECT_NAME} ALL
  COMMAND ${SUDO} -S ${SETCAP} cap_sys_nice+eip $<TARGET_FILE:${PROJECT_NAME}>
  DEPENDS ${PROJECT_NAME} ${JOB_POOL_OPTION}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(
  CODE
  "execute_process(COMMAND ${SUDO} -S ${SETCAP} cap_sys_nice+eip ${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME})"
)
