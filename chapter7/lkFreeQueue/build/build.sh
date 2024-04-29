!/bin/sh

cmake ..
# cmake  -DCMAKE_CXX_FLAGS="-fsanitize=address" ..
make
