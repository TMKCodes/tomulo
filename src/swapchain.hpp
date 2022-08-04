#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>
#include <vector>
#include <cstdint>
#include <limits>
#include <algorithm>

#include "support.hpp"
#include "window.hpp"
#include "device.hpp"

namespace tomulo {
    class SwapChain {
        public:
            SwapChain(tomulo::Window* window, tomulo::Device* device, VkSurfaceKHR& surface);
            ~SwapChain();
            std::vector<VkImage> getSwapchainImages();
            VkFormat getSwapchainImageFormat();
        private:
            tomulo::Window* window;
            tomulo::Device* device;
            VkSurfaceKHR surface;
            VkSwapchainKHR swapchain;
            std::vector<VkImage> swapchainImages;
            VkFormat swapchainImageFormat;
            VkExtent2D swapchainExtent;
            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
            
    };
}