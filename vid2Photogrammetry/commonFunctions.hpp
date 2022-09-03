#pragma once

/* 
This file stores functions which are used in at least two of the other .hpp files 
*/

#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

// Returns boolean value indicating whether a folder exists, if it does not it also prints an error message
bool folderExists(std::string framesFolder){
    if(!std::filesystem::exists(framesFolder)){
        std::cout << "ERR: folder does not exist" << std::endl;
        return false;
    }
    return true;
}

// Returns a vector of filepaths to all files in a folder
std::vector<std::string> getFilepathsInFolder(std::string folderPath){
    std::vector<std::string> files;
    for(auto& p : std::filesystem::directory_iterator(folderPath)){
        files.push_back(p.path().string());
    }
    return files;
}

// Returns the normalized histogram of an image
cv::Mat calcHistNorm(const cv::Mat& input){
    cv::Mat hist; // Histogram image
    cv::cvtColor(input, input, cv::COLOR_BGR2HSV); // Convert to HSV
    // The following variables are used to calculate the histogram:
    int h_bins = 50, s_bins = 60; 
    int histSize[] = {h_bins, s_bins};
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int channels[] = {0, 1};
    cv::calcHist(&input, 1, channels, cv::Mat(), hist, 2, histSize, ranges, true, false); // Calculate histogram
    cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat()); // Normalize the histogram
    return hist;
}

// Takes a folder path and threshold as input, and returns a vector of strings containing the paths of images which are similar enough to at least 1 other image in the folder
std::vector<std::string> getSimilarImagePaths(std::string framesFolder, float threshold){
    std::cout << "Using HISTCMP_BHATTACHARYYA" << std::endl;
    std::vector<std::string> files = getFilepathsInFolder(framesFolder);
    std::vector<std::string> similarFrames; // Stores the frames which are similar enough to at least one other frame to be kept
    std::unordered_map<std::string, bool> alreadyCompared; // Used to avoid doing the same comparison (or the same comparison the other way around) multiple times.
    for(auto fp : files){
        cv::Mat fp1hist = calcHistNorm(cv::imread(fp)); // Calculate the normalised histogram of the current frame
        alreadyCompared[fp+fp] = true; // Adding this to the map means that we dont need to compare this frame to itself
        for(auto fp2 : files){ // Compare the current frame to every other frame
            if(!(alreadyCompared[fp+fp2]) && !(alreadyCompared[fp2+fp])){ // If we havent already compared fp1hist to fp2hist or vice versa:
                float unSimilarity = cv::compareHist(fp1hist, calcHistNorm(cv::imread(fp2)), cv::HISTCMP_BHATTACHARYYA); // Calculate the (un)similarity between the two frames
                if((unSimilarity < threshold) && (std::find(similarFrames.begin(), similarFrames.end(), fp2) == similarFrames.end())){ // If the frames are similar enough and fp2 isnt already in the list of similar frames:
                    similarFrames.push_back(fp2); // Add fp2 to the list of similar frames
                }
                alreadyCompared[fp+fp2] = true; // Add this comparison to the map so we dont need to do it again
            }
        }
    }
    return similarFrames;
}