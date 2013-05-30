#pragma once

#include "glm\glm.hpp"
#include "Program.h"
#include "LitObject.h"
#include <memory>

class Light
{
public:
	Light(const glm::vec4 &_intensity);
	~Light(void);

	virtual void renderingSetup(const glm::mat4 &View, const glm::mat4 &Projection) = 0;
	virtual void collectData(std::shared_ptr<LitObject> &obj, const glm::mat4 &View, const glm::mat4 &Projection) = 0;

protected:
	glm::vec4 intensity;
};

