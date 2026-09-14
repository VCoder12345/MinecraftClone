# Minecraft-Style Voxel Renderer

A small Minecraft-style voxel game written in C++ with OpenGL. The project combines a custom ECS-based game-engine architecture with a voxel renderer focused on efficient block rendering.

## Features

* **Voxel rendering** — groups and batches blocks for efficient rendering.
* **ECS architecture** — entity and component management for game objects.
* **Resource management** — centralized handling of game resources.
* **Procedural terrain** — generates terrain using Perlin noise.
* **Block interaction** — ray-based voxel traversal for placing and destroying blocks.
* **OpenGL rendering** — custom rendering pipeline implemented directly with OpenGL.

## Focus

The main focus was exploring efficient rendering of voxel worlds, particularly how blocks can be grouped to reduce rendering overhead. The project also contains reusable game-engine infrastructure developed alongside it, including an ECS and resource-management system.
