#include <opencv2/opencv.hpp>

#include <string.h>

void extractFrames(std::string inputPath, std::string outputPath, std::string outputName, int frameCount){
    // Input validation goes here - doesnt exist for now

    // Create a VideoCapture object and open the input file
    cv::VideoCapture cap(inputPath);
    // Check if the file was opened successfully
    if(!cap.isOpened()){
        std::cout << "Error opening video file" << std::endl;
        return;
    }
    // Get the total number of frames in the video file
    int totalFrames = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);
    // Calculate the step size for the frame extraction with target frameCount
    int stepSize = (int)ceil((double)totalFrames / (double)frameCount);

    // Read through the video file, stepping stepSize frames at a time
    cv::Mat temp;
    for(int i = 0; i < frameCount; i++){
        // Set the videocapture frame to stepSize * i
        cap.set(cv::CAP_PROP_POS_FRAMES, stepSize * i);
        // Read the frame from the video file
        cap.read(temp);
        // Write the frame to the output file
        cv::imwrite(outputPath + outputName + std::to_string(i) + ".png", temp);
    }

}