cmake_minimum_required(VERSION 2.6)
project(KitsuneEngine)
set(KitsuneEngine_VERSION_MAJOR 0)
set(KitsuneEngine_VERSION_MINOR 1)

# compile flags
add_compile_options(-g3 -no-pie -std=c++14)

# adding links to dynamic libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Lua 5.2 REQUIRED)
find_package(SDL2 REQUIRED)

# header directories
include_directories(render)
include_directories(node)
include_directories(node/physics)
include_directories(node2d)

# project files
set(SOURCES main.cpp
display.cpp game.cpp input.cpp 
render/mesh.cpp render/shader.cpp render/texture.cpp
node/node.cpp 
node/physics/staticbody.cpp node/physics/kinematicbody.cpp
node2d/node2d.cpp node2d/sprite.cpp
)

# executable game
add_executable(KE ${SOURCES})
target_link_libraries(KE ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} ${LUA_LIBRARIES} ${SDL2_LIBRARIES})

