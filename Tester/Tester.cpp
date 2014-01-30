#include <cstdio>
#include <iostream>
#include <tiny_obj_loader.h>

#include "Engine.h"
#include "Input.h"
#include "Lights.h"
#include "MovingLight.h"
#include "Geometry.h"
#include "SineCosine.h"
#include "NormalDrawer.h"

using namespace std;
using namespace glm;
using namespace tinyobj;

vector<Drawable*> junk;

void cleanUp()
{
	for(int i = 0; i < junk.size(); ++i)
		delete junk[i];
	junk.clear();
}

void addSineCosine()
{
	mat4 Model = translate(mat4(1.0f), vec3(0.0f, -10.0f, 0.0f));

	vec2 x[] = 
	{
		vec2(-20.0f, -20.0f), vec2(-20.0f, 20.0f), vec2(20.0f, 20.0f),
		vec2(-20.0f, -20.0f), vec2(20.0f, 20.0f), vec2(20.0f, -20.0f)
	};
	Mesh *mesh = new Mesh();
	FunctionGraph graph(new SineCosine());
	graph.generateGraph(x, 7, -1000.0f, mesh);
	graph.generateGraph(x+3, 7, -1000.0f, mesh);

	mesh->setOrientation(GL_CCW);
	mesh->applyIndexing();
	mesh->makeUpUVData();

	const Material mat(vec4(1.0f, 0.2f, 0.2f, 1.0f), vec4(0.1f, 0.1f, 0.1f, 1.0f), vec4(0.7f, 0.7f, 0.7f, 1.0f), 128.0f);

	Object3D *obj = new Object3D(mesh, mat);
	obj->setModelMatrix(Model);
	junk.push_back(obj);
	Engine::addToDisplayList(junk.back());

	//Engine::addToDisplayList(new NormalDrawer(*mesh, Model));
	mesh = NULL;
	obj = NULL;
}

void addSphere()
{
	vector<vec3> *vec = Sphere::generate(4, 1.0f, vec3(0.0f));
	Mesh *sphereMesh = new Mesh(*vec);
	delete vec;

	sphereMesh->setOrientation(GL_CCW);
	sphereMesh->calculateNormals();
	sphereMesh->interpolateNormals();
	sphereMesh->applyIndexing();
	sphereMesh->makeUpUVData();

	const Material mat(vec4(0.2f, 0.1f, 1.0f, 1.0f), vec4(0.2f, 0.1f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), 32.0f);
	junk.push_back(new Object3D(sphereMesh, mat));

	Engine::addToDisplayList(junk.back());

	//Engine::addToDisplayList(new NormalDrawer(*sphereMesh));
	sphereMesh = NULL;
}

void addObjFile(const string &path, const string &mtl_basepath = string())
{
	vector<shape_t> shapes;
	string err;
	if(mtl_basepath.empty())
		err = LoadObj(shapes, path.c_str());
	else
		err = LoadObj(shapes, path.c_str(), mtl_basepath.c_str());

	if(!err.empty())
	{
		cout << err << endl;
		cleanUp();
		exit(0);
	}

	//const Material mat(vec4(0.7f, 0.7f, 7.0f, 1.0f), vec4(0.8f, 0.8f, 0.7f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), 32.0f);
	for(int i = 0; i < shapes.size(); ++i)
		junk.push_back(Engine::addModelToDisplayList(shapes[i]));
}

int main(int argc, char* argv[])
{
	Engine e(1.f / 80.f, 1280, 720);
	Input input;
	Engine::enableMode(GL_DEPTH_TEST);
	Engine::enableMode(GL_CULL_FACE); 

	input.setMouseMoveCallback();
	e.useStockCamera(vec3(0.0f, 0.0f, -30.0f), vec3(0.0f, 0.0f, 1.0f), 45.0f, 4.0f);
	
	addSineCosine();
	//addSphere();
	//addObjFile("../Resources/powerplant/powerplant.obj", "../Resources/powerplant/");
	addObjFile("../Resources/buddha/buddha.obj", "../Resources/buddha/");
	//addObjFile("../Resources/cube/cube.obj", "../Resources/cube/");
	//addObjFile("../Resources/cornell_box/cornell_box.obj", "../Resources/cornell_box/");
	//addObjFile("../Resources/sibenik/sponza.obj", "../Resources/sibenik/");

	Light *lights[3] = 
	{
		new AmbientLight(vec4(0.3f, 0.3f, 0.3f, 1.0f)),
		new SpecularPointLight(vec3(5.0f, 0.0f, 0.0f), vec4(10.5f, 10.5f, 10.5f, 10.0f), 2.0f),
		new SpecularPointLight(vec3(-5.0f, 0.0f, 0.0f), vec4(10.0f, 10.0f, 10.0f, 1.0f), 3.0f)
	};

	Engine::addLight(lights[0]);
	Engine::addLight(lights[1]);
	Engine::addLight(lights[2]);

	Engine::setWindowTitle("Tester");
	e.start();
	for(int i = 0; i < 3; ++i)
		delete lights[i];
	cleanUp();

	return 0;
}