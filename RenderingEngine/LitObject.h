#pragma once

#include "Drawable.h"
#include "Texture.h"
#include "Material.h"

class LitObject :
	public Drawable
{
public:
	LitObject(void);
	~LitObject(void);

	virtual const Material& getMaterial() const = 0;
	virtual glm::mat4& modelMatrix() = 0;
};

