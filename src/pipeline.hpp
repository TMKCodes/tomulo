#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>

#include "device.hpp"


namespace tomulo {
    class Pipeline {
        public:
            Pipeline(tomulo::Device* device);
            ~Pipeline();
        private:
            tomulo::Device* device;
            std::vector<char> readShader(const std::string& filename);
            VkShaderModule createShaderModule(const std::vector<char>& code);
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;
            VkPipelineLayout pipelineLayout;
    };
}