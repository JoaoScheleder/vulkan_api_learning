#include "VulkanRenderer.h"
#include <iostream>
#include <cstring>

VulkanRenderer::VulkanRenderer(GLFWwindow *window)
{
    this->window = window;
};

int VulkanRenderer::init(GLFWwindow *newWindow)
{
    this->window = newWindow;
    try
    {
        createInstance();
        getPhysicalDevice();
        createLogicalDevice();
    }
    catch (const std::runtime_error &e)
    {
        printf("Failed to create Vulkan instance: %s\n", e.what());
        return EXIT_FAILURE;
    }
    return 0;
}
void VulkanRenderer::cleanup() {
    vkDestroyDevice(mainDevice.logicalDevice, nullptr);
    vkDestroyInstance(instance, nullptr);
};

VulkanRenderer::~VulkanRenderer()
{
    vkDestroyInstance(instance, nullptr);
};

void VulkanRenderer::createInstance()
{
    // Informationa about the applcation itself
    // most data doesnt affect the program
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine"; // Custom engine name
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    // createInfo.pNext = nullptr;
    // createInfo.flags = VK_
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan instance");
    }

    // Create list to hold instance extensions
    std::vector<const char *> extensions = std::vector<const char *>();

    uint32_t glfwExtensionCount = 0; // GLFW may require multiple extensions
    const char **glfwExtensions;     // Pointer to array of extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    for (size_t i = 0; i < glfwExtensionCount; i++)
    {
        extensions.push_back(glfwExtensions[i]);
    }

    if (!checkInstanceExtensionSupport(&extensions))
    {
        throw std::runtime_error("Not all required extensions are supported");
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    // TODO: Set up validation layers
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan instance");
    }
}
void VulkanRenderer::createLogicalDevice()
{

    QueueFamilyIndices indices = getQueueFamilies(mainDevice.physicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f; // Highest priority
    queueCreateInfo.pQueuePriorities = &queuePriority;

    // Information to create logical device
    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
     // Logical device extensions !== instance extensions
    deviceCreateInfo.enabledExtensionCount = 0;
    deviceCreateInfo.ppEnabledExtensionNames = nullptr;
    deviceCreateInfo.enabledLayerCount = 0;

    deviceCreateInfo.pEnabledFeatures = nullptr; // Optional

    VkPhysicalDeviceFeatures deviceFeatures = {};
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    VkResult result = vkCreateDevice(mainDevice.physicalDevice, &deviceCreateInfo, nullptr, &mainDevice.logicalDevice);
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create logical device");
    }

    // Queues are created at the same time as the logical device
    // From given logical device, of given queue family, get queue index 0  
    vkGetDeviceQueue(mainDevice.logicalDevice, indices.graphicsFamily, 0, &graphicsQueue);

}
void VulkanRenderer::getPhysicalDevice()
{
    // Enumerate physical devices
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    // if no devices found, throw error
    if (deviceCount == 0)
    {
        throw std::runtime_error("Failed to find GPUs with Vulkan support");
    }

    // get list of physical devices
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto &device : devices)
    {
        if (checkDeviceSuitability(device))
        {
            mainDevice.physicalDevice = device;
            break;
        }
    }

}
bool VulkanRenderer::checkInstanceExtensionSupport(std::vector<const char *> *extensions)
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    for (const char *extensionName : *extensions)
    {
        bool found = false;

        for (const auto &extension : availableExtensions)
        {
            if (strcmp(extensionName, extension.extensionName) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }
    }

    return true;
}
bool VulkanRenderer::checkDeviceSuitability(VkPhysicalDevice device)
{

    // // Information about the device itself (ID, name, type, etc.)
    // VkPhysicalDeviceProperties deviceProperties;
    // vkGetPhysicalDeviceProperties(device, &deviceProperties);

    // // Check if the device is suitable for our needs
    // if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    // {
    //     return true;
    // }

    // return false;

    QueueFamilyIndices indices = getQueueFamilies(device);

    return indices.isComplete();
}

QueueFamilyIndices VulkanRenderer::getQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto &queueFamily : queueFamilies)
    {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicsFamily = i;
        }

        if (indices.isComplete())
        {
            break;
        }

        i++;
    }

    return indices;
}
