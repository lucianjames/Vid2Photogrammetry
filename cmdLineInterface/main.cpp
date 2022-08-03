#include <iostream>

#include <vid2photogrammetry.hpp>

// Command line arguments:
// 1. Input video file path
// 2. Output directory path
// 3. Output file name
// 4. Output file extension
// 5. Number of frames to extract

int main(int argc, char *argv[]){
    // Check if the number of arguments is correct
    if(argc != 6){
        std::cout << "Usage: " << argv[0] << " <input video file path> <output directory path> <output file name> <output file extension> <number of frames to extract>" << std::endl;
        return 1;
    }

    // Extract the command line arguments
    std::string inputPath = argv[1];
    std::string outputPath = argv[2];
    std::string outputName = argv[3];
    std::string outputExtension = argv[4];
    int frameCount = std::stoi(argv[5]);

    // Extract the frames
    extractFrames(inputPath, outputPath, outputName, outputExtension, frameCount);

    return 0;
}