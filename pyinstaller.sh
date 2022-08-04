#!/bin/bash
mkdir pybuild
cd pybuild
mkdir dist
cp ../GUI/*.ui .
cp ../DLLS/*.dll . # So shit works on windows
python3 -m PyInstaller --onefile --add-data '*.ui:.' --add-data '*.dll:.' ../GUI/vid2photogrammetryGUI.py --noconfirm
