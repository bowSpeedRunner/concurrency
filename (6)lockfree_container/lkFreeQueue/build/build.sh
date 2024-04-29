!/bin/sh

cmake ..
# cmake  -DCMAKE_CXX_FLAGS="-fsanitize=address" ..
make
rm -rf CMakeFiles
rm -f CMakeCache.txt
rm -f Makefile
rm -f cmake_install.cmake