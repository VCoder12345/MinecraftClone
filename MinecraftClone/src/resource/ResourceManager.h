#pragma once

#include <string>
#include <map>

#include <render/Shader.h>
#include <render/Texture.h>
#include <animation/Animation.h>

class ResourceManager {
public:
	//shader
	Shader getShader(std::string name);
	Shader loadShader(std::string name, const char* vertexPath, const char* fragmentPath);

	//texture
	Texture getTexture(std::string name);
	Texture loadTexture(std::string name, const char* filePath, bool alpha, bool nearestFilter);

	//animation
	Animation getAnimation(std::string name);
	Animation loadAnimation(std::string name, const char* filePath);
	
private:
	std::map<std::string, Shader> shaders;
	std::map<std::string, Texture> textures;
	std::map<std::string, Animation> animations;

	Shader loadShaderFromFile(const char* vertexPath, const char* fragmentPath);
	Texture loadTextureFromFile(const char* filePath, bool alpha, bool nearestFilter);
	Animation loadAnimationFromFile(const char* filePath);
};