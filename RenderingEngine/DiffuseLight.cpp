#include "DiffuseLight.h"

Program *DiffuseLight::p = NULL;

DiffuseLight::DiffuseLight(const glm::vec3 &_direction)
	: direction(_direction), Light(glm::vec4())
{
	if(p == NULL)
		p = new Program(VertexShader("../RenderingEngine/StockShaders/Lighting"), FragmentShader("../RenderingEngine/StockShaders/DiffuseLight"));
}


DiffuseLight::~DiffuseLight(void)
{
}

void DiffuseLight::renderingSetup(const glm::mat4 &View, const glm::mat4 &Projection)
{
	p->use();
	p->setUniform("projectionMatrix", Projection);
	p->setUniform("lightDir", direction);
}

void DiffuseLight::collectData(LitObject *obj, const glm::mat4 &View, const glm::mat4 &Projection)
{
	glm::mat4 MV = View * obj->modelMatrix();
	p->setUniform("mvMatrix", MV);
	p->setUniform("normalMatrix", glm::transpose(glm::inverse(glm::mat3(MV))));
	p->setUniform("diffuseColor", obj->getMaterial().diffuseColor);
	if(obj->getTexture() != NULL)
		p->setUniform("textureSampler", (int)obj->getTexture()->getID());
}
