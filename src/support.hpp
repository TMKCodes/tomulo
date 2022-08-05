#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <set>

namespace Tomulo {
    class Support {
        public:
            struct SwapChainSupportDetails {
                VkSurfaceCapabilitiesKHR capabilities;
                std::vector<VkSurfaceFormatKHR> formats;
                std::vector<VkPresentModeKHR> presentModes;
            };
            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR &surface);
        private:
            
    };
}