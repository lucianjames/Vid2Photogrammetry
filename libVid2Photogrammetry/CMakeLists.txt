find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB vid2photogrammetry_SRC
     "src/*.hpp"
     "src/*.cpp"
)

add_library(vid2photogrammetry
	${vid2photogrammetry_SRC}
)

target_link_libraries(vid2photogrammetry ${OpenCV_LIBS})
target_include_directories(vid2photogrammetry PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")