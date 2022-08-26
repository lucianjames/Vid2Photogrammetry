#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>

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

void deleteNearDuplicates(std::string framesFolder, float threshold){
    std::cout << "==================================================" << std::endl;
    std::cout << "Removing (near) duplicate frames...." << std::endl;
    std::cout << "Performing validation..." << std::endl;
    // Check framesFolder exists
    if(!std::filesystem::exists(framesFolder)){
        std::cout << "ERR: folder does not exist" << std::endl;
        return;
    }
    // Get the list of files in the framesFolder
    std::vector<std::string> files;
    for(auto& p : std::filesystem::directory_iterator(framesFolder)){
        files.push_back(p.path().string());
    }
    
    // This is disgustingly O(n^2).
    // Could be optimised a bit though.
    std::cout << "Performing histogram analysis and frame removal..." << std::endl;
    std::vector<std::string> toDelete; // Delete after loop to avoid having to account for fucky stuff.
    std::unordered_map<std::string, bool> alreadyCompared;
    for(auto fp : files){
        cv::Mat img1 = cv::imread(fp);
        cv::Mat img1_hist = calcHistNorm(img1);
        alreadyCompared[fp+fp] = true;
        for(auto fp2 : files){
            std::cout << alreadyCompared[fp+fp2] << std::endl;
            if(!(alreadyCompared[fp+fp2]) || !(alreadyCompared[fp2+fp])){
                cv::Mat img2 = cv::imread(fp2);
                cv::Mat img2_hist = calcHistNorm(img2);
                std::cout << fp << " | " << fp2 << std::endl;
                float unSimilarity = cv::compareHist(img1_hist, img2_hist, cv::HISTCMP_BHATTACHARYYA);
                std::cout << unSimilarity << std::endl;
                if(unSimilarity < threshold){
                    toDelete.push_back(fp2);
                    std::cout << fp << " and " << fp2 << " ARE TOO SIMILAR APPARENTLY!LRYTUYT!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                }
                alreadyCompared[fp+fp2] = true;
            }
        }
    }
    int removed = toDelete.size();
    for(auto fp : toDelete){
        std::filesystem::remove(fp);
    }
    std::cout << "Duplicate frame removal complete (" << removed << " deleted)" << std::endl;
}