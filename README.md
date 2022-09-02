# Vid2Photogrammetry
Software to process videos into an image sequence optimised for use with photogrammetry software. 
A-level computer science project

## Features:
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
### Arch Linux:
1. Install deps and tools.
```pacman -Syu
pacman -S git cmake opencv qt5
```
2. Clone repository, create build folder
```
git clone https://github.com/LJ3D/Vid2Photogrammetry.git
cd Vid2Photogrammetry 
mkdir build
cd build
```
3. Run cmake
```
cmake ..
cmake --build .
```
### Other distros:
Just swap out the package manager and it should be fine

### Windows:
Why? Just use the pre-compiled binary, installing and setting up opencv, qt5, cmake, and git takes too long.
If you really want to compile it on windows though, the steps are pretty much the same but you have to mess around adding opencv and qt5 to the list of environment variables. Also have fun figuring out the DLL files :) (hint: windeployqt.exe)

### Mac:
lmao
