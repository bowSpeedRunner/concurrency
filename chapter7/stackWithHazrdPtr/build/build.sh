#!/bin/bash
cmake ..
make
rm -rf CMakeFiles
rm -f CMakeCache.txt
rm -f Makefile
rm -f cmake_install.cmake