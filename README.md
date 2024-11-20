# Monte Carlo Simulation Project

This project is a Monte Carlo Simulation written in C++ with an interactive user interface built using ImGui. The simulation models the behavior of particles within a box and allows for energy calculations using the Lennard-Jones potential. It includes options for particle color-coding based on different physical properties, like temperature or energy.

## Features

- **Interactive User Interface**: Built using ImGui, providing easy access to change parameters such as particle count, temperature, and number of steps.
- **Particle Color-Coding**: Use colors to represent various properties like energy or temperature, providing a visual understanding of the state of the system.
- **Real-Time Visualization**: Render particles in a 3D space with OpenGL, showing their movement and behavior as the simulation progresses.
- **Multiple Simulation Modes**: Supports different configurations for particle interactions, including the Lennard-Jones potential.
- **Save and Load Functionality**: Save particle positions at specific intervals and load configurations for further analysis.

## Project Structure

```
MONTECARLOSIM/
├── build/                        # Build files (compiled output, build cache, etc.)
├── imgui/                        # ImGui library and backends
├── src/                          # Main source code directory
│   ├── include/                  # Project-specific headers
│   │   ├── Particle.h
│   │   ├── Box.h
│   │   ├── Simulation.h
│   │   ├── Renderer.h
│   │   ├── UI.h
│   │   └── glad/                 # Glad loader
│   │   └── KHR/                  # Khronos headers used by glad
│   ├── simulation/               # Simulation logic source files
│   │   ├── Particle.cpp
│   │   ├── Box.cpp
│   │   ├── Simulation.cpp
│   ├── rendering/                # Rendering code
│   │   ├── Renderer.cpp
│   ├── ui/                       # UI source files for ImGui
│   │   ├── UI.cpp
│   ├── main.cpp                  # Entry point for the program
│   └── CMakeLists.txt            # Build instructions for CMake (src-specific)
├── CMakeLists.txt                # Main CMakeLists for the project
└── .vscode/                      # Configuration files for VS Code (tasks, settings, etc.)
```

## Dependencies

- **GLFW**: Used for creating windows and managing input.
- **Glad**: OpenGL loader to manage OpenGL function calls.
- **ImGui**: GUI framework for user interface.
- **OpenGL**: Rendering the particles in real-time.
- **CMake**: Build system generator.

## Installation and Setup

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/yourusername/MonteCarloSim.git
   cd MonteCarloSim
   ```
2. **Build the Project**:
   - Ensure CMake is installed on your system.
   - Create a `build` directory and compile the project:
     ```sh
     mkdir build
     cd build
     cmake ..
     make
     ```
3. **Run the Simulation**:
   - Run the executable:
     ```sh
     ./MonteCarloSim
     ```

## Usage

- **Initialize the Simulation**: Adjust parameters such as the number of particles, temperature, and the number of simulation steps using the provided ImGui interface.
- **Run the Simulation**: Click "Run Simulation" to begin.
- **Save Data**: Save particle states at specific intervals for later analysis.
- **Visualization**: The particles are rendered in 3D, and their color changes depending on the selected color mode (e.g., energy or temperature).

## Controls
- **Adjust Parameters**: Use sliders and input boxes to modify parameters.
- **Toggle Color Modes**: Select color modes to visualize different properties of particles.
- **Pause and Resume**: Pause the simulation to analyze the state of the system at any given time.

## Future Improvements
- **Multithreading**: Implement parallel processing for faster simulation of large systems.
- **GPU Acceleration**: Use CUDA/OpenCL to accelerate particle interactions using the GPU.
- **More Interaction Potentials**: Add support for other potentials beyond Lennard-Jones.
- **Custom Scripting**: Add a Python scripting interface for more advanced user-defined behaviors.

## Contributing
Contributions are welcome! If you have ideas for new features, optimizations, or find a bug, feel free to open an issue or a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact
For any questions, please contact:
- **Your Name** - [your.email@example.com](mailto:your.email@example.com)
- **GitHub** - [https://github.com/yourusername](https://github.com/yourusername)

---

Happy Simulating!

