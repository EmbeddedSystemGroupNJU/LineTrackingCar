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
#        imageProcess/process.cpp
#        carControl/control_1.cpp
#        carControl/control_2.cpp
#        carControl/initControl.cpp
        carControl/control_3.cpp carControl/control_4.cpp)