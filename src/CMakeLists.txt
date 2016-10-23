
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qwt REQUIRED)
include_directories(${QWT_INCLUDE_DIRS})

add_executable(scatterplot
  main.cpp
  MainWindow.cpp
  Plot.cpp
  )

target_link_libraries(scatterplot Qt5::Widgets ${QWT_LIBRARY})


