#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>

#include "commonFunctions.hpp"

void deleteNearDuplicates(std::string framesFolder, float threshold){
    std::cout << "==================================================" << std::endl;
    std::cout << "Removing (near) duplicate frames...." << std::endl;
    std::cout << "Performing validation..." << std::endl;
    // Check framesFolder exists
    if(!folderExists(framesFolder)){return;}

    // Get the list of files in the framesFolder
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);
    
    // Perform the actual calculations:
    std::cout << "Performing histogram analysis and frame removal..." << std::endl;
    std::vector<std::string> toDelete = getSimilarImagePaths(framesFolder, threshold); // Get the images which are too similar to at least one other image
    for(auto fp : toDelete){
        std::filesystem::remove(fp);
    }
    std::cout << "Duplicate frame removal complete (" << toDelete.size() << " deleted)" << std::endl;
}
