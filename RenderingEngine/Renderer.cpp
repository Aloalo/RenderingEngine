#include "Renderer.h"


Renderer::Renderer(void)
{
}


Renderer::~Renderer(void)
{
}

void Renderer::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	bool set = false;
	for(std::list<std::shared_ptr<Light> >::iterator k = lightList.begin(); k != lightList.end(); k++)
	{
		(*k)->renderingSetup(View, Projection);
		for(std::list<std::shared_ptr<LitObject> >::iterator i = litList.begin(); i != litList.end(); i++)
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
	for(std::list<std::shared_ptr<UnLitObject> >::iterator i = unLitList.begin(); i != unLitList.end(); i++)
		(*i)->draw(View, Projection);

}

void Renderer::addObject(std::shared_ptr<Drawable> &obj)
{
	obj->initDrawing();
	if(std::shared_ptr<LitObject> ptr = std::dynamic_pointer_cast<LitObject>(obj))
		litList.push_back(ptr);
	else if(std::shared_ptr<UnLitObject> ptr = std::dynamic_pointer_cast<UnLitObject>(obj))
		unLitList.push_back(ptr);
}

void Renderer::addLight(std::shared_ptr<Light> &light)
{
	lightList.push_back(light);
}

void Renderer::clear()
{
	litList.clear();
	unLitList.clear();
	lightList.clear();
}
