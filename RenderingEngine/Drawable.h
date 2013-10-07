#pragma once

#include "glm/glm.hpp"

class Drawable
{
public:
	Drawable(void);
	virtual ~Drawable(void);

	virtual void initDrawing() = 0;
	virtual void draw(const glm::mat4 &View, const glm::mat4 &Projection) = 0;
};

