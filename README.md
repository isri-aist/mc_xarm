# mc_xarm

mc_rtc robot module for [UFACTORY xArm](https://www.ufactory.cc/) series robots (xArm5, xArm6, xArm7).

## Dependencies

- [ROS2](https://docs.ros.org/)

- [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/)

- [xarm_description](https://github.com/xArm-Developer/xarm_ros2)

```sh
git clone https://github.com/xArm-Developer/xarm_ros2.git
cd xarm_ros2
colcon build --packages-select xarm_description
source install/setup.bash # change setup.sh or setup.zsh accordingly
cd ..
```

## Build & Install

```sh
git clone https://github.com/isri-aist/mc_xarm.git
cd mc_xarm
mkdir -p build && cd build
cmake ..
make
sudo make install
cd ..
```

To test the module is installed correctly

```sh
mc_rtc_ticker -f etc/mc_rtc.yaml
```
