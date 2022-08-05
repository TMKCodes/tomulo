#include "application.hpp"

namespace Tomulo {
    Application::Application() {
        renderer = new Tomulo::Renderer(800, 600, "Tomulo Engine", false);
        // Optionally print extensions.
        renderer->printExtensions();
    }

    Application::~Application() {
        delete renderer;
    }

    void Application::run() {
        while(!renderer->shouldClose()) {
            glfwPollEvents();
        }
    }
}
