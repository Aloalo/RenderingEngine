#include "DiffuseLight.h"

using namespace glm;

namespace reng
{
	Program *DiffuseLight::p = NULL;
	TextureSampler DiffuseLight::imageSampler;

	DiffuseLight::DiffuseLight(const vec3 &_direction)
		: direction(_direction), Light(vec4())
	{
		if(p == NULL)
		{
			p = new Program(VertexShader("../RenderingEngine/StockShaders/Lighting"), FragmentShader("../RenderingEngine/StockShaders/DiffuseLight"));
			imageSampler.generate();
			imageSampler.samplerParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			imageSampler.samplerParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			imageSampler.samplerParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
			imageSampler.samplerParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);

			p->use();
			p->setUniform("textureSampler", 0);
			p->bindSamplerObjectToSampler("textureSampler", imageSampler);
		}
	}


	DiffuseLight::~DiffuseLight(void)
	{
	}

	void DiffuseLight::renderingSetup(const mat4 &View, const mat4 &Projection)
	{
		p->use();
		p->setUniform("projectionMatrix", Projection);
		p->setUniform("lightDir", direction);
	}

	void DiffuseLight::collectData(LitObject *obj, const mat4 &View, const mat4 &Projection)
	{
		glm::mat4 MV = View * obj->modelMatrix();
		p->setUniform("mvMatrix", MV);
		p->setUniform("normalMatrix", glm::transpose(glm::inverse(glm::mat3(MV))));
		p->setUniform("diffuseColor", obj->getMaterial().diffuseColor);

		glActiveTexture(GL_TEXTURE0 + p->getUniformi("textureSampler"));
		obj->getMaterial().diffuse_tex.bind();
	}
}