#!/bin/bash
mkdir pybuild
cd pybuild
mkdir dist
cp ../GUI/*.ui .
cp ../GUI/*.dll .
cp ../GUI/icon.png .
python3 -m PyInstaller --onedir --add-binary '*.dll;.' --add-data '*.ui;.' --add-data 'icon.png;.' ../GUI/vid2photogrammetryGUI.py --noconfirm 
