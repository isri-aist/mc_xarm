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
  ROBOT_MODULE_API void MC_RTC_ROBOT_MODULE(std::vector<std::string> & names)
  {
    names = {"xArm7", "xArm7FloatingBase"};
  }
  ROBOT_MODULE_API void destroy(mc_rbdyn::RobotModule * ptr)
  {
    delete ptr;
  }
  ROBOT_MODULE_API mc_rbdyn::RobotModule * create(const std::string & n)
  {
    // TODO: add suport for xArm5 and xArm6
    ROBOT_MODULE_CHECK_VERSION("xArm7")
    if(n == "xArm7")
    {
      return new mc_robots::XArmRobotModule("xarm7", true);
    }
    else if(n == "xArm7FloatingBase")
    {
      return new mc_robots::XArmRobotModule("xarm7", false);
    }
    else
    {
      mc_rtc::log::error("xArm module Cannot create an object of type {}", n);
      return nullptr;
    }
  }
}
