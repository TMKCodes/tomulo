#pragma once 
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>



namespace Tomulo {
    
    class Window {
        public:
            Window(int width, int height, std::string name, bool fullscreen);
            ~Window();
            bool shouldClose();
            GLFWwindow* get();
            bool framebufferResized = false;
        private:
            GLFWwindow* glfwWindow;
    };
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto object = reinterpret_cast<Tomulo::Window*>(glfwGetWindowUserPointer(window));
        object->framebufferResized = true;
    }
}