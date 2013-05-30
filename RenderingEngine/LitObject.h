#pragma once

#include "Drawable.h"

class LitObject :
	public Drawable
{
public:
	LitObject(void);
	~LitObject(void);

	virtual glm::vec4 diffuseColor() = 0;
	virtual glm::vec4 specularColor() = 0;
	virtual glm::vec4 ambientColor() = 0;
	virtual float shininessFactor() = 0;
	virtual glm::mat4 modelMatrix() = 0;
};

