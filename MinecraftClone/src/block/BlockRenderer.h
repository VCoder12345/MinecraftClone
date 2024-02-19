#pragma once

#include <render/Renderer.h>

#include <world/World.h>

#include <vector>

class BlockRenderer :
	public Renderer
{
public:
	BlockRenderer(Shader shader, Shader slcShader);
	~BlockRenderer() {
	}
	void init();

	void onRender() override;
	void renderBlockMesh(const BlockMesh& mesh, glm::vec3 offset);
	void renderSlc();

private:
	unsigned int slcVAO;
	Shader slcShader;
};

