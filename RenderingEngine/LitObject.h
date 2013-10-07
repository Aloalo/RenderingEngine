#pragma once

#include "Drawable.h"
#include "Material.h"

class LitObject :
	public Drawable
{
public:
	LitObject(void);
	~LitObject(void);

	virtual const Material* getMaterial() = 0;
	virtual glm::mat4 modelMatrix() = 0;
};

