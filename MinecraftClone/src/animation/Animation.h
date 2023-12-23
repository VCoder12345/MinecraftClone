#pragma once

#include "AnimationFrame.h"

#include <vector>

class Animation {
public:
	std::vector<AnimationFrame> frames;

	Animation() {}

	void addFrame(AnimationFrame frame) {
		frames.push_back(frame);
	}
};