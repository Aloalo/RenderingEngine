#include "SpecularPointLight.h"

using namespace glm;

Program *SpecularPointLight::p = NULL;

SpecularPointLight::SpecularPointLight(const vec3 &_position, const vec4 &_intensity, float _attenuation)
	: position(_position), attenuation(_attenuation), Model(1.0f),
	Light(_intensity)
{
	if(p == NULL)
		p = new Program(VertexShader("../RenderingEngine/StockShaders/Lighting"), FragmentShader("../RenderingEngine/StockShaders/PhongLighting"));
}

SpecularPointLight::~SpecularPointLight(void)
{
}

void SpecularPointLight::renderingSetup(const mat4 &View, const mat4 &Projection)
{
	p->use();
	p->setUniform("projectionMatrix", Projection);
	p->setUniform("cameraSpaceLightPos", glm::vec3(View * Model * glm::vec4(position, 1.0f)));
	p->setUniform("lightAttenuation", attenuation);
	p->setUniform("lightIntensity", intensity);
}

void SpecularPointLight::collectData(LitObject *obj, const mat4 &View, const mat4 &Projection)
{
	glm::mat4 MV = View * obj->modelMatrix();
	p->setUniform("mvMatrix", MV);
	p->setUniform("normalMatrix", glm::transpose(glm::inverse(glm::mat3(MV))));
	p->setUniform("specularColor", obj->getMaterial().specularColor);
	p->setUniform("diffuseColor", obj->getMaterial().diffuseColor);
	p->setUniform("shininessFactor", obj->getMaterial().shininess);
	if(obj->getTexture() != NULL)
		p->setUniform("textureSampler", (int)obj->getTexture()->getID());
}

glm::mat4& SpecularPointLight::modelMatrix()
{
	return Model;
}
