#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>

int quantifyBlur(cv::Mat img);
void detectBlurry(std::string framesFolder);