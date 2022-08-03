#include <iostream>

#include <vid2photogrammetry.hpp>

// Command line arguments:
// 1. Input video file path
// 2. Output directory path
// 3. Output file name
// 4. Number of frames to extract

int main(int argc, char *argv[]){
    // Check if the number of arguments is correct
    if(argc != 5){
        std::cout << "Usage: " << argv[0] << " <input video file path> <output directory path> <output file name> <number of frames to extract>" << std::endl;
        return 1;
    }

    // Extract the command line arguments
    std::string inputPath = argv[1];
    std::string outputPath = argv[2];
    std::string outputName = argv[3];
    int frameCount = std::stoi(argv[4]);

    // Extract the frames
    extractFrames(inputPath, outputPath, outputName, frameCount);

    return 0;
}