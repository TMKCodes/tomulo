#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>

#include "device.hpp"

namespace tomulo {
    class View {
        public:
            View(tomulo::Device* device, std::vector<VkImage> images, VkFormat imageFormat);
            ~View();
        private:
            tomulo::Device* device;
            std::vector<VkImageView> views;
    };
}