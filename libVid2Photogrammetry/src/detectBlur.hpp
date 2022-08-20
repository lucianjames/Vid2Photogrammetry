#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>

float quantifyBlur(cv::Mat img);
void removeBlurryFrames(std::string framesFolder, int threshold);