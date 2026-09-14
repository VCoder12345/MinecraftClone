# Minecraft-Style Voxel Renderer

A small Minecraft-style voxel game written in C++ with OpenGL. The project combines a custom ECS-based game-engine architecture with a voxel renderer focused on efficient block rendering.

<img width="1718" height="913" alt="image" src="https://github.com/user-attachments/assets/6530b4f8-3948-4f85-b3bb-de5bd8dc7157" />

<img width="1711" height="908" alt="image" src="https://github.com/user-attachments/assets/52311428-4b8a-4475-b960-6f356f9e8581" />


## Features

* **Voxel rendering** — groups and batches blocks for efficient rendering.
* **ECS architecture** — entity and component management for game objects.
* **Resource management** — centralized handling of game resources.
* **Procedural terrain** — generates terrain using Perlin noise.
* **Block interaction** — ray-based voxel traversal for placing and destroying blocks.
* **OpenGL rendering** — custom rendering pipeline implemented directly with OpenGL.

## Focus

The main focus was exploring efficient rendering of voxel worlds, particularly how blocks can be grouped to reduce rendering overhead. The project also contains reusable game-engine infrastructure developed alongside it, including an ECS and resource-management system.
