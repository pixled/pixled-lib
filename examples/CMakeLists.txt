cmake_minimum_required(VERSION 3.10)

project(pixled-examples)

find_package(pixled REQUIRED)

add_subdirectory(pixled/animation)
add_subdirectory(pixled/function)
add_subdirectory(pixled/random)
