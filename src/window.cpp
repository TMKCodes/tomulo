#include "window.hpp"

namespace tomulo {
    Window::Window(int width, int height, std::string name, bool fullscreen) {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        if(fullscreen) {

        } else {
            glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        }
    }

    Window::~Window() {
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }

    GLFWwindow* Window::get() {
        return glfwWindow;
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(glfwWindow);
    }
}