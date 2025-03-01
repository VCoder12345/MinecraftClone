#include "BlockRenderer.h"


#include <ecs/EntityItr.h>

#include "Block.h"
#include <utils/Transform.h>
#include <tuple>
#include <globals/Globals.h>
#include <camera/CameraMove.h>

BlockRenderer::BlockRenderer(Shader shader, Shader slcShader, Shader cubeShader) : Renderer(shader), slcShader(slcShader), cubeShader(cubeShader) {
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
	shader.setInt("fog.isActive", 0);
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

	cubeShader.use();
	cubeShader.setMat4("projection", projection);
	
	Entity& cam = Game::instance().getCurrentScene().getCamera();
	Transform& camT = cam.getComponent<Transform>();

	glm::mat4 view = camT.model;

	cubeShader.setMat4("view", view);
}

void BlockRenderer::onRender() {
	World& world = Globals::getWorld();
	Entity& cam = Game::instance().getCurrentScene().getCamera();
	Transform& camT = cam.getComponent<Transform>();

	glm::mat4 view = camT.model;
	glm::mat4 pv = projection * view;

	shader.use();

	auto& textures = world.textures();
	for (int i = 0; i < textures.size(); ++i) {
		textures[i].bindUnit(i);
	}
	shader.setMat4("view", view);

	int cullCounter = 0;

	int midHor = world.middleHor();
	int midVer = world.middleVer();
	for (int di = -world.chunkVisualDistHor; di <= world.chunkVisualDistHor; ++di) {
		for (int dj = -world.chunkVisualDistHor; dj <= world.chunkVisualDistHor; ++dj) {
			for (int dk = -world.chunkVisualDistVer; dk <= world.chunkVisualDistVer; ++dk) {
				int i = di + midHor;
				int j = dj + midHor;
				int k = dk + midVer;

				if (i >= world.chunkStoreSizeHor
					|| j >= world.chunkStoreSizeHor
					|| k >= world.chunkStoreSizeVer
					|| i < 0 || j < 0 || k < 0) continue;

				glm::vec3 offset = glm::vec3(di, dk, dj) * (float)world.chunkSize;
				if (shouldRenderChunk(offset, pv)) {
					BlockMesh& mesh = world.getChunk(i, j, k)->getMesh();
					renderBlockMesh(mesh, offset);
				}
				else {
					++cullCounter;
				}
			}
		}
	}

	//std::cout << "culled: " << cullCounter << std::endl;

	renderSlc();
}

void BlockRenderer::renderBlockMesh(const BlockMesh& mesh, glm::vec3 offset) {
	shader.use();

	shader.setVec3("offset", offset);

	glBindVertexArray(mesh.VAO);
	glDrawArrays(GL_TRIANGLES, 0, mesh.numTriangles);
	glBindVertexArray(0);
}

void BlockRenderer::renderCube(const glm::vec3& min, const glm::vec3& max) {
	glLineWidth(5);

	glm::mat4 model(1);
	//model = glm::scale(model, max - min);
	model = glm::translate(model, min);

	cubeShader.use();
	cubeShader.setMat4("model", model);

	glBindVertexArray(slcVAO);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
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

bool BlockRenderer::shouldRenderChunk(glm::vec3 offset, glm::mat4 pv) {
	glm::vec3 min = offset;
	glm::vec3 max = min + glm::vec3(16);
	glm::vec3 mid = (max + min) * 0.5f;
	glm::vec3 halfDiag = (max - min) * 0.5f;

	//renderCube(min, max);

	float la = pv[0][3] + pv[0][0];
	float lb = pv[1][3] + pv[1][0];
	float lc = pv[2][3] + pv[2][0];
	float ld = pv[3][3] + pv[3][0];

	float ra = pv[0][3] - pv[0][0];
	float rb = pv[1][3] - pv[1][0];
	float rc = pv[2][3] - pv[2][0];
	float rd = pv[3][3] - pv[3][0];

	float ba = pv[0][3] + pv[0][1];
	float bb = pv[1][3] + pv[1][1];
	float bc = pv[2][3] + pv[2][1];
	float bd = pv[3][3] + pv[3][1];

	float ta = pv[0][3] - pv[0][1];
	float tb = pv[1][3] - pv[1][1];
	float tc = pv[2][3] - pv[2][1];
	float td = pv[3][3] - pv[3][1];

	float na = pv[0][3] + pv[0][2];
	float nb = pv[1][3] + pv[1][2];
	float nc = pv[2][3] + pv[2][2];
	float nd = pv[3][3] + pv[3][2];

	return checkPlane(glm::vec3(la, lb, lc), ld, mid, halfDiag)
		&& checkPlane(glm::vec3(ra, rb, rc), rd, mid, halfDiag)
		&& checkPlane(glm::vec3(ba, bb, bc), bd, mid, halfDiag)
		&& checkPlane(glm::vec3(ta, tb, tc), td, mid, halfDiag)
		&& checkPlane(glm::vec3(na, nb, nc), nd, mid, halfDiag);
}

bool BlockRenderer::checkPlane(glm::vec3 normal, float d, const glm::vec3& mid, const glm::vec3& halfDiag) {
	float len = normal.length();
	normal /= -len;
	d /= -len;
	float r = halfDiag.x * abs(normal.x) + halfDiag.y * abs(normal.y) + halfDiag.z * abs(normal.z);
	float s = glm::dot(normal, mid) + d;

	return s <= r;
}