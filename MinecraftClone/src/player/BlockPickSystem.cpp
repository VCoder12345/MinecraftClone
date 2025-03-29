#include "BlockPickSystem.h"

#include "BlockPicker.h"
#include <ecs/EntityItr.h>
#include <camera/CameraMove.h>
#include <globals/Globals.h>

#include <functional>

#define FRAC0(x) (x - floorf(x))
#define FRAC1(x) (1 - x + floorf(x))

void BlockPickSystem::onStart() {
	Game::instance().getEventSystem().subscribe(this, &BlockPickSystem::onMouseEvent);
}

void BlockPickSystem::onUpdate() {
	Input& input = Game::instance().getInput();
	World& world = Globals::getWorld();
	for (Entity& e : EntityItr<BlockPicker, CameraMove>()) {
		BlockPicker& bp = e.getComponent<BlockPicker>();
		CameraMove& cm = e.getComponent<CameraMove>();

		int x = (int)(cm.pos.x);
		int y = (int)(cm.pos.y);
		int z = (int)(cm.pos.z);



		int stepx = 0, stepy = 0, stepz = 0;
		if (cm.front.x > 0) {
			stepx = 1;
		}
		else if (cm.front.x < 0) {
			stepx = -1;
		}

		if (cm.front.y > 0) {
			stepy = 1;
		}
		else if (cm.front.y < 0) {
			stepy = -1;
		}

		if (cm.front.z > 0) {
			stepz = 1;
		}
		else if (cm.front.z < 0) {
			stepz = -1;
		}

		int big = bp.maxPickDist + 1;

		float tDeltax = 0;
		float tDeltay = 0;
		float tDeltaz = 0;

		if (stepx != 0) {
			tDeltax = std::fmin(stepx / cm.front.x, big);
		}else {
			tDeltax = big;
		}

		if (stepy != 0) {
			tDeltay = std::fmin(stepy / cm.front.y, big);
		}
		else {
			tDeltay = big;
		}

		if (stepz != 0) {
			tDeltaz = std::fmin(stepz / cm.front.z, big);
		}
		else {
			tDeltaz = big;
		}

		float tMaxX, tMaxY, tMaxZ;
		if (stepx > 0) {
			tMaxX = tDeltax * FRAC1(cm.pos.x);
		}
		else {
			tMaxX = tDeltax * FRAC0(cm.pos.x);
		}

		if (stepy > 0) {
			tMaxY = tDeltay * FRAC1(cm.pos.y);
		}
		else {
			tMaxY = tDeltay * FRAC0(cm.pos.y);
		}

		if (stepz > 0) {
			tMaxZ = tDeltaz * FRAC1(cm.pos.z);
		}
		else {
			tMaxZ = tDeltaz * FRAC0(cm.pos.z);
		}


		float distUsed = 0;
		 
		world.slc.info.hit = false;

		//std::cout << "pos: " << cm.pos.x << " " << cm.pos.y << " " << cm.pos.z << std::endl;
		int mode = 0;
		while (distUsed <= bp.maxPickDist) {
			if (tMaxX < tMaxY) {
				if (tMaxX < tMaxZ) {
					x += stepx;
					tMaxX += tDeltax;
					distUsed += abs(tDeltax);

					mode = 0;
				}
				else {
					z += stepz;
					tMaxZ += tDeltaz;
					distUsed += abs(tDeltaz);

					mode = 2;
				}
			}
			else {
				if (tMaxY < tMaxZ) {
					y += stepy;
					tMaxY += tDeltay;
					distUsed += abs(tDeltay);

					mode = 1;
				}
				else {
					z += stepz;
					tMaxZ += tDeltaz;
					distUsed += abs(tDeltaz);

					mode = 2;
				}
			}

			BlockInfo blInfo = world.getBlockInfo(x, z, y);

			if (blInfo.hit) {
				//std::cout << "hit " << x << " " << y << " " << z << std::endl;
				world.slc.info = blInfo;
				world.slc.glI = x;
				world.slc.glJ = z;
				world.slc.glK = y;

				if (mode == 0) {
					if (stepx > 0) {
						world.slc.face = LEFT_FACE;
					}
					else {
						world.slc.face = RIGHT_FACE;
					}
				}
				else if (mode == 1) {
					if (stepy > 0) {
						world.slc.face = BOTTOM_FACE;
					}
					else {
						world.slc.face = TOP_FACE;
					}
				}
				else if (mode == 2) {
					if (stepz > 0) {
						world.slc.face = FRONT_FACE;
					}
					else {
						world.slc.face = BACK_FACE;
					}
				}
				break;
			}
			
		}
	}
}

void BlockPickSystem::onMouseEvent(MouseEvent* ev) {
	World& world = Globals::getWorld();
	if (ev->action == GLFW_PRESS) {
		if (ev->btn == GLFW_MOUSE_BUTTON_LEFT) {
			//destroy
			Chunk* chunk = world.chunks[world.slc.info.chunk];
			chunk->deleteBlock(world.slc.info.i, world.slc.info.j, world.slc.info.k);
			chunk->genVertices(true);
		}
		else if (ev->btn == GLFW_MOUSE_BUTTON_RIGHT) {
			//add block
			int ni = world.slc.glI;
			int nj = world.slc.glJ;
			int nk = world.slc.glK;
			switch (world.slc.face)
			{
			case TOP_FACE:
				//std::cout << "top" << std::endl;
				nk++;
				break;
			case BOTTOM_FACE:
				//std::cout << "bottom" << std::endl;
				nk--;
				break;
			case LEFT_FACE:
				//std::cout << "left" << std::endl;
				ni--;
				break;
			case RIGHT_FACE:
				//std::cout << "right" << std::endl;
				ni++;
				break;
			case FRONT_FACE:
				//std::cout << "front" << std::endl;
				nj--;
				break;
			case BACK_FACE:
				//std::cout << "back" << std::endl;
				nj++;
				break;
			}


			BlockInfo info = world.getBlockInfo(ni, nj, nk);

			if (!info.outOfBounds) {
				Chunk* chunk = world.chunks[info.chunk];
				/*Chunk* oChunk = world.chunks[world.slc.info.chunk];
				Block* bl = oChunk->get(world.slc.info.i, world.slc.info.j, world.slc.info.k);*/
				chunk->setBlock(MAT_STONE, info.i, info.j, info.k);
				chunk->genVertices(true);
			}

		}
	}
}