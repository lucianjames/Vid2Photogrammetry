find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(vid2photogrammetry
	src/vid2photogrammetry.hpp
	src/vid2photogrammetry.cpp
)

target_include_directories(vid2photogrammetry PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")