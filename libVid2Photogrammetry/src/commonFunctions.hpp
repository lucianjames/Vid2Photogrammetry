#pragma once

// This file stores functions which are used in at least two of the other .hpp files

#include <string>
#include <vector>

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