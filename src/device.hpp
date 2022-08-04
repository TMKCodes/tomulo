#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>
#include <vector>
#include <iostream>
#include <set>

#include "support.hpp"

namespace tomulo {
    class Device {
        public:
            Device(VkInstance &instance, VkSurfaceKHR &surface);
            ~Device();
            VkDevice logical();
            VkPhysicalDevice physical();
            struct QueueFamilyIndices {
                std::optional<uint32_t> graphicsFamily;
                std::optional<uint32_t> presentFamily;
                bool isComplete() {
                    return graphicsFamily.has_value() && presentFamily.has_value();
                }
            };
            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        private:
            void pickPhyiscalDevice();
            void createLogicalDevice();
            VkInstance instance;
            VkSurfaceKHR surface;
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkDevice device;
            VkQueue graphicsQueue;
            VkQueue presentQueue;
            bool isSuitable(VkPhysicalDevice device);
            const std::vector<const char*> deviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            
    };
}