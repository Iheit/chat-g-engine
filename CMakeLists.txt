cmake_minimum_required(VERSION 3.20)
project(Nova3D VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(NOVA3D_BUILD_DEMO "Build renderer demo" ON)

add_library(nova3d STATIC
    src/core/Math.cpp
    src/render/Renderer.cpp
    src/render/OpenGLRenderer.cpp
    src/platform/Window.cpp
)
target_include_directories(nova3d PUBLIC include)
target_compile_definitions(nova3d PUBLIC NOVA3D_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

if(WIN32)
  target_compile_definitions(nova3d PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
  target_link_libraries(nova3d PRIVATE opengl32 gdi32 user32)
elseif(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  find_package(OpenGL REQUIRED)
  target_link_libraries(nova3d PRIVATE X11::X11 OpenGL::GL dl)
endif()

if(MSVC)
  target_compile_options(nova3d PRIVATE /W4 /permissive- /EHsc)
else()
  target_compile_options(nova3d PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(NOVA3D_BUILD_DEMO)
  add_executable(nova3d_renderer_demo examples/renderer_demo/main.cpp)
  target_link_libraries(nova3d_renderer_demo PRIVATE nova3d)
endif()

install(TARGETS nova3d ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY assets/ DESTINATION share/nova3d/assets)
