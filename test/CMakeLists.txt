cmake_minimum_required (VERSION 3.5)

project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -g -pthread")

set(CMAKE_CXX_STANDARD 17)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${source_files})

#find_package(Threads REQUIRED)

#target_link_libraries(test ${CMAKE_THREAD_LIBS_INIT} atomic)