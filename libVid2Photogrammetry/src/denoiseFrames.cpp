#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>

void denoiseFrames(std::string framesFolder){
    // Check framesFolder exists
    if(!std::filesystem::exists(framesFolder)){
        std::cout << "Denoise error: folder does not exist" << std::endl;
        return;
    }

    // Get the list of files in the framesFolder
    std::vector<std::string> files;
    for(auto& p : std::filesystem::directory_iterator(framesFolder)){
        files.push_back(p.path().string());
    }

    // Denoise all the frames
    for(auto fp : files){
        cv::Mat denoised;
        cv::fastNlMeansDenoising(cv::imread(fp), denoised, 30.0, 7, 21);
        cv::imwrite(fp, denoised);
    }
}