#include <gameCode/probe/ProbeScene.h>
#include <game/Game.h>
#include <iostream>






int main() {
	Game& game = Game::instance();
	game.fpsDisplay = false;

	game.addScene(new ProbeScene(), 1);

	game.loadScene(1);

	game.start();

	return 0;
}

