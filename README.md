# Tomulo

Tomulo is Vulkan C++ 3D Engine for Game programming. 

# Background

I've started learning Vulkan 3D programming through [Vulkan Tutorial](https://vulkan-tutorial.com/) and
[Brendan Galea's videos](https://www.youtube.com/watch?v=Y9U9IE0gVHA&list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR) to upgrade my game development skills from 2D to 3D. Since it seems so hard to get work even as web developer.

# Current status

8.8.2022 Working on the basic functionality.  

# Building

Currently supporting building only from Linux with cmake. 

1. Dependancies:
    The engine and building it depends on the following projects.
    * Vulkan -- Graphics pipeline
    * GLFW -- For window creation
    * GLM -- 3D mathematics
    * CMAKE -- Building

    Which you can install in Arch based Wayland distributions with the following command:
    ```
    pamac install vulkan-tools vulkan-validation-layers glfw-wayland glm cmake
    ```


2. Clone the repository:
    ```
    git clone https://github.com/TMKCodes/Tomulo.git
    ```

3. Build and run the project with Linux distribution of your choice:

    First you need to compile the shaders:
    ```
    glslc shaders/shader.vert -o shaders/vert.spv
    glslc shaders/shader.frag -o shaders/frag.spv
    ```

    Then build with cmake:
    ```
    cmake -S . -B .
    ```

    Then build with make:
    ```
    make
    ```

    Then run:
    ```
    ./Tomulo
    ```
