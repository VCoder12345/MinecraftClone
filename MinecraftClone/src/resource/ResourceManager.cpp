#include "ResourceManager.h"

#include <fstream>
#include <sstream>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glad/glad.h>



Shader ResourceManager::getShader(std::string name) {
	return shaders[name];
}

Shader ResourceManager::loadShader(std::string name, const char* vertexPath, const char* fragmentPath) {
	Shader shader = loadShaderFromFile(vertexPath, fragmentPath);
	shaders[name] = shader;
	return shader;
}

Shader ResourceManager::loadShaderFromFile(const char* vertexPath, const char* fragmentPath) {
	try {
		std::ifstream vertexFile(vertexPath);
		std::ifstream fragmentFile(fragmentPath);

		std::stringstream fragmentStream;
		std::stringstream vertexStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		Shader shader;
		shader.compile(vertexStream.str().c_str(), fragmentStream.str().c_str());
		return shader;
	}
	catch (std::exception ex) {
		std::cout << "Failed to load Shader file" << std::endl;
	}
}

Texture ResourceManager::getTexture(std::string name) {
	return textures[name];
}

Texture ResourceManager::loadTexture(std::string name, const char* filePath, bool alpha = false, bool nearestFilter = false) {
	Texture texture = loadTextureFromFile(filePath, alpha, nearestFilter);
	textures[name] = texture;
	return texture;
}


Texture ResourceManager::loadTextureFromFile(const char* filePath, bool alpha, bool nearestFilter) {
	int width, height, nrChannels;

	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	Texture texture;
	if (data) {
		if (alpha) {
			texture.format = GL_RGBA;
			texture.internalFormat = GL_RGBA;
		}
		//nearest instead of linear -> for example for pixel art
		if (nearestFilter) {
			texture.minFilter = GL_NEAREST;
			texture.maxFilter = GL_NEAREST;
		}

		texture.generate(width, height, data);
	}
	else {
		std::cout << "Failed to load Texture file with path" << filePath << std::endl;
	}

	stbi_image_free(data);

	return texture;
}


Animation ResourceManager::getAnimation(std::string name) {
	return animations[name];
}

Animation ResourceManager::loadAnimation(std::string name, const char* filePath) {
	Animation animation = loadAnimationFromFile(filePath);
	animations[name] = animation;
	return animation;
}

Animation ResourceManager::loadAnimationFromFile(const char* filePath) {
	Animation animation;
	std::fstream file;
	file.open(filePath, std::ios::in);
	if (!file)
		std::cout << "Couldn't load animation with path " << filePath << std::endl;
	else {
		std::string line;
		//float time = 0.1f;
		while (std::getline(file, line)) {
			/*if (line == "") {
				std::getline(file, line);
				time = std::stof(line);
				std::cout << time << std::endl;
				continue;
			}*/
			Texture texture = loadTextureFromFile(line.c_str(), true, true);
			AnimationFrame frame(texture);
			animation.addFrame(frame);
		}

		//animation.time = time;
	}

	file.close();

	return animation;
}