#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Simulation.h"
#include "Renderer.h"
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

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

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

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

        if (ImGui::Button("Run Simulation")) {
            simulation.run();
        }

        if (ImGui::Button("Save Dump")) {
            simulation.saveParticles(filename);
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderParticles(simulation.getBox());

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
