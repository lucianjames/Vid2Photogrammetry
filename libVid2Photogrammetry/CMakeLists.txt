cmake_minimum_required(VERSION 3.4...3.18)
project(vid2photogrammetry_pybind)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB vid2photogrammetry_SRC
     "src/*.hpp"
     "src/*.cpp"
)

add_subdirectory(pybind11)
pybind11_add_module(vid2photogrammetry ${vid2photogrammetry_SRC})
set_property(TARGET vid2photogrammetry PROPERTY CXX_STANDARD 17)

target_link_libraries(vid2photogrammetry PRIVATE ${OpenCV_LIBS})
