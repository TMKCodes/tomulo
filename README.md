# Tomulo
I'm learning Vulkan 3D programming through [Vulkan tutorial](https://vulkan-tutorial.com/) to 
create Open World Sandbox Massive Multiplayer First person shooter game. Which means this is
a hobby project and I am not sure yet where or when or how or what. 

Thanks.

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
