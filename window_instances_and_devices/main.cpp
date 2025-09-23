#define GLFW_INCLUDE_VULKAN
#include "../includes/glfw3.h"

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "../includes/VulkanRenderer.h"

GLFWwindow* window;
VulkanRenderer* vulkanRenderer;

void initWindow (std::string wName = "Test window", const int width = 800 , const int height = 600) {
    // Init GLFW
    glfwInit();
    // Set GLFW to not create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Disable window resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main () {
    initWindow();

    // Create vulkan renderer instance
    vulkanRenderer = new VulkanRenderer(window);
    if (vulkanRenderer->init(window) == EXIT_FAILURE) {
        printf("Failed to initialize Vulkan renderer\n");
        return EXIT_FAILURE;
    }

    // loop until closed
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // destroy glfw window and stop
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}