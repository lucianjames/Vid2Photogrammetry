#!/bin/bash
mkdir libVid2Photogrammetry/build/
cd libVid2Photogrammetry/build/
cmake ..
cmake --build .
cp vid2photogrammetry.cpython-* ../../GUI/
cd ../../
mkdir pybuild
cd pybuild
python3 -m PyInstaller ../GUI/vid2photogrammetryGUI.py --noconfirm
cp ../GUI/*.ui dist/vid2photogrammetryGUI/
