cmake_minimum_required(VERSION 3.10)
project(MonteCarloSim)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find packages for GLFW and OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# If CMake has trouble finding glfw3, you can help it by adding the following line:
# list(APPEND CMAKE_PREFIX_PATH "C:/msys64/mingw64")

# Include directories for Dear ImGui, GLAD, and backends
include_directories(imgui imgui/backends src/include)  # Add src/include for GLAD headers

# Add source files for Dear ImGui and GLAD
set(IMGUI_FILES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

# Add glad.c to the source files
set(GLAD_SRC src/glad.c)

# Add executable
add_executable(MonteCarloSim src/main.cpp ${IMGUI_FILES} ${GLAD_SRC})

# Link libraries
target_link_libraries(MonteCarloSim glfw OpenGL::GL)
