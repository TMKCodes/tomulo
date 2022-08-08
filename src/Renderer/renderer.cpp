#include "renderer.hpp"


namespace Tomulo {
    Renderer::Renderer(int height, int width, std::string name, bool fullscreen) {
        window = new Tomulo::Window(height, width, name, fullscreen);
        createInstance();
        debugger = new Tomulo::DebugMessenger(instance);
        createSurface();
        device = new Tomulo::Device(instance, surface);
        swapchain = new Tomulo::SwapChain(window, device, surface);
        imageViews = new Tomulo::Views(device, swapchain->getSwapchainImages(), swapchain->getSwapchainImageFormat()); 
        renderpass = new Tomulo::Renderpass(device, swapchain->getSwapchainImageFormat());
        pipeline = new Tomulo::Pipeline(device, renderpass);
        framebuffers = new Tomulo::Framebuffers(device, renderpass, swapchain, imageViews);
        commandpool = new Tomulo::CommandPool(device);
        vertexbuffer = new Tomulo::VertexBuffer(device, commandpool);
        indexbuffer = new Tomulo::IndexBuffer(device, commandpool);
        commandbuffers = new Tomulo::CommandBuffers(device, swapchain, renderpass, pipeline, framebuffers, commandpool);
        synobjects = new Tomulo::SynObjects(device);
    }
    Renderer::~Renderer() {
        delete synobjects;
        delete commandbuffers;
        delete vertexbuffer;
        delete commandpool;
        delete framebuffers;
        delete pipeline;
        delete renderpass;
        delete imageViews;
        delete swapchain;
        delete device;
        delete debugger;
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
        delete window;
    }
    void Renderer::createInstance() {
        if(enableValidationLayers && !debugger->checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Lollero";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Tomulo";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if(enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            debugger->populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance!");
        }
    }
    void Renderer::createSurface() {
        if(glfwCreateWindowSurface(instance, window->get(), nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface!");
        }
    }
    void Renderer::printExtensions() {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cout << "Available extensions:\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << std::endl;
        }
    }
    std::vector<const char*> Renderer::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        if(enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }
    bool Renderer::shouldClose() {
        return window->shouldClose();
    }
    void Renderer::recreateSwapchain() {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window->get(), &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window->get(), &width, &height);
            glfwWaitEvents();
        }
        vkDeviceWaitIdle(device->logical());
        delete framebuffers;
        delete imageViews;
        delete swapchain;
        swapchain = new Tomulo::SwapChain(window, device, surface);
        imageViews = new Tomulo::Views(device, swapchain->getSwapchainImages(), swapchain->getSwapchainImageFormat());
        framebuffers = new Tomulo::Framebuffers(device, renderpass, swapchain, imageViews);
    }
    void Renderer::drawFrame() {
        vkWaitForFences(device->logical(), 1, &synobjects->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(device->logical(), swapchain->get(), UINT64_MAX, synobjects->imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
        if(result == VK_ERROR_OUT_OF_DATE_KHR ) {
            recreateSwapchain();
            return;
        } else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("Failed to acquire swap chain image!");
        }
        vkResetFences(device->logical(), 1, &synobjects->inFlightFences[currentFrame]);

        commandbuffers->reset(currentFrame);
        commandbuffers->record(framebuffers->get(), swapchain->getSwapchainExtent(), vertexbuffer, indexbuffer, imageIndex, currentFrame);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        VkSemaphore waitSemaphores[] = {synobjects->imageAvailableSemaphores[currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        VkCommandBuffer commandBuffer = commandbuffers->get(currentFrame);
        submitInfo.pCommandBuffers = &commandBuffer;

        VkSemaphore signalSemaphores[] = {synobjects->renderFinishedSemaphores[currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(device->graphicsQueue, 1, &submitInfo, synobjects->inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapchain->get()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(device->presentQueue, &presentInfo);
        if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window->framebufferResized) {
            window->framebufferResized = false;
            recreateSwapchain();
        } else if(result != VK_SUCCESS) {
            throw std::runtime_error("Failed to present swapchain image!");
        }
        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }
}