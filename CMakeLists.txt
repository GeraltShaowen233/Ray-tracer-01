cmake_minimum_required(VERSION 3.0.0)

project(Raytracer VERSION 0.1.0)


add_executable(Raytracer main.cpp)

target_include_directories(Raytracer
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/asset
)

