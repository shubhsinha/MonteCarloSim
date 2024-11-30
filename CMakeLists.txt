cmake_minimum_required(VERSION 3.10)
project(MonteCarloSim)

# Set the C++ standard to C++11 or newer
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the include directories for the project
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/imgui)
include_directories(${PROJECT_SOURCE_DIR}/src/include/glad)  # Include directory for glad.h

# Find the source files in their respective folders
file(GLOB PARTICLE_SRC "${PROJECT_SOURCE_DIR}/src/simulation/Particle.cpp")
file(GLOB BOX_SRC "${PROJECT_SOURCE_DIR}/src/simulation/Box.cpp")
file(GLOB SIMULATION_SRC "${PROJECT_SOURCE_DIR}/src/simulation/Simulation.cpp")
file(GLOB RENDERER_SRC "${PROJECT_SOURCE_DIR}/src/rendering/Renderer.cpp")
file(GLOB MAIN_SRC "${PROJECT_SOURCE_DIR}/src/main.cpp")
file(GLOB COLORUTILS_SRC "${PROJECT_SOURCE_DIR}/src/ColorUtils.cpp")  # ColorUtils source file

# Glad source file for OpenGL loader
set(GLAD_SRC "${PROJECT_SOURCE_DIR}/src/glad.c")  # Correct location of glad.c

# List of all source files to be compiled
set(SOURCES
    ${PARTICLE_SRC}
    ${BOX_SRC}
    ${SIMULATION_SRC}
    ${RENDERER_SRC}
    ${MAIN_SRC}
    ${GLAD_SRC}
    ${COLORUTILS_SRC}  # Include ColorUtils.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
)

# Find necessary packages like OpenGL and GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Define executable
add_executable(MonteCarloSim ${SOURCES})

# Link the libraries in the correct order
target_link_libraries(MonteCarloSim ${OPENGL_LIBRARIES} glfw)
