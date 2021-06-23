cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(lab_01)
add_definitions(-Wall -O3)
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}  "main_data_time.cpp" "data_time.cpp" "data_time.h"
                                "main_new_integer.cpp" "new_integer.cpp" "new_integer.h"
                                "main_Adam_time.cpp" "Adam_time.cpp" "Adam_time.h"
                                "main_spare_matrix.cpp" "spare_matrix.cpp" "spare_matrix.h"
                                )

