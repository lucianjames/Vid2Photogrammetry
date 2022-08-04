#!/bin/bash
mkdir pybuild
cd pybuild
mkdir dist
cp ../GUI/*.ui .
python3 -m PyInstaller --onefile --add-data '*.ui:.' ../GUI/vid2photogrammetryGUI.py --noconfirm
