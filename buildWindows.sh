#!/bin/bash
mkdir libVid2Photogrammetry/build/
cd libVid2Photogrammetry/build/
cmake ..
cmake --build . --config Release
cp vid2photogrammetry.cp* ../../GUI/
