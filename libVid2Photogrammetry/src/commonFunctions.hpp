#pragma once

// This file stores functions which are used in at least two of the other .hpp files

#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

bool framesFolderExists(std::string framesFolder){
    if(!std::filesystem::exists(framesFolder)){
        std::cout << "ERR: folder does not exist" << std::endl;
        return false;
    }
    return true;
}

std::vector<std::string> getFilepathsInFolder(std::string folderPath){
    std::vector<std::string> files;
    for(auto& p : std::filesystem::directory_iterator(folderPath)){
        files.push_back(p.path().string());
    }
    return files;
}

cv::Mat calcHistNorm(cv::Mat input){
    cv::Mat hist;
    // Convert to HSV
    cv::cvtColor(input, input, cv::COLOR_BGR2HSV);
    int h_bins = 50, s_bins = 60;
    int histSize[] = {h_bins, s_bins};
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int channels[] = {0, 1};
    cv::calcHist(&input, 1, channels, cv::Mat(), hist, 2, histSize, ranges, true, false);
    cv::normalize(hist, hist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    return hist;
}

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