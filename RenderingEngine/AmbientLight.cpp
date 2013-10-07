#include "AmbientLight.h"

Program *AmbientLight::p = NULL;

AmbientLight::AmbientLight(const glm::vec4 &_intensity)
	: Light(_intensity)
{
	if(p == NULL)
		p = new Program(VertexShader("../RenderingEngine/StockShaders/Lighting"), FragmentShader("../RenderingEngine/StockShaders/AmbientLight"));
}


AmbientLight::~AmbientLight(void)
{
}

void AmbientLight::renderingSetup(const glm::mat4 &View, const glm::mat4 &Projection)
{
	p->use();
	p->setUniform("ambientIntensity", intensity);
	p->setUniform("projectionMatrix", Projection);
}

void AmbientLight::collectData(std::shared_ptr<LitObject> &obj, const glm::mat4 &View, const glm::mat4 &Projection)
{
	glm::mat4 MV = View * obj->modelMatrix();
	p->setUniform("mvMatrix", MV);
	p->setUniform("materialAmbientColor", obj->getMaterial()->ambientColor);
}
