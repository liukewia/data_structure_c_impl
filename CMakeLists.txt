cmake_minimum_required(VERSION 3.14)
project(data_structure_c_impl C)

#set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD GNU99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -O1 -g use-after-free.c -o use-after-free out-of-bounds")

add_subdirectory(Status)
add_subdirectory(CourseBook)