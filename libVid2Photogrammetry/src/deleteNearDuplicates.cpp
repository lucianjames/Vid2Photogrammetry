#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>

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

void deleteNearDuplicates(std::string framesFolder){
    // Get the list of files in the framesFolder
    std::vector<std::string> files;
    for(auto& p : std::filesystem::directory_iterator(framesFolder)){
        files.push_back(p.path().string());
    }
    
    // This is disgustingly O(n^2).
    // Could be optimised a bit though.
    for(auto fp : files){
        cv::Mat img1 = cv::imread(fp);
        cv::Mat img1_hist = calcHistNorm(img1);
        for(auto fp2 : files){
            cv::Mat img2 = cv::imread(fp2);
            cv::Mat img2_hist = calcHistNorm(img2);
            std::cout << fp << " | " << fp2 << std::endl;
            std::cout << cv::compareHist(img1_hist, img2_hist, cv::HISTCMP_BHATTACHARYYA) << std::endl;
        }
    }
}