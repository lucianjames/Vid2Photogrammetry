cmake_minimum_required(VERSION 3.10.0)

project(vid2photogrammetry)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

if(UNIX)
set(CMAKE_CXX_FLAGS "-O3 -s")
endif(UNIX)

if(MSVC)
set(CMAKE_CXX_FLAGS "/O2")
endif(MSVC)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets Concurrent)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(vid2photogrammetry
   mainwindow.ui
   mainwindow.cpp
   main.cpp
   resources.qrc
)

target_link_libraries(vid2photogrammetry
   Qt5::Widgets
   Qt5::Concurrent
   ${OpenCV_LIBS}
)
