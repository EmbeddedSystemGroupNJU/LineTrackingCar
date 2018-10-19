# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (LineTrackingCar)

# 指定生成目标
add_executable(main main.cpp carControl/Speeds.cpp carControl/Speeds.h carControl/Distances.cpp carControl/Distances.h carControl/ControlConfigs.h carControl/PID.cpp carControl/PID.h)