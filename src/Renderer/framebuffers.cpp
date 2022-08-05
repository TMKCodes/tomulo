#include "framebuffers.hpp"

namespace Tomulo {
    Framebuffers::Framebuffers(Tomulo::Device* device, Tomulo::Renderpass* renderpass, Tomulo::SwapChain* swapchain, Tomulo::Views* views) : device{device}, renderpass{renderpass}, swapchain{swapchain}, views{views} {
        std::vector<VkImageView> imageViews = views->get();
        framebuffers.resize(imageViews.size());
        for(size_t i = 0; i < imageViews.size(); i++) {
            VkImageView attachments[] = {
                imageViews[i]
            };
            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderpass->get();
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            VkExtent2D swapchainExtent = swapchain->getSwapchainExtent();
            framebufferInfo.width = swapchainExtent.width;
            framebufferInfo.height = swapchainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device->logical(), &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create framebuffer!");
            }
        }
    }
    Framebuffers::~Framebuffers() {
        for(auto framebuffer: framebuffers) {
            vkDestroyFramebuffer(device->logical(), framebuffer, nullptr);
        }
    }
}