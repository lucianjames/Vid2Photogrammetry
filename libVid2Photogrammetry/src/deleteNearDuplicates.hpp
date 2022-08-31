#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>

#include "commonFunctions.hpp"

// Takes a folder path and threshold as input, and returns a vector of strings containing the paths of images which are similar enough to at least 1 other image in the folder
std::vector<std::string> getSimilarImagePaths(std::string framesFolder, float threshold){
    std::cout << "Using HISTCMP_BHATTACHARYYA" << std::endl;
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);
    std::vector<std::string> similarFrames; // Stores the frames which are similar enough to at least one other frame to be kept
    std::unordered_map<std::string, bool> alreadyCompared; // Used to avoid doing the same comparison (or the same comparison the other way around) multiple times.
    for(auto fp : files){
        cv::Mat fp1hist = calcHistNorm(cv::imread(fp));
        alreadyCompared[fp+fp] = true;
        for(auto fp2 : files){
            if(!(alreadyCompared[fp+fp2]) && !(alreadyCompared[fp2+fp])){
                float unSimilarity = cv::compareHist(fp1hist, calcHistNorm(cv::imread(fp2)), cv::HISTCMP_BHATTACHARYYA);
                if((unSimilarity < threshold) && (std::find(similarFrames.begin(), similarFrames.end(), fp2) == similarFrames.end())){
                    similarFrames.push_back(fp2);
                }
                alreadyCompared[fp+fp2] = true;
            }
        }
    }
    return similarFrames;
}

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