#include "StdAfx.h"

#include <cstdio>

#include "Engine.h"
#include "Triangle.h"
#include "MySphere.h"
#include "MeshTester.h"
#include <Input.h>

int _tmain(int argc, char* argv[])
{
	Engine *e = new Engine(1. / 60., 1024, 768);
	e->initialize();
	Input *input = new Input();
	Engine::enableMode(GL_DEPTH_TEST);

	input->setMouseMoveCallback();
	e->useStockCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), 45.0f);

	std::shared_ptr<Triangle> t(new Triangle());
	e->addToDisplayList(std::shared_ptr<Drawable>(t));
	e->addToUpdateList(std::shared_ptr<Updateable>(t));
	t = NULL;

	MySphere *s = new MySphere(32, 32, 1.0f);
	e->addToDisplayList(std::shared_ptr<Drawable>(s));
	s = NULL;

	MeshTester *test = new MeshTester();
	e->addToDisplayList(std::shared_ptr<Drawable>(test));
	test = NULL;

	e->start();
	return 0;
}