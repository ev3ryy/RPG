#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include "vulkan_renderer.hpp"
#include "logs.hpp"

VulkanRenderer::VulkanRenderer(const std::vector<std::string>& extensions)
: m_Instance(extensions),
  m_PhysicalDevice(m_Instance.Get()),
  m_Device(m_PhysicalDevice.Get())
{
    init(window);
}

VulkanRenderer::~VulkanRenderer() {
    cleanup();
}

void VulkanRenderer::init(Window& window) {
    createSurface(window);
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain(window);
    createRenderPass();
    createGraphicsPipeline();
    createFramebuffers();
    createCommandPool();
    createCommandBuffers();

    LOG_INFO("VulkanRenderer initialized");
}


void drawFrame() {

}

void VulkanRenderer::cleanup() {
    vkDeviceWaitIdle(m_Device.Get());

    if (m_CommandBuffers.size() > 0) {
        vkFreeCommandBuffers(m_Device.Get(), m_CommandPool, static_cast<uint32_t>(m_CommandBuffers.size()), m_CommandBuffers.data());
        m_CommandBuffers.clear();
    }

    for (auto framebuffer : m_Framebuffers) {
        vkDestroyFramebuffer(m_Device.Get(), framebuffer, nullptr);
    }
    m_Framebuffers.clear();

    vkDestroyPipeline(m_Device.Get(), m_GraphicsPipeline, nullptr);
    vkDestroyPipelineLayout(m_Device.Get(), m_PipelineLayout, nullptr);
    vkDestroyRenderPass(m_Device.Get(), m_RenderPass, nullptr);

    for (auto imageView : m_SwapChainImageViews) {
        vkDestroyImageView(m_Device.Get(), imageView, nullptr);
    }
    m_SwapChainImageViews.clear();

    if (m_SwapChain) {
        vkDestroySwapchainKHR(m_Device.Get(), m_SwapChain, nullptr);
        m_SwapChain = VK_NULL_HANDLE;
    }

    if (m_Surface) {
        vkDestroySurfaceKHR(m_Instance.Get(), m_Surface, nullptr);
        m_Surface = VK_NULL_HANDLE;
    }

    if (m_Device) {
        vkDestroyDevice(m_Device.Get(), nullptr);
        m_Device = VK_NULL_HANDLE;
    }

    if (m_CommandPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(m_Device.Get(), m_CommandPool, nullptr);
        m_CommandPool = VK_NULL_HANDLE;
    }

    LOG_INFO("VulkanRenderer cleaned up successfully");
}

void VulkanRenderer::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "RPG";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
}