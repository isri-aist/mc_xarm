#pragma once

#include <mc_rbdyn/RobotModule.h>
#include <mc_rbdyn/RobotModuleMacros.h>
#include <mc_robots/api.h>
#include <mc_rtc/logging.h>

namespace mc_robots
{

struct MC_ROBOTS_DLLAPI XArmRobotModule : public mc_rbdyn::RobotModule
{
  XArmRobotModule(const std::string & name, bool fixed);
};

} // namespace mc_robots

extern "C"
{
  ROBOT_MODULE_API void MC_RTC_ROBOT_MODULE(std::vector<std::string> & names) // NOLINT(readability-identifier-naming)
  {
    names = {"xArm5",       "xArm5FloatingBase",       "xArm6", "xArm6FloatingBase", "xArm7", "xArm7FloatingBase",
             "xArm7Mirror", "xArm7MirrorFloatingBase", "Lite6", "Lite6FloatingBase"};
  }
  ROBOT_MODULE_API void destroy(mc_rbdyn::RobotModule * ptr)
  {
    delete ptr; // NOLINT(cppcoreguidelines-owning-memory)
  }
  ROBOT_MODULE_API mc_rbdyn::RobotModule * create(const std::string & n)
  {
    ROBOT_MODULE_CHECK_VERSION("xArm")

    if(n == "xArm5")
    {
      return new mc_robots::XArmRobotModule("xarm5", true);
    }
    if(n == "xArm5FloatingBase")
    {
      return new mc_robots::XArmRobotModule("xarm5", false);
    }

    if(n == "xArm6")
    {
      return new mc_robots::XArmRobotModule("xarm6", true);
    }
    if(n == "xArm6FloatingBase")
    {
      return new mc_robots::XArmRobotModule("xarm6", false);
    }

    if(n == "xArm7")
    {
      return new mc_robots::XArmRobotModule("xarm7", true);
    }
    if(n == "xArm7FloatingBase")
    {
      return new mc_robots::XArmRobotModule("xarm7", false);
    }

    if(n == "xArm7Mirror")
    {
      return new mc_robots::XArmRobotModule("xarm7_mirror", true);
    }
    if(n == "xArm7MirrorFloatingBase")
    {
      return new mc_robots::XArmRobotModule("xarm7_mirror", false);
    }

    if(n == "Lite6")
    {
      return new mc_robots::XArmRobotModule("lite6", true);
    }
    if(n == "Lite6FloatingBase")
    {
      return new mc_robots::XArmRobotModule("lite6", false);
    }

    mc_rtc::log::error("xArm module cannot create an object of type {}", n);
    return nullptr;
  }
}
