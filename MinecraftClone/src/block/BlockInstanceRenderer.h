#pragma once

#include <render/Renderer.h>

class BlockInstanceRenderer :
    public Renderer
{
public:
	BlockInstanceRenderer(Shader shader);
	void init();

	void onRender() override;

protected:
	unsigned int VAO;
};

