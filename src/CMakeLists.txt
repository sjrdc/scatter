
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

if (WIN32)
  include_directories(D:/fftw/fftw-3.3.5-dll32)
  set(fftwf D:/fftw/fftw-3.3.5-dll32/libfftw3f-3.a)
else ()
  set(fftwf fftw3f)
endif()
  
add_executable(scatterplot
  main.cpp
  MainWindow.cpp
  ScatterWindow.cpp
  PSFWindow.cpp
  ScatterPlot.cpp
  ImageDisplay.cpp
  )

target_link_libraries(scatterplot Qt5::Widgets ${QWT_LIBRARY} ${fftwf})


