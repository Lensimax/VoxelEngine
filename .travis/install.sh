#!/bin/bash

if [ $TRAVIS_OS_NAME = 'linux' ]; then
    sudo apt-get update -qq
    sudo apt-get install -y build-essential cmake xorg-dev libgl1-mesa-dev libfreetype6-dev


  
else
    # Install some custom requirements on Linux
fi

mkdir build
cd build
cmake ..
