# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (LineTrackingCar)

# 指定生成目标
add_executable(main main.cpp CarControl/class/Speeds.cpp CarControl/class/Speeds.h CarControl/class/Distances.cpp CarControl/class/Distances.h CarControl/class/ControlConfigs.h CarControl/class/PID.cpp CarControl/class/PID.h)