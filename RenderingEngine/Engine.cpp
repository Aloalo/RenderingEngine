#include "Engine.h"
#include <GL/glfw.h>
#include "Input.h"

int Engine::windowWidth = 1024;
int Engine::windowHeight = 768;
float Engine::updateInterval = 1. / 60.;
std::shared_ptr<CameraHandler> Engine::cam;
std::list<std::shared_ptr<Drawable> > Engine::displayList;
std::list<std::shared_ptr<Updateable> > Engine::updateList;
GLbitfield Engine::mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
glm::vec4 Engine::backgroundColor = glm::vec4(0.4);


Engine::Engine(float _updateInterval, int _windowWidth, int _windowHeight)
{
	updateInterval = _updateInterval;
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

Engine::~Engine()
{
	stop();
}


void Engine::stop()
{
	updateList.clear();
	displayList.clear();
}

void Engine::useStockCamera(const glm::vec3 &position, const glm::vec3 &direction, float FoV)
{
	Camera *c = new Camera(position, (float) windowWidth / (float) windowHeight, FoV);
	glm::vec3 d = glm::normalize(direction);

	float phiy = asin(d.y);
	float phix = atan2(d.x, d.z);
	c->rotate(phix, phiy);

	cam = std::shared_ptr<CameraHandler>(new StockCameraHandler(c, 3.0f, 0.005f));
	Input::addInputObserver(std::shared_ptr<InputObserver>(cam));
	addToUpdateList(std::shared_ptr<Updateable>(cam));
}

void Engine::setCamera(std::shared_ptr<CameraHandler> _cam)
{
	cam = _cam;
}

void Engine::addToDisplayList(std::shared_ptr<Drawable> d)
{
	displayList.push_back(d);
}

void Engine::addToUpdateList(std::shared_ptr<Updateable> u)
{
	updateList.push_back(u);
}

void Engine::start()
{
	initalizeLists();
	renderingLoop();
}

void Engine::initialize()
{
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(-1);
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!glfwOpenWindow(windowWidth, windowHeight, 0, 0, 0, 0, 32, 8, GLFW_WINDOW))
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		glfwTerminate();
		exit(-1);
	}

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(-1);
	}
}

void Engine::enableMode(GLenum mode)
{
	glEnable(mode);
}

void Engine::disableMode(GLenum mode)
{
	glDisable(mode);
}

void Engine::setBufferClearMask(GLbitfield _mask)
{
	mask = _mask;
}

void Engine::initalizeLists()
{
	for(std::list<std::shared_ptr<Drawable> >::iterator i = displayList.begin(); i != displayList.end(); i++)
		(*i)->initDrawing();

	for(std::list<std::shared_ptr<Updateable> >::iterator i = updateList.begin(); i != updateList.end(); i++)
		(*i)->initState();
}

void Engine::renderingLoop()
{
	while(true)
		nextFrame();
}

inline void Engine::nextFrame()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;

	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
	glClear(mask);
	
	for(std::list<std::shared_ptr<Updateable> >::iterator i = updateList.begin(); i != updateList.end(); i++)
	{
		if(*i == NULL)
			updateList.erase(i);
		(*i)->update(deltaTime);
	}

	glm::mat4 VPmatrix = getViewProjectionMatrix();

	for(std::list<std::shared_ptr<Drawable> >::iterator i = displayList.begin(); i != displayList.end(); i++)
	{
		if(*i == NULL)
			displayList.erase(i);
		(*i)->draw(VPmatrix);
	}

	glfwSwapBuffers();
}

void Engine::setBackgroundColor(glm::vec4 color)
{
	backgroundColor = color;
}

glm::mat4 Engine::getViewProjectionMatrix()
{
	return cam->getProjectionMatrix() * cam->getViewMatrix();
}
