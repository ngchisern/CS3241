cmake_minimum_required(VERSION 3.23)
project(e0550524_lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(e0550524_lab1
        main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(e0550524_lab1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})