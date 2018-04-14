project(matlab)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cpu_matlab src/cpu_matlab.cpp)

link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(cpu_matlab ${OpenCV_LIBS})
