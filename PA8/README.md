# PA8: Bullet 

# Group members
Made with [Matt Johnson](https://github.com/antilectual/cs480Johnson)
Made with [Alex Novotny](https://github.com/alexander-novo/cs480Novotny)

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

The project also uses [ImGUI](https://github.com/ocornut/imgui) and [JSON for Modern C++](https://github.com/nlohmann/json), both of which are already included.

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)   
   
This project uses ImageMagick++ for loading textures. We have found that there are various forms of ImageMagick++ that can conflict with each other. In order to be sure that ImageMagick++ is installed properly for this project, we recommend removing all other forms before installing the libmagick++-dev library. 
``` sudo apt-get remove *magick* ``` should handle this removal.

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev libassimp-dev libmagick++-dev
```

## Building and Running

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the ```add_custom_target``` function place

```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```

# Controls

`w,a,s,d` - Detach camera from planet and move it around  
`shift` - Move camera down  
`spacebar` - Move camera up  
`left/right` - Rotate camera

`left click` - Drag to rotate camera around object (With planet selected)   
`Scroll wheel` - Zoom in and out (With planet selected)   

**Camera Distance** - Changes how far the camera is away from the current object.  Zooms out to overhead view.
**Camera Rotation** - Rotates the camera around whatever the camera is looking at. Useful for getting out of a planet's shadow  
**Realistic/Close Scale** - Switch between the two to get realistic planet scaling (where the sun is *much* bigger than the planets and everything is very far apart) or an easier to see scale  
**Labels** - Check appropriate box to display names over planets or moons


# Command Line Parameters

## Command Usage

`Tutorial` - Will run using the default configuration of `config.json`.   
`Tutorial --help` - Pull up the help menu / command usage  
`Tutorial <config>` - Run the program with the given config file (e.g. "Tutorial config.json")     