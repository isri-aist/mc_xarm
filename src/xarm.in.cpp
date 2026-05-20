#include "xarm.h"

#include <RBDyn/parsers/urdf.h>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

namespace
{

// This is set by CMake, see CMakeLists.txt
static const std::string XARM_DESCRIPTION_PATH = "@XARM_DESCRIPTION_PATH@";

} // namespace

namespace mc_robots
{

XArmRobotModule::XArmRobotModule(const std::string & name, bool fixed)
: mc_rbdyn::RobotModule(XARM_DESCRIPTION_PATH, name)
{
  // Makes all the basic initialization that can be done from an URDF file
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));

  // Automatically load the convex hulls associated to each body
  std::string convexPath = path + "/convex/" + name + "/";
  bfs::path p(convexPath);
  if(bfs::exists(p) && bfs::is_directory(p))
  {
    std::vector<bfs::path> files;
    std::copy(bfs::directory_iterator(p), bfs::directory_iterator(), std::back_inserter(files));
    for(const bfs::path & file : files)
    {
      size_t off = file.filename().string().rfind("-ch.txt");
      if(off != std::string::npos)
      {
        std::string body = file.filename().string();
        body.replace(off, 7, "");
        // xArm link names in URDF match the file stem directly
        _convexHull[body] = std::pair<std::string, std::string>(body, file.string());
      }
    }
  }
  else
  {
    mc_rtc::log::warning("No convex hull directory found at {}", convexPath);
  }

  // Define a minimal set of self-collisions
  _minimalSelfCollisions = {{"link_base", "link2", 0.01, 0.001, 0.0}, {"link_base", "link3", 0.01, 0.001, 0.0},
                            {"link_base", "link4", 0.01, 0.001, 0.0}, {"link_base", "link5", 0.01, 0.001, 0.0},
                            {"link_base", "link6", 0.01, 0.001, 0.0}, {"link_base", "link7", 0.01, 0.001, 0.0},

                            {"link1", "link3", 0.01, 0.001, 0.0},     {"link1", "link4", 0.01, 0.001, 0.0},
                            {"link1", "link5", 0.01, 0.001, 0.0},     {"link1", "link6", 0.01, 0.001, 0.0},
                            {"link1", "link7", 0.01, 0.001, 0.0},

                            {"link2", "link4", 0.01, 0.001, 0.0},     {"link2", "link5", 0.01, 0.001, 0.0},
                            {"link2", "link6", 0.01, 0.001, 0.0},     {"link2", "link7", 0.01, 0.001, 0.0},

                            {"link3", "link5", 0.01, 0.001, 0.0},     {"link3", "link6", 0.01, 0.001, 0.0},
                            {"link3", "link7", 0.01, 0.001, 0.0},

                            {"link4", "link6", 0.01, 0.001, 0.0},     {"link4", "link7", 0.01, 0.001, 0.0},

                            {"link5", "link7", 0.01, 0.001, 0.0}};
  _commonSelfCollisions = _minimalSelfCollisions;

  // Ref joint order
  _ref_joint_order = {"joint1", "joint2", "joint3", "joint4", "joint5", "joint6", "joint7"};

  // Stance: joint name, angle in degrees
  std::map<std::string, double> starting{{"joint1", 0.0}, {"joint2", 0.0}, {"joint3", 0.0}, {"joint4", 0.0},
                                         {"joint5", 0.0}, {"joint6", 0.0}, {"joint7", 0.0}};

  for(const auto & j : mb.joints())
  {
    if(j.name() != "Root" && j.dof() > 0)
    {
      _stance[j.name()] = {starting.at(j.name())};
    }
  }
}

} // namespace mc_robots
