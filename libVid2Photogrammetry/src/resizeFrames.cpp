#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>

void resizeFrames(std::string framesFolder, unsigned int x, unsigned int y){
    // Check framesFolder exists
    if(!std::filesystem::exists(framesFolder)){
        std::cout << "Resize error: folder does not exist" << std::endl;
        return;
    }

    // Get the list of files in the framesFolder
    std::vector<std::string> files;
    for(auto& p : std::filesystem::directory_iterator(framesFolder)){
        files.push_back(p.path().string());
    }

    // Resize each frame in the framesFolder
    for(int i=0; i<files.size(); i++){
        // Load the frame
        cv::Mat frame = cv::imread(files[i]);
        if(frame.empty()){
            std::cout << "Resize error: could not load frame " << i << std::endl;
            return;
        }
        cv::resize(frame, frame, cv::Size(x, y)); // Resize the frame
        cv::imwrite(files[i], frame); // Save the frame
    }
}