#pragma once

#include <render/Renderer.h>

class BlockRenderer :
    public Renderer
{
public:
	BlockRenderer(Shader shader);
	void init();

	void onRender() override;

protected:
	unsigned int VAO;
};

