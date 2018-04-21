project(matlab)
cmake_minimum_required(VERSION 3.5)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(test_cpu_normal_add_sub src/cpu_normal_add_sub_test.cpp src/cpu_matlab.cpp)
add_executable(test_cpu_normal_mul src/cpu_normal_mul_test.cpp src/cpu_matlab.cpp)
add_executable(test_cpu_normal_trp src/cpu_normal_trp_test.cpp src/cpu_matlab.cpp)
add_executable(test_init src/init_test.cpp src/cpu_matlab.cpp)
add_executable(test_cpu_sparse_add src/cpu_sparse_add_test.cpp src/cpu_matlab.cpp)
add_executable(test_validation_check src/validation_check_test.cpp src/cpu_matlab.cpp)
add_library(cpu_matlab SHARED src/cpu_matlab.cpp)

link_directories(${OpenCV_LIBRARY_DIRS})

target_link_libraries(test_cpu_normal_add_sub ${OpenCV_LIBS})
target_link_libraries(test_cpu_normal_mul ${OpenCV_LIBS})
target_link_libraries(test_cpu_normal_trp ${OpenCV_LIBS})
target_link_libraries(test_init ${OpenCV_LIBS})
target_link_libraries(test_cpu_sparse_add ${OpenCV_LIBS})
target_link_libraries(test_validation_check ${OpenCV_LIBS})
target_link_libraries(cpu_matlab ${OpenCV_LIBS})
target_link_libraries(test_validation_check ${OpenCV_LIBS})
