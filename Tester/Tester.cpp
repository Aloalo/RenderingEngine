#include "StdAfx.h"

#include <cstdio>

#include "Engine.h"
#include "MySphere.h"
#include "MeshTester.h"
#include <Input.h>
#include <SpecularPointLight.h>
#include <AmbientLight.h>
#include <DiffuseLight.h>
#include "MovingLight.h"

int _tmain(int argc, char* argv[])
{
	Engine *e = new Engine(1. / 60., 1024, 768);
	Input *input = new Input();
	Engine::enableMode(GL_DEPTH_TEST);
	Engine::enableMode(GL_CULL_FACE); 

	input->setMouseMoveCallback();
	e->useStockCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), 45.0f);

	MySphere *s = new MySphere(32, 32, 1.0f);
	e->addToDisplayList(std::shared_ptr<Drawable>(s));
	s = NULL;

	MeshTester *test = new MeshTester();
	e->addToDisplayList(std::shared_ptr<Drawable>(test));
	test = NULL;

	Engine::addLight(std::shared_ptr<Light>(new AmbientLight(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f))));
	Engine::addLight(std::shared_ptr<Light>(new DiffuseLight(glm::vec3(-1.0f, 1.0f, -1.0f))));
	Engine::addLight(std::shared_ptr<Light>(new SpecularPointLight(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec4(10.5f, 10.5f, 10.5f, 10.0f), 2.0f)));

	std::shared_ptr<Light> pointLight(new SpecularPointLight(glm::vec3(0.0f, -5.0f, 5.0f), glm::vec4(10.5f, 10.5f, 10.5f, 10.0f), 3.0f));
	Engine::addLight(pointLight);
	MovingLight *ptr = new MovingLight(pointLight);
	e->addToUpdateList(std::shared_ptr<Updateable>(ptr));
	pointLight = NULL;
	ptr = NULL;

	e->start();
	return 0;
}