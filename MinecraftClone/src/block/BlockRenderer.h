#pragma once

#include <render/Renderer.h>

#include <world/World.h>

#include <vector>

class BlockRenderer :
	public Renderer
{
public:
	BlockRenderer(Shader shader, Shader slcShader, Shader cubeShader);
	~BlockRenderer() {
	}
	void init();

	void onRender() override;
	void renderBlockMesh(const BlockMesh& mesh, glm::vec3 offset);
	void renderSlc();
	void renderCube(const glm::vec3& min, const glm::vec3& max);
	bool shouldRenderChunk(glm::vec3 offset, glm::mat4 pv);
	bool checkPlane(glm::vec3 normal, float d, const glm::vec3& mid, const glm::vec3& halfDiag);
private:
	unsigned int slcVAO;
	Shader slcShader, cubeShader;
};

