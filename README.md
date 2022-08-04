# Vid2Photogrammetry
Software to process videos into an image sequence optimised for use with photogrammetry software. 
A-level computer science project

## Proposed features:
* Extract n frames from any input video into an output folder
* Logical naming of output frames
* Resizing extracted frames
* Deleting unacceptably blurry extracted frames
* Resizing of extracted frames
* Denoising of extracted frames
* Removal of "outlier" extracted frames (frames where something is covering the camera, for example)
* Removal of duplicate (or very near duplicate) extracted frames
* Easy to use GUI

## Compiling:
### Arch linux:
```
pacman -Syu
pacman -S git cmake opencv python
pip install pyqt5
git clone --recusive https://github.com/LJ3D/Vid2Photogrammetry.git
cd Vid2Photogrammetry
./build.sh
(OPTIONAL) ./pyinstaller.sh
```
### Other distros:
You will figure it out, just replace pacman with whatever your package manager is
### Windows:
Its not fuckign worth it.
See https://github.com/LJ3D/Vid2Photogrammetry/issues/8 for some info
### Mac:
lol
