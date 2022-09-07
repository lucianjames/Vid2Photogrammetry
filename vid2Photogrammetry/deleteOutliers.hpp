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
    if(!folderExists(framesFolder)){return;}

    // Get the list of files in the framesFolder
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);

    // Perform the actual calculations:    
    std::cout << "Performing histogram analysis and frame removal..." << std::endl;
    std::vector<std::string> toKeep = getSimilarImagePaths(framesFolder, 1-threshold); // Get the images that are not outliers (similar to at least one other image, not a perfect system really but it works) 
    for(auto fp : files){
        if(std::find(toKeep.begin(), toKeep.end(), fp) == toKeep.end()){ // If the filepath isnt on the list of paths to keep, delete it
            std::filesystem::remove(fp);
        }
    }
    std::cout << "Outlier frame removal complete (" << files.size() - toKeep.size() << " deleted)" << std::endl;
}
