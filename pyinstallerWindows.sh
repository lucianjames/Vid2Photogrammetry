#!/bin/bash
mkdir pybuild
cd pybuild
mkdir dist
cp ../GUI/*.ui .
cp ../GUI/*.dll .
python3 -m PyInstaller --onefile --add-binary '*.dll;.' --add-data '*.ui;.' ../GUI/vid2photogrammetryGUI.py --noconfirm
