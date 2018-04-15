project(matlab)
cmake_minimum_required(VERSION 3.5)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cpu_matlab_test src/cpu_main.cpp)
add_library(cpu_matlab SHARED src/cpu_matlab.cpp)

link_directories(${OpenCV_LIBRARY_DIRS})

target_link_libraries(cpu_matlab_test ${OpenCV_LIBS})
target_link_libraries(cpu_matlab ${OpenCV_LIBS})
