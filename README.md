# Voxel-Engine

[![Build Status](https://travis-ci.com/TheSpyGeek/VoxelEngine.svg?branch=master)](https://travis-ci.com/TheSpyGeek/VoxelEngine)

Voxel-Engine is a WIP game engine specialized for voxel rendering. It is made by 2 students to learn the process of creating a game engine

![Voxel engine](ressources/demo.gif)

![terrain_1](.assets/terrain_1-1577640144395.png)

#### Features

###### Change transform

* Change position
* Change orientation
* Change scale
* Animate orientation

###### Change tools position

* Change camera position, fov, orientation
* Change light position

###### Display

* Activate/Deactivate display in wire frame


#### How to clone

```git clone --recursive https://github.com/TheSpyGeek/ImGUITemplate.git```

#### Build

##### On Linux

Dependencies :

```sudo apt-get install -y build-essential cmake xorg-dev libgl1-mesa-dev libfreetype6-dev```

To build :

```mkdir build && cd build && cmake .. && make```

##### On Windows

Dependencies :

* [Mingw](https://sourceforge.net/projects/mingw-w64/)
* [Cmake](https://cmake.org/download/)

To build :

* Create a directory ```build```
* Run ```Cmake```
* Configure with ```Mingw Makefile```
* Run ```mingw64```
* Go to ```build``` directory
* Compile with ```mingw32-make```

##### On MAC OSX

Should work

#### Resources

* https://sonarlearning.co.uk/coursepage.php?topic=game&course=ext-bb-3d-ged
* https://www.3dgep.com/courses/
* https://github.com/nothings/stb
* https://jheer.github.io/barnes-hut/
* https://www.youtube.com/watch?v=BP6NxVxDQIs
* https://community.khronos.org/t/how-to-draw-one-line-on-top-of-another-in-opengl-without-z-fighting/68922
* Free look camera : https://gamedev.stackexchange.com/questions/60266/create-a-fly-camera-with-lookat
* Third person camera : https://www.youtube.com/watch?v=PoxDDZmctnU&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP&index=19
* Procedural generation : https://www.youtube.com/watch?v=wbpMiKiSKm8
