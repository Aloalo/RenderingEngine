#include <cstdio>

#include "Engine.h"
#include "Input.h"
#include "Lights.h"
#include "MovingLight.h"
#include "Geometry.h"
#include "SineCosine.h"
#include <NormalDrawer.h>


Mesh *mesh;
Mesh *sphereMesh;

void addSineCosine()
{
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, 0.0f));

	glm::vec2 x[] = 
	{
		glm::vec2(-20.0f, -20.0f), glm::vec2(-20.0f, 20.0f), glm::vec2(20.0f, 20.0f),
		glm::vec2(-20.0f, -20.0f), glm::vec2(20.0f, 20.0f), glm::vec2(20.0f, -20.0f)
	};
	mesh = new Mesh();
	FunctionGraph graph(new SineCosine());
	graph.generateGraph(x, 7, -1000.0f, mesh);
	graph.generateGraph(x+3, 7, -1000.0f, mesh);

	mesh->setOrientation(GL_CCW);
	mesh->applyIndexing();

	Material mat(glm::vec4(1.0f, 0.2f, 0.2f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 128.0f);

	Engine::addToDisplayList(mesh, mat, Model);

	//Engine::addToDisplayList(std::shared_ptr<Drawable>(new NormalDrawer(mesh, Model)));
}

void addSphere()
{
	std::vector<glm::vec3> *vec = Sphere::generate(4, 1.0f, glm::vec3(0.0f));
	sphereMesh = new Mesh(*vec);
	delete vec;

	sphereMesh->setOrientation(GL_CCW);
	sphereMesh->calculateNormals();
	sphereMesh->interpolateNormals();
	sphereMesh->applyIndexing();

	const Material mat(glm::vec4(0.2f, 0.1f, 1.0f, 1.0f), glm::vec4(0.2f, 0.1f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 32.0f);
	Engine::addToDisplayList(sphereMesh, mat, glm::mat4(1.0f));


	Engine::addToDisplayList(new NormalDrawer(*sphereMesh));
}

int main(int argc, char* argv[])
{
	Engine e(1. / 80., 1280, 720);
	Input input;
	Engine::enableMode(GL_DEPTH_TEST);
	Engine::enableMode(GL_CULL_FACE); 

	input.setMouseMoveCallback();
	e.useStockCamera(glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(0.0f, 0.0f, 1.0f), 45.0f, 4.0f);

	addSphere();
	addSineCosine();

	Light *lights[4] = 
	{
		new AmbientLight(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)),
		new DiffuseLight(glm::vec3(-1.0f, 1.0f, -1.0f)),
		new SpecularPointLight(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec4(10.5f, 10.5f, 10.5f, 10.0f), 2.0f),
		new SpecularPointLight(glm::vec3(0.0f, -5.0f, 5.0f), glm::vec4(10.0f, 10.0f, 10.0f, 1.0f), 3.0f)
	};

	Engine::addLight(lights[0]);
	Engine::addLight(lights[1]);
	Engine::addLight(lights[2]);
	Engine::addLight(lights[3]);

	MovingLight *ptr = new MovingLight(lights[3]);
	e.addToUpdateList(ptr);

	Engine::setWindowTitle("Tester");
	e.start();

	delete mesh;
	delete sphereMesh;
	delete ptr;
	for(int i = 0; i < 4; ++i)
		delete lights[i];

	return 0;
}