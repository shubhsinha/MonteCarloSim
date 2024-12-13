#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Simulation.h"
#include "Renderer.h"
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

void createMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) {
                // Action for New
                std::cout << "New File selected\n";
            }
            if (ImGui::MenuItem("Open")) {
                // Action for Open
                std::cout << "Open File selected\n";
            }
            if (ImGui::MenuItem("Save")) {
                // Action for Save
                std::cout << "Save File selected\n";
            }
            if (ImGui::MenuItem("Print")) {
                // Action for Print
                std::cout << "Print selected\n";
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Cut")) {
                // Action for Cut
                std::cout << "Cut selected\n";
            }
            if (ImGui::MenuItem("Copy")) {
                // Action for Copy
                std::cout << "Copy selected\n";
            }
            if (ImGui::MenuItem("Paste")) {
                // Action for Paste
                std::cout << "Paste selected\n";
            }
            if (ImGui::MenuItem("Undo")) {
                // Action for Undo
                std::cout << "Undo selected\n";
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("Documentation")) {
                // Open documentation
                std::cout << "Documentation selected\n";
            }
            if (ImGui::MenuItem("Support")) {
                // Open support
                std::cout << "Support selected\n";
            }
            if (ImGui::MenuItem("About")) {
                // Display about info
                std::cout << "About selected\n";
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Monte Carlo Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context\n";
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    Simulation simulation(100, 10000, 1.0, 10.0);
    simulation.initialize();

    char filename[128] = "particles.dump";
    int intervalSteps = 10;
    bool isRunning = false;  // Toggle for simulation

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Top menu bar
        createMenuBar();

        // Control panel
        ImGui::Begin("Monte Carlo Simulation");

        static int numParticles = simulation.getNumParticles();
        static int numSteps = simulation.getNumSteps();
        static double temperature = simulation.getTemperature();

        ImGui::InputInt("Number of Particles", &numParticles);
        ImGui::InputInt("Number of Steps", &numSteps);
        ImGui::InputDouble("Temperature", &temperature);
        ImGui::InputInt("Interval of Steps", &intervalSteps);
        ImGui::InputText("Filename", filename, IM_ARRAYSIZE(filename));

        if (ImGui::Button("Initialize")) {
            simulation.setNumParticles(numParticles);
            simulation.setNumSteps(numSteps);
            simulation.setTemperature(temperature);
            simulation.setIntervalSteps(intervalSteps);
            simulation.initialize();
        }

        if (ImGui::Button(isRunning ? "Pause Simulation" : "Run Simulation")) {
            isRunning = !isRunning;
        }

        if (ImGui::Button("Save Dump")) {
            simulation.saveParticles(filename);
        }

        ImGui::End();

        // Render particles and update simulation
        if (isRunning) {
            simulation.run(1);  // Run one simulation step
        }

        // OpenGL rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1098f, 0.1725f, 0.2980f, 1.0f);  // Background color #1c2c4c
        glClear(GL_COLOR_BUFFER_BIT);



        renderParticles(simulation.getBox());  // Render current particle states

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
