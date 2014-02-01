#pragma once

#include "Light.h"
#include "TextureSampler.h"

class AmbientLight :
	public Light
{
public:
	AmbientLight(const glm::vec4 &_intensity);
	~AmbientLight(void);

	void renderingSetup(const glm::mat4 &View, const glm::mat4 &Projection);
	void collectData(LitObject *obj, const glm::mat4 &View, const glm::mat4 &Projection);
private:
	static Program *p;
	static TextureSampler imageSampler;
};