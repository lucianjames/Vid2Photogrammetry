#include <pybind11/pybind11.h>

#include <string>

void extractFrames(std::string inputPath, std::string outputPath, std::string outputName, std::string outputExtension, int frameCount);