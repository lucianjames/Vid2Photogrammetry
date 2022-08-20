#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>

float quantifyBlur(const cv::Mat& img){
    // Convert image to grayscale and scale it down
    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY); // Convert to gray
    cv::resize(grayImg, grayImg, cv::Size(512, 512)); // Resize to fixed size
    cv::Mat laplaceImage;
    cv::Laplacian(grayImg, laplaceImage, CV_64F);
    cv::Scalar mean, stddev;
    cv::meanStdDev(laplaceImage, mean, stddev, cv::Mat());
    return stddev.val[0]*stddev.val[0];
}

void removeBlurryFrames(std::string framesFolder, int threshold){
    // Just get the blur values for each image, going to program the removal feature next.
    // Check framesFolder exists
    if(!std::filesystem::exists(framesFolder)){
        std::cout << "Resize error: folder does not exist" << std::endl;
        return;
    }

    // Get the list of files in the framesFolder
    std::vector<std::string> files;
    for(auto& p : std::filesystem::directory_iterator(framesFolder)){
        files.push_back(p.path().string());
    }

    std::cout << "Blur detection values:" << std::endl;
    for(auto fp : files){
        std::cout << fp << std::endl;
        float frameBlur = quantifyBlur(cv::imread(fp));
        std::cout << frameBlur << std::endl;
        // If blur is below threshold, delete it
        if(frameBlur < threshold){
            std::filesystem::remove(fp);
        }
    }


}