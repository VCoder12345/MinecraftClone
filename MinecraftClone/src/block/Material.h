#pragma once

class Material {
public:
	float texIndexLeft, texIndexRight, texIndexTop, texIndexBottom, texIndexFront, texIndexBack;

	Material(float texIndexLeft, float texIndexRight, float texIndexTop, float texIndexBottom, float texIndexFront, float texIndexBack) 
		: texIndexLeft(texIndexLeft), texIndexRight(texIndexRight),
		texIndexTop(texIndexTop), texIndexBottom(texIndexBottom),
		texIndexFront(texIndexFront), texIndexBack(texIndexBack) {
	}

	Material(float texIndex) : Material(texIndex, texIndex, texIndex, texIndex, texIndex, texIndex) {
	}

	Material(float texIndexSide, float texIndexTop, float texIndexBottom)
		: Material(texIndexSide, texIndexSide, texIndexTop, texIndexBottom, texIndexSide, texIndexSide) {}
};