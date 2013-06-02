#pragma once

#include "Light.h"

class SpecularPointLight :
	public Light
{
public:
	SpecularPointLight(const glm::vec3 &_position, const glm::vec4 &_intensity, float _attenuation);
	~SpecularPointLight(void);

	void renderingSetup(const glm::mat4 &View, const glm::mat4 &Projection);
	void collectData(std::shared_ptr<LitObject> &obj, const glm::mat4 &View, const glm::mat4 &Projection);
	glm::mat4& modelMatrix();


private:
	glm::vec3 position;
	float attenuation;
	glm::mat4 Model;
	static Program *p;
};

