#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>

#include "commonFunctions.hpp"

void resizeFrames(std::string framesFolder, unsigned int x, unsigned int y){
    std::cout << "==================================================" << std::endl;
    std::cout << "Resizing frames...." << std::endl;
    std::cout << "Performing validation..." << std::endl;
    // Ensure x and y are greater than 0
    if(x == 0 || y == 0){
        std::cout << "ERR: x and y must be greater than 0" << std::endl;
        std::cout << "No frames were resized" << std::endl;
        return;
    }

    // Check framesFolder exists
    if(!framesFolderExists(framesFolder)){return;}

    // Get the list of files in the framesFolder
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);

    // Resize each frame in the framesFolder
    std::cout << "Resizing " << files.size() << " images..." << std::endl;
    for(auto fp : files){
        cv::Mat frame = cv::imread(fp);
        cv::resize(frame, frame, cv::Size(x, y)); // Resize the frame
        cv::imwrite(fp, frame); // Save the frame
    }
    std::cout << "Image resizing complete" << std::endl;
}