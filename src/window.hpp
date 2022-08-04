#pragma once 
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace tomulo {
    class Window {
        public:
            Window(int width, int height, std::string name, bool fullscreen);
            ~Window();
            bool shouldClose();
            GLFWwindow* get();
        private:
            GLFWwindow* glfwWindow;
    };
}