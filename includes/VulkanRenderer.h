#pragma once

#define GLFW_INCLUDE_VULKAN
#include "../includes/glfw3.h"

#include <stdexcept>
#include <vector>

class VulkanRenderer
{
public:
    VulkanRenderer(GLFWwindow *window);

    int init(GLFWwindow *newWindow);

    ~VulkanRenderer();

private:
    GLFWwindow *window;
    VkInstance instance;

    // - Vulkan Functions
    void createInstance();

    // - Support functions
    bool checkInstanceExtensionSupport(std::vector<const char *> *extensions);
};