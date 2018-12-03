# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#
#find_package(OpenCV REQUIRED)
#
#target_link_libraries(project_name ${OpenCV_LIBS})

# 项目信息
project (LineTrackingCar)

# 指定生成目标
add_executable(
        main
        main.cpp
        imageProcess/process.cpp
        abandonCarControl/class/Speeds.cpp
        abandonCarControl/class/Speeds.h
        abandonCarControl/class/Distances.cpp
        abandonCarControl/class/Distances.h
        abandonCarControl/class/ControlConfigs.h
        abandonCarControl/class/PID.cpp
        abandonCarControl/class/PID.h
        abandonCarControl/CarControlMethod.cpp
        abandonCarControl/CarControlMethod.h
        abandonCarControl/GetControlConfig.cpp
        abandonCarControl/GetControlConfig.h
        abandonCarControl/CarControl.cpp
        abandonCarControl/CarControl.h
        carControl/carControl.cpp
)