#!/bin/bash
mkdir libVid2Photogrammetry/build/
cd libVid2Photogrammetry/build/
cmake ..
cmake --build .
cp vid2photogrammetry.cpython-* ../../GUI/
