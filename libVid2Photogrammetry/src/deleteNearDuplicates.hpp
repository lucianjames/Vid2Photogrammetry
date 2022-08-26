#include <pybind11/pybind11.h>

#include <string>

// This is going to be O(n^2) :(
void deleteNearDuplicates(std::string framesFolder, float threshold);