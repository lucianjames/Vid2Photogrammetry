#include <opencv2/opencv.hpp>

#include <string>
#include <filesystem>

int numDigits(int number){ // Gets the number of digits in an int (for example, inputting 123 returns 3)
    int digits = 0;
    while(number){
        number /= 10;
        digits++;
    }
    return digits;
}

void extractFrames(std::string inputPath, std::string outputPath, std::string outputName, std::string outputExtension, int frameCount){
    std::cout << "==================================================" << std::endl;
    std::cout << "Starting frame extraction...." << std::endl;
    std::cout << "Performing validation..." << std::endl;
    int numDigitsInput = numDigits(frameCount); // Required for the file name

    // Check frameCount is above 0
    if(frameCount <= 0){
        std::cout << "ERR: FrameCount =< 0" << std::endl;
        return;
    }

    // Check inputPath is an existing file, of the supported file types
    if(!std::filesystem::exists(inputPath)){
        std::cout << "ERR: Input file does not exist" << std::endl;
        return;
    }
    
    // Check outputPath is an existing directory
    if(!std::filesystem::exists(outputPath)){
        std::cout << "ERR: Output directory does not exist" << std::endl;
        return;
    }

    // Check outputName is no longer than 64 characters (Avoid path length issues) - This number is chosen arbitrarily tbh
    if(outputName.length() > 64){
        std::cout << "ERR: Output file name is too long (Could cause path length issues)" << std::endl;
        return;
    }

    // Create a VideoCapture object and open the input file
    std::cout << "Creating cv::VideoCapture..." << std::endl;
    cv::VideoCapture cap(inputPath);
    if(!cap.isOpened()){
        std::cout << "ERR: Error opening video file" << std::endl;
        return;
    }

    // Get the total number of frames in the video file
    int totalFrames = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);
    std::cout << "Input file contains " << totalFrames << " frames" << std::endl;

    // Check if the number of frames to extract is greater than the total number of frames in the video file
    if(frameCount > totalFrames){
        std::cout << "ERR: Number of frames to extract is greater than the total number of frames in the video file" << std::endl;
        return;
    }

    // Calculate the step size for the frame extraction with target frameCount
    int stepSize = std::floor(totalFrames / frameCount);

    // Read through the video file, stepping stepSize frames at a time
    cv::Mat temp;
    std::cout << "Extracting and writing " << frameCount << " images to disk..." << std::endl;
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
            std::cout << "ERR: Error writing " << outputPath + "/" + outputName + std::to_string(i) + "." + outputExtension + " | " << e.what() << std::endl;
            return;
        }
    }
    std::cout << "Frame extraction complete" << std::endl;
}
