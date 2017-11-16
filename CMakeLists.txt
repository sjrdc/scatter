cmake_minimum_required(VERSION 3.0)

project(scatter)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
set(CMAKE_PREFIX_PATH "C://Qt//Qt5.8.0//5.8//msvc2015")

find_package(Qt5Widgets REQUIRED)
#find_package(Qwt REQUIRED)

add_subdirectory(src)