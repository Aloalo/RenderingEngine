#include "AmbientLight.h"

using namespace glm;

namespace reng
{
	Program *AmbientLight::p = NULL;
	TextureSampler AmbientLight::imageSampler;

	AmbientLight::AmbientLight(const vec4 &_intensity)
		: Light(_intensity)
	{
		if(p == NULL)
		{
			p = new Program(VertexShader("../RenderingEngine/StockShaders/Lighting"), FragmentShader("../RenderingEngine/StockShaders/AmbientLight"));
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

	AmbientLight::~AmbientLight(void)
	{
	}

	void AmbientLight::renderingSetup(const mat4 &View, const mat4 &Projection)
	{
		p->use();
		p->setUniform("ambientIntensity", intensity);
		p->setUniform("projectionMatrix", Projection);
	}

	void AmbientLight::collectData(LitObject *obj, const mat4 &View, const mat4 &Projection)
	{
		glm::mat4 MV = View * obj->modelMatrix();
		p->setUniform("mvMatrix", MV);
		p->setUniform("diffuseColor", obj->getMaterial().diffuseColor);

		glActiveTexture(GL_TEXTURE0 + p->getUniformi("textureSampler"));
		obj->getMaterial().diffuse_tex.bind();
	}
}
