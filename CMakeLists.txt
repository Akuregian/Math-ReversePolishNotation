cmake_minimum_required(VERSION 3.1)

project(Math)

file(GLOB SOURCES
    "source/Declaration/*.cpp" 
    "source/Header/*.h" )

add_executable(${PROJECT_NAME} ${SOURCES})
