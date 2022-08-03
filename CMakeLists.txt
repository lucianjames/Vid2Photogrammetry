cmake_minimum_required(VERSION 3.12) # Chosen a bit randomly
project(vid2photogrammetry)

add_library(vid2photogrammetry
	vid2photogrammetry.hpp
	vid2photogrammetry.cpp
)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE vid2photogrammetry)
