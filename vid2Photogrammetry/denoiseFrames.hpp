#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>

#include "commonFunctions.hpp"

void denoiseFrames(std::string framesFolder, float strength){
    std::cout << "==================================================" << std::endl;
    std::cout << "Denoising frames...." << std::endl;
    std::cout << "Performing validation..." << std::endl;
    // Check framesFolder exists
    if(!folderExists(framesFolder)){return;}

    // Get the list of files in the framesFolder
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);

    // Denoise all the frames
    std::cout << "Denoising " << files.size() << " images..." << std::endl;
    for(auto fp : files){
        cv::Mat denoised; // Create a new Mat to store the denoised frame
        cv::fastNlMeansDenoising(cv::imread(fp), denoised, strength, 7, 21); // Read the frame, denoise it, and store it in denoised
        cv::imwrite(fp, denoised); // Overwrite the original frame with the denoised frame
    }
    std::cout << "Denoising complete" << std::endl;
}
