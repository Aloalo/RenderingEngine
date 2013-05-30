#pragma once

#include "Light.h"

class DiffuseLight :
	public Light
{
public:
	DiffuseLight(const glm::vec3 &_direction);
	~DiffuseLight(void);

	void renderingSetup(const glm::mat4 &View, const glm::mat4 &Projection);
	void collectData(std::shared_ptr<LitObject> &obj, const glm::mat4 &View, const glm::mat4 &Projection);

private:
	glm::vec3 direction;
	static Program *p;
};

