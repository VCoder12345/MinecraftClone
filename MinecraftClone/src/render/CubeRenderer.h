#pragma once

#include "Renderer.h"
class CubeRenderer :
    public Renderer
{
public:
	CubeRenderer(Shader shader);
	void init();

	void onRender() override;

protected:
	unsigned int VAO;
};

