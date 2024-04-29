cmake_minimum_required (VERSION 3.5)

project(auto_machine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(CMAKE_CXX_STANDARD 17)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${source_files})

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} atomic)