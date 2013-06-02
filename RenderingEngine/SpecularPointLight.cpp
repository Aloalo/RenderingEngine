#include "SpecularPointLight.h"

Program *SpecularPointLight::p = NULL;

SpecularPointLight::SpecularPointLight(const glm::vec3 &_position, const glm::vec4 &_intensity, float _attenuation)
	: position(_position), attenuation(_attenuation), Model(1.0f),
	Light(_intensity)
{
	if(p == NULL)
		p = new Program(VertexShader("../RenderingEngine/StockShaders/Lighting"), FragmentShader("../RenderingEngine/StockShaders/PhongLighting"));
}

SpecularPointLight::~SpecularPointLight(void)
{
}

void SpecularPointLight::renderingSetup(const glm::mat4 &View, const glm::mat4 &Projection)
{
	p->use();
	p->setUniform("projectionMatrix", Projection);
	p->setUniform("cameraSpaceLightPos", glm::vec3(View * Model * glm::vec4(position, 1.0f)));
	p->setUniform("lightAttenuation", attenuation);
	p->setUniform("lightIntensity", intensity);
}

void SpecularPointLight::collectData(std::shared_ptr<LitObject> &obj, const glm::mat4 &View, const glm::mat4 &Projection)
{
	glm::mat4 MV = View * obj->modelMatrix();
	p->setUniform("mvMatrix", MV);
	p->setUniform("normalMatrix", glm::transpose(glm::inverse(glm::mat3(MV))));
	p->setUniform("specularColor", obj->specularColor());
	p->setUniform("shininessFactor", obj->shininessFactor());
}

glm::mat4& SpecularPointLight::modelMatrix()
{
	return Model;
}
