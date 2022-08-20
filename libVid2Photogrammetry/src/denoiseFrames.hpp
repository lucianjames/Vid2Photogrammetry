#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>

void denoiseFrames(std::string framesFolder, float strength);