# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (LineTrackingCar)

# 指定生成目标
add_executable(main main.cpp carControl/class/Speeds.cpp carControl/class/Speeds.h carControl/class/Distances.cpp carControl/class/Distances.h carControl/class/ControlConfigs.h carControl/class/PID.cpp carControl/class/PID.h)