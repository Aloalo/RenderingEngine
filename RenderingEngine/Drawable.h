#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

class Drawable
{
public:
	Drawable(void);
	virtual ~Drawable(void);

	virtual void initDrawing() = 0;
	virtual void draw(const glm::mat4 &ViewProjection) = 0;
};

