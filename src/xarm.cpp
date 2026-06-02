#include "xarm.h"
#include "config.h"

#include <regex>

#include <RBDyn/parsers/urdf.h>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

namespace mc_robots
{

XArmRobotModule::XArmRobotModule(const std::string & name, bool fixed)
: mc_rbdyn::RobotModule(XARM_DESCRIPTION_PATH, name)
{
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));

  // Determine dof from name
  std::smatch match;
  std::regex number_regex("([0-9]+)");
  int dof{0};
  if(std::regex_search(name, match, number_regex))
  {
    dof = std::stoi(match.str(1));
  }

  // Build link names
  std::vector<std::string> links;
  links.emplace_back("link_base");
  for(int i = 1; i <= dof; ++i)
  {
    links.push_back("link" + std::to_string(i));
  }

  // Self-collisions: all non-adjacent link pairs
  _minimalSelfCollisions.clear();
  for(size_t i = 0; i < links.size(); ++i)
  {
    for(size_t j = i + 2; j < links.size(); ++j)
    {
      _minimalSelfCollisions.emplace_back(links[i], links[j], 0.01, 0.001, 0.0);
    }
  }
  _commonSelfCollisions = _minimalSelfCollisions;

  // Ref joint order
  _ref_joint_order.clear();
  for(int i = 1; i <= dof; ++i)
  {
    _ref_joint_order.push_back("joint" + std::to_string(i));
  }

  // Stance: all joints at 0.0
  for(const auto & j : mb.joints())
  {
    if(j.name() != "Root" && j.dof() > 0)
    {
      _stance[j.name()] = {0.0};
    }
  }

  if(name != "lite6")
  {
    _forceSensors.push_back(mc_rbdyn::ForceSensor("EEForceSensor", "link7", sva::PTransformd::Identity()));
  }
}

} // namespace mc_robots
