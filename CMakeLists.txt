cmake_minimum_required(VERSION 2.6)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
  # TODO(amitp): I don't know how to set this properly with add_compile_options
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2")
  set(SDL2_LIBRARIES "-s USE_SDL=2")
  set(SDL2_IMAGE_LIBRARIES "-s USE_SDL_IMAGE=2")
else ()
  if (WIN32)
    find_package(GLEW REQUIRED glew)
  endif ()
  find_package(SDL2 REQUIRED sdl2)
  find_package(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
endif ()

add_executable(main main.cpp glwrappers.cpp window.cpp atlas.cpp font.cpp render-sprites.cpp render-surface.cpp render-imgui.cpp imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_demo.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 11)
include_directories(${SDL2_INCLUDE_DIR})

if (WIN32)
  include_directories(${GLEW_INCLUDE_DIR})
  target_link_libraries(main ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${GLEW_LIBRARY})
else ()
  target_link_libraries(main ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
endif ()
