
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

if (UNIX)
  # since qwt6-dev relies on qt4
  find_package(Qt4)
else ()
endif()

find_package(Qwt REQUIRED)
include_directories(${QWT_INCLUDE_DIRS})

add_executable(scatterplot
  main.cpp
  mainwindow.cpp
  plot.cpp
  )

target_link_libraries(scatterplot Qt4::QtGui ${QWT_LIBRARY})


