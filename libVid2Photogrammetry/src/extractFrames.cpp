#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>

template <class T>
int numDigits(T number) // Gets the number of digits in a number (for example, inputting 123 returns 3)
{
    int digits = 0;
    while(number){
        number /= 10;
        digits++;
    }
    return digits;
}

void extractFrames(std::string inputPath, std::string outputPath, std::string outputName, std::string outputExtension, int frameCount){
    int numDigitsInput = numDigits(frameCount); // Required for the file name

    // Check inputPath is an existing file, of the supported file types
    if(!std::filesystem::exists(inputPath)){
        std::cout << "Input file does not exist" << std::endl;
        return;
    }
    
    // Check outputPath is an existing directory
    if(!std::filesystem::exists(outputPath)){
        std::cout << "Output directory does not exist" << std::endl;
        return;
    }

    // Check outputName is no longer than 64 characters (Avoid path length issues) - This number is chosen arbitrarily tbh
    if(outputName.length() > 64){
        std::cout << "Output file name is too long (Could cause path length issues)" << std::endl;
        return;
    }

    // Create a VideoCapture object and open the input file
    cv::VideoCapture cap(inputPath);
    if(!cap.isOpened()){
        std::cout << "Error opening video file" << std::endl;
        return;
    }

    // Get the total number of frames in the video file
    int totalFrames = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);

    // Check if the number of frames to extract is greater than the total number of frames in the video file
    if(frameCount > totalFrames){
        std::cout << "Number of frames to extract is greater than the total number of frames in the video file" << std::endl;
        return;
    }

    // Calculate the step size for the frame extraction with target frameCount
    int stepSize = std::floor(totalFrames / frameCount);

    // Read through the video file, stepping stepSize frames at a time
    cv::Mat temp;
    for(int i = 0; i < frameCount; i++){
        // Set the videocapture frame to stepSize * i
        cap.set(cv::CAP_PROP_POS_FRAMES, stepSize * i);
        // Read the frame from the video file
        cap.read(temp);
        // Write the frame to the output file
        // Handle any errors that may occur
        try{
            cv::imwrite(outputPath + "/" + outputName + std::to_string(i) + "." + outputExtension, temp);
        }
        catch(cv::Exception& e){
            std::cout << "Error writing " << outputPath + "/" + outputName + std::to_string(i) + "." + outputExtension + " | " << e.what() << std::endl;
            return;
        }
    }

}
