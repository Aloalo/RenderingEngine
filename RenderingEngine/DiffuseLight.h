#pragma once

#include "Light.h"
#include "TextureSampler.h"

namespace reng
{
	class DiffuseLight :
		public Light
	{
	public:
		DiffuseLight(const glm::vec3 &_direction);
		~DiffuseLight(void);

		void renderingSetup(const glm::mat4 &View, const glm::mat4 &Projection);
		void collectData(LitObject *obj, const glm::mat4 &View, const glm::mat4 &Projection);

	private:
		glm::vec3 direction;
		static Program *p;
		static TextureSampler imageSampler;
	};
}

