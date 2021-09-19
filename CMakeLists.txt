# To build Makefiles, cd to build and cmake ../ -DCMAKE_LINKER=nvcc -DCMAKE_BUILD_TYPE=Release

cmake_minimum_required(VERSION 3.11)
project(XLaunch)
set(CMAKE_CXX_STANDARD 17)

# We want to be REALLY lightweight,
# so we're using X11 for graphics.
find_package(X11 REQUIRED)

# Because we're using GLOB, we need CMake 3.11.0+.
# See https://stackoverflow.com/a/62085797
file(GLOB PX_LIB_SRC "tk/impl/*.cpp")
add_library(PxTk ${PX_LIB_SRC})

include_directories(${X11_INCLUDE_DIR})
include_directories("tk/pub/")

target_link_libraries(PxTk ${X11_LIBRARIES})

# Add the sources
add_executable(XLaunch "app/main.cpp" "app/MainRenderer.cpp" "app/WordCompleter.cpp")

target_link_libraries(XLaunch PxTk)

