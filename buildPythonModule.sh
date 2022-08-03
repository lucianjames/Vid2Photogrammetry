#!/bin/bash
mkdir libVid2Photogrammetry/build/
cmake libVid2Photogrammetry/
cmake --build libVid2Photogrammetry/build
cp libVid2Photogrammetry/build/vid2photogrammetry.cpython-* GUI/
