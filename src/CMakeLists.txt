

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


