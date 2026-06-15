# Introduction

This repo currently contains the rendering engine / beginning of the game engine for a Man V. Zombie prototype game. Here is a sample video demoing the current state of the engine and showcasing a little bit of its functionality.

https://github.com/user-attachments/assets/9c5a0be2-5801-4fbf-bc2c-1ff358e52899

# Functionality

The engine uses Vulkan to render models to the scene, and uses point lights to light the scene. The engine has an update loop that allows for performing updates on game objects using the time between frames. It is capable of loading Wavefront (.obj) models using the tinyobjloader sdk. It is able to read the keyboard and perform movement using WASD for forward, backward, left and right movement. It is able to read the arrow keys for rotating the camera. It uses Q and E to move the camera up and down.
