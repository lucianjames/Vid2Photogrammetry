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

## Compiling
### Arch linux:
```
pacman -Syu
pacman -S opencv cmake
git clone https://github.com/LJ3D/Vid2Photogrammetry.git
cv Vid2Photogrammetry
mkdir build
cd build
cmake ..
cmake --build .
```
### Windows:
Lol

### Mac:
Cry about it
