#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>

#include "device.hpp"

namespace Tomulo {
    class View {
        public:
            View(Tomulo::Device* device, std::vector<VkImage> images, VkFormat imageFormat);
            ~View();
        private:
            Tomulo::Device* device;
            std::vector<VkImageView> views;
    };
}