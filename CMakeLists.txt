cmake_minimum_required(VERSION 3.2.2)

project(FEM)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

INCLUDE_DIRECTORIES ( "/gpfs/runtime/opt/eigen/3.2.1/include/eigen3" )

add_library(FEM
        inc/algorithm.h
      	inc/algorithm.cpp
        inc/algorithm2D.h
        inc/algorithm2D.cpp
        inc/algorithm3D.h
        inc/algorithm3D.cpp
	      inc/print_result.cpp
        inc/read_input.cpp
        inc/print_result.h
        inc/read_input.h
        inc/convergence.h
        inc/convergence.cpp
)
target_include_directories(FEM PUBLIC inc)

add_executable(main src/main.cpp)
target_link_libraries(main FEM)


# Require MPI for this project:
find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(MPI_INCLUDE_PATH)
target_link_libraries(FEM ${MPI_LIBRARIES})


# require openmp for this project
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
