#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "device.hpp"

namespace Tomulo {
    class Descriptors {
        public:
            Descriptors(Tomulo::Device* device, uint32_t binding, uint32_t count);
            ~Descriptors();
            VkDescriptorSetLayout get();
        private:
            Tomulo::Device* device;
            VkDescriptorSetLayout descriptorSetLayout;
    };
}