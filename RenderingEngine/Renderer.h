#pragma once

#include <list>
#include "LitObject.h"
#include "UnLitObject.h"
#include "Light.h"

namespace reng
{
	class Renderer
	{
	public:
		Renderer(void);
		~Renderer(void);

		void clear();

		void addObject(Drawable *obj);
		void addLight(Light *light);

		void draw(const glm::mat4 &Projection, const glm::mat4 &View);

	private:
		std::list<LitObject*> litList;
		std::list<UnLitObject*> unLitList;
		std::list<Light*> lightList;
	};
}
