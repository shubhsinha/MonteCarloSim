#include "include/glad/glad.h"  // Include GLAD first to load OpenGL functions
#include <GLFW/glfw3.h>         // GLFW is included after GLAD
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "../imgui/imgui.h"      // Include ImGui headers after GLAD and GLFW
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"

class Particle {
public:
    double x, y, z;
    Particle(double x_init = 0, double y_init = 0, double z_init = 0) 
        : x(x_init), y(y_init), z(z_init) {}
    void move(double dx, double dy, double dz) {
        x += dx;
        y += dy;
        z += dz;
    }
};

class Box {
private:
    double size;
    std::vector<Particle> particles;

public:
    Box(double box_size) : size(box_size) {}

    void addParticle(const Particle& particle) {
        particles.push_back(particle);
    }

    double calculateLennardJonesPotential(const Particle& p1, const Particle& p2) const {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        double dz = p1.z - p2.z;
        dx -= size * round(dx / size);
        dy -= size * round(dy / size);
        dz -= size * round(dz / size);
        double r2 = dx * dx + dy * dy + dz * dz;
        double r6 = r2 * r2 * r2;
        double r12 = r6 * r6;
        return 4 * 1.0 * (pow(1.0, 12) / r12 - pow(1.0, 6) / r6);
    }

    double calculateTotalEnergy() const {
        double totalEnergy = 0.0;
        for (size_t i = 0; i < particles.size(); i++) {
            for (size_t j = i + 1; j < particles.size(); j++) {
                totalEnergy += calculateLennardJonesPotential(particles[i], particles[j]);
            }
        }
        return totalEnergy;
    }

    void applyPeriodicBoundaryConditions(Particle& particle) {
        particle.x -= size * floor(particle.x / size);
        particle.y -= size * floor(particle.y / size);
        particle.z -= size * floor(particle.z / size);
    }

    // Mark this method as const
    Particle& getParticle(int index) const {
        return const_cast<Particle&>(particles[index]);
    }

    size_t getParticleCount() const {
        return particles.size();
    }

    double getSize() const {
        return size;
    }

    void clearParticles() {
        particles.clear();
    }
};

class Simulation {
private:
    Box box;
    int numParticles;
    int numSteps;
    double beta;

public:
    Simulation(int particles, int steps, double temperature, double box_size)
        : box(box_size), numParticles(particles), numSteps(steps), beta(1.0 / temperature) {}

    void initialize() {
        box.clearParticles();  // Clear existing particles
        std::srand(std::time(nullptr));
        for (int i = 0; i < numParticles; i++) {
            double x = static_cast<double>(std::rand()) / RAND_MAX * box.getSize();
            double y = static_cast<double>(std::rand()) / RAND_MAX * box.getSize();
            double z = static_cast<double>(std::rand()) / RAND_MAX * box.getSize();
            box.addParticle(Particle(x, y, z));
        }
    }

    void run() {
        for (int step = 0; step < numSteps; step++) {
            int i = std::rand() % numParticles;
            Particle& particle = box.getParticle(i);
            double oldX = particle.x;
            double oldY = particle.y;
            double oldZ = particle.z;
            double dx = (static_cast<double>(std::rand()) / RAND_MAX - 0.5);
            double dy = (static_cast<double>(std::rand()) / RAND_MAX - 0.5);
            double dz = (static_cast<double>(std::rand()) / RAND_MAX - 0.5);
            particle.move(dx, dy, dz);
            box.applyPeriodicBoundaryConditions(particle);
            double oldEnergy = box.calculateTotalEnergy();
            particle.x = oldX;
            particle.y = oldY;
            particle.z = oldZ;
            double newEnergy = box.calculateTotalEnergy();
            double dE = newEnergy - oldEnergy;
            if (dE > 0 && exp(-beta * dE) < static_cast<double>(std::rand()) / RAND_MAX) {
                particle.x = oldX;
                particle.y = oldY;
                particle.z = oldZ;
            } else {
                particle.move(dx, dy, dz);
            }
        }
    }

    int getNumParticles() const { return numParticles; }
    void setNumParticles(int num) { numParticles = num; }

    int getNumSteps() const { return numSteps; }
    void setNumSteps(int steps) { numSteps = steps; }

    double getTemperature() const { return 1.0 / beta; }
    void setTemperature(double temp) { beta = 1.0 / temp; }

    Box& getBox() { return box; }

    // Function to save the particle data to a dump file
    void saveParticles(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file " << filename << std::endl;
            return;
        }

        file << "ITEM: TIMESTEP\n";
        file << "0\n"; // Time step (usually incremented in MD simulations)
        file << "ITEM: NUMBER OF ATOMS\n";
        file << box.getParticleCount() << "\n";
        file << "ITEM: BOX BOUNDS pp pp pp\n";
        file << "0 " << box.getSize() << "\n";
        file << "0 " << box.getSize() << "\n";
        file << "0 " << box.getSize() << "\n";
        file << "ITEM: ATOMS id x y z\n";

        for (size_t i = 0; i < box.getParticleCount(); ++i) {
            const Particle& p = box.getParticle(i);
            file << (i + 1) << " " << p.x << " " << p.y << " " << p.z << "\n";
        }

        file.close();
    }
};

// Function to render particles as points
void renderParticles(const Box& box) {
    glPointSize(5.0f);  // Set the point size
    glBegin(GL_POINTS); // Start drawing points

    for (size_t i = 0; i < box.getParticleCount(); ++i) {
        const Particle& p = box.getParticle(i);

        glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
        glVertex3f(p.x / box.getSize(), p.y / box.getSize(), p.z / box.getSize()); // Normalize positions
    }

    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Monte Carlo Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader (GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context\n";
        return -1;
    }

    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    Simulation simulation(100, 10000, 1.0, 10.0);
    simulation.initialize();

    // Variables for the filename input
    char filename[128] = "particles.dump"; // Default filename

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create ImGui window
        ImGui::Begin("Monte Carlo Simulation");

        static int numParticles = simulation.getNumParticles();
        static int numSteps = simulation.getNumSteps();
        static double temperature = simulation.getTemperature();

        ImGui::InputInt("Number of Particles", &numParticles);
        ImGui::InputInt("Number of Steps", &numSteps);
        ImGui::InputDouble("Temperature", &temperature);

        if (ImGui::Button("Initialize")) {
            simulation.setNumParticles(numParticles);
            simulation.setNumSteps(numSteps);
            simulation.setTemperature(temperature);
            simulation.initialize();
        }

        if (ImGui::Button("Run Simulation")) {
            simulation.run();
        }

        // Input field for the dump file name
        ImGui::InputText("Filename", filename, IM_ARRAYSIZE(filename));

        // Button to save particles to the dump file
        if (ImGui::Button("Save Dump")) {
            simulation.saveParticles(filename);
        }

        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the particles
        renderParticles(simulation.getBox());

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


