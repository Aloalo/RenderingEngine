#include "Renderer.h"
#include "UIManager.h"

using namespace glm;

namespace reng
{
	Renderer::Renderer(void)
	{
	}


	Renderer::~Renderer(void)
	{
	}

	void Renderer::draw(const mat4 &View, const mat4 &Projection)
	{
		glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
		bool set = false;
		for(auto k = lightList.begin(); k != lightList.end(); ++k)
		{
			(*k)->renderingSetup(View, Projection);
			for(auto i = litList.begin(); i != litList.end(); ++i)
			{
				(*k)->collectData(*i, View, Projection);
				(*i)->draw(View, Projection);
			}

			if(!set)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE);
				glDepthFunc(GL_EQUAL);
				set = true;
			}
		}

		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
		for(auto i = unLitList.begin(); i != unLitList.end(); ++i)
			(*i)->draw(View, Projection);

		UIManager::get().draw();
	}

	void Renderer::addObject(Drawable *obj)
	{
		obj->initDrawing();
		if(LitObject *ptr = dynamic_cast<LitObject*>(obj))
			litList.push_back(ptr);
		else if(UnLitObject *ptr = dynamic_cast<UnLitObject*>(obj))
			unLitList.push_back(ptr);
	}

	void Renderer::addLight(Light *light)
	{
		lightList.push_back(light);
	}

	void Renderer::clear()
	{
		litList.clear();
		unLitList.clear();
		lightList.clear();
	}
}
