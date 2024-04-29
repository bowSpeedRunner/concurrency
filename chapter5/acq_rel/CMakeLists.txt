cmake_minimum_required (VERSION 3.5)

project(acq_rel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread")

set(CMAKE_CXX_STANDARD 17)

set(soure_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${soure_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${source_files})