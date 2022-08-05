#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "device.hpp"

namespace tomulo {
    class Renderpass {
        public:
            Renderpass(tomulo::Device* device, VkFormat imageFormat);
            ~Renderpass();
        private:
            tomulo::Device* device;
            VkRenderPass renderpass;
    };
}