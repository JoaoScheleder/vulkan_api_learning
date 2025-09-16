# Vulkan API Learning Project  
![Vulkan Logo](https://upload.wikimedia.org/wikipedia/commons/6/6a/Vulkan_API_logo.svg)

A study project in **C++** using the **Vulkan API** for graphics and compute. This project explores fundamental concepts of Vulkan programming, including:

- Instance and device creation  
- Swapchain and render pass setup  
- Graphics pipeline creation  
- Command buffers and synchronization  
- Basic drawing and compute examples  

The project is designed for learning and experimentation. More examples and advanced techniques will be added over time.

---

## Requirements

- **C++ compiler** (supports C++11 or later)  
- **Vulkan SDK** (tested with Vulkan 1.3.x)  
- **Compatible GPU/driver** with Vulkan support  

---

## Compilation

If you are compiling manually with `g++`/`clang++` (adjust paths as needed):

```bash
g++ main.cpp -o vulkan_project -lvulkan
```

or

```bash
g++ main.cpp -I$VULKAN_SDK/include -L$VULKAN_SDK/lib -lvulkan -lglfw -o main
```