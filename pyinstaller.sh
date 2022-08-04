#!/bin/bash
mkdir pybuild
cd pybuild
mkdir dist
cp ../GUI/*.ui dist/
python3 -m PyInstaller --onefile ../GUI/vid2photogrammetryGUI.py --noconfirm
