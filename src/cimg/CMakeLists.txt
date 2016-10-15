
add_executable(scatter
  scatter.cpp
  Point2D.cpp
  DataArray.cpp)

if (UNIX)
  target_link_libraries(scatter pthread X11)
endif()

