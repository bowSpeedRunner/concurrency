cmake_minimum_required (VERSION 3.5)

project(lock_free_queue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g -fsanitize=address")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${source_files})

find_package(Threads REQUIRED)

target_link_libraries(lock_free_queue ${CMAKE_THREAD_LIBS_INIT} atomic)

