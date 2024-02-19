#include "BlockRenderer.h"


#include <ecs/EntityItr.h>

#include "Block.h"
#include <utils/Transform.h>
#include <tuple>
#include <globals/Globals.h>

BlockRenderer::BlockRenderer(Shader shader, Shader slcShader) : Renderer(shader), slcShader(slcShader) {
	init(); 
}

void BlockRenderer::init() {
	World& world = Globals::getWorld();
	ResourceManager& rm = Game::instance().getResourceManager();

	shader.use();

	auto& textures = world.textures();
	int* samplers = new int[textures.size()];
	for (int i = 0; i < textures.size(); ++i) {
		samplers[i] = i;
	}
	shader.setIntAr("textures", samplers, textures.size());

	shader.setMat4("projection", projection);
	shader.setInt("fog.isActive", 1);
	shader.setVec3("fog.colour", glm::vec3(0.6f));
	shader.setFloat("fog.density", 0.03f);

	//init slc-stuff
	int l = -0.9f;
	int r = 1.1f;
	float vertices[] = {
		l, l, l, //0
		l, l, r, //1
		l, r, l, //2
		l, r, r, //3
		r, l, l, //4
		r, l, r, //5
		r, r, l, //6
		r, r, r  //7
	};

	unsigned int indices[] = {
		0, 1,
		0, 4,
		0, 2,

		1, 3,
		1, 5,

		2, 3,
		2, 6,
		
		3, 7,

		4, 5,
		4, 6,

		5, 7, 

		6, 7
	};

	unsigned int vbo, ebo;
	glGenVertexArrays(1, &slcVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(slcVAO);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	slcShader.use();
	slcShader.setMat4("projection", projection);
}

void BlockRenderer::onRender() {
	World& world = Globals::getWorld();
	//double time = glfwGetTime();
	int middle = world.currentChunkIndex();
	for (int di = -world.chunkVisualDist; di <= world.chunkVisualDist; ++di) {
		for (int dj = -world.chunkVisualDist; dj <= world.chunkVisualDist; ++dj) {
			int i = di + middle;
			int j = dj + middle;

			if (i >= world.chunkStoreSize || j >= world.chunkStoreSize || i < 0 || j < 0) continue;
			BlockMesh& mesh = world.getChunk(i, j)->getMesh();
			glm::vec3 offset = glm::vec3(di, 0, dj) * (float)world.chunkSize;
			renderBlockMesh(mesh, offset);
		}
	}

	renderSlc();
	/*double elapsed = glfwGetTime() - time;
	std::cout << "render: " << elapsed << std::endl;*/
}

void BlockRenderer::renderBlockMesh(const BlockMesh& mesh, glm::vec3 offset) {
	World& world = Globals::getWorld();
	Entity& cam = Game::instance().getCurrentScene().getCamera();
	Transform& camT = cam.getComponent<Transform>();

	glm::mat4 view = camT.model;

	shader.use();

	auto& textures = world.textures();
	for (int i = 0; i < textures.size(); ++i) {
		textures[i].bindUnit(i);
	}

	shader.setVec3("offset", offset);
	shader.setMat4("view", view);

	glBindVertexArray(mesh.VAO);
	glDrawArrays(GL_TRIANGLES, 0, mesh.numTriangles);
	glBindVertexArray(0);
}

void BlockRenderer::renderSlc() {
	World& world = Globals::getWorld();

	if (!world.slc.info.hit) return;

	glLineWidth(5);
	Entity& cam = Game::instance().getCurrentScene().getCamera();
	Transform& camT = cam.getComponent<Transform>();

	glm::mat4 view = camT.model;
	glm::vec3 offset = glm::vec3(world.slc.glI, world.slc.glK, world.slc.glJ);
	slcShader.use();
	slcShader.setVec3("offset", offset);
	slcShader.setMat4("view", view);

	glBindVertexArray(slcVAO);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
