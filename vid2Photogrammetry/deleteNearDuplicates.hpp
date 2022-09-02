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
    if(!framesFolderExists(framesFolder)){return;}

    // Get the list of files in the framesFolder
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);
    
    // Basically O(n^2), but ive optimised it a little bit
    std::cout << "Performing histogram analysis and frame removal..." << std::endl;
    std::vector<std::string> toDelete = getSimilarImagePaths(framesFolder, threshold);
    int removed = toDelete.size();
    for(auto fp : toDelete){
        std::filesystem::remove(fp);
    }
    std::cout << "Duplicate frame removal complete (" << removed << " deleted)" << std::endl;
}
