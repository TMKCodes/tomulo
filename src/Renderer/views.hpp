#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>

#include "device.hpp"

namespace Tomulo {
    class Views {
        public:
            Views(Tomulo::Device* device, std::vector<VkImage> images, VkFormat imageFormat);
            ~Views();
            std::vector<VkImageView> get();
        private:
            Tomulo::Device* device;
            std::vector<VkImageView> views;
    };
}