#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>

#include "device.hpp"
#include "renderpass.hpp"


namespace Tomulo {
    class Pipeline {
        public:
            Pipeline(Tomulo::Device* device, Tomulo::Renderpass* renderpass);
            ~Pipeline();
        private:
            Tomulo::Device* device;
            Tomulo::Renderpass* renderpass;
            std::vector<char> readShader(const std::string& filename);
            VkShaderModule createShaderModule(const std::vector<char>& code);
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;
            VkPipelineLayout pipelineLayout;
            VkPipeline graphicsPipeline;
    };
}