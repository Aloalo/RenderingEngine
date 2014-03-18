#include <cstdio>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

#include "Engine.h"
#include "Input.h"
#include "Lights.h"
#include "MovingLight.h"
#include "Geometry.h"
#include "SineCosine.h"
#include "NormalDrawer.h"

#include "Button.h"
#include "VerticalLayoutManager.h"
#include "Label.h"

using namespace std;
using namespace glm;
using namespace reng;

vector<Drawable*> junk;
vector<Light*> lights;

void cleanUp()
{
	for(auto jnk : junk)
		delete jnk;
	for(auto light : lights)
		delete light;
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
}

void addObjFile(const string &path, const string &folder, const mat4 &Model = mat4(1.0f))
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if(!scene)
	{
		printf("%s\n", importer.GetErrorString());
		return;
	}

	for(int i = 0; i < scene->mNumMeshes; ++i)
	{
		Object3D *obj = new Object3D(new Mesh(scene->mMeshes[i]), Material(scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], folder), Model);
		Engine::addToDisplayList(obj);
		junk.push_back(obj);
	}
	
}

struct TintChanger
{
	TintChanger(vec4 color) :
		color(color) {}

	void operator()()
	{
		UIManager::get().color = color;
	}

	vec4 color;
};

int main(int argc, char* argv[])
{
	Engine e(1.f / 80.f, 1280, 720);
	Engine::setWindowTitle("Tester");
	Input input;
	Engine::enableMode(GL_DEPTH_TEST);
	Engine::enableMode(GL_CULL_FACE); 

	e.useStockCamera(vec3(0.0f, 0.0f, -30.0f), vec3(0.0f, 0.0f, 1.0f), 45.0f, 4.0f);
	
	
	//addSineCosine();
	//addSphere();
	addObjFile("../Resources/crytek-sponza/sponza.obj", "../Resources/crytek-sponza/", scale(mat4(1.0f), vec3(0.01f, 0.01f, 0.01f)));
	//addObjFile("../Resources/nissan/nissan.obj", "../Resources/nissan/", scale(mat4(1.0f), vec3(0.05f, 0.05f, 0.05f)));
	//addObjFile("../Resources/demon/demon1_OBJ.obj", "../Resources/demon/", translate(mat4(1.0f), vec3(-10, 0, 0)));
	
	//addObjFile("../Resources/sibenik/sibenik.obj", "../Resources/sibenik/");
	//addObjFile("../Resources/dragon/dragon.obj", "../Resources/dragon/", scale(mat4(1.0f), vec3(3.1f, 3.1f, 3.1f)));
	//addObjFile("../Resources/rungholt/rungholt.obj", "../Resources/rungholt/", scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)));
	//addObjFile("../Resources/head/head.obj", "../Resources/head/");
	//addObjFile("../Resources/powerplant/powerplant.obj", "../Resources/powerplant/", scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)));
	//addObjFile("../Resources/buddha/buddha.obj", "../Resources/buddha/", scale(mat4(1.0f), vec3(3.1f, 3.1f, 3.1f)));
	//addObjFile("../Resources/cube/cube.obj", "../Resources/cube/");
	//addObjFile("../Resources/conference/conference.obj", "../Resources/conference/", scale(mat4(1.0f), vec3(0.01f, 0.01f, 0.01f)));

	lights.push_back(new AmbientLight(vec4(0.3f, 0.3f, 0.3f, 1.0f)));
	lights.push_back(new SpecularPointLight(vec3(5.0f, 4.0f, 0.0f), vec4(10.5f, 10.5f, 10.5f, 10.0f), 2.0f));
	lights.push_back(new DiffuseLight(vec3(-1.0f, 1.0f, 1.0f)));
	lights.push_back(new SpecularPointLight(vec3(-5.0f, 6.0f, 0.0f), vec4(10.0f, 10.0f, 10.0f, 1.0f), 3.0f));

	for(auto light : lights)
		Engine::addLight(light);
	
	FontFace *ff = new FontFace("../DefaultTextures/font.png", 10, 10, ' ', 0.8);
	Font *f = new Font(ff, 18);
	f->halign = Font::HAlignment::Center;
	f->valign = Font::VAlignment::Middle;

	UIManager::get().lm = new VerticalLayoutManager;

	Container *cont = new Container;
	cont->lm = new VerticalLayoutManager;
	cont->color = vec4(.4, .4, .4, 0.7);
	UIManager::get().add(cont);

	Button *b1 = new Button;
	b1->color = vec4(1, 0, 0, 1);
	b1->setAction(new TintChanger(vec4(1, 0, 0, 0.2)));
	b1->text = "Red";
	b1->font = f;
	cont->add(b1);

	Button *b2 = new Button;
	b2->color = vec4(0, 1, 0, 1);
	b2->setAction(new TintChanger(vec4(0, 1, 0, 0.2)));
	b2->text = "Green";
	b2->font = f;
	cont->add(b2);

	Button *b3 = new Button;
	b3->color = vec4(0, 0, 1, 1);
	b3->setAction(new TintChanger(vec4(0, 0, 1, 0.2)));
	b3->text = "Blue";
	b3->font = f;
	cont->add(b3);

	Button *b4 = new Button;
	b4->color = vec4(1, 1, 1, 1);
	b4->setAction(new TintChanger(vec4(1, 1, 1, 0)));
	b4->text = "White";
	b4->font = f;
	cont->add(b4);

	Button *b5 = new Button;
	b5->d = vec2(150, 150);
	b5->color = vec4(1, 0, 1, 1);
	auto func = [] () {puts("blah");};
	b5->setAction(&func);
	b5->text = "Trololo\nlololo\nlololo\nlolololo\nlololo";
	b5->font = f;
	cont->add(b5);

	cont->pack();

	e.start();
	cleanUp();
	delete cont;

	return 0;
}