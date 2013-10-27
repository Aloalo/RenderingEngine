#include "StdAfx.h"

#include <cstdio>

#include "Engine.h"
#include "Input.h"
#include "Lights.h"
#include "MovingLight.h"
#include "Geometry.h"
#include "SineCosine.h"
#include <NormalDrawer.h>

void addSineCosine()
{
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, 0.0f));

	glm::vec2 x[] = 
	{
		glm::vec2(-20.0f, -20.0f), glm::vec2(-20.0f, 20.0f), glm::vec2(20.0f, 20.0f),
		glm::vec2(-20.0f, -20.0f), glm::vec2(20.0f, 20.0f), glm::vec2(20.0f, -20.0f)
	};
	Mesh *mesh = new Mesh();
	FunctionGraph graph(new SineCosine());
	graph.generateGraph(x, 7, -1000.0f, mesh);
	graph.generateGraph(x+3, 7, -1000.0f, mesh);

	mesh->setOrientation(GL_CCW);
	mesh->applyIndexing();

	Material mat(glm::vec4(1.0f, 0.2f, 0.2f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 128.0f);

	Engine::addToDisplayList(mesh, mat, Model);

	mesh = NULL;
	//Engine::addToDisplayList(std::shared_ptr<Drawable>(new NormalDrawer(mesh, Model)));
}

void addSphere()
{
	std::vector<glm::vec3> *vec = Sphere::generate(4, 1.0f, glm::vec3(0.0f));
	Mesh *sphereMesh = new Mesh(*vec);
	delete vec;

	sphereMesh->setOrientation(GL_CCW);
	sphereMesh->calculateNormals();
	sphereMesh->interpolateNormals();
	sphereMesh->applyIndexing();

	const Material mat(glm::vec4(0.2f, 0.1f, 1.0f, 1.0f), glm::vec4(0.2f, 0.1f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 32.0f);
	Engine::addToDisplayList(sphereMesh, mat, glm::mat4(1.0f));


	Engine::addToDisplayList(std::shared_ptr<Drawable>(new NormalDrawer(*sphereMesh)));
	sphereMesh = NULL;
}

int _tmain(int argc, char* argv[])
{
	Engine *e = new Engine(1. / 60., 1024, 768);
	Input *input = new Input();
	Engine::enableMode(GL_DEPTH_TEST);
	Engine::enableMode(GL_CULL_FACE); 

	input->setMouseMoveCallback();
	e->useStockCamera(glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(0.0f, 0.0f, 1.0f), 45.0f, 4.0f);


	addSphere();
	addSineCosine();

	Engine::addLight(std::shared_ptr<Light>(new AmbientLight(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f))));
	Engine::addLight(std::shared_ptr<Light>(new DiffuseLight(glm::vec3(-1.0f, 1.0f, -1.0f))));
	Engine::addLight(std::shared_ptr<Light>(new SpecularPointLight(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec4(10.5f, 10.5f, 10.5f, 10.0f), 2.0f)));

	std::shared_ptr<Light> pointLight(new SpecularPointLight(glm::vec3(0.0f, -5.0f, 5.0f), glm::vec4(10.0f, 10.0f, 10.0f, 1.0f), 3.0f));
	Engine::addLight(pointLight);
	MovingLight *ptr = new MovingLight(pointLight);
	e->addToUpdateList(std::shared_ptr<Updateable>(ptr));
	pointLight = NULL;
	ptr = NULL;

	Engine::setWindowTitle("Tester");
	e->start();
	return 0;
}