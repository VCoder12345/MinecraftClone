#include <world/Chunk.h>



int Chunk::toIndex(int i, int j, int k) const {
	return (k * size * size) + (j * size) + i;
}

Block* Chunk::get(int i, int j, int k) const {
	return blocks[toIndex(i, j, k)];
}

bool Chunk::isBlockEmpty(int i, int j, int k) const {
	return get(i, j, k) == nullptr;
}

glm::vec3 Chunk::blockPos(int i, int j, int k) const {
	return glm::vec3(i, k, j);
}



bool Chunk::isEnclosed(int i, int j, int k) {
	if (i == 0 || j == 0 || k == 0 || i == size - 1 || j == size - 1 || k == size - 1) {
		return false;
	}

	return !isBlockEmpty(i - 1, j, k) && !isBlockEmpty(i + 1, j, k)
		&& !isBlockEmpty(i, j - 1, k) && !isBlockEmpty(i, j + 1, k)
		&& !isBlockEmpty(i, j, k - 1) && !isBlockEmpty(i, j, k + 1);
}



void Chunk::setBlock(int type, int i, int j, int k) {
	const int index = toIndex(i, j, k);

	if (blocks[index] == nullptr) {
		++numBlocks;
	}

	blocks[index] = blFactory->createBlock(type);
	//Game::instance().getCurrentScene().addEntity(blocks[index]);
}

void Chunk::deleteBlock(int i, int j, int k) {
	const int index = toIndex(i, j, k);

	blocks[index] = nullptr;
	--numBlocks;
}

void Chunk::genMesh(bool quadCulling) {
	if (numBlocks == 0) return;
	std::vector<float> allVertices;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < size; ++k) {
				glm::vec3 pos = blockPos(i, j, k);
				auto bl = get(i, j, k);

				if (bl == nullptr) continue;

				float lx = pos.x;
				float rx = pos.x + 1.0f;
				float ly = pos.y;
				float ry = pos.y + 1.0f;
				float lz = pos.z;
				float rz = pos.z + 1.0f;

				//back
				if (!quadCulling || j == 0 || isBlockEmpty(i, j - 1, k)) {
					allVertices.insert(allVertices.end(), {
						lx, ly, lz,  0.0f, 1.0f, bl->material->texIndexBack, BACK_FACE,
						rx, ly, lz,  1.0f, 1.0f, bl->material->texIndexBack, BACK_FACE,
						rx, ry, lz,  1.0f, 0.0f, bl->material->texIndexBack, BACK_FACE,
						rx, ry, lz,  1.0f, 0.0f, bl->material->texIndexBack, BACK_FACE,
						lx, ry, lz,  0.0f, 0.0f, bl->material->texIndexBack, BACK_FACE,
						lx, ly, lz,  0.0f, 1.0f, bl->material->texIndexBack, BACK_FACE
					});
				}
				

				//front
				if (!quadCulling || j == size - 1 || isBlockEmpty(i, j + 1, k)) {
					allVertices.insert(allVertices.end(), {
						lx, ly, rz, 0.0f, 1.0f, bl->material->texIndexFront, FRONT_FACE,
						rx, ly, rz, 1.0f, 1.0f, bl->material->texIndexFront, FRONT_FACE,
						rx, ry, rz, 1.0f, 0.0f, bl->material->texIndexFront, FRONT_FACE,
						rx, ry, rz, 1.0f, 0.0f, bl->material->texIndexFront, FRONT_FACE,
						lx, ry, rz, 0.0f, 0.0f, bl->material->texIndexFront, FRONT_FACE,
						lx, ly, rz, 0.0f, 1.0f, bl->material->texIndexFront, FRONT_FACE 
					});
				}


				//left
				if (!quadCulling || i == 0 || isBlockEmpty(i - 1, j, k)) {
					allVertices.insert(allVertices.end(), {
						lx, ry, rz,  0.0f, 0.0f, bl->material->texIndexLeft, LEFT_FACE,
						lx, ry, lz,  1.0f, 0.0f, bl->material->texIndexLeft, LEFT_FACE,
						lx, ly, lz,  1.0f, 1.0f, bl->material->texIndexLeft, LEFT_FACE,
						lx, ly, lz,  1.0f, 1.0f, bl->material->texIndexLeft, LEFT_FACE,
						lx, ly, rz,  0.0f, 1.0f, bl->material->texIndexLeft, LEFT_FACE,
						lx, ry, rz,  0.0f, 0.0f, bl->material->texIndexLeft, LEFT_FACE
					});
				}
				

				//right
				if (!quadCulling || i == size - 1 || isBlockEmpty(i + 1, j, k)) {
					allVertices.insert(allVertices.end(), {
						rx, ry, rz,  0.0f, 0.0f, bl->material->texIndexRight, RIGHT_FACE,
						rx, ry, lz,  1.0f, 0.0f, bl->material->texIndexRight, RIGHT_FACE,
						rx, ly, lz,  1.0f, 1.0f, bl->material->texIndexRight, RIGHT_FACE,
						rx, ly, lz,  1.0f, 1.0f, bl->material->texIndexRight, RIGHT_FACE,
						rx, ly, rz,  0.0f, 1.0f, bl->material->texIndexRight, RIGHT_FACE,
						rx, ry, rz,  0.0f, 0.0f, bl->material->texIndexRight, RIGHT_FACE
					});
				}
				

				//bottom
				if (!quadCulling || k == 0 || isBlockEmpty(i, j, k - 1)) {
					allVertices.insert(allVertices.end(), {
						lx, ly, lz,  0.0f, 1.0f, bl->material->texIndexBottom, BOTTOM_FACE,
						rx, ly, lz,  1.0f, 1.0f, bl->material->texIndexBottom, BOTTOM_FACE,
						rx, ly, rz,  1.0f, 0.0f, bl->material->texIndexBottom, BOTTOM_FACE,
						rx, ly, rz,  1.0f, 0.0f, bl->material->texIndexBottom, BOTTOM_FACE,
						lx, ly, rz,  0.0f, 0.0f, bl->material->texIndexBottom, BOTTOM_FACE,
						lx, ly, lz,  0.0f, 1.0f, bl->material->texIndexBottom, BOTTOM_FACE
					});
				}
				

				//top
				if (!quadCulling || k == size - 1 || isBlockEmpty(i, j, k + 1)) {
					allVertices.insert(allVertices.end(), {
						lx, ry, lz,  0.0f, 1.0f, bl->material->texIndexTop, TOP_FACE,
						rx, ry, lz,  1.0f, 1.0f, bl->material->texIndexTop,	TOP_FACE,
						rx, ry, rz,  1.0f, 0.0f, bl->material->texIndexTop,	TOP_FACE,
						rx, ry, rz,  1.0f, 0.0f, bl->material->texIndexTop,	TOP_FACE,
						lx, ry, rz,  0.0f, 0.0f, bl->material->texIndexTop,	TOP_FACE,
						lx, ry, lz,  0.0f, 1.0f, bl->material->texIndexTop,	TOP_FACE
					});
				}
			}
		}
	}

	unsigned int vbo, ebo;
	glGenVertexArrays(1, &mesh.VAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(mesh.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(float), &allVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	mesh.numTriangles = allVertices.size() / 5;
}

BlockMesh& Chunk::getMesh() {
	return mesh;
}

