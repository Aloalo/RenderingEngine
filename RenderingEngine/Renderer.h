#pragma once

#include <list>
#include "LitObject.h"
#include "UnLitObject.h"
#include "Light.h"

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	void clear();

	void addObject(std::shared_ptr<Drawable> &obj);
	void addLight(std::shared_ptr<Light> &light);

	void draw(const glm::mat4 &Projection, const glm::mat4 &View);

private:
	std::list<std::shared_ptr<LitObject> > litList;
	std::list<std::shared_ptr<UnLitObject> > unLitList;
	std::list<std::shared_ptr<Light> > lightList;
};

