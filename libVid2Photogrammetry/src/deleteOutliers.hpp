#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>

#include "commonFunctions.hpp"

void deleteOutliers(std::string framesFolder, float threshold){
    std::cout << "==================================================" << std::endl;
    std::cout << "Removing Outlier frames...." << std::endl;
    std::cout << "Performing validation..." << std::endl;
    // Check framesFolder exists
    if(!framesFolderExists(framesFolder)){return;}

    // Get the list of files in the framesFolder
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);
    
    // Basically O(n^2), but ive optimised it a little bit
    std::cout << "Performing histogram analysis and frame removal..." << std::endl;
    std::vector<std::string> toKeep = getSimilarImagePaths(framesFolder, 1-threshold);
    int removed = files.size() - toKeep.size();
    for(auto fp : files){
        if(std::find(toKeep.begin(), toKeep.end(), fp) == toKeep.end()){ // If the filepath isnt on the list of paths to keep, delete it
            std::filesystem::remove(fp);
        }
    }
    std::cout << "Outlier frame removal complete (" << removed << " deleted)" << std::endl;
}