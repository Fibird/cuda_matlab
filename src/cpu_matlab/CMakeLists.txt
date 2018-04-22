set(LIBCPU_MATLAB_SRC matrix.cpp sparse_matrix.cpp)
add_library(cpu_matlab SHARED ${LIBCPU_MATLAB_SRC})

