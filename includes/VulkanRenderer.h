#pragma once

#define GLFW_INCLUDE_VULKAN
#include "glfw3.h"
#include "Utilities.h"

#include <stdexcept>
#include <vector>

class VulkanRenderer
{
public:
    VulkanRenderer(GLFWwindow *window);

    int init(GLFWwindow *newWindow);
    void cleanup();

    ~VulkanRenderer();

private:
    GLFWwindow *window;
    VkInstance instance;
    struct {
        VkPhysicalDevice physicalDevice;
        VkDevice logicalDevice;
    } mainDevice;
    VkQueue graphicsQueue;

    // - Vulkan Functions
    void createInstance();
    void createLogicalDevice();

    // Get functions
    void getPhysicalDevice();
    
    // - Support functions

    bool checkInstanceExtensionSupport(std::vector<const char *> *extensions);
    bool checkDeviceSuitability(VkPhysicalDevice device);

    // -- Getter functions
    QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
};