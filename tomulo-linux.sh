#!/bin/bash
glslc shaders/shader.vert -o shaders/vert.spv
glslc shaders/shader.frag -o shaders/frag.spv
mkdir -p build
mkdir -p build/shaders
mv shaders/vert.spv build/shaders/vert.spv
mv shaders/frag.spv build/shaders/frag.spv
cd build
cmake -S ../ -B .
make && ./Tomulo
cd ..