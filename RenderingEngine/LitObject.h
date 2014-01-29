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
	virtual const glm::mat4& modelMatrix() const = 0;
	virtual const Texture* getTexture() const = 0;
};

