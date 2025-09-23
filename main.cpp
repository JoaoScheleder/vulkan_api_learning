#define GLFW_INCLUDE_VULKAN
#include "includes/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "includes/GLM/glm.hpp"
#include "includes/GLM/mat4x4.hpp"

#include <stdio.h>
#include <iostream>

int main()
{
    // Your code here
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    uint32_t glfwExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, nullptr);
    printf("Vulkan extensions supported: %d\n", glfwExtensionCount);

    glm::vec4 testVec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 testMat(1.0f);

    auto result = testMat * testVec;

    GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    printf("GLFW window created successfully\n");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}